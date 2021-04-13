#include "gtest/gtest.h"
#include "../vector.hpp"
#include <vector>
#include <string>
#include <stdexcept>

template <class T>
void	checkIfVectorsAreEqual(ft::vector<T> & f, std::vector<T> & s) {

	EXPECT_EQ(f.size(), s.size());
	EXPECT_EQ(f.empty(), s.empty());
	EXPECT_GE(f.capacity(), f.size());
	EXPECT_GE(s.capacity(), s.size());

	typename  ft::vector<T>::iterator itF = f.begin();
	typename  ft::vector<T>::iterator itFe = f.end();
	typename std::vector<T>::iterator itS = s.begin();
	typename std::vector<T>::iterator itSe = s.end();

	for (; itS != itSe; ) {
		EXPECT_EQ(*itS++, *itF++);
	}
	EXPECT_EQ(itF, itFe);
}

class VectorTest : public ::testing::Test {
protected:
	virtual void SetUp() { }
};

TEST_F(VectorTest, defaultConstructor) {
	ft::vector<int> f;
	std::vector<int> s;
	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, fillConstructor) {
	ft::vector<int> f(5);
	std::vector<int> s(5);
	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, fillConstructor2) {
	ft::vector<int> f(5, 2);
	std::vector<int> s(5, 2);
	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, rangeConstructor) {
	ft::vector<int> f(5, 2);
	std::vector<int> s(5, 2);

	ft::vector<int> ff(f.begin(), f.end());
	std::vector<int> ss(s.begin(), s.end());
	checkIfVectorsAreEqual(ff, ss);
}

TEST_F(VectorTest, copyConstructor) {
	ft::vector<int> f(5, 2);
	std::vector<int> s(5, 2);

	ft::vector<int> ff(f);
	std::vector<int> ss(s);
	checkIfVectorsAreEqual(ff, ss);
}

TEST_F(VectorTest, assignTest) {
	ft::vector<int> f(5, 2);
	std::vector<int> s(5, 2);

	ft::vector<int> ff = f;
	std::vector<int> ss = s;
	checkIfVectorsAreEqual(ff, ss);
}


TEST_F(VectorTest, sizeEmptyTest) {
	ft::vector<int> f;
	std::vector<int> s;
	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, sizeNotEmptyTest) {
	ft::vector<int> f(5);
	std::vector<int> s(5);
	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, maxSizeTest) {
	ft::vector<int> f(5);
	std::vector<int> s(5);
	ASSERT_EQ(f.max_size(), s.max_size());
}


TEST_F(VectorTest, resizeLowestTest) {
	ft::vector<int> f(10, 5);
	std::vector<int> s(10, 5);

	f.resize(5);
	s.resize(5);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, resizeLowestTest2) {
	ft::vector<int> f(10, 5);
	std::vector<int> s(10, 5);

	f.resize(5, 1);
	s.resize(5, 1);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, resizeHighTest) {
	ft::vector<int> f(10, 5);
	std::vector<int> s(10, 5);

	f.resize(50);
	s.resize(50);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, resizeHighTest2) {
	ft::vector<int> f(10, 5);
	std::vector<int> s(10, 5);

	f.resize(50, 1);
	s.resize(50, 1);

	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, capacityEmptyTest) {
	ft::vector<int> f;
	std::vector<int> s;
	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, capacityNotEmptyTest) {
	ft::vector<int> f(5);
	std::vector<int> s(5);
	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, emptyTest) {
	ft::vector<int> f;
	std::vector<int> s;
	ASSERT_EQ(f.empty(), s.empty());
}


TEST_F(VectorTest, notEmptyTest) {
	ft::vector<int> f(5);
	std::vector<int> s(5);
	ASSERT_EQ(f.empty(), s.empty());
}


TEST_F(VectorTest, reserveLowestTest) {
	ft::vector<int> f(10);
	std::vector<int> s(10);

	f.reserve(5);
	s.reserve(5);
	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, reserveHighTest) {
	ft::vector<int> f(5);
	std::vector<int> s(5);
	f.reserve(50);
	s.reserve(50);
	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, operatorrTest) {
	ft::vector<int> f(5);
	std::vector<int> s(5);
	ASSERT_EQ(f[3], s[3]);
}


TEST_F(VectorTest, atTest) {
	ft::vector<int> f(5);
	std::vector<int> s(5);
	ASSERT_EQ(f.at(3), s.at(3));
}

TEST_F(VectorTest, frontTest) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	ASSERT_EQ(f.front(), s.front());
}


TEST_F(VectorTest, backTest) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	ASSERT_EQ(f.back(), s.back());
}


TEST_F(VectorTest, assignRangeTest) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	ft::vector<int> ff;
	std::vector<int> ss;

	ff.assign(f.begin(), f.end());
	ss.assign(s.begin(), s.end());

	checkIfVectorsAreEqual(ff, ss);
}


TEST_F(VectorTest, assignFillTest) {
	ft::vector<int> f;
	std::vector<int> s;

	f.assign(5, 10);
	s.assign(5, 10);

	checkIfVectorsAreEqual(f, s);
}



TEST_F(VectorTest, pushBackTest) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, popBackTest) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	for (int i = 0; i < 5; ++i) {
		f.pop_back();
		s.pop_back();
	}

	checkIfVectorsAreEqual(f, s);
}



TEST_F(VectorTest, insertSingleElementBeginTest) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.insert(f.begin(), 5);
	s.insert(s.begin(), 5);

	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, insertSingleElementEndTest) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.insert(f.end(), 5);
	s.insert(s.end(), 5);

	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, insertSingleElementMiddleTest) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.insert(----f.end(), 5);
	s.insert(----s.end(), 5);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, insertFillBeginTest) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.insert(f.begin(), 5, 5);
	s.insert(s.begin(), 5, 5);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, insertFillEndTest) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.insert(f.end(), 5, 5);
	s.insert(s.end(), 5, 5);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, insertFillMiddleTest) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.insert(----f.end(), 5, 5);
	s.insert(----s.end(), 5, 5);

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, insertRangeBeginTest) {
	ft::vector<int> f;
	std::vector<int> s;
	ft::vector<int> ff;
	std::vector<int> ss;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		ff.push_back(i);
		ss.push_back(i);
	}

	f.insert(f.begin(), ff.begin(), ff.end());
	s.insert(s.begin(), ss.begin(), ss.end());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, insertRangeEndTest) {
	ft::vector<int> f;
	std::vector<int> s;
	ft::vector<int> ff;
	std::vector<int> ss;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		ff.push_back(i);
		ss.push_back(i);
	}

	f.insert(f.end(), ff.begin(), ff.end());
	s.insert(s.end(), ss.begin(), ss.end());

	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, insertMiddleTest) {
	ft::vector<int> f;
	std::vector<int> s;
	ft::vector<int> ff;
	std::vector<int> ss;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		ff.push_back(i);
		ss.push_back(i);
	}

	f.insert(----f.end(), ff.begin(), ff.end());
	s.insert(----s.end(), ss.begin(), ss.end());

	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, eraseOneElementBegin) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.erase(f.begin());
	s.erase(s.begin());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, eraseOneElementEnd) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.erase(--f.end());
	s.erase(--s.end());

	checkIfVectorsAreEqual(f, s);
}

TEST_F(VectorTest, eraseOneElementMiddle) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.erase(------f.end());
	s.erase(------s.end());

	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, eraseRange) {
	ft::vector<int> f;
	std::vector<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.erase(++f.begin(), ++++f.begin());
	s.erase(++s.begin(), ++++s.begin());

	checkIfVectorsAreEqual(f, s);
}


TEST_F(VectorTest, swapTest) {
	ft::vector<int> f;
	std::vector<int> s;
	ft::vector<int> ff;
	std::vector<int> ss;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	for (int i = 10; i > 0; --i) {
		ff.push_back(i);
		ss.push_back(i);
	}

	f.swap(ff);
	s.swap(ss);

	checkIfVectorsAreEqual(f, s);
	checkIfVectorsAreEqual(ff, ss);
}


TEST_F(VectorTest, clearTest) {
	ft::vector<int> f;
	std::vector<int> s;
	ft::vector<int> ff;
	std::vector<int> ss;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	for (int i = 10; i > 0; --i) {
		ff.push_back(i);
		ss.push_back(i);
	}

	f.swap(ff);
	s.swap(ss);

	f.clear();
	s.clear();
	checkIfVectorsAreEqual(f, s);
	checkIfVectorsAreEqual(ff, ss);
}