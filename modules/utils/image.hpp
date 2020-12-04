#ifndef IMAGE_HPP_INCLUDED
#define IMAGE_HPP_INCLUDED

#include <vector>
#include <cstring>

#include "../common/global.hpp"
#include "../core/ogl.hpp"

/*
	image - базовый класс для изображений. Описывает методы для загрузки изображений из файлов в RAM,
	записи изображений на жесткий диск. Все классы - наследники описывают алгоритмы работы с конкретными
	форматами файлов. Класс поддерживает работу с изображениями без альфа канала ( без прозрачности ) и
	с изображениями с альфа каналом ( с прозрачностью )

	Ограничения изображений:
	Только форматы RGB / BGR / RGBA / BGRA ( 24 / 32 бита на пиксель )
	Цветовое пространство sRGB
	Для формата TGA поддерживается сжатие ( кодирование RLE )
	Начало изображения - левый верхний угол
*/

namespace demonblade {

	class image {

		public:

			// Empty by default
			image( void );
			~image( void );

			// Перечисление базовых форматов упаковки пикселей
			enum img_base_format_e {
				BASE_RGB	= 0x1907,	// R G B
				BASE_RGBA	= 0x1908	// R G B A
			};

			// Перечисление расширенных форматов упаковки пикселей
			enum img_sized_format_e {
				SIZED_RGB	= 0x8051,	// RGB, 8 бит / пиксель
				SIZED_RGBA	= 0x8058,	// RGBA, 8 бит / пиксель
				SIZED_BGR	= 0x80E0,	// BGR,	8 бит / пиксель
				SIZED_BGRA 	= 0x80E1	// BGRA, 8 бит / пиксель
			};

			// Метод загрузки изображения из файла
			virtual bool load_from_file( std::string file_name ) = 0;

			// Метод записи изображения в файл
			virtual bool save_to_file( std::string file_name ) = 0;

			// Метод получения указателя на массив пикселей
			void* get_data_ptr( void );

			// Метод получения формата упаковки пикселей ( расширенного )
			img_sized_format_e get_pixel_format( void );

			// Метод получения формата упаковки пикселей ( базового )
			img_base_format_e get_base_pixel_format( void );

			// Метод получения расширенного формата упаковки пикселей из базового
			static img_base_format_e get_base_pixel_format( img_sized_format_e sized );

			// Методы получения размеров изображения
			uint16_t get_width( void );		// Ширина
			uint16_t get_height( void );	// Высота

			// Метод возвращает количество бит на пиксель ( bpp )
			// Вернет 0 в случае ошибки
			uint8_t get_bpp( void );

			// Метод возвращает размер массива данных пикселей
			// Может быть использован для проверки чтения после вызова
			// загрузки изображения из конструктора
			uint32_t get_data_size( void );

			// Метод возвращает количество пикселей в изображении
			// Вернет 0 в случае ошибки
			uint32_t get_pixel_count( void );

			// Метод конвертирования расширенного формата упаковки пикселей изображения
			// Исходный формат -> конвертированный формат
			// RGB -> BGR
			// RGBA -> BGRA
			// BGR -> RGB
			// BGRA -> RGBA
			// Вернет 1 в случае успеха
			// Вернет 0 в случае ошибки
			bool convert_format( void );

		private:

			// Массив пикселей
			std::vector< uint8_t >	_data;

			// Размеры изображения в пикселях
			uint32_t	_width;
			uint32_t	_height;

			// Формат изображения
			img_sized_format_e	_format;
	};

}	// namespace demonblade

#endif // IMAGE_HPP_INCLUDED
