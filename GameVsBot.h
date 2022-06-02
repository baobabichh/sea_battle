#ifndef SBAT_GAMEVSBOT_H
#define SBAT_GAMEVSBOT_H

#include "DrawShipField.h"
#include "ShipFieldConstructor.h"
#include "GameBase.h"
#include "TextButton.h"
#include "DrawShipFieldFriend.h"
#include "DrawShipFieldEnemy.h"
#include "BotRandom.h"
#include "ScaleTextButton.h"
#include "GameRecorder.h"


namespace sbat
{

	


	class GameVsBot
		:
		public sbat::GameBase
	{


	public:
		GameVsBot();
		virtual~GameVsBot();

		void init() override;

		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr) override ;

		bool finished()const override;

		GameRecord* get_record()const override;


	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


		enum class GameState
		{
			CONSTRUCTING,
			PLAYING,
			END,
			FINISHED,
		};

		enum class Turn
		{
			MY,
			BOT,
		};

		int m_button_distance;

		sbat::DrawShipFieldEnemy m_field_enemy;
		sbat::DrawShipFieldFriend m_field_friend;

		sbat::ShipFieldConstructor m_field_constructor;

		std::unordered_map<std::string, ScaleTextButton> m_constructor_buttons;

		BotRandom m_bot;

		GameState m_game_state;
		Turn m_turn;

		TextButton m_turn_text;

		sf::Text m_you_win_text , m_bot_text , m_player_text;

		std::list < sbat::Animation> m_ending_firework_anim;
		int m_ending_anim_max;

		GameRecorder m_game_recorder;

		void update_constructing(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr);
		void update_playing(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr);
		void update_ending(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr);

		void draw_constructing(sf::RenderTarget& target, sf::RenderStates states)const;
		void draw_playing(sf::RenderTarget& target, sf::RenderStates states)const;
		void draw_ending(sf::RenderTarget& target, sf::RenderStates states)const;

		void init_ending(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr);

	};




}


#endif // !SBAT_GAMEVSBOT_H

