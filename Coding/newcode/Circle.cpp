#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "StringHelpers.hpp"

#define PI 3.14159265

class Game
{
	public:
	
		Game();
		
		//functions
		void run();
		void checkGravity();
		void processEvents();
		void update(sf::Time elapsedTime);
		void render();

		void updateStatistics(sf::Time elapsedTime);	
		void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	
	
		//constants for update statistics
		static const float PlayerSpeed;
		static const sf::Time TimePerFrame;

		sf::RenderWindow mWindow;		
		
		//Circle sprite/texture
		sf::Texture	mCircleTexture;
		sf::CircleShape mCircle;
			
		//Arrow Indicator
		sf::Texture mArrowTexture;
		sf::Sprite mArrow;

		//Circle properties
		sf::Vector2f mCirclePos;
		sf::Vector2f mCircleOrigin;
		sf::Vector2f mStartPos;
		
		//Background sprite/texture
		sf::Texture mBackgroundTexture;
		sf::Sprite mBackground;
	
		//movement booleans
		bool mIsMovingUp;
		bool mIsMovingDown;
		bool mIsMovingRight;
		bool mIsMovingLeft;	

		//mouse position
		sf::Vector2i mMousePos;
	
		//statistics
		sf::Font mFont;
		sf::Text mStatisticsText;
		sf::Time mStatisticsUpdateTime;
		std::size_t	mStatisticsNumFrames;

		//Gravity
		const float g; //gravity constant initalized in constructor
		const float timePerGravityUpdate;  //amount of time before acceleration update
		float gCurrent; //curent gravity
		sf::Clock gravityClock; //measure time
	
	
};


const float Game::PlayerSpeed = 200.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


//instantiates most objects and sets starting values
Game::Game() : mBackgroundTexture(), mBackground(), mCircleTexture(), mCircle(),
			   mIsMovingUp(false), mIsMovingDown(false), mIsMovingRight(false),
			   mIsMovingLeft(false), mStatisticsText(), mStatisticsUpdateTime(),
			   mFont(), mArrowTexture(), mArrow(), g(0.6), timePerGravityUpdate(0.2)
{
	mWindow.create(sf::VideoMode(1200, 800), "CircleGame!");
	
	//set circle stuff
	mCircleTexture.loadFromFile("../../Character_Images/Anpan.png");
	mCircle.setTexture(&mCircleTexture);
	mCircle.setRadius(36);
	
	//set background
	mBackgroundTexture.loadFromFile("../../Stage_Images/IntroStage.png");
	mBackground.setTexture(mBackgroundTexture);
	
	//set all statistics
	mStatisticsNumFrames = 0;
	mFont.loadFromFile("Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setCharacterSize(20);
	mStatisticsText.setColor(sf::Color::White);
	
	//set arrow stuff
	mArrowTexture.loadFromFile("../../Character_Images/Arrowhead.png");
	mArrow.setTexture(mArrowTexture);
	mArrow.setPosition(490+45,600-30);
	mArrow.setOrigin(45,30);

	//Change as radius of circle changes.
	mCircleOrigin.x = mCircle.getRadius(); /* DEDIE: Should we just make this equal mCircle.setRadius? Since they are the same?*/
	mCircleOrigin.y = mCircleOrigin.x; //y must equal x to have perfect circle. Only need modify one value.
	mCircle.setOrigin(mCircleOrigin);
	
	//Start pos relative to the map
	mStartPos.x = 490;
	mStartPos.y = 0;
	
	//Must add Origin if changed. Default is (0,0), easy to modify later with bigger circles.
	mCircle.setPosition(mStartPos.x+mCircleOrigin.x, mStartPos.y-mCircleOrigin.y);
	
	
	//Set current position to starting position
	mCirclePos = mCircle.getPosition();

	gCurrent = g;
	
}


//main game loop. Runs all functions, processes events, updates game, updates statistics and renders
//read 
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		
		std::cout << "X: " << mMousePos.x << "\nY: " << mMousePos.y << std::endl; //debugging purposes

		//set the arrow position to follow the circle
		mArrow.setPosition(mCircle.getPosition());

		//get mouse-coordinates relative to the window
		mMousePos = sf::Mouse::getPosition(mWindow);
		
		//Positions of Origin for mArrow
		int cx=mArrow.getPosition().x;
		int cy=mArrow.getPosition().y;

		//The angle is arctangent of mArrow origin - current mouse position of Y/X.
		float angle_in_rad = atan2(cy-mMousePos.y,cx-mMousePos.x);

		//atan2 returns angle in radians, convert to degrees for debugging purposes		
		float angle_in_deg = (angle_in_rad*180)/PI;

		//apply formula to move mArrow around circumference of circle. (cx + r*cos(angle))
		mArrow.setPosition(cx-(mCircle.getRadius() * cos(angle_in_rad)), cy-(mCircle.getRadius() * sin(angle_in_rad)));
		
		//use setRotation to set new rotation angle instead of rotate(),  -90 since top left (x,y) = (0,0)
		mArrow.setRotation(angle_in_deg-90);

		//get the current amount of time elapsed
		sf::Time updateGravity = gravityClock.getElapsedTime();

		//if the current time is less than our update time
		if (updateGravity.asSeconds() <= timePerGravityUpdate)
		{
			//keep getting the time until it is greater
			updateGravity = gravityClock.getElapsedTime();

		}

		//once it is greater, update our current G (acceleration) and reset the clock to repeat
		else 
		{
			gCurrent+=g;
			updateGravity = gravityClock.restart();
		}


		//apply gravity
		checkGravity();

		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		updateStatistics(elapsedTime);
		render();
	}
}

void Game::checkGravity()
{
	if (mCirclePos.y <= 785-mCircleOrigin.y)
	{
		mCircle.move(0,gCurrent);
	}
	else gCurrent = g;

}


void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				break;

			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;

			case sf::Event::MouseMoved:
				break;

			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{	
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}


void Game::update(sf::Time elapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	int rotateangle=0;




	if (mIsMovingUp)
	{	
		if (mCirclePos.y >=0 ) NULL; //top of screen
		else 
		{
			movement.y -= PlayerSpeed;
			if ((mCirclePos.x <= 0+mCircleOrigin.x) ||
				((mCirclePos.x <= 775+mCircleOrigin.x && mCirclePos.x > 747-mCircleOrigin.x) && mCirclePos.y > 465-mCircleOrigin.y) ||
				(mCirclePos.x <= 455+mCircleOrigin.x && mCirclePos.x >= 87-mCircleOrigin.x && mCirclePos.y >= 735-mCircleOrigin.y)) rotateangle = -PlayerSpeed;
			else rotateangle = PlayerSpeed;
		}
	}	
		
	if (mIsMovingDown)
	{

		

		if  ((mCirclePos.x <= 450+mCircleOrigin.x && mCirclePos.x > 86-mCircleOrigin.x && mCirclePos.y >=732-mCircleOrigin.y) || //top of portal box
				 (mCirclePos.y >= 783-mCircleOrigin.y) ||  //bottom of screen
				((mCirclePos.x > 747-mCircleOrigin.x && mCirclePos.x <= 772+mCircleOrigin.x) && mCirclePos.y >= 463-mCircleOrigin.y)) NULL; //top of line
			
		else
		{
			movement.y += PlayerSpeed;
			if ((mCirclePos.x <= 0+mCircleOrigin.x) || 
				((mCirclePos.x <= 775+mCircleOrigin.x && mCirclePos.x > 747-mCircleOrigin.x) && mCirclePos.y > 465-mCircleOrigin.y) ||
				(mCirclePos.x <= 455+mCircleOrigin.x && mCirclePos.x >= 87-mCircleOrigin.x && mCirclePos.y >= 735-mCircleOrigin.y)) rotateangle=PlayerSpeed;
			else rotateangle = -PlayerSpeed;
		}
	}	
		


	if (mIsMovingLeft)
	{
		
		if ( (mCirclePos.x <= 455+mCircleOrigin.x && mCirclePos.x >= 87-mCircleOrigin.x && mCirclePos.y >= 735-mCircleOrigin.y) || //portal box
			   ((mCirclePos.x <= 775+mCircleOrigin.x && mCirclePos.x > 747-mCircleOrigin.x) && mCirclePos.y > 465-mCircleOrigin.y) ||  //line
				(mCirclePos.x <= 0+mCircleOrigin.x)) NULL;
		else 
		{
			movement.x -= PlayerSpeed;
			if (mCirclePos.y <= 0+mCircleOrigin.y) rotateangle = PlayerSpeed;
			else rotateangle = -PlayerSpeed;
		}
	}
	

	if (mIsMovingRight)
	{	
		if (((mCirclePos.x >= 745-mCircleOrigin.x && mCirclePos.x < 775-mCircleOrigin.x) && mCirclePos.y > 465-mCircleOrigin.y)  || //line 
				 (mCirclePos.x >= 1200-mCircleOrigin.x) || ((mCirclePos.x >= 81-mCircleOrigin.x && mCirclePos.x <= 455-mCircleOrigin.x) && mCirclePos.y >= 735-mCircleOrigin.x)) NULL;
		else 
		{
			movement.x += PlayerSpeed;
			if (mCirclePos.y <=0+mCircleOrigin.y) rotateangle = -PlayerSpeed;
			else rotateangle = PlayerSpeed;
		}
	}	
	
	
	mCircle.move(movement * elapsedTime.asSeconds());
	mCircle.rotate(rotateangle*elapsedTime.asSeconds());
	mCirclePos = mCircle.getPosition();
	
	
}



void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMilliseconds() / mStatisticsNumFrames) + "ms");
							 
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}


void Game::render()
{
	mWindow.clear();	
	mWindow.draw(mBackground);
	mWindow.draw(mStatisticsText);
	mWindow.draw(mArrow);
	mWindow.draw(mCircle);
	mWindow.display();
}

