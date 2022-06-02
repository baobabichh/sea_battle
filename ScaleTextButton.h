#ifndef SBAT_SCALETEXTBUTTON_H
#define SBAT_SCALETEXTBUTTON_H

#include "BaseButton.h"
#include "TextButton.h"
#include <sstream>

namespace sbat
{

	class ScaleTextButton
		:
		public TextButton
	{
	public:

		ScaleTextButton();

		virtual~ScaleTextButton();

		//MY

		

		void set_scale_val(float scale);
		float get_scale_val();

		//UPDATABLE

		void update(sf::RenderWindow& window, const float& dt, const sf::Event* event = nullptr) override;

	protected:

		
		float m_scale_val , m_curr_scale_val , m_speed;


		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};





}



#endif // !SBAT_SCALETEXTBUTTON_H
