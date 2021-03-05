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

		explicit stack (const container_type& ctnr = container_type()) : _ctnr(ctnr) {
		}
		bool empty() const { return _ctnr.empty(); }
		size_type size() const { return _ctnr.size(); }
		value_type& top() { return _ctnr.back(); }
		const value_type& top() const { return _ctnr.back(); }
		void push (const value_type& val) { _ctnr.push_back(val); }
		void pop() { _ctnr.pop_back(); }

		friend bool	operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return (lhs.c == rhs.c);
		}
		friend bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return (lhs.c != rhs.c);
		}
		friend bool	operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return (lhs.c < rhs.c);
		}
		friend bool operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return (lhs.c > rhs.c);
		}
		friend bool	operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return (lhs.c <= rhs.c);
		}
		friend bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
			return (lhs.c >= rhs.c);
		}

	protected:
		container_type	_ctnr;
	};
}

#endif //FT_CONTAINER_STACK_HPP
