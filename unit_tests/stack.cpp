
#include "gtest/gtest.h"
#include "../stack.hpp"
#include <stack>
#include <string>

class StackFullTest : public testing::Test {
protected:
	virtual void SetUp() {
	}

};


TEST_F(StackFullTest, constructorTest) {
	std::stack<std::string> s;
	ft::stack<std::string> f;

	ASSERT_EQ(s.empty(), f.empty());
	ASSERT_EQ(s.size(), f.size());
}

TEST_F(StackFullTest, emptyTest) {
	std::stack<std::string> s;
	ft::stack<std::string> f;

	ASSERT_EQ(s.empty(), f.empty());
}

TEST_F(StackFullTest, emptyTest2) {
	std::stack<std::string> s;
	ft::stack<std::string> f;
	s.push("hello");
	f.push("hello");

	ASSERT_EQ(s.empty(), f.empty());
}

TEST_F(StackFullTest, sizeTest) {
	std::stack<std::string> s;
	ft::stack<std::string> f;

	ASSERT_EQ(s.size(), f.size());
}

TEST_F(StackFullTest, sizeTest2) {
	std::stack<std::string> s;
	ft::stack<std::string> f;
	s.push("hello");
	f.push("hello");

	ASSERT_EQ(s.size(), f.size());
}


TEST_F(StackFullTest, pushTest) {
	std::stack<std::string> s;
	ft::stack<std::string> f;
	for (int i = 0; i < 10; ++i) {
		s.push("hello");
		f.push("hello");
	}

	ASSERT_EQ(s.top(), f.top());
}


TEST_F(StackFullTest, popTest) {
	std::stack<int> s;
	ft::stack<int> f;
	for (int i = 0; i < 10; ++i) {
		s.push(i);
		f.push(i);
	}

	while (s.size()){
		ASSERT_EQ(s.top(), f.top());
		s.pop();
		f.pop();
	}


}