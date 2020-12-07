#ifndef DEBUG_HPP_INCLUDED
#define DEBUG_HPP_INCLUDED

#include "global.hpp"

#include <iostream>
#include <cstring>

#ifdef __WIN32__
	#include "windows.h"
	#define DBG_WHITE_COLOR		0x0F
	#define DBG_YELLOW_COLOR	0x0E
	#define DBG_RED_COLOR		0x0C
#endif // __WIN32__

#ifdef __linux
	#define DBG_WHITE_COLOR		"\e[0m"
	#define DBG_YELLOW_COLOR	"\e[0;33m"
	#define DBG_RED_COLOR		"\e[0;31m"
#endif
/*
    ����� ��� ������ ���������� ���������
*/

namespace demonblade {

	class debug {
		public:

			// ���� ���������� ���������
			enum dbg_type_e {
				dbg_msg,	// ���������
				dbg_warn,	// ��������������
				dbg_error	// ������
			};

			static debug* get_instance( void ) {
				static debug debug_instance;
				return &debug_instance;
			}

			// ����� ����������� ���������
			void print( dbg_type_e type, std::string st );

		private:
			// ������ ������������, �����������, �������� �����������
			debug( void );
			~debug( void ) { };
			debug( const debug &_ex ) = delete;
			debug& operator=( const debug& ) = delete;

		protected:
			#ifdef __WIN32__
			HANDLE console_handle;
			#endif // __WIN32__

	};	// debug class


} // namespace demonblade

#endif // DEBUG_HPP_INCLUDED
