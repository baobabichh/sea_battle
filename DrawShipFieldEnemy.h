#ifndef SBAT_DRAWSHIPFIELDENEMY_H
#define SBAT_DRAWSHIPFIELDENEMY_H

#include "DrawShipField.h"

namespace sbat
{

	class DrawShipFieldEnemy
		:
		public DrawShipField
	{
	public:
		DrawShipFieldEnemy();
		~DrawShipFieldEnemy();

		void add_ship(const sf::Vector2i& pos, const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing)override;

	private:

	};



}

#endif // !SBAT_DRAWSHIPFIELDENEMY_H

