#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "StringHelpers.hpp"
#include "Entity.cpp"

#define PI 3.14159265
#define ENTITIES_MAX 3


class Game
{
	public:
	
		Game();
		
		//functions
		void run(Entity* entities[ENTITIES_MAX]);
		void checkGravity(Entity* entities[ENTITIES_MAX]);
		void entitySelector(Entity* entities[ENTITIES_MAX]);
		void Arrow(Entity* entities[ENTITIES_MAX]);

		void processEvents(Entity* entities[ENTITIES_MAX]);
		void update(sf::Time elapsedTime,Entity* entities[ENTITIES_MAX]);
		void render(Entity* entities[ENTITIES_MAX]);

		void updateStatistics(sf::Time elapsedTime);	
		void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	
	
		//constants for update statistics
		static const float PlayerSpeed;
		static const sf::Time TimePerFrame;

		sf::RenderWindow mWindow;		

		//Arrow Indicator
		sf::Texture mArrowTexture;
		sf::Sprite mArrow;

		
		//Background sprite/texture
		sf::Texture mBackgroundTexture;
		sf::Sprite mBackground;
	
		//movement booleans
		bool mIsMovingUp;
		bool mIsMovingDown;
		bool mIsMovingRight;
		bool mIsMovingLeft;
		bool mIsSpaceBar;

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
	
	
		int currentEntityIndex;
};


const float Game::PlayerSpeed = 200.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/100.f);


//instantiates most objects and sets starting values
Game::Game() : mBackgroundTexture(), mBackground(),
			   mIsMovingUp(false), mIsMovingDown(false), mIsMovingRight(false),
			   mIsMovingLeft(false), mIsSpaceBar(false), mStatisticsText(), mStatisticsUpdateTime(),
			   mFont(), mArrowTexture(), mArrow(), g(0.6), timePerGravityUpdate(0.2)
{
	mWindow.create(sf::VideoMode(1200, 800), "CircleGame!");
	

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

	currentEntityIndex = 0;

	gCurrent = g;
	
}


//main game loop. Runs all functions, processes events, updates game, updates statistics and renders
//read 
void Game::run(Entity* entities[ENTITIES_MAX])
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		//set the arrow position to follow the circle
		mArrow.setPosition(entities[currentEntityIndex]->cCircle.getPosition());
		Arrow(entities);
		//get mouse-coordinates relative to the window
		mMousePos = sf::Mouse::getPosition(mWindow);
		for (int x=0; x<ENTITIES_MAX; x++)
		{

			entities[x]->eBounds.x = entities[x]->cCircle.getPosition().x - entities[x]->cRadius;
			entities[x]->eBounds.y = entities[x]->cCircle.getPosition().y - entities[x]->cRadius;

		}
		
		//std::cout << "X: " << mMousePos.x << "\nY: " << mMousePos.y << std::endl; //debugging purposes
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
			for (int x=0; x<ENTITIES_MAX; x++)	entities[x]->gCurrent+=g;
			updateGravity = gravityClock.restart();
		}


		
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents(entities);
			update(TimePerFrame,entities);
		}
		updateStatistics(elapsedTime);
		render(entities);
	}
}


void Game::Arrow(Entity* entities[ENTITIES_MAX])
{
		//Positions of Origin for mArrow
		int cx=mArrow.getPosition().x;
		int cy=mArrow.getPosition().y;

		//The angle is arctangent of mArrow origin - current mouse position of Y/X.
		float angle_in_rad = atan2(cy-mMousePos.y,cx-mMousePos.x);

		//atan2 returns angle in radians, convert to degrees for debugging purposes		
		float angle_in_deg = (angle_in_rad*180)/PI;

		//apply formula to move mArrow around circumference of circle. (cx + r*cos(angle))
		mArrow.setPosition(cx-(entities[currentEntityIndex]->cRadius * cos(angle_in_rad)), cy-(entities[currentEntityIndex]->cRadius * sin(angle_in_rad)));
		
		//use setRotation to set new rotation angle instead of rotate(),  -90 since top left (x,y) = (0,0)
		mArrow.setRotation(angle_in_deg-90);

}

void Game::entitySelector(Entity* entities[ENTITIES_MAX])
{

	for (int x=0; x<ENTITIES_MAX; x++)
	{


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			std::cout << mMousePos.x << ", " << mMousePos.y << std::endl;
			std::cout << "bounds X from " <<  entities[0]->eBounds.x << " to " << entities[0]->eBounds.x+entities[x]->eTextureSize.x << std::endl;
			 if ( ((mMousePos.x >= entities[x]->eBounds.x) &&
				(mMousePos.x <= entities[x]->eBounds.x+entities[x]->eTextureSize.x)) && 
				((mMousePos.y >= entities[x]->eBounds.y) && 
				mMousePos.y <= entities[x]->eBounds.y+entities[x]->eTextureSize.y))
			{
				entities[x]->isCurrentEntity = true;
			}
			else entities[x]->isCurrentEntity = false;
		}
	}


}


void Game::checkGravity(Entity* entities[ENTITIES_MAX])
{
	bool isOnGround = true;
	for (int x=0; x<ENTITIES_MAX; x++)
	{

		if (entities[x]->cCircle.getPosition().y <= 785-entities[x]->cRadius)
		{
			isOnGround = false;
			entities[x]->cCircle.move(0,entities[x]->gCurrent+entities[x]->weight);
		}
		if (isOnGround) entities[x]->gCurrent = g;
	}
}


void Game::processEvents(Entity* entities[ENTITIES_MAX])
{
		checkGravity(entities);

		entitySelector(entities);
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
	if (key == sf::Keyboard::Space)
		mIsSpaceBar = isPressed;
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;

}


void Game::update(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX])
{
	sf::Vector2f movement(0.f, 0.f);
	int rotateangle=0;
	for (int x=0; x<ENTITIES_MAX; x++)
	{
		if (entities[x]->isCurrentEntity) currentEntityIndex = x;
	}


	if (mIsSpaceBar)
		entities[currentEntityIndex]->cCircle.setPosition(entities[currentEntityIndex]->cCircle.getPosition().x, 0);


	if (mIsMovingUp)
	{	
		if (entities[currentEntityIndex]->cCircle.getPosition().y >=0 ) NULL; //top of screen
		else 
		{
			movement.y -= PlayerSpeed;
			if ((entities[currentEntityIndex]->cCircle.getPosition().x <= 0+entities[currentEntityIndex]->cRadius) ||
				((entities[currentEntityIndex]->cCircle.getPosition().x <= 775+entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().x > 747-entities[currentEntityIndex]->cRadius) && entities[currentEntityIndex]->cCircle.getPosition().y > 465-entities[currentEntityIndex]->cRadius) ||
				(entities[currentEntityIndex]->cCircle.getPosition().x <= 455+entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().x >= 87-entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().y >= 735-entities[currentEntityIndex]->cRadius)) rotateangle = -PlayerSpeed;
			else rotateangle = PlayerSpeed;
		}
	}	
		
	if (mIsMovingDown)
	{

		

		if  ((entities[currentEntityIndex]->cCircle.getPosition().x <= 450+entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().x > 86-entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().y >=732-entities[currentEntityIndex]->cRadius) || //top of portal box
				 (entities[currentEntityIndex]->cCircle.getPosition().y >= 783-entities[currentEntityIndex]->cRadius) ||  //bottom of screen
				((entities[currentEntityIndex]->cCircle.getPosition().x > 747-entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().x <= 772+entities[currentEntityIndex]->cRadius) && entities[currentEntityIndex]->cCircle.getPosition().y >= 463-entities[currentEntityIndex]->cRadius)) NULL; //top of line
			
		else
		{
			movement.y += PlayerSpeed;
			if ((entities[currentEntityIndex]->cCircle.getPosition().x <= 0+entities[currentEntityIndex]->cRadius) || 
				((entities[currentEntityIndex]->cCircle.getPosition().x <= 775+entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().x > 747-entities[currentEntityIndex]->cRadius) && entities[currentEntityIndex]->cCircle.getPosition().y > 465-entities[currentEntityIndex]->cRadius) ||
				(entities[currentEntityIndex]->cCircle.getPosition().x <= 455+entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().x >= 87-entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().y >= 735-entities[currentEntityIndex]->cRadius)) rotateangle=PlayerSpeed;
			else rotateangle = -PlayerSpeed;
		}
	}	
		


	if (mIsMovingLeft)
	{
		
		if ( (entities[currentEntityIndex]->cCircle.getPosition().x <= 455+entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().x >= 87-entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().y >= 735-entities[currentEntityIndex]->cRadius) || //portal box
			   ((entities[currentEntityIndex]->cCircle.getPosition().x <= 775+entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().x > 747-entities[currentEntityIndex]->cRadius) && entities[currentEntityIndex]->cCircle.getPosition().y > 465-entities[currentEntityIndex]->cRadius) ||  //line
				(entities[currentEntityIndex]->cCircle.getPosition().x <= 0+entities[currentEntityIndex]->cRadius)) NULL;
		else 
		{
			movement.x -= PlayerSpeed;
			if (entities[currentEntityIndex]->cCircle.getPosition().y <= 0+entities[currentEntityIndex]->cRadius) rotateangle = PlayerSpeed;
			else rotateangle = -PlayerSpeed;
		}
	}
	

	if (mIsMovingRight)
	{	
		if (((entities[currentEntityIndex]->cCircle.getPosition().x >= 745-entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().x < 775-entities[currentEntityIndex]->cRadius) && entities[currentEntityIndex]->cCircle.getPosition().y > 465-entities[currentEntityIndex]->cRadius)  || //line 
				 (entities[currentEntityIndex]->cCircle.getPosition().x >= 1200-entities[currentEntityIndex]->cRadius) || ((entities[currentEntityIndex]->cCircle.getPosition().x >= 81-entities[currentEntityIndex]->cRadius && entities[currentEntityIndex]->cCircle.getPosition().x <= 455-entities[currentEntityIndex]->cRadius) && entities[currentEntityIndex]->cCircle.getPosition().y >= 735-entities[currentEntityIndex]->cRadius)) NULL;
		else 
		{
			movement.x += PlayerSpeed;
			if (entities[currentEntityIndex]->cCircle.getPosition().y <=0+entities[currentEntityIndex]->cRadius) rotateangle = -PlayerSpeed;
			else rotateangle = PlayerSpeed;
		}
	}	
	
	
	entities[currentEntityIndex]->cCircle.move(movement * elapsedTime.asSeconds());
	entities[currentEntityIndex]->cCircle.rotate(rotateangle*elapsedTime.asSeconds());
	//mCirclePos = mCircle.getPosition();
	
	
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


void Game::render(Entity* entities[ENTITIES_MAX])
{
	mWindow.clear();	
	mWindow.draw(mBackground);
	mWindow.draw(mStatisticsText);
	mWindow.draw(mArrow);
	for (int x=0; x<ENTITIES_MAX; x++) mWindow.draw(entities[x]->cCircle);
	mWindow.display();
}

