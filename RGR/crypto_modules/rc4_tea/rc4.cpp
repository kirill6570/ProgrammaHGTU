#include "crypto_interface.h"
#include <cstring>
#include <array>

static AlgorithmInfo info = {"rc4", 16};

extern "C" const AlgorithmInfo* get_algorithm_info() {
    return &info;
}

extern "C" size_t get_output_size(size_t input_size, int operation_type) {
    return input_size;
}

extern "C" int encrypt(ConstBuffer key, ConstBuffer input, MutBuffer* output) {
    if (output->size < input.size) return -1;
    if (key.size != 16) return -1;
    
    std::array<uint8_t, 256> S;
    for (int i = 0; i < 256; i++) S[i] = i;
    
    uint8_t j = 0;
    for (int i = 0; i < 256; i++) {
        j = j + S[i] + key.data[i % key.size];
        std::swap(S[i], S[j]);
    }
    
    uint8_t i = 0;
    j = 0;
    for (size_t n = 0; n < input.size; n++) {
        i++;
        j += S[i];
        std::swap(S[i], S[j]);
        uint8_t K = S[(S[i] + S[j]) % 256];
        output->data[n] = input.data[n] ^ K;
    }
    
    return 0;
}

extern "C" int decrypt(ConstBuffer key, ConstBuffer input, MutBuffer* output) {
    return encrypt(key, input, output);
}
