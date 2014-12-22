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
    
	Stage* stages[3];
	stages[0] = stage1;
	stages[1] = stage2;
    stages[2] = stage3;

	
	Game* game = new Game;
	game->run(entities,stages);


	delete baker;
	delete roti;
	delete anpan;
	delete boule;
	delete stage1;
	delete stage2;
	delete game;
	
	
	return 0;
	
}

