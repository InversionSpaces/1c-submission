#pragma once

#include <iostream>
#include <list>
#include <cctype>

class Tokenizer {
    std::istream& stream;

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
};

class Decoder {
    using chunk_t = std::list<std::string>;

    Tokenizer tokenizer;

    void process_chunk(const chunk_t& chunk, const size_t position) const {
        std::string code;

        size_t pos = 0;
        for (const auto& token: chunk) {
            if (pos >= token.size())
                break;
            code.push_back(token.at(pos));
            ++pos;
        }

        std::cout << code << " -> " << position << std::endl;
    }

public:

    static const size_t CHUNK_SIZE = 5;

    Decoder(std::istream& stream) : tokenizer(stream) {}

    void process() {
        chunk_t chunk;

        std::string token;
        for (size_t size = 0; size < CHUNK_SIZE; ++size) {
            if (!tokenizer.get_token(token)) {
                process_chunk(chunk, 0);
                return;
            }

            chunk.emplace_back(std::move(token));
        }

        process_chunk(chunk, 0);

        size_t position = 0;
        while (tokenizer.get_token(token)) {
            chunk.emplace_back(std::move(token));
            chunk.pop_front();

            ++position;
            process_chunk(chunk, position);
        }
    }
};
