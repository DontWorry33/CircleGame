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

	//create objects
	Baker* baker = new Baker;
	Roti* roti = new Roti;
	Anpan* anpan = new Anpan;
	Boule* boule = new Boule;
	//entities is an array of pointers of the objects 
	Entity* entities[4];
	entities[0] = baker;
	entities[1] = roti;
	entities[2] = anpan;
	entities[3] = boule;



	//initalize all stages
	Stage1* stage1 = new Stage1("../Stage_Images/Stage1/IntroStage.png");
	Stage2* stage2 = new Stage2("../Stage_Images/Stage2/StageTwo.png");    
    Stage3* stage3 = new Stage3("../Stage_Images/Stage3/StageThree.png");    
    Stage4* stage4 = new Stage4("../Stage_Images/Stage4/StageFour.png");    
    Stage5* stage5 = new Stage5("../Stage_Images/Stage5/StageFive.png");    
    Stage6* stage6 = new Stage6("../Stage_Images/Stage6/StageSix.png");    
    Stage7* stage7 = new Stage7("../Stage_Images/Stage7/StageSeven.png");
    Stage8* stage8 = new Stage8("../Stage_Images/Stage8/StageEight.png");    
    Stage9* stage9 = new Stage9("../Stage_Images/Stage9/StageNine.png");    
    Stage10* stage10 = new Stage10("../Stage_Images/Stage10/StageTen.png");
    Stage11* stage11 = new Stage11("../Stage_Images/Stage11/StageEleven.png");
    Stage12* stage12 = new Stage12("../Stage_Images/Stage12/StageTwelve.png");    
    Stage13* stage13 = new Stage13("../Stage_Images/Stage13/StageThirteen.png");
    Stage14* stage14 = new Stage14("../Stage_Images/Stage14/StageFourteen.png");    
    Stage15* stage15 = new Stage15("../Stage_Images/Stage15/StageFifteen.png");
    //initialize array of pointers to stages
	Stage* stages[15];
	stages[0] = stage1;
	stages[1] = stage2;
    stages[2] = stage3;
    stages[3] = stage4;
    stages[4] = stage5;
    stages[5] = stage6;
    stages[6] = stage7;
    stages[7] = stage8;
    stages[8] = stage9;
    stages[9] = stage10;
    stages[10] = stage11;
    stages[11] = stage12;
    stages[12] = stage13;
    stages[13] = stage14;
    stages[14] = stage15;

	
	//MAIN MENU WINDOW/LOOP

	//create menu window
    Main_Menu menu(1200,800);

    Tutorial_Menu tutorial(menu.win);

    //create game object with already created window so we dont have to create new one in the game
    Game* game = new Game(menu.win);



    while (menu.win->isOpen())
    {
    	//display all the items on the window
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
	    				//if you press return (enter) run the game and pass both arrays of pointers to the game
	    				game->run(entities,stages);
	    				std::cout << "asd" << std::endl;
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

	    				//if mouse click event on option 0 (continue), run the game and pass both arrays of pointers to the game
						game->run(entities,stages);
						std::cout << "asd" << std::endl;
						delete game;
	    			}

	    			if (menu.isTouchingOption() == 2)
	    			{
	    				std::cout << "tut starting" << std::endl;
	    				if (tutorial.MainLoop())
	    				{
	    					continue;
	    				}

	    			}
	    			
	    			else if (menu.isTouchingOption() == 3)
	    			{
	    				menu.win->close();
	    			}
	    			break;
	    	}
	    }


    }
    
    //cleaning memory 
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
    delete stage7;
    delete stage8;
    delete stage9;
    delete stage10;
    delete stage11;
    delete stage12;
    delete stage13;
    delete stage14;
    delete stage15;
   // delete game;
	
	
	return 0;
	
}

