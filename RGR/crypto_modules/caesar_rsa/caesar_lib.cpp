#include "crypto_interface.h"

static AlgorithmInfo info = {"caesar", 1};

extern "C" const AlgorithmInfo* get_algorithm_info() {
    return &info;
}

extern "C" size_t get_output_size(size_t input_size, int operation_type) {
    return input_size;
}

extern "C" int encrypt(ConstBuffer key, ConstBuffer input, MutBuffer* output) {
    if (output->size < input.size) return -1;
    for (size_t i = 0; i < input.size; i++) {
        output->data[i] = input.data[i] + key.data[0];
    }
    return 0;
}

extern "C" int decrypt(ConstBuffer key, ConstBuffer input, MutBuffer* output) {
    if (output->size < input.size) return -1;
    for (size_t i = 0; i < input.size; i++) {
        output->data[i] = input.data[i] - key.data[0];
    }
    return 0;
}
