#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>


using namespace std
;
int main()
{
	//Creates RenderWindow object with dimensons of 800x600 labeled CircleGame
    sf::RenderWindow window(sf::VideoMode(800, 600), "CircleGame!");
    //window.setKeyRepeatEnabled(true);


    //Create background sprite/image.
    sf::Texture bkg_img;
    bkg_img.loadFromFile("Set-StageOne.png");
    sf::Sprite bkg;
    bkg.setTexture(bkg_img);


    sf::CircleShape shape(20.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(460,555);

    int shape_x;
    int shape_y;


    while (window.isOpen())
    {
        sf::Event event;

        //Store X and Y positions of the circle to variables
        shape_x = shape.getPosition().x;
        shape_y = shape.getPosition().y;

        //debugging purposes
        cout << "X : " << shape_x << endl << "Y: " << shape_y << endl;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //if key pressed is A
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			//checks collisions and does nothing if it is colliding
			if ((shape_x <= 235 && shape_y >= 400) || //portal box
			   ((shape_x <= 590 && shape_x > 530) && shape_y >= 370)  ||  //line
			    (shape_x <= 0)) NULL; //left side of screen

			//if no collisions, then move
        		else shape.move(-5.f,0.f);
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//checks collisions and does nothing if it is colliding
			if (((shape_x >= 530 && shape_x < 590) && shape_y >= 370)  || //line 
				 (shape_x+40 >= 800)) NULL; //right side of screen

			//if no collisions, then move
			else shape.move(5.f,0.f);
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			//checks collisions and does nothing if it is colliding
			if (shape_y <= 0) NULL; //top of screen
			
			//if no collisions, then move
			else shape.move(0.f,-5.f);
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			//checks collisions and does nothing if it is colliding
			if  ((shape_x+5 <= 235 && shape_y >=395) || //top of portal box
				 (shape_y+40 >= 595) ||  //bottom of screen
				((shape_x > 530 && shape_x < 590) && shape_y >= 365)) NULL; //top of line

			//if no collisions, then move
            		else shape.move(0.f,5.f);
		}


        window.clear();
       
        window.draw(bkg);
        window.draw(shape);

        window.display();
    }

    return 0;
}
