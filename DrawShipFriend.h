#ifndef SBAT_DRAWSHIPFRIEND_H
#define SBAT_DRAWSHIPFRIEND_H

#include "DrawShip.h"


namespace sbat
{

    class DrawShipFriend :
        public DrawShip
    {
	public:
		//CONSTRUCTOR
		DrawShipFriend();

		DrawShipFriend
		(
			std::vector<sf::Texture>& ship_textures,
			sbat::Animation* explosion_anim, sbat::Animation* smoke_anim,
			const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing
		);

		//DESTRUCTOR
		virtual~DrawShipFriend();

		//MY
		void set_animations(sbat::Animation* explosion_anim, sbat::Animation* smoke_anim);

		sf::FloatRect get_cell_global_bounds(const sbat::ShipCellPosition& position);
		sf::FloatRect get_local_global_bounds(const sbat::ShipCellPosition& position);


		//BASE SHIP
		void set_ship_facing(const sbat::ShipFacing& rotation)override;
		void set_ship_type(const sbat::ShipType& type)override;

		void explode(const sbat::ShipCellPosition& position)override;
		void explode_with_final_anim(const sbat::ShipCellPosition& position);

		//TRANSFORMABLE


		//UPDATEBLE
		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr) override;

	protected:


		sbat::Animation* p_exposion_anim, * p_smoke_anim;


		std::vector<sbat::Animation> m_smoke_animations;
		std::vector<sbat::Animation> m_explosion_animations;

		int m_smokes_after_explosion = 7;

		//DRAWABLE
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };


}

#endif // !SBAT_DRAWSHIPFRIEND_H
