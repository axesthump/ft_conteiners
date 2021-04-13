#include "gtest/gtest.h"
#include "../list.hpp"
#include <list>
#include <sstream>
#include <cmath>

template< class T >
void print_list(T & list) {
	for (typename T::iterator it = list.begin(); it != list.end(); ++it) {
		std::cout << *it << ' ';
	}
	std::cout << std::endl;
}

class ListTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		for (int i = 0; i < 10; ++i)
			ftList.push_front(i);
		for (int i = 0; i < 10; ++i)
			stdList.push_front(i);
	}

	ft::list<int> ftList;
	std::list<int> stdList;
	ft::list<int>::iterator startFt = ftList.begin();
	ft::list<int>::iterator endFt = ftList.end();
	std::list<int>::iterator startStd = stdList.begin();
	std::list<int>::iterator endStd = stdList.end();
};

template <typename itFt, typename itFtEnd, typename itStd, typename itStdEnd>
void checkListEqual(itFt itF, itFtEnd itFe, itStd itS, itStdEnd itSe, size_t size = 10) {
	for (size_t i = 0; i < size; ++i)
	{
		--itF; --itS;
		if (itS == itSe) {
			ASSERT_EQ(itF, itFe);
			continue;
		}
		EXPECT_EQ(*itF, *itS);
	}
	for (size_t i = 0; i < size; ++i)
	{
		++itF; ++itS;
		if (itS == itSe) {
			ASSERT_EQ(itF, itFe);
			continue;
		}
		EXPECT_EQ(*itF, *itS);
	}
};
//
//template <typename ftIter, typename stdIter>
//void	listIteratorTest(ftIter & fIt, ftIter & fIte, ftIter & ftmpIt,
//						 stdIter & sIt, stdIter & sIte, stdIter & stmpIt)
//{
//	EXPECT_EQ(*fIt, *sIt);
//	++fIt;
//	++sIt;
//	EXPECT_EQ(*fIt, *sIt);
//	ftmpIt = fIt++;
//	stmpIt = sIt++;
//	EXPECT_EQ(*fIt, *sIt);
//	EXPECT_EQ(*stmpIt, *ftmpIt);
//
//	checkListEqual(fIt, fIte, sIt, sIte);
//}

TEST_F(ListTest, emptyList) {
	ft::list<int> f;
	std::list<int> s;

	ASSERT_EQ(f.size(), s.size());
}

TEST_F(ListTest, notEmptyList) {
	checkListEqual(startFt, endFt, startStd, endStd, 10);
}


TEST_F(ListTest, fillConstructor) {
	ft::list<int> f(5);
	std::list<int> s(5);

	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < 5; ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}


TEST_F(ListTest, fillConstructorSize) {
	ft::list<int> f(5);
	std::list<int> s(5);

	ASSERT_EQ(f.size(), s.size());
}

TEST_F(ListTest, rangeConstructorSize) {
	ft::list<int> ft(5);
	ft::list<int> f(ft.begin(), ft.end());

	ft::list<int>::iterator iF = f.begin();
	ft::list<int>::iterator iS = ft.begin();

	for (int i = 0; i < 5; ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}


TEST_F(ListTest, copyConstructorSize) {
	ft::list<int> ft(5);
	ft::list<int> f(ft);

	ft::list<int>::iterator iF = f.begin();
	ft::list<int>::iterator iS = ft.begin();

	for (int i = 0; i < 5; ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}

TEST_F(ListTest, assignTest) {
	ft::list<int> ft(5);
	ft::list<int> f = ft;

	ft::list<int>::iterator iF = f.begin();
	ft::list<int>::iterator iS = ft.begin();

	for (int i = 0; i < 5; ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}

TEST_F(ListTest, rbeginTest) {
	ft::list<int> f(5);
	std::list<int> s(5);


	ft::list<int>::reverse_iterator iF = f.rbegin();
	std::list<int>::reverse_iterator iS = s.rbegin();
	ft::list<int>::reverse_iterator iFe = f.rend();
	for (; iF != iFe; ++iF) {
		ASSERT_EQ(*iF, *iS);
		++iS;
	}

}


TEST_F(ListTest, emptyTrueTest) {
	ft::list<int> ff;
	std::list<int> ss;
	ASSERT_EQ(ff.empty(), ss.empty());

}


TEST_F(ListTest, emptyFalseTest) {
	ft::list<int> f(5);
	std::list<int> s(5);
	ASSERT_EQ(f.empty(), s.empty());

}


TEST_F(ListTest, sizeNotEmptyTest) {
	ft::list<int> f(5);
	std::list<int> s(5);
	ASSERT_EQ(f.size(), s.size());

}


TEST_F(ListTest, sizeEmptyTest) {
	ft::list<int> f;
	std::list<int> s;
	ASSERT_EQ(f.size(), s.size());

}


TEST_F(ListTest, maxSizeTest) {
	ft::list<int> f;
	std::list<int> s;
	ASSERT_EQ(f.max_size(), s.max_size());
}

TEST_F(ListTest, frontNotEmptyTest) {
	ASSERT_EQ(ftList.front(), stdList.front());
}


TEST_F(ListTest, frontEmptyTest) {
	ft::list<int> f;
	std::list<int> s;
	ASSERT_EQ(f.front(), s.front());
}


TEST_F(ListTest, backNotEmptyTest) {
	ASSERT_EQ(ftList.back(), stdList.back());
}


TEST_F(ListTest, backEmptyTest) {
	ft::list<int> f;
	std::list<int> s;
	ASSERT_EQ(f.back(), s.back());
}



TEST_F(ListTest, assignFillTest) {
	ft::list<int> f;
	std::list<int> s;

	f.assign(7, 100);
	s.assign(7, 100);


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}


TEST_F(ListTest, assignRangeTest) {
	ft::list<int> f;
	ft::list<int> s;

	f.assign(7, 100);
	s.assign(f.begin(), f.end());


	ft::list<int>::iterator iF = f.begin();
	ft::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}



TEST_F(ListTest, pushFrontTest) {
	ft::list<int> f;
	std::list<int> s;
	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	for (int i = 0; i < 20; ++i) {
		ASSERT_EQ(f.front(), s.front());
		f.push_front(i);
		s.push_front(i);
	}
}


TEST_F(ListTest, popFrontTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	for (int i = 0; i < 7; ++i) {
		ASSERT_EQ(f.front(), s.front());
		f.pop_front();
		s.pop_front();
	}
}



TEST_F(ListTest, pushBackTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	for (int i = 0; i < 20; ++i) {
		ASSERT_EQ(f.back(), s.back());
		f.push_back(i);
		s.push_back(i);
	}
}


TEST_F(ListTest, popBackTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	for (int i = 0; i < 7; ++i) {
		ASSERT_EQ(f.back(), s.back());
		f.pop_back();
		s.pop_back();
	}
}


TEST_F(ListTest, insertSingleElementBeginTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	f.insert(f.begin(), 10);
	s.insert(s.begin(), 10);
	ASSERT_EQ(f.front(), s.front());
}

TEST_F(ListTest, insertSingleElementEndTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	f.insert(f.end(), 10);
	s.insert(s.end(), 10);
	ASSERT_EQ(f.back(), s.back());
}

TEST_F(ListTest, insertSingleElementMiddleTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	f.insert(++f.begin(), 10);
	s.insert(++s.begin(), 10);
	ASSERT_EQ(*(++f.begin()), *(++s.begin()));
}


TEST_F(ListTest, insertFillBeginTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	f.insert(f.begin(), 10, 10);
	s.insert(s.begin(), 10, 10);

	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}

TEST_F(ListTest, insertFillEndTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	f.insert(f.end(), 10, 10);
	s.insert(s.end(), 10, 10);

	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}

TEST_F(ListTest, insertFillTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	f.insert(++f.begin(), 10, 10);
	s.insert(++s.begin(), 10, 10);
	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}



TEST_F(ListTest, insertRangeBeginTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	ft::list<int> fTemp(10);
	std::list<int> sTemp(10);


	f.insert(f.begin(),fTemp.begin(), fTemp.end());
	s.insert(s.begin(),sTemp.begin(), sTemp.end());

	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}

TEST_F(ListTest, insertRangeEndTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	ft::list<int> fTemp(10);
	std::list<int> sTemp(10);


	f.insert(f.end(),fTemp.begin(), fTemp.end());
	s.insert(s.end(),sTemp.begin(), sTemp.end());

	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}

TEST_F(ListTest, insertRangeTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	ft::list<int> fTemp(10);
	std::list<int> sTemp(10);


	f.insert(++f.begin(),fTemp.begin(), fTemp.end());
	s.insert(++s.begin(),sTemp.begin(), sTemp.end());

	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}





TEST_F(ListTest, eraseSingleBeginTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.erase(f.begin());
	s.erase(s.begin());
	ASSERT_EQ(f.front(), s.front());
}




TEST_F(ListTest, eraseSingleEndTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.erase(--f.end());
	s.erase(--s.end());
	ASSERT_EQ(f.back(), s.back());
}

TEST_F(ListTest, eraseSingleMidTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.erase(----f.end());
	s.erase(----s.end());
	ASSERT_EQ(*(----f.end()), *(----s.end()));
}





TEST_F(ListTest, eraseRangeBeginTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.erase(f.begin(), ++++f.begin());
	s.erase(s.begin(), ++++s.begin());
	ASSERT_EQ(f.front(), s.front());
}



TEST_F(ListTest, eraseRangeEndTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.erase(----f.end(), f.end());
	s.erase(----s.end(), s.end());
	ASSERT_EQ(f.back(), s.back());
}



TEST_F(ListTest, eraseRangeMidTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}

	f.erase(++f.begin(), ----f.end());
	s.erase(++s.begin(), ----s.end());
	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}



TEST_F(ListTest, swapTest) {
	ft::list<int> f;
	ft::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
	}

	for (int i = 9; i >= 0; --i) {
		s.push_back(i);
	}

	f.swap(s);
	ASSERT_EQ(f.front(), 9);
	ASSERT_EQ(s.front(), 0);
}



TEST_F(ListTest, resizeTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	s.resize(100, 6);
	f.resize(100, 6);

	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}

TEST_F(ListTest, clearTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	s.clear();
	f.clear();

	ASSERT_EQ(f.size(), s.size());
}


TEST_F(ListTest, spliceListBeginTest) {
	ft::list<int> f;
	ft::list<int> ft;
	std::list<int> s;
	std::list<int> st;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		ft.push_back(i);
		st.push_back(i);
	}

	f.splice(f.begin(), ft);
	s.splice(s.begin(), st);


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}


TEST_F(ListTest, spliceListEndTest) {
	ft::list<int> f;
	ft::list<int> ft;
	std::list<int> s;
	std::list<int> st;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		ft.push_back(i);
		st.push_back(i);
	}

	f.splice(f.end(), ft);
	s.splice(s.end(), st);


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}

TEST_F(ListTest, spliceListMiddleTest) {
	ft::list<int> f;
	ft::list<int> ft;
	std::list<int> s;
	std::list<int> st;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		ft.push_back(i);
		st.push_back(i);
	}

	f.splice(----f.end(), ft);
	s.splice(----s.end(), st);


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}


TEST_F(ListTest, spliceSingleBeginTest) {
	ft::list<int> f;
	ft::list<int> ft;
	std::list<int> s;
	std::list<int> st;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		ft.push_back(i);
		st.push_back(i);
	}

	f.splice(f.begin(), ft, ft.begin());
	s.splice(s.begin(), st, st.begin());


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}


TEST_F(ListTest, spliceSingleEndTest) {
	ft::list<int> f;
	ft::list<int> ft;
	std::list<int> s;
	std::list<int> st;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		ft.push_back(i);
		st.push_back(i);
	}

	f.splice(f.end(), ft, ft.begin());
	s.splice(s.end(), st, st.begin());


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}

TEST_F(ListTest, spliceSingleMiddleTest) {
	ft::list<int> f;
	ft::list<int> ft;
	std::list<int> s;
	std::list<int> st;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		ft.push_back(i);
		st.push_back(i);
	}

	f.splice(----f.end(), ft, ft.begin());
	s.splice(----s.end(), st, st.begin());


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}


TEST_F(ListTest, spliceRangeBeginTest) {
	ft::list<int> f;
	ft::list<int> ft;
	std::list<int> s;
	std::list<int> st;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		ft.push_back(i);
		st.push_back(i);
	}

	f.splice(f.begin(), ft, ft.begin(), ++++ft.begin());
	s.splice(s.begin(), st, st.begin(), ++++st.begin());


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}


TEST_F(ListTest, spliceRangeEndTest) {
	ft::list<int> f;
	ft::list<int> ft;
	std::list<int> s;
	std::list<int> st;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		ft.push_back(i);
		st.push_back(i);
	}

	f.splice(f.end(), ft, ft.begin(), ++++ft.begin());
	s.splice(s.end(), st, st.begin(), ++++st.begin());


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}


TEST_F(ListTest, spliceRangeMidTest) {
	ft::list<int> f;
	ft::list<int> ft;
	std::list<int> s;
	std::list<int> st;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		ft.push_back(i);
		st.push_back(i);
	}

	f.splice(----f.end(), ft, ft.begin(), ++++ft.begin());
	s.splice(----s.end(), st, st.begin(), ++++st.begin());


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}


TEST_F(ListTest, removeValidTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	f.remove(5);
	s.remove(5);


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}

TEST_F(ListTest, removeInvalidTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	f.remove(50);
	s.remove(50);


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}

bool isOdd(int num) { return num % 2; }

TEST_F(ListTest, removeIfTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
	}


	f.remove_if(isOdd);
	s.remove_if(isOdd);


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}

TEST_F(ListTest, uniqueTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		f.push_back(i);
		s.push_back(i);
		f.push_back(i);
		s.push_back(i);
	}


	f.unique();
	s.unique();


	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}


bool mycomparison (double first, double second)
{ return ( int(first)<int(second) ); }

TEST_F(ListTest, mergeTest) {
	std::list<double> first, second;

	first.push_back (3.1);
	first.push_back (2.2);
	first.push_back (2.9);

	second.push_back (3.7);
	second.push_back (7.1);
	second.push_back (1.4);

	first.sort();
	second.sort();
	first.merge(second);


	ft::list<double> firstft, secondft;

	firstft.push_back (3.1);
	firstft.push_back (2.2);
	firstft.push_back (2.9);

	secondft.push_back (3.7);
	secondft.push_back (7.1);
	secondft.push_back (1.4);

	firstft.sort();
	secondft.sort();
	firstft.merge(secondft);


	ft::list<double>::iterator iF = firstft.begin();
	std::list<double>::iterator iS = first.begin();

	for (int i = 0; i < firstft.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}



TEST_F(ListTest, sortTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 10; i > 0; --i) {
		f.push_back(i);
		s.push_back(i);
		f.push_back(i);
		s.push_back(i);
		f.push_back(i);
		s.push_back(i);
	}

	f.sort();
	s.sort();

	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}


TEST_F(ListTest, reverseTest) {
	ft::list<int> f;
	std::list<int> s;

	for (int i = 0; i < 10; ++i) {
		f.push_back(i);
		s.push_back(i);
		f.push_back(i);
		s.push_back(i);
		f.push_back(i);
		s.push_back(i);
	}

	f.reverse();
	s.reverse();

	ft::list<int>::iterator iF = f.begin();
	std::list<int>::iterator iS = s.begin();

	for (int i = 0; i < f.size(); ++i) {
		ASSERT_EQ(*iF, *iS);
		++iF;
		++iS;
	}
}