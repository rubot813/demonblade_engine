#include "debug.hpp"

namespace demonblade {

	#ifdef __WIN32__
	debug::debug( void ) {
		console_handle = GetStdHandle( STD_OUTPUT_HANDLE );
	}

	void debug::message( std::string st ) {
		SetConsoleTextAttribute( console_handle, DBG_WHITE_COLOR );
		std::cout << st;
	}

	void debug::warn( std::string st ) {
		SetConsoleTextAttribute( console_handle, DBG_YELLOW_COLOR );
		std::cout << st;
	}

	void debug::error( std::string st ) {
		SetConsoleTextAttribute( console_handle, DBG_RED_COLOR );
		std::cout << st;
	}

	#endif // __WIN32__
	#ifdef __linux__

	debug::debug( void ) {
		// np
	}

	void debug::message( std::string st ) {
		std::cout << DBG_WHITE_COLOR << st;
	}

	void debug::warn( std::string st ) {
		std::cout << DBG_YELLOW_COLOR << st;
	}

	void debug::error( std::string st ) {
		std::cout << DBG_RED_COLOR << st;
	}
	#endif // __linux__

} //namespace demonblade
