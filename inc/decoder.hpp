#pragma once

#include <list>
#include <string>
#include <optional>

#include <code_tree.hpp>
#include <tokenizer.hpp>

namespace solution {
class Decoder {
    using chunk_t = std::list<std::string>;

    void process_chunk(const chunk_t& chunk, const size_t position) {
        std::string code;

        size_t pos = 0;
        for (const auto& token: chunk) {
            if (pos >= token.size())
                break;
            code.push_back(token.at(pos));
            ++pos;
        }

        code_tree.add_code(code, position);
    }

public:
    static const size_t CHUNK_SIZE = 5;

    Decoder(const std::string& fname) : tokenizer(fname) {}

    CodeTree gen_code_tree() && {
        chunk_t chunk;
        std::string token;

        for (size_t size = 0; size < CHUNK_SIZE; ++size) {
            if (!tokenizer.get_token(token, CHUNK_SIZE))
                break;

            chunk.emplace_back(std::move(token));
        }

        size_t position = 0;
        process_chunk(chunk, position);

        while (tokenizer.get_token(token, CHUNK_SIZE)) {
            chunk.emplace_back(std::move(token));
            token = std::move(chunk.front());
            chunk.pop_front();

            ++position;
            process_chunk(chunk, position);
        }

        CodeTree retval = std::move(code_tree);
        return retval;
    }

private:
    Tokenizer tokenizer;
    CodeTree code_tree;
};
} // namespace solution
