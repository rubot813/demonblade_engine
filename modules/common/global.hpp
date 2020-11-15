#ifndef GLOBAL_HPP_INCLUDED
#define GLOBAL_HPP_INCLUDED

#define MACRO_TO_STR(x) #x

#define DB_VERSION 0.97

#define DB_DEBUG
#ifdef DB_DEBUG
	#include <iostream>	// std::cout
#endif // DB_DEBUG

#endif // GLOBAL_HPP_INCLUDED
