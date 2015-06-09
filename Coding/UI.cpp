#include <iostream>
#include "Option.cpp"

#ifndef UI_CPP
#define UI_CPP

using namespace std;



struct UI
{
	//contains a pointer to a window so we don't have to re-create and destroy when we switch screens
	sf::RenderWindow* win;

	//intial screen you see 
	sf::Texture UI_bkg_img;
	sf::Sprite UI_bkg;

	//main menu mouse position
	sf::Vector2i mm_mousepos;

	//vector of option pointers
	vector<Option*> UI_options;

	//clock for fade timer
	sf::Clock fadeClock;


	virtual int isTouchingOption(){}; //ONLY CALL ONCE WIN AIS INSTANTIANATED
	virtual void render(){};
	virtual void fade(){};

};


struct Main_Menu : UI
{
	//creating option pointers (Option.cpp)
	Option* new_game;
	Option* about;
	Option* tutorials;
	Option* quit;


	Main_Menu(int winX, int winY)
	{
		//create main window for the program
		win = new sf::RenderWindow(sf::VideoMode(winX, winY),"Bound");

		//initalize variables with positions and add all to vector 
		UI_bkg_img.loadFromFile("../User_Interfaces/Main_Menu/Menu-Default.png");
		UI_bkg.setTexture(UI_bkg_img);
		new_game = new Option("../User_Interfaces/Main_Menu/Menu-NewGame.png", 62, 136, 240, 179);
		UI_options.push_back(new_game);
		about = new Option("../User_Interfaces/Main_Menu/Menu-About.png", 62, 179, 240, 222);
		UI_options.push_back(about);
		tutorials  = new Option("../User_Interfaces/Main_Menu/Menu-Tutorials.png", 62, 222, 240, 260);
		UI_options.push_back(tutorials);
		quit = new Option("../User_Interfaces/Main_Menu/Menu-Quit.png", 62, 260, 240, 300);
		UI_options.push_back(quit);

		//set main menu (mm) mouse position to 0 so it is initalized
		mm_mousepos.x = 0;
		mm_mousepos.y = 0;
	}

	~Main_Menu()
	{
		delete win;
		delete new_game;
		delete about;
		delete tutorials;
		delete quit;
		std::cout << "main menu destroyed" << std::endl;
	}


	int isTouchingOption()
	{
		//get position of mouse relative to current window
		mm_mousepos = sf::Mouse::getPosition(*(win));

		//iterate through the options
		for (int x=0; x<UI_options.size(); x++)
		{
			//checking if the mouse position is within the bounds of any of the option objects
			if (mm_mousepos.x >= UI_options[x]->option_tl_bound.x && mm_mousepos.x <= UI_options[x]->option_br_bound.x
				&& mm_mousepos.y >= UI_options[x]->option_tl_bound.y && mm_mousepos.y <= UI_options[x]->option_br_bound.y)
			{
				//returns the index of the option that the mouse is over
				return x;
			}
		}
		return -1;
	}

	void render()
	{
		//clear window
		win->clear();
		//get current option that is being hovered over
		int menuVal = isTouchingOption();
		//if the mouse is over an option then draw new background/effect/image for that option
		if (menuVal>=0) win->draw(UI_options[menuVal]->option);
		//if the mouse is not over any options, draw the default background
		else win->draw(UI_bkg);
		//display whats drawn on the window
		win->display();
	}

	void fade(sf::Sprite bkg_fadeout, sf::Sprite bkg_fadein)
	{
		//sf::Color curr = UI_options[0]->option.getColor();
		
		//set alpha color to full
		int x = 255;

		while (x > 0)
		{	
			sf::Time fade = fadeClock.getElapsedTime();
			if (fade.asSeconds() >= 0.001)
			{
				//get new time for fade 
				fade = fadeClock.restart();
				win->clear();

				//set the background alpha color to x
				bkg_fadeout.setColor(sf::Color(bkg_fadeout.getColor().r, 
				bkg_fadeout.getColor().g, bkg_fadeout.getColor().b, x));

				//draw the image with new alpha color
				win->draw(bkg_fadeout);
				win->display();

				std::cout << x << std::endl;
				
				//lower alpha color by a value to simulate darkening (fade out)
				x-=2;
			}
		}

		//reinitalize to 0 for full black screen
		x = 0;
		while (x < 255)
		{
			sf::Time fade = fadeClock.getElapsedTime();
			if (fade.asSeconds() >= 0.001)
			{
				fade = fadeClock.restart();
				win->clear();

				//set the fade in background color to x
				bkg_fadein.setColor(sf::Color(bkg_fadein.getColor().r, 
				bkg_fadein.getColor().g, bkg_fadein.getColor().b, x));
				std::cout << x << std::endl;

				//draw the new image with the new alpha color
				win->draw(bkg_fadein);	
				win->display();

				//increase alpha color by a value to simulate lightening (fade in)
				x+=2;
			}
		}
		x = 255;
	}

};


//comments identical to Main_Menu
struct Pause_Menu : UI
{
	Option* resume;
	Option* quit;

	bool isPaused;

	Pause_Menu(sf::RenderWindow* curr_win, const char* bkg, const char* res, const char* qui)
	{
		win = curr_win;
		UI_bkg_img.loadFromFile(bkg);
		UI_bkg.setTexture(UI_bkg_img);
		resume = new Option(res,515,350,680,385);
		UI_options.push_back(resume);
		quit = new Option(qui,515,415,621,454);
		UI_options.push_back(quit);
		isPaused = false;
	}


	int isTouchingOption()
	{
		mm_mousepos = sf::Mouse::getPosition(*(win));
		for (int x=0; x<UI_options.size(); x++)
		{
			if (mm_mousepos.x >= UI_options[x]->option_tl_bound.x && mm_mousepos.x <= UI_options[x]->option_br_bound.x
				&& mm_mousepos.y >= UI_options[x]->option_tl_bound.y && mm_mousepos.y <= UI_options[x]->option_br_bound.y)
			{
				return x;
			}
		}
		return -1;
	}

	void render()
	{
		win->clear();
		int menuVal = isTouchingOption();
		if (menuVal>=0) win->draw(UI_options[menuVal]->option);
		else win->draw(UI_bkg);
		win->display();
	}

	~Pause_Menu()
	{
		delete resume;
		delete quit;
		std::cout << "pause menu destroyed" << std::endl;
	}


};


struct Tutorial_Menu : UI
{
	Option* main;
	Option* hud;
	Option* controls;
	Option* dream;
	Option* lie;
	Option* wish;
	Option* switches;

	int currentScreen;

	//similar comments to Main_Menu
	Tutorial_Menu(sf::RenderWindow* curr_win)
	{
		win = curr_win;
		main = new Option("../User_Interfaces/Tutorial_Screens/Tutorial_Main.png");
		UI_options.push_back(main);
		hud = new Option("../User_Interfaces/Tutorial_Screens/Tutorial_HUD.png");
		UI_options.push_back(hud);
		controls = new Option("../User_Interfaces/Tutorial_Screens/Tutorial_Controls.png");
		UI_options.push_back(controls);
		dream = new Option("../User_Interfaces/Tutorial_Screens/Tutorial_Dream.png");
		UI_options.push_back(dream);
		lie = new Option("../User_Interfaces/Tutorial_Screens/Tutorial_Lie.png");
		UI_options.push_back(lie);
		wish = new Option("../User_Interfaces/Tutorial_Screens/Tutorial_Wish.png");
		UI_options.push_back(wish);
		switches = new Option("../User_Interfaces/Tutorial_Screens/Tutorial_Switches.png");
		UI_options.push_back(switches);

		currentScreen = 0;

	}
	//need a loop as we have to have events that capture keyboard presses to move on to screens
	bool MainLoop()
	{
		while (win->isOpen())
		{
			sf::Event event;
		    while (win->pollEvent(event))
		    {
		    	//std::cout << "inside tut loop" << std::endl;
		    	switch (event.type)
		    	{
		    		case sf::Event::Closed:
						win->close();
						break;
					case sf::Event::KeyPressed:
						//if the right arrow key is pressed, move on to the next screen and check if we are at the last one
		    			if (event.key.code == sf::Keyboard::Right)
		    			{
		    				NextScreen();
		    				if (IsComplete()) return true;
		    			}
		    			//if the left arrow key is pressed, go back a screen
		    			else if (event.key.code == sf::Keyboard::Left)
		    			{
		    				PreviousScreen();
		    			}
		    			//if escape is pressed, return to the main menu
		    			else if (event.key.code == sf::Keyboard::Escape)
		    			{
		    				return true;
		    			}
		    			break;
		    	}
		    	Render();
		    }
		}
	}

	//moves to the next screen
	void NextScreen()
	{
		//checks if we are at last index
		if (currentScreen < UI_options.size()) currentScreen++;
	}
	//moves to previous screen
	void PreviousScreen()
	{
		//makes sure we cant go under 0
		if (currentScreen > 0) currentScreen--;
	}

	bool IsComplete()
	{
		//check if on last screen
		if (currentScreen==7) 
		{
			//need to reset index to 0 in case tutorial is launched again
			currentScreen = 0;
			return true;
		}
		return false;

	}

	//draw to screen
	void Render()
	{
		win->clear();
		win->draw(UI_options[currentScreen]->option);
		win->display();

	}

	~Tutorial_Menu()
	{
		delete main;
		delete hud;
		delete controls;
		delete dream;
		delete lie;
		delete wish;
		delete switches;
	}

};

struct AboutPage : UI
{
	float speedMultiplier;

	AboutPage(sf::RenderWindow* curr_win)
	{
		win = curr_win;
		UI_bkg_img.loadFromFile("../User_Interfaces/Main_Menu/AboutPage.png");
		UI_bkg.setTexture(UI_bkg_img);
		UI_bkg.setPosition(UI_bkg.getPosition().x, 800);
		speedMultiplier = 1;
	}


	bool MainLoop()
	{
		while (win->isOpen())
		{
			sf::Event event;
		    while (win->pollEvent(event))
		    {
		    	//std::cout << "inside tut loop" << std::endl;
		    	switch (event.type)
		    	{
					case sf::Event::Closed:
						win->close();
						break;
					case sf::Event::KeyPressed:
						//if the right arrow key is pressed, move on to the next screen and check if we are at the last one
		    			if (event.key.code == sf::Keyboard::Return)
		    			{
		    				UI_bkg.setPosition(UI_bkg.getPosition().x,800);
		    				return true;
		    			}
		    			if (event.key.code == sf::Keyboard::Space)
		    			{
		    				speedMultiplier -= 0.05;
		    			}
		    			break;
		    		case sf::Event::KeyReleased:
						if (event.key.code == sf::Keyboard::Space)
		    			{
		    				speedMultiplier = 1;
		    			}		    			
		    			break;
		    	}

		    }
		    ScrollUp();
		    Render();
		}

	}

	void ScrollUp()
	{
		if (UI_bkg.getPosition().y <= 0) 
		{
			if (UI_bkg.getPosition().y == 0) return;
			std::cout << "resetting bkg pos" << std::endl;
			UI_bkg.setPosition(UI_bkg.getPosition().x, 0);
			return;
		}
		sf::Time scrollTime = fadeClock.getElapsedTime();
		if (scrollTime.asSeconds() > 0.05*speedMultiplier) 
		{
			scrollTime = fadeClock.restart();
			UI_bkg.move(0, -1);
		}
		

	}

	void Render()
	{
		win->clear();
		win->draw(UI_bkg);
		win->display();

	}



};

#endif