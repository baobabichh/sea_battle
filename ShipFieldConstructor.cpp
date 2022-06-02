#include "ShipFieldConstructor.h"
#include "ShipFieldConstructor.h"

namespace sbat
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//CONSTRUCTOR

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ShipFieldConstructor::ShipFieldConstructor()
		:
		sbat::DrawField(),
		p_ship_textures(nullptr),
		m_ships(),
		m_is_ship_selected(0),
		m_is_ship_on_move(0),
		m_is_ship_on_move_prev(0),
		m_is_ship_selected_prev(0),
		m_moving_ship_start(),
		m_moving_ship_end()
	{
		
		
		m_field.resize(static_cast<int>(get_field_size().x) * get_field_size().y);
		std::fill(m_field.begin(), m_field.end(), 0);

	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//DESTRUCTOR

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ShipFieldConstructor::~ShipFieldConstructor()
	{

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//MY

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ShipFieldConstructor::init()
	{
		set_font(&sbat::GameResources::get_font(DEFAULT_FONT));
		p_ship_textures = &sbat::GameResources::get_ship_textures();
		set_style(sbat::GameStyles::DrawFieldStyles.Default);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ShipFieldConstructor::add_ship(const sf::Vector2i& pos, const sbat::DrawShipConstructor& ship)
	{
		m_ships[pos] = ship;
		update_matr();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ShipFieldConstructor::remove_ship(const sf::Vector2i& pos)
	{
		if (m_ships.find(pos) != m_ships.end())
		{
			m_ships.erase(pos);
			update_matr();
		}
			
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ShipFieldConstructor::set_ship_texture(std::vector<sf::Texture>& ship_textures)
	{
		this->p_ship_textures = &ship_textures;

		for (auto&& it : m_ships)
		{
			it.second.set_ship_texture(*p_ship_textures);
		}
		m_moving_ship_start.second.set_ship_texture(*p_ship_textures);
		m_moving_ship_end.second.set_ship_texture(*p_ship_textures);

		m_moving_ship_start.second.set_scale
		(
			static_cast<float>(get_cell_size()) / (*p_ship_textures)[0].getSize().x,
			static_cast<float>(get_cell_size()) / (*p_ship_textures)[0].getSize().x
		);

		m_moving_ship_end.second.set_scale
		(
			static_cast<float>(get_cell_size()) / (*p_ship_textures)[0].getSize().x,
			static_cast<float>(get_cell_size()) / (*p_ship_textures)[0].getSize().x
		);



	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	void ShipFieldConstructor::add_ship(const sf::Vector2i& pos, const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing)
	{
		
		sbat::DrawShipConstructor ship;

		ship.set_ship_texture(*p_ship_textures);
		ship.set_ship_type(ship_type);
		ship.set_ship_facing(ship_facing);

		ship.set_position(get_cell_local_bounds(pos).left, get_cell_local_bounds(pos).top);
		ship.set_scale
		(
			static_cast<float>(get_cell_size()) / (*p_ship_textures)[0].getSize().x,
			static_cast<float>(get_cell_size()) / (*p_ship_textures)[0].getSize().x
		);

		m_ships[pos] = ship;
		update_matr();
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ShipFieldConstructor::random()
	{
		m_is_ship_on_move = 0;
		m_is_ship_selected = 0;
		
		std::fill(m_field.begin(), m_field.end(), 0);

		m_ships.clear();
		
		std::vector<sf::Vector2i> free_places;


		//ship 4
		auto facing = static_cast<sbat::ShipFacing>(Random::rand(0, 3));

		if (facing == ShipFacing::LEFT || facing == ShipFacing::RIGHT)
		{
			add_ship(sf::Vector2i(Random::rand(0, 9 - static_cast<int>(sbat::ShipType::FOUR)), Random::rand(0, 9)), sbat::ShipType::FOUR, facing);
		}
		else
		{
			add_ship(sf::Vector2i(Random::rand(0, 9), Random::rand(0, 9 - static_cast<int>(sbat::ShipType::FOUR))), sbat::ShipType::FOUR, facing);
		}

		//ship 3
		free_places.reserve(get_field_size().x * get_field_size().y);

		facing = static_cast<sbat::ShipFacing>(Random::rand(0, 3));

		sbat::BaseShip tmp;
		tmp.set_ship_type(sbat::ShipType::TREE);
		tmp.set_ship_facing(facing);

		for (int ship_i = 0; ship_i < 2; ship_i++)
		{
			free_places.clear();
			for (int i = 0; i < get_field_size().y; i++)
			{
				for (int j = 0; j < get_field_size().x; j++)
				{
					if (can_ship_place(sf::Vector2i(j, i), tmp))
					{
						free_places.push_back(sf::Vector2i(j, i));
					}
				}
			}

			add_ship(free_places.at(Random::rand(0, static_cast<int>(free_places.size())-1)), tmp.get_ship_type(), tmp.get_ship_facing());
		}
		//ship 2
		facing = static_cast<sbat::ShipFacing>(Random::rand(0, 3));

		tmp.set_ship_type(sbat::ShipType::TWO);
		tmp.set_ship_facing(facing);

		for (int ship_i = 0; ship_i < 3; ship_i++)
		{
			free_places.clear();
			for (int i = 0; i < get_field_size().y; i++)
			{
				for (int j = 0; j < get_field_size().x; j++)
				{
					if (can_ship_place(sf::Vector2i(j, i), tmp))
					{
						free_places.push_back(sf::Vector2i(j, i));
					}
				}
			}

			add_ship(free_places.at(Random::rand(0, static_cast<int>(free_places.size()) - 1)), tmp.get_ship_type(), tmp.get_ship_facing());
		}
		//ship 1
		facing = static_cast<sbat::ShipFacing>(Random::rand(0, 3));

		tmp.set_ship_type(sbat::ShipType::ONE);
		tmp.set_ship_facing(facing);

		for (int ship_i = 0; ship_i < 4; ship_i++)
		{
			free_places.clear();
			for (int i = 0; i < get_field_size().y; i++)
			{
				for (int j = 0; j < get_field_size().x; j++)
				{
					if (can_ship_place(sf::Vector2i(j, i), tmp))
					{
						free_places.push_back(sf::Vector2i(j, i));
					}
				}
			}

			add_ship(free_places.at(Random::rand(0, static_cast<int>(free_places.size()) - 1)), tmp.get_ship_type(), tmp.get_ship_facing());
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ShipFieldConstructor::update_moving_ship(sf::RenderWindow& window, const float& dt, const sf::Event* event )
	{
		auto transform = get_Transfrom();

		m_is_ship_on_move_prev = m_is_ship_on_move;
		m_is_ship_selected_prev = m_is_ship_selected;


		if (event->type == sf::Event::MouseButtonPressed)
		{
			if (event->mouseButton.button == sf::Mouse::Button::Left)
			{
				if (transform.transformRect(m_moving_ship_end.second.get_global_bounds()).contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && m_is_ship_selected)
				{
					m_is_ship_on_move = 1;
					m_is_ship_selected = 1;
				}
				else
				{
					bool found = 0;
					for (auto& it : m_ships)
					{
						if (transform.transformRect(it.second.get_global_bounds()).contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
						{
							m_moving_ship_end.second.set_wrong_color(DrawShipConstructorState::DEFAULT);
							found = 1;
							if (m_is_ship_selected_prev)
							{

								if (can_ship_place(m_moving_ship_end.first, m_moving_ship_end.second))
								{
									add_ship(m_moving_ship_end.first, m_moving_ship_end.second);
								}
								else
								{
									add_ship(m_moving_ship_start.first, m_moving_ship_start.second);
								}
							}
							m_moving_ship_start = it;
							m_moving_ship_end = it;

							remove_ship(it.first);

							m_is_ship_on_move = 1;
							m_is_ship_selected = 1;
							break;
						}
					}
					if (!found && get_global_bounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					{
						m_is_ship_on_move = 0;
						m_is_ship_selected = 0;
					}
				}
			}
		}
		else if (event->type == sf::Event::MouseButtonReleased)
		{
			if (event->mouseButton.button == sf::Mouse::Button::Left)
			{
				m_is_ship_on_move = 0;
			}
		}


		
		if (m_is_ship_on_move)
		{
			//std::cout << "(" << m_moving_ship_end.first.x << "," << m_moving_ship_end.first.y << ")" << can_ship_place(m_moving_ship_end.first, m_moving_ship_end.second) << "\n";
			if (can_ship_place(m_moving_ship_end.first, m_moving_ship_end.second))
			{
				m_moving_ship_end.second.set_wrong_color(DrawShipConstructorState::SELECTED);
			}
			else
			{
				m_moving_ship_end.second.set_wrong_color(DrawShipConstructorState::WRONG);
			}
		}


		if (m_is_ship_selected && m_is_ship_on_move) // update moving
		{
			for (size_t i = 0; i < get_field_size().y; i++)
			{
				for (size_t j = 0; j < get_field_size().x; j++)
				{
					if (get_cell_global_bounds(i, j).contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					{
						m_moving_ship_end.second.set_position(get_cell_local_bounds(i, j).left, get_cell_local_bounds(i, j).top);
						m_moving_ship_end.first = sf::Vector2i(i, j);
						break;
					}
				}
			}
		}
		//field pressed
		if (m_is_ship_selected_prev && !m_is_ship_selected)
		{
			m_moving_ship_end.second.set_wrong_color(DrawShipConstructorState::DEFAULT);
			if (can_ship_place(m_moving_ship_end.first, m_moving_ship_end.second))
			{
				add_ship(m_moving_ship_end.first, m_moving_ship_end.second);
			}
			else
			{
				add_ship(m_moving_ship_start.first, m_moving_ship_start.second);
			}
			m_is_ship_on_move = 0;
			m_is_ship_selected = 0;
		}

	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ShipFieldConstructor::rotate_ship()
	{

		if (m_is_ship_selected)
		{
			m_moving_ship_end.second.set_ship_facing
			(
				static_cast<sbat::ShipFacing>((static_cast<int>(m_moving_ship_end.second.get_ship_facing()) + 1) % (static_cast<int>(sbat::ShipFacing::UP) + 1))
			);
			if (can_ship_place(m_moving_ship_end.first, m_moving_ship_end.second))
			{
				m_moving_ship_end.second.set_wrong_color(DrawShipConstructorState::SELECTED);
			}
			else
			{
				m_moving_ship_end.second.set_wrong_color(DrawShipConstructorState::WRONG);
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//UPDATABLE

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ShipFieldConstructor::update(sf::RenderWindow& window, const float& dt, const sf::Event* event)
	{
		DrawField::update(window, dt);


		this->update_moving_ship(window, dt, event);

		auto transform = get_Transfrom();

		for (auto&& it : m_ships)
		{
			it.second.update(window, dt);
		}



	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ShipFieldConstructor::update_matr()
	{
		std::fill(m_field.begin(), m_field.end(), 0);
		for (auto& ship : m_ships)
		{
			bool val = 1;
			int ship_size = static_cast<int>(ship.second.get_ship_type());
			sf::Vector2i tmp_pos;
			if (ship.second.get_ship_facing() == sbat::ShipFacing::LEFT || ship.second.get_ship_facing() == sbat::ShipFacing::RIGHT)
			{
				for (int i = 0; i < ship_size; i++)
				{
					for (int q1 = -1; q1 < 2; q1++)
					{
						for (int q2 = -1; q2 < 2; q2++)
						{
							tmp_pos = sf::Vector2i(ship.first.x + q1 + i, ship.first.y + q2);
							if (tmp_pos.x < get_field_size().x && tmp_pos.x >= 0 && tmp_pos.y < get_field_size().y && tmp_pos.y >= 0)
							{
								matr_val(tmp_pos.x, tmp_pos.y) = val;
							}
						}
					}
				}
			}
			else if (ship.second.get_ship_facing() == sbat::ShipFacing::UP || ship.second.get_ship_facing() == sbat::ShipFacing::DOWN)
			{
				for (int i = 0; i < ship_size; i++)
				{
					for (int q1 = -1; q1 < 2; q1++)
					{
						for (int q2 = -1; q2 < 2; q2++)
						{
							tmp_pos = sf::Vector2i(ship.first.x + q1, ship.first.y + q2 + i);
							if (tmp_pos.x < get_field_size().x && tmp_pos.x >= 0 && tmp_pos.y < get_field_size().y && tmp_pos.y >= 0)
							{
								matr_val(tmp_pos.x, tmp_pos.y) = val;
							}
						}
					}
				}
			}
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool ShipFieldConstructor::can_ship_place(const sf::Vector2i& pos, const sbat::BaseShip& ship)
	{
		bool val = 1;
		int ship_size = static_cast<int>(ship.get_ship_type());
		sf::Vector2i tmp_pos;
		if (ship.get_ship_facing() == sbat::ShipFacing::LEFT || ship.get_ship_facing() == sbat::ShipFacing::RIGHT)
		{
			for (int i = 0; i < ship_size; i++)
			{
				tmp_pos = sf::Vector2i(pos.x +  i, pos.y );
				if (tmp_pos.x < get_field_size().x && tmp_pos.x >= 0 && tmp_pos.y < get_field_size().y && tmp_pos.y >= 0)
				{
					if (matr_val(tmp_pos.x, tmp_pos.y) == val)
						return 0;
				}
				else
					return 0;
			}
		}
		else if (ship.get_ship_facing() == sbat::ShipFacing::UP || ship.get_ship_facing() == sbat::ShipFacing::DOWN)
		{
			for (int i = 0; i < ship_size; i++)
			{
				tmp_pos = sf::Vector2i(pos.x , pos.y  + i);
				if (tmp_pos.x < get_field_size().x && tmp_pos.x >= 0 && tmp_pos.y < get_field_size().y && tmp_pos.y >= 0)
				{
					if (matr_val(tmp_pos.x, tmp_pos.y) == val)
						return 0;
				}
				else
					return 0;
					
			}
		}
		return 1;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	short& ShipFieldConstructor::matr_val(int x, int y)
	{
		return m_field[y * get_field_size().x + x];
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//DRAWABLE

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void ShipFieldConstructor::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		DrawField::draw(target, states);
		states.transform *= get_Transfrom();
		

		for (auto&& it : m_ships)
		{
			target.draw(it.second, states);
		}

		if (m_is_ship_selected)
		{
			target.draw(m_moving_ship_end.second, states);
		}
		
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}