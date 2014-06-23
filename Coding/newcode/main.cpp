#include <iostream>
#include "Circle.cpp"
#include "Entity.cpp"

using namespace std;

int main()

{
	Game game;
	Baker baker;
	Roti roti;
	Anpan anpan;

	Entity* entities[3];
	entities[0] = &baker;
	entities[1] = &roti;
	entities[2] = &anpan;

	game.run(entities);
	return 0;
	
}

