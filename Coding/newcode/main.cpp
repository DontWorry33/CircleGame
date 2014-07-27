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
		Line line;

		Entity* entities[6];
		entities[0] = &baker;
		entities[1] = &roti;
		entities[2] = &anpan;
		entities[3] = &boule;
		entities[4] = &box;
		entities[5] = &line;
		Game game;
		int reset = game.run(entities);
		if (reset!=0) {
			continue;
		}
		else break;
	}
	return 0;
	
}

