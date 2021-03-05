//
// Created by casubmar on 23.02.2021.
//

#ifndef FT_CONTAINER_FT_HPP
#define FT_CONTAINER_FT_HPP

namespace ft {
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };
}

#endif //FT_CONTAINER_FT_HPP
