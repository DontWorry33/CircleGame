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
        for (int x=0; x<portalCount; x++) delete portals[x];
        if (portalCount>0) delete[] portals;
	}


};

struct Stage2 : public Stage
{

	Stage2(const char* bkg_filename)
	{
        
        //Dedie: Switches need to be put in final position.
        
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

		//oven = new Oven(780, 165);
        oven = new Oven(300, 800);


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
    
    Stage3(const char* bkg_filename)
    {

        //Dedie: Nearly done. Pressing L doesn't get me to here, though.
        
        lineCount = 12;
        lines = new Entity* [lineCount];
        
        platformCount = 4;
        platforms = new Entity* [platformCount];
        
        switchCount = 7;
        switches = new Entity* [switchCount];
        
        portalCount = 3;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage3/StageThree_Boule.png");
        background.setTexture(backgroundTexture);
        
        
        lines[0] = new Line ("../Stage_Images/Stage3/quad1Hor1.png", 263, 180);
        lines[1] = new Line ("../Stage_Images/Stage3/quad1Hor2.png", 389, 380);
        lines[2] = new Line ("../Stage_Images/Stage3/quad1Ver1.png", 513, 380);
        lines[3] = new Line ("../Stage_Images/Stage3/quad2Hor1.png", 613, 380);
        lines[4] = new Line ("../Stage_Images/Stage3/quad2Hor2.png", 1138, 220);
        lines[5] = new Line ("../Stage_Images/Stage3/quad3Hor1.png", 78, 628);
        lines[6] = new Line ("../Stage_Images/Stage3/quad4Hor1.png", 773, 582);
        lines[7] = new Line ("../Stage_Images/Stage3/quad4Hor2.png", 951, 496);
        lines[8] = new Line ("../Stage_Images/Stage3/quad4Ver1.png", 704, 553);
        lines[9] = new Line ("../Stage_Images/Stage3/quad4Ver2.png", 704, 679);
        lines[10] = new Line ("../Stage_Images/Stage3/quad4Ver3.png", 868, 582);
        lines[11] = new Line ("../Stage_Images/Stage3/quad4Ver4.png", 1100, 723);
      
        
        switches[0] = new Switch(95, 159,3,515, 705); //quad1Switch1
        switches[1] = new Switch(417,159,2,0); //quad1Switch2
        switches[2] = new Switch(995,363,1,1); //quad2Switch1
        switches[3] = new Switch(1158,201,0,1); //quad2Switch2
        switches[4] = new Switch(104, 778, 2, 67, 521); //quad3Switch1
        switches[5] = new Switch(952, 462, 3, 454, 96); //quad4Switch1
        switches[6] = new Switch(1164,781,3,1); //quad4Switch2
       
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage3/quad2VerPlatform1.png", 691, 347, 100); //Should move down
        platforms[1] = new Platform ("../Stage_Images/Stage3/quad2VerPlatform2.png", 865, 347, 100);
        platforms[2] = new Platform ("../Stage_Images/Stage3/quad2HorPlatform1.png", 953, 379, 100); //Should disappear
        platforms[3] = new Platform ("../Stage_Images/Stage3/quad3VerPlatform1.png", 353, 771, 400);
        
        portals[0] = new Portal (1145,359,0);
        portals[1] = new Portal(1017,250,1);
        portals[2] = new Portal(263,147,2);
        
        //oven = new Oven(470,351); Actual Oven Position. Below is just for testing.
        oven = new Oven(590, 800);
        
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
    }
    
    
};


struct Stage4 : public Stage
{
    
    Stage4(const char* bkg_filename)
    {
        
        lineCount = 1;
        lines = new Entity* [lineCount];
        
        platformCount = 1;
        platforms = new Entity* [platformCount];
        
        switchCount = 1;
        switches = new Entity* [switchCount];
        
        portalCount = 3;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage4/StageFour_Boule.png");
        background.setTexture(backgroundTexture);
        
        
        lines[0] = new Line ("../Stage_Images/Stage4/quad1Hor1.png", 200, 200);
        //lines[1] = new Line ("../Stage_Images/Stage4/quad1Hor2.png");
        //lines[2] = new Line ("../Stage_Images/Stage4/quad1Hor3.png");
        //lines[3] = new Line ("../Stage_Images/Stage4/quad1Hor4.png");
        //lines[4] = new Line ("../Stage_Images/Stage4/quad1Hor5.png");
        //lines[5] = new Line ("../Stage_Images/Stage4/quad2Hor1.png");
        //lines[6] = new Line ("../Stage_Images/Stage4/quad2Hor2.png");
        //lines[7] = new Line ("../Stage_Images/Stage4/quad2Hor3.png");
        //lines[8] = new Line ("../Stage_Images/Stage4/quad2Hor2.png");
        //lines[9] = new Line ("../Stage_Images/Stage4/quad2Ver1.png");
        //lines[10] = new Line ("../Stage_Images/Stage4/quad2Ver2.png");
        //lines[11] = new Line ("../Stage_Images/Stage4/quad3Hor1.png");
        //lines[12] = new Line ("../Stage_Images/Stage4/quad3Hor2.png");
        //lines[13] = new Line ("../Stage_Images/Stage4/quad3Hor3.png");
        //lines[14] = new Line ("../Stage_Images/Stage4/quad3Ver1.png");
        //lines[15] = new Line ("../Stage_Images/Stage4/quad3Ver2.png");
        //lines[16] = new Line ("../Stage_Images/Stage4/quad3Ver3.png");
        //lines[17] = new Line ("../Stage_Images/Stage4/quad4Hor1.png");
        //lines[18] = new Line ("../Stage_Images/Stage4/quad4Hor2.png");
        //lines[19] = new Line ("../Stage_Images/Stage4/quad4Hor3.png");
        //lines[20] = new Line ("../Stage_Images/Stage4/quad4Hor4.png");
        //lines[21] = new Line ("../Stage_Images/Stage4/quad4Hor5.png");
        //lines[22] = new Line ("../Stage_Images/Stage4/quad4Hor6.png");
        //lines[23] = new Line ("../Stage_Images/Stage4/quad4Ver1.png");
        //lines[24] = new Line ("../Stage_Images/Stage4/quad4Ver2.png");
        //lines[25] = new Line ("../Stage_Images/Stage4/quad4Ver3.png");

  
        
        
        switches[0] = new Switch(300,780,3,1000,300); //quad1Switch1
        //switches[1] = new Switch(); //quad1Switch2
        //switches[2] = new Switch(); //quad2Switch1
        //switches[3] = new Switch(); //quad2Switch2
        //switches[4] = new Switch(); //quad2Switch3
        //switches[5] = new Switch(); //quad3Switch1
        //switches[6] = new Switch(); //quad3Switch2
        //switches[7] = new Switch(); //quad4Switch1
        //switches[8] = new Switch(); //quad4Switch2
        //switches[9] = new Switch(); //quad4Switch3
        
        

        
        platforms[0] = new Platform ("../Stage_Images/Stage4/quad1HorPlatform1.png", 400, 400, 300);
        //platforms[1] = new Platform ("../Stage_Images/Stage4/quad1HorPlatform2.png", 0, 0, 0);
        //platforms[2] = new Platform ("../Stage_Images/Stage4/quad2HorPlatform1.png", 0, 0, 0);
        //platforms[3] = new Platform ("../Stage_Images/Stage4/quad3HorPlatform1.png", 0, 0, 0);
        //platforms[4] = new Platform ("../Stage_Images/Stage4/quad3HorPlatform2.png", 0, 0, 0);
        //platforms[5] = new Platform ("../Stage_Images/Stage4/quad3VerPlatform1.png", 0, 0, 0);
        //platforms[6] = new Platform ("../Stage_Images/Stage4/quad4HorPlatform1.png", 0, 0, 0);
        //platforms[7] = new Platform ("../Stage_Images/Stage4/quad4VerPlatform1.png", 0, 0, 0);
        
        portals[0] = new Portal (100,780,0);
        portals[1] = new Portal(900,780,1);
        portals[2] = new Portal(1110,780,2);
        
        oven = new Oven(300, 800);
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
    }
    
    
};


struct Stage5 : public Stage
{
    
    Stage5(const char* bkg_filename)
    {
        
        lineCount = 1;
        lines = new Entity* [lineCount];
        
        platformCount = 1;
        platforms = new Entity* [platformCount];
        
        switchCount = 1;
        switches = new Entity* [switchCount];
        
        portalCount = 3;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage5/StageFive_Boule.png");
        background.setTexture(backgroundTexture);
        
        
        lines[0] = new Line ("../Stage_Images/Stage5/quad1Hor1.png", 200, 200);
        //lines[1] = new Line ("../Stage_Images/Stage5/quad1Hor2.png");
        //lines[2] = new Line ("../Stage_Images/Stage5/quad1Hor3.png");
        //lines[3] = new Line ("../Stage_Images/Stage5/quad1Ver1.png");
        //lines[4] = new Line ("../Stage_Images/Stage5/quad1Ver2.png");
        //lines[5] = new Line ("../Stage_Images/Stage5/quad1Ver3.png");
        //lines[6] = new Line ("../Stage_Images/Stage5/quad1Ver4.png");
        //lines[7] = new Line ("../Stage_Images/Stage5/quad1Ver5.png");
        //lines[8] = new Line ("../Stage_Images/Stage5/quad2Hor1.png");
        //lines[9] = new Line ("../Stage_Images/Stage5/quad2Hor2.png");
        //lines[10] = new Line ("../Stage_Images/Stage5/quad2Hor3.png");
        //lines[11] = new Line ("../Stage_Images/Stage5/quad3Hor1.png");
        //lines[12] = new Line ("../Stage_Images/Stage5/quad3Hor2.png");
        //lines[13] = new Line ("../Stage_Images/Stage5/quad3Hor3.png");
        //lines[14] = new Line ("../Stage_Images/Stage5/quad3Ver1.png");
        //lines[15] = new Line ("../Stage_Images/Stage5/quad3Ver2.png");
        //lines[16] = new Line ("../Stage_Images/Stage5/quad3Ver3.png");
        //lines[17] = new Line ("../Stage_Images/Stage5/quad4Hor1.png");
        //lines[18] = new Line ("../Stage_Images/Stage5/quad4Hor2.png");
        //lines[19] = new Line ("../Stage_Images/Stage5/quad4Hor3.png");
        //lines[20] = new Line ("../Stage_Images/Stage5/quad4Hor4.png");
        //lines[21] = new Line ("../Stage_Images/Stage5/quad4Hor4.png");
        //lines[22] = new Line ("../Stage_Images/Stage5/quad4Ver1.png");
        //lines[23] = new Line ("../Stage_Images/Stage5/quad4Ver2.png");
        
     
        
        
        switches[0] = new Switch(300,780,3,1000,300); //quad2Switch1
        //switches[1] = new Switch(); //quad2Switch2
        //switches[2] = new Switch(); //quad2Switch3
        //switches[3] = new Switch(); //quad3Switch1
        //switches[4] = new Switch(); //quad3Switch2
        //switches[5] = new Switch(); //quad4Switch1
        //switches[6] = new Switch(); //quad4Switch2
        //switches[7] = new Switch(); //quad4Switch3
        
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage1/quad2VerPlatform1.png", 400, 400, 300);
        //platforms[1] = new Platform ("../Stage_Images/Stage1/quad2VerPlatform2.png", 0, 0, 0);
        //platforms[2] = new Platform ("../Stage_Images/Stage1/quad3VerPlatform1.png", 0, 0, 0);
        //platforms[3] = new Platform ("../Stage_Images/Stage1/quad4HorPlatform1.png", 0, 0, 0);
        //platforms[4] = new Platform ("../Stage_Images/Stage1/quad4VerPlatform1.png", 0, 0, 0);
        
        portals[0] = new Portal (100,780,0);
        portals[1] = new Portal(900,780,1);
        portals[2] = new Portal(1110,780,2);
        
        oven = new Oven(300, 800);
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
    }
    
    
};


struct Stage6 : public Stage
{
    
    Stage6(const char* bkg_filename)
    {
        
        lineCount = 1;
        lines = new Entity* [lineCount];
        
        platformCount = 1;
        platforms = new Entity* [platformCount];
        
        switchCount = 1;
        switches = new Entity* [switchCount];
        
        portalCount = 3;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage6/StageSix_Boule.png");
        background.setTexture(backgroundTexture);
        
  
        lines[0] = new Line ("../Stage_Images/Stage6/quad1Hor1.png", 200, 200);
        //lines[1] = new Line ("../Stage_Images/Stage6/quad1Hor2.png");
        //lines[2] = new Line ("../Stage_Images/Stage6/quad1Hor3.png");
        //lines[3] = new Line ("../Stage_Images/Stage6/quad1Hor4.png");
        //lines[4] = new Line ("../Stage_Images/Stage6/quad1Hor5.png");
        //lines[5] = new Line ("../Stage_Images/Stage6/quad1Hor6.png");
        //lines[6] = new Line ("../Stage_Images/Stage6/quad1Ver1.png");
        //lines[7] = new Line ("../Stage_Images/Stage6/quad1Ver2.png");
        //lines[8] = new Line ("../Stage_Images/Stage6/quad2Hor1.png");
        //lines[9] = new Line ("../Stage_Images/Stage6/quad2Hor2.png");
        //lines[10] = new Line ("../Stage_Images/Stage6/quad2Hor3.png");
        //lines[11] = new Line ("../Stage_Images/Stage6/quad2Ver1.png");
        //lines[12] = new Line ("../Stage_Images/Stage6/quad2Ver2.png");
        //lines[13] = new Line ("../Stage_Images/Stage6/quad2Ver3.png");
        //lines[14] = new Line ("../Stage_Images/Stage6/quad3Hor1.png");
        //lines[15] = new Line ("../Stage_Images/Stage6/quad3Hor2.png");
        //lines[16] = new Line ("../Stage_Images/Stage6/quad3Hor3.png");
        //lines[17] = new Line ("../Stage_Images/Stage6/quad3Hor4.png");
        //lines[18] = new Line ("../Stage_Images/Stage6/quad3Hor5.png");
        //lines[19] = new Line ("../Stage_Images/Stage6/quad3Hor6.png");
        //lines[20] = new Line ("../Stage_Images/Stage6/quad3Ver1.png");
        //lines[21] = new Line ("../Stage_Images/Stage6/quad3Ver2.png");
        //lines[22] = new Line ("../Stage_Images/Stage6/quad4Hor1.png");
        //lines[23] = new Line ("../Stage_Images/Stage6/quad4Ver1.png");
        //lines[24] = new Line ("../Stage_Images/Stage6/quad4Ver2.png");

        
        
        switches[0] = new Switch(300,780,3,1000,300); //quad1Switch1
        //switches[1] = new Switch(); //quad2Switch1
        //switches[2] = new Switch(); //quad3Switch1
        //switches[3] = new Switch(); //quad3Switch2
        //switches[4] = new Switch(); //quad3Switch3
        //switches[5] = new Switch(); //quad4Switch1
        
        platforms[0] = new Platform ("../Stage_Images/Stage1/quad1HorPlatform1.png", 700, 780, 300);
        //platforms[1] = new Platform ("../Stage_Images/Stage1/quad3HorPlatform1.png", 0, 0, 0);
        //platforms[2] = new Platform ("../Stage_Images/Stage1/quad3HorPlatform2.png", 0, 0, 0);
        //platforms[3] = new Platform ("../Stage_Images/Stage1/quad3HorPlatform3.png", 0, 0, 0);
        //platforms[4] = new Platform ("../Stage_Images/Stage1/quad4HorPlatform1.png", 0, 0, 0);
        //platforms[5] = new Platform ("../Stage_Images/Stage1/quad4VerPlatform1.png", 0, 0, 0);
        
        portals[0] = new Portal (100,780,0);
        portals[1] = new Portal(900,780,1);
        portals[2] = new Portal(1110,780,2);
        
        oven = new Oven(1000,10);
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
    }
    
    
};


#endif
