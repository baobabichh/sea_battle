#include "GameStyles.h"



namespace sbat
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//STATIC STYLES

	help_sbat::padding_styles  GameStyles::PaddingStyles;
	help_sbat::text_styles  GameStyles::TextStyles;
	help_sbat::draw_field_styles  GameStyles::DrawFieldStyles;

	GameStyles::GameStyles()
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//PADDING STYLES

		PaddingStyles.Default = Padding(0, 20, 0, 20);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//TEXT STYLES

		TextStyles.Default = TextStyle(24, 0, sf::Text::Bold, sf::Color::Black, sf::Color::White);
		TextStyles.DefaultText = TextStyle(24, 1, sf::Text::Bold, sf::Color::Black, sf::Color::White);
		TextStyles.YouWin = TextStyle(100, 2, sf::Text::Bold, sf::Color::Black, sf::Color::Red);
		

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//FIELD STYLEs

		DrawFieldStyles.Default = sbat::DrawFieldStyle(3, sf::Color::Black, sf::Color(53, 128, 219,200) , sf::Color::White, TextStyles.Default, PaddingStyles.Default);
		DrawFieldStyles.Attacking = sbat::DrawFieldStyle(3, sf::Color::Black, sf::Color(53, 128, 219, 200), sf::Color::Green, TextStyles.Default, PaddingStyles.Default);
		DrawFieldStyles.UnderAttack = sbat::DrawFieldStyle(3, sf::Color::Black, sf::Color(53, 128, 219, 200), sf::Color::Red, TextStyles.Default, PaddingStyles.Default);

	}

	GameStyles::~GameStyles()
	{
	}


}