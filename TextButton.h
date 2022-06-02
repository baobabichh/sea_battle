#ifndef SBAT_TEXTBUTTON_H
#define SBAT_TEXTBUTTON_H

#include "BaseButton.h"


namespace sbat
{

	class TextButton 
		:
		public BaseButton

	{
	public:
		//CONSTRUCTOR

		TextButton() ;
		//DESTRUCTOR

		virtual~TextButton() ;

		//MY

		void init();


		void set_font(sf::Font* font);
		
		void set_string(const std::wstring& title);
		const std::wstring& get_string()const;

		void set_style( const TextStyle& text_style);

		sf::FloatRect get_local_bounds()const;
		sf::FloatRect get_global_bounds()const;

		//UPDATABLE

		void update(sf::RenderWindow & window, const float& dt, const sf::Event * event = nullptr) override ;

	protected:

		sf::Text m_text;

		sbat::TextStyle m_text_style;


		//DRAWABLE

		void draw(sf::RenderTarget & target, sf::RenderStates states) const override;



	};

}






#endif // !SBAT_TEXTBUTTON_H




