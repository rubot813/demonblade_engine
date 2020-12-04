#include "image.hpp"

namespace demonblade {
	image::image( void ) {
		#ifdef __linux
		_data.clear( );
		#endif // __linux
	}

	image::~image( void ) {
		// nope
	}

	void* image::get_data_ptr( void ) {
		return _data.data( );
	}

	image::img_sized_format_e image::get_pixel_format( void ) {
		return _format;
	}

	image::img_base_format_e image::get_base_pixel_format( void ) {
		return get_base_pixel_format( _format );
	}

	image::img_base_format_e image::get_base_pixel_format( image::img_sized_format_e sized ) {
		img_base_format_e base;
		if ( sized == SIZED_BGR || sized == SIZED_RGB )
			base = BASE_RGB;

		if ( sized == SIZED_BGRA || sized == SIZED_RGBA )
			base = BASE_RGBA;
		return base;
	}

	uint16_t image::get_width( void ) {
		return _width;
	}

	uint16_t image::get_height( void ) {
		return _height;
	}

	uint8_t image::get_bpp( void ) {
		uint8_t bpp = 0;

		if ( _format == SIZED_RGB || _format == SIZED_BGR )
			bpp = 24;

		if ( _format == SIZED_RGBA || _format == SIZED_BGRA )
			bpp = 32;

		return bpp;
	}

	uint32_t image::get_data_size( void ) {
		return _data.size( );
	}

	uint32_t image::get_pixel_count( void ) {
		uint8_t component_count = get_bpp( ) / 8;
		uint32_t size;

		if ( component_count != 0 )
			size = _data.size( ) / component_count;
		else
			size = 0;

		return size;
	}

	bool image::convert_format( void ) {
		// ѕолучение количества байт на пиксель
		uint8_t component_count = get_bpp( ) / 8;
		bool _ok = 0;
		if ( component_count ) {
			for ( uint32_t i = 0; i < _data.size( ); i += component_count ) {
				// R <-> B
				_data[ i ] ^= _data[ i + 2 ];
				_data[ i + 2 ] ^= _data[ i ];
				_data[ i ] ^= _data[ i + 2 ];
			}
			_ok = 1;
		} else {
			#ifdef DB_DEBUG
				debug::get_instance( )->error( std::string( __FUNCTION__ ) + " -> incorrect component count\n" );
			#endif // DB_DEBUG
			_ok = 0;
		}
		return _ok;
	}
}	// namespace demonblade
