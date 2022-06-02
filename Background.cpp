#include "Background.h"

namespace sbat
{

	Background::Background()
		:
		m_curr_time(0.f),
		m_time_per_frame(5.f),
		m_curr_frame(0),
		m_draw_shader_default(1),
		m_time(0),
		m_alpha_time(2.f),
		m_curr_alpha_time(0.f),
		m_state(State::DEFAULT),
		m_max_sparks(20)
	{
		
		m_textures.push_back(&GameResources::get_texture("BACKGROUND_1"));
		m_textures.push_back(&GameResources::get_texture("BACKGROUND_2"));
		m_textures.push_back(&GameResources::get_texture("BACKGROUND_3"));
		m_textures.push_back(&GameResources::get_texture("BACKGROUND_4"));


		char alpha_shader[] =
			"#version 120\n"
			"uniform sampler2D currentTexture;\n"
			"uniform float time;\n"
			"void main() {\n"
			"vec2 coord = gl_TexCoord[0].xy;"
			"coord.y += cos(radians(100 * time + coord.y * 0)) * 0.05 * sin(time);"
			"vec4 pixel_color = texture2D(currentTexture, coord);"
			"float alpha = pixel_color.w- time;\n"
			"gl_FragColor = vec4(pixel_color.xyz, alpha);\n"
			"}\n";

		char shader[] =
			"#version 120\n"
			"uniform sampler2D currentTexture;\n"
			"uniform float time;\n"
			"void main()\n"
			"{\n"
			"vec2 uv = gl_FragCoord.xy / resolution.xy;\n"
			"uv -= .3;\n"
			"uv *= 3.;\n"

			"vec3 col = vec3(0.1, 0.6, 0.9);\n"

			"if (uv.y < cos(0.4 * time + uv.x * 4.) / 1.2) col = vec3(0, .4, 0);\n"
			"if (uv.y < cos(1.2 * time + uv.x * 8.) / 4.)  col = vec3(0, .6, 0);\n"
			"if (uv.y < sin(1.4 * time + uv.x * 6.) / 10.) col = vec3(0, 8, 0);\n"
			"gl_FragColor = vec4(col, 1.0);\n"
			"}\n";

		m_alpha_shader.loadFromMemory(alpha_shader, sf::Shader::Fragment);
		//m_shader.loadFromMemory(shader, sf::Shader::Fragment);

		m_sprite.setTexture(*(m_textures[0]));
		
		m_sprite.setTextureRect(sf::IntRect(0, 0, m_textures[m_curr_frame]->getSize().x, m_textures[m_curr_frame]->getSize().y));

	}

	Background::~Background()
	{
	}

	void Background::update(sf::RenderWindow& window, const float& dt, const sf::Event* event)
	{

		if (m_sparks.size() != m_max_sparks)
		{
			if (sbat::Random::rand(0, 3) == 0)
			{
				m_sparks.push_front(GameResources::get_animation("SPARK_ANIM"));
				m_sparks.begin()->play();
				m_sparks.begin()->set_position(Random::rand(0, static_cast<int>(window.getSize().x)), Random::rand(0, static_cast<int>(window.getSize().x)));
			}
		}

		std::vector < std::list<sbat::Animation>::iterator> needs_delete;
		for (auto it = m_sparks.begin(); it != m_sparks.end(); it++)
		{
			it->update(window, dt);
			if (it->ended())
				needs_delete.push_back(it);
		}

		for (auto& it : needs_delete)
			m_sparks.erase(it);

		if (m_state == State::ALPHA_END)
		{
			m_curr_alpha_time += dt;
			if (m_curr_alpha_time >= 1)
			{
				m_state = State::ALPHA_BEGIN;
				m_curr_alpha_time = 1;
				m_sprite.setTexture(*m_textures[m_curr_frame]);
				m_sprite.setTextureRect(sf::IntRect(0, 0, m_textures[m_curr_frame]->getSize().x, m_textures[m_curr_frame]->getSize().y));
				m_alpha_shader.setUniform("time", m_time);
			}
			m_alpha_shader.setUniform("time", m_curr_alpha_time);
		}
		else if (m_state == State::ALPHA_BEGIN)
		{
			m_curr_alpha_time -= dt;
			if (m_curr_alpha_time <= 0)
			{
				m_curr_alpha_time = 0;
				m_state = State::DEFAULT;
				m_draw_shader_default = 1;
			}
			m_alpha_shader.setUniform("time", m_curr_alpha_time);
		}
		else if (m_state == State::DEFAULT)
		{
			m_curr_time += dt;
			if (m_curr_time >= m_time_per_frame)
			{
				m_curr_time = 1;
				m_curr_frame++;
				m_curr_frame %= m_textures.size();
				m_state = State::ALPHA_END;
			}
			m_shader.setUniform("time", 1.f * m_curr_time);
		}
		


		m_sprite.setScale
		(
			static_cast<float>(window.getSize().x) / m_sprite.getLocalBounds().width,
			static_cast<float>(window.getSize().y+20) / m_sprite.getLocalBounds().height
		);
	}

	void Background::draw(sf::RenderTarget& target, sf::RenderStates states)const
	{
		if (m_state == State::DEFAULT)
		{
			states.shader = &m_shader;
		}
		else if (m_state == State::ALPHA_BEGIN || m_state == State::ALPHA_END)
		{
			states.shader = &m_alpha_shader;
		}

		target.draw(m_sprite, states);

		for (auto& it : m_sparks)
			target.draw(it, states);
	}

}