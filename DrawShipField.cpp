#include "DrawShipField.h"


namespace sbat
{


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//CONSTRUCTOR

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	sbat::DrawShipField::DrawShipField()
		:
		m_ships(),
		m_need_ship_style_update(0),
		p_ship_textures(nullptr),
		p_explosion_anim(nullptr),
		p_smoke_anim(nullptr),
		p_water_hit_anim(nullptr),
		p_cross_tx(nullptr)
	{

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//DESTRUCTOR

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	sbat::DrawShipField::~DrawShipField()
	{

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//MY

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void sbat::DrawShipField::init()
	{
		p_explosion_anim = &sbat::GameResources::get_animation(DEFAULT_EXPLOSION_ANIM);
		p_smoke_anim = &sbat::GameResources::get_animation(DEFAULT_SMOKE_ANIM);
		p_water_hit_anim = &sbat::GameResources::get_animation(DEFAULT_WATER_SPLASH_ANIM);
		p_cross_anim = &sbat::GameResources::get_animation(DEFAULT_FIELD_CROSS_ANIM);
		p_ship_textures = &sbat::GameResources::get_ship_textures();
		p_cross_tx = &sbat::GameResources::get_texture(DEFAULT_FIELD_CROSS_TEXTURE);
		sbat::DrawField::set_font(&sbat::GameResources::get_font(DEFAULT_FONT));

		set_style(GameStyles::DrawFieldStyles.Default);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void sbat:: DrawShipField::copy_ships(ShipFieldConstructor& val)
	{
		if (val.m_is_ship_selected)
		{
			if (val.can_ship_place(val.m_moving_ship_end.first, val.m_moving_ship_end.second))
				add_ship(val.m_moving_ship_end.first, val.m_moving_ship_end.second.get_ship_type(), val.m_moving_ship_end.second.get_ship_facing());
			else
				add_ship(val.m_moving_ship_start.first, val.m_moving_ship_start.second.get_ship_type(), val.m_moving_ship_start.second.get_ship_facing());
		}
		for (auto& it : val.m_ships)
		{
			add_ship(it.first, it.second.get_ship_type(), it.second.get_ship_facing());
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void sbat:: DrawShipField::set_ship_animations(sbat::Animation* explosion_anim, sbat::Animation* smoke_anim)
	{
		p_explosion_anim = explosion_anim;
		p_smoke_anim = smoke_anim;

		m_need_ship_style_update = 1;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void sbat:: DrawShipField::set_field_animation(sbat::Animation* water_hit_anim, sbat::Animation* cross_anim)
	{
		p_water_hit_anim = water_hit_anim;
		p_cross_anim = cross_anim;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void DrawShipField::set_ship_texture(std::vector<sf::Texture>& ship_textures)
	{
		p_ship_textures = &ship_textures;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void DrawShipField::set_field_textures(sf::Texture* cross_tx)
	{
		this->p_cross_tx = cross_tx;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void sbat:: DrawShipField::remove_ship(const sf::Vector2i& pos)
	{
		if (m_ships.find(pos) != m_ships.end())
			m_ships.erase(pos);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// UPDATEBLE

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void DrawShipField::update(sf::RenderWindow& window, const float& dt, const sf::Event* event)
	{
		sbat::DrawField::update(window, dt);

		


		std::vector<int> needs_delete_splash;
		std::vector<int> needs_delete_cross;

		//std::cout << "////////////////////////////////////////////////////////////////////\n";
		//std::cout << "splash anims : " << m_splash_animations.size() << std::endl;
		//std::cout << "cross anims : " << m_cross_animations.size() << std::endl;
		//std::cout << "cross sprites : " << m_cross_sprites.size() << std::endl;

		//water
		for (int i = 0; i < m_splash_animations.size(); i++)
		{
			if (m_splash_animations[i].second.ended())
			{
				needs_delete_splash.push_back(i);
				//create cross anim
				m_cross_animations.push_back(std::make_pair(m_splash_animations[i].first, *p_cross_anim));
				(m_cross_animations.end() - 1)->second.play();
				(m_cross_animations.end() - 1)->second.set_position
				(
					get_cell_local_bounds(m_splash_animations[i].first).left,
					get_cell_local_bounds(m_splash_animations[i].first).top
				);

				(m_cross_animations.end() - 1)->second.set_scale
				(
					get_cell_local_bounds(m_splash_animations[i].first).width / (m_cross_animations.end() - 1)->second.get_global_bounds().width,
					get_cell_local_bounds(m_splash_animations[i].first).height / (m_cross_animations.end() - 1)->second.get_global_bounds().height
				);
			}
			else
			{
				m_splash_animations[i].second.update(window, dt);
			}
		}

		for (int i = static_cast<int>(needs_delete_splash.size() - 1); i >= 0; i--)
		{
			m_splash_animations.erase(m_splash_animations.begin() + needs_delete_splash[i]);
		}


		//cross
		for (int i = 0; i < m_cross_animations.size(); i++)
		{
			if (m_cross_animations[i].second.ended())
			{
				needs_delete_cross.push_back(i);
				//create cross sprite
				m_cross_sprites.insert(std::make_pair(m_cross_animations[i].first, sf::Sprite()));
				m_cross_sprites[m_cross_animations[i].first].setTexture(*p_cross_tx);
				m_cross_sprites[m_cross_animations[i].first].setPosition
				(
					get_cell_local_bounds(m_cross_animations[i].first).left,
					get_cell_local_bounds(m_cross_animations[i].first).top
				);
				//m_cross_sprites[m_cross_animations[i].first].setColor(sf::Color(196, 0, 0));
				m_cross_sprites[m_cross_animations[i].first].setScale
				(
					get_cell_global_bounds(m_cross_animations[i].first).width / static_cast<float>(p_cross_tx->getSize().x),
					get_cell_global_bounds(m_cross_animations[i].first).height / static_cast<float>(p_cross_tx->getSize().y)
				);
			}
			else
			{
				m_cross_animations[i].second.update(window, dt);
			}
		}

		for (int i = static_cast<int>(needs_delete_cross.size() - 1); i >= 0; i--)
		{
			m_cross_animations.erase(m_cross_animations.begin() + needs_delete_cross[i]);
		}


		//ships
		for (auto&& it : m_ships)
		{
			it.second->update(window, dt);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//DRAWABLE 

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void DrawShipField::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sbat::DrawField::draw(target, states);

		states.transform = this->get_Transfrom();

		for (auto&& it : m_cross_sprites)
		{
			target.draw(it.second, states);
		}

		for (auto&& it : m_cross_animations)
		{
			target.draw(it.second, states);
		}

		for (auto&& it : m_splash_animations)
		{
			target.draw(it.second, states);
		}

		for (auto&& it : m_ships)
		{
			target.draw(*it.second, states);
		}

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void DrawShipField::create_cross_anim(const sf::Vector2i& pos)
	{
		m_cross_animations.push_back(std::make_pair(pos, *p_cross_anim));
		(m_cross_animations.end() - 1)->second.play();
		(m_cross_animations.end() - 1)->second.set_position
		(
			get_cell_local_bounds(pos).left,
			get_cell_local_bounds(pos).top
		);

		(m_cross_animations.end() - 1)->second.set_scale
		(
			get_cell_local_bounds(pos).width / (m_cross_animations.end() - 1)->second.get_global_bounds().width,
			get_cell_local_bounds(pos).height / (m_cross_animations.end() - 1)->second.get_global_bounds().height
		);
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void DrawShipField::explode_around_ship(const sf::Vector2i& pos, const BaseShip& ship)
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
					create_cross_anim(tmp_pos);
				}
			}
			//middle
			tmp_pos = sf::Vector2i(pos.x, pos.y - 1);
			if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
			{
				create_cross_anim(tmp_pos);
			}

			tmp_pos = sf::Vector2i(pos.x, pos.y + ship_size);
			if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
			{
				create_cross_anim(tmp_pos);
			}
			//right
			for (int i = -1; i < ship_size + 1; i++)
			{
				tmp_pos = sf::Vector2i(pos.x + 1, pos.y + i);
				if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
				{
					create_cross_anim(tmp_pos);
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
					create_cross_anim(tmp_pos);
				}
			}
			//middle
			tmp_pos = sf::Vector2i(pos.x - 1, pos.y);
			if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
			{
				create_cross_anim(tmp_pos);
			}

			tmp_pos = sf::Vector2i(pos.x + ship_size, pos.y);
			if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
			{
				create_cross_anim(tmp_pos);
			}
			//right
			for (int i = -1; i < ship_size + 1; i++)
			{
				tmp_pos = sf::Vector2i(pos.x + i, pos.y + 1);
				if ((tmp_pos.x >= 0 && tmp_pos.x < get_field_size().x && tmp_pos.y >= 0 && tmp_pos.y < get_field_size().y) && get_cell_state(tmp_pos) == sbat::FieldCellState::NOTHING)
				{
					create_cross_anim(tmp_pos);
				}
			}
		}


	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void DrawShipField::shoot(const sf::Vector2i& pos)
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

						it.second->explode(static_cast<sbat::ShipCellPosition>(i));
						if (it.second->ship_exploded())
						{
							this->explode_around_ship(it.first, *it.second);
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

						it.second->explode(static_cast<sbat::ShipCellPosition>(i));
						if (it.second->ship_exploded())
						{
							this->explode_around_ship(it.first, *it.second);
						}
						return;
					}
				}

			}
		}

		m_splash_animations.push_back(std::make_pair(pos, *p_water_hit_anim));
		(m_splash_animations.end() - 1)->second.play();
		float scale_val = std::max((m_splash_animations.end() - 1)->second.get_global_bounds().width, (m_splash_animations.end() - 1)->second.get_global_bounds().height);

		(m_splash_animations.end() - 1)->second.set_position(this->get_cell_local_bounds(pos).left, this->get_cell_local_bounds(pos).top);
		(m_splash_animations.end() - 1)->second.set_scale
		(
			this->get_cell_local_bounds(pos).width / scale_val,
			this->get_cell_local_bounds(pos).width / scale_val
		);

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	sbat::FieldCellState DrawShipField::get_cell_state(const sf::Vector2i& pos)const
	{
		if (!(pos.x >= 0 && pos.x < get_field_size().x && pos.y >= 0 && pos.y < get_field_size().y))
			throw std::out_of_range("sbat::FieldCellState& DrawShipField::get_cell_state , out of range");

		//is already hited m_cross_sprites
		if (m_cross_sprites.size())
			for (auto&& it : m_cross_sprites)
			{
				if (it.first == pos)
					return sbat::FieldCellState::NOTHING_HIT;
			}
		//is already hited m_splash_animations
		for (auto&& it : m_splash_animations)
		{
			if (it.first == pos)
				return sbat::FieldCellState::NOTHING_HIT;
		}
		//is already hited m_cross_animations
		for (auto&& it : m_cross_animations)
		{
			if (it.first == pos)
				return sbat::FieldCellState::NOTHING_HIT;
		}

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
							return sbat::FieldCellState::SHIP_EXPLODED;
						else if (it.second->get_cell_state(static_cast<sbat::ShipCellPosition>(i)) == sbat::ShipCellState::DEFAULT)
							return sbat::FieldCellState::SHIP;
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
							return sbat::FieldCellState::SHIP_EXPLODED;
						else if (it.second->get_cell_state(static_cast<sbat::ShipCellPosition>(i)) == sbat::ShipCellState::DEFAULT)
							return sbat::FieldCellState::SHIP;
					}
				}
			}
		}

		return sbat::FieldCellState::NOTHING;

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	bool DrawShipField::all_ships_exploded()const
	{
		for (auto& it : m_ships)
		{
			if (!it.second->ship_exploded())
				return 0;
		}
		return 1;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	 
	void DrawShipField::clear()
	{
		m_cross_animations.clear();
		m_cross_sprites.clear();
		m_splash_animations.clear();
		for (auto& it : m_ships)
			delete it.second;
		m_ships.clear();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const std::unordered_map<sf::Vector2i, DrawShip*, Vector2Ihash>& DrawShipField::get_ships()
	{
		return m_ships;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}