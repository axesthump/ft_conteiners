//
// Created by casubmar on 28.02.2021.
//

#ifndef FT_CONTAINER_VECTOR_HPP
#define FT_CONTAINER_VECTOR_HPP
#include <iostream>
#include <stdexcept>
#include "ft.hpp"

namespace ft {
	template <class T, class Alloc = std::allocator<T> >
class vector {
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
	allocator_type 			alloc;

	size_type 				_size;
	size_type 				_capacity;
	pointer					array;

	//Iterators
public:
	class iterator: public std::iterator<std::random_access_iterator_tag, value_type> {
	public:
		iterator(pointer ptr = 0): p(ptr) {}
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

		bool operator<=(iterator const & dt) const { return p <= dt.getPtr(); }
		bool operator>=(iterator const & dt) const { return p >= dt.getPtr(); }
		bool  operator<(iterator const & dt) const { return p  < dt.getPtr(); }
		bool  operator>(iterator const & dt) const { return p  > dt.getPtr(); }

		bool operator<=(const_iterator const & dt) const { return p <= dt.getPtr(); }
		bool operator>=(const_iterator const & dt) const { return p >= dt.getPtr(); }
		bool  operator<(const_iterator const & dt) const { return p  < dt.getPtr(); }
		bool  operator>(const_iterator const & dt) const { return p  > dt.getPtr(); }


		pointer getPtr() const {
			return p;
		}

		value_type& operator*() const { return *p; }
		value_type* operator->() const { return p; }

		iterator& operator++() {
			++p;
			return *this;
		}
		iterator operator++(int) { iterator temp = *this; ++p; return temp; }

		iterator& operator--() { --p; return *this; }
		iterator operator--(int) { iterator temp = *this; --p; return temp; }
		value_type & operator[]( const_reference const & index ) const { return p[index]; }
		iterator operator+(difference_type const & dt) const { return iterator(p + dt); }
		iterator operator-(difference_type const & dt) const { return iterator(p - dt); }
		iterator operator+=(difference_type const & dt) {
			p += dt;
			return *this;
		};

		iterator operator-=(difference_type const & dt) {
			p -= dt;
			return *this;
		};

	private:
		pointer p;

	};

public:
	class const_iterator: public std::iterator<std::random_access_iterator_tag, value_type> {
	public:
		const_iterator(pointer ptr = 0): p(ptr) {}
		const_iterator(const const_iterator& it) { *this = it; }
		const_iterator(const iterator& it) { *this = it; }
		const_iterator& operator=(const_iterator const & it) {
			if (this != &it) {
				p = it.getPtr();
			}
			return *this;
		}
		const_iterator& operator=(const iterator& it) {
			p = it.getPtr();
			return *this;
		}
		~const_iterator(){}

		bool operator<=(iterator const & dt) const { return p <= dt.getPtr(); }
		bool operator>=(iterator const & dt) const { return p >= dt.getPtr(); }
		bool  operator<(iterator const & dt) const { return p  < dt.getPtr(); }
		bool  operator>(iterator const & dt) const { return p  > dt.getPtr(); }

		bool operator<=(const_iterator const & dt) const { return p <= dt.getPtr(); }
		bool operator>=(const_iterator const & dt) const { return p >= dt.getPtr(); }
		bool  operator<(const_iterator const & dt) const { return p  < dt.getPtr(); }
		bool  operator>(const_iterator const & dt) const { return p  > dt.getPtr(); }

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

		pointer getPtr() const {
			return p;
		}

		value_type const& operator*() const { return *p; }
		value_type const* operator->() const { return p; }

		const_iterator& operator++() { ++p; return *this; }
		const_iterator operator++(int) {
			const_iterator temp = *this;
			++p;
			return temp;
		}

		const_iterator& operator--() { --p; return *this; }
		const_iterator operator--(int) { const_iterator temp = *this; --p; return temp; }
		value_type & operator[]( const_reference const & index ) const { return p[index]; }
		const_iterator operator+(difference_type const & dt) const { return iterator(p + dt); }
		const_iterator operator-(difference_type const & dt) const { return iterator(p - dt); }
		const_iterator operator+=(difference_type const & dt) {
			p += dt;
			return *this;
		};

		const_iterator operator-=(difference_type const & dt) {
			p -= dt;
			return *this;
		};

	private:
		pointer p;

	};

public:
	class reverse_iterator: public std::reverse_iterator<iterator> {
	public:
		reverse_iterator() {p = nullptr;}
		~reverse_iterator() {};
		reverse_iterator (reverse_iterator const & iter ) { *this = iter; }
		reverse_iterator(pointer ptr) { p = ptr; }
		reverse_iterator & operator=(reverse_iterator const & iter) {
			if (this != &iter)
				p = iter.p;
			return *this;
		}
		reverse_iterator & operator++() {
			this->p--;
			return *this;
		}
		reverse_iterator & operator--() {
			this->p++;
			return *this;
		}
		reverse_iterator operator++(int) {
			reverse_iterator temp = *this;
			this->operator++();
			return temp;
		}
		reverse_iterator operator--(int) {
			reverse_iterator temp = *this;
			this->operator--();
			return temp;
		}

		reverse_iterator &operator+=(difference_type count) {
			p -= count;
			return *this;
		};

		reverse_iterator &operator-=(difference_type count) {
			p += count;
			return *this;
		};

		reverse_iterator operator+(difference_type count) const { return reverse_iterator(p - count); };
		reverse_iterator operator-(difference_type count) const { return reverse_iterator(p + count); };
		difference_type operator+(reverse_iterator &i) const { return p - i.p; }
		difference_type operator-(reverse_iterator &i) const { return p + i.p; }

		bool operator==(reverse_iterator const & dt) const {return this->p == dt.p; }
		bool operator!=(reverse_iterator const & dt) const { return this->p != dt.p; }
		bool operator<=(reverse_iterator const & dt) const { return this->p >= dt.p; }
		bool operator>=(reverse_iterator const & dt) const { return this->p <= dt.p; }
		bool  operator<(reverse_iterator const & dt) const { return this->p > dt.p; }
		bool  operator>(reverse_iterator const & dt) const { return this->p < dt.p; }

		bool operator==(const_reverse_iterator const & dt) const { return this->p == dt.getPtr(); }
		bool operator!=(const_reverse_iterator const & dt) const { return this->p != dt.getPtr(); }
		bool operator<=(const_reverse_iterator const & dt) const { return this->p >= dt.getPtr(); }
		bool operator>=(const_reverse_iterator const & dt) const { return this->p <= dt.getPtr(); }
		bool  operator<(const_reverse_iterator const & dt) const { return this->p > dt.getPtr(); }
		bool  operator>(const_reverse_iterator const & dt) const { return this->p < dt.getPtr(); }

		value_type & operator*() const { return *this->p; }
		value_type * operator->() const { return this->p; }
		const_reference operator[](const_reference ref) const { return *(p - ref); };

		pointer getPtr() const {
			return p;
		}

	private:
		pointer p;

	};

public:
	class const_reverse_iterator: public std::reverse_iterator<const_iterator> {
	public:
		const_reverse_iterator() : p(nullptr) {}
		~const_reverse_iterator() {};
		const_reverse_iterator (reverse_iterator const & iter ) { *this = iter; }
		const_reverse_iterator (const_reverse_iterator const & iter ) { *this = iter; }
		const_reverse_iterator(pointer ptr) { p = ptr; }
		const_reverse_iterator & operator=(const_reverse_iterator const & iter) {
			if (this != &iter)
				p = iter.p;
			return *this;
		}

		const_reverse_iterator & operator=(reverse_iterator const & iter) {
			p = iter.getPtr();
			return *this;
		}

		const_reverse_iterator & operator++() {
			this->p--;
			return *this;
		}
		const_reverse_iterator & operator--() {
			this->p++;
			return *this;
		}
		const_reverse_iterator operator++(int) {
			const_reverse_iterator temp = *this;
			this->operator++();
			return temp;
		}
		const_reverse_iterator operator--(int) {
			const_reverse_iterator temp = *this;
			this->operator--();
			return temp;
		}

		const_reverse_iterator operator+(difference_type val) const { return const_reverse_iterator(p - val); };
		const_reverse_iterator operator-(difference_type val) const { return const_reverse_iterator(p + val); };
		difference_type operator+(const_reverse_iterator &it) const { return p - it._it; }
		difference_type operator-(const_reverse_iterator &it) const { return p + it._it; }
		const_reverse_iterator &operator+=(difference_type count) {
			p -= count;
			return *this;
		};

		const_reverse_iterator &operator-=(difference_type count) {
			p += count;
			return *this;
		};

		const_reference operator[](const_reference cr) { return *(p - cr); };
		const_reference operator*() { return *this->p; }
		const_pointer operator->() { return this->p; }

		bool operator==(reverse_iterator const & dt) const {return this->p == dt.getPtr(); }
		bool operator!=(reverse_iterator const & dt) const { return this->p != dt.getPtr(); }
		bool operator<=(reverse_iterator const & dt) const { return this->p >= dt.getPtr(); }
		bool operator>=(reverse_iterator const & dt) const { return this->p <= dt.getPtr(); }
		bool  operator<(reverse_iterator const & dt) const { return this->p > dt.getPtr(); }
		bool  operator>(reverse_iterator const & dt) const { return this->p < dt.getPtr(); }

		bool operator==(const_reverse_iterator const & dt) const { return this->p == dt.getPtr(); }
		bool operator!=(const_reverse_iterator const & dt) const { return this->p != dt.getPtr(); }
		bool operator<=(const_reverse_iterator const & dt) const { return this->p >= dt.getPtr(); }
		bool operator>=(const_reverse_iterator const & dt) const { return this->p <= dt.getPtr(); }
		bool  operator<(const_reverse_iterator const & dt) const { return this->p > dt.getPtr(); }
		bool  operator>(const_reverse_iterator const & dt) const { return this->p < dt.getPtr(); }

		pointer getPtr() const {
			return p;
		}

	private:
		pointer p;

	}; // end iterators

public:
	// Constructors
	vector (const allocator_type& _alloc = allocator_type()) {
		alloc = _alloc;
		_size = 0;
		_capacity = 0;
		array = 0;
	}

	vector (size_type n, const value_type& val = value_type(),
					 const allocator_type& _alloc = allocator_type()): alloc(_alloc) {
		array = alloc.allocate(n * 2);
		_capacity = n * 2;
		_size = 0;
		for (size_type i = 0; i < n; ++i) {
			push_back(val);
		}
	}

	template <class InputIterator>
	vector (InputIterator first, InputIterator last,
			const allocator_type& _alloc = allocator_type(), typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
		_size = 0;
		_capacity = len(first, last);
		alloc = _alloc;
		if (_capacity) {
			array = alloc.allocate(_capacity);//new value_type[_capacity];
			for (; first != last; ++first) {
				push_back(*first);
			}
		} else {
			array = 0;
		}

	}

	vector (const vector& x): _size(0), _capacity(0) {
		*this = x;
	}

	vector& operator= (const vector& x) {
		if (_size && array)
			clear();
		if (x._capacity > _capacity)
			_capacity = x._capacity;
		_size = 0;
		if (x.capacity()) {
			array = alloc.allocate(_capacity);//new value_type[_capacity];
			for (size_type i = 0; i < x._size; ++i) {
				push_back(x[i]);
			}
		} else
			array = x.array;
		return *this;
	}//end Constructors

	~vector() {
		clear();
	}

	//Iterators b:
	iterator begin() { return iterator(array); }
	const_iterator begin() const { return const_iterator(array); }
	iterator end() { return iterator(array + size()); }
	const_iterator end() const { return const_iterator(array + size()); }
	reverse_iterator rbegin() { return reverse_iterator(array + size() - 1); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(array + size() - 1); }
	reverse_iterator rend() { return reverse_iterator(array - 1); }
	const_reverse_iterator rend() const { return const_reverse_iterator(array - 1); }


	//Capacity:
	size_type size() const { return _size; }
	size_type	max_size() const {
		return alloc.max_size();
	}
	void resize (size_type n, value_type val = value_type()) {
		if (n < _size) {
			while (n < _size)
				pop_back();
		} else {
			pointer temp = alloc.allocate(n);//new value_type[n];
			for (size_type i = 0; i < _size; ++i) {
				temp[i] = array[i];
			}
			for (size_type i = _size; i < n; ++i) {
				temp[i] = val;
			}
			clear();
			array = temp;
			_size = n;
			_capacity = n;
		}

	}

	size_type capacity() const { return _capacity; }
	bool empty() const { return _size == 0; }

	void reserve (size_type n) {
		if (n <= _capacity) {
			return;
		}
		if (n > max_size()) {
			throw std::length_error("bad size");
		}
		size_type new_capacity = n;
		pointer temp = alloc.allocate(new_capacity);//new value_type[new_capacity];
		size_type temp_size = _size;
		for (size_type i = 0; i < _size; ++i) {
			alloc.construct(temp + i, array[i]);
		}
		clear();//delete[] array;
		array = temp;
		_size = temp_size;
		_capacity = new_capacity;
	} // end Capacity

	//Element access:
	reference operator[] (size_type n) { return *(array + n); }
	const_reference operator[] (size_type n) const { return *(array + n); }
	reference at (size_type n) {
		if (n >= _size)
			throw std::out_of_range("out of range");
		return array[n];
	}
	const_reference at (size_type n) const {
		if (n >= _size)
			throw std::out_of_range("out of range");
		return array[n];
	}
	reference front() { return array[0]; }
	const_reference front() const { return array[0]; }
	reference back() { return array[_size - 1]; }
	const_reference back() const { return array[_size - 1]; }
	//End element access

	//Modifiers:
	void	assign(size_type n, const value_type& val) {
		if (_capacity < n) {
			clear();
			array = alloc.allocate(n);//new value_type[n];
			_capacity = n;
		}
		for (size_type i = 0; i < n; ++i) {
			alloc.construct(array + i, val);
		}
		_size = n;

	}

	template <class InputIterator>
	void	assign (InputIterator first, InputIterator last,
					typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
		size_type l = len(first, last);
		if (_capacity < l) {
			clear();
			array = alloc.allocate(l);//new value_type[l];
			_capacity = l;
		}
		_size = 0;
		for (; first != last; ++first) {
			push_back(*first);
		}
	}

	void push_back (const value_type& val) {
		if (!array) {
			array = alloc.allocate(1);//new value_type[1];
			_capacity = 1;
			_size = 1;
			alloc.construct(array, val);//array[0] = val;
		} else {
			add_elem(val);
		}
	}
	void pop_back() {
		alloc.destroy(array + _size - 1);
		--_size;
	}
	void insert (iterator position, size_type n, const value_type& val) {
		vector<value_type> temp(begin(), position);

		while (n) {
			temp.push_back(val);
			--n;
		}
		temp.reserve(_size + n);
		for (; position != end(); ++position) {
			temp.push_back(*position);
		}
		size_type st = _size;
		clear();
		_size = st;
		*this = temp;
	}
	iterator insert (iterator position, const value_type& val) {
		vector<value_type> temp;
		if (_capacity < _size + 1) {
			return insert_with_realloc(position, val);
		} else {
			return insert_without_realloc(position, val);
		}
	}

	template <class InputIterator>
	void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
		while (first != last) {
			position = insert(position, *first);
			++position;
			++first;
		}
	}

	iterator erase (iterator position) {
		pointer ptr = position.getPtr();
		std::memmove(ptr, ptr + 1, static_cast<size_type>(abs((end().getPtr() - ptr))) * sizeof(value_type));
		--_size;
		return iterator(ptr);
	}

	iterator erase (iterator first, iterator last) {
		while (first != last) {
			erase(first);
			--last;
		}
		return last;
	}

	void swap (vector& x) {
		pointer tmpMass = x.array;
		size_type tmpSize = x._size;
		size_type tmpCapacity = x._capacity;
		allocator_type tmpAlloc = x.alloc;

		x.array = array;
		x._size = _size;
		x._capacity = _capacity;
		x.alloc = alloc;

		array = tmpMass;
		_size = tmpSize;
		_capacity = tmpCapacity;
		alloc = tmpAlloc;
	}
	void	clear() {
//		while (_size)
//			pop_back();
		for (size_type i = 0; i <_capacity; ++i) {
			alloc.destroy(array + i);
		}
		if (_capacity)
			alloc.deallocate(array, _capacity);
		_capacity = 0;
		_size = 0;
	}


private:
	iterator insert_with_realloc(iterator position, const value_type& val) {
		vector<value_type> temp;
		temp.reserve(_capacity * 2);
		bool isInsert = false;
		iterator start = begin();
		int i = 0;
		int res = 0;
		while (start != end()) {
			if (start == position && !isInsert) {
				temp.push_back(val);
				isInsert = true;
				res = i;
				++i;
			} else {
				temp.push_back(*start);
				++start;
				++i;
			}
		}
		if (position == end()) {
			temp.push_back(val);
			res = i;
		}
		*this = temp;
		_capacity = temp._capacity;
		_size = temp._size;
		return (iterator(array + res));
	}

	iterator insert_without_realloc(iterator position, const value_type& val) {
		size_type place = len(begin(), position);
		size_type last = len(begin(), end());
		value_type temp;
		value_type temp_val = val;
		while (place <= last) {
			temp = array[place];
			alloc.construct(array + place, temp_val);//array[place] = temp_val;
			temp_val = temp;
			++place;
		}
		++_size;
		return position;
	}


	void add_elem(const value_type& val) {

		if (_size + 1 > _capacity)
			resize();
		alloc.construct(array + _size, val);//array[_size] = val;
		++_size;
	}

	template <class InputIterator>
	size_type len(InputIterator first, InputIterator last, typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0) {
		size_type len = 0;
		while (first != last) {
			++len;
			++first;
		}
		return len;
	}

	void resize() {
		size_type new_capacity = _capacity * 2;
		pointer temp = alloc.allocate(new_capacity);//new value_type[new_capacity];
		for (size_type i = 0; i < _size; ++i) {
			alloc.construct(temp + i, array[i]);//temp[i] = array[i];
		}
		//delete[] array;
		size_type st = _size;
		clear();
		_size = st;
		array = temp;
		_capacity = new_capacity;
	}

}; // end vector
	template <class T, class Alloc> bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
		typename ft::vector<T, Alloc>::const_iterator lEnd = lhs.end();
		typename ft::vector<T, Alloc>::const_iterator rBegin = rhs.begin();

		if (lhs.size() != rhs.size())
			return false;
		for (typename ft::vector<T, Alloc>::const_iterator i = lhs.begin(); i != lEnd; ++i)
			if (*i != *rBegin++)
				return false;
		return true;
	}

	template <class T, class Alloc> bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(lhs == rhs); };
	template <class T, class Alloc> bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) {
		typename ft::vector<T, Alloc>::const_iterator lBegin = lhs.begin();
		typename ft::vector<T, Alloc>::const_iterator rBegin = rhs.begin();

		while (lBegin != lhs.end() && rBegin != rhs.end()){
			if (*lBegin < *rBegin)
				return true;
			++lBegin;
			++rBegin;
		}
		if (lBegin == lhs.end() && rBegin != rhs.end())
			return true;
		return false;
	};

	template <class T, class Alloc> bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs) { return !(rhs < lhs); };
	template <class T, class Alloc> bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return (rhs < lhs); };
	template <class T, class Alloc> bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) { return !(lhs < rhs); };
} // end ft

#endif //FT_CONTAINER_VECTOR_HPP
