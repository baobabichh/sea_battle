#ifndef SBAT_FUNC_H
#define SBAT_FUNC_H

#include "TextStyle.h"

namespace sbat
{

	struct Vector2Icompare
	{
		bool operator()(const sf::Vector2i& left, const sf::Vector2i& right)const
		{
			if (left.x < right.x)
				return 1;
			if (left.y < right.y && left.x == right.x)
				return 1;
			return 0;
		}
	};

	struct Vector2Ihash
	{
		size_t operator()(const sf::Vector2i& right)const
		{
			return right.x * 1000 + right.y;
		}
	};


	void apply_style_text(sf::Text& text, const sbat::TextStyle& style);
	
	sf::RectangleShape make_rect(sf::FloatRect rect);



}



#endif // SBAT_FUNC_H

