#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#ifndef OPTION_CPP
#define OPTION_CPP

struct Option
{
	//each option contains a texture/sprite
	sf::Texture option_img;
	sf::Sprite option;

	//We only need the top left and bottom right positions as we can get the rest of the outline with basic math

	//top-left bounds (mouse pos relative to window)
	sf::Vector2f option_tl_bound; 

	//bottom right bounds (mouse pos relative to window)
	sf::Vector2f option_br_bound; 


	Option(const char* filepath)
	{
		option_img.loadFromFile(filepath);
		option.setTexture(option_img);
	}

	Option(const char* filepath, float tlx, float tly, float brx, float bry)
	{
		//assigning variables
		option_img.loadFromFile(filepath);
		option.setTexture(option_img);
		option_tl_bound.x = tlx;
		option_tl_bound.y = tly;
		option_br_bound.x = brx;
		option_br_bound.y = bry;

	}

	void setBounds(float tlx, float tly, float brx, float bry)
	{
		option_tl_bound.x = tlx;
		option_tl_bound.y = tly;
		option_br_bound.x = brx;
		option_br_bound.y = bry;
	}

};

#endif