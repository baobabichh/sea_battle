#include "BotRandom.h"

namespace sbat
{
	BotRandom::BotRandom()
		:
		m_should_kill(0)
	{

	}

	sf::Vector2i BotRandom::make_move()
	{
		
		get_available_hits();
		sf::Vector2i res;

		if (p_field->all_ships_exploded())
		{
			return sf::Vector2i(-1, -1);
		}

		if (m_should_kill)
		{
//std::cout << "m_should_kill ";
			if (m_killing_ship.second->ship_exploded())
			{
				m_should_kill = 0;
				m_checked_facings.clear();
				m_probably_ship_here.clear();

			//	std::cout << "!m_should_kill ";
				res = make_random_move();
				if (p_field->get_cell_state(res) == sbat::FieldCellState::SHIP)
				{
					m_first_ship_pos = res;
					fill_probably_ship(res);
					m_should_kill = 1;
					m_killing_ship = get_ship(res);
				}
			}
			else
			{
				res = render_probably_ship();
			}
		}
		else
		{
			//std::cout << "!m_should_kill ";
			res = make_random_move();
			if (p_field->get_cell_state(res) == sbat::FieldCellState::SHIP)
			{
				m_first_ship_pos = res;
				fill_probably_ship(res);
				m_should_kill = 1;
				m_killing_ship = get_ship(res);
			}
		}

		//std::cout << "res x=" << res.x << " , y=" << res.y << "\n";

		p_field->shoot(res);
		return res;

	}

	sf::Vector2i BotRandom::make_random_move()
	{
		return m_available_hits[sbat::Random::rand(0, static_cast<int>(m_available_hits.size()) - 1)];
	}

	void BotRandom::get_available_hits()
	{
		m_available_hits.clear();
		for (int i = 0; i < p_field->get_field_size().y; i++)
		{
			for (int j = 0; j < p_field->get_field_size().x; j++)
			{
				auto val = p_field->get_cell_state(sf::Vector2i(j, i));
				if (val == FieldCellState::NOTHING || val == FieldCellState::SHIP)
					m_available_hits.push_back(sf::Vector2i(j, i));
			}
		}
	}

	void BotRandom::fill_probably_ship(const sf::Vector2i& pos)
	{
		m_probably_ship_here.clear();
		//up
		for (int i = 1; i < 4; i++)
		{
			auto tmp_vec = sf::Vector2i(pos.x, pos.y + i);

			if (!(tmp_vec.x < p_field->get_field_size().x && tmp_vec.x >= 0 && tmp_vec.y < p_field->get_field_size().y && tmp_vec.y >= 0))
				break;

			if (std::find(m_available_hits.begin(), m_available_hits.end(), tmp_vec) != m_available_hits.end())
			{
				m_probably_ship_here.push_back(tmp_vec);
			}
			else
				break;
		}
		//down
		for (int i = 1; i < 4; i++)
		{
			auto tmp_vec = sf::Vector2i(pos.x, pos.y - i);

			if (!(tmp_vec.x < p_field->get_field_size().x && tmp_vec.x >= 0 && tmp_vec.y < p_field->get_field_size().y && tmp_vec.y >= 0))
				break;

			if (std::find(m_available_hits.begin(), m_available_hits.end(), tmp_vec) != m_available_hits.end())
			{
				m_probably_ship_here.push_back(tmp_vec);
			}
			else
				break;
		}
		//left
		for (int i = 1; i < 4; i++)
		{
			auto tmp_vec = sf::Vector2i(pos.x -i, pos.y);

			if (!(tmp_vec.x < p_field->get_field_size().x && tmp_vec.x >= 0 && tmp_vec.y < p_field->get_field_size().y && tmp_vec.y >= 0))
				break;

			if (std::find(m_available_hits.begin(), m_available_hits.end(), tmp_vec) != m_available_hits.end())
			{
				m_probably_ship_here.push_back(tmp_vec);
			}
			else
				break;
		}
		//right
		for (int i = 1; i < 4; i++)
		{
			auto tmp_vec = sf::Vector2i(pos.x + i, pos.y);

			if (!(tmp_vec.x < p_field->get_field_size().x && tmp_vec.x >= 0 && tmp_vec.y < p_field->get_field_size().y && tmp_vec.y >= 0))
				break;

			if (std::find(m_available_hits.begin(), m_available_hits.end(), tmp_vec) != m_available_hits.end())
			{
				m_probably_ship_here.push_back(tmp_vec);
			}
			else
				break;
		}
	}

	sf::Vector2i BotRandom::render_probably_ship()
	{
		sf::Vector2i res;

		for (int facing_i = 0; facing_i <= static_cast<int>(ShipFacing::UP); facing_i++)
		{
			ShipFacing facing = static_cast<ShipFacing>(facing_i);
			if (std::find(m_checked_facings.begin(), m_checked_facings.end(), facing) == m_checked_facings.end())
			{

				sf::Vector2i tmp_vec(-1,-1);

				if (facing == ShipFacing::UP)
				{
					for (int ship_size_i = 0; ship_size_i < 4; ship_size_i++)
					{
						sf::Vector2i tmp_vec1 = sf::Vector2i(m_first_ship_pos.x, m_first_ship_pos.y - ship_size_i);
						if (std::find
						(
							m_probably_ship_here.begin(),
							m_probably_ship_here.end(),
							tmp_vec1
						) != m_probably_ship_here.end())
						{
							tmp_vec = tmp_vec1;
							break;
						}
					}
				}
				else if (facing == ShipFacing::DOWN)
				{
					for (int ship_size_i = 0; ship_size_i < 4; ship_size_i++)
					{
						sf::Vector2i tmp_vec1 = sf::Vector2i(m_first_ship_pos.x, m_first_ship_pos.y + ship_size_i);
						if (std::find
						(
							m_probably_ship_here.begin(),
							m_probably_ship_here.end(),
							tmp_vec1
						) != m_probably_ship_here.end())
						{
							tmp_vec = tmp_vec1;
							break;
						}
					}
				}
				else if (facing == ShipFacing::LEFT)
				{
					for (int ship_size_i = 0; ship_size_i < 4; ship_size_i++)
					{
						sf::Vector2i tmp_vec1 = sf::Vector2i(m_first_ship_pos.x - ship_size_i, m_first_ship_pos.y);
						if (std::find
						(
							m_probably_ship_here.begin(),
							m_probably_ship_here.end(),
							tmp_vec1
						) != m_probably_ship_here.end())
						{
							tmp_vec = tmp_vec1;
							break;
						}
					}
				}
				else if (facing == ShipFacing::RIGHT)
				{
					for (int ship_size_i = 0; ship_size_i < 4; ship_size_i++)
					{
						sf::Vector2i tmp_vec1 = sf::Vector2i(m_first_ship_pos.x + ship_size_i, m_first_ship_pos.y);
						if (std::find
						(
							m_probably_ship_here.begin(),
							m_probably_ship_here.end(),
							tmp_vec1
						) != m_probably_ship_here.end())
						{
							tmp_vec = tmp_vec1;
							break;
						}
					}
				}

				if (tmp_vec == sf::Vector2i(-1, -1))
				{
					//std::cout << "continue\n";
					continue;
				}

				res = tmp_vec;
			//	std::cout << "TMPVEC x=" << tmp_vec.x << " , y=" << tmp_vec.y << "\n";

				auto found_pos = std::find(m_probably_ship_here.begin(), m_probably_ship_here.end(), tmp_vec);
				m_probably_ship_here.erase(found_pos);

				//if ship hited on tmp_vec
				if (p_field->get_cell_state(tmp_vec) == FieldCellState::SHIP)
				{
					for (int i = 0; i < m_probably_ship_here.size(); i++)
					{
						if (facing == ShipFacing::UP)
						{
							m_checked_facings.push_back(ShipFacing::LEFT);
							m_checked_facings.push_back(ShipFacing::RIGHT);
							if (m_probably_ship_here[i].x != m_first_ship_pos.x)
							{
								m_probably_ship_here.erase(m_probably_ship_here.begin() + i);
								i--;
							}
						}
						else if (facing == ShipFacing::DOWN)
						{
							m_checked_facings.push_back(ShipFacing::LEFT);
							m_checked_facings.push_back(ShipFacing::RIGHT);
							if (m_probably_ship_here[i].x != m_first_ship_pos.x)
							{
								m_probably_ship_here.erase(m_probably_ship_here.begin() + i);
								i--;
							}
						}
						else if (facing == ShipFacing::LEFT)
						{
							m_checked_facings.push_back(ShipFacing::UP);
							m_checked_facings.push_back(ShipFacing::DOWN);
							if (m_probably_ship_here[i].y != m_first_ship_pos.y)
							{
								m_probably_ship_here.erase(m_probably_ship_here.begin() + i);
								i--;
							}
						}
						else if (facing == ShipFacing::RIGHT)
						{
							m_checked_facings.push_back(ShipFacing::UP);
							m_checked_facings.push_back(ShipFacing::DOWN);
							if (m_probably_ship_here[i].y != m_first_ship_pos.y)
							{
								m_probably_ship_here.erase(m_probably_ship_here.begin() + i);
								i--;
							}
						}
					}
				}
				else
				{
					m_checked_facings.push_back(facing);
					if (facing == ShipFacing::UP)
					{
						for (int i = 0; i < (int)m_probably_ship_here.size(); i++)
						{
							if (m_probably_ship_here[i].x == tmp_vec.x && m_probably_ship_here[i].y <= tmp_vec.y)
							{
								m_probably_ship_here.erase(m_probably_ship_here.begin() + i);
								i--;
							}
						}
					}
					else if (facing == ShipFacing::DOWN)
					{
						for (int i = 0; i < (int)m_probably_ship_here.size(); i++)
						{
							if (m_probably_ship_here[i].x == tmp_vec.x && m_probably_ship_here[i].y >= tmp_vec.y)
							{
								m_probably_ship_here.erase(m_probably_ship_here.begin() + i);
								i--;
							}
						}
					}
					else if (facing == ShipFacing::LEFT)
					{
						for (int i = 0; i < (int)m_probably_ship_here.size(); i++)
						{
							if (m_probably_ship_here[i].y == tmp_vec.y && m_probably_ship_here[i].x <= tmp_vec.x)
							{
								m_probably_ship_here.erase(m_probably_ship_here.begin() + i);
								i--;
							}
						}
					}
					else if (facing == ShipFacing::RIGHT)
					{
						for (int i = 0; i < (int)m_probably_ship_here.size(); i++)
						{
							if (m_probably_ship_here[i].y == tmp_vec.y && m_probably_ship_here[i].x >= tmp_vec.x)
							{
								m_probably_ship_here.erase(m_probably_ship_here.begin() + i);
								i--;
							}
						}
					}
				}



				return res;
			}

		}
	}

	std::pair<sf::Vector2i, sbat::BaseShip*> BotRandom::get_ship(const sf::Vector2i& pos)
	{
		for (auto& it : p_field->m_ships)
		{
			int ship_size = static_cast<int>(it.second->get_ship_type());
			if (it.second->get_ship_facing() == ShipFacing::LEFT || it.second->get_ship_facing() == ShipFacing::RIGHT)
			{
				for (int i = 0; i < ship_size; i++)
				{
					if (it.first.x + i == pos.x && it.first.y == pos.y)
						return std::make_pair(it.first, it.second);
				}
			}
			else if (it.second->get_ship_facing() == ShipFacing::UP || it.second->get_ship_facing() == ShipFacing::DOWN)
			{
				for (int i = 0; i < ship_size; i++)
				{
					if (it.first.x == pos.x && it.first.y + i == pos.y)
						return std::make_pair(it.first, it.second);
				}
			}
		}
	}

}