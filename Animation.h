#ifndef SBAT_ANIMATION_H
#define SBAT_ANIMATION_H

#include "Transformable.h"
#include "Updatable.h"
#include "Comparable.h"
#include <map>
#include "tiny_xml/tinyxml2.h"
#include <iostream>
namespace sbat
{

	enum class AnimState : int
	{
		PLAYING,
		PAUSED,
		STOPED,
	};


	class Animation :   public sbat::Updatable,
						public sbat::Positionable,
						public sbat::Rotatable,
						public sbat::Scalable, public sf::Drawable ,
						public sbat::Comparable<Animation>
	{
	public:

		//tmp

		void draw(sf::RenderWindow& window);


		//CONSTRUCTOR
		Animation();


		//DESTRUCTOR
		virtual ~Animation();


		//MY

		void load_from_file(const std::string& path);

		void play();
		void pause();
		void stop();

		bool ended();

		void loop(bool loop);

		float get_elapsed_value();

		sf::FloatRect get_global_bounds();
		sf::FloatRect get_local_bounds();

		void set_animation_delay(const float& anim_delay);
		const float& get_animation_delay();

		sbat::Animation& operator=(const sbat::Animation& anim);


		//UPDATABLE
		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr) override;

		//POSITIONABLE
		virtual	void 	set_position(const float& x, const float& y);

		//ROTATABLE
		virtual	void	set_rotation(const float& angle);

		//SCALABLE
		virtual	void	set_scale(const float& factorX, const  float& factorY);

		//COMPARABLE
		friend bool operator<(const  Animation& left, const  Animation& right);
		friend bool operator==(const  Animation& left, const  Animation& right);



	private:

		sf::Texture * m_texture;
		sf::Sprite m_sprite;
		float m_anim_delay, m_current_frame, m_prev_frame, m_max_frame;
		sbat::AnimState m_anim_state;
		bool m_loopped;
		std::vector<sf::IntRect> m_rects;

		//DRAWABLE
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};

}



#endif // !SBAT_ANIMATION_H





