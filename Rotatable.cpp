#include "Rotatable.h"

namespace sbat
{
	Rotatable::Rotatable() : m_rotation(0)
	{

	}

	void	sbat::Rotatable::set_rotation(const float& angle)
	{
		this->m_rotation = angle;
	}

	float	sbat::Rotatable::get_rotation() const
	{
		return this->m_rotation;
	}

	void	sbat::Rotatable::rotate(const float& angle)
	{
		this->set_rotation(this->get_rotation() + angle);
	}



	Rotatable::~Rotatable()
	{

	}
}