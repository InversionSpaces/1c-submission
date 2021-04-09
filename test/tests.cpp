#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

#include <decoder.hpp>

void SimpleTest () {
    std::cout << "Running test: " << "SimpleTest" << std::endl;
    
    std::stringstream stream;
    std::string test_data = "The size of wchar_t is implementation-defined. AFAICR, Windows is 2 byte (UCS-2 / UTF-16, depending on Windows version), Linux is 4 byte (UTF-32). In any case, since the standard doesn't define Unicode semantics for wchar_t, using it is non-portable guesswork. Don't guess, use ICU.";

    stream << test_data;

    solution::Decoder decoder(stream);
    solution::CodeTree code_tree = std::move(decoder).gen_code_tree();

    auto aan = code_tree.check_code("aan");
    assert(aan);
    assert(*aan == 23);

    auto sfh = code_tree.check_code("sfh");
    assert(sfh);
    assert(*sfh == 1);

    std::cout << "Passed" << std::endl;
}

int main () {
    SimpleTest();
}
