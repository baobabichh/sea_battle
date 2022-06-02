#ifndef SBAT_GAMERECORD_H
#define SBAT_GAMERECORD_H

#include <iostream>
#include "Animation.h"
#include <vector>
#include <list>
#include "BaseShip.h"
#include "DrawShipField.h"
#include <fstream>
#include <algorithm>
namespace sbat
{

	enum class GameTurn
	{
		LEFT,
		RIGHT
	};

	class GameRecord
	{
	public:

		friend class sbat::BaseShip;

		void to_file(const std::wstring& path);
		void from_file(const std::wstring& path);

		std::wstring m_left_name, m_right_name;
		std::list<std::pair <GameTurn, sf::Vector2i>> m_game_moves;
		std::unordered_map < sf::Vector2i, sbat::BaseShip, sbat::Vector2Ihash > m_left_ships;
		std::unordered_map < sf::Vector2i, sbat::BaseShip, sbat::Vector2Ihash > m_right_ships;
	};
}


#endif // !SBAT_GAMERECORD_H

