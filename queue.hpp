//
// Created by casubmar on 01.03.2021.
//

#ifndef FT_CONTAINER_QUEUE_HPP
#define FT_CONTAINER_QUEUE_HPP

namespace ft {

	template <class T, class Container = list<T> >
	class queue {
	public:
		typedef T			value_type;
		typedef	Container	container_type;
		typedef	size_t		size_type;

		explicit queue (const container_type& ctnr = container_type()) : _ctnr(ctnr) {
		}

		bool empty() const { return _ctnr.empty(); }
		size_type size() const { return _ctnr.size(); }

		value_type& front() { return _ctnr.front(); }
		const value_type& front() const { return _ctnr.front(); }
		value_type& back() { return _ctnr.back(); }
		const value_type& back() const { return _ctnr.back(); }
		void push (const value_type& val) { _ctnr.push_back(val); }
		void pop() { _ctnr.pop_front(); }

		friend bool	operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs) {
			return (lhs.c == rhs.c);
		}
		friend bool operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) {
			return (lhs.c != rhs.c);
		}
		friend bool	operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs) {
			return (lhs.c < rhs.c);
		}
		friend bool operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs) {
			return (lhs.c > rhs.c);
		}
		friend bool	operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) {
			return (lhs.c <= rhs.c);
		}
		friend bool operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) {
			return (lhs.c >= rhs.c);
		}

	protected:
		container_type	_ctnr;
	};

}

#endif //FT_CONTAINER_QUEUE_HPP
