#include "tea.hpp"
#include <iostream>
#include <bitset>

uint32_t* convert_64_to_32(uint64_t input){

    uint32_t* v = new uint32_t[2]();

    int pos = 0;

    for(int i=0;i<64;i++){

        if(i >= 32)
            pos = 1;
        
        v[pos] |= ((input & (1 << i)) >> pos*32);

    }

    // std::bitset<64> in_bin(input);
    // std::bitset<32> v_0(v[0]);
    // std::bitset<32> v_1(v[1]);

    // std::cout << in_bin << " -> [" << v_0 << "] + [" << v_1 << "]\n";

    return v;
}

uint64_t convert_32_to_64(uint32_t* input){
    uint64_t output = 0;

    for(int i=0;i<2;i++){
        for(int j=0;j<32;j++){
            uint64_t  a = (input[i] & (1 << j));

            uint64_t  b = a << (i*32);

            output |= b ;
        }
    }

    // std::bitset<64> in_bin(output);
    // std::bitset<32> v_0(input[0]);
    // std::bitset<32> v_1(input[1]);

    // std::cout << in_bin << " <- [" << v_0 << "] + [" << v_1 << "]\n";

    return output;
}

void encrypt (uint32_t v[2], uint32_t k[4]) {
    uint32_t v0=v[0], v1=v[1], sum=0, i;           /* set up */
    uint32_t delta=0x9E3779B9;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}

void decrypt (uint32_t v[2], uint32_t k[4]) {
    uint32_t v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /* set up; sum is 32*delta */
    uint32_t delta=0x9E3779B9;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        sum -= delta;
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}

uint64_t decrypt_64bit(uint64_t input, uint32_t k[4]){
    uint64_t output = 0;

    uint32_t* v = convert_64_to_32(input);

    decrypt(v,k);

    output = convert_32_to_64(v);

    return output;
}

unsigned long encrypt_64bit(unsigned long input, uint32_t k[4]){
    unsigned long int output = 0;

    uint32_t* v = convert_64_to_32(input);

    encrypt(v,k);

    output = convert_32_to_64(v);

    return output;
}
