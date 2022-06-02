#include "GameRecorder.h"

namespace sbat
{
	GameRecorder::GameRecorder()
		:
		m_finished(0)
	{
		m_record = new GameRecord;
	}

	GameRecorder::~GameRecorder()
	{

	}


	void GameRecorder::set_names(const std::wstring& left_name, const std::wstring& right_name)
	{
		m_record->m_left_name = left_name;
		m_record->m_right_name = right_name;
	}

	void GameRecorder::add_move(const GameTurn& turn, const sf::Vector2i& move)
	{
		if (!m_finished)
			m_record->m_game_moves.push_front(std::make_pair(turn, move));
	}
	
	void GameRecorder::set_fields(const std::unordered_map < sf::Vector2i, sbat::BaseShip, sbat::Vector2Ihash>& left_ships,
		const std::unordered_map < sf::Vector2i, sbat::BaseShip, sbat::Vector2Ihash>& right_ships)
	{
		for (auto& it : left_ships)
		{
			m_record->m_left_ships[it.first] = it.second;
		}

		for (auto& it : right_ships)
		{
			m_record->m_right_ships[it.first] = it.second;
		}

	}

	void  GameRecorder::finish()
	{
		m_finished = 1;
		std::reverse(m_record->m_game_moves.begin(), m_record->m_game_moves.end());
	}

	GameRecord* GameRecorder::get_record()const
	{
		return m_record;
	}


}