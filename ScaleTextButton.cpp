#include "ScaleTextButton.h"

namespace sbat
{


	ScaleTextButton::ScaleTextButton()
		:
		m_scale_val(1.2f),
		m_curr_scale_val(1.f),
		m_speed(3.f)
	{
		
	}

	ScaleTextButton::~ScaleTextButton()
	{

	}


	void ScaleTextButton::set_scale_val(float scale)
	{
		m_scale_val = scale;
	}

	float ScaleTextButton::get_scale_val()
	{
		return m_scale_val;
	}


	//UPDATABLE

	void ScaleTextButton::update(sf::RenderWindow& window, const float& dt, const sf::Event* event)
	{
		if (hovered(window))
		{
			if (m_curr_scale_val > m_scale_val)
				m_curr_scale_val = m_scale_val;
			else if (m_curr_scale_val < m_scale_val)
				m_curr_scale_val += m_speed * dt;
		}
		else
		{
			if (m_curr_scale_val < 1.f)
				m_curr_scale_val = 1.f;
			else if (m_curr_scale_val > 1.f)
				m_curr_scale_val -= m_speed * dt;
		}
		m_text.setScale(m_curr_scale_val, m_curr_scale_val);
		m_text.setOrigin(m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f);
		m_text.setPosition(m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f);

		

	}

	void ScaleTextButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= this->get_Transfrom();

		sf::RectangleShape rect;
		/*rect.setFillColor(sf::Color(0, 0, 150, 100));
		rect.setSize(sf::Vector2f(m_hit_box.width, m_hit_box.height));
		rect.setPosition(m_hit_box.left, m_hit_box.top);*/
		target.draw(rect, states);
		target.draw(m_text, states);
	}

}