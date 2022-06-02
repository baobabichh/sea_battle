#include "Originable.h"

namespace sbat
{
	sbat::Originable::Originable() : m_origin(0,0)
	{

	}

	void	sbat::Originable::set_origin(const float& x, const  float& y)
	{
		m_origin.x = x;
		m_origin.x = y;
	}
	void	sbat::Originable::set_origin(const sf::Vector2f& origin)
	{
		m_origin = origin;
	}
	const sf::Vector2f& sbat::Originable::get_origin() const
	{
		return m_origin;
	}

	sbat::Originable::~Originable()
	{

	}

}