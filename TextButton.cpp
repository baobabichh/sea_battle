#include "TextButton.h"




namespace sbat
{
	//CONSTRUCTOR

	TextButton::TextButton()
		:
		m_text(),
		m_text_style()
	{
		
	}
	//DESTRUCTOR

	TextButton::~TextButton()
	{

	}

	//MY

	void TextButton::init()
	{
		set_font(&sbat::GameResources::get_font(DEFAULT_FONT));
		set_style(sbat::GameStyles::TextStyles.Default);
		m_text.setOutlineThickness(1.5);
		m_text.setOutlineColor(sf::Color::Black);

		m_hit_box = m_text.getGlobalBounds();
		
	}

	void TextButton::set_font(sf::Font* font)
	{
		m_text.setFont(*font);

		m_hit_box = m_text.getGlobalBounds();
	}

	void TextButton::set_string(const std::wstring& title)
	{
		m_text.setString(title);

		m_hit_box = m_text.getGlobalBounds();
	}
	const std::wstring& TextButton::get_string()const
	{
		return m_text.getString();
	}

	void TextButton::set_style(const TextStyle& text_style)
	{
		apply_style_text(m_text, text_style);

		m_hit_box = m_text.getGlobalBounds();
	}

	sf::FloatRect TextButton::get_local_bounds()const
	{
		return m_text.getGlobalBounds();
	}

	sf::FloatRect TextButton::get_global_bounds()const
	{
		return this->get_Transfrom().transformRect(get_local_bounds());
	}

	//UPDATABLE

	void TextButton::update(sf::RenderWindow& window, const float& dt, const sf::Event* event )
	{
		
	}

	//DRAWABLE

	void TextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= this->get_Transfrom();
		target.draw(m_text, states);
	}

}