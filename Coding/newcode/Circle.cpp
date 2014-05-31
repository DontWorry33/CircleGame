#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include "StringHelpers.hpp"

class Game
{
	public:
	
		Game();
		
		//functions
		void run();
		void processEvents();
		void update(sf::Time elapsedTime);
		void render();

		void updateStatistics(sf::Time elapsedTime);	
		void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	
	
		//constans for update statistics
		static const float PlayerSpeed;
		static const sf::Time TimePerFrame;

		sf::RenderWindow mWindow;		
		
		//Circle sprite/texture
		sf::Texture	mCircleTexture;
		sf::CircleShape mCircle;
		
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
	
		//statistics
		sf::Font mFont;
		sf::Text mStatisticsText;
		sf::Time mStatisticsUpdateTime;
		std::size_t	mStatisticsNumFrames;
	
	
};


const float Game::PlayerSpeed = 200.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

//instantiates most objects and sets starting values
Game::Game() : mBackgroundTexture(), mBackground(), mCircleTexture(), mCircle(),
			   mIsMovingUp(false), mIsMovingDown(false), mIsMovingRight(false),
			   mIsMovingLeft(false), mStatisticsText(), mStatisticsUpdateTime(),
			   mFont()
{
	mWindow.create(sf::VideoMode(1200, 800), "CircleGame!");
	
	//set circle stuff
	mCircleTexture.loadFromFile("../../Baker_Images/TheBakerOne.png");
	mCircle.setTexture(&mCircleTexture);
	mCircle.setRadius(28.5);
	
	//set background
	mBackgroundTexture.loadFromFile("../../Stage_Images/Set-StageOne.png");
	mBackground.setTexture(mBackgroundTexture);
	
	//set all statistics
	mStatisticsNumFrames = 0;
	mFont.loadFromFile("Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(20);
	mStatisticsText.setColor(sf::Color::White);
	
	//Change as radius of circle changes.
	mCircleOrigin.x = 28.5;
	mCircleOrigin.y = 28.5;
	mCircle.setOrigin(mCircleOrigin);
	
	//Start pos relative to the map
	mStartPos.x = 490;
	mStartPos.y = 600;
	
	//Must add Origin if changed. Default is (0,0), easy to modify later with bigger circles.
	mCircle.setPosition(mStartPos.x+mCircleOrigin.x, mStartPos.y-mCircleOrigin.y);
	
	
	//Set current position to starting position
	mCirclePos = mCircle.getPosition();
	
	
}


//main game loop. Runs all functions, processes events, updates game, updates statistics and renders
//read 
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		std::cout << "X: " << mCirclePos.x << "\nY: " << mCirclePos.y << std::endl; //debugging purposes
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
		if (mCirclePos.y <= 0+mCircleOrigin.y) NULL; //top of screen
		else 
		{
			movement.y -= PlayerSpeed;
		}
	}	
		
	if (mIsMovingDown)
	{
		if  ((mCirclePos.x <= 287-mCircleOrigin.x && mCirclePos.y >=437-mCircleOrigin.y) || //top of portal box
				 (mCirclePos.y >= 595-mCircleOrigin.y) ||  //bottom of screen
				((mCirclePos.x > 580-mCircleOrigin.x && mCirclePos.x < 587+mCircleOrigin.x) && mCirclePos.y >= 400-mCircleOrigin.y)) NULL; //top of line
				
		else
		{
			movement.y += PlayerSpeed;
		}
	}	
		
	if (mIsMovingLeft)
	{
		
		if ((mCirclePos.x <= 235+mCircleOrigin.x && mCirclePos.y >= 400+mCircleOrigin.y) || //portal box
			   ((mCirclePos.x <= 590+mCircleOrigin.x && mCirclePos.x > 530+mCircleOrigin.x) && mCirclePos.y >= 370+mCircleOrigin.y)  ||  //line
				(mCirclePos.x <= 0+mCircleOrigin.x)) NULL;
		else 
		{
			movement.x -= PlayerSpeed;
			rotateangle = -PlayerSpeed;
		}
	}
	
	
	if (mIsMovingRight)
	{	
		if (((mCirclePos.x >= 570-mCircleOrigin.x && mCirclePos.x < 590-mCircleOrigin.x) && mCirclePos.y >= 370+mCircleOrigin.y)  || //line 
				 (mCirclePos.x >= 800-mCircleOrigin.x)) NULL;
		else 
		{
			movement.x += PlayerSpeed;
			rotateangle = PlayerSpeed;
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
	mWindow.draw(mCircle);
	//mWindow.draw(mStatisticsText);
	mWindow.display();
}

