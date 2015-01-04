#include <iostream>
#include <cmath>
#include "Entity.cpp"
#include "Bound.cpp"
#include "Stage.cpp"

using namespace std;

int main()

{

	Baker* baker = new Baker;
	Roti* roti = new Roti;
	Anpan* anpan = new Anpan;
	Boule* boule = new Boule;

	Entity* entities[4];
	entities[0] = baker;
	entities[1] = roti;
	entities[2] = anpan;
	entities[3] = boule;
	cout << sizeof(entities) << endl;
	//Baker b2;
	//cout << sizeof(b2) << endl;
	Stage1* stage1 = new Stage1(
					"../Stage_Images/Stage1/IntroStage.png",
			  	 	"../Stage_Images/Stage1/quad4Ver1.png"
				 );
    
	Stage2* stage2 = new Stage2(
				"../Stage_Images/Stage2/StageTwo.png");
    
    Stage3* stage3 = new Stage3(
                                "../Stage_Images/Stage3/StageThree.png");
    
    Stage4* stage4 = new Stage4(
                                "../Stage_Images/Stage4/StageFour.png");
    
    Stage5* stage5 = new Stage5(
                                "../Stage_Images/Stage5/StageFive.png");
    /*
    Stage6* stage6 = new Stage6(
                                "../Stage_Images/Stage6/StageSix.png");
     */
    
	Stage* stages[5];
	stages[0] = stage1;
	stages[1] = stage2;
    stages[2] = stage3;
    stages[3] = stage4;
    stages[4] = stage5;
    //stages[5] = stage6;

	
	Game* game = new Game;
	game->run(entities,stages);


	delete baker;
	delete roti;
	delete anpan;
	delete boule;
	delete stage1;
	delete stage2;
    delete stage3;
    delete stage4;
    delete stage5;
    //delete stage6;
	delete game;
	
	
	return 0;
	
}

