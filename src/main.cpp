#include <iostream>
#include <memory>
#include <cassert>

//using uint8 = unsigned char;

char const CHAR_TABLE[64] {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                              'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                              '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};
char const filler_char = '=';

void encode_base64(uint8_t const *original_str, uint8_t* encoded_str) {
    assert(original_str != nullptr);
    assert(encoded_str != nullptr);
    unsigned int constexpr ascii_byte_size = 8u;
    unsigned int constexpr base64_char_size = 6u;

    unsigned int origin_str_index = 0u;
    unsigned int encoded_str_index = 0u;
    unsigned int tail_size = 0u;

    unsigned int bit_sextet_prefix = 0u;
    unsigned int char_table_index = 0u;

    while (original_str[origin_str_index] != '\0') {
        tail_size += ascii_byte_size - base64_char_size;
        char prefix = bit_sextet_prefix << (ascii_byte_size - tail_size);
        char postfix = original_str[origin_str_index] >> tail_size;
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
    if (tail_size != 0)
    {
        unsigned int last_coded_char_index = original_str[origin_str_index - 1u] & ((1u << tail_size) - 1u) << (base64_char_size - tail_size);
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

void decode_base64(uint8_t const *encoded_str, uint8_t* restored_str) {
    assert(encoded_str != nullptr);
    assert(restored_str != nullptr);

}

int main(int argc, char**argv)
{
    uint8_t original_str[] {"Many hands make light work."};
    uint8_t encoded_str[100] {'\0'};
    uint8_t restored_str[100] {'\0'};
    encode_base64(original_str, encoded_str);
    std::cout << encoded_str << std::endl;
    decode_base64(encoded_str, restored_str);
    std::cout << restored_str << std::endl;

    return 0;
}
