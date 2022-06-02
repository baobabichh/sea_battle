#ifndef SBAT_DRAWSHIPFIELDFRIEND_H
#define SBAT_DRAWSHIPFIELDFRIEND_H

#include "DrawShipField.h"

namespace sbat
{

	class DrawShipFieldFriend
		:
		public DrawShipField
	{
	public:
		DrawShipFieldFriend();
		~DrawShipFieldFriend();

		void add_ship(const sf::Vector2i& pos, const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing)override;
		void shoot_with_final_anim(const sf::Vector2i& pos);

	private:
		void explode_around_ship_with_final_anim(const sf::Vector2i& pos, const BaseShip& ship);
		void create_cross(const sf::Vector2i& pos);
	};



}

#endif // !SBAT_DRAWSHIPFIELDFRIEND_H

