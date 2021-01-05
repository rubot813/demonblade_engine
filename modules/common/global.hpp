#ifndef GLOBAL_HPP_INCLUDED
#define GLOBAL_HPP_INCLUDED

#define DB_VERSION 0.982

// Закомментировать строчку ниже для отключения вывода отладочных сообщений
#define DB_DEBUG
#ifdef DB_DEBUG
	#include "debug.hpp"
	#define db_dbg_msg(msg) debug::get_instance( )->print( debug::dbg_msg, std::string( __FUNCTION__ ) + "[MSG]: " + msg )
	#define db_dbg_warn(warn) debug::get_instance( )->print( debug::dbg_warn, std::string( __FUNCTION__ ) + "[WARN]: " + warn )
	#define db_dbg_error(error) debug::get_instance( )->print( debug::dbg_error, std::string( __FUNCTION__ ) + "[ERROR]: " + error )
#else
	#define db_dbg_msg(msg) ;
	#define db_dbg_warn(warn) ;
	#define db_dbg_error(error) ;
#endif	// DB_DEBUG

#endif // GLOBAL_HPP_INCLUDED
