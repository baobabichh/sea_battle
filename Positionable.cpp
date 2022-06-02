#include "Positionable.h"

namespace sbat
{
	Positionable::Positionable() : m_position(0, 0)
	{

	}

	void 	sbat::Positionable::set_position(const float& x, const  float& y)
	{
		this->m_position.x = x; this->m_position.y = y;
	}
	void	sbat::Positionable::set_position(const sf::Vector2f& position)
	{
		this->set_position(position.x, position.y);
	}
	const sf::Vector2f& sbat::Positionable::get_position() const
	{
		return this->m_position;
	}
	void	sbat::Positionable::move(const float& offsetX, const  float& offsetY)
	{
		this->set_position(this->get_position().x + offsetX, this->get_position().y + offsetY);
	}
	void	sbat::Positionable::move(const sf::Vector2f& offset)
	{
		this->set_position(this->get_position().x + offset.x, this->get_position().y + offset.y);
	}

	Positionable::~Positionable()
	{

	}
}