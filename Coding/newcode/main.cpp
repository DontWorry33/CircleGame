#include <iostream>
#include "Circle.cpp"
#include "Entity.cpp"

using namespace std;

int main()

{


	while (true)
	{
		Baker baker;
		Roti roti;
		Anpan anpan;
		Boule boule;

		PortalBox box;
		Line line("../../Stage_Images/Standing_Border.png");

		Line red("../../Stage_Images/Red_Line_Test.png");
		red.eSprite.setPosition(285,400); 
		red.eBounds.x = red.eSprite.getPosition().x - red.eTextureSize.x/2;
		red.eBounds.y = red.eSprite.getPosition().y - red.eTextureSize.y/2;
		Line blue("../../Stage_Images/Blue_Line_Test.png");
		blue.eSprite.setPosition(375,460);
		blue.eBounds.x = blue.eSprite.getPosition().x - blue.eTextureSize.x/2;
		blue.eBounds.y = blue.eSprite.getPosition().y - blue.eTextureSize.y/2;
		Line green("../../Stage_Images/Green_Line_Test.png");
		green.eSprite.setPosition(450,400);
		green.eBounds.x = green.eSprite.getPosition().x - green.eTextureSize.x/2;
		green.eBounds.y = green.eSprite.getPosition().y - green.eTextureSize.y/2;

		Entity* entities[9];
		entities[0] = &baker;
		entities[1] = &roti;
		entities[2] = &anpan;
		entities[3] = &boule;
		entities[4] = &box;
		entities[5] = &line;
		entities[6] = &red;
		entities[7] = &blue;
		entities[8] = &green;
		Game game;
		int reset = game.run(entities);
		if (reset!=0) {
			continue;
		}
		else break;
	}
	return 0;
	
}

