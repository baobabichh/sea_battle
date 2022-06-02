#include "Animation.h"


namespace sbat
{

	void sbat::Animation::draw(sf::RenderWindow& window)
	{
		window.draw(m_sprite);
	}



	//CONSTRUCTOR
	sbat::Animation::Animation() : m_anim_delay(0), m_anim_state(AnimState::STOPED), m_current_frame(0), m_loopped(0), m_max_frame(0), m_prev_frame(0)
	{
		m_sprite.setColor(sf::Color::White);
	}


	//DESTRUCTOR
	sbat::Animation::~Animation()
	{

	}


	//MY

	void  sbat::Animation::load_from_file(const std::string& path)
	{
		
		tinyxml2::XMLDocument doc;
		doc.LoadFile(path.c_str());

		tinyxml2::XMLElement* sprite_elem = doc.FirstChildElement("sprites");
		std::string texture_file_name =sprite_elem->Attribute("image");

		tinyxml2::XMLElement* anim_elem = sprite_elem->FirstChildElement("animation");
		std::string title = anim_elem->Attribute("title");
		int delay = atoi(anim_elem->Attribute("delay"));
		this->m_anim_delay = delay*0.001f;

		tinyxml2::XMLElement* cut_elem = anim_elem->FirstChildElement("cut");

		while (cut_elem)
		{
			int h = atoi(cut_elem->Attribute("h"));
			int w = atoi(cut_elem->Attribute("w"));
			int x = atoi(cut_elem->Attribute("x"));
			int y = atoi(cut_elem->Attribute("y"));
			int row = atoi(cut_elem->Attribute("row"));
			int col = atoi(cut_elem->Attribute("col"));

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					sf::IntRect rect(x + (j * w / col), y + (i * h / row), w / col, h / row);
					this->m_rects.push_back(rect);
					this->m_max_frame++;
				}
			}
			cut_elem = cut_elem->NextSiblingElement();
		}
		this->m_texture = new sf::Texture();
		this->m_texture->loadFromFile(texture_file_name);
		this->m_sprite.setTexture(*(this->m_texture));
		//this->m_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));

	}

	void sbat::Animation::play()
	{
		m_anim_state = AnimState::PLAYING;
		m_sprite.setTextureRect(m_rects[0]);
	}
	void sbat::Animation::pause()
	{
		m_anim_state = AnimState::PAUSED;
	}
	void sbat::Animation::stop()
	{
		m_anim_state = AnimState::STOPED;
		this->m_current_frame = 0;
		this->m_prev_frame = 0;
	}
	bool sbat::Animation::ended()
	{
		if (this->m_anim_state == AnimState::STOPED)
			return 1;
		return 0;
	}

	void sbat::Animation::loop(bool loop)
	{
		m_loopped = loop;
	}

	sf::FloatRect sbat::Animation::get_global_bounds()
	{
		return this->m_sprite.getGlobalBounds();
	}
	sf::FloatRect sbat::Animation::get_local_bounds()
	{
		return this->m_sprite.getLocalBounds();
	}

	float sbat::Animation::get_elapsed_value()
	{
		return m_current_frame / (m_max_frame - 1.0f);
	}

	void sbat::Animation::set_animation_delay(const float& anim_delay)
	{
		this->m_anim_delay = anim_delay;
	}
	const float& sbat::Animation::get_animation_delay()
	{
		return this->m_anim_delay;
	}

	sbat::Animation& sbat::Animation::operator=(const sbat::Animation& anim)
	{
		this->m_anim_delay = anim.m_anim_delay;
		this->m_anim_state = anim.m_anim_state;
		this->m_current_frame = anim.m_current_frame;
		this->m_loopped = anim.m_loopped;
		this->m_max_frame = anim.m_max_frame;
		this->m_prev_frame = anim.m_prev_frame;
		this->m_rects = anim.m_rects;
		this->m_texture = anim.m_texture;
		this->m_sprite.setTexture(*(this->m_texture));
		this->m_sprite = anim.m_sprite;
		return *this;
	}

	//UPDATABLE
	void sbat::Animation::update(sf::RenderWindow& window, const float& dt, const sf::Event* event )
	{
		if (m_anim_state == AnimState::PLAYING)
		{
			m_prev_frame = m_current_frame;
			m_current_frame += (dt /m_anim_delay);
			if (static_cast<int>(m_current_frame) >= static_cast<int>(m_max_frame)-1)
			{
				m_current_frame = m_max_frame-1;
			}
			m_sprite.setTextureRect(m_rects[static_cast<int>(m_current_frame)]);
			//std::cout << "current frame " << m_current_frame << std::endl;
			if (static_cast<int>(m_current_frame) >= static_cast<int>(m_max_frame) - 1)
			{
				if (!m_loopped)
				{
					m_anim_state = AnimState::STOPED;
					m_current_frame = 0.0f;
					m_prev_frame = 0.0f;
					m_sprite.setTextureRect(sf::IntRect(0,0,0,0));
				}
				else
				{
					m_current_frame = 0.0f;
					m_prev_frame = 0.0f;
				}
			}
		}
		else if (m_anim_state == AnimState::STOPED)
		{

		}
		else if (m_anim_state == AnimState::PAUSED)
		{

		}
	}

	//POSITIONABLE
	void 	sbat::Animation::set_position(const float& x, const float& y)
	{
		sbat::Positionable::set_position(x, y);
		m_sprite.setPosition(x, y);
	}

	//ROTATABLE
	void	sbat::Animation::set_rotation(const float& angle)
	{
		sbat::Rotatable::set_rotation(angle);
		m_sprite.setRotation(angle);
	}

	//SCALABLE
	void	sbat::Animation::set_scale(const float& factorX, const  float& factorY)
	{
		sbat::Scalable::set_scale(factorX, factorY);
		m_sprite.setScale(factorX, factorY);
	}

	//COMPARABLE
	bool operator<(const  Animation& left, const  Animation& right)
	{
		return 1;
	}
	bool operator==(const  Animation& left, const  Animation& right)
	{
		return 0;
	}

	//DRAWABLE
	void sbat::Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(this->m_sprite, states);
	}



}