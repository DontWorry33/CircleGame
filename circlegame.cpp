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

    //create texture for circle
    sf::Texture shape_img;
    shape_img.loadFromFile("temp_circle_texture.png");

    //create circle and set texture
    sf::CircleShape shape(20.f);
    shape.setTexture(&shape_img);

    //set origin coords of circle to radius=20 for good rotation
    int origin_x = 20;
    int origin_y = 20;

    //set origin of circle to coords.
    shape.setOrigin(origin_x,origin_y);

    //set original position
    shape.setPosition(460+origin_x,555+origin_y);

    //x and y coords of circle
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
			if ((shape_x <= 235+origin_x && shape_y >= 400+origin_y) || //portal box
			   ((shape_x <= 590+origin_x && shape_x > 530+origin_x) && shape_y >= 370+origin_y)  ||  //line
			    (shape_x <= 0+origin_x)) NULL; //left side of screen

			//if no collisions, then move and rotate
        	else
            {
                shape.move(-5.f,0.f);
                shape.rotate(-5.f);
            } 
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//checks collisions and does nothing if it is colliding
			if (((shape_x >= 530+origin_x && shape_x < 590+origin_x) && shape_y >= 370+origin_y)  || //line 
				 (shape_x+40 >= 800+origin_x)) NULL; //right side of screen

			//if no collisions, then move and rotate
			else 
            {
                shape.move(5.f,0.f);
                shape.rotate(5.f);
            }
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			//checks collisions and does nothing if it is colliding
			if (shape_y <= 0+origin_y) NULL; //top of screen
			
			//if no collisions, then move
			else shape.move(0.f,-5.f);
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			//checks collisions and does nothing if it is colliding
			if  ((shape_x+5 <= 235+origin_x && shape_y >=395+origin_y) || //top of portal box
				 (shape_y+40 >= 595+origin_y) ||  //bottom of screen
				((shape_x > 530+origin_x && shape_x < 590+origin_x) && shape_y >= 365+origin_y)) NULL; //top of line

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
