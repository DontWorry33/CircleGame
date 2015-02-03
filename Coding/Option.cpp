#ifndef OPTION_CPP
#define OPTION_CPP

struct Option
{
	sf::Texture option_img;
	sf::Sprite option;
	sf::Vector2f option_tl_bound; //top-left bounds (mouse pos relative to window)
	sf::Vector2f option_br_bound; //bottom right bounds (mouse pos relative to window)
	Option(const char* filepath, float tlx, float tly, float brx, float bry)
	{
		option_img.loadFromFile(filepath);
		option.setTexture(option_img);
		option_tl_bound.x = tlx;
		option_tl_bound.y = tly;
		option_br_bound.x = brx;
		option_br_bound.y = bry;

	}
};

#endif