#include <iostream>
#include <vector>
#include <string>
#include <set>

struct Rule {
public:
    Rule() {}
    Rule(char left, std::string right) : left(left), right(right) {}
    char left;
    std::string right;
};

struct Value {
public:
    Value(int rule_number, int offset, int number) : rule_number(rule_number), offset(offset), number(number) {}
    Value() {}

    int rule_number = -1;
    int offset = 0;
    int number = -1;

    bool operator == (Value& other) {
        return (rule_number == other.rule_number && offset == other.offset && number == other.number);
    }
    bool operator < (const Value& other) const {
        if (rule_number < other.rule_number) {
            return true;
        }
        if (rule_number == other.rule_number && offset < other.offset) {
            return true;
        }
        if (rule_number == other.rule_number && offset == other.offset && number < other.number) {
            return true;
        }
        return false;
    }
};

class Parser {
public:
    Parser() {}
    Parser(std::vector<Rule> rules) : rules_(rules) {}

    void ReadRules();
    bool CheckWord(std::string str);


private:

    std::vector<Rule> rules_;
    void Complete(std::vector<std::set<Value>>& D, int number);
    void Predict(std::vector<std::set<Value>>& D, int number);
    bool AddNew(std::vector<Value>& to, std::vector<Value>& from);
    void Scan(std::vector<std::set<Value>>& D, std::string str, int step);
};

void Parser::ReadRules() {
    rules_.emplace_back('0', "S");
    char left = 'a';
    std::string right;
    while(left != '1') {
        std::cin >> left;
        if (left == '1') {
            break;
        }
        std::cin >> right;
        if (right == "eps") {
            right = "";
        }
        rules_.emplace_back(left, right);
    }
}

void Print(int i, std::set<Value>& D) {
    std::cout << i << "\n";
    for (auto a : D) {
        std::cout << a.rule_number << " " << a.offset << " " << a.number << "\n";
    }
}

bool Parser::CheckWord(std::string str) {
    if (str == "eps") {
        str = "";
    }
    std::vector<std::set<Value>> D (str.size() + 1);
    D[0].emplace(0, 0, 0);
    int new_values_offset = 0;
    int old_size = D[0].size();
    for (int i = 0; i <= str.size(); ++i) {
        Scan(D, str, i);
        old_size = D[i].size();
        do {
            old_size = D[i].size();
            Complete(D, i);
            Predict(D, i);
        } while(old_size != D[i].size());
        Print(i, D[i]);
    }
    for (auto i : D.back()) {
        if (i.number == 0 && i.offset == 1 && i.rule_number == 0) {
            return true;
        }
    }
    return false;
}

void Parser::Complete(std::vector<std::set<Value>>& D, int number) {
    bool flag = false;
    for (auto value : D[number]) {
        if (value.offset == rules_[value.rule_number].right.size()) {
            for (auto i_values : D[value.number]) {
                if (i_values.offset < rules_[i_values.rule_number].right.size() &&
                    rules_[i_values.rule_number].right[i_values.offset] == rules_[value.rule_number].left) {
                    D[number].emplace(i_values.rule_number, i_values.offset + 1, i_values.number);
                }
            }
        }
    }
}

void Parser::Predict(std::vector<std::set<Value>>& D, int number) {
    bool flag = false;
    for (auto value : D[number]) {
        if (value.offset < rules_[value.rule_number].right.size() ) {
            char symbol = rules_[value.rule_number].right[value.offset];
            for (int k = 0; k < rules_.size(); ++k) {
                if (rules_[k].left == symbol) {
                    D[number].emplace(k, 0, number);
                }
            }
        }
    }
}

bool Parser::AddNew(std::vector<Value>& to, std::vector<Value>& from) {
    bool flag = false;
    for (auto i : from) {
        bool not_add_yet = true;
        for (auto j : to) {
            if (j == i) {
                not_add_yet = false;
                break;
            }
        }
        if (not_add_yet) {
            to.push_back(i);
            flag = true;
        }
    }
    return flag;
}

void Parser::Scan(std::vector<std::set<Value>>& D, std::string str, int step) {
    if (step == 0) {
        return;
    }
    for (auto i : D[step - 1]) {
        if (i.offset < rules_[i.rule_number].right.size() && 
            rules_[i.rule_number].right[i.offset] == str[step - 1]) {
                D[step].emplace(i.rule_number, i.offset + 1, i.number);
        }
    }
}