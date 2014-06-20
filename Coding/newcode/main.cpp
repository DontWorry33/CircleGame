#include <iostream>
#include "Circle.cpp"
#include "Entity.cpp"

using namespace std;

int main()

{
	Game game;
	Baker baker;
	Roti roti;

	Entity* entities[2];
	entities[0] = &baker;
	entities[1] = &roti;

	game.run(entities);
	return 0;
	
}

