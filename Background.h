#ifndef SBAT_BACKGROUND_H
#define SBAT_BACKGROUND_H

#include "Animation.h"
#include "GameResources.h"
#include "Random.h"

namespace sbat
{

	class Background
		:
		public Updatable,
		public sf::Drawable
	{
	public:

		Background();
		~Background();

		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr)override;

		enum State
		{
			ALPHA_END,
			ALPHA_BEGIN,
			DEFAULT
		};

	protected:

		void draw(sf::RenderTarget& target, sf::RenderStates states)const override;

	private:
		std::vector<sf::Texture *> m_textures;
		sf::Sprite m_sprite;
		sf::Shader m_alpha_shader, m_shader;
		float m_time_per_frame, m_curr_time , m_alpha_time , m_curr_alpha_time;
		float m_time;
		int m_curr_frame;
		bool m_draw_shader_default;
		State m_state;

		int m_max_sparks;
		std::list<sbat::Animation> m_sparks;
	}; 




}

#endif // !SBAT_BACKGROUND_H

