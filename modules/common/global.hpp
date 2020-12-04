#ifndef GLOBAL_HPP_INCLUDED
#define GLOBAL_HPP_INCLUDED

#define DB_VERSION 0.978

// Закомментировать строчку ниже для отключения вывода отладочных сообщений
#define DB_DEBUG
#ifdef DB_DEBUG
	#include "debug.hpp"
#endif	// DB_DEBUG

#endif // GLOBAL_HPP_INCLUDED
