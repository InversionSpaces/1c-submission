#pragma once

#include <iostream>
#include <cctype>
#include <string>

class Tokenizer {
public:
    Tokenizer(std::istream& stream) : stream(stream) {}

    bool get_token(std::string& token) {
        token.clear();

        char symbol = 0;
        while (stream.get(symbol) && !std::isalpha(symbol));

        if (!std::isalpha(symbol))
            return false;

        token.push_back(symbol);

        while (stream.get(symbol) && std::isalpha(symbol))
            token.push_back(symbol);

        return true;
    }

private:
    std::istream& stream;
};
