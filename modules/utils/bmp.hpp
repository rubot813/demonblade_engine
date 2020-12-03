#ifndef BMP_HPP_INCLUDED
#define BMP_HPP_INCLUDED

#include <vector>
#include <fstream>

#include "../common/global.hpp"
#include "bmp.hpp"

/*
	Класс позволяет читать, редактировать и сохранять BMP файлы
*/

namespace demonblade {
	class bmp {

		public:

#pragma pack(push, 1)
			// Структура заголовка bmp файла
			struct bmp_header_s {
				uint16_t file_type;		// Тип файла, всегда равен 0x4D42
				uint32_t file_size;		// Размер файла в байтах
				uint32_t _reserved;		// Резерв 32 бита
				uint32_t offset_data; 	// Смещение начала массива пикселей
				bmp_header_s( void ) {
					#ifdef __linux
					memset( this, 0, sizeof( bmp_header_s ) );
					#endif
					file_type = 0x4D42;
				}
			};

			struct bmp_info_header_s {
				uint32_t	size;				// Размер заголовка ( bmp_info_header_s )  в байтах
				int32_t		width;				// Ширина массива в пикселях
				int32_t		height;				// Длина массива в пикселях
				// Если > 0, значит начало с нижнего левого угла
				// Если < 0, значит начало с верхнего левого угла

				uint16_t	planes;				// Количество плоскостей битовых полей. Всегда = 1
				uint16_t	bpp;				// Количество бит на пиксель
				uint16_t	compression;		// Степень сжатия изображения. 0 для 24bpp, 3 для 32bpp
				uint32_t	image_size;

				int32_t		x_pix_per_meter;
				int32_t		y_pix_per_meter;
				uint32_t	used_color_ind;		// Количество индексов цветов из палитры
				uint32_t	color_req;			// Количество цветов используемых в изображении. 0 - вся палитра
				bmp_info_header_s( void ) {
					#ifdef __linux
					memset( this, 0, sizeof( bmp_info_header_s ) );
					#endif
					planes = 1;
				}
			};

			struct bmp_color_header_s {
				uint32_t red_mask;			// Цветовые маски
				uint32_t green_mask;
				uint32_t blue_mask;
				uint32_t alpha_mask;
				uint32_t color_space_type;	// Тип цветового пространства
				uint32_t _reserved[ 16 ];

				bmp_color_header_s( void ) {
					#ifdef __linux
					memset( this, 0, sizeof( bmp_color_header_s ) );
					#endif
					red_mask			= 0x00ff0000;
					green_mask			= 0x0000ff00;
					blue_mask			= 0x000000ff;
					alpha_mask			= 0xff000000;
					color_space_type	= 0x73524742;	// spaceRGB
				}

				// Метод возвращает 1, если данные хранятся в формате BGRA и цветовое пространство sRGB
				// Иначе возвращает 0
				bool is_correct_type( void );

			};

#pragma pack(pop)

			bmp( void );
			bmp( std::string file_name );

			~bmp( void );

			// Низкоуровневые методы

			// Чтение битмапа из файла
			bool read( std::string file_name );

			// Запись битмапа в файл
			bool write( std::string file_name );

			// Создание в памяти битмапа указаных размеров, с флагом альфа - канала
			bool create( uint16_t width, uint16_t height, bool alpha = 1 );

			// Проверка, имеет ли экземпляр класса массив пикселей
			// Может быть использован для проверки чтения после вызова из конструктора
			bool is_empty( void );

			// Метод получения указателя на массив пикселей
			void *get_data_ptr( void );

			// Методы получения размеров изображения
			int32_t get_width( void );
			int32_t get_height( void );

		private:

			// Заголовки
			bmp_header_s		_header;
			bmp_info_header_s	_info_header;
			bmp_color_header_s	_color_header;

			// Контейнер загруженного массива пикселей
			std::vector< uint8_t > _data;
	};	// class bmp

}	// namespace demonblade

#endif // BMP_HPP_INCLUDED
