#include "DrawShipEnemy.h"



namespace sbat
{



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//CONSTRUCTOR

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sbat::DrawShipEnemy::DrawShipEnemy()
		:
		m_explosion_animations(),
		m_smoke_animations(),
		p_exposion_anim(nullptr),
		p_smoke_anim(nullptr),
		m_show_main_texture(0),
		m_cell_sprites()
	{

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sbat::DrawShipEnemy::DrawShipEnemy
	(
		std::vector<sf::Texture>& ship_textures,
		sbat::Animation* explosion_anim, sbat::Animation* smoke_anim,
		const sbat::ShipType& ship_type, const sbat::ShipFacing& ship_facing
	) :

		m_explosion_animations(),
		m_smoke_animations(),
		p_exposion_anim(explosion_anim),
		p_smoke_anim(smoke_anim),
		m_show_main_texture(0),
		m_cell_sprites()
	{
	
		m_textures = &ship_textures;

		this->m_cell_sprites.resize(static_cast<int>(ship_type));
		for (auto&& it : m_cell_sprites)
		{
			it.setTexture((*m_textures)[4]);
		}
		if (this->get_ship_facing() == sbat::ShipFacing::UP || this->get_ship_facing() == sbat::ShipFacing::DOWN)
		{
			for (int i = 0; i < m_cell_sprites.size(); i++)
			{
				m_cell_sprites[i].setTexture((*m_textures)[4]);
				m_cell_sprites[i].setPosition(0, (*m_textures)[0].getSize().y * i);
			}
		}
		else if (this->get_ship_facing() == sbat::ShipFacing::LEFT || this->get_ship_facing() == sbat::ShipFacing::RIGHT)
		{
			for (int i = 0; i < m_cell_sprites.size(); i++)
			{
				m_cell_sprites[i].setTexture((*m_textures)[4]);
				m_cell_sprites[i].setPosition((*m_textures)[0].getSize().x * i, 0);
			}
		}

		for (auto&& it : m_cell_sprites)
		{
			it.setTexture((*m_textures)[4]);
		}
		if (this->get_ship_facing() == sbat::ShipFacing::UP || this->get_ship_facing() == sbat::ShipFacing::DOWN)
		{
			for (int i = 0; i < m_cell_sprites.size(); i++)
			{
				m_cell_sprites[i].setTexture((*m_textures)[4]);
				m_cell_sprites[i].setPosition(0, (*m_textures)[0].getSize().y * i);
			}
		}
		else if (this->get_ship_facing() == sbat::ShipFacing::LEFT || this->get_ship_facing() == sbat::ShipFacing::RIGHT)
		{
			for (int i = 0; i < m_cell_sprites.size(); i++)
			{
				m_cell_sprites[i].setTexture((*m_textures)[4]);
				m_cell_sprites[i].setPosition((*m_textures)[0].getSize().x * i, 0);
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//DESTRUCTOR

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sbat::DrawShipEnemy::~DrawShipEnemy()
	{

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//MY

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void sbat::DrawShipEnemy::set_animations(sbat::Animation* explosion_anim, sbat::Animation* smoke_anim)
	{
		this->p_exposion_anim = explosion_anim;
		this->p_smoke_anim = smoke_anim;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void sbat::DrawShipEnemy::set_ship_texture(std::vector<sf::Texture>& ship_textures)
	{

		m_textures = &ship_textures;
		this->m_sprite.setTexture(((*m_textures)[static_cast<int>(this->get_ship_type()) - 1]));
		this->set_ship_facing(this->get_ship_facing());

		for (auto&& it : m_cell_sprites)
		{
			it.setTexture((*m_textures)[4]);
		}
		if (this->get_ship_facing() == sbat::ShipFacing::UP || this->get_ship_facing() == sbat::ShipFacing::DOWN)
		{
			for (int i = 0; i < m_cell_sprites.size(); i++)
			{
				m_cell_sprites[i].setTexture((*m_textures)[4]);
				m_cell_sprites[i].setPosition(0, (*m_textures)[0].getSize().y * i);
			}
		}
		else if (this->get_ship_facing() == sbat::ShipFacing::LEFT || this->get_ship_facing() == sbat::ShipFacing::RIGHT)
		{
			for (int i = 0; i < m_cell_sprites.size(); i++)
			{
				m_cell_sprites[i].setTexture((*m_textures)[4]);
				m_cell_sprites[i].setPosition((*m_textures)[0].getSize().x * i, 0);
			}
		}
	}



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sf::FloatRect sbat::DrawShipEnemy::get_cell_global_bounds(const sbat::ShipCellPosition& position)
	{
		sf::FloatRect res;
		if (this->get_ship_facing() == sbat::ShipFacing::UP || this->get_ship_facing() == sbat::ShipFacing::DOWN)
		{
			res = sf::FloatRect(0, static_cast<int>(position) * (*m_textures)[0].getSize().y, (*m_textures)[0].getSize().x, (*m_textures)[0].getSize().y);
		}
		else if (this->get_ship_facing() == sbat::ShipFacing::LEFT || this->get_ship_facing() == sbat::ShipFacing::RIGHT)
		{
			res = sf::FloatRect(static_cast<int>(position) * (*m_textures)[0].getSize().x, 0, (*m_textures)[0].getSize().x, (*m_textures)[0].getSize().y);
		}
		return this->get_Transfrom().transformRect(res);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	sf::FloatRect sbat::DrawShipEnemy::get_local_global_bounds(const sbat::ShipCellPosition& position)
	{
		sf::FloatRect res;
		if (this->get_ship_facing() == sbat::ShipFacing::UP || this->get_ship_facing() == sbat::ShipFacing::DOWN)
		{
			res = sf::FloatRect(0, static_cast<int>(position) * (*m_textures)[0].getSize().y, (*m_textures)[0].getSize().x, (*m_textures)[0].getSize().y);
		}
		else if (this->get_ship_facing() == sbat::ShipFacing::LEFT || this->get_ship_facing() == sbat::ShipFacing::RIGHT)
		{
			res = sf::FloatRect(static_cast<int>(position) * (*m_textures)[0].getSize().x, 0, (*m_textures)[0].getSize().x, (*m_textures)[0].getSize().y);
		}
		return res;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//BASE SHIP

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void	sbat::DrawShipEnemy::set_ship_type(const sbat::ShipType& type)
	{
		BaseShip::set_ship_type(type);
		this->m_sprite.setTexture(((*m_textures)[static_cast<int>(this->get_ship_type()) - 1]));
		this->m_sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(((*m_textures)[static_cast<int>(this->get_ship_type()) - 1]).getSize().x), static_cast<int>(((*m_textures)[static_cast<int>(this->get_ship_type()) - 1]).getSize().y)));
		this->set_ship_facing(this->get_ship_facing());
			
		this->m_cell_sprites.clear();
		this->m_cell_sprites.resize(static_cast<int>(this->get_ship_type()));
		if (this->get_ship_facing() == sbat::ShipFacing::UP || this->get_ship_facing() == sbat::ShipFacing::DOWN)
		{
			for (int i = 0; i < m_cell_sprites.size(); i++)
			{
				m_cell_sprites[i].setTexture((*m_textures)[4]);
				m_cell_sprites[i].setPosition(0, (*m_textures)[0].getSize().y * i);
			}
		}
		else if (this->get_ship_facing() == sbat::ShipFacing::LEFT || this->get_ship_facing() == sbat::ShipFacing::RIGHT)
		{
			for (int i = 0; i < m_cell_sprites.size(); i++)
			{
				m_cell_sprites[i].setTexture((*m_textures)[4]);
				m_cell_sprites[i].setPosition((*m_textures)[0].getSize().x * i,0);
			}
		}

	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void	sbat::DrawShipEnemy::set_ship_facing(const sbat::ShipFacing& rotation)
	{

		BaseShip::set_ship_facing(rotation);
		if (get_ship_facing() == sbat::ShipFacing::RIGHT)
		{
			this->m_sprite.setRotation(180);
			this->m_sprite.setPosition(static_cast<int>(this->m_sprite.getLocalBounds().width), static_cast<int>(this->m_sprite.getLocalBounds().height));

		}
		else if (get_ship_facing() == sbat::ShipFacing::DOWN)
		{
			this->m_sprite.setRotation(270);
			this->m_sprite.setPosition(0, static_cast<int>(m_sprite.getLocalBounds().width));
		}
		else if (get_ship_facing() == sbat::ShipFacing::LEFT)
		{
			this->m_sprite.setRotation(0);
			this->m_sprite.setPosition(0, 0);

		}
		else if (get_ship_facing() == sbat::ShipFacing::UP)
		{
			this->m_sprite.setRotation(90);
			this->m_sprite.setPosition(static_cast<int>(m_sprite.getLocalBounds().height), 0);
		}


		if (this->get_ship_facing() == sbat::ShipFacing::UP || this->get_ship_facing() == sbat::ShipFacing::DOWN)
		{
			for (int i = 0; i < m_cell_sprites.size(); i++)
			{
				m_cell_sprites[i].setTexture((*m_textures)[4]);
				m_cell_sprites[i].setPosition(0, (*m_textures)[0].getSize().y * i);
			}
		}
		else if (this->get_ship_facing() == sbat::ShipFacing::LEFT || this->get_ship_facing() == sbat::ShipFacing::RIGHT)
		{
			for (int i = 0; i < m_cell_sprites.size(); i++)
			{
				m_cell_sprites[i].setTexture((*m_textures)[4]);
				m_cell_sprites[i].setPosition((*m_textures)[0].getSize().x * i, 0);
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void sbat::DrawShipEnemy::explode(const sbat::ShipCellPosition& position)
	{
		sbat::BaseShip::explode(position);
		this->m_explosion_animations.push_back(*this->p_exposion_anim);
		(this->m_explosion_animations.end() - 1)->play();

		if (this->get_ship_facing() == sbat::ShipFacing::UP || this->get_ship_facing() == sbat::ShipFacing::DOWN)
		{
			(this->m_explosion_animations.end() - 1)->set_position
			(
				(*m_textures)[0].getSize().x / 2 - (this->m_explosion_animations.end() - 1)->get_global_bounds().width / 2,
				(*m_textures)[0].getSize().y / 2 - (this->m_explosion_animations.end() - 1)->get_global_bounds().height / 2 + static_cast<int>(position) * (*m_textures)[0].getSize().y
			);
		}
		else if (this->get_ship_facing() == sbat::ShipFacing::LEFT || this->get_ship_facing() == sbat::ShipFacing::RIGHT)
		{
			(this->m_explosion_animations.end() - 1)->set_position
			(
				(*m_textures)[0].getSize().x / 2 - (this->m_explosion_animations.end() - 1)->get_global_bounds().width / 2 + static_cast<int>(position) * (*m_textures)[0].getSize().x,
				(*m_textures)[0].getSize().y / 2 - (this->m_explosion_animations.end() - 1)->get_global_bounds().height / 2
			);
		}


		for (int j = 0; j < m_smokes_after_explosion; j++)
		{
			this->m_smoke_animations.push_back(*this->p_smoke_anim);
			(this->m_smoke_animations.end() - 1)->play();
			(this->m_smoke_animations.end() - 1)->loop(1);

			if (this->get_ship_facing() == sbat::ShipFacing::UP || this->get_ship_facing() == sbat::ShipFacing::DOWN)
			{
				(this->m_smoke_animations.end() - 1)->set_position
				(
					(rand() % (*m_textures)[0].getSize().x) - (this->m_smoke_animations.end() - 1)->get_global_bounds().width / 2,
					(rand() % (*m_textures)[0].getSize().y) - (this->m_smoke_animations.end() - 1)->get_global_bounds().height / 2 + static_cast<int>(position) * (*m_textures)[0].getSize().y
				);
			}
			else if (this->get_ship_facing() == sbat::ShipFacing::LEFT || this->get_ship_facing() == sbat::ShipFacing::RIGHT)
			{
				(this->m_smoke_animations.end() - 1)->set_position
				(
					(rand() % (*m_textures)[0].getSize().x) - (this->m_smoke_animations.end() - 1)->get_global_bounds().width / 2 + static_cast<int>(position) * (*m_textures)[0].getSize().x,
					(rand() % (*m_textures)[0].getSize().y) - (this->m_smoke_animations.end() - 1)->get_global_bounds().height / 2
				);
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//UPDATABLE

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void sbat::DrawShipEnemy::update(sf::RenderWindow& window, const float& dt, const sf::Event* event )
	{
		std::vector<int> need_delete;

		for (int i = 0; i < m_explosion_animations.size(); i++)
		{
			m_explosion_animations[i].update(window, dt);

			if (m_explosion_animations[i].ended())
			{
				need_delete.push_back(i);
			}

		}

		if (!m_show_main_texture)
		{
			bool exploded=1;
			for (int i = 0; i < static_cast<int>(this->get_ship_type()); i++)
			{
				if (this->get_cell_state(static_cast<sbat::ShipCellPosition>(i)) != sbat::ShipCellState::EXPLODED)
				{
					exploded = 0;
				}
			}
			if (exploded && static_cast<int>(this->get_ship_type())!=0)
			{
				m_show_main_texture = 1;
			}
		}

		for (int i = need_delete.size() - 1; i >= 0; i--)
		{
			m_explosion_animations.erase(m_explosion_animations.begin() + (need_delete[i]));
		}

		for (auto&& it : m_smoke_animations)
		{
			it.update(window, dt);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//DRAWABLE

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void	sbat::DrawShipEnemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= get_Transfrom();

		if (!m_hiden)
		{
			if (this->m_show_main_texture)
				target.draw(m_sprite, states);
			else
			{
				for (int i=0;i<m_cell_sprites.size();i++)
				{
					if (this->get_cell_state(static_cast<sbat::ShipCellPosition>(i)) == sbat::ShipCellState::EXPLODED)
						target.draw(m_cell_sprites[i], states);
				}
			}
			
			for (auto&& it : this->m_smoke_animations)
			{
				target.draw(it, states);
			}
			for (auto&& it : this->m_explosion_animations)
			{
				target.draw(it, states);
			}
		}


	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




}