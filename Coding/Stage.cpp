#include "Entity.cpp"
#include <iostream>

#ifndef STAGE_H
#define STAGE_H


struct Stage
{

	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Texture bouleTexture;

	Entity** lines;
	Entity** platforms;
	Entity** switches;
	Entity** portals;


	int lineCount;
	int platformCount;
	int switchCount;
	int portalCount;

	Oven* oven;
};



struct Stage1 : public Stage
{

	Stage1(const char* bkg_filename, const char* tex_filename)
	{

        //Dedie: I may need to redesign Stage1. As a platform moves, it doesn't move the Baker with it. No other stage has this feature, though, so the cheapest fix would be for a revamp. We'll see what happens. Gravity will need to be fixed for me, at least. Mac seems to have heavier objects.... And lastly, I need to increase the repulsion force of Roti's second activation. Because right now, Baker and Roti can't clear even the smallest gaps.

		lineCount = 1;
		lines = new Entity* [lineCount];

		platformCount = 1;
		platforms = new Entity* [platformCount];

		switchCount = 1;
		switches = new Entity* [switchCount];

		portalCount = 3;
		portals = new Entity* [portalCount];
		backgroundTexture.loadFromFile(bkg_filename);

		bouleTexture.loadFromFile("../Stage_Images/Stage1/IntroStage_Boule.png");
		background.setTexture(backgroundTexture);


		lines[0] = new Line ("../Stage_Images/Stage1/quad4Ver1.png", 770,782);


		switches[0] = new Switch(1000,780,0,0);


		platforms[0] = new Platform ("../Stage_Images/Stage1/quad3VerPlatform1.png", 490, 783, 500);

		portals[0] = new Portal (100,600,0);
		portals[1] = new Portal(900,600,1);
		portals[2] = new Portal(1110,600,2);

		oven = new Oven(200,780);
	}

	~Stage1()
	{
		std::cout << "destructing stg 1" << std::endl;
		for (int x=0; x<lineCount; x++) delete lines[x];
		if (lineCount>0) delete[] lines;
		for (int x=0; x<platformCount; x++) delete platforms[x];
		if (platformCount > 0) delete[] platforms;
		for (int x=0; x<switchCount; x++) delete switches[x];
		if (switchCount>0) delete[] switches;
	}


};

struct Stage2 : public Stage
{

	Stage2(const char* bkg_filename)
	{
        
        //Dedie: There's a bug in here that Hussain's taking care of. When Roti's power is activated on the platform[0], everyone shoots to the top. ): Other than that, things are looking good.
        
		lineCount = 6;
		lines = new Entity* [lineCount];

		platformCount = 2;
		platforms = new Entity* [platformCount];

		switchCount = 2;
        switches = new Entity* [switchCount];
        
        
		portalCount = 1;
        portals = new Entity* [portalCount];

		backgroundTexture.loadFromFile(bkg_filename);
		bouleTexture.loadFromFile("../Stage_Images/Stage2/StageTwo_Boule.png");
		background.setTexture(backgroundTexture);

		
        lines[0] = new Line("../Stage_Images/Stage2/quad1Hor1.png", 218, 400);
        lines[1] = new Line("../Stage_Images/Stage2/quad2Hor1.png", 861, 394);
        lines[2] = new Line("../Stage_Images/Stage2/quad2Hor2.png", 784, 179);
        lines[3] = new Line("../Stage_Images/Stage2/quad3Hor1.png", 78, 682);
        lines[4] = new Line("../Stage_Images/Stage2/quad3Ver1.png", 178, 700);
        lines[5] = new Line("../Stage_Images/Stage2/quad4Hor1.png", 776, 790);
        
        switches[0] = new Switch(760,700,0,1);
        switches[1] = new Switch(840,700,1,1);

        platforms[0] = new Platform ("../Stage_Images/Stage2/quad1VerPlatform1.png", 530, 360, -30);
        platforms[1] = new Platform ("../Stage_Images/Stage2/quad2VerPlatform1.png", 710, 160, -50);
        
        portals[0] = new Portal (995,740,0);

		oven = new Oven(780, 165);


	}

	~Stage2()
	{
		std::cout << "destructing stg 2" << std::endl;
		for (int x=0; x<lineCount; x++) delete lines[x];
		if (lineCount>0) delete[] lines;
		for (int x=0; x<platformCount; x++) delete platforms[x];
		if (platformCount > 0) delete[] platforms;
		for (int x=0; x<switchCount; x++) delete switches[x];
		if (switchCount>0) delete[] switches;
		for (int x=0; x<portalCount; x++) delete portals[x];
		if (portalCount>0) delete[] portals; 
	}
};



struct Stage3 : public Stage
{
    
    Stage3(const char* bkg_filename, const char* tex_filename)
    {

        
        lineCount = 3;
        lines = new Entity* [lineCount];
        
        platformCount = 1;
        platforms = new Entity* [platformCount];
        
        switchCount = 1;
        switches = new Entity* [switchCount];
        
        portalCount = 3;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage3/StageThree_Boule.png");
        background.setTexture(backgroundTexture);
        
        
        
        lines[0] = new Line (tex_filename);
        lines[1] = new Line ("../Stage_Images/Red_Line_Test.png",250,780);
        lines[2] = new Line ("../Stage_Images/Blue_Line_Test.png",350,150);
        
        
        switches[0] = new Switch(300,780,3,1000,300);
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage1/quad3HorPlatform1.png", 700, 780, 300);
        
        portals[0] = new Portal (100,780,0);
        portals[1] = new Portal(900,780,1);
        portals[2] = new Portal(1110,780,2);
        
        oven = new Oven(1000,10);
    }
    
    ~Stage3()
    {
        std::cout << "destructing stg 1" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
    }
    
    
};


struct Stage4 : public Stage
{
    
    Stage4(const char* bkg_filename, const char* tex_filename)
    {
        
        lineCount = 3;
        lines = new Entity* [lineCount];
        
        platformCount = 1;
        platforms = new Entity* [platformCount];
        
        switchCount = 1;
        switches = new Entity* [switchCount];
        
        portalCount = 3;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage1/IntroStage_Boule.png");
        background.setTexture(backgroundTexture);
        
        
        lines[0] = new Line (tex_filename);
        lines[1] = new Line ("../Stage_Images/Red_Line_Test.png",250,780);
        lines[2] = new Line ("../Stage_Images/Blue_Line_Test.png",350,150);
  
        
        
        switches[0] = new Switch(300,780,3,1000,300);

        
        platforms[0] = new Platform ("../Stage_Images/Stage1/quad3HorPlatform1.png", 700, 780, 300);
        
        portals[0] = new Portal (100,780,0);
        portals[1] = new Portal(900,780,1);
        portals[2] = new Portal(1110,780,2);
        
        oven = new Oven(1000,10);
    }
    
    ~Stage4()
    {
        std::cout << "destructing stg 1" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
    }
    
    
};


struct Stage5 : public Stage
{
    
    Stage5(const char* bkg_filename, const char* tex_filename)
    {
        
        lineCount = 3;
        lines = new Entity* [lineCount];
        
        platformCount = 1;
        platforms = new Entity* [platformCount];
        
        switchCount = 1;
        switches = new Entity* [switchCount];
        
        portalCount = 3;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage1/IntroStage_Boule.png");
        background.setTexture(backgroundTexture);
        
        
        lines[0] = new Line (tex_filename);
        lines[1] = new Line ("../Stage_Images/Red_Line_Test.png",250,780);
        lines[2] = new Line ("../Stage_Images/Blue_Line_Test.png",350,150);
     
        
        
        switches[0] = new Switch(300,780,3,1000,300);
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage1/quad3HorPlatform1.png", 700, 780, 300);
        
        portals[0] = new Portal (100,780,0);
        portals[1] = new Portal(900,780,1);
        portals[2] = new Portal(1110,780,2);
        
        oven = new Oven(1000,10);
    }
    
    ~Stage5()
    {
        std::cout << "destructing stg 1" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
    }
    
    
};


struct Stage6 : public Stage
{
    
    Stage6(const char* bkg_filename, const char* tex_filename)
    {
        
        lineCount = 3;
        lines = new Entity* [lineCount];
        
        platformCount = 1;
        platforms = new Entity* [platformCount];
        
        switchCount = 1;
        switches = new Entity* [switchCount];
        
        portalCount = 3;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage1/IntroStage_Boule.png");
        background.setTexture(backgroundTexture);
        
  
        lines[0] = new Line (tex_filename);
        lines[1] = new Line ("../Stage_Images/Red_Line_Test.png",250,780);
        lines[2] = new Line ("../Stage_Images/Blue_Line_Test.png",350,150);

        
        
        switches[0] = new Switch(300,780,3,1000,300);
        
        platforms[0] = new Platform ("../Stage_Images/Stage1/quad3HorPlatform1.png", 700, 780, 300);
        
        portals[0] = new Portal (100,780,0);
        portals[1] = new Portal(900,780,1);
        portals[2] = new Portal(1110,780,2);
        
        oven = new Oven(1000,10);
    }
    
    ~Stage6()
    {
        std::cout << "destructing stg 1" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
    }
    
    
};


#endif
