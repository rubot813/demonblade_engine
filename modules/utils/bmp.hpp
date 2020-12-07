#ifndef BMP_HPP_INCLUDED
#define BMP_HPP_INCLUDED

#include <fstream>

#include "image.hpp"

/*
	Класс позволяет работать с bmp и dib файлами
	Класс - потомок image
*/

namespace demonblade {
	class bmp : public image {

		public:

#pragma pack(push, 1)
			// Структура заголовка файла
			struct bmp_file_header_s {
				uint16_t type;			// Тип файла, всегда равен 0x4D42
				uint32_t size;			// Размер файла в байтах
				uint32_t _reserved;		// Резерв 32 бита
				uint32_t offset_data; 	// Смещение начала массива пикселей

				bmp_file_header_s( void ) {
					memset( this, 0, sizeof( bmp_file_header_s ) );
					type = 0x4D42;	// 'B' + 'M'
				}
			};

			// Структура заголовка информации о файле
			struct bmp_info_header_s {
				uint32_t	size;				// Размер заголовка ( bmp_info_header_s )  в байтах
				int32_t		width;				// Ширина массива в пикселях
				int32_t		height;				// Длина массива в пикселях
				// Если > 0, значит начало с нижнего левого угла
				// Если < 0, значит начало с верхнего левого угла

				uint16_t	planes;				// Количество плоскостей битовых полей. Всегда = 1
				uint16_t	bpp;				// Количество бит на пиксель
				uint32_t	compression;		// Степень сжатия изображения. 0 для 24bpp, 3 для 32bpp
				uint32_t	image_size;

				int32_t		x_pix_per_meter;
				int32_t		y_pix_per_meter;
				uint32_t	used_color_ind;		// Количество индексов цветов из палитры
				uint32_t	color_req;			// Количество цветов используемых в изображении. 0 - вся палитра

				// Перечисление версий заголовка bmp_info_header
				enum version_s {
					VERSION_CORE	= 0,
					VERSION_3		= 3,
					VERSION_4		= 4,
					VERSION_5		= 5,
				};

				bmp_info_header_s( void ) {
					memset( this, 0, sizeof( bmp_info_header_s ) );
					planes = 1;
				}

				// Получение версии заголовка bmp_info_header
				// Версия заголовка ( и допустимые для чтения / записи поля ) определяются по размеру структуры ( поля size )
				version_s get_version( void );
			};

			// Структура заголовка информации о маске цвета
			struct bmp_color_header_s {
				uint32_t red_mask;			// Цветовые маски
				uint32_t green_mask;
				uint32_t blue_mask;
				uint32_t alpha_mask;
				uint32_t color_space_type;	// Тип цветового пространства
				uint32_t _reserved[ 16 ];

				bmp_color_header_s( void ) {
					memset( this, 0, sizeof( bmp_color_header_s ) );
					// По умолчанию формат упаковки BGRA. sRGB
					red_mask			= 0x00ff0000;
					green_mask			= 0x0000ff00;
					blue_mask			= 0x000000ff;
					alpha_mask			= 0xff000000;
					color_space_type	= 0x73524742;	// spaceRGB
				}



				// Функции возвращают 1, если цветовая маска соответствует названию
				bool is_bgr( void );	// BGR
				bool is_bgra( void );	// BGRA
				bool is_rgb( void );	// RGB
				bool is_rgba( void );	// RGBA

				// Функция возвращает 1, если цветовое пространство маски цвета sRGB
				bool is_srgb( void );

			};

#pragma pack(pop)

			// default
			bmp( void );
			bmp( std::string file_name );
			~bmp( void );

			// Метод загрузки изображения из файла
			bool load_from_file( std::string file_name );

			// Метод записи изображения в файл
			bool save_to_file( std::string file_name );

		private:

			// Метод читает заголовки открытого bmp/dib файла
			// Возвращает 1 если заголовки заполнены корректно и формат пикселей поддерживается
			bool _read_header( std::ifstream *file );

			// Метод читает данные пикселей открытого bmp/dib файла
			// Возвращает 1 если успешно
			bool _read_pixel_data( std::ifstream *file );

			// Заголовки bmp/dib формата
			bmp_file_header_s	_file_header;
			bmp_info_header_s	_info_header;
			bmp_color_header_s	_color_header;

	};	// class bmp

}	// namespace demonblade

#endif // BMP_HPP_INCLUDED
