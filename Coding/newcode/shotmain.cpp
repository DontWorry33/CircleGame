#include <iostream>
#include "TrajectCircle.cpp"
#include "Entity.cpp"

using namespace std;

int main()

{
	Game game;
	Baker baker;
	Entity roti;
	Entity anpan;
	Entity boule;

	Entity* entities[4];
	entities[0] = &baker;
	entities[1] = &roti;
	entities[2] = &anpan;
	entities[3] = &boule;

	game.run(entities);
	
	return 0;
	
}

