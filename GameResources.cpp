#include "GameResources.h"

std::vector<sf::Texture> sbat::GameResources::m_ship_textures = std::vector<sf::Texture>();
std::unordered_map<std::string, sf::Texture> sbat::GameResources::m_textures = std::unordered_map<std::string, sf::Texture>();
std::unordered_map<std::string, sbat::Animation> sbat::GameResources::m_animations = std::unordered_map<std::string, sbat::Animation>();
std::unordered_map<std::string, sf::Font> sbat::GameResources::m_fonts = std::unordered_map<std::string, sf::Font>();

namespace sbat
{

	//CONSTRUCTOR
	GameResources::GameResources()
	{
		////////////////////////////////////////////////////////////////////////////////
		//TEXSTURES

		m_textures["FIELD_CROSS"].loadFromFile("resources\\textures\\FIELD_CROSS.png");
		m_textures["BACKGROUND"].loadFromFile("resources\\textures\\background.jpg");
		m_textures["BACKGROUND_1"].loadFromFile("resources\\textures\\BACKGROUND_1.jpg");
		m_textures["BACKGROUND_2"].loadFromFile("resources\\textures\\BACKGROUND_2.jpg");
		m_textures["BACKGROUND_3"].loadFromFile("resources\\textures\\BACKGROUND_3.jpg");
		m_textures["BACKGROUND_4"].loadFromFile("resources\\textures\\BACKGROUND_4.jpg");
		m_textures["BACKGROUND_5"].loadFromFile("resources\\textures\\BACKGROUND_5.jpg");
		m_textures["BACKGROUND_6"].loadFromFile("resources\\textures\\BACKGROUND_6.jpg");
		m_textures["GAME_BACKGROUND"].loadFromFile("resources\\textures\\GAME_BACKGROUND.jpg");

		for (auto& it : m_textures)
		{
			it.second.setSmooth(1);
		}
		
		
		////////////////////////////////////////////////////////////////////////////////
		//SHIP TEXTURES
		m_ship_textures.resize(5);

		m_ship_textures[0].loadFromFile("ship_images\\ship_1.png");
		m_ship_textures[1].loadFromFile("ship_images\\ship_2.png");
		m_ship_textures[2].loadFromFile("ship_images\\ship_3.png");
		m_ship_textures[3].loadFromFile("ship_images\\ship_4.png");
		m_ship_textures[4].loadFromFile("ship_images\\ship_cell.png");


		////////////////////////////////////////////////////////////////////////////////
		//ANIMATIONS

		m_animations["EXPLOSION_1"].load_from_file("resources\\animations\\EXPLOSION_1.xml");

		m_animations["EXPLOSION_2"].load_from_file("resources\\animations\\EXPLOSION_2.xml");
		m_animations["EXPLOSION_2"].set_scale(1.5f, 1.5f);

		m_animations["SMOKE_1"].load_from_file("resources\\animations\\SMOKE_1.xml");

		m_animations["WATER_SPLASH_1"].load_from_file("resources\\animations\\WATER_SPLASH_1.xml");

		m_animations["FIELD_CROSS_1"].load_from_file("resources\\animations\\FIELD_CROSS_1.xml");

		m_animations["SPARK_ANIM"].load_from_file("resources\\animations\\SPARK_ANIM.xml");

		m_animations["FIREWORK_1"].load_from_file("resources\\animations\\FIREWORK_1.xml");

		////////////////////////////////////////////////////////////////////////////////
		//FONTS

		m_fonts["MY_FONT"].loadFromFile("resources\\fonts\\font.ttf");
	}

	//DESTRUCTOR
	GameResources::~GameResources()
	{

	}

	//MY

	sf::Font& GameResources::get_font(const std::string& name)
	{
		return m_fonts[name];
	}

	sbat::Animation& GameResources::get_animation(const std::string& name)
	{
		return m_animations[name];
	}

	sf::Texture& GameResources::get_texture(const std::string& name)
	{
		return m_textures[name];
	}

	std::vector<sf::Texture>& GameResources::get_ship_textures()
	{
		return m_ship_textures;
	}


}