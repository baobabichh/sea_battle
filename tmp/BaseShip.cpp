#include "BaseShip.h"

namespace sbat
{

	sbat::BaseShip::BaseShip() 
		: m_cells(1) , m_facing(sbat::ShipFacing::UP) , m_position(sf::Vector2i(0,0)), m_ship_type(sbat::ShipType::ONE)
	{

	}
	sbat::BaseShip::BaseShip(const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing, const sf::Vector2i& position)
		: m_ship_type(ship_type), m_cells(static_cast<std::size_t>(m_ship_type)), m_position(position), m_facing(ship_facing)
	{
		
	}

	//FACING
	void sbat::BaseShip::set_ship_facing(const sbat::ShipFacing& rotation)
	{
		this->m_facing = rotation;
	}
	const sbat::ShipFacing& sbat::BaseShip::get_ship_facing()const
	{
		return m_facing;
	}

	//SHIP TYPE
	void sbat::BaseShip::set_ship_type(const sbat::ShipType& type)
	{
		this->m_cells.resize(static_cast<int>(type));
		this->m_ship_type = type;
	}
	const sbat::ShipType& sbat::BaseShip::get_ship_type()const
	{
		return this->m_ship_type;
	}

	//SHIP CELL STATE
	//void sbat::BaseShip::set_cell_state(const sbat::ShipCellPosition& position, const sbat::ShipCellState& cell_state)
	//{
	//	if (static_cast<int>(position) >= 0 && static_cast<int>(position) < m_cells.size())
	//	{
	//		this->m_cells[static_cast<int>(position)] = cell_state;
	//	}
	//}

	void sbat::BaseShip::explode(const sbat::ShipCellPosition& position)
	{
		if (static_cast<int>(position) >= 0 && static_cast<int>(position) < m_cells.size())
		{
			this->m_cells[static_cast<int>(position)] = sbat::ShipCellState::EXPLODED;
		}
	}

	const sbat::ShipCellState& sbat::BaseShip::get_cell_state(const sbat::ShipCellPosition& position)const
	{
		if (static_cast<int>(position) >= 0 && static_cast<int>(position) <= 4)
		{
			return  m_cells[static_cast<int>(position)];
		}
		else
			throw std::out_of_range("sbat::BaseShip::get_cell_state() , out of range");
		
	}

	//FIELD POSITION
	void sbat::BaseShip::set_field_position(const sf::Vector2i& position)//main
	{
		this->m_position = position;
	}

	void sbat::BaseShip::set_field_position(const int& x, const int& y)
	{
		this->set_field_position(sf::Vector2i(x, y));
	}

	const sf::Vector2i& sbat::BaseShip::get_field_position()const
	{
		return this->m_position;
	}



	sbat::BaseShip::~BaseShip()
	{

	}


	//OPERATORS

	bool operator==(const sbat::BaseShip& left, const sbat::BaseShip& right)
	{
		if (left.m_ship_type == right.m_ship_type)
			return 1;
		return 0;
	}
	bool operator<(const sbat::BaseShip& left, const sbat::BaseShip& right)
	{
		if (static_cast<int>(left.m_ship_type) < static_cast<int>(right.m_ship_type))
			return 1;
		return 0;
	}
}