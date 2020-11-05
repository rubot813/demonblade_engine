#ifndef CORE_HPP_INCLUDED
#define CORE_HPP_INCLUDED

#include <cstdint>

// todo: light

namespace demonblade {

class core {
public:
	static core* get_instance( void ) {
		static core core_instance;	// lazy :<
		return &core_instance;
	}

	// Перечисление функций ядра
	enum func_e {
		TEXTURE_2D	= 0x0DE1,	// Текстуры 2D
		LIGHT		= 0x0B50,	// Свет
		ALPHA_TEST	= 0x0BC0,	// Альфа тест ( спрайты, текстуры )
		FOG			= 0x0B60,	// Туман
		CULL		= 0x0B44,	// Отсечение невидимых граней
		DITHERING	= 0x0BD0	// Смешивание цветов при отрисовке
	};

	// Функция инициализации ядра OpenGL
	// Принимает размеры порта вывода ( окна ) для отображения
	bool init( uint16_t window_width, uint16_t window_height );

	// Функция изменения размеров окна
	void reshape( uint16_t window_width, uint16_t window_height );

	// Функция очистки матрицы MODELVIEW и буферов OpenGL
	void clear( void );

	// Функции включения / выключения возможностей OpenGL
	void enable( func_e type );
	void disable( func_e type );
	void select( func_e type, bool state );

private:
	// Запрет конструктора, деструктора, операции копирования
	core( void ) { };
	~core( void ) { };
	core( const core &_ex ) = delete;
	core& operator=( const core& ) = delete;

protected:
	// no childs allowed
};	// core

namespace fog {
// Установка параметров тумана
// Начало, конец, плотность
void set( float start, float end, float density );

}	// namespace fog

namespace light {
	// todo
}	// namespace light

} // namespace demonblade

#endif // CORE_HPP_INCLUDED
