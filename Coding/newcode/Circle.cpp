#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "StringHelpers.hpp"
#include "Entity.cpp"

#define PI 3.14159265
#define ENTITIES_MAX 6
#define G_MAX 160.0

class Game
{
	public:
	
		Game();
		
		//functions
		void run(Entity* entities[ENTITIES_MAX]);
		void checkGravity(Entity* entities[ENTITIES_MAX], int character); //D: Now takes two arguments. Second for iteration
		void checkBounds(Entity* entities[ENTITIES_MAX]);
		bool isTouchingSurface(Entity* entities[ENTITIES_MAX], int stage_id, int character);//D: extra argument. Same reason

		void breadSelector(sf::Keyboard::Key key, int selectedEntity); //D: new function to update Tab selection.	
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
		//int currentlySelected; //D: added currentlySelected int

};


const float Game::PlayerSpeed = 250.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


//instantiates most objects and sets starting values
Game::Game() : mBackgroundTexture(), mBackground(),
			   mIsMovingUp(false), mIsMovingDown(false), mIsMovingRight(false),
			   mIsMovingLeft(false), mIsSpaceBar(false), mStatisticsText(), mStatisticsUpdateTime(),
			   mFont(), mArrowTexture(), mArrow(), g(0.6), timePerGravityUpdate(0.0002) 
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
	mArrow.setPosition(490+45,600-55);
	mArrow.setOrigin(45,55);

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
			if (entities[x]->isCircle)
			{
				entities[x]->eBounds.x = entities[x]->cCircle.getPosition().x - entities[x]->cRadius;
				entities[x]->eBounds.y = entities[x]->cCircle.getPosition().y - entities[x]->cRadius;
			}
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
			for (int x=0; x<ENTITIES_MAX; x++)	
				{
					if (entities[x]->gCurrent < G_MAX) entities[x]->gCurrent+=g;
					else entities[x]->gCurrent = G_MAX;
				}
			updateGravity = gravityClock.restart();
		}

		//processEvents(entities);
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents(entities);
			for (int x = 0; x<ENTITIES_MAX; x++) { checkGravity(entities, x); } //D: Loops per character. Separating gravity effects for each

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
		if (entities[x]->isClickable)
		{

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//std::cout << mMousePos.x << ", " << mMousePos.y << std::endl;
				//std::cout << "bounds X from " <<  entities[0]->eBounds.x << " to " << entities[0]->eBounds.x+entities[x]->eTextureSize.x << std::endl;
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


}

/*
void Game::breadSelector(sf::Keyboard::Key key, int selectedEntity)
{
	if ( key == sf::Keyboard::Tab)
	{
		currentlySelected ++;
		std::cout << "currentEntity is: " << currentEntityIndex << std::endl;
		std::cout << "currentlySelected is: " << currentlySelected << std::endl;
		return;
	}
	

	else 
	{
		//std::cout << "Not on TheBaker" << std::endl;
		return;
	}
}
*/

//stage id is index of entities which you need to apply the gravity check on
bool Game::isTouchingSurface(Entity* entities[ENTITIES_MAX], int stage_id, int x)
{
	
	if (entities[x]->isCircle)
	{
		if (
			((entities[x]->eBounds.x+entities[x]->eTextureSize.x >= entities[stage_id]->eBounds.x+8) &&
			 (entities[x]->eBounds.x <= entities[stage_id]->eBounds.x+entities[stage_id]->eTextureSize.x-8)) &&
			((entities[x]->eBounds.y+entities[x]->eTextureSize.x >= entities[stage_id]->eBounds.y) &&
			 entities[x]->eBounds.y+entities[x]->eTextureSize.y <= entities[stage_id]->eBounds.y+entities[stage_id]->eTextureSize.y+50)
			) 
			{
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , entities[stage_id]->eBounds.y-entities[x]->cRadius+5);
				return true;	
			}		
	}
	
	return false;

}

void Game::checkBounds(Entity* entities[ENTITIES_MAX])
{
	for (int x=0; x<ENTITIES_MAX; x++)
	{
		if (entities[x]->isCircle)
		{
			//floor
			if (entities[x]->cCircle.getPosition().y >= 785-entities[x]->cRadius) entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x,785-entities[x]->cRadius);
		}
	}



}


void Game::checkGravity(Entity* entities[ENTITIES_MAX], int character)
{
	bool isOnGround = true;
	//for (int x=0; x<4; x++) { entities[x]->isOnGround = true; }

	if (entities[character]->isCircle)
	{
			//need this to reset gravity if touching a surface
		if ( (entities[character]->cCircle.getPosition().y >=  785-entities[character]->cRadius) )  NULL;
		else if (isTouchingSurface(entities,4, character)) NULL; //4 is portal box
		else if (isTouchingSurface(entities,5, character)) NULL; //5 is line
		else 
		{
			isOnGround = false;
			//entities[x]->isOnGround = false;
			//std::cout << "entity: " << x << " , " << " gcurrent: " << entities[character]->gCurrent << std::endl;
			entities[character]->cCircle.move(0,entities[character]->gCurrent+entities[character]->weight);
		}
	}
	if (/*entities[x]->isOnGround*/isOnGround) entities[character]->gCurrent = g;
	checkBounds(entities);

	
		

}



void Game::processEvents(Entity* entities[ENTITIES_MAX])
{
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
				//breadSelector(event.key.code, 0); 
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
/*
	if (mIsSpaceBar && currentEntityIndex == 0) //Space only works, if TheBaker is selected.
	{
		std::cout << "SpaceBar check/currSelect: " << currentlySelected << std::endl;
		if (currentlySelected%3 == 1)
		{
			entities[1]->create();
		}

		else if (currentlySelected%3 == 2)
		{
			entities[2]->create();
		}
		
		else if (currentlySelected%3 == 0)
		{
			entities[3]->create();
		}
	}

*/
	if (mIsSpaceBar)
	{
		entities[currentEntityIndex]->cCircle.setPosition(entities[currentEntityIndex]->cCircle.getPosition().x,0);
	}
	if (mIsMovingUp)
	{	
		bool canMoveUp = true;
		for (int x=0; x<ENTITIES_MAX; x++)
		{
			if (currentEntityIndex == x || entities[x]->isCircle) continue;
			if (
				((entities[currentEntityIndex]->eBounds.x+entities[currentEntityIndex]->eTextureSize.x >= entities[x]->eBounds.x+8) &&
				 (entities[currentEntityIndex]->eBounds.x <= entities[x]->eBounds.x+entities[x]->eTextureSize.x-8)) &&
				((entities[currentEntityIndex]->eBounds.y <= entities[x]->eBounds.y+entities[x]->eTextureSize.y) &&
				 (entities[currentEntityIndex]->eBounds.y >= entities[x]->eBounds.y))
				) canMoveUp = false;

		}
		if ( !canMoveUp || entities[currentEntityIndex]->cCircle.getPosition().y <=0 ) NULL; //top of screen
		else 
		{
			movement.y -= PlayerSpeed;
			rotateangle = PlayerSpeed;
		}
	}	
		
	if (mIsMovingDown)
	{
		bool canMoveDown = true;
		for (int x=0; x<ENTITIES_MAX; x++)
		{
			if (currentEntityIndex == x || entities[x]->isCircle) continue;
			if (
				((entities[currentEntityIndex]->eBounds.x+entities[currentEntityIndex]->eTextureSize.x >= entities[x]->eBounds.x) &&
				 (entities[currentEntityIndex]->eBounds.x <= entities[x]->eBounds.x+entities[x]->eTextureSize.x)) &&
				((entities[currentEntityIndex]->eBounds.y+entities[currentEntityIndex]->eTextureSize.x >= entities[x]->eBounds.y) &&
				 entities[currentEntityIndex]->eBounds.y+entities[currentEntityIndex]->eTextureSize.y <= entities[x]->eBounds.y+entities[x]->eTextureSize.y)
				) 
				{
					canMoveDown = false;
				}
		}
		

		if  ( !canMoveDown  || (entities[currentEntityIndex]->cCircle.getPosition().y >= 785-entities[currentEntityIndex]->cRadius))  NULL;  //bottom of screen
		else
		{
			movement.y += PlayerSpeed;
			rotateangle = -PlayerSpeed;
		}
	}	
		


	if (mIsMovingLeft)
	{
		//std::cout << "currentEntityIndex: " << currentEntityIndex << std::endl;
		bool canMoveLeft = true;
		for (int x=0; x<ENTITIES_MAX; x++)
		{
			if (currentEntityIndex == x || entities[x]->isCircle) continue;
			if (
				((entities[currentEntityIndex]->eBounds.x <= entities[x]->eBounds.x+entities[x]->eTextureSize.x) &&
				 (entities[currentEntityIndex]->eBounds.x >= entities[x]->eBounds.x)) && 
				((entities[currentEntityIndex]->eBounds.y+entities[currentEntityIndex]->eTextureSize.y >= entities[x]->eBounds.y+8) && //+8 is give/take value
				 (entities[currentEntityIndex]->eBounds.y <= entities[x]->eBounds.y+entities[x]->eTextureSize.y-8))
				) canMoveLeft = false;
		}	
		if ( !canMoveLeft || (entities[currentEntityIndex]->cCircle.getPosition().x <= 0+entities[currentEntityIndex]->cRadius)) NULL;

		else 
		{
			movement.x -= PlayerSpeed;
			rotateangle = -PlayerSpeed;
		}
		


	}
	

	if (mIsMovingRight)
	{	
		bool canMoveRight = true;
		for (int x=0; x<ENTITIES_MAX; x++)
		{
			if (currentEntityIndex == x || entities[x]->isCircle) continue;

			if (
				((entities[currentEntityIndex]->eBounds.x + entities[currentEntityIndex]->eTextureSize.x >= entities[x]->eBounds.x) &&
				 (entities[currentEntityIndex]->eBounds.x + entities[currentEntityIndex]->eTextureSize.x <= entities[x]->eBounds.x+entities[x]->eTextureSize.x)) &&
				((entities[currentEntityIndex]->eBounds.y + entities[currentEntityIndex]->eTextureSize.y >= entities[x]->eBounds.y+8) &&
				 (entities[currentEntityIndex]->eBounds.y <= entities[x]->eBounds.y+entities[x]->eTextureSize.y-8))
				) canMoveRight = false;

		}
		if (!canMoveRight || (entities[currentEntityIndex]->cCircle.getPosition().x >= 1200-entities[currentEntityIndex]->cRadius)) NULL;
		else 
		{
			movement.x += PlayerSpeed;
			rotateangle = PlayerSpeed;
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
	for (int x=0; x<ENTITIES_MAX; x++) 
	{
		if (entities[x]->isCircle) mWindow.draw(entities[x]->cCircle);
		else mWindow.draw(entities[x]->eSprite);
	}
	mWindow.display();
}
