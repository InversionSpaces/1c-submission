#include <iostream>
#include <fstream>
#include <string>

#include <decoder.hpp>

using namespace solution;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Secret decoder" << std::endl;
        std::cout << "Usage: " << argv[0] << " TEXT_FILE.txt" << std::endl;

        return 0;
    }

    std::string filename(argv[1]);
    std::ifstream file(filename);

    Decoder decoder(file);
    auto codes = std::move(decoder).gen_codes();

    return 0;
    for (;;) {
        std::string code;
        std::cout << "Specify Code (Ctrl-D to exit) > ";
        if (!(std::cin >> code)) {
            std::cout << std::endl;
            break;
        }

        auto result = codes.count(code);
        if (!result) {
            std::cout << "Code Not Found" << std::endl;
        }
        else {
            std::cout << "Found code at position: " << codes.at(code) + 1 << std::endl;
        }
    }
}
