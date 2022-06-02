#ifndef DRAWSHIP_H
#define DRAWSHIP_H



#include "BaseShip.h"
#include "Transformable.h"
#include "Updatable.h"
#include "Animation.h"

namespace sbat
{
	class DrawShip  : public sbat::BaseShip
				    , public sf::Drawable
					, public sbat::Updatable
					, public sbat::Scalable
					, public sbat::Positionable
	{
	public :
		//CONSTRUCTOR
		DrawShip();
		DrawShip(std::vector<sf::Texture>& ship_textures, sbat::Animation *explosion_anim , sbat::Animation* smoke_anim,  const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing, const sf::Vector2i& field_position);

		//DESTRUCTOR
		virtual~DrawShip();

		//MY
		void set_animations(sbat::Animation* explosion_anim, sbat::Animation* smoke_anim);
		void set_texture(std::vector<sf::Texture>& ship_textures);
		void show();
		void hide();

		sf::FloatRect get_global_bounds();
		sf::FloatRect get_local_bounds();

		//BASE SHIP
		virtual void set_ship_facing(const sbat::ShipFacing& rotation);
		virtual void set_ship_type(const sbat::ShipType& type);

		virtual void explode(const sbat::ShipCellPosition& position);

		//TRANSFORMABLE
		virtual	void 	set_position(const float& x, const float& y);
		virtual	void	set_scale(const float& factorX, const  float& factorY);

		//UPDATEBLE
		virtual void update(sf::RenderWindow& window, const float& dt);

	private:

		std::vector<sf::Texture * >m_textures;
		sf::Sprite m_sprite;
		sf::Vector2i m_facing_position;
		float m_facing_rotation;
		bool m_hiden;
		
		sbat::Animation* p_exposion_anim, * p_smoke_anim;

		std::vector<sf::Sprite> m_cell_sprites;
		std::vector<sbat::Animation> m_smoke_animations;
		std::vector<sbat::Animation> m_explosion_animations;


		//DRAWABLE
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	};


}


#endif // !DRAWSHIP_H