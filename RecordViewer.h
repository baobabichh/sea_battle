#ifndef SBAT_RECORDVIEWER_H
#define SBAT_RECORDVIEWER_H
#include "DrawShipFieldFriend.h"
#include "GameRecord.h"
#include "ScaleTextButton.h"
#include <filesystem>

#define DEFAULT_REPLAY_PATH L"replays/"

namespace sbat
{

	class RecordViewer
		:
		public sbat::Updatable,
		public sf::Drawable
	{
		enum class State
		{
			SELECTING_FILE,
			VIEWING,

			COUNT
		};

	public:

		

		RecordViewer();
		~RecordViewer();

		

		void next_step();
		void previous_step();

		bool finished();

		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr) override;

		void search_first_file();
		void search_next_file();
		void search_prev_file();
	private:

		void set_record(GameRecord* record);

		bool m_file_exist;
		std::wstring m_current_file;

		sf::RectangleShape m_selected_cell;
		sf::Text m_left_name, m_right_name;
		DrawShipFieldFriend m_left_field, m_right_field;
		GameRecord* m_record;
		int m_curr_step;
		bool m_could_be_closed;

		State m_state;

		

		ScaleTextButton m_button_next, m_button_prev, m_button_exit;

		ScaleTextButton m_button_next_file, m_button_prev_file;

		sf::Text m_text_current_file;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};




}

#endif // !SBAT_RECORDVIEWER_H
