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
	Option* continue_game;
	Option* new_game;
	Option* tutorials;
	Option* quit;


	Main_Menu(int winX, int winY)
	{
		//create main window for the program
		win = new sf::RenderWindow(sf::VideoMode(winX, winY),"Bound");

		//initalize variables with positions and add all to vector 
		UI_bkg_img.loadFromFile("../User_Interfaces/Main_Menu/Menu-Default.png");
		UI_bkg.setTexture(UI_bkg_img);
		continue_game = new Option("../User_Interfaces/Main_Menu/Menu-Continue.png", 62, 136, 240, 179);
		UI_options.push_back(continue_game);
		new_game = new Option("../User_Interfaces/Main_Menu/Menu-NewGame.png", 62, 179, 240, 222);
		UI_options.push_back(new_game);
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
		delete continue_game;
		delete new_game;
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


//comments identical to Main_Menu
struct Tutorial_Menu : UI
{
	Tutorial_Menu(sf::RenderWindow* curr_win)
	{
		win = curr_win;

	}

};

#endif