#ifndef DRAWSHIP_H
#define DRAWSHIP_H



#include "BaseShip.h"
#include "Transformable.h"
#include "Updatable.h"
#include "Animation.h"
#include <list>
#include <ctime>

namespace sbat
{
	class DrawShip  : 
		public sbat::BaseShip,
		public sbat::Transformable,
		public sf::Drawable,
		public sbat::Updatable
	{
	public :
		//CONSTRUCTOR
		DrawShip();

		//DESTRUCTOR
		virtual~DrawShip();

		//MY
		
		void show();
		void hide();

		void set_ship_texture(std::vector<sf::Texture>& ship_textures);

		sf::FloatRect get_global_bounds();
		sf::FloatRect get_local_bounds();

		//BASE SHIP
		void set_ship_facing(const sbat::ShipFacing& rotation) override;
		void set_ship_type(const sbat::ShipType& type)override;


		//TRANSFORMABLE


		//UPDATEBLE
		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr) override;

	protected:

		std::vector<sf::Texture>*m_textures;
		sf::Sprite m_sprite;

		bool m_hiden;

		//DRAWABLE
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};


}


#endif // !DRAWSHIP_H