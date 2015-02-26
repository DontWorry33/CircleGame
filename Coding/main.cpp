#include <iostream>
#include <cmath>
#include "Entity.cpp"
#include "Bound.cpp"
#include "Stage.cpp"
#include "UI.cpp"
#include "Option.cpp"

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
    
    Stage6* stage6 = new Stage6(
                                "../Stage_Images/Stage6/StageSix.png");
    
    
	Stage* stages[6];
	stages[0] = stage1;
	stages[1] = stage2;
    stages[2] = stage3;
    stages[3] = stage4;
    stages[4] = stage5;
    stages[5] = stage6;

	
	//MAIN MENU WINDOW/LOOP
    Main_Menu menu(1200,800);
    Game* game = new Game(menu.win);
    while (menu.win->isOpen())
    {
	    menu.render();

	    sf::Event event;
	    while (menu.win->pollEvent(event))
	    {
	    	switch (event.type)
	    	{
	    		case sf::Event::KeyPressed:
	    			if (event.key.code == sf::Keyboard::Escape)
	    			{
	    				menu.win->close();
	    			}
	    			if (event.key.code == sf::Keyboard::Return)
	    			{
	    				game->run(entities,stages);
	    				delete game;
	    			}
	    			break;

				case sf::Event::Closed:
					menu.win->close();
					break;

	    		case sf::Event::MouseButtonPressed:
	    			if (menu.isTouchingOption() == 0)
	    			{
	    				//menu.fade(menu.UI_options[0]->option, stages[0]->background);
	    				//std::cout << "fade finished" << std::endl;
						game->run(entities,stages);
						delete game;
	    			}
	    			else if (menu.isTouchingOption() == 3)
	    			{
	    				menu.win->close();
	    			}
	    			break;
	    	}
	    }


    }
    





	delete baker;
	delete roti;
	delete anpan;
	delete boule;
	delete stage1;
	delete stage2;
    delete stage3;
    delete stage4;
    delete stage5;
    delete stage6;
	
	
	return 0;
	
}

