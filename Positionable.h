#pragma once
#ifndef SBAT_POSITIONABLE_H
#define SBAT_POSITIONABLE_H
#include <SFML/Graphics.hpp>

namespace sbat {

	class Positionable
	{
	public :

		Positionable();

		virtual	void 	set_position(const float& x, const float& y);

		void	set_position(const sf::Vector2f& position);
		const sf::Vector2f& get_position() const;
		void	move(const float& offsetX, const  float& offsetY);
		void	move(const sf::Vector2f& offset);

		virtual ~Positionable();

	private:
		sf::Vector2f m_position;
	};



}

#endif // !SBAT_POSITIONABLE_H





