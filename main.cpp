#include <iostream>
#include <list>
#include <vector>
#include "list.hpp"
#include "vector.hpp"

template <class iterator>
void print_list(iterator first, iterator last) { // todo УДААЛИТЬ
	while (first != last) {
		std::cout << *first << " ";
		++first;
	}
	std::cout << std::endl;
}

template <class T>
void my_vector_info(ft::vector<T> my_vector) {
	std::cout << "------MY_LIST------\n";
	my_vector.print();
	std::cout << "\nmy_vector size - " << my_vector.size() << std::endl;
	std::cout << "-------------------\n\n\n";
}

template <class T>
void std_list_info(std::list<T> std_list) {
	std::cout << "------STD_LIST------\n";
	print_list(std_list.begin(), std_list.end());
	std::cout << "std_list size - " << std_list.size() << std::endl;
	std::cout << "-------------------\n\n\n";
}

int main() {
	ft::vector<int> my_vector;
	for (int i = 0; i < 10; ++i) {
		my_vector.push_back(i);
	}
	ft::vector<int>my_vector_two(my_vector);
	my_vector_info(my_vector_two);
	ft::vector<int>::iterator first = my_vector_two.begin();
	for (int i = 0; i < 5; ++i) {
		++first;
	}
	std::cout << "ERASE\n";
	my_vector_two.erase(first, my_vector_two.end());

	my_vector_info(my_vector_two);



	return 0;
}
