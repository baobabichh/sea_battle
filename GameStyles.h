#ifndef SBAT_GAMESTYLES_H
#define SBAT_GAMESTYLES_H

#include "DrawFieldStyle.h"
#include "Padding.h"
#include "TextStyle.h"


namespace sbat
{

	namespace help_sbat
	{
		struct text_styles
		{
			TextStyle Default;
			TextStyle DefaultText;
			TextStyle YouWin;
		};
		struct padding_styles
		{
			Padding Default;
		};
		struct draw_field_styles
		{
			DrawFieldStyle Default;
			DrawFieldStyle UnderAttack;
			DrawFieldStyle Attacking;
		};
	}

	class GameStyles
	{

	public:
		//CONSTRUCTOR

		GameStyles();

		//DESTRUCTOR

		virtual~GameStyles();

		//MY

		static help_sbat::padding_styles PaddingStyles;
		static help_sbat::text_styles TextStyles;
		static help_sbat::draw_field_styles DrawFieldStyles;


	};




}


#endif // !SBAT_GAMESTYLES_H

