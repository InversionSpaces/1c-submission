#include <iostream>
#include <string>

#include <decoder.hpp>

int main() {
    Tokenizer tokenizer(std::cin);
    std::string token;
    while (tokenizer.get_token(token))
        std::cout << token << std::endl;
}
