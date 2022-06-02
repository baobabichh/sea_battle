#ifndef  SBAT_BOTRANDOM_H
#define SBAT_BOTRANDOM_H

#include "BotBase.h"
#include "Random.h"
namespace sbat
{

	class BotRandom
		:
		public BotBase
	{
		friend class sbat::DrawShipField;
	public:

		BotRandom();
		virtual ~BotRandom() = default;

		sf::Vector2i make_move()override;

	protected:

		std::vector<sf::Vector2i> m_available_hits;

		std::vector<sf::Vector2i>m_probably_ship_here;

		sf::Vector2i m_first_ship_pos;

		bool m_should_kill;

		std::pair<sf::Vector2i, sbat::BaseShip*> m_killing_ship;

		std::vector<sbat::ShipFacing> m_checked_facings;



		sf::Vector2i make_random_move();

		void get_available_hits();

		void fill_probably_ship(const sf::Vector2i& pos);

		sf::Vector2i render_probably_ship();

		std::pair<sf::Vector2i, sbat::BaseShip*> get_ship(const sf::Vector2i& pos);


	};
}

#endif // ! SBAT_BOTRANDOM_H


