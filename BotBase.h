#ifndef  SBAT_BOTBASE_H
#define SBAT_BOTBASE_H

#include "DrawShipField.h"

namespace sbat
{
	
	class BotBase
		:
		public sbat::Updatable
	{
		friend class sbat::DrawShipField;

	public:

		BotBase();
		virtual ~BotBase() = default;

		void set_field(DrawShipField* field);
		virtual sf::Vector2i make_move() = 0;

		void set_delay(float delay);
		float get_delay();

		bool delayed();

		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr)override;



	protected:

		DrawShipField* p_field;

		float m_delay , m_curr_delay;
		

	};


}

#endif // ! SBAT_BOTBASE_H

