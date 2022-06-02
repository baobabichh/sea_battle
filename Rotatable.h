#pragma once
#ifndef SBAT_ROTATABLE_H
#define SBAT_ROTATABLE_H
#include <SFML/Graphics.hpp>

namespace sbat {

	class Rotatable
	{
	public :
		Rotatable();

		virtual	void	set_rotation(const float& angle);
		float	get_rotation() const;
		void	rotate(const float& angle);

		virtual ~Rotatable();
	private:
		float m_rotation;

	};

}

#endif // !SBAT_ROTATABLE_H


