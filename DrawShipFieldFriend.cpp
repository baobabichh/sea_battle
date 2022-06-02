#include "DrawShipFieldFriend.h"

namespace sbat
{
	DrawShipFieldFriend::DrawShipFieldFriend()
		:
		DrawShipField()
	{
	}

	DrawShipFieldFriend::~DrawShipFieldFriend()
	{
	}


	void sbat::DrawShipFieldFriend::add_ship(const sf::Vector2i& pos, const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing)
	{
		DrawShip* ship = new DrawShipFriend();

		ship->set_ship_texture(*p_ship_textures);
		dynamic_cast<DrawShipFriend*>(ship)->set_animations(p_explosion_anim, p_smoke_anim);
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

	void sbat::DrawShipFieldFriend::shoot_with_final_anim(const sf::Vector2i& pos)
	{
		if (!(pos.x >= 0 && pos.x < get_field_size().x && pos.y >= 0 && pos.y < get_field_size().y))
			return;


		//is already hited m_cross_sprites
		for (auto&& it : m_cross_sprites)
		{
			if (it.first == pos)
				return;
		}
		//is already hited m_splash_animations
		for (auto&& it : m_splash_animations)
		{
			if (it.first == pos)
				return;
		}
		//is already hited m_cross_animations
		for (auto&& it : m_cross_animations)
		{
			if (it.first == pos)
				return;
		}


		//ship check
		for (auto&& it : m_ships)
		{
			int ship_size = static_cast<int>(it.second->get_ship_type());
			if ((it.second->get_ship_facing() == sbat::ShipFacing::UP || it.second->get_ship_facing() == sbat::ShipFacing::DOWN) && it.first.x == pos.x)
			{
				for (int i = 0; i < ship_size; i++)
				{
					if (pos.y == it.first.y + i)//if ship hited;
					{
						if (it.second->get_cell_state(static_cast<sbat::ShipCellPosition>(i)) == sbat::ShipCellState::EXPLODED)
							return;

						dynamic_cast<sbat::DrawShipFriend*>(it.second)->explode_with_final_anim(static_cast<sbat::ShipCellPosition>(i));
						if (it.second->ship_exploded())
						{
							this->explode_around_ship_with_final_anim(it.first, *it.second);
						}

						return;
					}
				}

			}
			else if ((it.second->get_ship_facing() == sbat::ShipFacing::LEFT || it.second->get_ship_facing() == sbat::ShipFacing::RIGHT) && it.first.y == pos.y)
			{
				for (int i = 0; i < ship_size; i++)
				{
					if (pos.x == it.first.x + i)
					{
						if (it.second->get_cell_state(static_cast<sbat::ShipCellPosition>(i)) == sbat::ShipCellState::EXPLODED)
							return;

						dynamic_cast<sbat::DrawShipFriend*>(it.second)->explode_with_final_anim(static_cast<sbat::ShipCellPosition>(i));
						if (it.second->ship_exploded())
						{
							this->explode_around_ship_with_final_anim(it.first, *it.second);
						}
						return;
					}
				}

			}
		}
		create_cross(pos);
	}


	void DrawShipFieldFriend::explode_around_ship_with_final_anim(const sf::Vector2i& pos, const BaseShip& ship)
	{
		if (!(pos.x >= 0 && pos.x < get_field_size().x && pos.y >= 0 && pos.y < get_field_size().y))
			return;

		//if (!ship.ship_exploded())
		//	return;

		int ship_size = static_cast<int>(ship.get_ship_type());

		sf::Vector2i tmp_pos;
		if (ship.get_ship_facing() == sbat::ShipFacing::UP || ship.get_ship_facing() == sbat::ShipFacing::DOWN)
		{
			//left
			for (int i = -1; i < ship_size + 1; i++)
			{
				tmp_pos = sf::Vector2i(pos.x - 1, pos.y + i);
				if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
				{
					create_cross(tmp_pos);
				}
			}
			//middle
			tmp_pos = sf::Vector2i(pos.x, pos.y - 1);
			if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
			{
				create_cross(tmp_pos);
			}

			tmp_pos = sf::Vector2i(pos.x, pos.y + ship_size);
			if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
			{
				create_cross(tmp_pos);
			}
			//right
			for (int i = -1; i < ship_size + 1; i++)
			{
				tmp_pos = sf::Vector2i(pos.x + 1, pos.y + i);
				if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
				{
					create_cross(tmp_pos);
				}
			}
		}
		else if (ship.get_ship_facing() == sbat::ShipFacing::LEFT || ship.get_ship_facing() == sbat::ShipFacing::RIGHT)
		{
			//left
			for (int i = -1; i < ship_size + 1; i++)
			{
				tmp_pos = sf::Vector2i(pos.x + i, pos.y - 1);
				if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
				{
					create_cross(tmp_pos);
				}
			}
			//middle
			tmp_pos = sf::Vector2i(pos.x - 1, pos.y);
			if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
			{
				create_cross(tmp_pos);
			}

			tmp_pos = sf::Vector2i(pos.x + ship_size, pos.y);
			if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
			{
				create_cross(tmp_pos);
			}
			//right
			for (int i = -1; i < ship_size + 1; i++)
			{
				tmp_pos = sf::Vector2i(pos.x + i, pos.y + 1);
				if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
				{
					create_cross(tmp_pos);
				}
			}
		}
	}

	void sbat::DrawShipFieldFriend::create_cross(const sf::Vector2i& pos)
	{
		m_cross_sprites.insert(std::make_pair(pos, sf::Sprite()));
		m_cross_sprites[pos].setTexture(*p_cross_tx);
		m_cross_sprites[pos].setPosition
		(
			get_cell_local_bounds(pos).left,
			get_cell_local_bounds(pos).top
		);
		//m_cross_sprites[m_cross_animations[i].first].setColor(sf::Color(196, 0, 0));
		m_cross_sprites[pos].setScale
		(
			get_cell_global_bounds(pos).width / static_cast<float>(p_cross_tx->getSize().x),
			get_cell_global_bounds(pos).height / static_cast<float>(p_cross_tx->getSize().y)
		);
	}

}