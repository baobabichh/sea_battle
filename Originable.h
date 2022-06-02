#ifndef SBAT_ORIGINABLE_H
#define SBAT_ORIGINABLE_H
#include <SFML/Graphics.hpp>

namespace sbat {

	class Originable
	{
	public:
		Originable();

		virtual	void	set_origin(const float& x, const  float& y);
		void	set_origin(const sf::Vector2f& origin);
		const sf::Vector2f& get_origin() const;

		virtual~Originable();
	private:
		sf::Vector2f m_origin;
	};

}

#endif // !SBAT_ORIGINABLE_H


