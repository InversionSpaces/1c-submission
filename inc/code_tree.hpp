#pragma once

#include <memory>
#include <string>
#include <unordered_map>

namespace solution {
class CodeTree {
    template<typename T>
    using ptr = std::shared_ptr<T>;

public:
    struct CodeNode {
        const size_t position;
        std::unordered_map<char, ptr<CodeNode>> nexts;

        CodeNode(const size_t position = 0) : position(position) {}
    };

    CodeTree() : root(std::make_shared<CodeNode>()) {}

    /*
     * Добавление ключа code на позици position
     */
    void add_code(const std::string& code, const size_t position) {
        ptr<CodeNode> current = root;

        // Спуск и обновление бора
        for (const auto& symbol: code) {
            auto lowered = std::tolower(symbol);
            if (!current->nexts.count(lowered)) {
                auto inserted = std::make_shared<CodeNode>(position);
                current->nexts[lowered] = inserted;
            }
            current = current->nexts.at(lowered);
        }
    }

    /*
     * Проверка существования ключа
     * std::nullopt в случае отсутсвия ключа, его позиция иначе
     */
    std::optional<size_t> check_code(const std::string& code) const {
        ptr<CodeNode> current = root;

        for (const auto& symbol: code) {
            auto lowered = std::tolower(symbol);
            if (!current->nexts.count(lowered)) {
                return std::nullopt;
            }
            current = current->nexts.at(lowered);
        }

        return current->position;
    }

private:
    ptr<CodeNode> root;
};
} // namespace solution
