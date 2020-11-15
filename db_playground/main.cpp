#include "playground.h"

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
