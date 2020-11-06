#ifndef GLOBAL_HPP_INCLUDED
#define GLOBAL_HPP_INCLUDED

#define DB_VERSION 0.95

#ifndef M_PI
	#define M_PI	3.14159265358979323846
#endif

#ifdef GLM_FORCE_RADIANS
	#pragma message "WARN: Use radians on fov param \"ogl->init\""
#endif // GLM_FORCE_RADIANS

#endif // GLOBAL_HPP_INCLUDED
