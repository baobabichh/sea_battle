#ifndef SBAT_DRAWSHIPENEMY_H
#define SBAT_DRAWSHIPENEMY_H

#include "DrawShip.h"

namespace sbat
{

	class DrawShipEnemy :
		public DrawShip
	{
	public:
		//CONSTRUCTOR
		DrawShipEnemy();

		DrawShipEnemy
		(
			std::vector<sf::Texture>& ship_textures,
			sbat::Animation* explosion_anim, sbat::Animation* smoke_anim,
			const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing
		);

		//DESTRUCTOR
		virtual~DrawShipEnemy();

		//MY
		void set_animations(sbat::Animation* explosion_anim, sbat::Animation* smoke_anim);
		void set_ship_texture(std::vector<sf::Texture>& ship_textures) ;

		sf::FloatRect get_cell_global_bounds(const sbat::ShipCellPosition& position);
		sf::FloatRect get_local_global_bounds(const sbat::ShipCellPosition& position) ;

		void set_ship_facing(const sbat::ShipFacing& rotation) override;
		void set_ship_type(const sbat::ShipType& type)override;

		//BASE SHIP

		void explode(const sbat::ShipCellPosition& position)override;

		//TRANSFORMABLE


		//UPDATEBLE
		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr) override;

	private:


		bool  m_show_main_texture;

		sbat::Animation* p_exposion_anim, * p_smoke_anim;


		std::vector<sbat::Animation> m_smoke_animations;
		std::vector<sbat::Animation> m_explosion_animations;
		std::vector<sf::Sprite> m_cell_sprites;

		int m_smokes_after_explosion = 7;

		//DRAWABLE
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};


}

#endif // !SBAT_DRAWSHIPENEMY_H
