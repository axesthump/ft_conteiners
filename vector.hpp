//
// Created by casubmar on 28.02.2021.
//

#ifndef FT_CONTAINER_VECTOR_HPP
#define FT_CONTAINER_VECTOR_HPP

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
	class iterator: public std::iterator<std::bidirectional_iterator_tag, value_type> {
	public:
		explicit iterator(pointer ptr = 0): p(ptr) {}
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

	private:
		pointer p;

	};

public:
	class const_iterator: public std::iterator<std::bidirectional_iterator_tag, value_type> {
	public:
		explicit const_iterator(pointer ptr = 0): p(ptr) {}
		const_iterator(const const_iterator& it) { *this = it; }
		const_iterator& operator=(const const_iterator& it) {
			if (this != &it) {
				p = it.p;
			}
			return *this;
		}
		~const_iterator(){}

		bool operator==(const iterator& rhs) const {
			return (p == rhs.p);
		}

		bool operator==(const const_iterator& rhs) const {
			return (p == rhs.getPtr());
		}


		bool operator!=(const iterator& rhs) const {
			return (p != rhs.p);
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
		const_iterator& operator++(int) { const_iterator temp = *this; ++p; return temp; }

		const_iterator& operator--() { --p; return *this; }
		const_iterator& operator--(int) { const_iterator temp = p; --p; return temp; }

	private:
		pointer p;

	};

public:
	class reverse_iterator: public std::reverse_iterator<iterator> {
	public:
		explicit reverse_iterator(pointer ptr = 0): p(ptr) {}
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

		pointer getPtr() const {
			return p;
		}

		value_type& operator*() const { return *p; }
		value_type* operator->() const { return p; }

		reverse_iterator& operator++() { --p; return *this; }
		reverse_iterator& operator++(int) { reverse_iterator temp = *this; --p; return temp; }

		reverse_iterator& operator--() { ++p; return *this; }
		reverse_iterator& operator--(int) { reverse_iterator temp = *this; ++p; return temp; }

	private:
		pointer p;

	};

public:
	class const_reverse_iterator: public std::reverse_iterator<const_iterator> {
	public:
		explicit const_reverse_iterator(pointer ptr = 0): p(ptr) {}
		const_reverse_iterator(const const_reverse_iterator& it) { *this = it; }
		const_reverse_iterator& operator=(const const_reverse_iterator& it) {
			if (this != &it) {
				p = it.p;
			}
			return *this;
		}
		~const_reverse_iterator(){}

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

		pointer getPtr() const {
			return p;
		}

		value_type const& operator*() const { return *p; }
		value_type const* operator->() const { return p; }

		const_reverse_iterator& operator++() { --p; return *this; }
		const_reverse_iterator& operator++(int) { reverse_iterator temp = *this; --p; return temp; }

		const_reverse_iterator& operator--() { ++p; return *this; }
		const_reverse_iterator& operator--(int) { reverse_iterator temp = *this; ++p; return temp; }

	private:
		pointer p;

	}; // end iterators

public:
	// Constructors
	explicit vector (const allocator_type& alloc = allocator_type()) {
		this->alloc = alloc;
		_size = 0;
		_capacity = 1; //todo Чекнуть
		array = new value_type[1];
	}

//	explicit vector (size_type n, const value_type& val = value_type(),
//					 const allocator_type& alloc = allocator_type()) {
//		array = new value_type[n * 2];
//		_capacity = n * 2;
//		_size = 0;
//		for (size_type i = 0; i < n; ++i) {
//			push_back(val);
//		}
//	}

	template <class InputIterator>
	vector (InputIterator first, InputIterator last,
			const allocator_type& alloc = allocator_type()) {
		_size = 0;
		_capacity = 1; //todo Чекнуть
		array = new value_type[1];
		for (; first != last; ++first) {
			push_back(*first);
		}
	}

	vector (const vector& x): _size(0), _capacity(0) {
		*this = x;
	}

	vector& operator= (const vector& x) {
		if (_size)
			delete[] array;
		_capacity = x._capacity;
		_size = x._size;
		array = new value_type[_capacity];
		for (size_type i = 0; i < _size; ++i) {
			array[i] = x.array[i];
		}
	}//end Constructors

	//Iterators b:
	iterator begin() { return iterator(array); }
	const_iterator begin() const { return const_iterator(array); }
	iterator end() { return iterator(array + size()); }
	const_iterator end() const { return const_iterator(array + size()); }
	reverse_iterator rbegin() { return reverse_iterator(array + size()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(array + size()); }
	reverse_iterator rend() { return reverse_iterator(array); }
	const_reverse_iterator rend() const { return const_reverse_iterator(array); }


	//Capacity:
	size_type size() const { return _size; }
	size_type	max_size() const {
		return alloc.max_size();
	}
	void resize (size_type n, value_type val = value_type()) {
		while (n < this->_size)
			pop_back();
		while (n > this->_size)
			push_back(val);
	}
	size_type capacity() const { return _capacity; }
	bool empty() const { return _size == 0; }

	void reserve (size_type n) {
		if (n <= _capacity) {
			return;
		}
		size_type new_capacity = n;
		pointer temp = new value_type[new_capacity];
		for (size_type i = 0; i < _size; ++i) {
			temp[i] = array[i];
		}
		delete[] array;
		array = temp;
		_capacity = new_capacity;
	} // end Capacity

	//Element access:
	reference operator[] (size_type n) { return array[n]; }
	const_reference operator[] (size_type n) const { return array[n]; }
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
		_size = 0;
		while (n) {
			push_back(val);
			--n;
		}
	}

//	template <class InputIterator>
//	void	assign (InputIterator first, InputIterator last,
//					typename ft::check_type<typename ft::iterator_traits<InputIterator>::iterator_category>::type* = 0) {
//		_size = 0;
//		while (first != last) {
//			push_back(*first);
//			++first;
//		}
//	}

	void push_back (const value_type& val) { add_elem(val); }
	void pop_back() { --_size; }
	void insert (iterator position, size_type n, const value_type& val) { //todo не чекал
		vector<value_type> temp(begin(), position);
		while (n) {
			temp.push_back(val);
			--n;
		}
		temp.assign(position, end());
		_size = 0;
		*this = temp;
	}
	iterator insert (iterator position, const value_type& val) {//todo не чекал
		insert(position, 1, val);
		return (--position);
	}

//	template <class InputIterator>//todo не чекал
//	void insert (iterator position, InputIterator first, InputIterator last) {
//		vector<value_type> temp(begin(), position);
//		while (first != last) {
//			temp.push_back(*first);
//			++first;
//		}
//		temp.assign(position, end());
//		_size = 0;
//		*this = temp;
//	}

	iterator erase (iterator position) {
		iterator res(position);
		iterator last = --end();
		iterator next(position);
		++next;
		while (position != last) {
			*position = *next;
			++position;
			++next;
		}
		--_size;
		return res;
	}

	iterator erase (iterator first, iterator last) {
		iterator res(last);
		size_type count = len(first, last);

		while (last != end()) {
			*first = *last;
			++first;
			++last;
		}
		_size -= count;
		return res;
	}

	void swap (vector& x) {
		vector temp(x);
		x = *this;
		*this = temp;
	}
	void	clear() {
		while (_size)
			pop_back();


















	void print() {
		for (size_type i = 0; i < _size; ++i) {
			std::cout << array[i] << " ";
		}
	}


private:
	void add_elem(const value_type& val) {
		if (_size + 1 >= _capacity)
			resize();
		array[_size] = val;
		++_size;
	}

	size_type len(iterator first, iterator last) {
		size_type len = 0;
		while (first != last) {
			++len;
			++first;
		}
		return len;
	}

	void resize() {
		size_type new_capacity = _capacity * 2;
		pointer temp = new value_type[new_capacity];
		for (size_type i = 0; i < _size; ++i) {
			temp[i] = array[i];
		}
		delete[] array;
		array = temp;
		_capacity = new_capacity;
	}

}; // end vector
} // end ft

#endif //FT_CONTAINER_VECTOR_HPP
