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


		switches[0] = new Switch(1000,780,0,0,"../Stage_Images/Stage1/quad4Switch1.png");
//For platforms,

		platforms[0] = new Platform ("../Stage_Images/Stage1/quad3VerPlatform1.png", 490, 783, 500, 1);

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
        
        switches[0] = new Switch(1143,780,0,1, "../Stage_Images/Stage2/quad4Switch1.png");
        switches[1] = new Switch(100,780,1,1, "../Stage_Images/Stage2/quad3Switch1.png");

        platforms[0] = new Platform ("../Stage_Images/Stage2/quad1VerPlatform1.png", 530, 360, -30, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage2/quad2VerPlatform1.png", 710, 160, -50, 0);
        
        portals[0] = new Portal (995,740,0);

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
        lines[6] = new Line ("../Stage_Images/Stage3/quad4Hor1.png", 1149, 780);
      
        
        switches[0] = new Switch(263,160,1,4, "../Stage_Images/Stage3/quad1Switch1.png");
        switches[1] = new Switch(1156,201,0,4, "../Stage_Images/Stage3/quad2Switch1.png");
        switches[2] = new Switch(104, 780, 2, 67, 521, "../Stage_Images/Stage3/quad3Switch1.png");
        switches[3] = new Switch(1159, 697, 2, 1, "../Stage_Images/Stage3/quad4Switch1.png");
       
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage3/quad1VerPlatform1.png", 384, 137, 550, 0); //Should move down
        platforms[1] = new Platform ("../Stage_Images/Stage3/quad2HorPlatform1.png", 953, 379, 100, 0); //Should disappear
        platforms[2] = new Platform ("../Stage_Images/Stage3/quad3VerPlatform1.png", 353, 771, 500, 0);
        
        portals[0] = new Portal (472,152,0);
        //portals[1] = new Portal(1017,250,1);
        portals[1] = new Portal(95,152,2);
        
        oven = new Oven(470,351);
        
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
        //Dedie: Nearly done. Switch functionality has not been added, because this stage relies heavily on one of the last types of switches to be made. Otherwise complete.
        
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

        
        switches[0] = new Switch(632,186,3,474,166, "../Stage_Images/Stage4/quad2Switch1.png");
        switches[1] = new Switch(916,398,1,4, "../Stage_Images/Stage4/quad2Switch2.png");
        switches[2] = new Switch(23,780,3,4, "../Stage_Images/Stage4/quad3Switch1.png");
        switches[3] = new Switch(265,780,4,4, "../Stage_Images/Stage4/quad3Switch2.png");
        switches[4] = new Switch(467,780,0,4, "../Stage_Images/Stage4/quad3Switch3.png");
        switches[5] = new Switch(1156,599,3,382,535, "../Stage_Images/Stage4/quad4Switch1.png");
        switches[6] = new Switch(1170,780,2,4, "../Stage_Images/Stage4/quad4Switch2.png");
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage4/quad2HorPlatform1.png", 1120, 170, 0, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage4/quad3HorPlatform1.png", 57, 622, 0, 0);
        platforms[2] = new Platform ("../Stage_Images/Stage4/quad3VerPlatform1.png", 217, 750, 0, 0);
        platforms[3] = new Platform ("../Stage_Images/Stage4/quad4HorPlatform1.png", 1003, 615, 0, 0);
        platforms[4] = new Platform ("../Stage_Images/Stage4/quad4VerPlatform1.png", 787, 768, 0, 0);
        
        portals[0] = new Portal(550,170,0);
        portals[1] = new Portal(730,765,1);
        portals[2] = new Portal(373,766,2);
        
        oven = new Oven(490, 800);
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
        //Dedie: All placeholders have been implemented. Just need to quality check. And again, Baker needs to spawn at the specified location for this stage. Getting some issues with having just a sole Anpan portal. Will look into that.
        
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
        

        lines[0] = new Line ("../Stage_Images/Stage5/quad1Hor1.png", 435, 159);
        lines[1] = new Line ("../Stage_Images/Stage5/quad1Hor2.png", 404, 278);
        lines[2] = new Line ("../Stage_Images/Stage5/quad1Hor3.png", 528, 403);
        lines[3] = new Line ("../Stage_Images/Stage5/quad1Ver1.png", 112, 620);
        lines[4] = new Line ("../Stage_Images/Stage5/quad1Ver2.png", 221, 528);
        lines[5] = new Line ("../Stage_Images/Stage5/quad1Ver3.png", 587, 402);
        lines[6] = new Line ("../Stage_Images/Stage5/quad2Hor1.png", 864, 285);
        lines[7] = new Line ("../Stage_Images/Stage5/quad2Hor2.png", 1070, 159);
        lines[8] = new Line ("../Stage_Images/Stage5/quad2Ver1.png", 762, 145);
        lines[9] = new Line ("../Stage_Images/Stage5/quad2Ver2.png", 949, 273);
        lines[10] = new Line ("../Stage_Images/Stage5/quad3Hor1.png", 435, 630);
        lines[11] = new Line ("../Stage_Images/Stage5/quad3Hor2.png", 280, 529);
        lines[12] = new Line ("../Stage_Images/Stage5/quad3Ver1.png", 306, 785);
        lines[13] = new Line ("../Stage_Images/Stage5/quad3Ver2.png", 485, 617);
        lines[14] = new Line ("../Stage_Images/Stage5/quad4Hor1.png", 838, 696);
        lines[15] = new Line ("../Stage_Images/Stage5/quad4Hor2.png", 1027, 467);
        lines[16] = new Line ("../Stage_Images/Stage5/quad4Hor3.png", 1155, 580);
        lines[17] = new Line ("../Stage_Images/Stage5/quad4Ver1.png", 777, 688);
        lines[18] = new Line ("../Stage_Images/Stage5/quad4Ver2.png", 986, 545);
        
     
        
        
        switches[0] = new Switch(530,390,2,1048,296, "../Stage_Images/Stage5/quad1Switch1.png");
        switches[1] = new Switch(373,780,2,628,100, "../Stage_Images/Stage5/quad3Switch1.png");
        switches[2] = new Switch(697,780,1,1, "../Stage_Images/Stage5/quad4Switch1.png");
        switches[3] = new Switch(1164,567,0,1, "../Stage_Images/Stage5/quad4Switch2.png");
        
        
        platforms[0] = new Platform ("../Stage_Images/Stage5/quad3VerPlatform1.png", 571, 764, 630, 0);
        platforms[1] = new Platform ("../Stage_Images/Stage5/quad4VerPlatform1.png", 828, 723, 680, 0);
        
        portals[0] = new Portal (1129,761,0);
        portals[1] = new Portal (1024,413,2);
        
        
        oven = new Oven(205, 780);
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

/*
struct Stage6 : public Stage
{
    
    Stage6(const char* bkg_filename)
    {
        
        lineCount = 22;
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
        
  
        lines[0] = new Line ("../Stage_Images/Stage6/quad1Hor1.png", 33, 300);
        lines[1] = new Line ("../Stage_Images/Stage6/quad1Hor2.png", 89, 274);
        lines[2] = new Line ("../Stage_Images/Stage6/quad1Hor3.png", 236l, 130);
        lines[3] = new Line ("../Stage_Images/Stage6/quad1Hor4.png", 240, 382);
        lines[4] = new Line ("../Stage_Images/Stage6/quad1Hor5.png", 318, 233);
        lines[5] = new Line ("../Stage_Images/Stage6/quad1Hor6.png", 561, 395);
        lines[6] = new Line ("../Stage_Images/Stage6/quad1Ver1.png", 73, 300);
        lines[7] = new Line ("../Stage_Images/Stage6/quad1Ver2.png", 367, 649);
        lines[8] = new Line ("../Stage_Images/Stage6/quad2Hor1.png", 635, 255);
        lines[9] = new Line ("../Stage_Images/Stage6/quad2Hor2.png", 673, 393);
        lines[10] = new Line ("../Stage_Images/Stage6/quad2Hor3.png", 1124, 102);
        lines[11] = new Line ("../Stage_Images/Stage6/quad2Ver1.png", 610, 394);
        lines[12] = new Line ("../Stage_Images/Stage6/quad2Ver2.png", 875, 416);
        lines[13] = new Line ("../Stage_Images/Stage6/quad2Ver3.png", 1061, 680);
        lines[14] = new Line ("../Stage_Images/Stage6/quad3Hor1.png", 29, 546);
        lines[15] = new Line ("../Stage_Images/Stage6/quad3Hor2.png", 68, 729);
        lines[16] = new Line ("../Stage_Images/Stage6/quad3Hor3.png", 113, 622);
        lines[17] = new Line ("../Stage_Images/Stage6/quad3Hor4.png", 193, 548);
        lines[18] = new Line ("../Stage_Images/Stage6/quad3Hor5.png", 303, 650);
        lines[19] = new Line ("../Stage_Images/Stage6/quad3Hor6.png", 477, 553);
        lines[20] = new Line ("../Stage_Images/Stage6/quad3Ver1.png", 150, 729);
        lines[21] = new Line ("../Stage_Images/Stage6/quad3Ver2.png", 492, 708);
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
*/

#endif
