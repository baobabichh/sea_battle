#ifndef SBAT_SHIPFIELDCONSTRUCTOR_H
#define SBAT_SHIPFIELDCONSTRUCTOR_H

#include "GameResources.h"
#include "GameStyles.h"
#include "func.h"
#include "DrawField.h"
#include "FieldConstructorStyle.h"
#include "DrawShipConstructor.h"

#include <algorithm>
#include "Random.h"
#include <unordered_map>

namespace sbat
{

	class DrawShipField;

	class ShipFieldConstructor 
		:
		public sbat::DrawField
	{
		friend class DrawShipField;
	public:
	
		//CONSTRUCTOR
		ShipFieldConstructor();

		//DESTRUCTOR
		virtual ~ShipFieldConstructor();

		//MY

		void init();

		void set_ship_texture(std::vector<sf::Texture>& ship_textures);

		void add_ship(const sf::Vector2i& pos, const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing);
		void add_ship(const sf::Vector2i& pos, const sbat::DrawShipConstructor& ship);

		void remove_ship(const sf::Vector2i& pos);


		//UPDATABLE
		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr) override;

		void update_moving_ship(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr);

		void rotate_ship();

		void random();


	protected:

		std::unordered_map<sf::Vector2i , sbat::DrawShipConstructor , Vector2Ihash> m_ships;

		std::pair<sf::Vector2i, sbat::DrawShipConstructor> m_moving_ship_start, m_moving_ship_end;


		std::vector<short> m_field;

		std::vector<sf::Texture>* p_ship_textures;

		

		bool m_is_ship_selected , m_is_ship_selected_prev;
		bool m_is_ship_on_move , m_is_ship_on_move_prev;

	protected:

		bool can_ship_place(const sf::Vector2i& pos, const sbat::BaseShip& ship);

		void update_matr();

		short& matr_val(int x, int y);


		//DRAWABLE
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};




}





#endif // !SBAT_SHIPFIELDCONSTRUCTOR_H
