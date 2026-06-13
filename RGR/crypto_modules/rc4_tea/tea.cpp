#include "crypto_interface.h"
#include <cstring>
#include <vector>
#include <random>

static AlgorithmInfo info = {"tea", 16};

const int TEA_ROUNDS = 32;
const uint32_t DELTA = 0x9E3779B9;

void encrypt_block(uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = 0;
    for (int i = 0; i < TEA_ROUNDS; i++) {
        sum += DELTA;
        v0 += ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        v1 += ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
    }
    v[0] = v0;
    v[1] = v1;
}

void decrypt_block(uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0 = v[0], v1 = v[1];
    uint32_t sum = DELTA * TEA_ROUNDS;
    for (int i = 0; i < TEA_ROUNDS; i++) {
        v1 -= ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
        v0 -= ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        sum -= DELTA;
    }
    v[0] = v0;
    v[1] = v1;
}

void load_key(const uint8_t* key_data, uint32_t k[4]) {
    for (int i = 0; i < 4; i++) {
        k[i] = (key_data[i*4] << 24) | (key_data[i*4+1] << 16) | (key_data[i*4+2] << 8) | key_data[i*4+3];
    }
}

extern "C" const AlgorithmInfo* get_algorithm_info() {
    static AlgorithmInfo info = {"tea", 16};
    return &info;
}

extern "C" size_t get_output_size(size_t input_size, int operation_type) {
    if (operation_type == 0) {
        size_t block_size = 8;
        size_t pad = block_size - (input_size % block_size);
        if (pad == 0) pad = block_size;
        return input_size + pad;
    } else {
        return input_size;
    }
}

extern "C" int encrypt(ConstBuffer key, ConstBuffer input, MutBuffer* output) {
    if (key.size != 16) return -1;
    if (output->size < input.size + 8) return -1;
    
    uint32_t k[4];
    load_key(key.data, k);
    
    size_t block_size = 8;
    size_t pad = block_size - (input.size % block_size);
    if (pad == 0) pad = block_size;
    
    std::vector<uint8_t> plain(input.size + pad);
    memcpy(plain.data(), input.data, input.size);
    for (size_t i = input.size; i < plain.size(); i++) plain[i] = pad;
    
    for (size_t i = 0; i < plain.size(); i += 8) {
        uint32_t v[2];
        v[0] = (plain[i] << 24) | (plain[i+1] << 16) | (plain[i+2] << 8) | plain[i+3];
        v[1] = (plain[i+4] << 24) | (plain[i+5] << 16) | (plain[i+6] << 8) | plain[i+7];
        encrypt_block(v, k);
        output->data[i] = (v[0] >> 24) & 0xFF;
        output->data[i+1] = (v[0] >> 16) & 0xFF;
        output->data[i+2] = (v[0] >> 8) & 0xFF;
        output->data[i+3] = v[0] & 0xFF;
        output->data[i+4] = (v[1] >> 24) & 0xFF;
        output->data[i+5] = (v[1] >> 16) & 0xFF;
        output->data[i+6] = (v[1] >> 8) & 0xFF;
        output->data[i+7] = v[1] & 0xFF;
    }
    
    return 0;
}

extern "C" int decrypt(ConstBuffer key, ConstBuffer input, MutBuffer* output) {
    if (key.size != 16) return -1;
    if (input.size % 8 != 0) return -1;
    if (output->size < input.size) return -1;
    
    uint32_t k[4];
    load_key(key.data, k);
    
    std::vector<uint8_t> plain(input.size);
    
    for (size_t i = 0; i < input.size; i += 8) {
        uint32_t v[2];
        v[0] = (input.data[i] << 24) | (input.data[i+1] << 16) | (input.data[i+2] << 8) | input.data[i+3];
        v[1] = (input.data[i+4] << 24) | (input.data[i+5] << 16) | (input.data[i+6] << 8) | input.data[i+7];
        decrypt_block(v, k);
        plain[i] = (v[0] >> 24) & 0xFF;
        plain[i+1] = (v[0] >> 16) & 0xFF;
        plain[i+2] = (v[0] >> 8) & 0xFF;
        plain[i+3] = v[0] & 0xFF;
        plain[i+4] = (v[1] >> 24) & 0xFF;
        plain[i+5] = (v[1] >> 16) & 0xFF;
        plain[i+6] = (v[1] >> 8) & 0xFF;
        plain[i+7] = v[1] & 0xFF;
    }
    
    uint8_t pad = plain[plain.size() - 1];
    if (pad > 8 || pad == 0) return -1;
    
    size_t out_size = plain.size() - pad;
    memcpy(output->data, plain.data(), out_size);
    
    return 0;
}
