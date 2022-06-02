#include "DrawField.h"


namespace sbat
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//CONSTRUCTOR

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sbat::DrawField::DrawField
	(
	) :
		m_field_size(10,10), // FIELD SIZE
		m_cell_size(0),
		m_style(),
		m_line_horizontal(),
		m_line_vertical(),
		m_need_field_update(0),
		m_font(nullptr),
		m_global_rect(),
		m_need_font_update(0)
	{
		this->m_line_horizontal.resize(m_field_size.y-1);
		this->m_line_vertical.resize(m_field_size.x-1);

		this->m_letters_horizontal.resize(m_field_size.x);
		this->m_letters_vertical.resize(m_field_size.y);

		for (int i = 0; i < m_letters_vertical.size(); i++)
		{
			std::string str;

			str = 'A' + i;

			m_letters_vertical[i].setString(str);
			m_letters_vertical[i].setCharacterSize(this->m_style.text_style.character_size);
			m_letters_vertical[i].setFillColor(this->m_style.text_style.fill_color);
			m_letters_vertical[i].setStyle(this->m_style.text_style.style);
		}

		for (int i = 0; i < m_letters_horizontal.size(); i++)
		{
			std::string str;

			str = '0'+i;

			m_letters_horizontal[i].setString(str);
			m_letters_horizontal[i].setCharacterSize(this->m_style.text_style.character_size);
			m_letters_horizontal[i].setFillColor(this->m_style.text_style.fill_color);
			m_letters_horizontal[i].setStyle(this->m_style.text_style.style);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//DESTRUCTOR

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sbat::DrawField::~DrawField()
	{

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//MY

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void sbat::DrawField::set_cell_size(const int& size)
	{
		m_need_field_update = 1;
		this->m_cell_size = size;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const int& sbat::DrawField::get_cell_size()const
	{
		return this->m_cell_size;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void sbat::DrawField::set_font(sf::Font* font)
	{
		m_need_font_update = 1;
		this->m_font = font;

		for (int i =0 ; i< m_letters_vertical.size() ; i++)
		{
			m_letters_vertical[i].setFont(*m_font);
		}

		for (int i = 0; i < m_letters_horizontal.size(); i++)
		{
			m_letters_horizontal[i].setFont(*m_font);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sf::Font* sbat::DrawField::get_font()const
	{
		return this->m_font;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void sbat::DrawField::set_style(const sbat::DrawFieldStyle& style)
	{
		m_need_field_update = 1;
		this->m_style = style;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const sbat::DrawFieldStyle& sbat::DrawField::get_style()const
	{
		return this->m_style;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sf::FloatRect sbat::DrawField::get_cell_global_bounds(int x, int y)const
	{

		return this->get_Transfrom().transformRect(get_cell_local_bounds(x,y));
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sf::FloatRect sbat::DrawField::get_cell_global_bounds(const sf::Vector2i& pos)const
	{
		return get_cell_global_bounds(pos.x, pos.y);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sf::FloatRect sbat::DrawField::get_global_bounds()const
	{
		return this->get_Transfrom().transformRect(this->get_local_bounds());
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sf::FloatRect sbat::DrawField::get_cell_local_bounds(int x, int y)const
	{
		return sf::FloatRect
		(
			static_cast<float>( m_style.padding.left + (x + 1) * m_cell_size),
			static_cast<float>( m_style.padding.top + (y + 1) * m_cell_size),
			static_cast<float>(m_cell_size),
			static_cast<float>(m_cell_size)
		);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sf::FloatRect sbat::DrawField::get_cell_local_bounds(const sf::Vector2i& pos)const
	{
		return get_cell_local_bounds(pos.x, pos.y);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sf::FloatRect sbat::DrawField::get_local_bounds()const
	{
		return sf::FloatRect
		(
			static_cast<float>(0),
			static_cast<float>(0),
			static_cast<float>( (m_field_size.x + 1) * (m_cell_size)+m_style.padding.left + m_style.padding.right),
			static_cast<float>( (m_field_size.y + 1) * (m_cell_size)+m_style.padding.top + m_style.padding.down)
		);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void sbat::DrawField::update(sf::RenderWindow& window, const float& dt, const sf::Event* event )
	{
		if (m_need_field_update)
		{
			m_need_field_update = 0;

			field_update();
			
		}
		if (m_need_font_update)
		{
			m_need_font_update = 0;
			for (int i = 0; i < m_letters_vertical.size(); i++)
			{
				
				m_letters_vertical[i].setCharacterSize(this->m_style.text_style.character_size);
				m_letters_vertical[i].setFillColor(this->m_style.text_style.fill_color);
				m_letters_vertical[i].setStyle(this->m_style.text_style.style);
				m_letters_vertical[i].setPosition
				(
					static_cast<float>( m_style.padding.left +m_cell_size * i + m_cell_size / 2 - m_letters_vertical[i].getGlobalBounds().width / 2 + m_cell_size),
					static_cast<float>( m_style.padding.top - m_cell_size / 2 - m_letters_vertical[i].getGlobalBounds().height / 2 + m_cell_size)
				);
			}

			for (int i = 0; i < m_letters_horizontal.size(); i++)
			{

				m_letters_horizontal[i].setCharacterSize(this->m_style.text_style.character_size);
				m_letters_horizontal[i].setFillColor(this->m_style.text_style.fill_color);
				m_letters_horizontal[i].setStyle(this->m_style.text_style.style);
				m_letters_horizontal[i].setPosition
				(
					static_cast<float>( m_style.padding.left - m_cell_size / 2 - m_letters_horizontal[i].getGlobalBounds().width / 2 + m_cell_size),
					static_cast<float>( m_style.padding.top + m_cell_size * i + m_cell_size / 2 - m_letters_horizontal[i].getGlobalBounds().height / 2 + m_cell_size)
				);
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void sbat::DrawField::field_update()
	{
		for (int i = 0; i < m_line_horizontal.size(); i++)
		{
			m_line_horizontal[i].setPosition(sf::Vector2f
			(
				static_cast<float>(m_style.padding.left + m_cell_size),
				static_cast<float>(m_style.padding.top + m_cell_size * (i + 1) - m_style.line_width / 2. + m_cell_size)
			));
			m_line_horizontal[i].setSize(sf::Vector2f(static_cast<float>(m_field_size.x * m_cell_size), static_cast<float> (m_style.line_width)));
			m_line_horizontal[i].setFillColor(m_style.line_color);
		}

		for (int i = 0; i < m_line_vertical.size(); i++)
		{
			m_line_vertical[i].setPosition(sf::Vector2f
			(
				static_cast<float>(m_style.padding.left + m_cell_size * (i + 1) - m_style.line_width / 2. + m_cell_size),
				static_cast<float>(m_style.padding.top + m_cell_size)
			));
			m_line_vertical[i].setSize(sf::Vector2f(static_cast<float>(m_style.line_width), static_cast<float>(m_field_size.y * m_cell_size)));
			m_line_vertical[i].setFillColor(m_style.line_color);
		}

		m_global_rect.setPosition(static_cast<float>(0), static_cast<float>(0));
		m_global_rect.setSize(sf::Vector2f
		(
			static_cast<float>((m_field_size.x + 1) * (m_cell_size)+m_style.padding.left + m_style.padding.right - m_style.line_width),
			static_cast<float>((m_field_size.y + 1) * (m_cell_size)+m_style.padding.top + m_style.padding.down - m_style.line_width)
		));
		m_global_rect.setOutlineThickness(static_cast<float>(m_style.line_width));
		m_global_rect.setFillColor(m_style.background_color);
		m_global_rect.setOutlineColor(m_style.outline_color);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	const sf::Vector2i& sbat::DrawField::get_field_size()const
	{
		return m_field_size;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void sbat::DrawField::draw(sf::RenderTarget& target, sf::RenderStates states)const
	{

		states.transform *=this->get_Transfrom();

		target.draw(m_global_rect, states);
		for (auto&& it : m_line_horizontal)
		{
			target.draw(it, states);
		}

		for (auto&& it : m_line_vertical)
		{
			target.draw(it, states);
		}

		for (auto&& it : m_letters_horizontal)
		{
			target.draw(it, states);
		}

		for (auto&& it : m_letters_vertical)
		{
			target.draw(it, states);
		}

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//COMPARABLE

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	bool operator<(const sbat::DrawField& left, const sbat::DrawField& right)
	{
		sf::FloatRect left_r =left.get_global_bounds();
		sf::FloatRect right_r = right.get_global_bounds();
		if (left_r.width * left_r.height < right_r.width * right_r.height)
			return 1;
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool operator==(const sbat::DrawField& left, const sbat::DrawField& right)
	{
		sf::FloatRect left_r = left.get_global_bounds();
		sf::FloatRect right_r = right.get_global_bounds();
		if (left_r.width * left_r.height == right_r.width * right_r.height)
			return 1;
		return 0;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}