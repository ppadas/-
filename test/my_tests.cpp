#include "src/autom.h"
#include "gtest/gtest.h"

TEST(Case1, LibTest1){
        Automatic a("ab+c.aba.∗.bac.+.+∗");
	EXPECT_EQ(true, a.Check("ab"));
        EXPECT_EQ(true, a.Check("$"));
        EXPECT_EQ(true, a.Check("acbcabababaacac"));
        EXPECT_EQ(false, a.Check("a"));
        EXPECT_EQ(true, a.Check("ab"));
        EXPECT_EQ(false, a.Check("acbcabababaacaa"));
}

TEST(Case1, LibTest2){
        Automatic a("ab+c∗.ab..ca.+aba+∗.c.ab+.+∗");
	EXPECT_EQ(true, a.Check("aab"));
	EXPECT_EQ(false, a.Check("cababac"));
	EXPECT_EQ(false, a.Check("c"));
	EXPECT_EQ(false, a.Check("caaaab"));
	EXPECT_EQ(true, a.Check("cacaacccababbabca"));
	EXPECT_EQ(true, a.Check("cacaacccab"));
	EXPECT_EQ(true, a.Check("aababbbbacb"));
}

TEST(Case1, LibTest3){
        Automatic a("ab+∗c∗.ab+∗.c∗.abc++∗.");
	EXPECT_EQ(true, a.Check("aab"));
	EXPECT_EQ(true, a.Check("cababac"));
	EXPECT_EQ(true, a.Check("c"));
	EXPECT_EQ(true, a.Check("caaaab"));
	EXPECT_EQ(true, a.Check("cacaacccababbabca"));
	EXPECT_EQ(true, a.Check("cacaacccab"));
	EXPECT_EQ(true, a.Check("aababbbbacb"));
	EXPECT_EQ(true, a.Check("$"));
}


TEST(Case1, LibTest4){
        Automatic a("abc..∗");
	EXPECT_EQ(false, a.Check("aab"));
	EXPECT_EQ(false, a.Check("cababac"));
	EXPECT_EQ(false, a.Check("c"));
	EXPECT_EQ(true, a.Check("abcabc"));
	EXPECT_EQ(false, a.Check("cac"));
	EXPECT_EQ(false, a.Check("cab"));
	EXPECT_EQ(false, a.Check("b"));
	EXPECT_EQ(true, a.Check("$"));
}

TEST(Case1, LibTest5){
        Automatic a("abc..");
	EXPECT_EQ(false, a.Check("aab"));
	EXPECT_EQ(false, a.Check("cababac"));
	EXPECT_EQ(false, a.Check("c"));
	EXPECT_EQ(false, a.Check("abcabc"));
	EXPECT_EQ(true, a.Check("abc"));
	EXPECT_EQ(false, a.Check("cab"));
	EXPECT_EQ(false, a.Check("b"));
	EXPECT_EQ(false, a.Check("$"));
}