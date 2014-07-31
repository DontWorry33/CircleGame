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
		int run(Entity* entities[ENTITIES_MAX]);
		void checkGravity(Entity* entities[ENTITIES_MAX], int character); //D: Now takes two arguments. Second for iteration
		void checkBounds(Entity* entities[ENTITIES_MAX]);
		bool isTouchingSurface(Entity* entities[ENTITIES_MAX], int stage_id, int character);//D: extra argument. Same reason

		void breadSelector(sf::Keyboard::Key key, int selectedEntity); //D: new function to update Tab selection.
		void powerMetreUpdate(sf::Keyboard::Key key);	
		void entitySelector(Entity* entities[ENTITIES_MAX]);
		void Arrow(Entity* entities[ENTITIES_MAX]);
		void trajectory(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX]); //D: Function for firing Entities
		bool checkHitting(Entity* entities[ENTITIES_MAX]);
		void activateRotiPower(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX]);
		void activateAnpanPower(Entity* entities[ENTITIES_MAX]);


		void processEvents(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX]);
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
		bool mTeleportation;


		//Trajectory
		bool mIsLaunched; //D: used to initiate trajectory.
		sf::Clock shotClock; //length of shooting force's application.
		const float timePerShot;


		//mouse position
		sf::Vector2i mMousePos;
	
		//statistics
		sf::Font mFont;
		sf::Text mStatisticsText;
		sf::Time mStatisticsUpdateTime;
		std::size_t	mStatisticsNumFrames;

		//power gauuge
		sf::Sprite mPowerGaugeShell;
		sf::Sprite mPowerGaugeMetre;
		sf::Texture mPowerGaugeShellTexture;
		sf::Texture mPowerGaugeMetreTexture;


		//
		float powerMetre;

		//Gravity
		const float g; //gravity constant initalized in constructor
		const float timePerGravityUpdate;  //amount of time before acceleration update
		float gCurrent; //curent gravity
		sf::Clock gravityClock; //measure time
	
	
		int currentEntityIndex;
		int currentlySelected; //D: added currentlySelected int
		int shotChooser;

		bool mouseLock;
		bool repulsionReady;

		bool positionLock;

		bool mResetGame;

		bool mDrawMetre;


		//stores position of baker so we can manipulate  positionLock.
		sf::Vector2f traj_pos;

};


const float Game::PlayerSpeed = 150.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


//instantiates most objects and sets starting values
Game::Game() : mBackgroundTexture(), mBackground(),
			   mIsMovingUp(false), mIsMovingDown(false), mIsMovingRight(false),
			   mIsMovingLeft(false), mIsSpaceBar(false), mTeleportation(false), mStatisticsText(), mStatisticsUpdateTime(), repulsionReady(false),
			   mFont(), mArrowTexture(), mPowerGaugeShell(), mPowerGaugeShellTexture() , mArrow(), g(0.6), 
			   timePerGravityUpdate(0.0002), mPowerGaugeMetreTexture(), mPowerGaugeMetre(),  timePerShot(10000.0), shotChooser(1)	

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

	//set powergauge stuff
	mPowerGaugeMetreTexture.loadFromFile("../../Character_Images/PowerGauge_Metre.png");
	mPowerGaugeShellTexture.loadFromFile("../../Character_Images/PowerGauge_Shell.png");
	mPowerGaugeMetre.setTexture(mPowerGaugeMetreTexture);
	mPowerGaugeShell.setTexture(mPowerGaugeShellTexture);


	//current entity index is the bread which is clicked
	currentEntityIndex = 0;

	//currently selected is which bread is going to be fired
	currentlySelected = 1;

	gCurrent = g;


	//this determins wether we call trajectory or not.
	mIsLaunched = false;

	//power bar multiplier for trajectory
	powerMetre = 0;

	//Locks mouse and position when trajectory is active so that we don't get curved bread.
	mouseLock=false;
	positionLock = false;

	//checks to see if we pressed "r"
	mResetGame = false;

	//Only draws meter when we hit space
	mDrawMetre = false;
}


//main game loop. Runs all functions, processes events, updates game, updates statistics and renders
//read 
int Game::run(Entity* entities[ENTITIES_MAX])
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		
		//get the current amount of time elapsed
		if (mResetGame) break;

		
		//processEvents(elapsedTime, entities);
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{

			timeSinceLastUpdate -= TimePerFrame;

			//if mouse lock is not active, get the curr pos, same with position
			if (!mouseLock) mMousePos = sf::Mouse::getPosition(mWindow);
			if (!positionLock)
			{
				traj_pos = entities[0]->cCircle.getPosition();
			//	std::cout << "lock pos(X): " << traj_pos.x << std::endl;
				mArrow.setPosition(entities[currentEntityIndex]->cCircle.getPosition());

			}
			else
			{
				mArrow.setPosition(traj_pos);
			}
			//	std::cout << "LOCKED!!!" << std::endl;

			//set the arrow position to follow the circle

			mPowerGaugeShell.setPosition(entities[currentEntityIndex]->cCircle.getPosition().x-100,entities[currentEntityIndex]->cCircle.getPosition().y-80);
			mPowerGaugeMetre.setPosition(mPowerGaugeShell.getPosition());


			Arrow(entities);
			//get mouse-coordinates relative to the window

			for (int x=0; x<ENTITIES_MAX; x++)
			{
				if (entities[x]->isCircle)
				{
					entities[x]->eBounds.x = entities[x]->cCircle.getPosition().x - entities[x]->cRadius;
					entities[x]->eBounds.y = entities[x]->cCircle.getPosition().y - entities[x]->cRadius;
				}
			}

			for (int x = 0; x<ENTITIES_MAX; x++) { if (entities[x]->isCircle) checkGravity(entities, x); } //D: Loops per character. Separating gravity effects for each

	//---------------------GRAVITY
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

				//std::cout << "PM : " << powerMetre << std::endl;


				if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && currentEntityIndex == 1 && abs (entities[0]->cCircle.getPosition().x - entities[1]->cCircle.getPosition().x) < 200)
				{
					entities[currentEntityIndex]->gCurrent = 0;
					entities[0]->gCurrent = 0;
				}


	//--------------TRAJECTORY PARAMETERS
				if ( (mIsLaunched)) 
				{
					positionLock = true;
					mouseLock=true;

					trajectory(elapsedTime, entities);
				
				//Right Border Collision Check	
					if (entities[shotChooser]->cCircle.getPosition().x >= 1200 - entities[shotChooser]->cRadius)
					{
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->cCircle.setPosition(1200-entities[shotChooser]->cRadius, entities[shotChooser]->cCircle.getPosition().y);
				
						entities[shotChooser]->isCreated = true;
						entities[shotChooser]->gCurrent = 0;	
					}
					
				//Left Border Collision Check	
					if (entities[shotChooser]->cCircle.getPosition().x <= 0 + entities[shotChooser]->cRadius)
					{
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->cCircle.setPosition(0+entities[shotChooser]->cRadius, entities[shotChooser]->cCircle.getPosition().y);
					
						entities[shotChooser]->gCurrent = 0;	
						entities[shotChooser]->isCreated = true;
					}

				//Top Border Collision Check
					if (entities[shotChooser]->cCircle.getPosition().y <= 0+entities[shotChooser]->cRadius)
					{
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->cCircle.setPosition(entities[shotChooser]->cCircle.getPosition().x,0+entities[shotChooser]->cRadius);
					
						entities[shotChooser]->gCurrent = 0;	
						entities[shotChooser]->isCreated = true;
					}

				//Bottom Border Collision Check
					if (entities[shotChooser]->cCircle.getPosition().y >= 770-entities[shotChooser]->cRadius)
					{
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->cCircle.setPosition(entities[shotChooser]->cCircle.getPosition().x,785-entities[shotChooser]->cRadius);
					
						entities[shotChooser]->isCreated = true;
						entities[shotChooser]->gCurrent = 0;	
					}
					
					if (checkHitting(entities))
					{
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->gCurrent = 0;	
						entities[shotChooser]->isCreated = true;
					}
					

					
					if (isTouchingSurface(entities, 4, shotChooser))
					{
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->isCreated = true;
					}

					if (isTouchingSurface(entities, 5, shotChooser))
					{
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->isCreated = true;
					}						
				}


				else 
				{
					mouseLock=false;
					positionLock=false;
				}

			processEvents(elapsedTime, entities);

			update(TimePerFrame,entities);
		}

		updateStatistics(elapsedTime);
		render(entities);
	}
	if (mResetGame) return 1;
	return 0;
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

	//Power: Attracting Baker towards it.
void Game::activateRotiPower(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX])
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && currentEntityIndex == 1)
	{
		sf::Vector2f attract_direction(0.f, 0.f);
		int rotateangle = 0;
/*
		else if ( abs (entities[0]->cCircle.getPosition().x - entities[1]->cCircle.getPosition().x) > 200 )
		{
			repulsionReady = false;
		}
 */

	//If Roti is Right of Baker (Greater)
		if (entities[1]->cCircle.getPosition().x > entities[0]->cCircle.getPosition().x)
		{
			for ( int x = 5 ; x < ENTITIES_MAX; x++ )
			{
				if (
					((entities[0]->eBounds.x + entities[0]->eTextureSize.x >= entities[x]->eBounds.x) &&
			 		(entities[0]->eBounds.x + entities[0]->eTextureSize.x <= entities[x]->eBounds.x+entities[5]->eTextureSize.x)) &&
					((entities[0]->eBounds.y + entities[0]->eTextureSize.y >= entities[x]->eBounds.y+8) &&
			 		(entities[0]->eBounds.y <= entities[x]->eBounds.y+entities[x]->eTextureSize.y-8))
			   	) entities[0]->canMoveRight = false; 

				if( !entities[0]->canMoveRight) NULL;
			
				else
				{	
					attract_direction.x += 150.0;
					rotateangle = 150.0;
				}
			}
		}
		
		

	//If Roti is Left of Baker (Less)
		if (entities[1]->cCircle.getPosition().x < entities[0]->cCircle.getPosition().x)
		{
			for (int x = 5; x < ENTITIES_MAX; x++)
			{
				if (
					((entities[0]->eBounds.x <= entities[x]->eBounds.x+entities[x]->eTextureSize.x) &&
					 (entities[0]->eBounds.x >= entities[x]->eBounds.x)) && 
					((entities[0]->eBounds.y+entities[0]->eTextureSize.y >= entities[x]->eBounds.y+8) && //+8 is give/take value
					 (entities[0]->eBounds.y <= entities[x]->eBounds.y+entities[x]->eTextureSize.y-8))
					) entities[0]->canMoveLeft = false;
	
				if (!entities[0]->canMoveLeft) NULL;
			
				else 
				{
					attract_direction.x -= 150.0;
					rotateangle = -150.0;
				}
			}
		}
		
/*
		//If Roti is Above of Baker (Less)
		if (entities[1]->cCircle.getPosition().y < entities[0]->cCircle.getPosition().y)
		{
			attract_direction.y -= 150.0;
			entities[0]->cCircle.move(attract_direction * elapsedTime.asSeconds());
	
		}
		
		//If Roti is Beneath of Baker (More)
		if (entities[1]->cCircle.getPosition().y > entities[0]->cCircle.getPosition().y)
		{
			attract_direction.y += 150.0;
			entities[0]->cCircle.move(attract_direction * elapsedTime.asSeconds());
	
		}
*/
		entities[0]->cCircle.move(attract_direction * elapsedTime.asSeconds());
		entities[0]->cCircle.rotate(rotateangle*elapsedTime.asSeconds());
	}
}


	//Power: Swapping places with Baker
void Game::activateAnpanPower(Entity* entities[ENTITIES_MAX])
{

	//Need to check if able to fit first, refer to bugs.txt

	//currentEntityIndex 2 = Boule. Check main.cpp for indicies.
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && currentEntityIndex == 2)
	{
		std::cout << "activating SWAP" << std::endl;	
		sf::Vector2f temp_pos = entities[0]->cCircle.getPosition();
		entities[0]->cCircle.setPosition(entities[currentEntityIndex]->cCircle.getPosition());
		entities[currentEntityIndex]->cCircle.setPosition(temp_pos);
		entities[currentEntityIndex]->isCurrentEntity = false;
		currentEntityIndex = 0;
		entities[0]->isCurrentEntity = true;

	}

}


void Game::breadSelector(sf::Keyboard::Key key, int selectedEntity)
{
	if ( key == sf::Keyboard::Tab)
	{
		currentlySelected++;
		return;
	}
}

void Game::powerMetreUpdate(sf::Keyboard::Key key)
{
	//bool positive = true;
	if (key == sf::Keyboard::Space) 
		{
			mDrawMetre = true;
			if (powerMetre <=60 ) powerMetre+=1.5;
			else powerMetre = 0;
		}
	else 
		{
			mDrawMetre=false;
			if (!mIsLaunched) powerMetre=0;
		}


}

//stage id is index of entities which you need to apply the gravity check on
bool Game::isTouchingSurface(Entity* entities[ENTITIES_MAX], int stage_id, int x)
{
	
	if (entities[x]->isCircle)
	{		
		if (
			((entities[x]->eBounds.x+entities[x]->eTextureSize.x >= entities[stage_id]->eBounds.x) &&
			 (entities[x]->eBounds.x <= entities[stage_id]->eBounds.x+entities[stage_id]->eTextureSize.x)) &&
			((entities[x]->eBounds.y+entities[x]->eTextureSize.y >= entities[stage_id]->eBounds.y) &&
			 entities[x]->eBounds.y+entities[x]->eTextureSize.y <= entities[stage_id]->eBounds.y+25)
			)
			{
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , entities[stage_id]->eBounds.y-entities[x]->cRadius);
				//std::cout << "touchin da surf" << std::endl;
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
			entities[character]->cCircle.move(0,entities[character]->gCurrent+entities[character]->weight);
		}
	}
	if (isOnGround) entities[character]->gCurrent = g;
	checkBounds(entities);

}


bool Game::checkHitting(Entity* entities[ENTITIES_MAX])
{
	
	for (int x=0; x<ENTITIES_MAX; x++)
	{
		if (!entities[x]->isCircle)
		{
			if (				
				(
				((entities[shotChooser]->eBounds.x <= entities[x]->eBounds.x+entities[x]->eTextureSize.x) &&
				 (entities[shotChooser]->eBounds.x >= entities[x]->eBounds.x)) && 
				((entities[shotChooser]->eBounds.y+entities[shotChooser]->eTextureSize.y >= entities[x]->eBounds.y) && //+8 is give/take value
				 (entities[shotChooser]->eBounds.y <= entities[x]->eBounds.y+entities[x]->eTextureSize.y))
				)

				||

				(
				((entities[shotChooser]->eBounds.x + entities[shotChooser]->eTextureSize.x >= entities[x]->eBounds.x) &&
				 (entities[shotChooser]->eBounds.x + entities[shotChooser]->eTextureSize.x <= entities[x]->eBounds.x+entities[x]->eTextureSize.x)) &&
				((entities[shotChooser]->eBounds.y + entities[shotChooser]->eTextureSize.y >= entities[x]->eBounds.y+8) &&
				 (entities[shotChooser]->eBounds.y <= entities[x]->eBounds.y+entities[x]->eTextureSize.y-8))
				)

			   )

				{
					std::cout << x << "  IS TOUCHING STAGE PART" << std::endl;
					return true;
				}
		}
	}
	return false;
}

void Game::trajectory(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX])
{


	sf::Vector2f motion(0.f, 0.f);	
	double xDirection = mArrow.getPosition().x - traj_pos.x;
	double yDirection = mArrow.getPosition().y - traj_pos.y;

	if (mIsLaunched && !(entities[shotChooser]->isCreated))
	{
		motion.y += yDirection*(powerMetre/2);
		motion.x += xDirection*(powerMetre/2);
		entities[shotChooser]->cCircle.move(motion * elapsedTime.asSeconds());
	}
}



void Game::processEvents(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX])
{
	entitySelector(entities);
	activateRotiPower(elapsedTime, entities);
	sf::Event event;
	
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				breadSelector(event.key.code, 0);
				powerMetreUpdate(event.key.code); 
				break;

			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				
				if (event.key.code == sf::Keyboard::Space) 
					{
						mIsLaunched = true;
						//powerMetre=0;
					}
				
				break;

			case sf::Event::MouseMoved:
				break;


			case sf::Event::MouseButtonPressed:
				activateAnpanPower(entities);
				//activateRotiPower(elapsedTime, entities);
				break;


			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{	
	if (key == sf::Keyboard::Space){
		mIsSpaceBar = isPressed;
		//powerMetreUpdate(key);		
	}
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
	if (key == sf::Keyboard::T)
		mTeleportation = isPressed;
	if (key == sf::Keyboard::R) 
		{
			std::cout << "reset" << std::endl;
			mResetGame=true;
		}
}


void Game::update(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX])
{
	sf::Vector2f movement(0.f, 0.f);
	int rotateangle=0;
	int motionValue=0;

	
	for (int x=0; x<ENTITIES_MAX; x++)
	{
		if (entities[x]->isCurrentEntity)  
			{
				currentEntityIndex = x;
			}
	}

	for (int x=0; x<4; x++)
	{
		entities[x]->canMoveRight = true;
		entities[x]->canMoveLeft = true;
		entities[x]->canMoveUp = true;
		entities[x]->canMoveDown = true;
	}

	if (mIsSpaceBar && currentEntityIndex == 0) //Space only works, if TheBaker is selected.
	{
		//std::cout << "SpaceBar check/currSelect: " << currentlySelected << std::endl;
		if (currentlySelected%3 == 1 && !entities[1]->isCreated)
		{
			entities[1]->create();
			entities[1]->cCircle.setPosition(entities[0]->cCircle.getPosition().x, entities[0]->cCircle.getPosition().y);
			shotChooser = 1;
		}

		else if (currentlySelected%3 == 2 && !entities[2]->isCreated)
		{
			entities[2]->create();
			entities[2]->cCircle.setPosition(entities[0]->cCircle.getPosition());
			shotChooser = 2;
		}
		
		else if (currentlySelected%3 == 0 && !entities[3]->isCreated)
		{
			entities[3]->create();
			entities[3]->cCircle.setPosition(entities[0]->cCircle.getPosition());
			shotChooser = 3;
		}
	}


	if (mIsSpaceBar)
	{
		//entities[currentEntityIndex]->cCircle.setPosition(entities[currentEntityIndex]->cCircle.getPosition().x,0);
		NULL;
	}
	if (mIsMovingUp)
	{	
		//bool canMoveUp = true;
		for (int x=0; x<ENTITIES_MAX; x++)
		{
			if (currentEntityIndex == x || entities[x]->isCircle) continue;
			if (
				((entities[currentEntityIndex]->eBounds.x+entities[currentEntityIndex]->eTextureSize.x >= entities[x]->eBounds.x+8) &&
				 (entities[currentEntityIndex]->eBounds.x <= entities[x]->eBounds.x+entities[x]->eTextureSize.x-8)) &&
				((entities[currentEntityIndex]->eBounds.y <= entities[x]->eBounds.y+entities[x]->eTextureSize.y) &&
				 (entities[currentEntityIndex]->eBounds.y >= entities[x]->eBounds.y))
				) entities[currentEntityIndex]->canMoveUp = true;//false;

		}
		if ( !entities[currentEntityIndex]->canMoveUp || entities[currentEntityIndex]->cCircle.getPosition().y >=0 ) NULL; //top of screen
		else 
		{
			movement.y -= PlayerSpeed;
			rotateangle = PlayerSpeed;
		}
	}	
		
	if (mIsMovingDown)
	{
		//bool canMoveDown = true;
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
					entities[currentEntityIndex]->canMoveDown = false;
				}
		}
		

		if  ( !entities[currentEntityIndex]->canMoveDown  || (entities[currentEntityIndex]->cCircle.getPosition().y >= 785-entities[currentEntityIndex]->cRadius))  NULL;  //bottom of screen
		else
		{
			movement.y += PlayerSpeed;
			rotateangle = -PlayerSpeed;
		}
	}	
		


	if (mIsMovingLeft && !positionLock)
	{
		//bool canMoveLeft = true;
		for (int x=0; x<ENTITIES_MAX; x++)
		{
			if (currentEntityIndex == x || entities[x]->isCircle) continue;
			if (
				((entities[currentEntityIndex]->eBounds.x <= entities[x]->eBounds.x+entities[x]->eTextureSize.x) &&
				 (entities[currentEntityIndex]->eBounds.x >= entities[x]->eBounds.x)) && 
				((entities[currentEntityIndex]->eBounds.y+entities[currentEntityIndex]->eTextureSize.y >= entities[x]->eBounds.y+8) && //+8 is give/take value
				 (entities[currentEntityIndex]->eBounds.y <= entities[x]->eBounds.y+entities[x]->eTextureSize.y-8))
				) entities[currentEntityIndex]->canMoveLeft = false;
		}	
		if ( !entities[currentEntityIndex]->canMoveLeft || (entities[currentEntityIndex]->cCircle.getPosition().x <= 0+entities[currentEntityIndex]->cRadius)) NULL;

		else 
		{
			movement.x -= PlayerSpeed;
			rotateangle = -PlayerSpeed;
		}
		


	}
	

	if (mIsMovingRight && !positionLock)
	{	
		//bool canMoveRight = true;
		for (int x=0; x<ENTITIES_MAX; x++)
		{
			if (currentEntityIndex == x || entities[x]->isCircle) continue;

			if (
				((entities[currentEntityIndex]->eBounds.x + entities[currentEntityIndex]->eTextureSize.x >= entities[x]->eBounds.x) &&
				 (entities[currentEntityIndex]->eBounds.x + entities[currentEntityIndex]->eTextureSize.x <= entities[x]->eBounds.x+entities[x]->eTextureSize.x)) &&
				((entities[currentEntityIndex]->eBounds.y + entities[currentEntityIndex]->eTextureSize.y >= entities[x]->eBounds.y+8) &&
				 (entities[currentEntityIndex]->eBounds.y <= entities[x]->eBounds.y+entities[x]->eTextureSize.y-8))
				) entities[currentEntityIndex]->canMoveRight = false;

		}
		if (!entities[currentEntityIndex]->canMoveRight || (entities[currentEntityIndex]->cCircle.getPosition().x >= 1200-entities[currentEntityIndex]->cRadius)) NULL;
		else 
		{
			movement.x += PlayerSpeed;
			rotateangle = PlayerSpeed;
		}
	}	

	if (mTeleportation)
	{
		entities[currentEntityIndex]->cCircle.setPosition(0,785-entities[currentEntityIndex]->cRadius);
	}
	
	
	entities[currentEntityIndex]->cCircle.move(movement * elapsedTime.asSeconds());
	entities[currentEntityIndex]->cCircle.rotate(rotateangle*elapsedTime.asSeconds());
	
	
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
	
	if (currentlySelected%3 == 1) 
	{
		entities[1]->cCircle.setOutlineThickness(5);
		entities[1]->cCircle.setOutlineColor(sf::Color(60, 129, 113));
		mWindow.draw(entities[1]->eSprite2);
		entities[2]->cCircle.setOutlineThickness(0);
		entities[3]->cCircle.setOutlineThickness(0);
	}
	else if (currentlySelected%3 == 2) 
	{
		entities[2]->cCircle.setOutlineThickness(5);
		entities[2]->cCircle.setOutlineColor(sf::Color(60, 129, 113));
		mWindow.draw(entities[2]->eSprite2);
		entities[1]->cCircle.setOutlineThickness(0);
		entities[3]->cCircle.setOutlineThickness(0);

	}
	else
	{
		entities[3]->cCircle.setOutlineThickness(5);
		entities[3]->cCircle.setOutlineColor(sf::Color(60, 129, 113));
		mWindow.draw(entities[3]->eSprite2);
		entities[1]->cCircle.setOutlineThickness(0);
		entities[2]->cCircle.setOutlineThickness(0);

	}
	
	for (int x=0; x<ENTITIES_MAX; x++) 
	{
		if (entities[x]->isCircle) mWindow.draw(entities[x]->cCircle);
		else mWindow.draw(entities[x]->eSprite);
	}
	mPowerGaugeMetre.setTextureRect(sf::IntRect(0,0,mPowerGaugeMetreTexture.getSize().x,powerMetre));
	if (mDrawMetre)
	{
		mWindow.draw(mPowerGaugeShell);
		mWindow.draw(mPowerGaugeMetre);
	}
	mWindow.draw(mArrow);
	mWindow.display();
}
