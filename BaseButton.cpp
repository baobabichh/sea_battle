#include "BaseButton.h"


namespace sbat
{

	bool BaseButton::pressed(sf::RenderWindow& window, sf::Mouse::Button button )const
	{

		if (sf::Mouse::isButtonPressed(button) && this->hovered(window))
		{
			return 1;
		}
		return 0;
	}
	bool BaseButton::clicked(sf::RenderWindow& window, const sf::Event& event, sf::Mouse::Button button )const
	{
		if (event.type == event.MouseButtonReleased && this->hovered(window))
		{
			if (event.mouseButton.button == button)
			{
				return 1;
			}
		}
		return 0;
	}
	bool BaseButton::hovered(sf::RenderWindow& window) const
	{
		if (get_Transfrom().transformRect(m_hit_box).contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
		{
			return 1;
		}
		return 0;
	}

}