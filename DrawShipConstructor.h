#ifndef SBAT_DRAWSHIPCONSTUCTOR_H
#define SBAT_DRAWSHIPCONSTUCTOR_H

#include "DrawShip.h"

namespace sbat
{

	enum class DrawShipConstructorState : short
	{
		DEFAULT,
		WRONG,
		SELECTED
	};


	class DrawShipConstructor
		:
		public sbat::DrawShip
	{

	public :

		DrawShipConstructor() ;
		virtual ~DrawShipConstructor() = default;

		void set_colors(const sf::Color& color_default, const sf::Color& color_wrong, const sf::Color& color_selected);
		void set_wrong_color(DrawShipConstructorState state);// default 0 ;

		DrawShipConstructorState is_wrong();

	protected:

		sf::Color  m_default_color, m_wrong_color , m_selected_color;
		DrawShipConstructorState m_cur_state;

	};




}


#endif // !SBAT_DRAWSHIPCONSTUCTOR_H

