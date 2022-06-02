#ifndef SBAT_TEXTSTYLE_H
#define SBAT_TEXTSTYLE_H

#include <SFML/Graphics.hpp>

namespace sbat
{
	struct TextStyle
	{
		TextStyle()
			:
			character_size(0),
			fill_color(0),
			style(0),
			outline_color(0),
			outline_thinkness(0)
		{

		}

		TextStyle(int a_character_size, int a_outline_thinkness, sf::Uint32 a_style  , sf::Color a_outline_color, sf::Color a_fill_color)
			:
			character_size(a_character_size),
			fill_color(a_fill_color),
			style(a_style),
			outline_color(a_outline_color),
			outline_thinkness(a_outline_thinkness)
		{

		}
		
		

		int character_size , outline_thinkness;
		sf::Color fill_color , outline_color;
		sf::Uint32 style;
	};
}




#endif // !SBAT_TEXTSTYLE_H



