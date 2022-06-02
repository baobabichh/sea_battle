#include "App.h"



namespace sbat
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	App::App()
		:
		m_app_state(AppState::MAIN_MENU),
		m_game_vs_bot_backround_shader()
	{
		//---------------------------------------------------------------------------------------------------------------------------------------------
		//window setup

		create_window();

		//---------------------------------------------------------------------------------------------------------------------------------------------
		//background

		m_game_vs_bot_backround.setTexture(GameResources::get_texture("GAME_BACKGROUND"));
		m_game_vs_bot_backround.setScale
		(
			((static_cast<float>(m_window.getSize().x) / m_game_vs_bot_backround.getGlobalBounds().width)),
			((static_cast<float>(m_window.getSize().x) / m_game_vs_bot_backround.getGlobalBounds().width))
		);
		m_game_vs_bot_backround.setScale
		(
			(m_game_vs_bot_backround.getGlobalBounds().width+80) / m_game_vs_bot_backround.getGlobalBounds().width,
			(m_game_vs_bot_backround.getGlobalBounds().height + 80) / m_game_vs_bot_backround.getGlobalBounds().height
		);
		//m_game_vs_bot_backround.scale(1.2f, 1.2f);
		m_game_vs_bot_backround.setOrigin(m_game_vs_bot_backround.getLocalBounds().width / 2.f, m_game_vs_bot_backround.getLocalBounds().height / 2.f);

		m_game_vs_bot_backround.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2);

		if (!m_game_vs_bot_backround_shader.loadFromFile("resources\\shaders\\example_001.frag", sf::Shader::Fragment))
		{
			std::cerr << "Error while shaders" << std::endl;
		}
		m_game_vs_bot_backround_shader.setUniform("time", 1.f);
		m_game_vs_bot_backround_shader.setUniform("currentTexture", sf::Shader::CurrentTexture);
		

		//---------------------------------------------------------------------------------------------------------------------------------------------
		//main menu setup

		m_main_menu["Play vs bot"] = new ScaleTextButton();
		dynamic_cast<ScaleTextButton*>(m_main_menu["Play vs bot"])->init();
		dynamic_cast<ScaleTextButton*>(m_main_menu["Play vs bot"])->set_position(100, 100);
		dynamic_cast<ScaleTextButton*>(m_main_menu["Play vs bot"])->set_string(L"Play with bot");

		m_main_menu["Record view"] = new ScaleTextButton();
		dynamic_cast<ScaleTextButton*>(m_main_menu["Record view"])->init();
		dynamic_cast<ScaleTextButton*>(m_main_menu["Record view"])->set_position(100, 200);
		dynamic_cast<ScaleTextButton*>(m_main_menu["Record view"])->set_string(L"Record view");

		m_main_menu["Exit"] = new ScaleTextButton();
		dynamic_cast<ScaleTextButton*>(m_main_menu["Exit"])->init();
		dynamic_cast<ScaleTextButton*>(m_main_menu["Exit"])->set_position(100, 300);
		dynamic_cast<ScaleTextButton*>(m_main_menu["Exit"])->set_string(L"Exit");

		//---------------------------------------------------------------------------------------------------------------------------------------------
		//app states

		m_app_state_methods[AppState::MAIN_MENU].set_init(&App::state_main_menu_init);
		m_app_state_methods[AppState::MAIN_MENU].set_update(&App::state_main_menu_update);
		m_app_state_methods[AppState::MAIN_MENU].set_draw(&App::state_main_menu_draw);
		m_app_state_methods[AppState::MAIN_MENU].set_destroy(&App::state_main_menu_destroy);

		m_app_state_methods[AppState::GAME_VS_BOT].set_init(&App::state_game_vs_bot_init);
		m_app_state_methods[AppState::GAME_VS_BOT].set_update(&App::state_game_vs_bot_update);
		m_app_state_methods[AppState::GAME_VS_BOT].set_draw(&App::state_game_vs_bot_draw);
		m_app_state_methods[AppState::GAME_VS_BOT].set_destroy(&App::state_game_vs_bot_destroy);

		m_app_state_methods[AppState::RECORD_VIEW].set_init(&App::state_record_view_init);
		m_app_state_methods[AppState::RECORD_VIEW].set_update(&App::state_record_view_update);
		m_app_state_methods[AppState::RECORD_VIEW].set_draw(&App::state_record_view_draw);
		m_app_state_methods[AppState::RECORD_VIEW].set_destroy(&App::state_record_view_destroy);


		//---------------------------------------------------------------------------------------------------------------------------------------------
		//debug
		m_debug_should_draw_fps = 0;
		m_debug_fps.setPosition(0, 0);
		m_debug_fps.setFont(GameResources::get_font(DEFAULT_FONT));
		apply_style_text(m_debug_fps, GameStyles::TextStyles.Default);

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	App::~App()
	{

	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void App::render()
	{
		while (m_window.isOpen())
		{
			m_dt = m_clock.restart().asSeconds();
			m_all_dt += m_dt ;
			if (m_window.pollEvent(m_event))
			{
				if (m_event.type == sf::Event::Closed)
				{
					m_window.close();
				}
				else if (m_event.type == sf::Event::KeyReleased)
				{
					if (m_event.key.code == sf::Keyboard::F1)
					{
						if (m_debug_should_draw_fps)
							m_debug_should_draw_fps = 0;
						else
							m_debug_should_draw_fps = 1;
					}
				}
			}
			else
			{
				m_event.type = static_cast<sf::Event::EventType>(sf::Event::EventType::Count + 1);
			}

			this->update();

			////////////////////////////////////////////////
			m_window.clear(sf::Color::Black);
			////////////////////////////////////////////////

			this->draw();
			debug_draw();

			////////////////////////////////////////////////
			m_window.display();
			////////////////////////////////////////////////

		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void App::update()
	{
		if (m_app_state == AppState::NONE)
		{
			return;
		}
		if (m_app_state_prev != m_app_state)
		{
			if (m_app_state_prev != AppState::NONE)
				m_app_state_methods[m_app_state_prev].destroy(this);
			m_app_state_methods[m_app_state].init(this);
		}

		m_app_state_prev = m_app_state;

		m_app_state_methods[m_app_state].update(this);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void App::draw()
	{
		if (m_app_state == AppState::NONE)
		{
			return;
		}
		m_app_state_methods[m_app_state_prev].draw(this);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void App::create_window()
	{
		m_window_size.x = 1280;
		m_window_size.y = 720;
		m_window_frame_rate_limit = 144;

		m_window.create(sf::VideoMode(m_window_size.x, m_window_size.y), m_window_name, sf::Style::Close | sf::Style::Titlebar);
		m_window.setFramerateLimit(m_window_frame_rate_limit);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void App::save_replay(GameRecord * rec)
	{
		time_t now = time(0);
		tm* ltm = new tm;
		localtime_s(ltm, &now);

		std::wstringstream path;
		path<< L"replays/replay_"
			<< ltm->tm_mday << L"."
			<< 1 + ltm->tm_mon << L"."
			<< 1900 + ltm->tm_year << L"_"
			<< 5 + ltm->tm_hour << L"."
			<< 30 + ltm->tm_min << L"."
			<< ltm->tm_sec << L".bin";

		std::wcout << "path = " << path.str() << std::endl;

		rec->to_file(path.str());
		
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//==========================================================================================================================================
	//App states

	//main menu 

	void App::state_main_menu_init()
	{


	}


	void App::state_main_menu_update()
	{
		m_main_menu_background.update(m_window, m_dt, &m_event);
		for (auto& it : m_main_menu)
			it.second->update(m_window, m_dt, &m_event);

		for (auto& it : m_main_menu)
		{
			if (it.second->clicked(m_window, m_event))
			{
				if (it.first == "Exit")
				{
					m_window.close();
				}
				else if (it.first == "Play vs bot")
				{
					m_app_state = AppState::GAME_VS_BOT;
				}
				else if (it.first == "Record view")
				{
					m_app_state = AppState::RECORD_VIEW;
				}
			}
		}
	}

	void App::state_main_menu_draw()
	{
		m_window.draw(m_main_menu_background);
		for (auto& it : m_main_menu)
			m_window.draw(*it.second);
	}

	void App::state_main_menu_destroy()
	{

	}

	//game vs bot

	void App::state_game_vs_bot_init()
	{
		m_game_vs_bot = new GameVsBot();		
		m_game_vs_bot->init();

		m_game_vs_bot_exit_button = new ScaleTextButton();
		m_game_vs_bot_exit_button->init();
		m_game_vs_bot_exit_button->set_string(L"Exit");
		auto style = GameStyles::TextStyles.Default;
		style.character_size = 50;
		m_game_vs_bot_exit_button->set_style(style);

		
		m_game_vs_bot_exit_button->set_position
		(
			(m_window.getSize().x - m_game_vs_bot_exit_button->get_global_bounds().width)-40,
			(m_window.getSize().y - m_game_vs_bot_exit_button->get_global_bounds().height)-40
		);

		m_game_vs_bot_save_replay_button = new ScaleTextButton();
		m_game_vs_bot_save_replay_button->init();
		m_game_vs_bot_save_replay_button->set_string(L"Save replay");
		m_game_vs_bot_save_replay_button->set_style(style);
		m_game_vs_bot_save_replay_button->set_position
		(
			(m_game_vs_bot_exit_button->get_global_bounds().left - m_game_vs_bot_save_replay_button->get_global_bounds().width) - 20.f,
			m_game_vs_bot_exit_button->get_position().y
		);

	}

	void App::state_game_vs_bot_update()
	{
		m_game_vs_bot_backround_shader.setUniform("time", m_all_dt * 0.02f);
		m_game_vs_bot->update(m_window, m_dt, &m_event);
		if (m_game_vs_bot->finished())
		{
			m_game_vs_bot_save_replay_button->update(m_window, m_dt, &m_event);
			m_game_vs_bot_exit_button->update(m_window, m_dt, &m_event);
			if (m_game_vs_bot_exit_button->clicked(m_window, m_event))
				m_app_state = AppState::MAIN_MENU;
			if (m_game_vs_bot_save_replay_button->clicked(m_window, m_event))
			{
				save_replay(m_game_vs_bot->get_record());
			}
		}
	}

	void App::state_game_vs_bot_draw()
	{
		m_window.draw(m_game_vs_bot_backround, &m_game_vs_bot_backround_shader);
		m_window.draw(*m_game_vs_bot);
		if (m_game_vs_bot->finished())
		{
			m_window.draw(*m_game_vs_bot_exit_button);
			m_window.draw(*m_game_vs_bot_save_replay_button);
		}
		m_window.draw(sbat::make_rect(sf::FloatRect(m_game_vs_bot_save_replay_button->get_position().x, m_game_vs_bot_save_replay_button->get_position().y,10.f,10.f)));
		m_window.draw(sbat::make_rect(sf::FloatRect(m_game_vs_bot_exit_button->get_position().x, m_game_vs_bot_exit_button->get_position().y,10.f,10.f)));
	}

	//record_viewer
	void App::state_record_view_init()
	{
		m_record_view_record_viewer = new RecordViewer();
	}
	void App::state_record_view_update()
	{
		m_record_view_record_viewer->update(m_window, m_dt, &m_event);
		if (m_record_view_record_viewer->finished())
		{
			m_app_state = AppState::MAIN_MENU;
		}
	}
	void App::state_record_view_draw()
	{
		m_game_vs_bot_backround_shader.setUniform("time", m_all_dt * 0.02f);
		m_window.draw(m_game_vs_bot_backround, &m_game_vs_bot_backround_shader);
		m_window.draw(*m_record_view_record_viewer);
	}
	void App::state_record_view_destroy()
	{
		delete m_record_view_record_viewer;
	}

	void App::state_game_vs_bot_destroy()
	{
		delete m_game_vs_bot->get_record();
		delete m_game_vs_bot_exit_button;
		delete m_game_vs_bot;
		delete m_game_vs_bot_save_replay_button;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//DEBUG

	void App::debug_draw()
	{
		if (m_debug_should_draw_fps)
		{
			std::stringstream tmp;
			tmp << 1.f / m_dt;
			m_debug_fps.setString(tmp.str());
			m_window.draw(m_debug_fps);
		}
	}
}