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
		lines[1] = new Line ("../Stage_Images/Red_Line_Test.png",285,750);
		lines[2] = new Line ("../Stage_Images/Blue_Line_Test.png",350,550);
		lines[3] = new Line ("../Stage_Images/Green_Line_Test.png",450,200);
		lines[4] = new Line ("../Stage_Images/Universal_StageParts/Stage_Oven_Default.png", 1000, 780, true);


		switches[0] = new Switch(300,780,0);

		//Platform p1("../../Stage_Images/ActivatedPlatform.png");
		//Platform oven("../../Stage_Images/Oven.png",400,750,300);
		platforms[0] = new Platform ("../Stage_Images/Stage1/quad3HorPlatform1.png", 700, 780, 300);
	}


};

struct Stage2 : public Stage
{

	Stage2(const char* bkg_filename)
	{
		lineCount = 6;
		lines = new Entity* [lineCount];

		platformCount = 1;
		platforms = new Entity* [platformCount];

		switchCount = 0;
		
		backgroundTexture.loadFromFile(bkg_filename);
		background.setTexture(backgroundTexture);

		//lines[0] = new Line("../Stage_Images/Red_Line_Test.png",800,650);
		//lines[1] = new Line("../Stage_Images/Blue_Line_Test.png",550,200);
		//lines[2] = new Line("../Stage_Images/Green_Line_Test.png",700,400);
		lines[0] = new Line ("../Stage_Images/Universal_StageParts/Stage_Oven_Default.png", 780, 165, true);
        lines[1] = new Line("../Stage_Images/Stage2/quad1Hor1.png", 218, 400);
        lines[2] = new Line("../Stage_Images/Stage2/quad2Hor1.png", 861, 394);
        lines[3] = new Line("../Stage_Images/Stage2/quad2Hor2.png", 784,179);
        lines[4] = new Line("../Stage_Images/Stage2/quad3Hor1.png", 78, 682);
        lines[5] = new Line("../Stage_Images/Stage2/quad3Ver1.png", 178, 700);
        //lines[6] = new Line("../Stage_Images/Stage2/quad4Hor1.png", 776, 750);
        



		//platforms[0] = new Platform ("../Stage_Images/Stage1/quad3HorPlatform1.png");
        platforms[0] = new Platform ("../Stage_Images/Stage2/quad1VerPlatform1.png");

	}

};


#endif
