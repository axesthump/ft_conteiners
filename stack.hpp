//
// Created by casubmar on 01.03.2021.
//

#ifndef FT_CONTAINER_STACK_HPP
#define FT_CONTAINER_STACK_HPP

# include "vector.hpp"

namespace ft {

	template <class T, class Container = vector<T> >
	class stack {
	public:
		typedef T			value_type;
		typedef	Container	container_type;
		typedef	size_t		size_type;

		explicit stack (const container_type& ctnr = container_type()) : data(ctnr) {
		}
		bool empty() const { return data.empty(); }
		size_type size() const { return data.size(); }
		value_type& top() { return data.back(); }
		const value_type& top() const { return data.back(); }
		void push (const value_type& val) { data.push_back(val); }
		void pop() { data.pop_back(); }

		container_type getStack() const { return data; }

	protected:
		container_type	data;
	};

	template <class T, class Container> bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.getStack() == rhs.getStack();
	}
	template <class T, class Container> bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.getStack() != rhs.getStack();
	}
	template <class T, class Container> bool operator< (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.getStack() < rhs.getStack();
	}
	template <class T, class Container> bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.getStack() <= rhs.getStack();
	}
	template <class T, class Container> bool operator> (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.getStack() > rhs.getStack();
	}
	template <class T, class Container> bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return lhs.getStack() >= rhs.getStack();
	}

}

#endif //FT_CONTAINER_STACK_HPP
