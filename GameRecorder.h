#ifndef SBAT_GAMERECORDER_H
#define SBAT_GAMERECORDER_H

#include "GameRecord.h"


namespace sbat
{


	class GameRecorder
	{
	public:
		GameRecorder();
		virtual ~GameRecorder();

		void set_names(const std::wstring& left_name, const std::wstring& right_name);
		void add_move(const GameTurn& turn, const sf::Vector2i& move);
		void set_fields(const std::unordered_map < sf::Vector2i, sbat::BaseShip, sbat::Vector2Ihash>& left_ships,
						const std::unordered_map < sf::Vector2i, sbat::BaseShip, sbat::Vector2Ihash>& right_ships);
		void finish();
		GameRecord* get_record()const;

	private:

		bool m_finished;
		GameRecord* m_record;

	};
}

#endif // !SBAT_GAMERECORDER_H

