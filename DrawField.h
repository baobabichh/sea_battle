#ifndef SBAT_DRAWFIELD_H
#define SBAT_DRAWFIELD_H

#include "DrawShip.h"
#include "Updatable.h"
#include "Comparable.h"
#include "DrawFieldStyle.h"
#include <string>
namespace sbat
{
		

	class DrawField :
		public sbat::Updatable,
		public sf::Drawable,
		public sbat::Transformable,
		public sbat::Comparable<DrawField>
	{
	public :
		//CONSTRUCTOR
		DrawField();

		//DESTRUCTOR
		virtual~DrawField();

		//MY

		const sf::Vector2i& get_field_size()const;

		void set_cell_size(const int& size);
		const int& get_cell_size()const;

		void set_font(sf::Font* font);
		sf::Font* get_font()const;

		void set_style(const sbat::DrawFieldStyle& style);
		const sbat::DrawFieldStyle& get_style()const;


		sf::FloatRect get_cell_global_bounds(int x, int y)const;
		sf::FloatRect get_cell_global_bounds(const sf::Vector2i &pos)const;

		sf::FloatRect get_cell_local_bounds(int x, int y)const;
		sf::FloatRect get_cell_local_bounds(const sf::Vector2i& pos)const;

		virtual sf::FloatRect get_global_bounds()const;
		virtual sf::FloatRect get_local_bounds()const;

		//COMPARABLE
		friend bool operator<(const sbat::DrawField& left, const sbat::DrawField& right);
		friend bool operator==(const sbat::DrawField& left, const sbat::DrawField& right);

		//UPDATEBLE
		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr) override;
	private:
		
		sf::Vector2i m_field_size;
		sbat::DrawFieldStyle m_style;
		std::vector<sf::RectangleShape> m_line_horizontal;
		std::vector<sf::RectangleShape> m_line_vertical;

		sf::RectangleShape m_global_rect;

		bool m_need_field_update , m_need_font_update;

		sf::Font* m_font;
		std::vector<sf::Text> m_letters_horizontal;
		std::vector<sf::Text> m_letters_vertical;


		int m_cell_size;

	protected:

		void field_update();

		//DRAWABLE
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};


}

#endif // !SBAT_DRAWFIELD_H






