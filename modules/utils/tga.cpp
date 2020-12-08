#include "tga.hpp"

namespace demonblade {

	tga::tga( void ) {
		#ifdef __linux
		_data.clear( );
		#endif	// ifdef __linux
	}
	tga::tga( std::string file_name ) {
		load_from_file( file_name );
	}

	tga::~tga( void ) {
		// nope
	}

	bool tga::load_from_file( std::string file_name ) {
		db_dbg_msg( "currently unsupported\n" );
		return 0;
	}

	bool tga::save_to_file( std::string file_name ) {
		db_dbg_msg( "currently unsupported\n" );
		return 0;
	}

}	// namespace demonblade

