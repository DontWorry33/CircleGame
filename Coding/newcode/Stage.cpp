#include "Entity.cpp"
#include <iostream>

#ifndef STAGE_H
#define STAGE_H


struct Stage
{

	sf::Texture backgroundTexture;
	sf::Sprite background;

	Entity** lines;
	Entity** platforms;
	Entity** switches;

	int lineCount;
	int platformCount;
	int switchCount;

	//Oven* oven;
};



struct Stage1 : public Stage
{

	Stage1(const char* bkg_filename, const char* tex_filename)
	{

		//oven = new Oven(200,780);

		lineCount = 5;
		lines = new Entity* [lineCount];

		platformCount = 1;
		platforms = new Entity* [platformCount];

		switchCount = 1;
		switches = new Entity* [switchCount];

		backgroundTexture.loadFromFile(bkg_filename);
		background.setTexture(backgroundTexture);


		//Line standing_border(tex_filename);
		//Line red("../../Stage_Images/Red_Line_Test.png",285,200);
		//Line blue("../../Stage_Images/Blue_Line_Test.png",375,260);
		//Line green("../../Stage_Images/Green_Line_Test.png",450,200);
		lines[0] = new Line (tex_filename);
		lines[1] = new Line ("../../Stage_Images/Red_Line_Test.png",285,200);
		lines[2] = new Line ("../../Stage_Images/Blue_Line_Test.png",375,260);
		lines[3] = new Line ("../../Stage_Images/Green_Line_Test.png",450,200);
		lines[4] = new Line ("../../Stage_Images/Oven.png", 1000, 780, true);


		switches[0] = new Switch(300,780,0);

		//Platform p1("../../Stage_Images/ActivatedPlatform.png");
		//Platform oven("../../Stage_Images/Oven.png",400,750,300);
		platforms[0] = new Platform ("../../Stage_Images/ActivatedPlatform.png");
	}


};

struct Stage2 : public Stage
{

	Stage2(const char* bkg_filename)
	{
		lineCount = 4;
		lines = new Entity* [lineCount];

		platformCount = 1;
		platforms = new Entity* [platformCount];


		backgroundTexture.loadFromFile(bkg_filename);
		background.setTexture(backgroundTexture);

		lines[0] = new Line("../../Stage_Images/Red_Line_Test.png",800,650);
		lines[1] = new Line("../../Stage_Images/Blue_Line_Test.png",550,200);
		lines[2] = new Line("../../Stage_Images/Green_Line_Test.png",700,400);
		lines[3] = new Line ("../../Stage_Images/Oven.png", 300, 780, true);


		platforms[0] = new Platform ("../../Stage_Images/ActivatedPlatform.png");

	}

};


#endif