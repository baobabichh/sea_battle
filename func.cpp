#include "func.h"



namespace sbat
{

	void apply_style_text(sf::Text& text, const sbat::TextStyle& style)
	{
		text.setCharacterSize(style.character_size);
		text.setFillColor(style.fill_color);
		text.setOutlineColor(style.outline_color);
		text.setOutlineThickness(style.outline_thinkness);
		text.setStyle(style.style);
	}

	sf::RectangleShape make_rect(sf::FloatRect rect)
	{
		sf::RectangleShape s;
		s.setPosition(rect.left, rect.top);
		s.setSize(sf::Vector2f(rect.width, rect.height));
		s.setFillColor(sf::Color(0, 100, 0, 100));
		return s;
	}


}