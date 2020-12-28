#include "Parser.h"
#include <string>

int main() {
    Parser p;
    p.ReadRules();
    std::string str;
    std::cin >> str;
    std::cout << p.CheckWord(str) << "\n";
}