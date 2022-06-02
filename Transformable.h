#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include "Comparable.h"
#include "Originable.h"
#include "Positionable.h"
#include "Rotatable.h"
#include "Scalable.h"



namespace sbat
{

	class Transformable
	{
	public:
								Transformable();
				//NEED OVERLOAD
				virtual	void 	set_position(const float& x, const float& y);
				virtual	void	set_rotation(const float& angle);
				virtual	void	set_scale(const float& factorX, const  float& factorY);
				virtual	void	set_origin(const float& x, const  float& y);

						void	set_position(const sf::Vector2f& position);
					    void	set_scale(const sf::Vector2f& factors);
						void	set_origin(const sf::Vector2f& origin);
		const sf::Vector2f&		get_position() const;
						float	get_rotation() const;
		const sf::Vector2f&		get_scale() const;
		const sf::Vector2f&		get_origin() const;
						void	move(const float& offsetX, const  float& offsetY);
						void	move(const sf::Vector2f& offset);
						void	rotate(const float& angle);
						void	scale(const float& factorX, const float& factorY);
						void	scale(const sf::Vector2f& factor);

			   sf::Transform	get_Transfrom()const;

					 virtual	~Transformable();

	private:
		sf::Vector2f m_position;
		float m_rotation;
		sf::Vector2f m_scale;
		sf::Vector2f m_orgin;
	};





}



#endif // !TRANSFORMABLE_H




