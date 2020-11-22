#include "debug.hpp"

namespace demonblade {

	debug::debug( void ) {
		#ifdef __WIN32__
			console_handle = GetStdHandle( STD_OUTPUT_HANDLE );
		#endif // __WIN32__
	}

	void debug::message( std::string st ) {
		#ifdef __WIN32__
			SetConsoleTextAttribute( console_handle, DBG_WHITE_COLOR );
			std::cout << st;
		#endif // __WIN32__

		#ifdef __linux__
			std::cout << DBG_WHITE_COLOR << st;
		#endif // __linux__
	}

	void debug::warn( std::string st ) {
		#ifdef __WIN32__
			SetConsoleTextAttribute( console_handle, DBG_YELLOW_COLOR );
			std::cout << st;
		#endif // __WIN32__

		#ifdef __linux__
			std::cout << DBG_YELLOW_COLOR << st;
		#endif // __linux__
	}

	void debug::error( std::string st ) {
		#ifdef __WIN32__
			SetConsoleTextAttribute( console_handle, DBG_RED_COLOR );
			std::cout << st;
		#endif // __WIN32__

		#ifdef __linux__
			std::cout << DBG_RED_COLOR << st;
		#endif // __linux__
	}

} //namespace demonblade
