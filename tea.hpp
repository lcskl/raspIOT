#ifndef TEA_HPP
#define TEA_HPP

#include <cstdint>

uint32_t* convert_64_to_32(uint64_t input);

uint64_t convert_32_to_64(uint32_t* input);

void encrypt (uint32_t v[2], uint32_t k[4]);

void decrypt (uint32_t v[2], uint32_t k[4]);

uint64_t decrypt_64bit(uint64_t input, uint32_t k[4]);

uint64_t encrypt_64bit(uint64_t input, uint32_t k[4]);

#endif
