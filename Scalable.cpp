#include "Scalable.h"

namespace sbat
{
	sbat::Scalable::Scalable() : m_scale(1,1)
	{

	}

	void	sbat::Scalable::set_scale(const float& factorX, const float& factorY)
	{
		this->m_scale.x = factorX; this->m_scale.y = factorY;
	}

	void	sbat::Scalable::set_scale(const sf::Vector2f& factors)
	{
		this->set_scale(factors.x, factors.y);
	}
	const sf::Vector2f& sbat::Scalable::get_scale() const
	{
		return this->m_scale;
	}
	void	sbat::Scalable::scale(const float& factorX, const float& factorY)
	{
		this->set_scale(this->get_scale().x * factorX, this->get_scale().y * factorY);
	}
	void	sbat::Scalable::scale(const sf::Vector2f& factor)
	{
		this->set_scale(this->get_scale().x * factor.x, this->get_scale().y * factor.y);
	}

	sbat::Scalable::~Scalable()
	{

	}
}