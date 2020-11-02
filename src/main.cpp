#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <string>

struct Position {
    bool final = false;
    std::unordered_map<char, std::vector<int>> transitions;
};

struct Part {
    Part (int start, int finish) : start(start), finish(finish) {}
    int start = 0;
    int finish = 0;
};

class Automatic {
public:
    Automatic (std::string s) {
        for (int i = 0; i < s.size(); ++i) {
            //std::cout << s[i];
            //std::cout << i << "\n " << s[i] << " " << current_state.size() << "\n";
            if (s[i] == '+') {
                if (current_state.size() < 2) {
                    std::cout << "Error\n";
                    flag = false;
                    break;
                }
                Add();
            } else if (s[i] == '.') {
                if (current_state.size() < 2) {
                    std::cout << "Error\n";
                    flag = false;
                    break;
                }
                Mult();
            }  else if (s[i] == '1') {
                Letter('$');
            } else if (s[i] == ' ') {
                continue;
            } else if (s[i] & (~char(0) << 7)) { //проблема с ∗
                if (current_state.size() < 1) {
                    std::cout << "Error\n";
                    flag = false;
                    break;
                }
                i += 2;
                Degree();
            } else {
                Letter(s[i]);
            }
        }
        if (current_state.size() != 1) {
            std::cout << "Error\n";
            flag = false;
        }
        start = current_state.top().start;
    }

    void Print () {
        std::cout << "\n---------------Print---------------:\n";
        std::cout << "Start: " << start << "\n";
        for (int i = 0; i < graph.size(); ++i) {
            std::cout << i << " " << graph[i].final << ":\n";
            for (auto j : graph[i].transitions) {
                std::cout << " " << j.first << ": ";
                for (int k = 0; k < j.second.size(); ++k) {
                    std::cout << j.second[k] << " ";
                }
                std::cout << "\n";
            }
        }
    }

    bool Check (std::string word) {
        if (!flag) {
            std::cout << "Bad structure\n";
            return false;
        }
        std::vector<std::unordered_set<int>> save_from_looping(graph.size());
        save_from_looping[start].insert(0);
        std::queue<std::pair<int, int>> dfs;
        dfs.push(std::make_pair(start, 0));
        while (!dfs.empty()) {
            auto value = dfs.front();
            //std::cout << value.first << " " << value.second << "\n";
            dfs.pop();
            if (value.second >= word.size()) {
                if (graph[value.first].final == true) {
                    return true;
                }
            }
            if (value.second < word.size()) {
                auto check_letter = graph[value.first].transitions.find(word[value.second]);
                if (check_letter != graph[value.first].transitions.end()) {
                    for (auto i : check_letter -> second) {
                        if (save_from_looping[i].find(value.second + 1) == save_from_looping[i].end()) {
                            save_from_looping[i].insert(value.second + 1);
                            dfs.push(std::make_pair(i, value.second + 1));
                        }
                    }
                }
            }
            auto check_letter = graph[value.first].transitions.find('$');
            if (check_letter != graph[value.first].transitions.end()) {
                for (auto i : check_letter -> second) {
                    if (save_from_looping[i].find(value.second) == save_from_looping[i].end()) {
                        save_from_looping[i].insert(value.second);
                        dfs.push(std::make_pair(i, value.second));
                    }
                }
            }
        }
        return false;
    }
    
private:
    std::vector<Position> graph;
    std::stack<Part> current_state;
    int start = 0;
    bool flag = true;

    void Letter(char letter) {
        graph.push_back(Position());
        graph.back().transitions.insert({letter, std::vector<int>(1, graph.size())});
        graph.push_back(Position());
        graph.back().final = true;
        current_state.push(Part(graph.size() - 2, graph.size() - 1));
        //std::cout << graph.size() << " " << current_state.size() << " " << current_state.top().start << " - " << current_state.top().finish << "\n"; 
    }
    
    void Add() {
        Part p2 = current_state.top();
        current_state.pop();
        Part p1 = current_state.top();
        current_state.pop();

        graph.push_back(Position()); //меняем стартовое
        std::vector<int> trans(2);
        trans[0] = p1.start;
        trans[1] = p2.start;
        graph.back().transitions.insert({'$', trans});

        graph.push_back(Position()); //меняем конечное
        graph.back().final = true;
        //std::cout << p1.finish << " " << p2.finish << "\n";
        graph[p1.finish].final = false;
        graph[p2.finish].final = false;
        AddTrans(p1.finish, '$', graph.size() - 1);
        AddTrans(p2.finish, '$', graph.size() - 1);
        
        current_state.push(Part(graph.size() - 2, graph.size() - 1));
    }

    void Mult() {
        Part p2 = current_state.top();
        current_state.pop();
        Part p1 = current_state.top();
        current_state.pop();

        graph[p1.finish].final = false;
        AddTrans(p1.finish, '$', p2.start);
        current_state.push(Part(p1.start, p2.finish));
    }

    void Degree() {
        Part p = current_state.top();
        current_state.pop();
        graph.push_back(Position());
        graph.back().final = true;
        graph[p.finish].final = false;
        AddTrans(p.finish, '$', graph.size() - 1);
        AddTrans(graph.size() - 1, '$', p.start);
        current_state.push(Part(graph.size() - 1, graph.size() - 1));
    }

    void AddTrans(const int from, const char letter, const int to) {
        auto ans = graph[from].transitions.find(letter);
        if (ans == graph[from].transitions.end()) {
            graph[from].transitions.insert({letter, std::vector<int>(1, to)});
        } else {
            std::vector<int> a_to = ans -> second;
            a_to.push_back(to);
            graph[from].transitions.erase(letter);
            graph[from].transitions.insert({letter, a_to});
        }
    }
};

int main () {
    std::string regular;
    std::string word;
    getline(std::cin, regular);
    std::cin >> word;
    Automatic a(regular);
    int max = -1;
    int from = 0;
    int to = 0;
    if (a.Check("$")) {
        max = 0;
    }
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
