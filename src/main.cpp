#include <iostream>
#include <string>

#include <decoder.hpp>

int main() {
    Decoder decoder(std::cin);
    CodeTree code_tree = std::move(decoder).gen_code_tree();
}
