#include "DrawShipConstructor.h"


namespace sbat
{

	sbat::DrawShipConstructor::DrawShipConstructor()
		:
		sbat::DrawShip(),
		m_default_color(sf::Color::White),
		m_wrong_color(sf::Color::Red),
		m_selected_color(sf::Color::Green),
		m_cur_state(DrawShipConstructorState::DEFAULT)
	{

	}

	void sbat::DrawShipConstructor::set_colors(const sf::Color& color_default, const sf::Color& color_wrong , const sf::Color& color_selected)
	{
		m_default_color = color_default;
		m_wrong_color = color_wrong;
		m_selected_color = color_selected;
	}

	void sbat::DrawShipConstructor::set_wrong_color(DrawShipConstructorState state)
	{
		m_cur_state = state;
		if (m_cur_state == DrawShipConstructorState::WRONG)
			m_sprite.setColor(m_wrong_color);
		else if(m_cur_state == DrawShipConstructorState::DEFAULT)
			m_sprite.setColor(m_default_color);
		else if (m_cur_state == DrawShipConstructorState::SELECTED)
			m_sprite.setColor(m_selected_color);
	}

	DrawShipConstructorState sbat::DrawShipConstructor::is_wrong()
	{
		return m_cur_state;
	}

}