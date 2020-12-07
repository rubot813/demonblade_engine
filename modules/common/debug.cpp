#include "debug.hpp"

namespace demonblade {

	#ifdef __WIN32__
	debug::debug( void ) {
		console_handle = GetStdHandle( STD_OUTPUT_HANDLE );
	}

	void debug::print( dbg_type_e type, std::string st ) {
		uint16_t color;
		switch ( type ) {
			case dbg_msg: {
				color = DBG_WHITE_COLOR;
				break;
			}
			case dbg_warn: {
				color = DBG_YELLOW_COLOR;;
				break;
			}
			case dbg_error: {
				color = DBG_RED_COLOR;
				break;
			}
			default:
				color = DBG_WHITE_COLOR;
		}	// switch type

		SetConsoleTextAttribute( console_handle, color );
		std::cout << st;
	}

	#endif // __WIN32__
	#ifdef __linux__

	debug::debug( void ) {
		// np
	}

	void debug::print( dbg_type_e type, std::string st ) {
		std::string color;
		switch ( type ) {
			case dbg_msg: {
				color = DBG_WHITE_COLOR;
				break;
			}
			case dbg_warn: {
				color = DBG_YELLOW_COLOR;;
				break;
			}
			case dbg_error: {
				color = DBG_RED_COLOR;
				break;
			}
			default:
				color = DBG_WHITE_COLOR;
		}	// switch type
		std::cout << color << st;
	}

	#endif // __linux__

} //namespace demonblade
