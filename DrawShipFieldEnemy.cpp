#include "DrawShipFieldEnemy.h"

namespace sbat
{

	DrawShipFieldEnemy::DrawShipFieldEnemy()
		:
		DrawShipField()
	{
	}

	DrawShipFieldEnemy::~DrawShipFieldEnemy()
	{
	}


	void sbat::DrawShipFieldEnemy::add_ship(const sf::Vector2i& pos, const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing)
	{
		DrawShip* ship = new DrawShipEnemy();

		ship->set_ship_texture(*p_ship_textures);
		dynamic_cast<DrawShipEnemy*>(ship)->set_animations(p_explosion_anim, p_smoke_anim);
		ship->set_ship_type(ship_type);
		ship->set_ship_facing(ship_facing);

		ship->set_position(get_cell_local_bounds(pos).left, get_cell_local_bounds(pos).top);
		ship->set_scale
		(
			static_cast<float>(get_cell_size()) / (*p_ship_textures)[0].getSize().x,
			static_cast<float>(get_cell_size()) / (*p_ship_textures)[0].getSize().x
		);

		m_ships[pos] = ship;
	}



}