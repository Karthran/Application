#pragma once
#include <string>
#include <memory>

typedef unsigned int uint;

const uint one_block_size_bytes = 64;  // количество байб в блоке
const uint one_block_size_uints = 16;    // количество 4байтовых  в блоке
const uint block_expend_size_uints = 80;  // количество 4байтовых в дополненном блоке

const uint SHA1HASHLENGTHBYTES = 20;
const uint SHA1HASHLENGTHUINTS = 5;

typedef uint* Block;
typedef uint ExpendBlock[block_expend_size_uints];

const uint H[5] = {
    0x67452301,
    0xEFCDAB89,
    0x98BADCFE,
    0x10325476,
    0xC3D2E1F0
}; // константы, согласно стандарту

auto cycle_shift_left(uint val, int bit_count) -> uint;
auto bring_to_human_view(uint val) -> uint;

//uint* sha1(char* message, uint msize_bytes); // отданный массив нужно удалить вручную
auto sha1(const std::string& message) -> std::shared_ptr<uint[]>;  // отданный массив нужно удалить вручную