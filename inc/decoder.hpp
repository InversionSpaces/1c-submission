#pragma once

#include <iostream>
#include <list>
#include <cctype>
#include <unordered_map>
#include <memory>
#include <optional>

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

class CodeTree {
    template<typename T>
    using ptr = std::shared_ptr<T>;
public:
    struct CodeNode {
        const size_t position;
        std::unordered_map<char, ptr<CodeNode>> nexts;

        CodeNode(const size_t position=0) : position(position) {}
    };

    CodeTree() : root(std::make_shared<CodeNode>()) {}

    void add_code(const std::string& code, const size_t position) {
        ptr<CodeNode> current = root;

        for (const auto& symbol: code) {
            if (!current->nexts.count(symbol))
                current->nexts[symbol] = std::make_shared<CodeNode>(position);
            current = current->nexts.at(symbol);
        }
    }

    std::optional<size_t> check_code(const std::string& code) const {
        ptr<CodeNode> current = root;

        for (const auto& symbol: code) {
            if (!current->nexts.count(symbol))
                return std::nullopt;
            current = current->nexts.at(symbol);
        }

        return current->position;
    }

private:
    ptr<CodeNode> root;
};

class Decoder {
    using chunk_t = std::list<std::string>;

    Tokenizer tokenizer;
    CodeTree code_tree;

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

    Decoder(std::istream& stream) : tokenizer(stream) {}

    CodeTree gen_code_tree() && {
        chunk_t chunk;
        std::string token;

        for (size_t size = 0; size < CHUNK_SIZE; ++size) {
            if (!tokenizer.get_token(token))
                break;

            chunk.emplace_back(std::move(token));
        }

        size_t position = 0;
        process_chunk(chunk, position);

        while (tokenizer.get_token(token)) {
            chunk.emplace_back(std::move(token));
            chunk.pop_front();

            ++position;
            process_chunk(chunk, position);
        }

        CodeTree retval = std::move(code_tree);
        return retval;
    }
};
