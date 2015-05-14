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

    sf::Vector2f bakerStartPos;
    
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

        //Dedie: Done.

        bakerStartPos.x = 600;
        bakerStartPos.y = 700;
        
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

		switches[0] = new Switch("../Stage_Images/Stage1/quad4Switch1.png", 1000, 784, 0, 0);

		platforms[0] = new Platform ("../Stage_Images/Stage1/quad3VerPlatform1.png", 490, 783, 500, 1);

		portals[0] = new Portal (900,600,0);
		portals[1] = new Portal(100,600,1);
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
        for (int x=0; x<portalCount; x++) delete portals[x];
        if (portalCount>0) delete[] portals;

        delete oven;
	}


};


struct Stage2 : public Stage
{

	Stage2(const char* bkg_filename)
	{
        
        bakerStartPos.x = 500;
        bakerStartPos.y = 780;
        
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
        lines[2] = new Line("../Stage_Images/Stage2/quad2Hor2.png", 835, 179);
        lines[3] = new Line("../Stage_Images/Stage2/quad3Hor1.png", 78, 682);
        lines[4] = new Line("../Stage_Images/Stage2/quad3Ver1.png", 178, 700);
        lines[5] = new Line("../Stage_Images/Stage2/quad4Hor1.png", 776, 790);
        
        switches[0] = new Switch("../Stage_Images/Stage2/quad4Switch1.png", 1143, 784, 0, 1);
        switches[1] = new Switch("../Stage_Images/Stage2/quad3Switch1.png", 100, 784, 1, 1);

        platforms[0] = new Platform ("../Stage_Images/Stage2/quad1VerPlatform1.png", 530, 360, -30, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage2/quad2VerPlatform1.png", 710, 160, -50, 0);
        
        portals[0] = new Portal (1000,770,0);

		oven = new Oven(870, 165);
        


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
        delete oven;
	}
};



struct Stage3 : public Stage
{
    
    Stage3(const char* bkg_filename)
    {
 
        bakerStartPos.x = 900;
        bakerStartPos.y = 100;
 
        lineCount = 7;
        lines = new Entity* [lineCount];
        
        platformCount = 3;
        platforms = new Entity* [platformCount];
        
        switchCount = 3;
        switches = new Entity* [switchCount];
        
        portalCount = 1;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage3/StageThree_Boule.png");
        background.setTexture(backgroundTexture);
        
        
        lines[0] = new Line ("../Stage_Images/Stage3/quad1Hor1.png", 271, 235);
        lines[1] = new Line ("../Stage_Images/Stage3/quad1Ver1.png", 520, 428);
        lines[2] = new Line ("../Stage_Images/Stage3/quad2Hor1.png", 630, 428);
        lines[3] = new Line ("../Stage_Images/Stage3/quad2Hor2.png", 1110, 220);
        lines[4] = new Line ("../Stage_Images/Stage3/quad3Hor1.png", 89, 640);
        lines[5] = new Line ("../Stage_Images/Stage3/quad3Hor2.png", 387, 429);
        lines[6] = new Line ("../Stage_Images/Stage3/quad4Hor1.png", 1084, 785);
      
        
        switches[0] = new Switch("../Stage_Images/Stage3/quad1Switch1.png", 262, 195, 1, 4);
        switches[1] = new Switch("../Stage_Images/Stage3/quad2Switch1.png", 1156, 182, 0, 4);
        switches[2] = new Switch("../Stage_Images/Stage3/quad4Switch1.png", 1159, 700, 2, 1);
       
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage3/quad1VerPlatform1.png", 384, 170, 550, 0); //Should move down
        platforms[1] = new Platform ("../Stage_Images/Stage3/quad4HorPlatform1.png", 968, 428, 100, 0); //Should disappear
        platforms[2] = new Platform ("../Stage_Images/Stage3/quad3VerPlatform1.png", 361, 771, 500, 0);
        
        portals[0] = new Portal (470,171,0);
        
        oven = new Oven(464,388);
        
    }
    
    ~Stage3()
    {
        std::cout << "destructing stg 3" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
        for (int x=0; x<portalCount; x++) delete portals[x];
        if (portalCount>0) delete[] portals;
        delete oven;
    }
    
    
};


struct Stage4 : public Stage
{
    
    Stage4(const char* bkg_filename)
    {
        //Dedie: Done.
        
        bakerStartPos.x = 600;
        bakerStartPos.y = 600;
        
        lineCount = 4;
        lines = new Entity* [lineCount];
        
        platformCount = 2;
        platforms = new Entity* [platformCount];
        
        switchCount = 2;
        switches = new Entity* [switchCount];
        
        portalCount = 0;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage4/StageFour_Boule.png");
        background.setTexture(backgroundTexture);

        
        lines[0] = new Line ("../Stage_Images/Stage4/quad1Ver1.png", 412, 414);
        lines[2] = new Line ("../Stage_Images/Stage4/quad2Hor1.png", 600, 302);
        lines[1] = new Line ("../Stage_Images/Stage4/quad2Ver1.png", 788, 414);
        lines[3] = new Line ("../Stage_Images/Stage4/quad4Hor1.png", 600, 782);

        platforms[0] = new Platform ("../Stage_Images/Stage4/quad3VerPlatform1.png", 170, 1175, 520, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage4/quad4VerPlatform1.png", 1022, 1175, 520, 0);

        switches[0] = new Switch("../Stage_Images/Stage4/quad3Switch1.png", 433, 710, 0, 1);
        switches[1] = new Switch("../Stage_Images/Stage4/quad4Switch1.png", 768, 710, 1, 1);
        
        
        oven = new Oven(600, 264);
    }
    
    ~Stage4()
    {
        std::cout << "destructing stg 4" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
        for (int x=0; x<portalCount; x++) delete portals[x];
        if (portalCount>0) delete[] portals;
        delete oven;
    }
    
    
};


struct Stage5 : public Stage
{
    
    Stage5(const char* bkg_filename)
    {
        //Dedie: Done.
        
        bakerStartPos.x = 212;
        bakerStartPos.y = 248;
        
        lineCount = 5;
        lines = new Entity* [lineCount];
        
        platformCount = 3;
        platforms = new Entity* [platformCount];
        
        switchCount = 3;
        switches = new Entity* [switchCount];
        
        portalCount = 3;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage5/StageFive_Boule.png");
        background.setTexture(backgroundTexture);
        
        lines[0] = new Line ("../Stage_Images/Stage5/quad2Hor1.png", 836, 241);
        lines[1] = new Line ("../Stage_Images/Stage5/quad3Hor1.png", 206, 426);
        lines[2] = new Line ("../Stage_Images/Stage5/quad3Hor2.png", 495, 621);
        lines[3] = new Line ("../Stage_Images/Stage5/quad4Hor1.png", 887, 466);
        lines[4] = new Line ("../Stage_Images/Stage5/quad4Ver1.png", 1010, 622);
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage5/quad2VerPlatform1.png", 610, 564, 300, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage5/quad2HorPlatform1.png", 1130, 242, 242, 0);
        platforms[2] = new Platform ("../Stage_Images/Stage5/quad4VerPlatform1.png", 660, 770, 719, 0);
        
        switches[0] = new Switch("../Stage_Images/Stage5/quad1Switch1.png", 360, 395, 0, 1);
        switches[1] = new Switch("../Stage_Images/Stage5/quad3Switch1.png", 102, 780, 2, 4);
        switches[2] = new Switch("../Stage_Images/Stage5/quad4Switch1.png", 968, 435, 1, 4);
        
        portals[0] = new Portal (1110,120,0);
        portals[1] = new Portal (330,750,2);
        portals[2] = new Portal (60,380,1);
        
        
        oven = new Oven(480, 780);
    }
    
    ~Stage5()
    {
        std::cout << "destructing stg 5" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
        for (int x=0; x<portalCount; x++) delete portals[x];
        if (portalCount>0) delete[] portals;
        delete oven;
    }
    
    
};


struct Stage6 : public Stage
{
    
    Stage6(const char* bkg_filename)
    {
        //Dedie: Done.
        
        bakerStartPos.x = 995;
        bakerStartPos.y = 50;

        lineCount = 7;
        lines = new Entity* [lineCount];
        
        platformCount = 4;
        platforms = new Entity* [platformCount];
        
        switchCount = 4;
        switches = new Entity* [switchCount];
        
        portalCount = 2;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage6/StageSix_Boule.png");
        background.setTexture(backgroundTexture);
        
  
        lines[0] = new Line ("../Stage_Images/Stage6/quad1Hor1.png", 308, 371);
        lines[1] = new Line ("../Stage_Images/Stage6/quad2Hor1.png", 694, 371);
        lines[2] = new Line ("../Stage_Images/Stage6/quad2Hor2.png", 1048, 200);
        lines[3] = new Line ("../Stage_Images/Stage6/quad3Hor1.png", 100, 830);
        lines[4] = new Line ("../Stage_Images/Stage6/quad4Hor1.png", 758, 598);
        lines[5] = new Line ("../Stage_Images/Stage6/quad4Hor2.png", 1112, 830);
        lines[6] = new Line ("../Stage_Images/Stage6/quad4Ver1.png", 936, 597);
        
        switches[0] = new Switch("../Stage_Images/Stage6/quad1Switch1.png", 280,333,3,4);
        switches[1] = new Switch("../Stage_Images/Stage6/quad2Switch1.png", 1146,163,0,4);
        switches[2] = new Switch("../Stage_Images/Stage6/quad3Switch1.png", 46,732,2,4);
        switches[3] = new Switch("../Stage_Images/Stage6/quad4Switch1.png", 1168,732,1,5);

        
        platforms[0] = new Platform ("../Stage_Images/Stage6/quad1HorPlatform1.png", 98, 180, 0, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage6/quad1VerPlatform1.png", 440, 376, 550, 0);
        platforms[2] = new Platform ("../Stage_Images/Stage6/quad2HorPlatform1.png", 1078, 364, 0, 0);
        platforms[3] = new Platform ("../Stage_Images/Stage6/quad4VerPlatform1.png", 742, 540, 0, 0);
        
        portals[0] = new Portal(90,130,0);
        portals[1] = new Portal(940,150,1);
        
        oven = new Oven(870,560);
    }
    
    ~Stage6()
    {
        std::cout << "destructing stg 6" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
        for (int x=0; x<portalCount; x++) delete portals[x];
        if (portalCount>0) delete[] portals;
        delete oven;
    }
    
    
};


struct Stage7 : public Stage
{
    
    Stage7(const char* bkg_filename)
    {
        //Dedie: Done.
        
        bakerStartPos.x = 135;
        bakerStartPos.y = 620;
        
        lineCount = 4;
        lines = new Entity* [lineCount];
        
        platformCount = 2;
        platforms = new Entity* [platformCount];
        
        switchCount = 2;
        switches = new Entity* [switchCount];
        
        portalCount = 1;
        portals = new Entity* [portalCount];
        
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage7/StageSeven_Boule.png");
        background.setTexture(backgroundTexture);
        
        
        lines[0] = new Line ("../Stage_Images/Stage7/quad1Hor1.png", 148, 249);
        lines[1] = new Line ("../Stage_Images/Stage7/quad2Hor1.png", 1078, 314);
        lines[2] = new Line ("../Stage_Images/Stage7/quad3Ver1.png", 569, 814);
        lines[3] = new Line ("../Stage_Images/Stage7/quad4Hor1.png", 1031, 814);
        
        switches[0] = new Switch("../Stage_Images/Stage7/quad2Switch1.png", 1170,279,1,1);
        switches[1] = new Switch("../Stage_Images/Stage7/quad4Switch1.png", 1175,559,0,5);
        
        platforms[0] = new Platform ("../Stage_Images/Stage7/quad2VerPlatform1.png", 731, 308, 350, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage7/quad3VerPlatform1.png", 415, 1370, 560, 0);
        
        portals[0] = new Portal(730,730,1);
        
        oven = new Oven(50,216);
    }
    
    ~Stage7()
    {
        std::cout << "destructing stg 7" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
        for (int x=0; x<portalCount; x++) delete portals[x];
        if (portalCount>0) delete[] portals;
        delete oven;
    }
    
    
};

struct Stage8 : public Stage
{
    
    Stage8(const char* bkg_filename)
    {
        //Dedie: Done.
        
        bakerStartPos.x = 460;
        bakerStartPos.y = 630;
        
        lineCount = 7;
        lines = new Entity* [lineCount];
        
        platformCount = 3;
        platforms = new Entity* [platformCount];
        
        switchCount = 3;
        switches = new Entity* [switchCount];
        
        portalCount = 1;
        portals = new Entity* [portalCount];
        
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage8/StageEight_Boule.png");
        background.setTexture(backgroundTexture);
        
        
        lines[0] = new Line ("../Stage_Images/Stage8/quad1Hor1.png", 156, 398);
        lines[1] = new Line ("../Stage_Images/Stage8/quad2Hor1.png", 889, 198);
        lines[2] = new Line ("../Stage_Images/Stage8/quad3Hor1.png", 190, 578);
        lines[3] = new Line ("../Stage_Images/Stage8/quad3Hor2.png", 260, 780);
        lines[4] = new Line ("../Stage_Images/Stage8/quad4Hor1.png", 850, 780);
        lines[5] = new Line ("../Stage_Images/Stage8/quad4Hor2.png", 900, 532);
        lines[6] = new Line ("../Stage_Images/Stage8/quad4Ver1.png", 1066, 780);
        
        
        switches[0] = new Switch("../Stage_Images/Stage8/quad1Switch1.png", 280,357,2,1);
        switches[1] = new Switch("../Stage_Images/Stage8/quad4Switch1.png", 980,497,0,4);
        switches[2] = new Switch("../Stage_Images/Stage8/quad4Switch2.png", 1140,780,1,4);
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage8/quad2HorPlatform1.png", 1150, 190, 0, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage8/quad3VerPlatform1.png", 250, 530, 0, 0);
        platforms[2] = new Platform ("../Stage_Images/Stage8/quad4VerPlatform1.png", 590, 1325, 455, 0);
        
        portals[0] = new Portal(60,350,1);
        
        oven = new Oven(40,540);
    }
    
    ~Stage8()
    {
        std::cout << "destructing stg 8" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
        for (int x=0; x<portalCount; x++) delete portals[x];
        if (portalCount>0) delete[] portals;
        delete oven;
    }
    
    
};

struct Stage9 : public Stage
{
    
    Stage9(const char* bkg_filename)
    {
        //Dedie: Done.
        
        bakerStartPos.x = 240;
        bakerStartPos.y = 210;
        
        lineCount = 9;
        lines = new Entity* [lineCount];
        
        platformCount = 2;
        platforms = new Entity* [platformCount];
        
        switchCount = 3;
        switches = new Entity* [switchCount];
        
        portalCount = 1;
        portals = new Entity* [portalCount];
        
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage9/StageNine_Boule.png");
        background.setTexture(backgroundTexture);
        
        lines[0] = new Line ("../Stage_Images/Stage9/quad1Hor1.png", 280, 410);
        lines[1] = new Line ("../Stage_Images/Stage9/quad1Hor2.png", 490, 290);
        lines[2] = new Line ("../Stage_Images/Stage9/quad1Ver1.png", 386, 410);
        lines[3] = new Line ("../Stage_Images/Stage9/quad2Hor1.png", 928, 358);
        lines[4] = new Line ("../Stage_Images/Stage9/quad2Ver1.png", 590, 290);
        lines[5] = new Line ("../Stage_Images/Stage9/quad3Hor1.png", 413, 610);
        lines[6] = new Line ("../Stage_Images/Stage9/quad3Ver1.png", 295, 610);
        lines[7] = new Line ("../Stage_Images/Stage9/quad4Hor1.png", 910, 564);
        lines[8] = new Line ("../Stage_Images/Stage9/quad4Ver1.png", 1046, 780);
        
        switches[0] = new Switch("../Stage_Images/Stage9/quad1Switch1.png", 530,250,1,4);
        switches[1] = new Switch("../Stage_Images/Stage9/quad2Switch1.png", 1000,320,0,4);
        switches[2] = new Switch("../Stage_Images/Stage9/quad4Switch1.png", 1160,783,2,480, 450);
        
        platforms[0] = new Platform ("../Stage_Images/Stage9/quad4VerPlatform1.png", 830, 500, 0, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage9/quad4HorPlatform1.png", 1140, 560, 0, 0);
        
        portals[0] = new Portal(110,780,1);
        
        oven = new Oven(990,530);
    }
    
    ~Stage9()
    {
        std::cout << "destructing stg 9" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
        for (int x=0; x<portalCount; x++) delete portals[x];
        if (portalCount>0) delete[] portals;
        delete oven;
    }
    
    
};

struct Stage10 : public Stage
{
    
    Stage10(const char* bkg_filename)
    {
        //Dedie: Done.
        
        bakerStartPos.x = 240;
        bakerStartPos.y = 190;
        
        lineCount = 7;
        lines = new Entity* [lineCount];
        
        platformCount = 4;
        platforms = new Entity* [platformCount];
        
        switchCount = 4;
        switches = new Entity* [switchCount];
        
        portalCount = 3;
        portals = new Entity* [portalCount];
        
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage10/StageTen_Boule.png");
        background.setTexture(backgroundTexture);
        
        lines[0] = new Line ("../Stage_Images/Stage10/quad1Hor1.png", 234, 300);
        lines[1] = new Line ("../Stage_Images/Stage10/quad2Hor1.png", 1040, 230);
        lines[2] = new Line ("../Stage_Images/Stage10/quad3Hor1.png", 94, 560);
        lines[3] = new Line ("../Stage_Images/Stage10/quad3Ver1.png", 450, 780);
        lines[4] = new Line ("../Stage_Images/Stage10/quad4Hor1.png", 830, 560);
        lines[5] = new Line ("../Stage_Images/Stage10/quad4Hor2.png", 830, 780);
        lines[6] = new Line ("../Stage_Images/Stage10/quad4Ver1.png", 1008, 780);
        
        switches[0] = new Switch("../Stage_Images/Stage10/quad1Switch1.png", 60,261,3,4);
        switches[1] = new Switch("../Stage_Images/Stage10/quad2Switch1.png", 1120,192,2,4);
        switches[2] = new Switch("../Stage_Images/Stage10/quad3Switch1.png", 110,780,1,1);
        switches[3] = new Switch("../Stage_Images/Stage10/quad4Switch1.png", 1120,780,0,5);
        
        platforms[0] = new Platform ("../Stage_Images/Stage10/quad3HorPlatform1.png", 310, 550, 800, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage10/quad3HorPlatform2.png", 570, 550, 280, 0);
        platforms[2] = new Platform ("../Stage_Images/Stage10/quad4HorPlatform1.png", 1120, 560, 0, 0);
        platforms[3] = new Platform ("../Stage_Images/Stage10/quad4VerPlatform1.png", 770, 730, 0, 0);
        
        
        portals[0] = new Portal(390,260,0);
        portals[1] = new Portal(80,510,1);
        portals[2] = new Portal(910,510,2);
        
        oven = new Oven(950,740);
    }
    
    ~Stage10()
    {
        std::cout << "destructing stg 10" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
        for (int x=0; x<portalCount; x++) delete portals[x];
        if (portalCount>0) delete[] portals;
        delete oven;
    }
    
    
};

struct Stage11 : public Stage
{
    
    Stage11(const char* bkg_filename)
    {
        //Dedie: Done.
        
        bakerStartPos.x = 585;
        bakerStartPos.y = 130;
        
        lineCount = 8;
        lines = new Entity* [lineCount];
        
        platformCount = 4;
        platforms = new Entity* [platformCount];
        
        switchCount = 4;
        switches = new Entity* [switchCount];
        
        portalCount = 2;
        portals = new Entity* [portalCount];
        
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage11/StageEleven_Boule.png");
        background.setTexture(backgroundTexture);
        
        lines[0] = new Line ("../Stage_Images/Stage11/quad1Ver1.png", 440, 364);
        lines[1] = new Line ("../Stage_Images/Stage11/quad2Hor1.png", 718, 278);
        lines[2] = new Line ("../Stage_Images/Stage11/quad3Hor1.png", 186, 780);
        lines[3] = new Line ("../Stage_Images/Stage11/quad3Hor2.png", 382, 582);
        lines[4] = new Line ("../Stage_Images/Stage11/quad3Ver1.png", 222, 583);
        lines[5] = new Line ("../Stage_Images/Stage11/quad4Hor1.png", 882, 480);
        lines[6] = new Line ("../Stage_Images/Stage11/quad4Hor2.png", 882, 582);
        lines[7] = new Line ("../Stage_Images/Stage11/quad4Ver1.png", 994, 583);
        
        
        switches[0] = new Switch("../Stage_Images/Stage11/quad1Switch1.png", 520,238,2,4);
        switches[1] = new Switch("../Stage_Images/Stage11/quad3Switch1.png", 80,752,0,4);
        switches[2] = new Switch("../Stage_Images/Stage11/quad3Switch2.png", 280,544,3,1);
        switches[3] = new Switch("../Stage_Images/Stage11/quad4Switch1.png", 1130,780,1,4);
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage11/quad1HorPlatform1.png", 336, 366, 0, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage11/quad3VerPlatform1.png", 220, 730, 0, 0);
        platforms[2] = new Platform ("../Stage_Images/Stage11/quad3VerPlatform2.png", 530, 780, 0, 0);
        platforms[3] = new Platform ("../Stage_Images/Stage11/quad4HorPlatform1.png", 660, 580, 455, 0);
        
        
        portals[0] = new Portal(730,220,1);
        portals[1] = new Portal(850,770,2);
        
        oven = new Oven(940,440);
    }
    
    ~Stage11()
    {
        std::cout << "destructing stg 11" << std::endl;
        for (int x=0; x<lineCount; x++) delete lines[x];
        if (lineCount>0) delete[] lines;
        for (int x=0; x<platformCount; x++) delete platforms[x];
        if (platformCount > 0) delete[] platforms;
        for (int x=0; x<switchCount; x++) delete switches[x];
        if (switchCount>0) delete[] switches;
        for (int x=0; x<portalCount; x++) delete portals[x];
        if (portalCount>0) delete[] portals;
        delete oven;
    }
    
    
};

#endif
