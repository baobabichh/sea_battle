#include "BaseShip.h"

namespace sbat
{

	sbat::BaseShip::BaseShip() 
		: m_cells(1) , m_facing(sbat::ShipFacing::UP) ,  m_ship_type(sbat::ShipType::ONE)
	{

	}
	sbat::BaseShip::BaseShip(const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing, const sf::Vector2i& position)
		: m_ship_type(ship_type), m_cells(static_cast<std::size_t>(m_ship_type)),  m_facing(ship_facing)
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

	bool sbat::BaseShip::ship_exploded()
	{
		for (auto&& it : m_cells)
		{
			if (it != sbat::ShipCellState::EXPLODED)
				return 0;
		}
		return 1;
	}






	sbat::BaseShip::~BaseShip()
	{

	}


	//OPERATORS

	bool sbat::BaseShip::operator==( const sbat::BaseShip& right)const
	{
		if (this->m_ship_type == right.m_ship_type)
			return 1;
		return 0;
	}
	bool sbat::BaseShip::operator<(const sbat::BaseShip& right)const
	{
		if (static_cast<int>(this->m_ship_type) < static_cast<int>(right.m_ship_type))
			return 1;
		return 0;
	}

	void sbat::BaseShip::to_binary(std::ofstream& out)const
	{
		out.write((char*)( & m_facing), sizeof(m_facing));
		out.write((char*)( & m_ship_type), sizeof(m_ship_type));

		out.write((char*)(m_cells.data()), sizeof(ShipCellState) * m_cells.size());
	}
	void sbat::BaseShip::from_binary(std::ifstream& in)
	{
		in.read((char*)( & m_facing), sizeof(m_facing));
		in.read((char*)( & m_ship_type), sizeof(m_ship_type));

		m_cells.clear();
		m_cells.resize(static_cast<size_t>(m_ship_type));
		for (int i = 0; i < m_cells.size(); i++)
		{
			in.read((char*)( & m_cells[i]), sizeof(ShipCellState));
		}
	}

}