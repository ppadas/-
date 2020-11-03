#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <string>
#include "autom.h"

int main () {
    std::string regular;
    std::string word;
    getline(std::cin, regular);
    std::cin >> word;
    Automatic a(regular);
    int max = -1;
    int from = -1;
    int to = -1;
    if (a.Check("$")) {
        max = 0;
    }
    a.Print();
    for (int i = 0; i < word.size(); ++i) {
        for (int j = 1; j < word.size() - i + 1; ++j) {
            if(a.Check(word.substr(i, j))) {
                //max = std::max(max, j);
                if (max < j) {
                    max = j;
                    from = i;
                    to = i + j - 1;
                }
            }
        }
    }
    std::cout << max << " " << from << " " << to << "\n";
}

//ab+c.aba.∗.bac.+.+∗
