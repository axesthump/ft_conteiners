

#include "gtest/gtest.h"
#include "../queue.hpp"
#include <queue>
#include <list>
#include <string>

class QueueFullTest : public testing::Test {
protected:
	virtual void SetUp() {
	}

};


TEST_F(QueueFullTest, constructorTest) {
	std::queue<std::string> s;
	ft::queue<std::string> f;

	EXPECT_EQ(s.empty(), f.empty());
	EXPECT_EQ(s.size(), f.size());
}

TEST_F(QueueFullTest, emptyTest) {
	std::queue<std::string> s;
	ft::queue<std::string> f;


	ASSERT_EQ(s.empty(), f.empty());
}

TEST_F(QueueFullTest, emptyTest2) {
	std::queue<std::string> s;
	ft::queue<std::string> f;

	s.push("hello");
	f.push("hello");

	ASSERT_EQ(s.empty(), f.empty());
}

TEST_F(QueueFullTest, sizeTest) {
	std::queue<std::string> s;
	ft::queue<std::string> f;

	ASSERT_EQ(s.size(), f.size());
}

TEST_F(QueueFullTest, sizeTest2) {
	std::queue<std::string> s;
	ft::queue<std::string> f;

	s.push("hello");
	f.push("hello");

	ASSERT_EQ(s.size(), f.size());
}


TEST_F(QueueFullTest, pushTest) {
	std::queue<std::string> s;
	ft::queue<std::string> f;

	for (int i = 0; i < 10; ++i) {
		s.push("hello");
		f.push("hello");
	}

	ASSERT_EQ(s.front(), f.front());
	ASSERT_EQ(s.back(), f.back());
}


TEST_F(QueueFullTest, popTest) {
	std::queue<int> s;
	ft::queue<int> f;

	for (int i = 0; i < 10; ++i) {
		s.push(i);
		f.push(i);
	}

	while (s.size()){
		ASSERT_EQ(s.front(), f.front());
		ASSERT_EQ(s.back(), f.back());
		s.pop();
		f.pop();
	}


}