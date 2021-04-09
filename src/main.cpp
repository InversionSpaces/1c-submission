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

    Decoder decoder(argv[1]);
    CodeTree code_tree = std::move(decoder).gen_code_tree();

    return 0;

    for (;;) {
        std::string code;
        std::cout << "Specify Code (Ctrl-D to exit) > ";
        if (!(std::cin >> code)) {
            std::cout << std::endl;
            break;
        }

        auto result = code_tree.check_code(code);
        if (!result) {
            std::cout << "Code Not Found" << std::endl;
        }
        else {
            std::cout << "Found code at position: " << *result + 1 << std::endl;
        }
    }
}
