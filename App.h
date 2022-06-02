#ifndef SBAT_APP_H
#define SBAT_APP_H

#include "GameVsBot.h"
#include "Background.h"
#include "SFML/Graphics/Shader.hpp"
#include <math.h>
#include <chrono>
#include <ctime>
#include "RecordViewer.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//SETUP

namespace sbat
{
	class App;
	class AppStateFunc
	{
	public:
		void draw( App * app)
		{
			(*app.*m_draw)();
		}
		void update(App* app)
		{
			(*app.*m_update)();
		}
		void init(App* app)
		{
			(*app.*m_init)();
		}
		void destroy(App* app)
		{
			(*app.*m_destroy)();
		}
		void set_update(void (App::* val)())
		{
			m_update = val;
		}
		void set_draw(void (App::* val)())
		{
			m_draw = val;
		}
		void set_init(void (App::* val)())
		{
			m_init = val;
		}
		void set_destroy(void (App::* val)())
		{
			m_destroy = val;
		}
	private:
		void (App::*m_init)();
		void (App::*m_update)();
		void (App::*m_draw)();
		void (App::*m_destroy)();
	};

}

namespace sbat
{

	class App
	{
	public:

		App();
		virtual ~App();

		void render();

	private:

		void create_window();

		void update();
		void draw();

		//==========================================================================================================================================
		//App states

		//main menu 
		void state_main_menu_init();
		void state_main_menu_update();
		void state_main_menu_draw();
		void state_main_menu_destroy();

		//game vs bot
		void state_game_vs_bot_init();
		void state_game_vs_bot_update();
		void state_game_vs_bot_draw();
		void state_game_vs_bot_destroy();

		//record_viewer
		void state_record_view_init();
		void state_record_view_update();
		void state_record_view_draw();
		void state_record_view_destroy();

		//==========================================================================================================================================
		//Debug
		void debug_draw();

		//help

		void save_replay(GameRecord * rec);

	private:

		enum class AppState
		{
			NONE,
			MAIN_MENU,
			GAME_VS_BOT,
			RECORD_VIEW,

			COUNT,
		};

		//============================================================================================================================================
		//WINDOW

		sf::RenderWindow m_window;
		sf::Vector2u m_window_size;
		std::wstring m_window_name;
		unsigned int m_window_frame_rate_limit;
		float m_dt , m_all_dt;
		sf::Event m_event;
		sf::Clock m_clock;

		//============================================================================================================================================
		//APP STATE

		AppState m_app_state , m_app_state_prev;
		std::unordered_map<AppState, AppStateFunc> m_app_state_methods;

		//============================================================================================================================================
		//BACKGROUND

		Background m_main_menu_background;
		sf::Sprite m_game_vs_bot_backround;
		sf::Shader m_game_vs_bot_backround_shader;
		sf::Texture m_game_vs_bot_backround_texture;

		//============================================================================================================================================
		//MAIN MENU

		std::unordered_map<std::string, BaseButton* > m_main_menu;

		//============================================================================================================================================
		//GameVsBot

		GameVsBot* m_game_vs_bot;
		ScaleTextButton* m_game_vs_bot_exit_button ,* m_game_vs_bot_save_replay_button;

		//============================================================================================================================================
		//RecorViever

		RecordViewer* m_record_view_record_viewer;

		//============================================================================================================================================
		//Debug things
		sf::Text m_debug_fps;
		bool m_debug_should_draw_fps;


	};






}


#endif // !SBAT_APP_H
