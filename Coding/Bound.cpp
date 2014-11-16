#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "StringHelpers.hpp"
#include "Entity.cpp"
#include "Stage.cpp"

#ifndef BOUND_H
#define BOUND_H

#define PI 3.14159265
#define ENTITIES_MAX 4
#define STAGES_MAX 2
#define G_MAX 160.0

class Game
{
	public:
	
		Game();
		
		//functions
		void run(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void checkGravity(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int character);
		void checkBounds(Entity* entities[ENTITIES_MAX]);
		bool isTouchingSurface(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		void swapStage(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void resetLevel(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);

		void breadSelector(sf::Keyboard::Key key, int selectedEntity); 
		void powerMetreUpdate(sf::Keyboard::Key key);	
		void entitySelector(Entity* entities[ENTITIES_MAX]);
		void Arrow(Entity* entities[ENTITIES_MAX]);
		void trajectory(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX]); 
		int checkHitting(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int airborneEntity, bool isSwitch);
		
		void activateRotiPowerAlpha(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void activateRotiPowerBeta(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void activateAnpanPower(Entity* entities[ENTITIES_MAX],Stage* stages[STAGES_MAX]);


		void processEvents(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		
		void motionCheck(int character, Entity* entities[ENTITIES_MAX],Stage* stages[STAGES_MAX]);
		void update(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void render(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);

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

		bool mPlatformSwitch;


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


	
		float powerMetre;

		//Gravity
		const float g; //gravity constant initalized in constructor
		const float timePerGravityUpdate;  //amount of time before acceleration update
		float gCurrent; //curent gravity
		sf::Clock gravityClock; //measure time
	
	
		int currentEntityIndex;
		int currentlySelected; 
		int shotChooser;

		bool mouseLock;
		bool rotiActivated;
		
		bool repulsionReadyA; //Baker pushed Leftwards
		bool repulsionReadyB; //Baker pushed Rightwards
		bool repulsionReadyC; //Baker pushed Downwards

		bool positionLock;

		bool mResetGame;

		bool mDrawMetre;
		bool mDrawNull;


		sf::Texture mNullSignTexture;
		sf::Sprite mNullSign;

		//stores position of baker so we can manipulate  positionLock.
		sf::Vector2f traj_pos;

		sf::Clock nullSignTime;


		bool negateGravity;

		bool isBeingAttracted;

		int currentStage;


};


const float Game::PlayerSpeed = 150.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


//instantiates most objects and sets starting values
Game::Game() : 
			   mIsMovingUp(false), mIsMovingDown(false), mIsMovingRight(false),
			   mIsMovingLeft(false), mIsSpaceBar(false), mTeleportation(false), mStatisticsText(), mStatisticsUpdateTime(), rotiActivated(false), 
			   mFont(), mArrowTexture(), mPowerGaugeShell(), mPowerGaugeShellTexture() , mArrow(), g(0.6), 
			   timePerGravityUpdate(0.0002), mPowerGaugeMetreTexture(), mPowerGaugeMetre(),  timePerShot(1), shotChooser(1), mNullSignTexture(), mNullSign(), nullSignTime()

{
	mWindow.create(sf::VideoMode(1200, 800), "CircleGame!");

	//set all statistics
	mStatisticsNumFrames = 0;
	mFont.loadFromFile("Sansation.ttf");
	mStatisticsText.setFont(mFont);

	mStatisticsText.setCharacterSize(20);
	mStatisticsText.setColor(sf::Color::White);
	
	//set arrow stuff
	mArrowTexture.loadFromFile("../Character_Images/Arrowhead.png");
	mArrow.setTexture(mArrowTexture);
	mArrow.setPosition(490+45,600-55);
	mArrow.setOrigin(45,55);

	//set powergauge stuff
	mPowerGaugeMetreTexture.loadFromFile("../Character_Images/PowerGauge_Metre.png");
	mPowerGaugeShellTexture.loadFromFile("../Character_Images/PowerGauge_Shell.png");
	mPowerGaugeMetre.setTexture(mPowerGaugeMetreTexture);
	mPowerGaugeShell.setTexture(mPowerGaugeShellTexture);

	mNullSignTexture.loadFromFile("../Stage_Images/Universal_StageParts/Stage_NullSign.png");
	mNullSign.setTexture(mNullSignTexture);

	//current entity index is the bread which is clicked
	currentEntityIndex = 0;

	//currently selected is which bread is going to be fired
	currentlySelected = 1;

	gCurrent = g;


	//this determins wether we call trajectory or not.
	mIsLaunched = false;

	//power bar multiplier for trajectory
	powerMetre = 3;

	//Locks mouse and position when trajectory is active so that we don't get curved bread.
	mouseLock=false;
	positionLock = false;

	//checks to see if we pressed "r"
	mResetGame = false;

	//Only draws meter when we hit space
	mDrawMetre = false;

	mDrawNull = false;

	negateGravity = false;

	isBeingAttracted = false;

	mPlatformSwitch = false;

	currentStage = 0;
}




//main game loop. Runs all functions, processes events, updates game, updates statistics and renders
//read 
void Game::run(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		
		//get the current amount of time elapsed
		
		//processEvents(elapsedTime, entities);
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			//std::cout << entities[2]->cCircle.getPosition().x << ", " << entities[2]->cCircle.getPosition().y << std::endl;
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
				entities[x]->eBounds.x = entities[x]->cCircle.getPosition().x - entities[x]->cRadius;
				entities[x]->eBounds.y = entities[x]->cCircle.getPosition().y - entities[x]->cRadius;

				entities[x]->topCircle[0] = entities[x]->cCircle.getPosition().x + (entities[x]->cRadius*cos(3*PI/2));
				entities[x]->topCircle[1] = entities[x]->cCircle.getPosition().y + (entities[x]->cRadius*sin(3*PI/2));

				entities[x]->rightCircle[0] = entities[x]->cCircle.getPosition().x + (entities[x]->cRadius*cos(2*PI));
				entities[x]->rightCircle[1] = entities[x]->cCircle.getPosition().y + (entities[x]->cRadius*sin(2*PI));

				entities[x]->bottomCircle[0] = entities[x]->cCircle.getPosition().x + (entities[x]->cRadius*cos(PI/2));
				entities[x]->bottomCircle[1] = entities[x]->cCircle.getPosition().y + (entities[x]->cRadius*sin(PI/2));

				entities[x]->leftCircle[0] = entities[x]->cCircle.getPosition().x + (entities[x]->cRadius*cos(PI));
				entities[x]->leftCircle[1] = entities[x]->cCircle.getPosition().y + (entities[x]->cRadius*sin(PI));
			}
		if (mResetGame) resetLevel(entities,stages);

			for (int x=0; x < stages[currentStage]->platformCount; x++)
			{
				stages[currentStage]->platforms[x]->eBounds.x = stages[currentStage]->platforms[x]->eSprite.getPosition().x - stages[currentStage]->platforms[x]->eTextureSize.x/2;
				stages[currentStage]->platforms[x]->eBounds.y = stages[currentStage]->platforms[x]->eSprite.getPosition().y - stages[currentStage]->platforms[x]->eTextureSize.y/2;
			}

			for (int x = 0; x<ENTITIES_MAX; x++) 
			{ 
				if (!negateGravity) checkGravity(entities, stages, x); 

			} //D: Loops per character. Separating gravity effects for each

			swapStage(entities,stages);
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
						if (entities[x]->gCurrent < G_MAX && !negateGravity) entities[x]->gCurrent+=g;
						else if (negateGravity && ( x == 0 || x == 1)) continue; 
						else entities[x]->gCurrent = G_MAX;
					}
					updateGravity = gravityClock.restart();
				}
	//-----------------
				//std::cout << "PM : " << powerMetre << std::endl;
			
				//activateRotiPowerBeta(elapsedTime, entities);

	//--------------TRAJECTORY PARAMETERS
				if ( (mIsLaunched)) 
				{
					positionLock = true;
					mouseLock=true;

					trajectory(elapsedTime, entities);
				
				//Right Border Collision Check	
					if (entities[shotChooser]->cCircle.getPosition().x >= 1200 - entities[shotChooser]->cRadius)
					{
						std::cout << "rb stopped trag" << std::endl;
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->cCircle.setPosition(1200-entities[shotChooser]->cRadius, entities[shotChooser]->cCircle.getPosition().y);
				
						entities[shotChooser]->isCreated = true;
						entities[shotChooser]->gCurrent = 0;	
					}
					
				//Left Border Collision Check	
					if (entities[shotChooser]->cCircle.getPosition().x <= 0 + entities[shotChooser]->cRadius)
					{
						std::cout << "lb stopped trag" << std::endl;
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->cCircle.setPosition(0+entities[shotChooser]->cRadius, entities[shotChooser]->cCircle.getPosition().y);
					
						entities[shotChooser]->gCurrent = 0;	
						entities[shotChooser]->isCreated = true;
					}

				//Top Border Collision Check
					if (entities[shotChooser]->cCircle.getPosition().y <= 0+entities[shotChooser]->cRadius)
					{
						std::cout << "tb stopped trag" << std::endl;
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->cCircle.setPosition(entities[shotChooser]->cCircle.getPosition().x,0+entities[shotChooser]->cRadius);
					
						entities[shotChooser]->gCurrent = 0;	
						entities[shotChooser]->isCreated = true;
					}

				//Bottom Border Collision Check
					std::cout << "ebounds.y (" << shotChooser << "): " << entities[shotChooser]->eBounds.y+entities[shotChooser]->eTextureSize.y << std::endl;
					if (entities[shotChooser]->eBounds.y+entities[shotChooser]->eTextureSize.y >= 785)
					{
						std::cout << "bb stopped trag" << std::endl;
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->cCircle.setPosition(entities[shotChooser]->cCircle.getPosition().x,785-entities[shotChooser]->cRadius);
					
						entities[shotChooser]->isCreated = true;
						entities[shotChooser]->gCurrent = 0;	
					}

					if (isTouchingSurface(entities, stages, shotChooser))
					{
						std::cout << "touching da surf stopped trajectory" << std::endl;
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->isCreated = true;
					}
					
					
					else if (checkHitting(entities,stages,shotChooser,false))
					{
						std::cout << "check hitting stopped trajectory" << std::endl;
						mIsLaunched = false;
						mDrawMetre = false;
						entities[shotChooser]->gCurrent = 0;	
						entities[shotChooser]->isCreated = true;
					}
					
				
					//CHANGED TO TEST FOR ALL STAGE PARTS AT ALL TIMES. LESS EFFICIEINT.	
							
				}


				else 
				{
					mouseLock=false;
					positionLock=false;
				}

			processEvents(elapsedTime, entities, stages);
			update(TimePerFrame,entities,stages);

		}

		updateStatistics(elapsedTime);
		render(entities,stages);
	}
	//if (mResetGame) return 1;
	//return 0;
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

	int rooX = entities[currentEntityIndex]->cCircle.getPosition().x + (entities[currentEntityIndex]->cRadius*cos(PI));
	int rooY = entities[currentEntityIndex]->cCircle.getPosition().y + (entities[currentEntityIndex]->cRadius*sin(PI));
	//std::cout << "(" << rooX << "," << rooY << ")" << std::endl;
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

void Game::swapStage(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{
	for (int x=0; x< stages[currentStage]->lineCount; x++)
		{
			
			if (stages[currentStage]->lines[x]->nextStage == true)
			{
				if (				
					(((entities[0]->eBounds.x <= stages[currentStage]->lines[x]->eBounds.x+stages[currentStage]->lines[x]->eTextureSize.x) &&
					 (entities[0]->eBounds.x >= stages[currentStage]->lines[x]->eBounds.x)) && 
					((entities[0]->eBounds.y+entities[0]->eTextureSize.y >= stages[currentStage]->lines[x]->eBounds.y) && //+8 is give/take value
					 (entities[0]->eBounds.y <= stages[currentStage]->lines[x]->eBounds.y+stages[currentStage]->lines[x]->eTextureSize.y)))
					)
				{
					currentStage += 1;
					return;
				}			

			
				else if	(
					((entities[0]->eBounds.x + entities[0]->eTextureSize.x >= stages[currentStage]->lines[x]->eBounds.x) &&
					 (entities[0]->eBounds.x + entities[0]->eTextureSize.x <= stages[currentStage]->lines[x]->eBounds.x+stages[currentStage]->lines[x]->eTextureSize.x)) &&
					((entities[0]->eBounds.y + entities[0]->eTextureSize.y >= stages[currentStage]->lines[x]->eBounds.y+8) &&
					 (entities[0]->eBounds.y <= stages[currentStage]->lines[x]->eBounds.y+stages[currentStage]->lines[x]->eTextureSize.y-8))
					)	   
				{
					currentStage += 1;
					return;
				}
			}
			
		}
}

void Game::resetLevel(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{
	entities[0]->cCircle.setPosition(entities[0]->eStartPos);

	for (int x=1; x<ENTITIES_MAX; x++)
	{
		entities[x]->cCircle.setPosition(entities[x]->eStartPos);
		entities[x]->isCreated = false;
	}

	for (int x=0; x<stages[currentStage]->platformCount; x++)
	{
		stages[currentStage]->platforms[x]->eSprite.setPosition(stages[currentStage]->platforms[x]->eStartPos);
		stages[currentStage]->platforms[x]->activatePlatform = false;
	}
	for (int x=0; x<stages[currentStage]->switchCount; x++)
	{
		stages[currentStage]->switches[x]->eSprite.setTexture(stages[currentStage]->switches[x]->eTexture);
	}
	for (int x=1; x<ENTITIES_MAX; x++)
	{
		entities[x]->isCurrentEntity = false;
	}
	currentEntityIndex = 0;
	powerMetre = 3;
	entities[0]->isCurrentEntity = true;
	mResetGame = false;

}


void Game::activateRotiPowerAlpha(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && currentEntityIndex == 1)
	{
		sf::Vector2f attract_direction(150.0,0.f);
		int rotateangle = 150;


		motionCheck(0,entities,stages);
		
		//If Roti is Right of Baker (Greater)
		if (entities[1]->cCircle.getPosition().x > entities[0]->cCircle.getPosition().x)
		{
			if (!entities[0]->canMoveRight)
			{
				attract_direction.x = 0;
				rotateangle = 0;
			}
		}

		else
		{
			attract_direction.x = -attract_direction.x;
			rotateangle = -rotateangle;
			if (!entities[0]->canMoveLeft)
			{
				attract_direction.x = 0;
				rotateangle = 0;
			}
		}
		int bakerHitting = checkHitting(entities,stages,0,false);
		int rotiHitting = checkHitting(entities,stages,1,false);
		if (bakerHitting > 1 && rotiHitting > 1 && bakerHitting!=rotiHitting) //checks if both touching a surface, now we need to check if touching opposite sides && saftey check for length of surface.
		{
			negateGravity = true;
			entities[0]->canMoveDown = true;
			entities[1]->canMoveDown = true;
			if (entities[1]->cCircle.getPosition().y <= entities[0]->cCircle.getPosition().y)
			{
				//motionCheck(0, entities);
				isBeingAttracted = true;
				attract_direction.y = -150.f;
				//entities[0]->gCurrent = 0;
			}
			else attract_direction.y = 150.f;

		}
		else 
		{
			negateGravity = false;
			isBeingAttracted = false;
		}
	


		entities[0]->cCircle.move(attract_direction * elapsedTime.asSeconds());
		entities[0]->cCircle.rotate(rotateangle*elapsedTime.asSeconds());

	}


}

void Game::activateRotiPowerBeta(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{

	if (isBeingAttracted)
	{
		negateGravity = false;
		int bakerHitting = checkHitting(entities,stages,0,false);
		int rotiHitting = checkHitting(entities,stages,1,false);
		std::cout << "baker: " << bakerHitting << ", " << "roti: " << rotiHitting << std::endl;

		//const float pushValue = 1000.f;

		sf::Vector2f bakerRepulsion(5000.f,0.f);
		sf::Vector2f rotiRepulsion(1000.f,0.f);
		sf::Time applyRepulsion = shotClock.getElapsedTime();

		if (bakerHitting == 2 && rotiHitting == 3)
		{
			bakerRepulsion = -bakerRepulsion;
		}

		if (rotiHitting == 2 && bakerHitting == 3)
		{
			rotiRepulsion = -rotiRepulsion;
		}
		
		entities[1]->cCircle.move( rotiRepulsion * elapsedTime.asSeconds());
		entities[0]->cCircle.move( bakerRepulsion * elapsedTime.asSeconds());
	}
	isBeingAttracted = false;	
	
} 	

void Game::activateAnpanPower(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && currentEntityIndex == 2)
	{	
		//std::cout << "activating SWAP" << std::endl;	
		sf::Vector2f temp_pos = entities[0]->cCircle.getPosition();
		entities[0]->cCircle.setPosition(entities[currentEntityIndex]->cCircle.getPosition().x,entities[currentEntityIndex]->cCircle.getPosition().y-42 );
		entities[0]->eBounds.x = entities[0]->cCircle.getPosition().x - entities[0]->cRadius;
		entities[0]->eBounds.y = entities[0]->cCircle.getPosition().y - entities[0]->cRadius;
		motionCheck(0,entities,stages);
		if (!entities[0]->canMoveRight || !entities[0]->canMoveLeft)
		{
			//std::cout << "could not swap " << std::endl;
			entities[0]->cCircle.setPosition(temp_pos);
			mDrawNull = true;
		}
		else 
		{
			entities[currentEntityIndex]->cCircle.setPosition(temp_pos);
			entities[currentEntityIndex]->isCurrentEntity = false;
			currentEntityIndex = 0;
			entities[0]->isCurrentEntity = true;
		}
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
			else powerMetre = 3;
		}
	else 
		{
			//std::cout << "Setting drawmtre false" << std::endl;
			mDrawMetre=false;
			//if (!mIsLaunched) powerMetre=0;
		}
}

//stage id is index of entities which you need to apply the gravity check on
/*
bool Game::isTouchingSurface(Entity* entities[ENTITIES_MAX], int stage_id, int x)
{
	
	if (entities[x]->isCircle)
	{		
		if (
			((entities[x]->eBounds.x+entities[x]->eTextureSize.x >= entities[stage_id]->eBounds.x) &&
			 (entities[x]->eBounds.x <= entities[stage_id]->eBounds.x+entities[stage_id]->eTextureSize.x)) &&
			((entities[x]->eBounds.y+entities[x]->eTextureSize.y >= entities[stage_id]->eBounds.y) &&
			 entities[x]->eBounds.y+entities[x]->eTextureSize.y <= entities[stage_id]->eBounds.y+10)
			)
			{
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , entities[stage_id]->eBounds.y-entities[x]->cRadius);	
				//std::cout << "touchin da surf" << std::endl;
				return true;	
			}		
	}
	
	return false;
}
*/

bool Game::isTouchingSurface(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x)
{
	/*	
	for (int a=0; a<stages[currentStage]->lineCount ; a++)
	{
		if  (				
				((entities[x]->eBounds.x+entities[x]->eTextureSize.x >= stages[currentStage]->lines[a]->eBounds.x) && //right side circle >=  left side stage
				(entities[x]->eBounds.x <= stages[currentStage]->lines[a]->eBounds.x+stages[currentStage]->lines[a]->eTextureSize.x)) && //left side circle <= right side stage
				((entities[x]->eBounds.y+entities[x]->eTextureSize.y >= stages[currentStage]->lines[a]->eBounds.y) && //bottom of circle >= top of stage
				(entities[x]->eBounds.y+entities[x]->eTextureSize.y <= stages[currentStage]->lines[a]->eBounds.y+stages[currentStage]->lines[a]->eTextureSize.y)) //bottom of circle < bottom of stage
			)
			{
				//std::cout << "touch da surf" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-entities[x]->cRadius);
				return true;	
			}

	}
	*/

/*
	for (int a=0; a<stages[currentStage]->lineCount; a++)
	{
		if (
			entities[x]->bottomCircle >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->bottomCircle <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->rightCircle >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->leftCircle <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x
			)
		{

			if (entities[x]->bottomCircle >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->bottomCircle <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y)
			{
				std::cout << "touch da surf" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-entities[x]->cRadius);
				return true;
			}
			
			else
			{
				NULL;
			}
			
		}

	}
*/
	for (int a=0; a<stages[currentStage]->lineCount; a++)
	{
		if (entities[x]->rightCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->rightCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->rightCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->rightCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(stages[currentStage]->lines[a]->eBounds.x-entities[x]->cRadius, entities[x]->cCircle.getPosition().y);
				return false;
			}

		else if (entities[x]->leftCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->leftCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->leftCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->leftCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(stages[currentStage]->lines[a]->eBounds.x+stages[currentStage]->lines[a]->eTextureSize.x+entities[x]->cRadius, entities[x]->cCircle.getPosition().y);
				return false;
			}

		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->bottomCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->bottomCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-entities[x]->cRadius);
				return true;
			}
	}

	/*
	for (int b=0; b<stages[currentStage]->platformCount ; b++)
	{
		if (
			((entities[x]->eBounds.x+entities[x]->eTextureSize.x >= stages[currentStage]->platforms[b]->eBounds.x) &&
			 (entities[x]->eBounds.x <= stages[currentStage]->platforms[b]->eBounds.x+stages[currentStage]->platforms[b]->eTextureSize.x)) &&
			((entities[x]->eBounds.y+entities[x]->eTextureSize.y >= stages[currentStage]->platforms[b]->eBounds.y) &&
			 entities[x]->eBounds.y+entities[x]->eTextureSize.y <= stages[currentStage]->platforms[b]->eBounds.y)
			)
			{
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[b]->eBounds.y-entities[x]->cRadius);
				return true;	
			}					
	}
	*/
	/*
	for (int c=0; c<stages[currentStage]->boxCount ; c++)
	{
		if (
			((entities[x]->eBounds.x+entities[x]->eTextureSize.x >= stages[currentStage]->boxes[c]->eBounds.x) &&
			 (entities[x]->eBounds.x <= stages[currentStage]->boxes[c]->eBounds.x+stages[currentStage]->boxes[c]->eTextureSize.x)) &&
			((entities[x]->eBounds.y+entities[x]->eTextureSize.y >= stages[currentStage]->boxes[c]->eBounds.y) &&
			 entities[x]->eBounds.y+entities[x]->eTextureSize.y <= stages[currentStage]->boxes[c]->eBounds.y+10)
			)
			{
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->boxes[c]->eBounds.y-entities[x]->cRadius);
				return true;	
			}	
	}
	*/
	return false;
	
}
//stages[currentStage]->lines[x]->


void Game::checkBounds(Entity* entities[ENTITIES_MAX])
{
	for (int x=0; x<ENTITIES_MAX; x++)
	{
		if (entities[x]->isCircle)
		{
			//floor
			if (entities[x]->eBounds.y+entities[x]->eTextureSize.y >= 785) entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x,785-entities[x]->cRadius);
		}
	}
}


void Game::checkGravity(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int character)
{
	bool isOnGround = true;
	
	//need this to reset gravity if touching a surface
	if ( (entities[character]->cCircle.getPosition().y >=  785-entities[character]->cRadius) )  NULL;
	else if (isTouchingSurface(entities, stages, character)) NULL;
	else 
	{
		isOnGround = false;
		entities[character]->cCircle.move(0,entities[character]->gCurrent+entities[character]->weight);
	}


	if (isOnGround) entities[character]->gCurrent = g;
	checkBounds(entities);
}




//left side return = 2;
//right side return = 3;
//ambiguous return = 1;
//not touching return = 0;
int Game::checkHitting(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int airborneEntity, bool isSwitch)
{
	if (isSwitch)
	{
		for (int x=0; x<stages[currentStage]->switchCount; x++)
		{
			if (
			(((entities[airborneEntity]->eBounds.x <= stages[currentStage]->switches[x]->eBounds.x+stages[currentStage]->switches[x]->eTextureSize.x) &&
			 (entities[airborneEntity]->eBounds.x >= stages[currentStage]->switches[x]->eBounds.x)) && 
			((entities[airborneEntity]->eBounds.y+entities[airborneEntity]->eTextureSize.y >= stages[currentStage]->switches[x]->eBounds.y) && //+8 is give/take value
			 (entities[airborneEntity]->eBounds.y <= stages[currentStage]->switches[x]->eBounds.y+stages[currentStage]->switches[x]->eTextureSize.y)))
			)
			{
				return x; //returns which switch it is touching
			}

			else if	(
			((entities[airborneEntity]->eBounds.x + entities[airborneEntity]->eTextureSize.x >= stages[currentStage]->switches[x]->eBounds.x) &&
			 (entities[airborneEntity]->eBounds.x + entities[airborneEntity]->eTextureSize.x <= stages[currentStage]->switches[x]->eBounds.x+stages[currentStage]->switches[x]->eTextureSize.x)) &&
			((entities[airborneEntity]->eBounds.y + entities[airborneEntity]->eTextureSize.y >= stages[currentStage]->switches[x]->eBounds.y+8) &&
			 (entities[airborneEntity]->eBounds.y <= stages[currentStage]->switches[x]->eBounds.y+stages[currentStage]->switches[x]->eTextureSize.y-8))
			)	   
			{
				return x; //returns which switch it is touching
			}

		}
		return -1;
	}
	for (int x=0; x< stages[currentStage]->lineCount; x++)
	{
		if (				
			(((entities[airborneEntity]->eBounds.x <= stages[currentStage]->lines[x]->eBounds.x+stages[currentStage]->lines[x]->eTextureSize.x) &&
			 (entities[airborneEntity]->eBounds.x >= stages[currentStage]->lines[x]->eBounds.x)) && 
			((entities[airborneEntity]->eBounds.y+entities[airborneEntity]->eTextureSize.y >= stages[currentStage]->lines[x]->eBounds.y) && //+8 is give/take value
			 (entities[airborneEntity]->eBounds.y <= stages[currentStage]->lines[x]->eBounds.y+stages[currentStage]->lines[x]->eTextureSize.y)))
			)
		{
			std::cout << "rs" <<std::endl;
			return 3;
		}			

		if	(
			((entities[airborneEntity]->eBounds.x + entities[airborneEntity]->eTextureSize.x >= stages[currentStage]->lines[x]->eBounds.x) &&
			 (entities[airborneEntity]->eBounds.x + entities[airborneEntity]->eTextureSize.x <= stages[currentStage]->lines[x]->eBounds.x+stages[currentStage]->lines[x]->eTextureSize.x)) &&
			((entities[airborneEntity]->eBounds.y + entities[airborneEntity]->eTextureSize.y >= stages[currentStage]->lines[x]->eBounds.y) &&
			 (entities[airborneEntity]->eBounds.y <= stages[currentStage]->lines[x]->eBounds.y+stages[currentStage]->lines[x]->eTextureSize.y))
			)	   
		{
			std::cout << "ls" << std::endl;
			return 2;
		}
	}

	for (int x=0; x< stages[currentStage]->platformCount; x++)
	{
		if (				
			(((entities[airborneEntity]->eBounds.x <= stages[currentStage]->platforms[x]->eBounds.x+stages[currentStage]->platforms[x]->eTextureSize.x) &&
			 (entities[airborneEntity]->eBounds.x >= stages[currentStage]->platforms[x]->eBounds.x)) && 
			((entities[airborneEntity]->eBounds.y+entities[airborneEntity]->eTextureSize.y >= stages[currentStage]->platforms[x]->eBounds.y) && //+8 is give/take value
			 (entities[airborneEntity]->eBounds.y <= stages[currentStage]->platforms[x]->eBounds.y+stages[currentStage]->platforms[x]->eTextureSize.y)))
			)
		{
			return 3;
		}			

		if	(
			((entities[airborneEntity]->eBounds.x + entities[airborneEntity]->eTextureSize.x >= stages[currentStage]->platforms[x]->eBounds.x) &&
			 (entities[airborneEntity]->eBounds.x + entities[airborneEntity]->eTextureSize.x <= stages[currentStage]->platforms[x]->eBounds.x+stages[currentStage]->lines[x]->eTextureSize.x)) &&
			((entities[airborneEntity]->eBounds.y + entities[airborneEntity]->eTextureSize.y >= stages[currentStage]->platforms[x]->eBounds.y) &&
			 (entities[airborneEntity]->eBounds.y <= stages[currentStage]->platforms[x]->eBounds.y+stages[currentStage]->platforms[x]->eTextureSize.y))
			)	   
		{
			return 2;
		}
	}

	return 0;
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



void Game::processEvents(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{
	entitySelector(entities);
	sf::Event event;
	activateRotiPowerAlpha(elapsedTime, entities,stages);
	
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed:
				handlePlayerInput(event.key.code, true);
				breadSelector(event.key.code, 0);
				powerMetreUpdate(event.key.code); 
				if (event.key.code == sf::Keyboard::R) 
					{
						std::cout << "reset" << std::endl;
						mResetGame=true;
					}
				break;

			case sf::Event::KeyReleased:
				
                switch(event.key.code)
                {		
	                case sf::Keyboard::Space:
						mIsLaunched = true;
						break;
						//powerMetre=0;

				}
				handlePlayerInput(event.key.code, false);
				break;

			case sf::Event::MouseMoved:
				break;


			case sf::Event::MouseButtonPressed:
				activateAnpanPower(entities,stages);
				break;

			case sf::Event::MouseButtonReleased:
    				if (event.mouseButton.button == sf::Mouse::Right) activateRotiPowerBeta(elapsedTime,entities,stages);
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
	if (key == sf::Keyboard::L)
		{
			currentStage = 1;
		}
}

void Game::motionCheck( int character, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{
	for (int x=0; x < stages[currentStage]->lineCount; x++)
	{

	//canMoveUp Check
		if (
			((entities[character]->eBounds.x+entities[character]->eTextureSize.x >= stages[currentStage]->lines[x]->eBounds.x+8) &&
			 (entities[character]->eBounds.x <= stages[currentStage]->lines[x]->eBounds.x+stages[currentStage]->lines[x]->eTextureSize.x-8)) &&
			((entities[character]->eBounds.y <= stages[currentStage]->lines[x]->eBounds.y+stages[currentStage]->lines[x]->eTextureSize.y) &&
			 (entities[character]->eBounds.y >= stages[currentStage]->lines[x]->eBounds.y))
		) entities[character]->canMoveUp = false;
		

	//canMoveLeft Check
			if (
				((entities[character]->eBounds.x <= stages[currentStage]->lines[x]->eBounds.x+stages[currentStage]->lines[x]->eTextureSize.x) &&
				 (entities[character]->eBounds.x >= stages[currentStage]->lines[x]->eBounds.x)) && 
				((entities[character]->eBounds.y+entities[character]->eTextureSize.y >= stages[currentStage]->lines[x]->eBounds.y+8) && //+8 is give/take value
				 (entities[character]->eBounds.y <= stages[currentStage]->lines[x]->eBounds.y+stages[currentStage]->lines[x]->eTextureSize.y-8))
				) entities[character]->canMoveLeft = false;
			


	//canMoveRight Check
			if (
				((entities[character]->eBounds.x + entities[character]->eTextureSize.x >= stages[currentStage]->lines[x]->eBounds.x) &&
				 (entities[character]->eBounds.x + entities[character]->eTextureSize.x <= stages[currentStage]->lines[x]->eBounds.x+stages[currentStage]->lines[x]->eTextureSize.x)) &&
				((entities[character]->eBounds.y + entities[character]->eTextureSize.y >= stages[currentStage]->lines[x]->eBounds.y+8) &&
				 (entities[character]->eBounds.y <= stages[currentStage]->lines[x]->eBounds.y+stages[currentStage]->lines[x]->eTextureSize.y-8))
				) entities[character]->canMoveRight = false;

		
	}

	for (int x=0; x < stages[currentStage]->platformCount; x++)
	{

	//canMoveUp Check
		if (
			((entities[character]->eBounds.x+entities[character]->eTextureSize.x >= stages[currentStage]->platforms[x]->eBounds.x+8) &&
			 (entities[character]->eBounds.x <= stages[currentStage]->platforms[x]->eBounds.x+stages[currentStage]->platforms[x]->eTextureSize.x-8)) &&
			((entities[character]->eBounds.y <= stages[currentStage]->platforms[x]->eBounds.y+stages[currentStage]->platforms[x]->eTextureSize.y) &&
			 (entities[character]->eBounds.y >= stages[currentStage]->platforms[x]->eBounds.y))
		) entities[character]->canMoveUp = false;
		

	//canMoveLeft Check
			if (
				((entities[character]->eBounds.x <= stages[currentStage]->platforms[x]->eBounds.x+stages[currentStage]->platforms[x]->eTextureSize.x) &&
				 (entities[character]->eBounds.x >= stages[currentStage]->platforms[x]->eBounds.x)) && 
				((entities[character]->eBounds.y+entities[character]->eTextureSize.y >= stages[currentStage]->platforms[x]->eBounds.y+8) && //+8 is give/take value
				 (entities[character]->eBounds.y <= stages[currentStage]->platforms[x]->eBounds.y+stages[currentStage]->platforms[x]->eTextureSize.y-8))
				) entities[character]->canMoveLeft = false;
			


	//canMoveRight Check
			if (
				((entities[character]->eBounds.x + entities[character]->eTextureSize.x >= stages[currentStage]->platforms[x]->eBounds.x) &&
				 (entities[character]->eBounds.x + entities[character]->eTextureSize.x <= stages[currentStage]->platforms[x]->eBounds.x+stages[currentStage]->platforms[x]->eTextureSize.x)) &&
				((entities[character]->eBounds.y + entities[character]->eTextureSize.y >= stages[currentStage]->platforms[x]->eBounds.y+8) &&
				 (entities[character]->eBounds.y <= stages[currentStage]->platforms[x]->eBounds.y+stages[currentStage]->platforms[x]->eTextureSize.y-8))
				) entities[character]->canMoveRight = false;

		
	}	

}

void Game::update(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
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

	for (int x=0; x<ENTITIES_MAX; x++)
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
		for (int x=0; x< stages[currentStage]->lineCount; x++)
		{
			if (
				((entities[currentEntityIndex]->eBounds.x + entities[currentEntityIndex]->eTextureSize.x >= stages[currentStage]->lines[x]->eBounds.x+8) &&
				 (entities[currentEntityIndex]->eBounds.x <= stages[currentStage]->lines[x]->eBounds.x+stages[currentStage]->lines[x]->eTextureSize.x-8)) &&
				((entities[currentEntityIndex]->eBounds.y <= stages[currentStage]->lines[x]->eBounds.y+stages[currentStage]->lines[x]->eTextureSize.y) &&
				 (entities[currentEntityIndex]->eBounds.y >= stages[currentStage]->lines[x]->eBounds.y))
				) 	entities[currentEntityIndex]->canMoveUp = false;

		}

		for (int x=0; x< stages[currentStage]->platformCount; x++)
		{
			if (
				((entities[currentEntityIndex]->eBounds.x + entities[currentEntityIndex]->eTextureSize.x >= stages[currentStage]->platforms[x]->eBounds.x+8) &&
				 (entities[currentEntityIndex]->eBounds.x <= stages[currentStage]->platforms[x]->eBounds.x+stages[currentStage]->platforms[x]->eTextureSize.x-8)) &&
				((entities[currentEntityIndex]->eBounds.y <= stages[currentStage]->platforms[x]->eBounds.y+stages[currentStage]->platforms[x]->eTextureSize.y) &&
				 (entities[currentEntityIndex]->eBounds.y >= stages[currentStage]->platforms[x]->eBounds.y))
				) 	entities[currentEntityIndex]->canMoveUp = false;

		}


		if ( !entities[currentEntityIndex]->canMoveUp || !negateGravity /*entities[currentEntityIndex]->cCircle.getPosition().y >=0*/ ) NULL; //top of screen
		else 
		{
			movement.y -= PlayerSpeed;
			rotateangle = -PlayerSpeed;
		}
	}	
		
	if (mIsMovingDown)
	{
		//bool canMoveDown = true;
		for (int x=0; x< stages[currentStage]->lineCount; x++)
		{
			if (
				((entities[currentEntityIndex]->eBounds.x+entities[currentEntityIndex]->eTextureSize.x >= stages[currentStage]->lines[x]->eBounds.x) &&
				 (entities[currentEntityIndex]->eBounds.x <= stages[currentStage]->lines[x]->eBounds.x+stages[currentStage]->lines[x]->eTextureSize.x)) &&
				((entities[currentEntityIndex]->eBounds.y+entities[currentEntityIndex]->eTextureSize.x >= stages[currentStage]->lines[x]->eBounds.y) &&
				 entities[currentEntityIndex]->eBounds.y+entities[currentEntityIndex]->eTextureSize.y <= stages[currentStage]->lines[x]->eBounds.y+stages[currentStage]->lines[x]->eTextureSize.y)
				) entities[currentEntityIndex]->canMoveDown = false;

		}



		for (int x=0; x< stages[currentStage]->platformCount; x++)
		{
			if (
				((entities[currentEntityIndex]->eBounds.x+entities[currentEntityIndex]->eTextureSize.x >= stages[currentStage]->platforms[x]->eBounds.x) &&
				 (entities[currentEntityIndex]->eBounds.x <= stages[currentStage]->platforms[x]->eBounds.x+stages[currentStage]->platforms[x]->eTextureSize.x)) &&
				((entities[currentEntityIndex]->eBounds.y+entities[currentEntityIndex]->eTextureSize.x >= stages[currentStage]->platforms[x]->eBounds.y) &&
				 entities[currentEntityIndex]->eBounds.y+entities[currentEntityIndex]->eTextureSize.y <= stages[currentStage]->platforms[x]->eBounds.y+stages[currentStage]->platforms[x]->eTextureSize.y)
				) entities[currentEntityIndex]->canMoveDown = false;

		}


		

		if  ( (entities[currentEntityIndex]->cCircle.getPosition().y >= 785-entities[currentEntityIndex]->cRadius))  NULL;  //bottom of screen
		else
		{
			movement.y += PlayerSpeed;
			rotateangle = PlayerSpeed;
		}
	}	
		


	if ( mIsMovingLeft && !positionLock)
	{
		//bool canMoveLeft = true;
		for (int x=0; x< stages[currentStage]->lineCount; x++)
		{
			if (
				((entities[currentEntityIndex]->eBounds.x <= stages[currentStage]->lines[x]->eBounds.x+stages[currentStage]->lines[x]->eTextureSize.x) &&
				 (entities[currentEntityIndex]->eBounds.x >= stages[currentStage]->lines[x]->eBounds.x)) && 
				((entities[currentEntityIndex]->eBounds.y+entities[currentEntityIndex]->eTextureSize.y >= stages[currentStage]->lines[x]->eBounds.y+8) && //+8 is give/take value
				 (entities[currentEntityIndex]->eBounds.y <= stages[currentStage]->lines[x]->eBounds.y+stages[currentStage]->lines[x]->eTextureSize.y-8))
				) entities[currentEntityIndex]->canMoveLeft = false;
		}	



		for (int x=0; x< stages[currentStage]->platformCount; x++)
		{
			if (
				((entities[currentEntityIndex]->eBounds.x <= stages[currentStage]->platforms[x]->eBounds.x+stages[currentStage]->platforms[x]->eTextureSize.x) &&
				 (entities[currentEntityIndex]->eBounds.x >= stages[currentStage]->platforms[x]->eBounds.x)) && 
				((entities[currentEntityIndex]->eBounds.y+entities[currentEntityIndex]->eTextureSize.y >= stages[currentStage]->platforms[x]->eBounds.y+8) && //+8 is give/take value
				 (entities[currentEntityIndex]->eBounds.y <= stages[currentStage]->platforms[x]->eBounds.y+stages[currentStage]->platforms[x]->eTextureSize.y-8))
				) entities[currentEntityIndex]->canMoveLeft = false;
		}	



		if ( !entities[currentEntityIndex]->canMoveLeft || (entities[currentEntityIndex]->cCircle.getPosition().x <= 0+entities[currentEntityIndex]->cRadius)) NULL;
			
		else 
		{
			movement.x -= PlayerSpeed;
			rotateangle = -PlayerSpeed;
		}
		


	}
	

	if ( mIsMovingRight && !positionLock)
	{	
		//bool canMoveRight = true;
		for (int x=0; x< stages[currentStage]->lineCount; x++)
		{

			if (
				((entities[currentEntityIndex]->eBounds.x + entities[currentEntityIndex]->eTextureSize.x >= stages[currentStage]->lines[x]->eBounds.x) &&
				 (entities[currentEntityIndex]->eBounds.x + entities[currentEntityIndex]->eTextureSize.x <= stages[currentStage]->lines[x]->eBounds.x+stages[currentStage]->lines[x]->eTextureSize.x)) &&
				((entities[currentEntityIndex]->eBounds.y + entities[currentEntityIndex]->eTextureSize.y >= stages[currentStage]->lines[x]->eBounds.y+8) &&
				 (entities[currentEntityIndex]->eBounds.y <= stages[currentStage]->lines[x]->eBounds.y+stages[currentStage]->lines[x]->eTextureSize.y-8))
				) entities[currentEntityIndex]->canMoveRight = false;

		}

		for (int x=0; x< stages[currentStage]->platformCount; x++)
		{
			if (
				((entities[currentEntityIndex]->eBounds.x + entities[currentEntityIndex]->eTextureSize.x >= stages[currentStage]->platforms[x]->eBounds.x) &&
				 (entities[currentEntityIndex]->eBounds.x + entities[currentEntityIndex]->eTextureSize.x <= stages[currentStage]->platforms[x]->eBounds.x+stages[currentStage]->platforms[x]->eTextureSize.x)) &&
				((entities[currentEntityIndex]->eBounds.y + entities[currentEntityIndex]->eTextureSize.y >= stages[currentStage]->platforms[x]->eBounds.y+8) &&
				 (entities[currentEntityIndex]->eBounds.y <= stages[currentStage]->platforms[x]->eBounds.y+stages[currentStage]->platforms[x]->eTextureSize.y-8))
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
		entities[2]->cCircle.setPosition(340,100);
	}

	
	
	//MOVING PLATFORM BY HOLDING SWITCH
	/*
	int currentSwitch = checkHitting(entities,stages,0,true);
	std::cout << "CURRENT SWITCH: " << currentSwitch << std::endl;	
	for (int x=0; x < stages[currentStage]->platformCount; x++)
	{
		if (currentSwitch >= 0)
		{
			//entities[9]->activatePlatform = true;
			stages[currentStage]->switches[currentSwitch]->eSprite.setTexture(stages[currentStage]->switches[currentSwitch]->eTexture2);
			if (stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch]->platformToActivate]->eSprite.getPosition().y <= stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch]->platformToActivate]->maxHeight) stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch]->platformToActivate]->activatePlatform = false;
			else stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch]->platformToActivate]->activatePlatform = true;
			if (stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch]->platformToActivate]->activatePlatform) stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch]->platformToActivate]->eSprite.move(0, -100*elapsedTime.asSeconds());
		}
		else 
			{
				stages[currentStage]->switches[0]->eSprite.setTexture(stages[currentStage]->switches[0]->eTexture);
				stages[currentStage]->platforms[x]->activatePlatform = false;
				if (stages[currentStage]->platforms[x]->eSprite.getPosition().y<= stages[currentStage]->platforms[x]->eStartPos.y)  stages[currentStage]->platforms[x]->eSprite.move(0, 100*elapsedTime.asSeconds());
			}
	}
	*/
	//END MOVING PLATFORM BY HOLDING SWITCH
	
		
	//EXTRA CODE, DO NOT ERASE
	/*
	else if (checkHitting(entities,0) != 0 && mPlatformSwitch)
	{
		mPlatformSwitch = false;
		entities[9]->activatePlatform = false;
		std::cout << "switch de-activated" << std::endl;
	}
	*/
	/*
	else
	{
		if (entities[9]->eSprite.getPosition().y<= entities[9]->eStartPos.y)  entities[9]->eSprite.move(0, 100*elapsedTime.asSeconds());
	}
	*/
	//EXTRA CODE, DO NOT ERASE


	
	//MOVING PLATFORM BY TOUCHING SWITCH
	
	int currentSwitch = checkHitting(entities,stages,0,true);
	//std::cout << "CURRENT SWITCH: " << currentSwitch << std::endl;
	for (int x=0; x<stages[currentStage]->platformCount; x++)
	{
		if (currentSwitch >= 0)
		{
			//std::cout << "CURRENT SWITCH: " << currentSwitch << std::endl;
			stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch]->platformToActivate]->activatePlatform = true;
			//std::cout << "switch activated" << std::endl;
			stages[currentStage]->switches[currentSwitch]->eSprite.setTexture(stages[currentStage]->switches[currentSwitch]->eTexture2);

		}	


		if (stages[currentStage]->platforms[x]->eSprite.getPosition().y <= stages[currentStage]->platforms[x]->maxHeight) stages[currentStage]->platforms[x]->activatePlatform = false;
		if (stages[currentStage]->platforms[x]->activatePlatform)
		{
			stages[currentStage]->platforms[x]->eSprite.move(0,-100*elapsedTime.asSeconds());
		}	

	}
	
	//END MOVING PLATFORM BY TOUCHING SWITCH


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


void Game::render(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{
	mWindow.clear();	
	mWindow.draw(stages[currentStage]->background);
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
		mWindow.draw(entities[x]->cCircle);
		//else mWindow.draw(entities[x]->eSprite);
	}

	for (int x=0; x<stages[currentStage]->lineCount; x++)
	{
		mWindow.draw(stages[currentStage]->lines[x]->eSprite);
	}

	for (int x=0; x<stages[currentStage]->platformCount; x++)
	{
		mWindow.draw(stages[currentStage]->platforms[x]->eSprite);
	}

	for (int x=0; x<stages[currentStage]->switchCount; x++)
	{
		mWindow.draw(stages[currentStage]->switches[x]->eSprite);
	}
	//mWindow.draw(stages[currentStage]->oven->eSprite);
	mPowerGaugeMetre.setTextureRect(sf::IntRect(0,0,mPowerGaugeMetreTexture.getSize().x,powerMetre));
	if (mDrawMetre)
	{
		mWindow.draw(mPowerGaugeShell);
		mWindow.draw(mPowerGaugeMetre);
	}
	

	//for (int x=7; x<ENTITIES_MAX; x++) mWindow.draw(entities[x]->eSprite);


	//mWindow.draw(entities[9]->eSprite);
	//mWindow.draw(entities[10]->eSprite);

	sf::Time removeNullSign = nullSignTime.getElapsedTime();
	if (!mDrawNull) removeNullSign = nullSignTime.restart();

	//if the current time is less than our update time
	if (removeNullSign.asSeconds() <= 2.0)
	{
		//keep getting the time until it is greater
		removeNullSign = nullSignTime.getElapsedTime();
		//std::cout << removeNullSign.asSeconds() << std::endl;
	}
	else 
	{
		mDrawNull = false;
		removeNullSign = nullSignTime.restart();
	}

	if (mDrawNull) mWindow.draw(mNullSign);

	mWindow.draw(mArrow);
	mWindow.display();
}


#endif