#include <iostream>
#include "Circle.cpp"
#include "Entity.cpp"
#include "Stage.cpp"

using namespace std;

int main()

{


	while (true)
	{
		Baker baker;
		Roti roti;
		Anpan anpan;
		Boule boule;

		Entity* entities[4];
		entities[0] = &baker;
		entities[1] = &roti;
		entities[2] = &anpan;
		entities[3] = &boule;


		Stage1 stage1(
						"../Stage_Images/Stage1/IntroStage.png",
				  	 	"../Stage_Images/quad4Ver1.png"
					 );
		Stage2 stage2(
					"../Stage_Images/Stage2/StageTwo.png");
		Stage* stages[2];
		stages[0] = &stage1;
		stages[1] = &stage2;

		
		Game game;
		int reset = game.run(entities,stages);
		if (reset!=0) {
			continue;
		}
		else break;
		
	}
	return 0;
	
}

