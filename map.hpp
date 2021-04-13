//
// Created by Cave Submarine on 4/5/21.
//

#ifndef FT_CONTAINER_MAP_HPP
#define FT_CONTAINER_MAP_HPP

#include "string"
#include "ft.hpp"
#include "iostream"

namespace ft {

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key,T> > > class map {

	public:
		class												iterator;
		class												const_iterator;
		class												reverse_iterator;
		class 												const_reverse_iterator;

		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const key_type,mapped_type>			value_type;
		typedef Compare										key_compare;
		typedef Alloc										allocator_type;
		typedef value_type &								reference;
		typedef const value_type &							const_reference;
		typedef value_type *								pointer;
		typedef const value_type *							const_pointer;
		typedef size_t 										size_type;
		typedef ptrdiff_t 									difference_type;

		class value_compare : public std::binary_function<value_type, value_type, bool> {
		public:
			key_compare cmp;

			explicit value_compare(key_compare c) : cmp(c) {};
		public:

			bool operator()(const value_type &x, const value_type &y) const { return cmp(x.first, y.first); };
		};


	private:
		typedef struct Node {
			Node*	left;
			Node*	right;
			Node*	parent;
			pointer data;
			char 	color;
		}			TreeNode;

		typedef typename allocator_type::template rebind<TreeNode>::other alloc_rebind;

		TreeNode *	root;
		TreeNode *	endNode;
		TreeNode *	beginNode;
		size_type 	_size;
		key_compare	cmp;

		alloc_rebind		 	alloc_r;
		allocator_type 			alloc;

		// Utils
		void allocBeginNode() {
			beginNode = alloc_r.allocate(1);
			beginNode->color = 'b';
			beginNode->left = nullptr;
			beginNode->right = nullptr;
			beginNode->parent = nullptr;
		}

		void allocEndNode() {
			endNode = alloc_r.allocate(1);
			endNode->color = 'b';
			endNode->left = nullptr;
			endNode->right = nullptr;
			endNode->parent = nullptr;
		}

		void allocEmptyMap() {
			allocBeginNode();
			allocEndNode();
		}

		TreeNode* createNode(TreeNode* parent, const_reference value, char color) {
			TreeNode* node = alloc_r.allocate(1);
			node->parent = parent;
			node->right = nullptr;
			node->left = nullptr;
			node->color = color;
			node->data = alloc.allocate(1);
			alloc.construct(node->data, value);
			++_size;
			return node;
		}

		void destroyNode(TreeNode* node) {
			alloc.destroy(node->data);
			alloc.deallocate(node->data, 1);
			alloc_r.deallocate(node, 1);
			--_size;
		}


		bool treeInsert(value_type key) {
			TreeNode* node = createNode(nullptr, key, 'r');
			if (root == nullptr) {
				root = node;
				root->color = 'b';
			}
			else {
				TreeNode* parent = getNodeByKey(key.first);
				if (parent && parent->data->first == key.first) {
					destroyNode(node);
					return false;
				}
				node->parent = parent;
				if (key < (*parent->data))
					parent->left = node;
				else
					parent->right = node;
				nodeRecolor(node);
			}
			return true;
		}


		TreeNode* getNodeByKey(key_type key) {
			TreeNode* tmp = root;

			while (tmp != nullptr) {
				if (key > tmp->data->first) {
					if (tmp->right == nullptr)
						break;
					tmp = tmp->right;
				}
				else if (key < tmp->data->first) {
					if (tmp->left == nullptr)
						break;
					tmp = tmp->left;
				}
				else {
					break;
				}
			}
			return tmp;
		}



		void nodeRecolor(TreeNode* node) {
			TreeNode* parent = node->parent;
			TreeNode* grandparent = parent ? parent->parent : nullptr;
			TreeNode* uncle = parent ? getUncle(parent): nullptr;

			if (node == root) {
				node->color = 'b';
				return;
			}
			if (isRedNode(parent)) {
				if (uncle && isRedNode(uncle)) {
					parent->color = 'b';
					uncle->color = 'b';
					grandparent->color = 'r';
					nodeRecolor(grandparent);
				}
				else
					isLeftNode(parent) ? leftBalance(node, parent, grandparent) : rightBalance(node, parent,
																							   grandparent);
			}
		}



		void leftBalance(TreeNode *node, TreeNode *parent, TreeNode *grandparent) {
			if (isLeftNode(node))
				swapColors(parent, grandparent);
			else {
				leftRotate(parent);
				swapColors(node, grandparent);
			}
			rightRotate(grandparent);
		}

		void rightBalance(TreeNode *node, TreeNode *parent, TreeNode *grandparent) {
			if (isLeftNode(node)) {
				rightRotate(parent);
				swapColors(node, grandparent);
			}
			else
				swapColors(parent, grandparent);
			leftRotate(grandparent);
		}



		TreeNode* getUncle(TreeNode* parentNode) {
			if (parentNode == nullptr || parentNode->parent == nullptr) {
				return nullptr;
			}
			if (isLeftNode(parentNode))
				return parentNode->parent->right;
			else
				return parentNode->parent->left;

		}

		bool isLeftNode(TreeNode* node) { return node == node->parent->left; }
		bool isRedNode(TreeNode* node) { return node->color == 'r'; }


		void swapColors(TreeNode* lhs, TreeNode* rhs) {
			if (lhs == nullptr || rhs == nullptr)
				return;
			char lhsColor = lhs->color;
			lhs->color = rhs->color;
			rhs->color = lhsColor;
		}



		void rightRotate(TreeNode *oldRoot) {
			TreeNode *newRoot = oldRoot->left;
			if (oldRoot == root)
				root = newRoot;
			lowNode(newRoot, oldRoot);
			oldRoot->left = newRoot->right;
			if (newRoot->right != nullptr)
				newRoot->right->parent = oldRoot;
			newRoot->right = oldRoot;
		}

		void leftRotate(TreeNode* node) {
			TreeNode* rightNode = node->right;
			if (node == root)
				root = rightNode;
			lowNode(rightNode, node);
			node->right = rightNode->left;
			if (rightNode->left != nullptr)
				rightNode->left->parent = node;
			rightNode->left = node;

		}

		void lowNode(TreeNode *newRoot, TreeNode *oldRoot) {
			if (oldRoot->parent != NULL)
				isLeftNode(oldRoot) ? oldRoot->parent->left = newRoot : oldRoot->parent->right = newRoot;
			newRoot->parent = oldRoot->parent;
			oldRoot->parent = newRoot;
		}


		void addBeginNode() {
			TreeNode* temp = root;
			while (temp->left) {
				temp = temp->left;
			}
			temp->left = beginNode;
			beginNode->parent = temp;
		}

		void addEndNode() {
			TreeNode* temp = root;
			while (temp->right) {
				temp = temp->right;
			}
			temp->right= endNode;
			endNode->parent = temp;
		}



		void treeErase(TreeNode* toErase) {
			if (toErase == root && toErase->left == nullptr && toErase->right == nullptr) {
				destroyNode(root);
				root = nullptr;
				return;
			}
			TreeNode* nodeToReplace = getNodeToReplace(toErase);

			bool boothBlack = ((!nodeToReplace || !isRedNode(nodeToReplace)) && (!isRedNode(toErase)));
			TreeNode* parent = toErase->parent;

			if (!nodeToReplace) {
				if (nodeToReplace == root) {
					root = nullptr;
				} else {
					if (boothBlack)
						fixDoubleBlack(toErase);
					else
						if (getSibling(toErase) != nullptr)
							getSibling(toErase)->color = 'r';
					isLeftNode(toErase)
							? parent->left = nullptr
							: parent->right = nullptr;
				}
				destroyNode(toErase);
				return;
			}
			if (!toErase->left || !toErase->right) {
				if (toErase == root) {
					alloc.destroy(toErase->data);
					alloc.construct(toErase->data, *(nodeToReplace->data));
					toErase->left = nullptr;
					toErase->right = nullptr;
					destroyNode(nodeToReplace);
				} else {
					isLeftNode(toErase)
							? parent->left = nodeToReplace
							: parent->right = nodeToReplace;
					destroyNode(toErase);
					nodeToReplace->parent = parent;
					if (boothBlack)
						fixDoubleBlack(nodeToReplace);
					else
						nodeToReplace->color = 'b';
				}
				return;
			}

			nodeToReplace = swapValues(nodeToReplace, toErase);
			treeErase(nodeToReplace);
		}


		TreeNode* swapValues(TreeNode* nodeToReplace, TreeNode* nodeToErase) {
			bool isLeft = isLeftNode(nodeToReplace);
			TreeNode *leftChild = nodeToReplace->left;
			TreeNode *rightChild = nodeToReplace->right;
			TreeNode *parentReplace = nodeToReplace->parent;
			TreeNode *parentErase = nodeToErase->parent;

			if (parentReplace == nodeToErase) {
				if (!isLeft)
					link(nodeToReplace, nodeToErase->left, 'b');
				else
					link(nodeToReplace, nodeToErase->right,'r');

				if (parentErase) {
					if (isLeftNode(nodeToErase))
						link(parentErase, nodeToReplace, 'b');
					else
						link(parentErase, nodeToReplace, 'r');
				}
				else
					parentReplace = nullptr;

				if (!isLeft)
					link(nodeToReplace, nodeToErase, 'r');
				else
					link(nodeToReplace, nodeToErase, 'b');

				link(nodeToErase, rightChild, 'r');
				link(nodeToErase, leftChild, 'b');
			}
			else {
				link(nodeToReplace, nodeToErase->right, 'r');
				link(nodeToReplace, nodeToErase->left, 'b');
				if (nodeToErase != root && isLeftNode(nodeToErase))
					link(parentErase, nodeToReplace, 'b');
				else
					link(parentErase, nodeToReplace, 'r');

				if (isLeft)
					link(parentReplace, nodeToErase, 'b');
				else
					link(parentReplace, nodeToErase, 'r');
				link(nodeToErase, leftChild, 'b');
				link(nodeToErase, rightChild, 'r');
			}
			if (nodeToErase == root) {
				root = nodeToReplace;
				root->parent = nullptr;
			}
			return nodeToErase;
		}

		void link(TreeNode *parent, TreeNode *node, char side) {
			if (!parent)
				return;
			side == 'r' ? parent->right = node : parent->left = node;
			if (node)
				node->parent = parent;
		}


		void fixDoubleBlack(TreeNode* node) {
			if (node == root)
				return;

			TreeNode* brother = getSibling(node);
			TreeNode* parent = node->parent;
			if (brother == nullptr) {
				fixDoubleBlack(parent);
			} else {
				if (isRedNode(brother)) {
					parent->color = 'r';
					brother->color = 'b';
					if (brother == parent->left) {
						rightRotate(parent);
					} else {
						leftRotate(parent);
					}
					fixDoubleBlack(node);
				} else {
					if (hasRedChild(brother)) {
						if (brother->left != nullptr && isRedNode(brother->left)) {
							if (brother == parent->left) {
								brother->left->color = brother->color;
								brother->color = parent->color;
								rightRotate(parent);
							} else {
								brother->left->color = parent->color;
								rightRotate(brother);
								leftRotate(parent);
							}
						} else {
							if (brother == parent->left) {
								brother->right->color = parent->color;
								leftRotate(brother);
								rightRotate(parent);
							} else {
								brother->right->color = brother->color;
								brother->color = parent->color;
								leftRotate(parent);
							}
						}
						parent->color = 'b';
					} else {
						brother->color = 'r';
						if (!isRedNode(parent))
							fixDoubleBlack(parent);
						else
							parent->color = 'b';
					}
				}
			}
		}

		bool hasRedChild(TreeNode* node) {
			return (node->left != nullptr and node->left->color == 'r') or
				   (node->right != nullptr and node->right->color == 'r');
		}









		TreeNode* getSibling(TreeNode* node) {
			if (!node || node->parent == nullptr) {
				return nullptr;
			} else if (node->parent->left == node) {
				return node->parent->right;
			} else {
				return node->parent->left;
			}
		}


		TreeNode* successor(TreeNode* x) {
			Node *temp = x;

			while (temp->left != NULL)
				temp = temp->left;

			return temp;
		}

		TreeNode* getNodeToReplace(TreeNode* toErase) {
			if (!toErase->left && !toErase->right)
				return nullptr;
			else if (toErase->left && toErase->right) {
				return successor(toErase->right);
			}
			else {
				return toErase->left ? toErase->left : toErase->right;
			}
		}


		bool eraseByKey(key_type key) {
			if (root == nullptr)
				return false;
			TreeNode *node = getNodeByKey(key);
			if (node->data->first != key)
				return false;
			treeErase(node);
			return true;
		}


		void unlinkBeginAndEnd() {
			if (_size) {
				if (beginNode->parent)
					beginNode->parent->left = nullptr;
				if (endNode->parent)
					endNode->parent->right = nullptr;
			}
		}

		void linkBeginAndEnd() {
			if (_size) {
				addEndNode();
				addBeginNode();
			}
		}

	public:
		map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : root(nullptr), cmp(comp), alloc(alloc), _size(0){
			allocEmptyMap();
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& _alloc = allocator_type(),
			 typename ft::enable_if<std::__is_input_iterator<InputIterator>::value>::type* = 0): alloc(_alloc), _size(0), cmp(comp) {
			allocEmptyMap();
			insert(first, last);
		}

		map (const map& x)  : _size(0) {
			*this = x;
		}


		map& operator=(const map& x) {
			if (this != &x) {
				const_iterator iter = x.begin();
				clear();
				allocEmptyMap();
				while (iter != x.end())
					insert(*(iter)++);
			}
			return *this;
		}


		~map() {
			clear();
			alloc_r.deallocate(endNode, 1);
			alloc_r.deallocate(beginNode, 1);
		}

		iterator 					find (const key_type& k) {
			iterator step = begin();
			for (; step != end(); ++step)
				if (step.getNode()->data->first == k)
					break;
			return step;
		}


		const_iterator 				find (const key_type& k) const {
			const_iterator step = begin();
			for (; step != end(); ++step)
				if (step.getNode()->data->first == k)
					break;
			return step;
		}



		std::pair<iterator, bool> insert (const_reference val) {
			unlinkBeginAndEnd();
			bool result = treeInsert(val);
			linkBeginAndEnd();
			return std::make_pair(find(val.first), result);
		};


		iterator insert (iterator position, const value_type& val) {
			(void)position;
			return insert(val).first;
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last) {
			for (; first != last; ++first) {
				insert(*first);
			}
		}

		void erase (iterator position) {
			if (position != iterator(endNode))
				erase(position->first);
		};

		size_type erase (const key_type& k) {
			unlinkBeginAndEnd();
			bool ret = eraseByKey(k);
			linkBeginAndEnd();
			return ret;
		}


		void erase (iterator first, iterator last) {
			if (first == begin() && last == end()) {
				clear();
				return;
			}
			iterator tmp;
			while (first != last) {
				tmp = first;
				++tmp;
				erase(first);
				first = tmp;
			}
		}


		void swap (map& lhs) {
			TreeNode *t = root;
			root = lhs.root;
			lhs.root = t;
			t = endNode;
			endNode = lhs.endNode;
			lhs.endNode = t;
			t = beginNode;
			beginNode = lhs.beginNode;
			lhs.beginNode = t;
			size_type size = _size;
			_size = lhs._size;
			lhs._size = size;
		}


		void clear() {
			while (_size) {
				erase(begin());
			}
		}

		key_compare key_comp() const { return cmp; }

		value_compare value_comp() const { return value_compare(cmp); }


		size_type count (const key_type& k) const { return find(k) != end(); }


		iterator 		lower_bound (const key_type& k) {
			iterator start = begin();
			iterator finish = end();
			while (start != finish && cmp(start->first, k))
				++start;
			return start;
		};

		const_iterator	lower_bound (const key_type& k) const {
			iterator start = begin();
			iterator finish = end();
			while (start != finish && cmp(start->first, k))
				++start;
			return start;
		};


		iterator 		upper_bound (const key_type& k) {
			iterator lb = lower_bound(k);
			if (lb != end() && !cmp(lb->first, k) && !cmp(k, lb->first))
				return ++lb;
			return lb;
		};

		const_iterator	upper_bound (const key_type& k) const {
			const_iterator lb = lower_bound(k);
			if (lb != end() && !cmp(lb->first, k) && !cmp(k, lb->first))
				return ++lb;
			return lb;
		};


		std::pair<const_iterator,const_iterator> equal_range (const key_type& k) const {  return std::make_pair(lower_bound(k), upper_bound(k)); }
		std::pair<iterator,iterator>             equal_range (const key_type& k) { return std::make_pair(lower_bound(k), upper_bound(k)); }













		iterator 				begin()             { return (_size) ? iterator(beginNode->parent) : iterator(endNode); }
		const_iterator 		    begin()     const   { return (_size) ? const_iterator(beginNode->parent) : const_iterator(endNode); }
		iterator				end()               { return iterator(endNode); }
		const_iterator			end()       const   { return const_iterator(endNode); }

		reverse_iterator		rbegin()            { return (_size) ? reverse_iterator(endNode->parent) : reverse_iterator(beginNode); }
		const_reverse_iterator	rbegin()    const   { return (_size) ? const_reverse_iterator(endNode->parent) : const_reverse_iterator(beginNode); }
		reverse_iterator		rend()              { return reverse_iterator(beginNode); }
		const_reverse_iterator	rend()      const   { return const_reverse_iterator(beginNode); }






		class iterator : public std::iterator<std::bidirectional_iterator_tag, value_type> {
		private:
			TreeNode* node;
		public:
			iterator(TreeNode* _node = nullptr): node(_node) {};
			~iterator() {};
			iterator & operator=(const iterator &it) {
				node = it.node;
				return *this;
			};
			iterator(const iterator &it) { *this = it; };
			iterator & operator++() {
				if (node->right) {
					node = deep(node->right);
					return *this;
				}
				else if (node->parent && isLeftChild(node)) {
					node = node->parent;
					return *this;
				}
				else if (!isLeftChild(node))
					node = node->parent;
				TreeNode *temp = node;
				while (!isLeftChild(temp)) {
					temp = temp->parent;
					if (!temp) {
						node = node->right;
						return *this;
					}
				}
				node = temp->parent;
				return *this;
			};
			iterator operator++(int) {
				iterator temp(node);
				operator++();
				return temp;
			};
			iterator & operator--() {
				if (node->left) {
					node = up(node->left);
					return *this;
				}
				else if (node->parent && !isLeftChild(node)) {
					node = node->parent;
					return *this;
				}
				TreeNode *temp = node;
				while (isLeftChild(temp)) {
					temp = temp->parent;
					if (!temp) {
						node = node->left;
						return *this;
					}
				}
				node = node->parent;
				return *this;
			};
			iterator operator--(int) {
				iterator temp(node);
				operator--();
				return temp;
			};

			bool operator==(const iterator &iter) const { return node == iter.node; };
			bool operator!=(const iterator &iter) const { return node != iter.node; };
			bool operator==(const const_iterator &iter) const { return node == iter.getNode(); };
			bool operator!=(const const_iterator &iter) const { return node != iter.getNode(); };

			reference operator*() const { return *(node->data); }
			pointer operator->() const {
				return node->data; }
			TreeNode *getNode() const { return node; }

		private:
			bool isLeftChild(TreeNode* node) { return node && node->parent && node->parent->left == node; }

			TreeNode *deep(TreeNode *node) {
				if (node->left)
					return deep(node->left);
				return node;
			}

			TreeNode *up(TreeNode *node) {
				if (node->right)
					return up(node->right);
				return node;
			}
		};










		class const_iterator : public std::iterator<std::bidirectional_iterator_tag, value_type const> {
		private:
			TreeNode* node;
		public:
			const_iterator(TreeNode* _node = nullptr): node(_node) {};
			~const_iterator() {};
			const_iterator & operator=(const_iterator const & rhs) {
				if (this != &rhs)
					node = rhs.getNode();
				return *this;
			}
			const_iterator & operator=(iterator const & rhs) {
				node = rhs.getNode();
				return *this;
			}


			const_iterator(const const_iterator &src) { *this = src; };
			const_iterator(const iterator& src) { *this = src; }
			const_iterator & operator++() {
				if (node->right) {
					node = getMinNode(node->right);
					return *this;
				}
				else if (node->parent && node->parent->left == node) {
					node = node->parent;
					return *this;
				}
				else if (node->parent->right == node)
					node = node->parent;
				TreeNode *temp = node;
				while (temp->parent->right == temp) {
					temp = temp->parent;
					if (!temp) {
						node = node->right;
						return *this;
					}
				}
				node = temp->parent;
				return *this;
			};
			const_iterator operator++(int) {
				iterator temp(node);
				operator++();
				return temp;
			};
			const_iterator & operator--() {
				if (node->left) {
					node = getMaxNode(node->left);
					return *this;
				}
				else if (node->parent && node->parent->right == node) {
					node = node->parent;
					return *this;
				}
				TreeNode *temp = node;
				while (temp->parent->left == temp) {
					temp = temp->parent;
					if (!temp) {
						node = node->left;
						return *this;
					}
				}
				node = node->parent;
				return *this;
			};
			const_iterator operator--(int) {
				iterator temp(node);
				operator--();
				return temp;
			};
			bool operator==(const iterator &iter) const { return node == iter.getNode(); };
			bool operator!=(const iterator &iter) const { return node != iter.getNode(); };

			bool operator==(const const_iterator &iter) const { return node == iter.getNode(); };
			bool operator!=(const const_iterator &iter) const { return node != iter.getNode(); };

			reference operator*() const { return *(node->data); }
			pointer operator->() const {
				return node->data; }
			TreeNode *getNode() const { return node; }

		private:
			TreeNode *getMinNode(TreeNode *node) {
				if (node->left)
					return getMinNode(node->left);
				return node;
			}

			TreeNode *getMaxNode(TreeNode *node) {
				if (node->right)
					return getMaxNode(node->right);
				return node;
			}
		};



		class reverse_iterator : public std::reverse_iterator<iterator> {
		private:
			TreeNode * node;
		public:
			reverse_iterator(TreeNode * _node = nullptr): node(_node) {};
			~reverse_iterator() {};
			reverse_iterator(const reverse_iterator &iter) { *this = iter; };

			reverse_iterator & operator=(const reverse_iterator &iter) {
				this->node = iter.node;
				return *this;
			};

			reverse_iterator & operator++() {
				if (node->left) {
					node = up(node->left);
					return *this;
				}
				else if (node->parent && node->parent->right == node) {
					node = node->parent;
					return *this;
				}
				TreeNode *temp = node;
				while (temp->parent->left == temp)
					if ((temp = temp->parent) == nullptr) {
						node = temp->left;
						return *this;
					}
				node = temp->parent;
				return *this;
			};

			reverse_iterator operator++(int) {
				reverse_iterator temp(node);
				operator++();
				return temp;

			};
			reverse_iterator & operator--() {
				if (node->right) {
					node = deep(node->right);
					return *this;
				}
				else if (node->parent && node->parent->left == node) {
					node = node->parent;
					return *this;
				}
				else if (node->parent->right == node)
					node = node->parent;
				TreeNode *temp = node;
				while (temp->parent->right == temp) {
					temp = temp->parent;
					if (!temp) {
						node = node->right;
						return *this;
					}
				}
				node = temp->parent;
				return *this;
			};

			reverse_iterator operator--(int) {
				reverse_iterator temp(node);
				operator--();
				return temp;
			};
			bool operator==(const reverse_iterator &iter) const { return node == iter.node; };
			bool operator!=(const reverse_iterator &iter) const { return node != iter.node; };

			bool operator==(const const_reverse_iterator &iter) const { return node == iter.getNode(); };
			bool operator!=(const const_reverse_iterator &iter) const { return node != iter.getNode(); };

			const value_type & operator*() const { return *(node->data); };
			const value_type * operator->() const {
				return node->data; }

			TreeNode *getNode() const { return node; }
		private:
			TreeNode *deep(TreeNode *node) {
				if (node->left)
					return deep(node->left);
				return node;
			}

			TreeNode *up(TreeNode *node) {
				if (node->right)
					return up(node->right);
				return node;
			}
		};

		class const_reverse_iterator : public std::reverse_iterator<iterator> {
		private:
			TreeNode * node;
		public:
			const_reverse_iterator(TreeNode* _node = nullptr): node(_node) {};
			~const_reverse_iterator() {};

			const_reverse_iterator & operator=(const const_reverse_iterator &iter) {
				this->node = iter.node;
				return *this;
			};

			const_reverse_iterator & operator=(const reverse_iterator &iter) {
				this->node = iter.getNode();
				return *this;
			};

			const_reverse_iterator(const const_reverse_iterator &iter) { *this = iter; };
			const_reverse_iterator(const reverse_iterator &iter) { *this = iter; };

			const_reverse_iterator & operator++() {
				if (node->left) {
					node = up(node->left);
					return *this;
				}
				else if (node->parent && node->parent->right == node) {
					node = node->parent;
					return *this;
				}
				TreeNode *temp = node;
				while (temp->parent->left == temp)
					if ((temp = temp->parent) == nullptr) {
						node = temp->left;
						return *this;
					}
				node = temp->parent;
				return *this;
			};

			const_reverse_iterator operator++(int) {
				const_reverse_iterator tmp(node);
				operator++();
				return tmp;
			};

			const_reverse_iterator & operator--() {
				if (node->right) {
					node = deep(node->right);
					return *this;
				}
				else if (node->parent && node->parent->left == node) {
					node = node->parent;
					return *this;
				}
				else if (node->parent->right == node)
					node = node->parent;
				TreeNode *temp = node;
				while (temp->parent->right == temp) {
					temp = temp->parent;
					if (!temp) {
						node = node->right;
						return *this;
					}
				}
				node = temp->parent;
				return *this;
			};

			const_reverse_iterator operator--(int) {
				const_reverse_iterator tmp(node);
				operator--();
				return tmp;
			};

			bool operator==(const const_reverse_iterator &iter) const { return node == iter.node; };
			bool operator!=(const const_reverse_iterator &iter) const { return node != iter.node; };

			bool operator==(const reverse_iterator &iter) const { return node == iter.getNode(); };
			bool operator!=(const reverse_iterator &iter) const { return node != iter.getNode(); };

			const_reference operator*() const { return *(this->node->data); }
			const_pointer operator->() const { return this->it->data; }

			TreeNode *getNode() const { return node; }
		private:
			TreeNode *deep(TreeNode *node) {
				if (node->left)
					return deep(node->left);
				return node;
			}

			TreeNode *up(TreeNode *node) {
				if (node->right)
					return up(node->right);
				return node;
			}
		};



		// Capacity:
		bool		empty() const { return _size == 0; }
		size_type 	size() const { return _size; }
		size_type	max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }


		// Element access:
		mapped_type& operator[] (const key_type& k) {return (*((this->insert(make_pair(k,mapped_type()))).first)).second; }

	};

} // end ft




#endif //FT_CONTAINER_MAP_HPP
