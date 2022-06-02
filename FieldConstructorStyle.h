#ifndef SBAT_FIELDCONSTRUCTORSTYLE_H
#define SBAT_FIELDCONSTRUCTORSTYLE_H

#include <SFML/Graphics.hpp>

namespace sbat
{
	struct FieldConstructorStyle
	{
		int padding, marging, line_width;
		sf::Color line_color, background_color;

		FieldConstructorStyle()
			:
			padding(0),
			marging(0),
			line_width(0),
			line_color(0),
			background_color(0)
		{

		}

		FieldConstructorStyle(int a_padding, int a_margin, int a_line_width, sf::Color a_line_color, sf::Color a_background_color)
			:
			padding(a_padding),
			marging(a_margin),
			line_width(a_line_width),
			line_color(a_line_color),
			background_color(a_background_color)
		{

		}

	};

}

#endif // !SBAT_FIELDCONSTRUCTORSTYLE_H

