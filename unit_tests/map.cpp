
#include "gtest/gtest.h"
#include "../map.hpp"
#include <map>
#include <string>
#include <stdexcept>

#ifndef FT_CONTAINERS_DEBUG
template < class G, class U >
std::ostream & operator<<(std::ostream & o, std::pair<G, U> p) {
	o << "_" << p.first;
	return o;
}
#endif

template< class T >
void printContainer(T & l) {
	for (typename T::iterator it = l.begin(); it != l.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}

template < class T, class U>
bool operator==(std::pair<T, U> p1, std::pair<T, U> p2) {
	return (p1.first == p2.first && p1.second == p2.second);
}

template <class T, class U>
void	checkIfMapsAreEqual(ft::map<T, U> & f, std::map<T, U> & s, int i = 0) {
	ASSERT_EQ(f.size(), s.size()) << "i = " << i;
	ASSERT_EQ(f.empty(), s.empty()) << "i = " << i;

	typename  ft::map<T, U>::iterator itf = f.begin();
	typename  ft::map<T, U>::iterator itfe = f.end();
	typename std::map<T, U>::iterator its = s.begin();
	typename std::map<T, U>::iterator itse = s.end();

	for (; its != itse; ) {
		ASSERT_EQ(*its++, *itf++)  << "i = " << i;
	}
	ASSERT_EQ(itf, itfe)  << "i = " << i;
}

class MapTest : public testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i) {
			ss.insert(std::make_pair(std::to_string(i), i));
			ff.insert(std::make_pair(std::to_string(i), i));
		}
	}

	std::map<std::string, int> ss;
	ft::map<std::string, int> ff;

	std::map<std::string, int>::iterator it;
};

TEST_F(MapTest, constructorTest) {
	std::map<std::string, int> s;
	ft::map<std::string, int> f;

	ASSERT_EQ(s.size(), f.size());
	ASSERT_EQ(s.empty(), f.empty());
}

TEST_F(MapTest, constructorRangeTest) {
	ft::map<std::string, int> f(ff.begin(), ff.end());
	std::map<std::string, int> s(ss.begin(), ss.end());

	checkIfMapsAreEqual(f, s);
}

TEST_F(MapTest, constructorCopyTest) {
	ft::map<std::string, int> f(ff);
	std::map<std::string, int> s(ss);

	checkIfMapsAreEqual(f, s);
}

TEST_F(MapTest, assignTest) {
	ft::map<std::string, int> f = ff;
	std::map<std::string, int> s = ss;

	checkIfMapsAreEqual(f, s);
}


TEST_F(MapTest, emptyTest) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	checkIfMapsAreEqual(f, s);
}

TEST_F(MapTest, emptyTest2) {
	ft::map<std::string, int> f = ff;
	std::map<std::string, int> s = ss;

	checkIfMapsAreEqual(f, s);
}


TEST_F(MapTest, sizeTest) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	checkIfMapsAreEqual(f, s);
}

TEST_F(MapTest, sizeTest2) {
	ft::map<std::string, int> f = ff;
	std::map<std::string, int> s = ss;

	checkIfMapsAreEqual(f, s);
}

TEST_F(MapTest, operatorr) {
	ft::map<std::string, int> f = ff;
	std::map<std::string, int> s = ss;

	ASSERT_EQ(f["1"], s["1"]);
}


TEST_F(MapTest, insertSingleElementTest) {
	ft::map<std::string, int> f = ff;
	std::map<std::string, int> s = ss;

	f.insert(std::make_pair("10", 5));
	s.insert(std::make_pair("10", 5));
	checkIfMapsAreEqual(f, s);
}


TEST_F(MapTest, insertHintTest) {
	ft::map<std::string, int> f = ff;
	std::map<std::string, int> s = ss;

	f.insert(f.begin(), std::make_pair("10", 5));
	s.insert(s.begin(), std::make_pair("10", 5));
	checkIfMapsAreEqual(f, s);
}


TEST_F(MapTest, insertRangeTest) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());
	checkIfMapsAreEqual(f, s);
}


TEST_F(MapTest, eraseTest) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	f.erase(f.begin());
	s.erase(s.begin());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapTest, eraseTest1) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	f.erase(++f.begin());
	s.erase(++s.begin());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapTest, eraseTest3) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	f.erase(++++f.begin());
	s.erase(++++s.begin());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapTest, eraseTest4) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	f.erase("4");
	s.erase("4");
	checkIfMapsAreEqual(f, s);
}



TEST_F(MapTest, eraseTest5) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	f.erase("40");
	s.erase("40");
	checkIfMapsAreEqual(f, s);
}


TEST_F(MapTest, eraseTest6) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	f.erase(++++f.begin(), ----f.end());
	s.erase(++++s.begin(), ----s.end());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapTest, eraseTest7) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	f.erase(f.begin(), --f.end());
	s.erase(s.begin(), --s.end());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapTest, eraseTest8) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	f.erase(f.begin(), f.end());
	s.erase(s.begin(), s.end());
	checkIfMapsAreEqual(f, s);
}

TEST_F(MapTest, clearTest) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	f.clear();
	s.clear();
	checkIfMapsAreEqual(f, s);
}


TEST_F(MapTest, swapTest) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	ft::map<std::string, int> f2;
	std::map<std::string, int> s2;

	f.swap(f2);
	s.swap(s2);

	checkIfMapsAreEqual(f, s);
	checkIfMapsAreEqual(f2, s2);
}

TEST_F(MapTest, findTest) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	ASSERT_EQ(f.find("asd"), f.end());
	ASSERT_EQ(s.find("asd"), s.end());
}

TEST_F(MapTest, findTest2) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	ASSERT_NE(f.find("1"), f.end());
	ASSERT_NE(s.find("1"), s.end());
}


TEST_F(MapTest, countTest) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	ASSERT_EQ(f.count("asd"), s.count("asd"));
}

TEST_F(MapTest, countTest2) {
	ft::map<std::string, int> f;
	std::map<std::string, int> s;

	f.insert(ff.begin(), ff.end());
	s.insert(ss.begin(), ss.end());


	ASSERT_EQ(f.count("1"), s.count("1"));
}


TEST_F(MapTest, lowerUpperBTest) {
	std::map<char,int> mymap;
	std::map<char,int>::iterator itlow,itup;

	mymap.insert(std::make_pair('a', 20));
	mymap.insert(std::make_pair('b', 40));
	mymap.insert(std::make_pair('c', 60));
	mymap.insert(std::make_pair('d', 80));
	mymap.insert(std::make_pair('e', 100));

	itlow=mymap.lower_bound ('b');
	itup=mymap.upper_bound ('d');

	mymap.erase(itlow,itup);

	ft::map<char,int> mymap2;
	ft::map<char,int>::iterator itlow2,itup2;

	mymap2.insert(std::make_pair('a', 20));
	mymap2.insert(std::make_pair('b', 40));
	mymap2.insert(std::make_pair('c', 60));
	mymap2.insert(std::make_pair('d', 80));
	mymap2.insert(std::make_pair('e', 100));

	itlow2=mymap2.lower_bound ('b');
	itup2=mymap2.upper_bound ('d');

	mymap2.erase(itlow2,itup2);

	checkIfMapsAreEqual(mymap2, mymap);
}










