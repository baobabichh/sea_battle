#ifndef SBAT_BUTTON_H
#define SBAT_BUTTON_H

#include "Updatable.h"
#include <SFML/Graphics.hpp>
#include "Transformable.h"
#include "func.h"
#include "Padding.h"
#include <corecrt_wstring.h>	
#include "GameResources.h"
#include "GameStyles.h"


namespace sbat
{


	class BaseButton
		:
		public sbat::Updatable,
		public sf::Drawable,
		public sbat::Transformable
	{
	public:

		//CONSTRUCTOR

		BaseButton() = default;
		//DESTRUCTOR

		virtual~BaseButton() = default;

		//MY


		bool pressed(sf::RenderWindow& window, sf::Mouse::Button button = sf::Mouse::Left)const;
		bool clicked(sf::RenderWindow& window, const sf::Event& event , sf::Mouse::Button button = sf::Mouse::Left)const;
		bool hovered(sf::RenderWindow& window) const;

		//UPDATABLE

		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr) override =0;

	protected:

		sf::FloatRect m_hit_box;

		//DRAWABLE

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override =0;
		
	};



}



#endif // !SBAT_BUTTON_H

