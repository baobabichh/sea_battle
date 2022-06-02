#ifndef SBAT_GAMERESOURCES_H
#define SBAT_GAMERESOURCES_H

#include <vector>
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include <unordered_map>

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define DEFAULT_SMOKE_ANIM					"SMOKE_1"
#define DEFAULT_EXPLOSION_ANIM				"EXPLOSION_2"
#define DEFAULT_WATER_SPLASH_ANIM			"WATER_SPLASH_1"
#define DEFAULT_FIELD_CROSS_ANIM			"FIELD_CROSS_1"


#define DEFAULT_FONT						"MY_FONT"


#define DEFAULT_FIELD_CROSS_TEXTURE			"FIELD_CROSS"

////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace sbat
{

	class GameResources
	{
	public:
		
		//CONSTRUCTOR
		GameResources();

		//DESTRUCTOR
		virtual ~GameResources();

		
		//MY

		static sf::Font& get_font(const std::string& name);

		static sbat::Animation& get_animation(const std::string& name);

		static sf::Texture& get_texture(const std::string& name);

		static std::vector<sf::Texture>& get_ship_textures();

	private:

		static std::vector<sf::Texture> m_ship_textures;
		static  std::unordered_map<std::string, sf::Font> m_fonts;
		static  std::unordered_map<std::string, sf::Texture> m_textures;
		static  std::unordered_map<std::string, sbat::Animation> m_animations;
	};


}


#endif // !SBAT_GAMERESOURCES_H






