//
// Created by casubmar on 25.12.2020.
//

#ifndef FT_CONTAINER_LIST_HPP
#define FT_CONTAINER_LIST_HPP

#include <memory>
#include <stdexcept>
#include <cstddef>
#include <limits>
#include "ft.hpp"

namespace ft {

template <class T, class Alloc = std::allocator<T> >
class list {

public:
	typedef T											value_type;
	typedef Alloc										allocator_type;
	typedef typename allocator_type::reference			reference;
	typedef typename allocator_type::const_reference	const_reference;
	typedef typename allocator_type::pointer			pointer;
	typedef typename allocator_type::const_pointer		const_pointer;
	class 												iterator;
	class												const_iterator;
	class 												reverse_iterator;
	class												const_reverse_iterator;
	typedef ptrdiff_t									difference_type;
	typedef size_t										size_type;

private:
	typedef struct		s_node
	{
		struct s_node*	next;
		struct s_node*	prev;
		value_type*		data;
	}					t_node;
	typedef typename allocator_type::template rebind<t_node>::other allocator_rebind_type;

	t_node 					*end_node;
	allocator_type 			alloc;
	size_type 				_size;
	allocator_rebind_type	allocator_rebind;

//Iterators
public:
	class iterator: public std::iterator<std::bidirectional_iterator_tag, value_type> {
	public:
		explicit iterator(t_node* ptr = 0): p(ptr) {}
		iterator(const iterator& it) { *this = it; }
		iterator& operator=(const iterator& it) {
			if (this != &it) {
				p = it.p;
			}
			return *this;
		}
		~iterator(){}

		bool operator==(const iterator& rhs) const {
			return (p == rhs.getPtr());
		}

		bool operator==(const const_iterator& rhs) const {
			return (p == rhs.getPtr());
		}


		bool operator!=(const iterator& rhs) const {
			return (p != rhs.getPtr());
		}

		bool operator!=(const const_iterator& rhs) const {
			return (p != rhs.getPtr());
		}

		t_node* getPtr() const {
			return p;
		}

		value_type& operator*() const { return *(p->data); }
		value_type* operator->() const { return p->data; }

		iterator& operator++() {
			p = p->next;
			return *this;
		}
		iterator operator++(int) { iterator temp = *this; p = p->next; return temp; }

		iterator& operator--() { p = p->prev; return *this; }
		iterator operator--(int) { iterator temp = *this; p = p->prev; return temp; }

private:
	t_node * p;

};

 public:
	 class const_iterator: public std::iterator<std::bidirectional_iterator_tag, value_type> {
	 public:
		 explicit const_iterator(t_node* ptr = 0): p(ptr) {}
		 const_iterator(const const_iterator& it) { *this = it; }
		 const_iterator(const iterator& it) { *this = it; }

		 const_iterator& operator=(const const_iterator& it) {
			 if (this != &it) {
				 p = it.p;
			 }
			 return *this;
		 }

		 const_iterator& operator=(const iterator& it) {
			 p = it.getPtr();
			 return *this;
		 }

		 ~const_iterator(){}

		 bool operator==(const iterator& rhs) const {
			 return (p == rhs.getPtr());
		 }

		 bool operator==(const const_iterator& rhs) const {
			 return (p == rhs.getPtr());
		 }


		 bool operator!=(const iterator& rhs) const {
			 return (p != rhs.getPtr());
		 }

		 bool operator!=(const const_iterator& rhs) const {
			 return (p != rhs.getPtr());
		 }

		 t_node* getPtr() const {
			 return p;
		 }

		 value_type const& operator*() const { return *(p->data); }
		 value_type const* operator->() const { return p->data; }

		 const_iterator& operator++() { p = p->next; return *this; }
		 const_iterator operator++(int) { const_iterator temp = *this; p = p->next; return temp; }

		 const_iterator& operator--() { p = p->prev; return *this; }
		 const_iterator operator--(int) { const_iterator temp = p; p = p->prev; return temp; }

	 private:
		 t_node * p;

	 };

 public:
class reverse_iterator: public std::reverse_iterator<list::iterator> {
	 public:
		 explicit reverse_iterator(t_node* ptr = 0): p(ptr) {}
		 reverse_iterator(const reverse_iterator& it) { *this = it; }
		 reverse_iterator& operator=(const reverse_iterator& it) {
			 if (this != &it) {
				 p = it.p;
			 }
			 return *this;
		 }
		 ~reverse_iterator(){}

		 bool operator==(const reverse_iterator& rhs) const {
			 return (p == rhs.p);
		 }

		 bool operator==(const const_reverse_iterator& rhs) const {
			 return (p == rhs.getPtr());
		 }


		 bool operator!=(const reverse_iterator& rhs) const {
			 return (p != rhs.p);
		 }

		 bool operator!=(const const_reverse_iterator& rhs) const {
			 return (p != rhs.getPtr());
		 }

		 t_node* getPtr() const {
			 return p;
		 }

		 value_type& operator*() const { return *(p->data); }
		 value_type* operator->() const { return p->data; }

		 reverse_iterator& operator++() { p = p->prev; return *this; }
		 reverse_iterator operator++(int) { reverse_iterator temp = *this; p = p->prev; return temp; }

		 reverse_iterator& operator--() { p = p->next; return *this; }
		 reverse_iterator operator--(int) { reverse_iterator temp = *this; p = p->next; return temp; }

	 private:
		 t_node * p;

	 };

 public:
class const_reverse_iterator: public std::reverse_iterator<list::const_iterator> {
	 public:
		 explicit const_reverse_iterator(t_node* ptr = 0): p(ptr) {}
		 const_reverse_iterator(const const_reverse_iterator & it) { *this = it; }
		 const_reverse_iterator(const reverse_iterator & it) { *this = it; }
		 const_reverse_iterator& operator=(const const_reverse_iterator& it) {
			 if (this != &it) {
				 p = it.p;
			 }
			 return *this;
		 }
		const_reverse_iterator& operator=(const reverse_iterator& it) {
		 	p = it.getPtr();
			return *this;
		}
		 ~const_reverse_iterator(){}

		 bool operator==(const reverse_iterator& rhs) const {
			 return (p == rhs.getPtr());
		 }

		 bool operator==(const const_reverse_iterator& rhs) const {
			 return (p == rhs.getPtr());
		 }


		 bool operator!=(const reverse_iterator& rhs) const {
			 return (p != rhs.getPtr());
		 }

		 bool operator!=(const const_reverse_iterator& rhs) const {
			 return (p != rhs.getPtr());
		 }

		 t_node* getPtr() const {
			 return p;
		 }

		 value_type const& operator*() const { return *(p->data); }
		 value_type const* operator->() const { return p->data; }

		 const_reverse_iterator& operator++() { p = p->prev; return *this; }
		 const_reverse_iterator operator++(int) { const_reverse_iterator temp = *this; p = p->prev; return temp; }

		 const_reverse_iterator& operator--() { p = p->next; return *this; }
		 const_reverse_iterator operator--(int) { const_reverse_iterator temp = *this; p = p->next; return temp; }

	 private:
		 t_node * p;

	 };


public:
	explicit list (const allocator_type& alloc = allocator_type()) {
		this->alloc = alloc;
		create_end_node();
		_size = 0;
	}

	explicit list (size_type n, const value_type& val = value_type(),
				   const allocator_type& alloc = allocator_type()): _size(0) {
		this->alloc = alloc;
		create_end_node();

		for (size_type i = 0; i < n; ++i) {
			push_back(val);
		}
	}

	template <class InputIterator>
	list (InputIterator first, InputIterator last,
		  const allocator_type& alloc = allocator_type(), typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
		_size = 0;
		this->alloc = alloc;
		create_end_node();
		while(first != last) {
			push_back(*first);
			++first;
		}
	}

	list (const list& x): _size(0) {
		create_end_node();
		*this = x;
	}

	list& operator= (const list& x) {
		clear_list();
		const_iterator first = x.begin();
		for (; first != x.end(); ++first) {
			push_back(*first);
		}
		return *this;
	}

	~list() {
		clear();
		alloc.destroy(end_node->data);
		alloc.deallocate(end_node->data, 1);
		allocator_rebind.deallocate(end_node, 1);
	}

	iterator begin() {
		 return iterator(end_node->next);
	}
	const_iterator begin() const {
		 return const_iterator(end_node->next);
	}

	iterator end() {
		 return iterator(end_node);
	}
	const_iterator end() const {
		 return const_iterator(end_node);
	}

	reverse_iterator rbegin() {
		 return reverse_iterator(end_node->prev);
	}
	const_reverse_iterator rbegin() const {
		 return const_reverse_iterator(end_node->prev);
	}
	reverse_iterator rend() {
		return reverse_iterator(end_node);
	}
	const_reverse_iterator rend() const {
		return const_reverse_iterator(end_node);
	}

	//Capacity:
	bool empty() const { return _size == 0; }
	size_type size() const { return _size; }
	size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(t_node) / ((sizeof(value_type) == 1) ? 2 : 1); }

	//Element access:
	reference front() {
		return *end_node->next->data;
	}
	const_reference front() const {return end_node->next->data;}
	reference back() {return *end_node->prev->data;}
	const_reference back() const {return end_node->prev->data;}

	//Modifiers:
	void push_back (const value_type& val) {
		t_node* tmp = create_node(val);
		link_node(end_node->prev, end_node, tmp);
	}

	 template <class InputIterator>
	 void assign (InputIterator first, InputIterator last, typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
		clear_list();
		while (first != last) {
			push_back(*first);
			++first;
		}
	}

	void assign (size_type n, const value_type& val) {
		clear_list();
		for (size_type i = 0; i < n; ++i) {
			push_back(val);
		}
	}

	void push_front (const value_type& val) {
		link_node(end_node, end_node->next, create_node(val));
	}

	void pop_front() {
		if (_size) {
			end_node->next = delete_node(end_node->next);
			end_node->next->prev = end_node;
		}
	}

	void pop_back() {
		if (_size) {
			t_node* temp = end_node->prev;
			unlink_node(temp);
			delete_node(temp);
		}
	}

	iterator insert (iterator position, const value_type& val) {
		link_node(position.getPtr()->prev, position.getPtr(), create_node(val));
		return iterator(position.getPtr()->prev);
	}

	void insert (iterator position, size_type n, const value_type& val) {
		for (size_type i = 0; i < n; ++i) {
			link_node(position.getPtr()->prev, position.getPtr(), create_node(val));
		}
	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last) {
		ft::list<T> temp(first, last);
		iterator firstT = temp.begin();
		iterator lastT = temp.end();
		for (; firstT != lastT; ++firstT) {
			insert(position, *firstT);
		}
	}

	iterator erase (iterator position) {
		unlink_node(position.getPtr());
		return iterator(delete_node(position.getPtr()));
	}

	iterator erase (iterator first, iterator last) {
		for (; first != last; ) {
			first = erase(first);
		}
		return first;
	}

	void swap (list& x) {
		t_node* temp = end_node;
		end_node = x.end_node;
		x.end_node = temp;
		size_type temp_size = _size;
		_size = x.size();
		x._size = temp_size;
	}

	void resize (size_type n, value_type val = value_type()) {
		while (_size > n) {
			pop_back();
		}
		while (_size < n) {
			push_back(val);
		}
	}

	void clear() {
		clear_list();
	}

	//Operations:
	void splice (iterator position, list& x) {
		splice(position, x, x.begin(), x.end());
	}

	void splice (iterator position, list& x, iterator i) {
		 t_node* prev = position.getPtr()->prev;
		unlink_node(i.getPtr());
		 link_node(prev, position.getPtr(), i.getPtr());
		 ++_size;
		 --x._size;
	}

	void splice (iterator position, list& x, iterator first, iterator last) {
		while (first != last) {
			iterator temp = first;
			++first;
			splice(position, x, temp);
		}
	}

	void remove (const value_type& val) {
		iterator start = begin();
		while (start != end()) {
			if (*start == val)
				start = erase(start);
			else
				++start;
		}
	}

	template <class Predicate>
	void remove_if (Predicate pred) {
		iterator start = begin();
		while (start != end()) {
			if (pred(*start))
				start = erase(start);
			else
				++start;
		}
	}

	void	unique() {
		iterator first = begin();
		iterator last = end();
		iterator next = first;
		while (++next != last) {
			if (*first == *next) {
				erase(next);
			} else {
				first = next;
			}
			next = first;
		}
	}

	template <class BinaryPredicate>
	void unique (BinaryPredicate binary_pred) {
		iterator first = begin();
		iterator last = end();
		iterator next = first;
		while (++next != last) {
			if (binary_pred(*first, *next)) {
				erase(next);
			} else {
				first = next;
			}
			next = first;
		}
	}

	void merge (list& x) {
		if (this == &x)
			return;
		iterator thisIterator = begin();
		iterator targetIterator = x.begin();
		size_type i = x._size;
		while (i){
			if (thisIterator == end()){
				splice(thisIterator, x, targetIterator, x.end());
				break;
			}
			if (*targetIterator <= *thisIterator){
				thisIterator = insert(thisIterator, *targetIterator);
				x.pop_front();
				i--;
				targetIterator++;
			}
			thisIterator++;
		}

	}

	template <class Compare>
	void merge (list& x, Compare comp) {
		if (this == &x)
			return;
		iterator thIt = begin();
		iterator xIt = x.begin();
		size_type i = x._size;
		while (i){
			if (thIt == end()){
				splice(thIt, x, xIt, x.end());
				break;
			}
			if (comp(*xIt, *thIt)){
				thIt = insert(thIt, *xIt);
				x.pop_front();
				i--;
				xIt++;
			}
			thIt++;
		}
	}



	void sort() {
		iterator start = begin();
		if (start == end())
			return;
		iterator next = ++begin();

		while (start != end()) {
			while (next != end()) {
				if (*next < *start) {
					swap(next.getPtr(), start.getPtr());
				}
				++next;
			}
			++start;
			next = start;
			++next;
		}
	}

	template <class Compare>
	void sort (Compare comp) {
		iterator start = begin();
		if (start == end())
			return;
		iterator next = ++begin();

		while (start != end()) {
			while (next != end()) {
				if (comp(*next, *start)) {
					swap(next.getPtr(), start.getPtr());
				}
				++next;
			}
			++start;
			next = start;
			++next;
		}
	}

	void reverse() {
		t_node* up = end_node->next;
		t_node* down = end_node->prev;
		for (int i = 0; i < _size / 2; ++i){
			swap(up, down);
			up = up->next;
			down = down->prev;
		}
	}






private:

	 void	swap(t_node* first, t_node* second) {
		 if (first == second)
			 return ;
		 value_type* temp = first->data;
		 first->data = second->data;
		 second->data = temp;
	}

	t_node* create_node(const value_type& val) {
		t_node* tmp = allocator_rebind.allocate(1);
		tmp->data = alloc.allocate(1);
		alloc.construct(tmp->data, val);
		++_size;
		return tmp;
	}

	void	link_node(t_node* prev, t_node* next, t_node* target) {
		target->prev = prev;
		target->next = next;
		prev->next = target;
		next->prev = target;
	}

	void	unlink_node(t_node* target) {
		target->prev->next = target->next;
		target->next->prev = target->prev;
	}

	void create_end_node() {
		end_node = allocator_rebind.allocate(1);
		end_node->next = end_node;
		end_node->prev = end_node;
		end_node->data = alloc.allocate(1);
	}

	t_node* delete_node(t_node* node) {
		if (size()) {
			t_node* temp = node->next;
			alloc.destroy(node->data);
			alloc.deallocate(node->data, 1);
			allocator_rebind.deallocate(node, 1);
			--_size;
			return temp;
		}
		return 0;
	}

	void clear_list() {
		while (size()) {
			pop_back();
		}
	}


}; //end list
	template <class T, class Alloc>
	bool operator==(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		typename ft::list<T, Alloc>::const_iterator it = rhs.begin();
		typename ft::list<T, Alloc>::const_iterator i = lhs.begin();
		if (lhs.size() == rhs.size() && lhs.size() == 0)
			return true;
		if (lhs.size() == rhs.size()) {
			for (; i != lhs.end() && it != rhs.end(); ++i)
				if (*i != *it++)
					return false;
			return true;
		}
		return false;
	}

	template <class T, class Alloc>
	bool operator!= (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) { return !(lhs == rhs); }

	template <class T, class Alloc>
	bool operator<  (const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		typename ft::list<T, Alloc>::const_iterator rhsBegin = rhs.begin();
		typename ft::list<T, Alloc>::const_iterator lhsBegin = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator rhsEnd = rhs.end();
		typename ft::list<T, Alloc>::const_iterator lhsEnd = lhs.end();

		if (lhs.size() == rhs.size() && lhs.size() == 0)
			return false;
		while (rhsBegin != rhsEnd && lhsBegin != lhsEnd) {
			if (*lhsBegin++ < *rhsBegin++)
				return true;
		}
		if (rhs.size() != lhs.size())
			return lhs.size() < rhs.size();
		return false;
	}

	template <class T, class Alloc>
	bool operator<=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>=(const list<T,Alloc>& lhs, const list<T,Alloc>& rhs) {
		return (!(lhs < rhs));
	}

	template <class T, class Alloc> void swap(list<T,Alloc>& x, list<T,Alloc>& y) { x.swap(y);};

} //end ft

#endif //FT_CONTAINER_LIST_HPP
