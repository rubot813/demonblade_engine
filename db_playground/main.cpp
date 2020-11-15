#include "playground.h"

/*
	Как компилировать db_playground:
	Подключить SFML как обычно
	Пути компилятора:
	../modules
	../external

	Пути линкера:
	../build
	../external/glew/lib/gcc

	Параметры линкера:
	Весь sfml
	demonblade
	glew32
	opengl32
*/


// Entry point for playground only
int main( void ) {
	// Suppress unused var warn
	#ifdef __GNUC__
	__attribute__((unused)) playground *pg;
	#else
	playground *pg;
	#endif
	pg = new playground( );
	return 0;
}
