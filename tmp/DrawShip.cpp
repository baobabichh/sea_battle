#include "DrawShip.h"


namespace sbat
{
	//CONSTRUCTOR
	sbat::DrawShip::DrawShip()
		: BaseShip(), Positionable(), Updatable(), Scalable(), sf::Drawable(),
		m_facing_position(0, 0),
		m_facing_rotation(0),
		m_sprite(),
		m_hiden(0),
		p_exposion_anim(nullptr),
		p_smoke_anim(nullptr)
	{
		this->m_textures.resize(5);
	}
	sbat::DrawShip::DrawShip(std::vector<sf::Texture>& ship_textures, sbat::Animation* explosion_anim, sbat::Animation* smoke_anim, const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing, const sf::Vector2i& field_position)
		: BaseShip(ship_type, ship_facing, field_position), Positionable(), Scalable(), Updatable(), sf::Drawable(),
		m_facing_position(0, 0),
		m_facing_rotation(0),
		m_sprite(),
		m_hiden(0),
		p_exposion_anim(nullptr),
		p_smoke_anim(nullptr)
	{


		this->p_exposion_anim = explosion_anim;
		this->p_smoke_anim = smoke_anim;

		this->m_textures.resize(5);
		this->set_texture(ship_textures);
		this->set_ship_facing(ship_facing);

		this->m_cell_sprites.resize(static_cast<int>(ship_type));
		for (auto&& it : this->m_cell_sprites)
		{
			it.setTexture(ship_textures[4]);
			it.setColor(sf::Color::Transparent);
		}
	}


	//DESTRUCTOR
	sbat::DrawShip::~DrawShip()
	{

	}





	//MY

	void sbat::DrawShip::set_animations(sbat::Animation* explosion_anim, sbat::Animation* smoke_anim)
	{
		this->p_exposion_anim = explosion_anim;
		this->p_smoke_anim = smoke_anim;
	}

	void sbat::DrawShip::set_texture(std::vector<sf::Texture>& ship_textures)
	{
		for (int i = 0; i < ship_textures.size(); i++)
		{
			this->m_textures[i] = &ship_textures[i];
		}
		this->m_sprite.setTexture(*(this->m_textures[static_cast<int>(this->get_ship_type()) - 1]));
		this->set_ship_facing(this->get_ship_facing());
	}

	sf::FloatRect sbat::DrawShip::get_global_bounds()
	{
		return this->m_sprite.getGlobalBounds();
	}
	sf::FloatRect sbat::DrawShip::get_local_bounds()
	{
		return this->m_sprite.getLocalBounds();
	}

	void sbat::DrawShip::show()
	{
		this->m_hiden = 0;
	}
	void sbat::DrawShip::hide()
	{
		this->m_hiden = 1;
	}


	//BASE SHIP

	void	sbat::DrawShip::set_ship_type(const sbat::ShipType& type)
	{
		BaseShip::set_ship_type(type);
		this->m_sprite.setTexture(*(this->m_textures[static_cast<int>(this->get_ship_type()) - 1]));
		this->m_sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>((this->m_textures[static_cast<int>(this->get_ship_type()) - 1])->getSize().x), static_cast<int>((this->m_textures[static_cast<int>(this->get_ship_type()) - 1])->getSize().y)));
		this->set_ship_facing(this->get_ship_facing());
		this->m_cell_sprites.resize(static_cast<int>(type));
	}

	void	sbat::DrawShip::set_ship_facing(const sbat::ShipFacing& rotation)
	{
		BaseShip::set_ship_facing(rotation);
		if (get_ship_facing() == sbat::ShipFacing::RIGHT)
		{
			this->m_sprite.setRotation(180);
			this->m_sprite.setPosition(this->get_position());
			this->m_facing_position.x = static_cast<int>(this->m_sprite.getGlobalBounds().width);
			this->m_facing_position.y = static_cast<int>(this->m_sprite.getGlobalBounds().height);
		}
		else if (get_ship_facing() == sbat::ShipFacing::DOWN)
		{
			this->m_sprite.setRotation(270);
			this->m_sprite.setPosition(this->get_position());
			this->m_facing_position.x = 0;
			this->m_facing_position.y = static_cast<int>(m_sprite.getGlobalBounds().height);
		}
		else if (get_ship_facing() == sbat::ShipFacing::LEFT)
		{
			this->m_sprite.setRotation(0);
			this->m_sprite.setPosition(this->get_position());
			this->m_facing_position.x = 0;
			this->m_facing_position.y = 0;
		}
		else if (get_ship_facing() == sbat::ShipFacing::UP)
		{
			this->m_sprite.setRotation(90);
			this->m_sprite.setPosition(this->get_position());
			this->m_facing_position.x = static_cast<int>(m_sprite.getGlobalBounds().width);
			this->m_facing_position.y = 0;
		}
		m_sprite.setPosition(get_position().x + m_facing_position.x, get_position().y + m_facing_position.y);
	}

	void sbat::DrawShip::explode(const sbat::ShipCellPosition& position)
	{
		if (this->get_cell_state(position) == sbat::ShipCellState::EXPLODED)
			return;
		sbat::BaseShip::explode(position);

		this->m_cell_sprites[static_cast<int>(position)].setColor(sf::Color::White);
		this->m_explosion_animations.push_back(*this->p_exposion_anim);
		(this->m_explosion_animations.end()-1)->play();
		(this->m_explosion_animations.end() - 1)->scale();

		bool all_exploded = 1;
		for (int i = 0; i < static_cast<int>((this->get_ship_type())); i++)
		{
			if (this->get_cell_state(static_cast<sbat::ShipCellPosition>(i)) != sbat::ShipCellState::EXPLODED)
			{
				all_exploded = 0;
			}
		}
		if (all_exploded)
		{
			for (auto&& it : this->m_cell_sprites)
			{
				it.setColor(sf::Color::Transparent);
			}
		}
	}

	//TRANSFORMABLE

	void 	sbat::DrawShip::set_position(const float& x, const float& y)
	{
		sbat::Positionable::set_position(x, y);
		this->m_sprite.setPosition(x + m_facing_position.x, y + m_facing_position.y);
		if (this->get_ship_facing() == sbat::ShipFacing::DOWN || this->get_ship_facing() == sbat::ShipFacing::UP)
		{
			for (int i = 0; i < this->m_cell_sprites.size(); i++)
			{
				this->m_cell_sprites[i].setPosition(this->get_position().x, this->get_position().y + m_cell_sprites[i].getGlobalBounds().height);
			}
		}
		else if (this->get_ship_facing() == sbat::ShipFacing::RIGHT || this->get_ship_facing() == sbat::ShipFacing::LEFT)
		{
			for (int i = 0; i < this->m_cell_sprites.size(); i++)
			{
				this->m_cell_sprites[i].setPosition(this->get_position().x + m_cell_sprites[i].getGlobalBounds().width, this->get_position().y);
			}
		}


	}

	void	sbat::DrawShip::set_scale(const float& factorX, const float& factorY)
	{
		sbat::Scalable::set_scale(factorX, factorY);
		this->m_sprite.setScale(factorX, factorY);
		this->set_ship_facing(this->get_ship_facing());
		for (int i = 0; i < this->m_cell_sprites.size(); i++)
		{
			this->m_cell_sprites[i].setScale(this->get_scale());
		}
		if (this->get_ship_facing() == sbat::ShipFacing::DOWN || this->get_ship_facing() == sbat::ShipFacing::UP)
		{
			for (int i = 0; i < this->m_cell_sprites.size(); i++)
			{
				this->m_cell_sprites[i].setPosition(this->get_position().x, this->get_position().y + m_cell_sprites[i].getGlobalBounds().height);
			}
		}
		else if (this->get_ship_facing() == sbat::ShipFacing::RIGHT || this->get_ship_facing() == sbat::ShipFacing::LEFT)
		{
			for (int i = 0; i < this->m_cell_sprites.size(); i++)
			{
				this->m_cell_sprites[i].setPosition(this->get_position().x + m_cell_sprites[i].getGlobalBounds().width, this->get_position().y);
			}
		}
	}


	//UPDATABLE
	void sbat::DrawShip::update(sf::RenderWindow& window, const float& dt)
	{
		if (!m_hiden)
		{

		}

		for (auto&& it : this->m_explosion_animations)
		{
			it.update(window, dt);
		}
		for (auto&& it =this->m_explosion_animations.begin();it< this->m_explosion_animations.end();it++)
		{
			if (it->ended())
			{
				this->m_explosion_animations.erase(it);
				it++;
			}
		}

		for (auto&& it : this->m_smoke_animations)
		{
			it.update(window, dt);
		}
		for (auto&& it = this->m_smoke_animations.begin(); it < this->m_smoke_animations.end(); it++)
		{
			if (it->ended())
			{
				this->m_smoke_animations.erase(it);
				it++;
			}
		}
	}

	//DRAWABLE
	void	sbat::DrawShip::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (!m_hiden)
			target.draw(m_sprite, states);

		for (auto&& it : this->m_cell_sprites)
		{
			target.draw(it, states);
		}
		for (auto&& it : this->m_explosion_animations)
		{
			target.draw(it, states);
		}
		for (auto&& it : this->m_smoke_animations)
		{
			target.draw(it, states);
		}

	}

}

