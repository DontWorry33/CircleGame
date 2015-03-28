#include <iostream>

#ifndef TRANSITION_CPP
#define TRANSITION_CPP

using namespace std;

struct Transition
{
	sf::Texture bkg_img; //showing the bkg
	sf::Sprite bkg; 


	sf::Texture img1_img; //showing first element
	sf::Sprite img1;
	sf::Texture img2_img; //showing the second element
	sf::Sprite img2;
	sf::Texture img3_img; //showing the quote
	sf::Sprite img3;
	vector<sf::Sprite*> transit;


	Transition(const char* path1, const char* path2, const char* path3)
	{
		bkg_img.loadFromFile("../testscreens/Transit_0-Default.png");
		bkg.setTexture(bkg_img);
		img1_img.loadFromFile(path1);
		img1.setTexture(img1_img);
		img2_img.loadFromFile(path2);
		img2.setTexture(img2_img);
		img3_img.loadFromFile(path3);
		img3.setTexture(img3_img);

		transit.push_back(&img1);
		transit.push_back(&img2);
		transit.push_back(&img3);

	}

};




#endif