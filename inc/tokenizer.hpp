#pragma once

#include <iostream>
#include <cctype>
#include <string>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

namespace solution {
class Tokenizer {
    bool get(char& symbol) {
        if (!mapped_file || pos == file_size)
            return false;

        symbol = *(mapped_file + pos);
        ++pos;

        return true;
    }
public:
    Tokenizer(const std::string& fname) {
        int fdesc = open(fname.c_str(), O_RDONLY);

        if (fdesc < 0) {
            return;
        }

        struct stat st;
        int res = fstat(fdesc, &st);

        if (res < 0 || st.st_size == 0) {
            close(fdesc);
            return;
        }

        file_size = st.st_size;
        mapped_file = (char*)mmap(0, st.st_size, PROT_READ, MAP_SHARED, fdesc, 0);

        close(fdesc);

        if (mapped_file == MAP_FAILED) {
            mapped_file = nullptr;
        }
    }

    bool get_token(std::string& token, const size_t max_len) {
        token.clear();

        char symbol = 0;
        while (get(symbol) && !std::isalpha(symbol));

        if (!std::isalpha(symbol))
            return false;

        token.push_back(symbol);

        while (get(symbol) && std::isalpha(symbol)) {
            if (token.size() < max_len) {
                token.push_back(symbol);
            }
        }

        return true;
    }

private:
    char* mapped_file = nullptr;
    size_t file_size = 0;
    size_t pos = 0;
};
} // namespace solution
