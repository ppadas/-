#include "src/Parser.h"
#include "gtest/gtest.h"
#include <vector>

TEST(Case0, LibTest0){
    std::vector<Rule> rules;
    rules.emplace_back('0', "S");
    rules.emplace_back('S', "aS");
    Parser p(rules);
    EXPECT_EQ(false, p.CheckWord("ab"));
    EXPECT_EQ(false, p.CheckWord("aaaa"));
    EXPECT_EQ(false, p.CheckWord(""));
}

TEST(Case1, LibTest1){
    std::vector<Rule> rules;
    rules.emplace_back('0', "S");
    rules.emplace_back('S', "aS");
    rules.emplace_back('S', "");
    Parser p(rules);
    EXPECT_EQ(false, p.CheckWord("ab"));
    EXPECT_EQ(true, p.CheckWord("aaa"));
    EXPECT_EQ(true, p.CheckWord("a"));
    EXPECT_EQ(true, p.CheckWord("aa"));
    EXPECT_EQ(true, p.CheckWord("aaaa"));
    EXPECT_EQ(true, p.CheckWord("eps"));
}

TEST(Case2, LibTest2) {
    std::vector<Rule> rules;
    rules.emplace_back('0', "S");
    rules.emplace_back('S', "SS");
    rules.emplace_back('S', "aSb");
    rules.emplace_back('S', "");
    Parser p(rules);
    EXPECT_EQ(true, p.CheckWord("eps"));
    EXPECT_EQ(false, p.CheckWord("aaaa"));
    EXPECT_EQ(true, p.CheckWord("aabb"));
    EXPECT_EQ(true, p.CheckWord("ababaababb"));
    EXPECT_EQ(true, p.CheckWord("aabbaabbaabababb"));
    EXPECT_EQ(false, p.CheckWord("aabbaabbaababab"));
    EXPECT_EQ(false, p.CheckWord("bbaabbaa"));
}

TEST(Case3, LibTest3) {
    std::vector<Rule> rules;
    rules.emplace_back('0', "S");
    rules.emplace_back('S', "cT");
    rules.emplace_back('S', "bS");
    rules.emplace_back('T', "Uc");
    rules.emplace_back('T', "cTa");
    rules.emplace_back('U', "cV");
    rules.emplace_back('U', "bUb");
    rules.emplace_back('V', "cbV");
    rules.emplace_back('V', "c");
    Parser p(rules);
    EXPECT_EQ(false, p.CheckWord("eps"));
    EXPECT_EQ(true, p.CheckWord("bbbccbccbcbca"));
    EXPECT_EQ(false, p.CheckWord("ababacb"));
    EXPECT_EQ(false, p.CheckWord("ccbbccbba"));
    EXPECT_EQ(true, p.CheckWord("bcccc"));
    EXPECT_EQ(false, p.CheckWord("bbccc"));
    EXPECT_EQ(false, p.CheckWord("ccbbcbbca"));
    EXPECT_EQ(true, p.CheckWord("ccbbccbbca"));
}
