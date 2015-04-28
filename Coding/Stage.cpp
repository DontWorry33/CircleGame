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

		switches[0] = new Switch("../Stage_Images/Stage1/quad4Switch1.png", true, 1000, 784, 0, 0);

		platforms[0] = new Platform ("../Stage_Images/Stage1/quad3VerPlatform1.png", 490, 783, 500, 1);

		portals[0] = new Portal (900,600,0);
		portals[1] = new Portal(100,600,1);
		portals[2] = new Portal(1110,600,2);

		oven = new Oven(200,780, true);
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
        
        //Dedie: Done.
        
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
        lines[2] = new Line("../Stage_Images/Stage2/quad2Hor2.png", 784, 179);
        lines[3] = new Line("../Stage_Images/Stage2/quad3Hor1.png", 78, 682);
        lines[4] = new Line("../Stage_Images/Stage2/quad3Ver1.png", 178, 700);
        lines[5] = new Line("../Stage_Images/Stage2/quad4Hor1.png", 776, 790);
        
        switches[0] = new Switch("../Stage_Images/Stage2/quad4Switch1.png", true, 1143, 784, 0, 1);
        switches[1] = new Switch("../Stage_Images/Stage2/quad3Switch1.png", true, 100, 784, 1, 1);

        platforms[0] = new Platform ("../Stage_Images/Stage2/quad1VerPlatform1.png", 530, 360, -30, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage2/quad2VerPlatform1.png", 710, 160, -50, 0);
        
        portals[0] = new Portal (995,740,0);

		oven = new Oven(870, 165, true);
        


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

        //Dedie: Done.
        
 
        bakerStartPos.x = 900;
        bakerStartPos.y = 100;
 
        lineCount = 7;
        lines = new Entity* [lineCount];
        
        platformCount = 3;
        platforms = new Entity* [platformCount];
        
        switchCount = 4;
        switches = new Entity* [switchCount];
        
        portalCount = 2;
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
        lines[6] = new Line ("../Stage_Images/Stage3/quad4Hor1.png", 1149, 781);
      
        
        switches[0] = new Switch("../Stage_Images/Stage3/quad1Switch1.png", true, 263, 160, 1, 4);
        switches[1] = new Switch("../Stage_Images/Stage3/quad2Switch1.png", true, 1156, 201, 0, 4);
        switches[2] = new Switch("../Stage_Images/Stage3/quad3Switch1.png", true, 104, 784, 2, 67, 521);
        switches[3] = new Switch("../Stage_Images/Stage3/quad4Switch1.png", false, 1159, 698, 2, 1);
       
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage3/quad1VerPlatform1.png", 384, 137, 550, 0); //Should move down
        platforms[1] = new Platform ("../Stage_Images/Stage3/quad2HorPlatform1.png", 953, 379, 100, 0); //Should disappear
        platforms[2] = new Platform ("../Stage_Images/Stage3/quad3VerPlatform1.png", 353, 771, 500, 0);
        
        portals[0] = new Portal (470,150,0);
        portals[1] = new Portal(90,150,2);
        
        oven = new Oven(470,351, true);
        
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
        
        bakerStartPos.x = 1000;
        bakerStartPos.y = 0;
        
        lineCount = 24;
        lines = new Entity* [lineCount];
        
        platformCount = 5;
        platforms = new Entity* [platformCount];
        
        switchCount = 7;
        switches = new Entity* [switchCount];
        
        portalCount = 3;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage4/StageFour_Boule.png");
        background.setTexture(backgroundTexture);
        
        
        lines[0] = new Line ("../Stage_Images/Stage4/quad1Hor1.png", 65, 365);
        lines[1] = new Line ("../Stage_Images/Stage4/quad1Hor2.png", 212, 164);
        lines[2] = new Line ("../Stage_Images/Stage4/quad1Hor3.png", 212, 265);
        lines[3] = new Line ("../Stage_Images/Stage4/quad1Hor4.png", 394, 395);
        lines[4] = new Line ("../Stage_Images/Stage4/quad1Hor5.png", 549, 212);
        lines[5] = new Line ("../Stage_Images/Stage4/quad2Hor1.png", 703, 395);
        lines[6] = new Line ("../Stage_Images/Stage4/quad2Hor2.png", 913, 170);
        lines[7] = new Line ("../Stage_Images/Stage4/quad2Hor3.png", 955, 348);
        lines[8] = new Line ("../Stage_Images/Stage4/quad2Hor4.png", 1116, 260);
        lines[9] = new Line ("../Stage_Images/Stage4/quad2Ver1.png", 784, 644);
        lines[10] = new Line ("../Stage_Images/Stage4/quad2Ver2.png", 952, 399);
        lines[11] = new Line ("../Stage_Images/Stage4/quad3Hor1.png", 224, 622);
        lines[12] = new Line ("../Stage_Images/Stage4/quad3Hor2.png", 426, 622);
        lines[13] = new Line ("../Stage_Images/Stage4/quad3Ver1.png", 136, 623);
        lines[14] = new Line ("../Stage_Images/Stage4/quad3Ver2.png", 312, 782);
        lines[15] = new Line ("../Stage_Images/Stage4/quad3Ver3.png", 549, 622);
        lines[16] = new Line ("../Stage_Images/Stage4/quad4Hor1.png", 671, 622);
        lines[17] = new Line ("../Stage_Images/Stage4/quad4Hor2.png", 845, 641);
        lines[18] = new Line ("../Stage_Images/Stage4/quad4Hor3.png", 936, 419);
        lines[19] = new Line ("../Stage_Images/Stage4/quad4Hor4.png", 935, 477);
        lines[20] = new Line ("../Stage_Images/Stage4/quad4Hor5.png", 1070, 477);
        lines[21] = new Line ("../Stage_Images/Stage4/quad4Hor6.png", 1150, 626);
        lines[22] = new Line ("../Stage_Images/Stage4/quad4Ver2.png", 892, 477);
        lines[23] = new Line ("../Stage_Images/Stage4/quad4Ver3.png", 899, 640);

        
        switches[0] = new Switch("../Stage_Images/Stage4/quad2Switch1.png", false, 632, 186, 3, 474, 166);
        switches[1] = new Switch("../Stage_Images/Stage4/quad2Switch2.png", false, 916, 398, 1, 4);
        switches[2] = new Switch("../Stage_Images/Stage4/quad3Switch1.png", false, 23, 784, 3, 4);
        switches[3] = new Switch("../Stage_Images/Stage4/quad3Switch2.png", false, 265, 784, 4, 4);
        switches[4] = new Switch("../Stage_Images/Stage4/quad3Switch3.png", false, 467, 784, 0, 4);
        switches[5] = new Switch("../Stage_Images/Stage4/quad4Switch1.png", false, 1156, 599, 3, 382, 535);
        switches[6] = new Switch("../Stage_Images/Stage4/quad4Switch2.png", false, 1170, 784, 2, 4);
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage4/quad2HorPlatform1.png", 1120, 170, 0, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage4/quad3HorPlatform1.png", 57, 622, 0, 0);
        platforms[2] = new Platform ("../Stage_Images/Stage4/quad3VerPlatform1.png", 217, 750, 0, 0);
        platforms[3] = new Platform ("../Stage_Images/Stage4/quad4HorPlatform1.png", 1003, 615, 0, 0);
        platforms[4] = new Platform ("../Stage_Images/Stage4/quad4VerPlatform1.png", 787, 768, 0, 0);
        
        portals[0] = new Portal(470,180,0);
        portals[1] = new Portal(720,770,1);
        portals[2] = new Portal(370,770,2);
        
        oven = new Oven(530, 782, true);
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
        
        bakerStartPos.x = 1066;
        bakerStartPos.y = 80;
        
        lineCount = 19;
        lines = new Entity* [lineCount];
        
        platformCount = 2;
        platforms = new Entity* [platformCount];
        
        switchCount = 4;
        switches = new Entity* [switchCount];
        
        portalCount = 2;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage5/StageFive_Boule.png");
        background.setTexture(backgroundTexture);
        

        lines[0] = new Line ("../Stage_Images/Stage5/quad1Hor1.png", 425, 162);
        lines[1] = new Line ("../Stage_Images/Stage5/quad1Hor2.png", 428, 279);
        lines[2] = new Line ("../Stage_Images/Stage5/quad1Hor3.png", 548, 399);
        lines[3] = new Line ("../Stage_Images/Stage5/quad1Ver1.png", 100, 622);
        lines[4] = new Line ("../Stage_Images/Stage5/quad1Ver2.png", 211, 521);
        lines[5] = new Line ("../Stage_Images/Stage5/quad2Hor1.png", 855, 309);
        lines[6] = new Line ("../Stage_Images/Stage5/quad2Hor2.png", 1073, 175);
        lines[7] = new Line ("../Stage_Images/Stage5/quad2Ver1.png", 637, 398);
        lines[8] = new Line ("../Stage_Images/Stage5/quad2Ver2.png", 750, 145);
        lines[9] = new Line ("../Stage_Images/Stage5/quad2Ver3.png", 953, 309);
        lines[10] = new Line ("../Stage_Images/Stage5/quad3Hor1.png", 439, 622);
        lines[11] = new Line ("../Stage_Images/Stage5/quad3Hor2.png", 273, 522);
        lines[12] = new Line ("../Stage_Images/Stage5/quad3Ver1.png", 260, 782);
        lines[13] = new Line ("../Stage_Images/Stage5/quad3Ver2.png", 481, 595);
        lines[14] = new Line ("../Stage_Images/Stage5/quad4Hor1.png", 848, 694);
        lines[15] = new Line ("../Stage_Images/Stage5/quad4Hor2.png", 1034, 460);
        lines[16] = new Line ("../Stage_Images/Stage5/quad4Hor3.png", 1160, 581);
        lines[17] = new Line ("../Stage_Images/Stage5/quad4Ver1.png", 779, 694);
        lines[18] = new Line ("../Stage_Images/Stage5/quad4Ver2.png", 992, 530);
        
     
        
        
        switches[0] = new Switch("../Stage_Images/Stage5/quad1Switch1.png", true, 580, 382, 2, 1048, 296);
        switches[1] = new Switch("../Stage_Images/Stage5/quad3Switch1.png", true, 373, 784, 2, 628, 100);
        switches[2] = new Switch("../Stage_Images/Stage5/quad4Switch1.png", false, 695, 784, 1, 1);
        switches[3] = new Switch("../Stage_Images/Stage5/quad4Switch2.png", false, 1164, 562, 0, 1);
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage5/quad3VerPlatform1.png", 572, 765, 630, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage5/quad4VerPlatform1.png", 838, 719, 680, 0);
        
        portals[0] = new Portal (1130,760,0);
        portals[1] = new Portal (1030,420,2);
        
        
        oven = new Oven(205, 780, true);
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
        
        bakerStartPos.x = 730;
        bakerStartPos.y = 299;
        
        //bakerStartPos.x = 730;
        //bakerStartPos.y = 523;

        lineCount = 16;
        lines = new Entity* [lineCount];
        
        platformCount = 3;
        platforms = new Entity* [platformCount];
        
        switchCount = 5;
        switches = new Entity* [switchCount];
        
        portalCount = 2;
        portals = new Entity* [portalCount];
        backgroundTexture.loadFromFile(bkg_filename);
        
        bouleTexture.loadFromFile("../Stage_Images/Stage6/StageSix_Boule.png");
        background.setTexture(backgroundTexture);
        
  
        lines[0] = new Line ("../Stage_Images/Stage6/quad1Hor1.png", 33, 290);
        lines[1] = new Line ("../Stage_Images/Stage6/quad1Hor2.png", 236, 138);
        lines[2] = new Line ("../Stage_Images/Stage6/quad1Hor3.png", 240, 382);
        lines[3] = new Line ("../Stage_Images/Stage6/quad1Hor4.png", 288, 273);
        lines[4] = new Line ("../Stage_Images/Stage6/quad1Ver1.png", 367, 565);
        lines[5] = new Line ("../Stage_Images/Stage6/quad2Hor1.png", 664, 250);
        lines[6] = new Line ("../Stage_Images/Stage6/quad2Ver1.png", 660, 413);
        lines[7] = new Line ("../Stage_Images/Stage6/quad2Ver2.png", 933, 359);
        lines[8] = new Line ("../Stage_Images/Stage6/quad3Hor1.png", 127, 475);
        lines[9] = new Line ("../Stage_Images/Stage6/quad3Hor2.png", 227, 565);
        lines[10] = new Line ("../Stage_Images/Stage6/quad3Hor3.png", 484, 564);
        lines[11] = new Line ("../Stage_Images/Stage6/quad3Hor4.png", 588, 413);
        lines[12] = new Line ("../Stage_Images/Stage6/quad4Hor1.png", 735, 413);
        lines[13] = new Line ("../Stage_Images/Stage6/quad4Hor2.png", 733, 697);
        lines[14] = new Line ("../Stage_Images/Stage6/quad4Hor3.png", 856, 697);
        lines[15] = new Line ("../Stage_Images/Stage6/quad4Hor4.png", 1095, 545);
        
        switches[0] = new Switch("../Stage_Images/Stage6/quad1Switch1.png", false, 319,255,0,4);
        switches[1] = new Switch("../Stage_Images/Stage6/quad2Switch1.png", true, 607,232,2,772,177);
        switches[2] = new Switch("../Stage_Images/Stage6/quad3Switch1.png", false, 416,536,2,5);
        switches[3] = new Switch("../Stage_Images/Stage6/quad4Switch1.png", true, 750,673,2,730,523);
        switches[4] = new Switch("../Stage_Images/Stage6/quad4Switch2.png", true, 1152,784,1,1);
        
        platforms[0] = new Platform ("../Stage_Images/Stage6/quad1HorPlatform1.png", 58, 383, 0, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage6/quad3VerPlatform1.png", 494, 752, 560, 0);
        platforms[2] = new Platform ("../Stage_Images/Stage6/quad4VerPlatform1.png", 793, 780, 855, 0);
        
        portals[0] = new Portal(870,780,0);
        portals[1] = new Portal(300,360,2);
        
        oven = new Oven(619,399, false);
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


#endif
