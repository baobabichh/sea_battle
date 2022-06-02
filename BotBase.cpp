#include "BotBase.h"

namespace sbat
{

	BotBase::BotBase()
		:
		m_curr_delay(0.f),
		m_delay(0.f),
		p_field(nullptr)
	{

	}

	void BotBase::set_field(DrawShipField* field)
	{
		p_field = field;
	}

	void BotBase::set_delay(float delay)
	{
		m_delay = delay;
	}
	float BotBase::get_delay()
	{
		return m_delay;
	}

	void BotBase::update(sf::RenderWindow& window, const float& dt, const sf::Event* event)
	{
		m_curr_delay += dt;
	}

	bool BotBase::delayed()
	{
		if (m_curr_delay >= m_delay)
		{
			m_curr_delay = 0;
			return 1;
		}
		return 0;

	}

}