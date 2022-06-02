#ifndef UPDATABLE_H
#define UPDATABLE_H

#include <SFML/Graphics.hpp>

namespace sbat
{


	class Updatable
	{
	public:
		Updatable(){}

		virtual void update(sf::RenderWindow& window, const float& dt, const sf::Event * event = nullptr) = 0;

		virtual ~Updatable(){}
	};


}

#endif // !UPDATABLE_H

