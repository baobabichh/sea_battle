#ifndef SBAT_DRAWFIELDSTYLE_H
#define SBAT_DRAWFIELDSTYLE_H

#include "TextStyle.h"
#include "Padding.h"


namespace sbat
{

	struct DrawFieldStyle
	{
		DrawFieldStyle()
			:
			padding(),
			line_width(0),
			line_color(0),
			background_color(0),
			text_style()
		{

		}
		

		DrawFieldStyle( int a_line_width, sf::Color a_line_color, sf::Color a_background_color ,sf::Color outline_color, sbat::TextStyle a_text_style ,sbat::Padding a_padding )
			:
			padding(a_padding),
			line_width(a_line_width),
			line_color(a_line_color),
			background_color(a_background_color),
			text_style(a_text_style),
			outline_color(outline_color)
		{

		}

		sbat::Padding padding;
		int line_width ;
		sf::Color line_color, background_color , outline_color;
		sbat::TextStyle text_style;
	};

}


#endif // !SBAT_DRAWFIELDSTYLE_H

