//
// Created by casubmar on 01.03.2021.
//

#ifndef FT_CONTAINER_QUEUE_HPP
#define FT_CONTAINER_QUEUE_HPP

#include "list.hpp"

namespace ft {

	template <class T, class Container = list<T> >
	class queue {
	public:
		typedef T			value_type;
		typedef	Container	container_type;
		typedef	size_t		size_type;

		explicit queue (const container_type& ctnr = container_type()) : data(ctnr) {
		}

		bool empty() const { return data.empty(); }
		size_type size() const { return data.size(); }

		value_type& front() { return data.front(); }
		const value_type& front() const { return data.front(); }
		value_type& back() { return data.back(); }
		const value_type& back() const { return data.back(); }
		void push (const value_type& val) { data.push_back(val); }
		void pop() { data.pop_front(); }

		container_type getQueue() const { return data; }

	protected:
		container_type	data;
	};

	template <class T, class Container> bool operator==(const queue<T,Container>& lhs, const queue<T,Container>& rhs);
	template <class T, class Container> bool operator!=(const queue<T,Container>& lhs, const queue<T,Container>& rhs);
	template <class T, class Container> bool operator<(const queue<T,Container>& lhs, const  queue<T,Container>& rhs);
	template <class T, class Container> bool operator<=(const queue<T,Container>& lhs, const queue<T,Container>& rhs);
	template <class T, class Container> bool operator>(const queue<T,Container>& lhs, const queue<T,Container>& rhs);
	template <class T, class Container> bool operator>=(const queue<T,Container>& lhs, const queue<T,Container>& rhs);

}


template <class T, class Container> bool ft::operator==(const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) {
	return lhs.getQueue() == rhs.getQueue();
}

template <class T, class Container> bool ft::operator!=(const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) {
	return lhs.getQueue() != rhs.getQueue();
}

template <class T, class Container> bool ft::operator<(const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) {
	return lhs.getQueue() < rhs.getQueue();
}

template <class T, class Container> bool ft::operator<=(const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) {
	return lhs.getQueue() <= rhs.getQueue();
}

template <class T, class Container> bool ft::operator> (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) {
	return lhs.getQueue() > rhs.getQueue();
}

template <class T, class Container> bool ft::operator>=(const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs) {
	return  lhs.getQueue() >= rhs.getQueue();
}

#endif //FT_CONTAINER_QUEUE_HPP
