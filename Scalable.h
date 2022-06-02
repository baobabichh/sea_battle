#ifndef SBAT_SCALABLE_H
#define SBAT_SCALABLE_H
#include <SFML/Graphics.hpp>

namespace sbat {

	class Scalable
	{
	public:
					Scalable();

virtual	void		set_scale(const float& factorX, const  float& factorY);
		void		set_scale(const sf::Vector2f& factors);
const sf::Vector2f& get_scale() const;
		void		scale(const float& factorX, const float& factorY);
		void		scale(const sf::Vector2f& factor);
		
		virtual		~Scalable();
	private:
		sf::Vector2f m_scale;
	};

}

#endif // !SBAT_SCALABLE_H





