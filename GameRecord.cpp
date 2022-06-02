#include "GameRecord.h"

namespace sbat
{

	void GameRecord::to_file(const std::wstring& path)
	{
		std::ofstream file;
		file.open(path, std::ios::out |std::ios::binary);
		if (!file.is_open())
		{
			std::cout << "Bad file\n";
		}

		//names
		auto size = m_left_name.size();
		file.write((char*)( & size), sizeof(size));
		file.write((char*)(&m_left_name[0]), sizeof(wchar_t) * m_left_name.size());

		size = m_right_name.size();
		file.write((char*)&size, sizeof(size));
		file.write((char*)(&m_right_name[0]), sizeof(wchar_t) * m_right_name.size());

		//ships 10
		for (auto& it : m_left_ships)
		{
			file.write((char*)( & it.first), sizeof(it.first));
			it.second.to_binary(file);
		}
		for (auto& it : m_right_ships)
		{
			file.write((char*)( & it.first), sizeof(it.first));
			it.second.to_binary(file);
		}

		//moves
		size = m_game_moves.size();
		file.write((char*)( & size), sizeof(size));
		for (auto& it : m_game_moves)
		{
			file.write((char*)( & it.first), sizeof(it.first));
			file.write((char*)( & it.second), sizeof(it.second));
		}
		file.close();
	}
	void GameRecord::from_file(const std::wstring& path)
	{
		std::ifstream file;
		file.open(path, std::ios::in |std::ios::binary);
		if (!file.good())
		{
			std::cout << "BAD FILE\n";
			return;
		}
		//names
		size_t tmp_size;
		file.read((char*)( & tmp_size), sizeof(tmp_size));
		m_left_name.resize(tmp_size+1);
		file.read((char*)( & m_left_name[0]), tmp_size * sizeof(wchar_t));

		file.read((char*)( & tmp_size), sizeof(tmp_size));
		m_right_name.resize(tmp_size+1);
		file.read((char*)( & m_right_name[0]), tmp_size * sizeof(wchar_t));
		
		//ships 10
		for (int i = 0; i < 10; i++)
		{
			sf::Vector2i pos;
			file.read((char*)( & pos), sizeof(pos));
			m_left_ships[pos].from_binary(file);
		}
		for (int i = 0; i < 10; i++)
		{
			sf::Vector2i pos;
			file.read((char*)( & pos), sizeof(pos));
			m_right_ships[pos].from_binary(file);
		}

		//moves
		file.read((char*)( & tmp_size), sizeof(tmp_size));
		for (int i = 0; i < tmp_size; i++)
		{
			GameTurn turn;
			sf::Vector2i pos;
			file.read((char*)( & turn), sizeof(turn));
			file.read((char*)(& pos), sizeof(pos));
			m_game_moves.push_front(std::make_pair(turn, pos));
		}

		std::reverse(m_game_moves.begin(), m_game_moves.end());
		file.close();
	}


}