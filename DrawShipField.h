#ifndef SBAT_DRAWSHIPFIELD_H
#define SBAT_DRAWSHIPFIELD_H

#include "DrawField.h"
#include "DrawShipEnemy.h"
#include "DrawShipFriend.h"
#include <unordered_map>
#include "func.h"
#include "GameResources.h";
#include "GameStyles.h"
#include "ShipFieldConstructor.h"


namespace sbat
{

	class ShipFieldConstructor;


	enum class FieldCellState : short
	{
		NOTHING,
		NOTHING_HIT,
		SHIP,
		SHIP_EXPLODED,
	};

	class DrawShipField
		:
		public sbat::DrawField
	{
		friend class BotRandom;
		friend class BotBase;
		friend class ShipFieldConstructor;

	public:
		//CONSTRUCTOR

		DrawShipField();
		
		//DESTRUCTOR

		virtual~DrawShipField();

		//MY

		void init();

		void set_ship_animations(sbat::Animation* explosion_anim, sbat::Animation* smoke_anim);
		void set_field_animation(sbat::Animation* water_hit_anim, sbat::Animation* cross_anim);
		void set_ship_texture(std::vector<sf::Texture>& ship_textures);
		void set_field_textures(sf::Texture* cross_tx);
		
		virtual void add_ship(const sf::Vector2i& pos, const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing)=0;
		void remove_ship(const sf::Vector2i& pos);

		void shoot(const sf::Vector2i& pos);

		sbat::FieldCellState get_cell_state(const sf::Vector2i& pos)const;

		bool all_ships_exploded()const;

		void clear();

		void copy_ships(ShipFieldConstructor& val);

		const std::unordered_map<sf::Vector2i, DrawShip*, Vector2Ihash>& get_ships();

		// UPDATEBLE

		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr) override;

	private :

		//DRAWABLE

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected :

		std::unordered_map<sf::Vector2i, DrawShip*, Vector2Ihash> m_ships;

		sbat::Animation* p_explosion_anim, * p_smoke_anim, * p_water_hit_anim , * p_cross_anim;

		std::vector<sf::Texture> * p_ship_textures;

		sf::Texture* p_cross_tx;

		bool m_need_ship_style_update;

		std::unordered_map <sf::Vector2i, sf::Sprite  , Vector2Ihash> m_cross_sprites;

		std::vector<std::pair<sf::Vector2i, sbat::Animation>> m_splash_animations;

		std::vector<std::pair<sf::Vector2i ,sbat::Animation>> m_cross_animations;

		void create_cross_anim(const sf::Vector2i& pos);

		void explode_around_ship(const sf::Vector2i& pos, const BaseShip& ship);
		

	};

	//typedef DrawShipField<DrawShipEnemy> DrawShipFieldEnemy;
	//typedef DrawShipField<DrawShipFriend> DrawShipFieldFriend;









	
}


#endif // ! SBAT_DRAWSHIPFIELD_H






