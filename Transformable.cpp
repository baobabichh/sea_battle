#include "Transformable.h"


namespace sbat
{

	sbat::Transformable::Transformable() :m_orgin(0, 0), m_position(0, 0), m_rotation(0), m_scale(1, 1)
	{

	}
	//virtual
	void 	sbat::Transformable::set_position(const float &x, const  float &y)
	{
		this->m_position.x = x; this->m_position.y = y;
	}
	void	sbat::Transformable::set_rotation(const float& angle)
	{
		this->m_rotation = angle;
	}
	void	sbat::Transformable::set_scale(const float& factorX, const float& factorY)
	{
		this->m_scale.x = factorX; this->m_scale.y = factorY;
	}
	void	sbat::Transformable::set_origin(const float& x, const float& y)
	{
		this->m_orgin.x = x; this->m_orgin.y = y;
	}


	//auto
	void	sbat::Transformable::set_position(const sf::Vector2f& position)
	{
		this->set_position(position.x, position.y);
	}
	void	sbat::Transformable::set_scale(const sf::Vector2f& factors)
	{
		this->set_scale(factors.x, factors.y);
	}
	void	sbat::Transformable::set_origin(const sf::Vector2f& origin)
	{
		this->set_origin(m_orgin.x, m_orgin.y);
	}
	const sf::Vector2f& sbat::Transformable::get_position() const
	{
		return this->m_position;
	}
	float	sbat::Transformable::get_rotation() const
	{
		return this->m_rotation;
	}
	const sf::Vector2f& sbat::Transformable::get_scale() const
	{
		return this->m_scale;
	}
	const sf::Vector2f& sbat::Transformable::get_origin() const
	{
		return m_orgin;
	}
	void	sbat::Transformable::move(const float& offsetX, const  float& offsetY)
	{
		this->set_position(this->get_position().x + offsetX, this->get_position().y + offsetY);
	}
	void	sbat::Transformable::move(const sf::Vector2f& offset)
	{
		this->set_position(this->get_position().x + offset.x, this->get_position().y + offset.y);
	}
	void	sbat::Transformable::rotate(const float& angle)
	{
		this->set_rotation(this->get_rotation() + angle);
	}
	void	sbat::Transformable::scale(const float& factorX, const float& factorY)
	{
		this->set_scale(this->get_scale().x * factorX, this->get_scale().y * factorY);
	}
	void	sbat::Transformable::scale(const sf::Vector2f& factor)
	{
		this->set_scale(this->get_scale().x * factor.x, this->get_scale().y * factor.y);
	}

	sf::Transform	sbat::Transformable::get_Transfrom()const
	{
		sf::Transformable res;
		res.setRotation(m_rotation);
		res.setOrigin(m_orgin);
		res.setPosition(m_position);
		res.setScale(m_scale);
		return  res.getTransform();
	}

	sbat::Transformable::~Transformable()
	{

	}

}