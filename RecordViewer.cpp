#include "RecordViewer.h"

namespace sbat
{


	RecordViewer::RecordViewer()
		:
		m_record(nullptr),
		m_curr_step(-1),
		m_could_be_closed(0)

	{

	

		m_selected_cell.setOutlineThickness(3);
		m_selected_cell.setOutlineColor(sf::Color::Green);
		m_selected_cell.setFillColor(sf::Color::Transparent);

		m_left_name.setFont(GameResources::get_font(DEFAULT_FONT));
		apply_style_text(m_left_name, GameStyles::TextStyles.DefaultText);

		m_right_name.setFont(GameResources::get_font(DEFAULT_FONT));
		apply_style_text(m_right_name, GameStyles::TextStyles.DefaultText);

		m_left_field.init();
		
		m_right_field.init();


		m_left_field.set_cell_size(42);
		m_left_field.set_position(100, 100);

		m_right_field.set_cell_size(42);
		m_right_field.set_position
		(
			m_left_field.get_global_bounds().left + m_left_field.get_global_bounds().width + 100,
			m_left_field.get_global_bounds().top
		);



		m_button_prev.init();
		m_button_prev.set_string(L"Previous step");
		m_button_prev.set_position
		(
			m_left_field.get_global_bounds().left,
			m_left_field.get_global_bounds().top + m_left_field.get_global_bounds().height + 20.f
		);

		m_button_next.init();
		m_button_next.set_string(L"Next step");
		m_button_next.set_position
		(
			m_button_prev.get_global_bounds().left + m_button_prev.get_global_bounds().width + 20,
			m_button_prev.get_position().y
		);

		m_button_exit.init();
		m_button_exit.set_string(L"Exit");
		m_button_exit.set_position
		(
			m_button_next.get_global_bounds().left + m_button_next.get_global_bounds().width + 20,
			m_button_prev.get_position().y	
		);

		m_text_current_file.setFont(GameResources::get_font(DEFAULT_FONT));
		auto text_style =GameStyles::TextStyles.DefaultText;
		text_style.character_size = 19;
		text_style.fill_color = sf::Color::Green;
		apply_style_text(m_text_current_file, text_style);
		m_text_current_file.setPosition(m_right_field.get_global_bounds().left, m_right_field.get_global_bounds().top + m_right_field.get_global_bounds().height + 20);

		m_button_prev_file.init();
		m_button_prev_file.set_string(L"Prev file");
		m_button_prev_file.set_position
		(
			m_text_current_file.getGlobalBounds().left,
			m_text_current_file.getGlobalBounds().top + m_text_current_file.getGlobalBounds().height + 40
		);

		m_button_next_file.init();
		m_button_next_file.set_string(L"Next file");
		m_button_next_file.set_position
		(
			m_button_prev_file.get_position().x + m_button_prev_file.get_global_bounds().width + 20.f,
			m_button_prev_file.get_position().y
		);
		


		

		search_first_file();
	}

	RecordViewer::~RecordViewer()
	{
		if (m_record)
			delete m_record;
	}

	void RecordViewer::set_record(GameRecord* record)
	{

		m_curr_step = 0;

		m_selected_cell.setPosition(-100, -100);
		m_record = record;
		
		m_left_field.clear();
		m_right_field.clear();

		for (auto& it : record->m_left_ships)
		{
			m_left_field.add_ship(it.first, it.second.get_ship_type(), it.second.get_ship_facing());
		}
		
		for (auto& it : record->m_right_ships)
		{
			m_right_field.add_ship(it.first, it.second.get_ship_type(), it.second.get_ship_facing());
		}
		
	
		m_left_name.setString(m_record->m_left_name);
		m_left_name.setPosition(m_left_field.get_position().x, (m_left_field.get_position().y - m_left_name.getGlobalBounds().height) - 20);

		m_right_name.setString(m_record->m_right_name);
		m_right_name.setPosition(m_right_field.get_position().x, (m_right_field.get_position().y - m_right_name.getGlobalBounds().height) - 20);



	}

	void RecordViewer::next_step()
	{
		if (m_curr_step < (int)m_record->m_game_moves.size())
		{
			m_curr_step++;
			int q = 0;
			for (auto& it : m_record->m_game_moves)
			{
				if (q == m_curr_step)
				{
					if (it.first == GameTurn::LEFT)
					{
						m_left_field.shoot(it.second);
						m_selected_cell.setPosition(sf::Vector2f(m_left_field.get_cell_global_bounds(it.second).left, m_left_field.get_cell_global_bounds(it.second).top));
						m_selected_cell.setSize(sf::Vector2f(m_left_field.get_cell_global_bounds(it.second).width, m_left_field.get_cell_global_bounds(it.second).height));
					}
					else if (it.first == GameTurn::RIGHT)
					{
						m_right_field.shoot(it.second);
						m_selected_cell.setPosition(sf::Vector2f(m_right_field.get_cell_global_bounds(it.second).left, m_right_field.get_cell_global_bounds(it.second).top));
						m_selected_cell.setSize(sf::Vector2f(m_right_field.get_cell_global_bounds(it.second).width, m_right_field.get_cell_global_bounds(it.second).height));
					}

					break;
				}
				q++;
			}
		}
		
	}

	void RecordViewer::previous_step()
	{
		if (m_curr_step > 0)
		{
			m_curr_step--;
			m_left_field.clear();
			m_right_field.clear();
			for (auto& it : m_record->m_left_ships)
			{
				m_left_field.add_ship(it.first, it.second.get_ship_type(), it.second.get_ship_facing());
			}

			for (auto& it : m_record->m_right_ships)
			{
				m_right_field.add_ship(it.first, it.second.get_ship_type(), it.second.get_ship_facing());
			}

			for (int i = 0; i <= m_curr_step; i++)
			{
				int q = 0;
				for (const auto& it : m_record->m_game_moves)
				{
					if (q == i)
					{
						if (it.first == GameTurn::LEFT)
						{
							m_left_field.shoot_with_final_anim(it.second);
							m_selected_cell.setPosition(sf::Vector2f(m_left_field.get_cell_global_bounds(it.second).left, m_left_field.get_cell_global_bounds(it.second).top));
							m_selected_cell.setSize(sf::Vector2f(m_left_field.get_cell_global_bounds(it.second).width, m_left_field.get_cell_global_bounds(it.second).height));
						}
						else if (it.first == GameTurn::RIGHT)
						{
							m_right_field.shoot_with_final_anim(it.second);
							m_selected_cell.setPosition(sf::Vector2f(m_right_field.get_cell_global_bounds(it.second).left, m_right_field.get_cell_global_bounds(it.second).top));
							m_selected_cell.setSize(sf::Vector2f(m_right_field.get_cell_global_bounds(it.second).width, m_right_field.get_cell_global_bounds(it.second).height));
						}
						
						break;
					}
					q++;
				}
			}
			
		}

	}


	void RecordViewer::update(sf::RenderWindow& window, const float& dt, const sf::Event* event)
	{


		if (event->type == sf::Event::KeyPressed)
		{
			if (event->key.code == sf::Keyboard::Right)
				this->next_step();
			else if (event->key.code == sf::Keyboard::Left)
				this->previous_step();
			else if (event->key.code == sf::Keyboard::Up)
				this->search_next_file();
			else if (event->key.code == sf::Keyboard::Down)
				this->search_prev_file();
			else if (event->key.code == sf::Keyboard::Q)
			{
				this->finished();
			}
				
		}
		if (m_button_prev_file.clicked(window, *event))
		{
			search_prev_file();
		}
		else if (m_button_next_file.clicked(window, *event))
		{
			search_next_file();
		}
		else if (m_button_exit.clicked(window, *event))
		{
			m_could_be_closed = 1;
		}
		else if (m_button_next.clicked(window, *event))
		{
			this->next_step();
		}
		else if (m_button_prev.clicked(window, *event))
		{
			this->previous_step();
		}

		m_button_exit.update(window, dt, event);
		m_button_next.update(window, dt, event);
		m_button_prev.update(window, dt, event);
		m_button_prev_file.update(window, dt, event);
		m_button_next_file.update(window, dt, event);

		m_left_field.update(window, dt, event);
		m_right_field.update(window, dt, event);


	}

	void RecordViewer::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_left_name,states);
		target.draw(m_right_name, states);

		target.draw(m_left_field, states);
		target.draw(m_right_field, states);

		target.draw(m_button_exit, states);
		target.draw(m_button_next, states);
		target.draw(m_button_prev, states);
		target.draw(m_selected_cell, states);

		target.draw(m_button_next_file, states);
		target.draw(m_button_prev_file, states);
		target.draw(m_text_current_file, states);
	}

	bool RecordViewer::finished()
	{
		return m_could_be_closed;
	}


	void RecordViewer::search_first_file()
	{
		namespace fs = std::filesystem;

		m_file_exist = 0;

		std::wstring path = DEFAULT_REPLAY_PATH;
		for (const auto& entry : fs::directory_iterator(path))
		{
			m_current_file = entry.path();
			m_file_exist = 1;
			break;
		}
		
		if (m_record)
			delete m_record;

		GameRecord * tmp_rec = new GameRecord();

		if (m_file_exist)
		{
			auto tmp = (m_current_file.substr(m_current_file.rfind(L"/")+1, m_current_file.length() - m_current_file.rfind(L"/")));
			tmp = L"Current replay : " + tmp;
			m_text_current_file.setString(tmp);
			tmp_rec->from_file(m_current_file);
			set_record(tmp_rec);
		}
		else
		{
			auto tmp = L"Current replay : no replay" ;
			m_text_current_file.setString(tmp);
		}

	}

	void RecordViewer::search_next_file()
	{
		namespace fs = std::filesystem;

		m_file_exist = 0;

		std::wstring path = DEFAULT_REPLAY_PATH;
		bool next_is_result = 0, got_result = 0;
		for (const auto& entry : fs::directory_iterator(path))
		{
			if (m_current_file == entry.path())
			{
				next_is_result = 1;
			}
			else if (next_is_result)
			{
				got_result = 1;
				m_current_file = entry.path();
				break;
			}
		}

		if (!got_result)
		{
			for (const auto& entry : fs::directory_iterator(path))
			{
				m_current_file = entry.path();
				got_result = 1;
				break;
			}
		}

		if (m_record)
			delete m_record;

		GameRecord *tmp_rec = new GameRecord();

		if (got_result)
		{
			auto tmp = (m_current_file.substr(m_current_file.rfind(L"/") + 1, m_current_file.length() - m_current_file.rfind(L"/")));
			tmp = L"Current replay : " + tmp;
			m_text_current_file.setString(tmp);
			tmp_rec->from_file(m_current_file);
			set_record(tmp_rec);
		}
		else
		{
			auto tmp = L"Current replay : no replay";
			m_text_current_file.setString(tmp);

		}


	}

	void RecordViewer::search_prev_file()
	{
		namespace fs = std::filesystem;

		namespace fs = std::filesystem;

		m_file_exist = 0;

		std::wstring path = DEFAULT_REPLAY_PATH, last_path , prev_path=L"NULL";
		bool  got_result = 0;
		for (const auto& entry : fs::directory_iterator(path))
		{
			last_path = entry.path();
			if (m_current_file == entry.path())
			{
				if (prev_path != L"NULL")
				{
					m_current_file = prev_path;
					got_result = 1;
				}
			}
			prev_path = entry.path();
		}

		if (!got_result)
		{
			m_current_file = last_path;
			got_result = 1;
		}

		if (m_record)
			delete m_record;

		GameRecord* tmp_rec = new GameRecord();

		if (got_result)
		{
			auto tmp = (m_current_file.substr(m_current_file.rfind(L"/") + 1, m_current_file.length() - m_current_file.rfind(L"/")));
			tmp = L"Current replay : " + tmp;
			m_text_current_file.setString(tmp);
			tmp_rec->from_file(m_current_file);
			set_record(tmp_rec);
		}
		else
		{
			auto tmp = L"Current replay : no replay";
			m_text_current_file.setString(tmp);

		}



	}

}