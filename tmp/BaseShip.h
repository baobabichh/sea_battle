#ifndef BASESHIP_H
#define BASESHIP_H

#include <SFML/Graphics.hpp>
#include "Comparable.h"
#include <stdexcept>

namespace sbat
{
	enum class ShipType : int
	{
		ONE=1,
		TWO=2,
		TREE=3,
		FOUR=4,
	};

	enum class ShipFacing : int
	{
		RIGHT,
		DOWN,
		LEFT,
		UP,
	};

	enum class ShipCellPosition : int       //[0][1][2][3]
	{										//[1]
		FIRST=0	,							//[2]
		SECOND=1,							//[3]
		THIRD=2,
		FOURTH=3,

	};
	

	enum class ShipCellState : int
	{
		DEFAULT,
		HIDEN,
		EXPLODED,
	};



	
	class BaseShip : public sbat::Comparable<BaseShip>
	{
	public:

		BaseShip();
		BaseShip(const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing, const sf::Vector2i& position);

		//VIRTUAL
		virtual void set_ship_facing(const sbat::ShipFacing& rotation);
		virtual void set_ship_type(const sbat::ShipType& type);
		//virtual void set_cell_state(const sbat::ShipCellPosition& position, const sbat::ShipCellState& cell_state);
		virtual void explode(const sbat::ShipCellPosition& position);
		virtual void set_field_position(const sf::Vector2i& position);//main


		//FACING
		const sbat::ShipFacing& get_ship_facing()const;

		//SHIP TYPE
		const sbat::ShipType& get_ship_type()const;

		//SHIP CELL STATE
		const sbat::ShipCellState & get_cell_state(const sbat::ShipCellPosition& position)const;

		//FIELD POSITION
		void set_field_position(const int& x, const int& y);
		const sf::Vector2i& get_field_position()const;

		//DESTRUCTOR
		virtual ~BaseShip();

		//OPERATOR

		friend bool operator==(const sbat::BaseShip& left, const sbat::BaseShip& right);
		friend bool operator<(const sbat::BaseShip& left, const sbat::BaseShip& right);

	private:

		sf::Vector2i m_position;
		sbat::ShipFacing m_facing;
		sbat::ShipType m_ship_type;
		std::vector<sbat::ShipCellState> m_cells;

	};

}


#endif // !BASESHIP_H

