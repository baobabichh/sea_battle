#include "GameVsBot.h"

namespace sbat
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GameVsBot::GameVsBot()
		:
		m_game_state(GameState::CONSTRUCTING),
		m_button_distance(20),
		m_ending_anim_max(100)
	{
		m_bot.set_field(&m_field_friend);

		

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GameVsBot::~GameVsBot()
	{

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameVsBot::init()
	{

		m_constructor_buttons["GENERATE_SHIPS"];
		m_constructor_buttons["ROTATE_SHIP"];
		m_constructor_buttons["SUBMIT_SHIPS"];

		for (auto& it : m_constructor_buttons)
		{
			it.second.init();
		}
		m_field_constructor.init();
		m_field_enemy.init();
		m_field_friend.init();


		//fields

		m_field_friend.set_cell_size(42);
		m_field_friend.set_position(100, 100);

		m_field_enemy.set_cell_size(42);
		m_field_enemy.set_position
		(
			m_field_friend.get_global_bounds().left + m_field_friend.get_global_bounds().width + 100,
			m_field_friend.get_global_bounds().top
		);



		m_field_constructor.set_cell_size(50);
		m_field_constructor.set_position(100,100);


		m_field_constructor.random();

		//BUTTONS


		m_constructor_buttons["SUBMIT_SHIPS"].set_string(L"Submit");
		m_constructor_buttons["SUBMIT_SHIPS"].set_position
		(
			m_field_constructor.get_global_bounds().left + m_field_constructor.get_global_bounds().width + m_button_distance,
			m_field_constructor.get_global_bounds().top
		);

		m_constructor_buttons["ROTATE_SHIP"].set_string(L"Rotate");
		m_constructor_buttons["ROTATE_SHIP"].set_position
		(
			m_constructor_buttons["SUBMIT_SHIPS"].get_global_bounds().left,
			m_constructor_buttons["SUBMIT_SHIPS"].get_global_bounds().top + m_constructor_buttons["SUBMIT_SHIPS"].get_global_bounds().height + m_button_distance
		);

		m_constructor_buttons["GENERATE_SHIPS"].set_string(L"Generate field");
		m_constructor_buttons["GENERATE_SHIPS"].set_position
		(
			m_constructor_buttons["ROTATE_SHIP"].get_global_bounds().left,
			m_constructor_buttons["ROTATE_SHIP"].get_global_bounds().top + m_constructor_buttons["ROTATE_SHIP"].get_global_bounds().height + m_button_distance
		);

		//TEXT

		m_you_win_text.setFont(GameResources::get_font(DEFAULT_FONT));
		sbat::apply_style_text(m_you_win_text, GameStyles::TextStyles.YouWin);

		m_bot_text.setFont(GameResources::get_font(DEFAULT_FONT));
		sbat::apply_style_text(m_bot_text, GameStyles::TextStyles.DefaultText);
		m_bot_text.setString(L"Бот");
		m_bot_text.setPosition(m_field_enemy.get_position().x, (m_field_enemy.get_position().y - m_bot_text.getGlobalBounds().height) - 20);

		m_player_text.setFont(GameResources::get_font(DEFAULT_FONT));
		sbat::apply_style_text(m_player_text, GameStyles::TextStyles.DefaultText);
		m_player_text.setString(L"Игрок");
		m_player_text.setPosition(m_field_friend.get_position().x, (m_field_friend.get_position().y - m_player_text.getGlobalBounds().height) - 20);

		//turn

		m_turn_text.init();
		m_turn_text.set_style(sbat::TextStyle(24, 2, sf::Text::Bold, sf::Color::Red, sf::Color::Yellow));
		m_turn_text.set_position(1000, 0);
		if (m_turn == Turn::MY)
			m_turn_text.set_string(L"Игрок ходит");
		else if (m_turn == Turn::BOT)
			m_turn_text.set_string(L"Бот ходит");

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool GameVsBot::finished()const
	{
		if (m_game_state == GameState::FINISHED || m_game_state == GameState::END)
			return 1;
		return 0;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameVsBot::update_constructing(sf::RenderWindow& window, const float& dt, const sf::Event* event )
	{
		if (m_constructor_buttons["ROTATE_SHIP"].clicked(window, *event))
		{
			m_field_constructor.rotate_ship();
		}
		if (m_constructor_buttons["SUBMIT_SHIPS"].clicked(window, *event))
		{
			m_field_friend.copy_ships(m_field_constructor);

			sbat::ShipFieldConstructor tmp;
			tmp.init();
			tmp.random();
			
			m_field_enemy.copy_ships(tmp);

			m_game_recorder.set_names(L"Player", L"Bot");

			std::unordered_map < sf::Vector2i, BaseShip, Vector2Ihash > tmp_ships_friend , tmp_ships_enemy;
			for (auto& it : m_field_friend.get_ships())
			{
				tmp_ships_friend[it.first] = *dynamic_cast<BaseShip*>(it.second);
			}
			for (auto& it : m_field_enemy.get_ships())
			{
				tmp_ships_enemy[it.first] = *dynamic_cast<BaseShip*>(it.second);
			}

			m_game_recorder.set_fields(tmp_ships_friend, tmp_ships_enemy);

			m_game_state = GameState::PLAYING;
		}
		if (m_constructor_buttons["GENERATE_SHIPS"].clicked(window, *event))
		{
			m_field_constructor.random();
		}

		m_field_constructor.update(window, dt, event);
		for (auto& it : m_constructor_buttons)
		{
			it.second.update(window, dt, event);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameVsBot::update_playing(sf::RenderWindow& window, const float& dt, const sf::Event* event )
	{
		if (event->type == sf::Event::KeyReleased)
		{
			if (event->key.code == sf::Keyboard::F3)
			{
				m_game_state = GameState::END;
				init_ending(window, dt, event);
				return;
			}
		}

		if (m_field_enemy.all_ships_exploded() || m_field_friend.all_ships_exploded() )
		{
			m_game_state = GameState::END;
			init_ending(window, dt, event);
			return;
		}

		if (m_turn == Turn::MY)
			m_turn_text.set_string(L"Игрок ходит");
		else if (m_turn == Turn::BOT)
			m_turn_text.set_string(L"Бот ходит");

		if (m_turn == Turn::MY)
		{
			m_field_enemy.set_style(sbat::GameStyles::DrawFieldStyles.UnderAttack);
			m_field_friend.set_style(sbat::GameStyles::DrawFieldStyles.Attacking);
		}
		else if (m_turn == Turn::BOT)
		{
			m_field_enemy.set_style(sbat::GameStyles::DrawFieldStyles.Attacking);
			m_field_friend.set_style(sbat::GameStyles::DrawFieldStyles.UnderAttack);
		}

		if (m_turn == Turn::MY)
		{
			for (int i = 0; i < m_field_enemy.get_field_size().x; i++)
			{
				for (int j = 0; j < m_field_enemy.get_field_size().y; j++)
				{

					if (m_field_enemy.get_cell_global_bounds(i, j).contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
					{
						if (event->type == sf::Event::MouseButtonReleased && event->mouseButton.button == sf::Mouse::Left)
						{
							auto val = m_field_enemy.get_cell_state(sf::Vector2i(i, j));
							if (val == FieldCellState::NOTHING || val == FieldCellState::SHIP)
							{
								m_field_enemy.shoot(sf::Vector2i(i, j));
								m_game_recorder.add_move(GameTurn::RIGHT, sf::Vector2i(i, j));
								if (m_field_enemy.get_cell_state(sf::Vector2i(i, j)) == FieldCellState::SHIP_EXPLODED)
								{
									m_turn = Turn::MY;
								}
								else
								{
									m_turn = Turn::BOT;
								}
							}
						}
					}
				}
			}
		}
		else if(m_turn == Turn::BOT)
		{
			if (m_bot.delayed())
			{
				auto move = m_bot.make_move();
				m_game_recorder.add_move(GameTurn::LEFT, move);
				if (m_field_friend.get_cell_state(move) == FieldCellState::SHIP_EXPLODED)
				{
					m_turn = Turn::BOT;
				}
				else
				{
					m_turn = Turn::MY;
				}
			}
			m_bot.update(window, dt, event);
		}

		m_field_enemy.update(window, dt, event);
		m_field_friend.update(window, dt, event);
		

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameVsBot::update_ending(sf::RenderWindow& window, const float& dt, const sf::Event* event )
	{
		std::vector<std::list<Animation>::iterator> needs_delete;

		if (m_ending_firework_anim.size() < m_ending_anim_max)
		{
			if (Random::rand(0, 3))
			{
				m_ending_firework_anim.push_front(GameResources::get_animation("FIREWORK_1"));
				m_ending_firework_anim.begin()->set_position
				(
					Random::rand(0 - static_cast<int>(m_ending_firework_anim.begin()->get_local_bounds().width), static_cast<int>(window.getSize().x)),
					Random::rand(0 - static_cast<int>(m_ending_firework_anim.begin()->get_local_bounds().height), static_cast<int>(window.getSize().y))
				);
				m_ending_firework_anim.begin()->play();
			}

		}

		for(auto & it : m_ending_firework_anim)
			it.update(window, dt, event);

		for (auto it = m_ending_firework_anim.begin(); it != m_ending_firework_anim.end(); it++)
		{
			if (it->ended())
			{
				needs_delete.push_back(it);
			}
			
		}

		for (auto& it : needs_delete)
			m_ending_firework_anim.erase(it);


		m_field_enemy.update(window, dt, event);
		m_field_friend.update(window, dt, event);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameVsBot::draw_constructing(sf::RenderTarget& target, sf::RenderStates states)const
	{
		for (auto& it : m_constructor_buttons)
			target.draw(it.second, states);
		target.draw(m_field_constructor, states);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameVsBot::draw_playing(sf::RenderTarget& target, sf::RenderStates states)const
	{
		target.draw(m_turn_text , states);
		target.draw(m_field_enemy, states);
		target.draw(m_field_friend, states);
		target.draw(m_player_text, states);
		target.draw(m_bot_text, states);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameVsBot::draw_ending(sf::RenderTarget& target, sf::RenderStates states)const
	{
		
		target.draw(m_field_enemy, states);
		target.draw(m_field_friend, states);
		target.draw(m_player_text, states);
		target.draw(m_bot_text, states);
		for (auto& it : m_ending_firework_anim)
		{
			target.draw(it, states);
		}
		target.draw(m_you_win_text, states);

		
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameVsBot::update(sf::RenderWindow& window, const float& dt, const sf::Event* event )
	{
		switch (m_game_state)
		{
		case GameState::CONSTRUCTING:
			this->update_constructing(window, dt, event);
			break;
		case GameState::PLAYING:
			this->update_playing(window, dt, event);
			break;
		case GameState::END:
			this->update_ending(window, dt, event);
			break;
		default:
			break;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameVsBot::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		switch (m_game_state)
		{
		case GameState::CONSTRUCTING :
			this->draw_constructing(target, states);
			break;
		case GameState::PLAYING:
			this->draw_playing(target, states);
			break;
		case GameState::END:
			this->draw_ending(target, states);
			break;
		default:
			break;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void GameVsBot::init_ending(sf::RenderWindow& window, const float& dt, const sf::Event* event )
	{
		float dist=10.f;

		m_game_recorder.finish();

		if (m_turn == Turn::MY)
			m_you_win_text.setString(L"Победил игрок");
		else if (m_turn == Turn::BOT)
			m_you_win_text.setString(L"Победил бот");

		auto val = (static_cast<float>(window.getSize().x)-dist*2.f) / m_you_win_text.getGlobalBounds().width;
		m_you_win_text.scale
		(
			val,
			val
		);
		m_you_win_text.setPosition(dist, static_cast<float>(window.getSize().y) / 2.f - m_you_win_text.getGlobalBounds().height / 2.f);


	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	GameRecord* GameVsBot::get_record()const
	{
		return m_game_recorder.get_record();
	}
}