#include <iostream>
#include <vector>
#include <string>

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
};

class Parser {
public:
    Parser() {}
    Parser(std::vector<Rule> rules) : rules_(rules) {}

    void ReadRules();
    bool CheckWord(std::string str);


private:

    std::vector<Rule> rules_;
    bool Complete(std::vector<std::vector<Value>>& D, int number);
    bool Predict(std::vector<std::vector<Value>>& D, int number);
    bool AddNew(std::vector<Value>& to, std::vector<Value>& from);
    void Scan(std::vector<std::vector<Value>>& D, std::string str, int step);
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
    /*for (auto i : rules_) {
        std::cout << i.left << " -> " << i.right << "\n";
    }*/
}

void Print(int i, std::vector<Value>& D) {
    std::cout << i << "\n";
    for (auto a : D) {
        std::cout << a.rule_number << " " << a.offset << " " << a.number << "\n";
    }
}

bool Parser::CheckWord(std::string str) {
    if (str == "eps") {
        str = "";
    }
    std::vector<std::vector<Value>> D (str.size() + 1);
    D[0].emplace_back(0, 0, 0);
    for (int i = 0; i <= str.size(); ++i) {
        Scan(D, str, i);
        while(Complete(D, i) || Predict(D, i)) {}
        //Print(i, D[i]);
    }
    for (auto i : D.back()) {
        if (i.number == 0 && i.offset == 1 && i.rule_number == 0) {
            return true;
        }
    }
    return false;
}

bool Parser::Complete(std::vector<std::vector<Value>>& D, int number) {
    bool flag = false;
    std::vector<Value> should_add;
    for (auto value : D[number]) {
        if (value.offset == rules_[value.rule_number].right.size()) {
            for (auto i_values : D[value.number]) {
                if (i_values.offset < rules_[i_values.rule_number].right.size() &&
                    rules_[i_values.rule_number].right[i_values.offset] == rules_[value.rule_number].left) {
                    should_add.emplace_back(i_values.rule_number, i_values.offset + 1, i_values.number);
                }
            }
        }
    }
    return AddNew(D[number], should_add); 
}

bool Parser::Predict(std::vector<std::vector<Value>>& D, int number) {
    bool flag = false;
    std::vector<Value> should_add;
    for (auto value : D[number]) {
        if (value.offset < rules_[value.rule_number].right.size() ) {
            char symbol = rules_[value.rule_number].right[value.offset];
            for (int k = 0; k < rules_.size(); ++k) {
                if (rules_[k].left == symbol) {
                    should_add.emplace_back(k, 0, number);
                }
            }
        }
    }
    return AddNew(D[number], should_add);
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

void Parser::Scan(std::vector<std::vector<Value>>& D, std::string str, int step) {
    if (step == 0) {
        return;
    }
    for (auto i : D[step - 1]) {
        if (i.offset < rules_[i.rule_number].right.size() && 
            rules_[i.rule_number].right[i.offset] == str[step - 1]) {
                D[step].emplace_back(i.rule_number, i.offset + 1, i.number);
        }
    }
}