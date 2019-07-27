#include <iostream>
#include <memory>
#include <cassert>

//using uint8 = unsigned char;

uint8_t const CHAR_TABLE[64] {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                              'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
uint8_t const filler_char = '=';

void encode_base64(uint8_t const *original_str, uint8_t* encoded_str) {
    assert(original_str != nullptr);
    assert(encoded_str != nullptr);
    uint8_t const ascii_byte_size = 8u;
    uint8_t const base64_char_size = 6u;

    unsigned int origin_str_index = 0;
    unsigned int encoded_str_index = 0u;
    uint8_t tail_size = 0u;
    uint8_t bit_sextet_prefix = 0u;
    uint8_t char_table_index = 0u;

    while (original_str[origin_str_index] != '\0') {
        tail_size += ascii_byte_size - base64_char_size;
        auto prefix = bit_sextet_prefix << (ascii_byte_size - tail_size);
        auto postfix = original_str[origin_str_index] >> tail_size;
        char_table_index = prefix + postfix;
        bit_sextet_prefix = original_str[origin_str_index] & ((1u << tail_size) - 1u);
        encoded_str[encoded_str_index] = CHAR_TABLE[char_table_index];
        ++origin_str_index;
        ++encoded_str_index;
        if (tail_size == base64_char_size) {
            encoded_str[encoded_str_index] = CHAR_TABLE[bit_sextet_prefix];
            tail_size = 0u;
            ++encoded_str_index;
            bit_sextet_prefix = 0u;
        }
    }
    if (tail_size != 0u)
    {
        uint8_t last_coded_char_index = original_str[origin_str_index - 1u] & ((1u << tail_size) - 1u) << (base64_char_size - tail_size);
        encoded_str[encoded_str_index] = CHAR_TABLE[char_table_index];
        do
        {
            ++encoded_str_index;
            encoded_str[encoded_str_index] = filler_char;
            tail_size += 2u;
        }
        while (tail_size < base64_char_size);
        ++encoded_str_index;
    }
    encoded_str[encoded_str_index] = '\0';
}

void decode_base64(uint8_t const *encoded_str, uint8_t* original_str) {
    assert(encoded_str != nullptr);
    assert(original_str != nullptr);
}

int main(int argc, char**argv)
{
    uint8_t original_str[] {"ManMa"};
    uint8_t encoded_str[10] {'\0'};
    encode_base64(original_str, encoded_str);
    std::cout << encoded_str << std::endl;

    return 0;
}
