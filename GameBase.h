#ifndef SBAT_GAMEBASE_H
#define SBAT_GAMEBASE_H

#include "DrawShipField.h"
#include "GameRecord.h"

namespace sbat
{

	class GameBase
		:
		public sf::Drawable,
		public sbat::Updatable

	{
	public:
		GameBase() = default;
		virtual~GameBase() = default;

		virtual void init() = 0;

		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr) override = 0;

		virtual bool finished()const = 0;

		virtual GameRecord* get_record()const = 0;

	protected:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

	};




}


#endif // !SBAT_GAMEBASE_H

