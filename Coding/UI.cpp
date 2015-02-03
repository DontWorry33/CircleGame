#include <iostream>
#include "Option.cpp"

#ifndef UI_CPP
#define UI_CPP

using namespace std;



struct UI
{
	sf::RenderWindow win;
	sf::Texture UI_bkg_img;
	sf::Sprite UI_bkg;

	//main menu mouse position
	sf::Vector2i mm_mousepos;

	//vector of option pointers
	vector<Option*> UI_options;

	//clock for fade timer
	sf::Clock fadeClock;


	virtual int isTouchingOption(){}; //ONLY CALL ONCE WIN IS INSTANTIANATED
	virtual void render(){};
	virtual void fade(){};

};


struct Main_Menu : UI
{

	Option* none;
	Option* continue_game;
	Option* new_game;
	Option* tutorials;
	Option* quit;


	Main_Menu()
	{
		continue_game = new Option("../User_Interfaces/Main_Menu/Menu-Continue.png", 62, 136, 240, 160);
		UI_options.push_back(continue_game);
		new_game = new Option("../User_Interfaces/Main_Menu/Menu-NewGame.png", 62, 179, 240, 203);
		UI_options.push_back(new_game);
		tutorials  = new Option("../User_Interfaces/Main_Menu/Menu-Tutorials.png", 62, 222, 240, 246);
		UI_options.push_back(tutorials);
		quit = new Option("../User_Interfaces/Main_Menu/Menu-Quit.png", 62, 260, 240, 284);
		UI_options.push_back(quit);
	}

	Main_Menu(int winX, int winY)
	{

		win.create(sf::VideoMode(winX, winY),"Bound");
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
		mm_mousepos.x = 0;
		mm_mousepos.y = 0;
	}




	int isTouchingOption()
	{
		mm_mousepos = sf::Mouse::getPosition(win);
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
		win.clear();
		int menuVal = isTouchingOption();
		if (menuVal>=0) win.draw(UI_options[menuVal]->option);
		else win.draw(UI_bkg);
		win.display();
	}

	void fade()
	{
		//sf::Color curr = UI_options[0]->option.getColor();
		int x = 255;
		while (x!= 0)
		{	
			sf::Time fade = fadeClock.getElapsedTime();
			if (fade.asSeconds() >= 0.001)
			{
				fade = fadeClock.restart();
				win.clear();
				UI_options[0]->option.setColor(sf::Color(UI_options[0]->option.getColor().r, 
				UI_options[0]->option.getColor().g, UI_options[0]->option.getColor().b, x));
				win.draw(UI_options[0]->option);
				win.display();
				std::cout << x << std::endl;
				x--;
			}
		}

	}

};

#endif