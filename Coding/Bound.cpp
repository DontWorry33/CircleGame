#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include "StringHelpers.hpp"
#include "Entity.cpp"
#include "Stage.cpp"
#include "UI.cpp"
#include "Transition.cpp"

#ifndef BOUND_H
#define BOUND_H

#define PI 3.14159265
#define ENTITIES_MAX 4
#define STAGES_MAX 6
#define G_MAX 160.0

class Game
{
	public:
	
		Game(sf::RenderWindow* tmpWin);
		//functions
		void run(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void updateEntityPosition(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		bool bottomCircleCollision(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		bool rightCircleCollision(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		bool leftCircleCollision(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		void checkGravity(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int character);
		void checkBounds(Entity* entities[ENTITIES_MAX]);
		int isTouchingPortal(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		int isTouchingBread(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		bool isTouchingSurface(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		bool isTouchingRotiSurface(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		void swapStage(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void initPostStage(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void startTransition(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void resetLevel(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);

		void breadSelector(sf::Keyboard::Key key, int selectedEntity); 
		void powerMetreUpdate(sf::Keyboard::Key key);	
		void entitySelector(Entity* entities[ENTITIES_MAX]);
		void Arrow(Entity* entities[ENTITIES_MAX]);
		void trajectory(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX]); 
		void checkHitting(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int airborneEntity, bool isSwitch, int* data);
		
		void activateRotiPowerAlpha(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void activateRotiPowerBeta(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void activateAnpanPower(Entity* entities[ENTITIES_MAX],Stage* stages[STAGES_MAX]);
		void swapBackground(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void activateBoulePower(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX],sf::Time elapsedTime);

		void processEvents(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		int pauseMenuRun();


		void motionCheck(int character, Entity* entities[ENTITIES_MAX],Stage* stages[STAGES_MAX]);
		void update(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		void render(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);

		void updateStatistics(sf::Time elapsedTime);	
		void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
		~Game();
		
	
		//constants for update statistics
		static const float PlayerSpeed;
		static const sf::Time TimePerFrame;

		//int* retValLeft;
		//int* retValRight;
		//int* retValS;
		sf::RenderWindow* mWindow;		


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


		sf::Text postScreenText;


		sf::Clock stageTime;
		sf::Text currentPointsText;
		sf::Text stageTimeText;

		//power gauuge
		sf::Sprite mPowerGaugeShell;
		sf::CircleShape mPowerGaugeMetre;

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

		bool mMissing; //for drawing missing
		int mEntityMissing; //for getting the index of the missing

		//stores position of baker so we can manipulate  positionLock.
		sf::Vector2f traj_pos;

		sf::Clock nullSignTime;
		sf::Clock missingSignTime;

		sf::Clock rotiShotTime;


		sf::Time elapsedTime;
		sf::Clock clock;
		sf::Time timeSinceLastUpdate;

		sf::Time currentStageTime;

		bool negateGravity;

		bool isBeingAttracted;

		bool bouleActivated;

		bool portalTeleport;
		bool breadTeleport;
		bool bLock;
		bool pLock;

		bool displaced;
		bool disp;
		bool negate;

		int currentStage;
		int tSwitch;
		int displacedSwitch;

		std::vector<sf::Music*> music;
   		sf::Music music1;
   		sf::Music music2;
   		sf::Music music3;
   		sf::Music music4;
   		sf::Music music5;
   		sf::Music music6;

   		int currSong;
   		bool rotiActive;
   		bool skipRoti;
   		bool skipBaker;
   		bool pointAdded;

   		int itrnum;

  		sf::Vector2f bakerRepulsion;
		sf::Vector2f rotiRepulsion;

		sf::Texture arrowTailImage;
		sf::Sprite arrowTail;

		Pause_Menu** pauseMenu; 
		Transition** transitList;

		sf::Clock fadeClock;

		sf::Texture postScreen_img;
		sf::Sprite postScreen;



		bool mDrawPostScreen;
		int currentPoints;

		bool debug;


};


const float Game::PlayerSpeed = 150.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);


//instantiates most objects and sets starting values
Game::Game(sf::RenderWindow* tmpWin) : 
			   mIsMovingUp(false), mIsMovingDown(false), mIsMovingRight(false),
			   mIsMovingLeft(false), mIsSpaceBar(false), mTeleportation(false), mStatisticsText(), mStatisticsUpdateTime(), rotiActivated(false), 
			   mFont(), mArrowTexture(), mPowerGaugeShell(), mPowerGaugeShellTexture() , mArrow(), g(0.6), 
			   timePerGravityUpdate(0.0002), mPowerGaugeMetreTexture(), mPowerGaugeMetre(),  timePerShot(1), shotChooser(0), mNullSignTexture(), mNullSign(), nullSignTime(), missingSignTime(),
			   music1(), music2(), music3(), music4(), music5(), rotiShotTime(), arrowTailImage(), arrowTail(), fadeClock(), postScreen(), postScreen_img(), stageTime()

{
   // mWindow->create(sf::VideoMode(1200, 800), "CircleGame!");
   // mWindow->setFramerateLimit(120);

	mWindow = tmpWin;
	//set all statistics
	mWindow->setFramerateLimit(60);
	mStatisticsNumFrames = 0;
	mFont.loadFromFile("Sansation.ttf");
	mStatisticsText.setFont(mFont);

	mStatisticsText.setCharacterSize(20);
	mStatisticsText.setColor(sf::Color::White);

	postScreenText.setFont(mFont);
	postScreenText.setColor(sf::Color::Black);
	postScreenText.setCharacterSize(35);

	currentPointsText.setFont(mFont);
	currentPointsText.setColor(sf::Color::Black);
	currentPointsText.setCharacterSize(30);
	currentPointsText.setPosition(900,10);
	

	stageTimeText.setFont(mFont);
	stageTimeText.setColor(sf::Color::Black);
	stageTimeText.setCharacterSize(30);
	stageTimeText.setPosition(240,10);

	//set arrow stuff
	mArrowTexture.loadFromFile("../Character_Images/Arrowhead.png");
	mArrow.setTexture(mArrowTexture);
	mArrow.setPosition(490+45,600-55);
	mArrow.setOrigin(45,55);

	//set powergauge stuff
	mPowerGaugeMetreTexture.loadFromFile("../Character_Images/PowerGauge_Metre.png");
	mPowerGaugeShellTexture.loadFromFile("../Character_Images/PowerGauge_Shell.png");
	mPowerGaugeMetre.setTexture(&mPowerGaugeMetreTexture);
	mPowerGaugeShell.setTexture(mPowerGaugeShellTexture);

	mPowerGaugeMetre.setRadius(mPowerGaugeMetreTexture.getSize().x/2);
	mPowerGaugeMetre.setOrigin(mPowerGaugeMetreTexture.getSize().x/2,mPowerGaugeMetreTexture.getSize().y/2);


	mNullSignTexture.loadFromFile("../Stage_Images/Universal_StageParts/Stage_NullSign.png");
	mNullSign.setTexture(mNullSignTexture);

	postScreen_img.loadFromFile("../User_Interfaces/postgamescreen.png");
	postScreen.setTexture(postScreen_img);
	mDrawPostScreen = false;
	currentPoints = 0;

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

	mDrawNull = false;

	mMissing = false;
	mEntityMissing = 1;

	negateGravity = false;

	isBeingAttracted = false;

	mPlatformSwitch = false;

	currentStage = 0;

	bouleActivated = false;

	portalTeleport = false;
	breadTeleport = false;


	pLock = false;
	bLock = false;

	displaced = false;
	disp = false;
	negate = false;

	tSwitch = 0;
	currSong = 0;
    displacedSwitch = -1;
    rotiActive = false;

    skipRoti = false;
    skipBaker = false;

    bakerRepulsion.x = 400;
    rotiRepulsion.x = 600;
    bakerRepulsion.y = 0;
    rotiRepulsion.y = 0;
    pointAdded = false;

    //DEBUG VAR, TRUE WILL ENABLE ALL THE TEXT
    debug = false;

    itrnum = 0;

	if (!music1.openFromFile("../Music/bossX.ogg")) NULL; music.push_back(&music1);
	if (!music2.openFromFile("../Music/puzzlegamebackgroundmusic.ogg")) NULL; music.push_back(&music2);
	if (!music3.openFromFile("../Music/puzzlegametheme.ogg")) NULL; music.push_back(&music3);
	if (!music4.openFromFile("../Music/freneticpuzzlegame.ogg")) NULL; music.push_back(&music4);
	if (!music5.openFromFile("../Music/puzzlegamemusic.ogg")) NULL; music.push_back(&music5);
    //LET CALLERS PER FUCNTION ALLOCATE ARRAY ON STACK THEN MODIFY IN CHECKHITTING AND RETURN!
	//retValLeft = new int[2];
	//retValRight = new int[2];
	//retValS = new int[1];



	arrowTailImage.loadFromFile("../Character_Images/Arrowtail.png");
	arrowTail.setTexture(arrowTailImage);

	pauseMenu = new Pause_Menu* [STAGES_MAX];

	pauseMenu[0] = new Pause_Menu(mWindow, 
		"../User_Interfaces/Pause_Screens/1Pause/1Pause_Default.png",
		"../User_Interfaces/Pause_Screens/1Pause/1Pause_Resume.png",
		"../User_Interfaces/Pause_Screens/1Pause/1Pause_Quit.png");
	pauseMenu[1] = new Pause_Menu(mWindow, 
		"../User_Interfaces/Pause_Screens/2Pause/2Pause_Default.png",
		"../User_Interfaces/Pause_Screens/2Pause/2Pause_Resume.png",
		"../User_Interfaces/Pause_Screens/2Pause/2Pause_Quit.png");
	pauseMenu[2] = new Pause_Menu(mWindow, 
		"../User_Interfaces/Pause_Screens/3Pause/3Pause_Default.png",
		"../User_Interfaces/Pause_Screens/3Pause/3Pause_Resume.png",
		"../User_Interfaces/Pause_Screens/3Pause/3Pause_Quit.png");
	pauseMenu[3] = new Pause_Menu(mWindow, 
		"../User_Interfaces/Pause_Screens/4Pause/4Pause_Default.png",
		"../User_Interfaces/Pause_Screens/4Pause/4Pause_Resume.png",
		"../User_Interfaces/Pause_Screens/4Pause/4Pause_Quit.png");
	pauseMenu[4] = new Pause_Menu(mWindow, 
		"../User_Interfaces/Pause_Screens/5Pause/5Pause_Default.png",
		"../User_Interfaces/Pause_Screens/5Pause/5Pause_Resume.png",
		"../User_Interfaces/Pause_Screens/5Pause/5Pause_Quit.png");
	pauseMenu[5] = new Pause_Menu(mWindow, 
		"../User_Interfaces/Pause_Screens/6Pause/6Pause_Default.png",
		"../User_Interfaces/Pause_Screens/6Pause/6Pause_Resume.png",
		"../User_Interfaces/Pause_Screens/6Pause/6Pause_Quit.png");



	transitList = new Transition* [1];

	transitList[0] = new Transition("../User_Interfaces/Transit_Screens/Transit_0-Default.png",
									   "../User_Interfaces/Transit_Screens/Transit_1-Curiosity.png",
									   "../User_Interfaces/Transit_Screens/Transit_1-CuriosityB.png");

	timeSinceLastUpdate = sf::Time::Zero;
}






//main game loop. Runs all functions, processes events, updates game, updates statistics and renders
//read 
void Game::run(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{
	
	timeSinceLastUpdate = sf::Time::Zero;
	stageTime.restart();
	while (mWindow->isOpen())
	{
		
		//get the current amount of time elapsed
		
		//processEvents(elapsedTime, entities);
			if (debug) std::cout << "window open " << std::endl;
			elapsedTime = clock.restart();
			timeSinceLastUpdate += elapsedTime;
			if (debug) std::cout << elapsedTime.asSeconds() << std::endl;
			//if (music[currSong]->getStatus() !=  sf::Sound::Playing) music[currSong]->play();

			while (timeSinceLastUpdate > TimePerFrame)
			{
				if (debug) std::cout << "inner while " << std::endl;
				timeSinceLastUpdate -= TimePerFrame;

				//mPowerGaugeMetre.setRadius(powerMetre);

				//if mouse lock is not active, get the curr pos, same with position
				if (!mouseLock && !pauseMenu[currentStage]->isPaused) mMousePos = sf::Mouse::getPosition(*(mWindow));
				if (!positionLock)
				{
					traj_pos = entities[0]->cCircle.getPosition();
					mArrow.setPosition(entities[0]->cCircle.getPosition());

				}
				else
				{
					mArrow.setPosition(traj_pos);
				}
				//set the arrow position to follow the circle

				mPowerGaugeShell.setPosition(entities[currentEntityIndex]->cCircle.getPosition().x-100,entities[currentEntityIndex]->cCircle.getPosition().y-80);
				mPowerGaugeMetre.setPosition(mPowerGaugeShell.getPosition().x+mPowerGaugeMetre.getRadius(), mPowerGaugeShell.getPosition().y+mPowerGaugeMetre.getRadius());


				Arrow(entities);
				if (currentEntityIndex > 0 ) arrowTail.setPosition(entities[currentEntityIndex]->eBounds.x, entities[currentEntityIndex]->eBounds.y-40);
				//get mouse-coordinates relative to the window

				updateEntityPosition(entities,stages);

				if (mResetGame) resetLevel(entities,stages);
				
				for (int x=0; x < stages[currentStage]->platformCount; x++)
				{
					stages[currentStage]->platforms[x]->eBounds.x = stages[currentStage]->platforms[x]->eSprite.getPosition().x - stages[currentStage]->platforms[x]->eTextureSize.x/2;
					stages[currentStage]->platforms[x]->eBounds.y = stages[currentStage]->platforms[x]->eSprite.getPosition().y - stages[currentStage]->platforms[x]->eTextureSize.y/2;
				}

				for (int x = 0; x<ENTITIES_MAX; x++) 
				{ 
					if (!negateGravity && !pauseMenu[currentStage]->isPaused)
						{
							//std::cout << "gravity applying" << std::endl;
							checkGravity(entities, stages, x); 
						}
					//checkGravity(entities,stages,x);
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
							if (entities[x]->gCurrent < G_MAX && !negateGravity && !pauseMenu[currentStage]->isPaused) entities[x]->gCurrent+=g;
							else if (negateGravity && ( x == 0 || x == 1)) continue; 
							//else entities[x]->gCurrent = G_MAX;
						}
						updateGravity = gravityClock.restart();
					}
		//-----------------
					//std::cout << "PM : " << powerMetre << std::endl;
				
					//activateRotiPowerBeta(elapsedTime, entities);

	//				std::cout << "entities 1 pos: " << entities[1]->eBounds.x << ", " << entities[1]->eBounds.y << std::endl;

		//--------------TRAJECTORY PARAMETERS
					itrnum++;
					if (debug) std::cout << "iteration: " << itrnum << std::endl;

					if ( (mIsLaunched)) 
					{
						positionLock = true;
						mouseLock=true;
						if (!pauseMenu[currentStage]->isPaused)
						{
							if (debug) std::cout << "entities 1 pos before traj call: " << entities[1]->cCircle.getPosition().x << ", " << entities[1]->cCircle.getPosition().y << std::endl;

							trajectory(elapsedTime, entities);
							if (debug) std::cout << "entities 1 pos after traj call: " << entities[1]->cCircle.getPosition().x << ", " << entities[1]->cCircle.getPosition().y << std::endl;
						
						//Right Border Collision Check	
							if (entities[shotChooser]->cCircle.getPosition().x >= 1200 - entities[shotChooser]->cRadius)
							{
								std::cout << "rb stopped trag" << std::endl;
								powerMetre = 3;
								mIsLaunched = false;
								mDrawMetre = false;
								entities[shotChooser]->cCircle.setPosition(1200-entities[shotChooser]->cRadius, entities[shotChooser]->cCircle.getPosition().y);
								updateEntityPosition(entities,stages);
								entities[shotChooser]->isCreated = true;
								entities[shotChooser]->gCurrent = 0;	
							}
							
						//Left Border Collision Check	
							if (entities[shotChooser]->cCircle.getPosition().x <= 0 + entities[shotChooser]->cRadius)
							{
								std::cout << "lb stopped trag" << std::endl;
								powerMetre = 3;
								mIsLaunched = false;
								mDrawMetre = false;
								entities[shotChooser]->cCircle.setPosition(0+entities[shotChooser]->cRadius, entities[shotChooser]->cCircle.getPosition().y);
								updateEntityPosition(entities,stages);

							
								//entities[shotChooser]->gCurrent = 0;	
								//entities[shotChooser]->isCreated = true;
							}

						//Top Border Collision Check
							if (entities[shotChooser]->eBounds.y <= 0+entities[shotChooser]->cRadius)
							{
								if (debug) std::cout << "entities 1 pos inside TB collision check: " << entities[1]->cCircle.getPosition().x << ", " << entities[1]->cCircle.getPosition().y << std::endl;
								std::cout << "tb stopped trag" << std::endl;
								powerMetre = 3;
								mIsLaunched = false;
								mDrawMetre = false;
								entities[shotChooser]->cCircle.setPosition(entities[shotChooser]->cCircle.getPosition().x,0+entities[shotChooser]->cRadius);
								updateEntityPosition(entities,stages);

							
								//entities[shotChooser]->gCurrent = 0;	
								//entities[shotChooser]->isCreated = true;
							}

						//Bottom Border Collision Check
							//std::cout << "ebounds.y (" << shotChooser << "): " << entities[shotChooser]->eBounds.y+entities[shotChooser]->eTextureSize.y << std::endl;
							if (entities[shotChooser]->eBounds.y+entities[shotChooser]->eTextureSize.y >= 785)
							{
								std::cout << "bb stopped trag" << std::endl;
								powerMetre = 3;
								mIsLaunched = false;
								mDrawMetre = false;
								entities[shotChooser]->cCircle.setPosition(entities[shotChooser]->cCircle.getPosition().x,785-entities[shotChooser]->cRadius);
								updateEntityPosition(entities,stages);

							
								entities[shotChooser]->isCreated = true;
								entities[shotChooser]->gCurrent = 0;	
							}

							if (isTouchingSurface(entities, stages, shotChooser))
							{
								std::cout << "touching da surf stopped trajectory" << std::endl;
								//bottomCircleCollision(entities,stages,shotChooser);
								powerMetre = 3;
								mIsLaunched = false;
								mDrawMetre = false;
								entities[shotChooser]->isCreated = true;
								
							}
							
							int tmmp[3];
							checkHitting(entities,stages,shotChooser,false,tmmp);
							if (tmmp[1])
							{
								std::cout << "check hitting stopped trajectory" << std::endl;
								powerMetre = 3;
								mIsLaunched = false;
								mDrawMetre = false;
								entities[shotChooser]->gCurrent = 0;	
								entities[shotChooser]->isCreated = true;
							}
							
						
							//CHANGED TO TEST FOR ALL STAGE PARTS AT ALL TIMES. LESS EFFICIEINT.	
									
						}
						//else entities[shotChooser]->isCreated = true;
					}

					else 
					{
						mouseLock=false;
						positionLock=false;
					}


				processEvents(elapsedTime, entities, stages);

				if (debug) std::cout << "entities 1 pos after PE: " << entities[1]->cCircle.getPosition().x << ", " << entities[1]->cCircle.getPosition().y << std::endl;


				if (rotiActive)
				{

					std::cout << "currently active" << std::endl;
					negateGravity = false;
					int bakerHitting[3]; 
					int	rotiHitting[3]; 
					checkHitting(entities,stages,0,false,bakerHitting);
					checkHitting(entities,stages,1,false,rotiHitting);

			//const float pushValue = 1000.f;

					//sf::Time applyRepulsion = shotClock.getElapsedTime();
					if (!skipBaker)
					{
						if (bakerHitting[1] == 3 && rotiHitting[1] == 2)
						{
							if (bakerRepulsion.x > 0) bakerRepulsion.x = -bakerRepulsion.x;
							std::cout << "negating baker in skipbaker" << std::endl;
						}
						if (rotiHitting[1] == 3 && bakerHitting[1] == 2)
						{	
							if (rotiRepulsion.x > 0) rotiRepulsion.x = -rotiRepulsion.x;
							std::cout << "negating roti in skipbaker****" << std::endl;

						}
					}
					if (!skipRoti)
					{
						if (rotiHitting[1] == 3 && bakerHitting[1] == 2)
						{	
							if (rotiRepulsion.x > 0) rotiRepulsion.x = -rotiRepulsion.x;
							std::cout << "negating roti in skiproti" << std::endl;

						}
						if (bakerHitting[1] == 3 && rotiHitting[1] == 2)
						{
							if (bakerRepulsion.x > 0) bakerRepulsion.x = -bakerRepulsion.x;
							std::cout << "negating baker in skiproti****" << std::endl;
						}
					}
					//need to restrict movement as it can currently move "through" a wall.
					//std::cout << elapsedTime.asSeconds() << std::endl;
					//std::cout << applyMotion.asSeconds() << std::endl;
					//std::cout << bakerRepulsion.x << rotiRepulsion.x << std::endl;
					//if (applyMotion.asSeconds() < 0.35) 
					if (!isTouchingRotiSurface(entities,stages,0) || (entities[0]->cCircle.getPosition().y >=  785-entities[0]->cRadius))
					{
						//std::cout << "applying baker force" << std::endl;
						if (!skipBaker) std::cout << "starting skip baker" << std::endl;
						skipBaker=true;
						if (bakerRepulsion.x > 0) if (rightCircleCollision(entities,stages,0)) { rotiActive=false; std::cout << "baker, > 0" << std::endl; currentPoints+=1;}
						if (bakerRepulsion.x < 0) if (leftCircleCollision(entities,stages,0)) { rotiActive = false; std::cout << "baker, < 0" << std::endl; currentPoints+=1;}
						entities[0]->cCircle.move( bakerRepulsion * elapsedTime.asSeconds());
					}
					else
					{
						//std::cout << "stopping baker force" << std::endl;
						bakerRepulsion.x = 400;
						skipBaker = false;
					}
					if (!isTouchingRotiSurface(entities,stages,1) || (entities[1]->cCircle.getPosition().y >=  785-entities[1]->cRadius))
					{
						//std::cout << "applying roti force" << std::endl;
						if (!skipRoti) std::cout << "starting skip roti" << std::endl;
						skipRoti = true;
						if (rotiRepulsion.x > 0) if (rightCircleCollision(entities,stages,1)) { rotiActive=false; std::cout << "roti, > 0" << std::endl; currentPoints+=1;}
						if (rotiRepulsion.x < 0) if (leftCircleCollision(entities,stages,1)) { rotiActive=false; std::cout << "roti, < 0" << std::endl; currentPoints+=1;}
						entities[1]->cCircle.move( rotiRepulsion * elapsedTime.asSeconds());
					}
					else
					{
						//std::cout << "stopping roti force " << std::endl;
						rotiRepulsion.x = 600;
						skipRoti = false;
					}



					//BUG WITH THIS! WHEN ROTI/BAKER ARE AT TOP, I THINK IT TRIGGERS BL OR
					if ( (isTouchingRotiSurface(entities,stages,0) || (entities[0]->cCircle.getPosition().y >=  785-entities[0]->cRadius)) && (isTouchingRotiSurface(entities,stages,1) || (entities[1]->cCircle.getPosition().y >=  785-entities[1]->cRadius)))
					{
						if (bakerRepulsion.x > 0 && (skipRoti || skipBaker)) if (rightCircleCollision(entities,stages,0)) { rotiActive=false; std::cout << "c1" << std::endl; currentPoints+=1;}
						if (bakerRepulsion.x < 0 && (skipRoti || skipBaker)) if (leftCircleCollision(entities,stages,0)) { rotiActive=false; std::cout << "c2" << std::endl; currentPoints+=1;}
						if (rotiRepulsion.x > 0 && (skipRoti || skipBaker)) if (rightCircleCollision(entities,stages,1)) { rotiActive=false; std::cout << "c3" << std::endl; currentPoints+=1;}
						if (rotiRepulsion.x < 0 && (skipRoti || skipBaker)) if (rightCircleCollision(entities,stages,1)) { rotiActive=false; std::cout << "c4" << std::endl; currentPoints+=1;}
						std::cout << "rotiactive is false" << std::endl;
						currentPoints+=1;
						rotiActive = false;
					}
				}

			if (!pauseMenu[currentStage]->isPaused) 
				{
					update(TimePerFrame,entities,stages);
				}

			}

			updateStatistics(elapsedTime);
			render(entities,stages);
		}
		//if (mResetGame) return 1;
		//return 0;
	

}

void Game::updateEntityPosition(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{
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

		entities[x]->bottomRCircle[0] = entities[x]->cCircle.getPosition().x + (entities[x]->cRadius*cos(PI/4));
		entities[x]->bottomRCircle[1] = entities[x]->cCircle.getPosition().y + (entities[x]->cRadius*sin(PI/4));

		entities[x]->bottomLCircle[0] = entities[x]->cCircle.getPosition().x + (entities[x]->cRadius*cos(3*PI/4));
		entities[x]->bottomLCircle[1] = entities[x]->cCircle.getPosition().y + (entities[x]->cRadius*sin(3*PI/4));

		entities[x]->bottomLLCircle[0] =  entities[x]->cCircle.getPosition().x + (entities[x]->cRadius*cos(2*PI/3));
		entities[x]->bottomLLCircle[1] = entities[x]->cCircle.getPosition().y + (entities[x]->cRadius*sin(2*PI/3));

		entities[x]->bottomRRCircle[0] =  entities[x]->cCircle.getPosition().x + (entities[x]->cRadius*cos(PI/3));
		entities[x]->bottomRRCircle[1] = entities[x]->cCircle.getPosition().y + (entities[x]->cRadius*sin(PI/3));
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

		int rooX = entities[currentEntityIndex]->cCircle.getPosition().x + (entities[currentEntityIndex]->cRadius*cos(PI));
		int rooY = entities[currentEntityIndex]->cCircle.getPosition().y + (entities[currentEntityIndex]->cRadius*sin(PI));
	//std::cout << "(" << rooX << "," << rooY << ")" << std::endl;
		//apply formula to move mArrow around circumference of circle. (cx + r*cos(angle))

		 mArrow.setPosition(cx-(entities[currentEntityIndex]->cRadius * cos(angle_in_rad)), cy-(entities[currentEntityIndex]->cRadius * sin(angle_in_rad)));
		 //arrowTail.setPosition(cx-(entities[currentEntityIndex]->cRadius * cos(angle_in_rad)), cy-(entities[currentEntityIndex]->cRadius * sin(angle_in_rad)));
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
	if (				
		(((entities[0]->eBounds.x <= stages[currentStage]->oven->eBounds.x+stages[currentStage]->oven->eTextureSize.x) &&
		 (entities[0]->eBounds.x >= stages[currentStage]->oven->eBounds.x)) && 
		((entities[0]->eBounds.y+entities[0]->eTextureSize.y >= stages[currentStage]->oven->eBounds.y) && //+8 is give/take value
		 (entities[0]->eBounds.y <= stages[currentStage]->oven->eBounds.y+stages[currentStage]->oven->eTextureSize.y)))
		)
	{

		mIsMovingLeft = false;
		mDrawPostScreen = true;
		render(entities,stages);
		initPostStage(entities,stages);
		mDrawPostScreen = false;
		render(entities,stages);
		startTransition(entities,stages);
		resetLevel(entities,stages);
		currentStage += 1;
		resetLevel(entities,stages);
		entities[0]->cCircle.setPosition(stages[currentStage]->bakerStartPos);
		currentPoints = 0;
		stageTime.restart();
		return;
	}			


	else if	(
		((entities[0]->eBounds.x + entities[0]->eTextureSize.x >= stages[currentStage]->oven->eBounds.x) &&
		 (entities[0]->eBounds.x + entities[0]->eTextureSize.x <= stages[currentStage]->oven->eBounds.x+stages[currentStage]->oven->eTextureSize.x)) &&
		((entities[0]->eBounds.y + entities[0]->eTextureSize.y >= stages[currentStage]->oven->eBounds.y+8) &&
		 (entities[0]->eBounds.y <= stages[currentStage]->oven->eBounds.y+stages[currentStage]->oven->eTextureSize.y-8))
		)	   
	{
		mIsMovingLeft = false;
		mDrawPostScreen = true;
		render(entities,stages);
		initPostStage(entities,stages);
		mDrawPostScreen = false;
		render(entities,stages);
		startTransition(entities,stages);
		resetLevel(entities,stages);
		currentStage += 1;
		resetLevel(entities,stages);
		entities[0]->cCircle.setPosition(stages[currentStage]->bakerStartPos);
		currentPoints = 0;
		stageTime.restart();
		return;
	}
}

void Game::initPostStage(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{
		
		sf::Event event4;
		while (true)
		{
			while (mWindow->pollEvent(event4))
			{
				switch (event4.type)
				{
					case sf::Event::KeyPressed:
						if (event4.key.code == sf::Keyboard::Return) return;

				}
			}

		}


}

void Game::startTransition(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{

		for (int tr = 0; tr < 3; tr++)
		{
			int x = 255;
			if (tr == 0)	
			{	
				while (x > 0)
				{	
					sf::Time fade = fadeClock.getElapsedTime();
					if (fade.asSeconds() >= 0.001)
					{
						fade = fadeClock.restart();
						mWindow->clear();
						stages[currentStage]->background.setColor(sf::Color(stages[currentStage]->background.getColor().r, 
						stages[currentStage]->background.getColor().g, stages[currentStage]->background.getColor().b, x));
						mWindow->draw(stages[currentStage]->background);
						mWindow->display();
						std::cout << x << std::endl;
						x-=2;
					}
				}
				x = 0;
				while (x < 255)
				{
					sf::Time fade = fadeClock.getElapsedTime();
					if (fade.asSeconds() >= 0.01)
					{
						fade = fadeClock.restart();
						mWindow->clear();
						transitList[currentStage]->transit[0]->setColor(sf::Color(transitList[currentStage]->transit[0]->getColor().r, 
						transitList[currentStage]->transit[0]->getColor().g, transitList[currentStage]->transit[0]->getColor().b, x));
						std::cout << x << std::endl;
						mWindow->draw(*(transitList[currentStage]->transit[0]));	
						mWindow->display();
						x+=2;
					}
				}
				x = 255;
			}

			else
			{
				x = 0;
				while (x < 255)
				{
					sf::Time fade = fadeClock.getElapsedTime();
					if (fade.asSeconds() >= 0.001)
					{
						fade = fadeClock.restart();
						mWindow->clear();
						transitList[currentStage]->transit[tr]->setColor(sf::Color(transitList[currentStage]->transit[tr]->getColor().r, 
						transitList[currentStage]->transit[tr]->getColor().g, transitList[currentStage]->transit[tr]->getColor().b, x));
						std::cout << x << std::endl;
						mWindow->draw(*(transitList[currentStage]->transit[tr-1]));
						mWindow->draw(*(transitList[currentStage]->transit[tr]));	
						mWindow->display();
						x+=2;
					}
				
				}
				

			}
		}
		sf::Event event3;
		//sf::Time fade = fadeClock.restart();
		//while (fade.asSeconds() < 2.f) fade = fadeClock.getElapsedTime();;
		while (true)
		{
			while (mWindow->pollEvent(event3))
			{
				switch (event3.type)
				{
					case sf::Event::KeyPressed:
						if (event3.key.code == sf::Keyboard::Q) return;

				}
			}

		}
		
}


void Game::resetLevel(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{
	entities[0]->cCircle.setPosition(stages[currentStage]->bakerStartPos);
	for (int x=1; x<ENTITIES_MAX; x++)
	{
		entities[x]->cCircle.setPosition(entities[x]->eStartPos);
		entities[x]->isCreated = false;

		entities[x]->isCurrentEntity = false;
	}

	for (int x=0; x<stages[currentStage]->platformCount; x++)
	{
		stages[currentStage]->platforms[x]->eSprite.setPosition(stages[currentStage]->platforms[x]->eStartPos);
		stages[currentStage]->platforms[x]->activatePlatform = false;
	}
	for (int x=0; x<stages[currentStage]->switchCount; x++)
	{
		stages[currentStage]->switches[x]->eSprite.setTexture(stages[currentStage]->switches[x]->eTexture);
		stages[currentStage]->switches[x]->switchUsed = false;
	}
	currentEntityIndex = 0;
	powerMetre = 3;
	entities[0]->isCurrentEntity = true;
	mResetGame = false;
	if (bouleActivated) swapBackground(entities,stages);

	portalTeleport = false;
	breadTeleport = false;
	pLock = false;
	bLock = false;
    rotiActive = false;
    shotChooser = 0;

    skipRoti = false;
    skipBaker = false;

    bakerRepulsion.x = 400;
    rotiRepulsion.x = 600;
    bakerRepulsion.y = 0;
    rotiRepulsion.y = 0;
	updateEntityPosition(entities,stages);

	

}

/*
we need to check if the stage part tthat roti/baker is on, make sure it's under the max height.

*/
void Game::activateRotiPowerAlpha(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && currentEntityIndex == 1)
	{


		
		sf::Vector2f attract_direction(150.0,0.f);
		int rotateangle = 150;


		motionCheck(0,entities,stages);
		
		//If Roti is Right of Baker (Greater)
		if (entities[1]->eBounds.x > entities[0]->eBounds.x)
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
		int bakerHitting[3];
		int rotiHitting[3];
		checkHitting(entities,stages,0,false,bakerHitting);
		checkHitting(entities,stages,1,false,rotiHitting);


		if (bakerHitting[1] > 1 && rotiHitting[1] > 1 && bakerHitting[1]!=rotiHitting[1] && bakerHitting[0] == rotiHitting[0]) //checks if both touching a surface, now we need to check if touching opposite sides && saftey check for length of surface.
		{
			//std::cout << "hitting opposite sides of same surface";
			//std::cout << "baker: " << bakerHitting[1] << ", " << "roti: " << rotiHitting[1] << std::endl;
			//std::cout << "bakerstage: " << bakerHitting[0] << ", " << "rotistage: " << rotiHitting[0] << std::endl;
			//check data[0] max height
			//std::cout << entities[0]->eBounds.y << std::endl;
			//std::cout << stages[currentStage]->platforms[bakerHitting[0]]->eBounds.y << std::endl;
			if (rotiHitting[2]==0) if (entities[1]->eBounds.y+entities[1]->cRadius-25 <= stages[currentStage]->lines[rotiHitting[0]]->eBounds.y)
			{
				negateGravity = false;
			}
			else 
			{
				negateGravity = true;

			}				
			if (rotiHitting[2] == 1) if (entities[1]->eBounds.y+entities[1]->cRadius-25 <= stages[currentStage]->platforms[rotiHitting[0]]->eBounds.y)
			{
				negateGravity = false;
			}
			else
			{
				negateGravity = true;
				
			}
			entities[0]->canMoveDown = true;
			entities[0]->gCurrent = 0;
			entities[1]->canMoveDown = true;
			entities[1]->gCurrent = 0;
			rotateangle = 150;
			if (entities[1]->eBounds.y <= entities[0]->eBounds.y+27)
			{

				isBeingAttracted = true;
				attract_direction.y = -150.f;
				updateEntityPosition(entities,stages);
			}
			std::cout << "baker bound: " << entities[0]->eBounds.y << ", roti bound: " << entities[1]->eBounds.y << std::endl;
			if (entities[0]->eBounds.y < entities[1]->eBounds.y-39)
			{
				negateGravity = false;
			}


		}
		else 
		{
			negateGravity = false;
			//entities[0]->gCurrent = 0;
			//entities[1]->gCurrent = 1;
			isBeingAttracted = false;
		}

		entities[0]->cCircle.move(attract_direction * elapsedTime.asSeconds());
		entities[0]->cCircle.rotate(rotateangle*elapsedTime.asSeconds());

	}



}

//FIX SO THAT TRAJECTORY IS APPLIED INSTEAD OF JUST 1 SINGLE BIG MOVEMENT

/*
	use the function to set a boolean value.
Reason for this is so that the external function can be called with frame time rather than on-buttom-release so that
we can move with the trajectory instead of 1 movement.
*/
void Game::activateRotiPowerBeta(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{

	if (isBeingAttracted)
	{ 
		//std::cout << "setting active to true" << std::endl;
		rotiActive = true;
		//negateGravity = false;
	}
	negateGravity = false;
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
			currentPoints +=1;
			entities[currentEntityIndex]->cCircle.setPosition(temp_pos);
			entities[currentEntityIndex]->isCurrentEntity = false;
			currentEntityIndex = 0;
			entities[0]->isCurrentEntity = true;
		}
	}
}

void Game::swapBackground(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{
	if(stages[currentStage]->background.getTexture() == &(stages[currentStage]->backgroundTexture)) 
		{
			currentPoints+=1;
			stages[currentStage]->background.setTexture(stages[currentStage]->bouleTexture);
			bouleActivated = true;
		}
	else 
		{
			stages[currentStage]->background.setTexture(stages[currentStage]->backgroundTexture);
			bouleActivated = false;
		}
}

void Game::activateBoulePower(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], sf::Time elapsedTime)
{

		if (bouleActivated)
		{
			int currentSwitch[1];
			checkHitting(entities,stages,3,true, currentSwitch);

			//if (currentSwitch[0] >= 0 && (stages[currentStage]->switches[currentSwitch[0]]->switchType == 1 || stages[currentStage]->switches[currentSwitch[0]]->switchType == 0))
			
			
			//std::cout << "CURRENT TYPE: " << stages[currentStage]->switches[currentSwitch[0]]->switchType << std::endl;
			//std::cout << "SWITCH #: " << currentSwitch[0] << std::endl;
				for (int x=0; x < stages[currentStage]->platformCount; x++)
				{
					//std::cout << "holding" << std::endl;
					if (currentSwitch[0] >= 0 && stages[currentStage]->switches[currentSwitch[0]]->switchType == 1)
					{
						//entities[9]->activatePlatform = true;
						tSwitch = currentSwitch[0];
						if (tSwitch > 0 && stages[currentStage]->switches[tSwitch-1]->switchUsed)
						{
							for (int sw = 0; sw <= tSwitch; sw++)
							{
								if (sw<tSwitch)
								{
									//std::cout << "within" << std::endl;
									if (stages[currentStage]->switches[sw]->switchUsed) stages[currentStage]->switches[sw]->eSprite.setTexture(stages[currentStage]->switches[sw]->eTexture);
									if (stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->eSprite.getPosition().y <= stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->eStartPos.y) stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->eSprite.move(0, 100*elapsedTime.asSeconds());
									stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->activatePlatform = false;
								}
							}
						}
						if (tSwitch+1 <= stages[currentStage]->switchCount-1 )
						{
							if (stages[currentStage]->switches[tSwitch+1]->switchUsed)
							{
								for (int sw=tSwitch; sw<=tSwitch+1; sw++)
								{
									if (sw>tSwitch)
									{
										if (stages[currentStage]->switches[sw]->switchUsed) stages[currentStage]->switches[sw]->eSprite.setTexture(stages[currentStage]->switches[sw]->eTexture);
										if (stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->eSprite.getPosition().y<= stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->eStartPos.y) stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->eSprite.move(0, 100*elapsedTime.asSeconds());
										stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->activatePlatform = false;
									}
								}
							}
						}

						//std::cout << "TSWITCH: " << tSwitch << std::endl;
						stages[currentStage]->switches[currentSwitch[0]]->eSprite.setTexture(stages[currentStage]->switches[currentSwitch[0]]->eTexture2);
						if (stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->eSprite.getPosition().y <= stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->maxHeight) stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->activatePlatform = false;
						else stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->activatePlatform = true;
						if (stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->activatePlatform && stages[currentStage]->switches[currentSwitch[0]]->switchUsed) stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->eSprite.move(0, -100*elapsedTime.asSeconds());
						stages[currentStage]->switches[currentSwitch[0]]->switchUsed = true;
					}
					else if (stages[currentStage]->switches[tSwitch]->switchType == 1)
						{
							//std::cout << "SWAPPING TEXTURE BACK ON: " << tSwitch << std::endl;
								stages[currentStage]->switches[tSwitch]->eSprite.setTexture(stages[currentStage]->switches[tSwitch]->eTexture);
								stages[currentStage]->switches[tSwitch]->switchUsed = false;					

							stages[currentStage]->platforms[x]->activatePlatform = false;
							if (stages[currentStage]->platforms[x]->eSprite.getPosition().y <= stages[currentStage]->platforms[x]->eStartPos.y)  stages[currentStage]->platforms[x]->eSprite.move(0, 100*elapsedTime.asSeconds());
						}
				}
		
				for (int x=0; x<stages[currentStage]->platformCount; x++)
				{
					//std::cout << "touching" << std::endl;
					if (currentSwitch[0] >= 0 && stages[currentStage]->switches[currentSwitch[0]]->switchType == 0)
					{
						//if touching a switch, activate the associated platform and swap textures
						stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->activatePlatform = true;
						stages[currentStage]->switches[currentSwitch[0]]->eSprite.setTexture(stages[currentStage]->switches[currentSwitch[0]]->eTexture2);

					}	

					//this essentially just checks if it is moving up and wether or not if it has attained max height. Sets platform activation to false.
					if (stages[currentStage]->platforms[x]->eSprite.getPosition().y <= stages[currentStage]->platforms[x]->maxHeight && stages[currentStage]->platforms[x]->move == 1) 
						{
							std::cout << "platform is at high limit, stopping" << std::endl;

							stages[currentStage]->platforms[x]->activatePlatform = false;
						}

				}
			

			//------------------------------------------------------------------------------------------------------------------------------------
			//reset switch	
			if (currentSwitch[0] >= 0 && stages[currentStage]->switches[currentSwitch[0]]->switchType == 2 && !stages[currentStage]->switches[currentSwitch[0]]->switchUsed)
			{
				std::cout << "reset switch activated" << std::endl;
				stages[currentStage]->switches[currentSwitch[0]]->switchUsed = true;
				stages[currentStage]->switches[currentSwitch[0]]->eSprite.setTexture(stages[currentStage]->switches[currentSwitch[0]]->eTexture2);
				for (int x=1; x<ENTITIES_MAX; x++)
				{
					entities[x]->cCircle.setPosition(entities[x]->eStartPos);
					entities[x]->isCreated = false;
					entities[x]->isCurrentEntity = false;
				}
				entities[0]->isCurrentEntity = true;
				currentEntityIndex = 0;
				entities[0]->cCircle.setPosition(stages[currentStage]->switches[currentSwitch[0]]->displacement);
				swapBackground(entities,stages);
			}


			sf::Vector2f dispVal;
			dispVal.x = 0;
			dispVal.y = 0; 
			//displacement switch
			if (currentSwitch[0] >= 0 && stages[currentStage]->switches[currentSwitch[0]]->switchType == 3)
			{
				std::cout << "displacement switch activated" << std::endl;
				if(entities[1]->isCreated && !displaced) 
					{
						entities[1]->cCircle.setPosition(stages[currentStage]->switches[currentSwitch[0]]->displacement);
						dispVal = stages[currentStage]->switches[currentSwitch[0]]->displacement;
						stages[currentStage]->switches[currentSwitch[0]]->eSprite.setTexture(stages[currentStage]->switches[currentSwitch[0]]->eTexture2);
						displacedSwitch = currentSwitch[0];
					}
				entities[1]->gCurrent = 0;
				displaced = true;
			}
			//------------------------------------------------------------------------------------------------------------------------------------


			//------------------------------------------------------------------------------------------------------------------------------------
			if (currentSwitch[0] >= 0 && stages[currentStage]->switches[currentSwitch[0]]->switchType == 4 && !disp)
			{
				std::cout << currentSwitch[0] << std::endl;
				std::cout << "platform dissappear switch activated" << std::endl;
				//stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->eSprite.setTexture(stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->disappear,true);
				if (stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->eSprite.getPosition().x <= 0) 
					{
						stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->eSprite.setPosition(stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->eStartPos);
						stages[currentStage]->switches[currentSwitch[0]]->eSprite.setTexture(stages[currentStage]->switches[currentSwitch[0]]->eTexture);
					}
				else
					{
						stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->eSprite.setPosition(-999,-999);
						stages[currentStage]->switches[currentSwitch[0]]->eSprite.setTexture(stages[currentStage]->switches[currentSwitch[0]]->eTexture2);

					}

				disp = true;
			}	
			//------------------------------------------------------------------------------------------------------------------------------------



			//------------------------------------------------------------------------------------------------------------------------------------

				for (int x=0; x < stages[currentStage]->platformCount; x++)
				{
					//std::cout << "holding" << std::endl;
					if (currentSwitch[0] >= 0 && stages[currentStage]->switches[currentSwitch[0]]->switchType == 5)
					{
						//entities[9]->activatePlatform = true;
						tSwitch = currentSwitch[0];
						if (tSwitch > 0 && stages[currentStage]->switches[tSwitch-1]->switchUsed)
						{
							for (int sw = 0; sw <= tSwitch; sw++)
							{
								if (sw<tSwitch)
								{
									//std::cout << "within" << std::endl;
									if (stages[currentStage]->switches[sw]->switchUsed) stages[currentStage]->switches[sw]->eSprite.setTexture(stages[currentStage]->switches[sw]->eTexture);

									if (stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->eSprite.getPosition().y >= 
										stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->eStartPos.y)
										stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->eSprite.move(0, -100*elapsedTime.asSeconds());

									stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->activatePlatform = false;
								}
							}
						}
						if (tSwitch+1 <= stages[currentStage]->switchCount-1 )
						{
							if (stages[currentStage]->switches[tSwitch+1]->switchUsed)
							{
								for (int sw=tSwitch; sw<=tSwitch+1; sw++)
								{
									if (sw>tSwitch)
									{
										if (stages[currentStage]->switches[sw]->switchUsed) stages[currentStage]->switches[sw]->eSprite.setTexture(stages[currentStage]->switches[sw]->eTexture);

										if (stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->eSprite.getPosition().y >= 
											stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->eStartPos.y)
											stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->eSprite.move(0, -100*elapsedTime.asSeconds());

										stages[currentStage]->platforms[stages[currentStage]->switches[sw]->platformToActivate]->activatePlatform = false;
									}
								}
							}
						}

						//std::cout << "TSWITCH: " << tSwitch << std::endl;
						stages[currentStage]->switches[currentSwitch[0]]->eSprite.setTexture(stages[currentStage]->switches[currentSwitch[0]]->eTexture2);
						if (stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->eSprite.getPosition().y 
							< stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->maxHeight) 
							stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->activatePlatform = true;


						else stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->activatePlatform = false;

						if (stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->activatePlatform && 
							stages[currentStage]->switches[currentSwitch[0]]->switchUsed) 
						{
							std::cout << "moving down" << std::endl;
							stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->eSprite.move(0, 100*elapsedTime.asSeconds());
						}
						 
						stages[currentStage]->switches[currentSwitch[0]]->switchUsed = true;
					}
					else if (stages[currentStage]->switches[tSwitch]->switchType == 5)
					{
						if (stages[currentStage]->platforms[x]->eSprite.getPosition().y >= stages[currentStage]->platforms[x]->eStartPos.y)  stages[currentStage]->platforms[x]->eSprite.move(0, -100*elapsedTime.asSeconds());
					}
				}

				//SWITCH 6
				for (int x=0; x<stages[currentStage]->platformCount; x++)
				{
					//checks if touching move Down switch then sets activate platform to true if so.
					if (currentSwitch[0] >= 0 && stages[currentStage]->switches[currentSwitch[0]]->switchType == 6)
					{
						stages[currentStage]->platforms[stages[currentStage]->switches[currentSwitch[0]]->platformToActivate]->activatePlatform = true;
						stages[currentStage]->switches[currentSwitch[0]]->eSprite.setTexture(stages[currentStage]->switches[currentSwitch[0]]->eTexture2);

					}	
					//checks if platform has attained mininmum hieght and is currently moving downwards, then sets activate platform to false
					if (stages[currentStage]->platforms[x]->eSprite.getPosition().y >= stages[currentStage]->platforms[x]->maxHeight && stages[currentStage]->platforms[x]->move == 2) 
						{
							std::cout << "platform is at low limit, stopping" << std::endl;
							stages[currentStage]->platforms[x]->activatePlatform = false;
						}


					//CHECKS IF PLATFORM IS MOVING DOWN OR MOVING UP AND MOVES ACCORDINGLY BASED ON SWITCHES 0 AND 6, AND THE BOOLEAN MOVEDOWN
					if (stages[currentStage]->platforms[x]->activatePlatform && stages[currentStage]->platforms[x]->move == 2)
					{
						std::cout << "moving down" << std::endl;
						stages[currentStage]->platforms[x]->eSprite.move(0,100*elapsedTime.asSeconds());
					}
					else if (stages[currentStage]->platforms[x]->activatePlatform && stages[currentStage]->platforms[x]->move == 1)
					{
						std::cout << "moving up " << std::endl;
						stages[currentStage]->platforms[x]->eSprite.move(0,-100*elapsedTime.asSeconds());
					}
				}
			

			//------------------------------------------------------------------------------------------------------------------------------------


			//------------------------------------------------------------------------------------------------------------------------------------
			if (currentSwitch[0] < 0) 
			{
				displaced = false;
				if (displacedSwitch!=-1) stages[currentStage]->switches[displacedSwitch]->eSprite.setTexture(stages[currentStage]->switches[displacedSwitch]->eTexture);
				disp = false;

			}
 			//------------------------------------------------------------------------------------------------------------------------------------
			//start with boule checking if touching breaed
			int currentBread = isTouchingBread(entities,stages,3);
			//check if boule is touching portal
			int currentPortal = isTouchingPortal(entities,stages,3);

			//if boule is touching the bread and portalLock is false
			if (currentBread >= 0 && !pLock)
			{
				portalTeleport = true; //set to true to activate teleportation to portal
				bLock = true; //set a lock so it can't go back to the bread through the portal
			}
			else portalTeleport = false;

			

			//if boule is touching the portal and breadLock is false
			if (currentPortal >=0 && !bLock)
			{
				breadTeleport = true; //set to true to activate teleportation to the bread
				pLock = true; //set a lock so it can't go back to the portal through the bread
			}
			else breadTeleport = false;





			//only if portal teleport is true and if boule is touching a bread, move it to a portal.
			if (portalTeleport && currentBread>=0)
			{
				for (int x=0; x<stages[currentStage]->portalCount; x++)
				{
					if (stages[currentStage]->portals[x]->portalType == currentBread)
					{
						entities[3]->cCircle.setPosition(stages[currentStage]->portals[x]->eSprite.getPosition());
					}
				}
			}



			//only if bread teleport is true and if boule is touching a portal, move boule to a bread
			if (breadTeleport && currentPortal>=0)
			{
					if (!entities[stages[currentStage]->portals[currentPortal]->portalType]->isCreated) 
						{
							mEntityMissing = currentPortal;
							mMissing = true;
						}
					else 
					{
						entities[3]->cCircle.setPosition(entities[stages[currentStage]->portals[currentPortal]->portalType]->cCircle.getPosition());
					}
				
			}

			//have to update ebounds since we modified posiion and need to check modified position in same frame
			updateEntityPosition(entities,stages);
			//re-check if boule is touching either bread or portal with updated position in frame
			currentBread = isTouchingBread(entities,stages,3);
			currentPortal = isTouchingPortal(entities,stages,3);


			//unlocking the locks
			if (currentPortal < 0 ) bLock = false;
			if (currentBread < 0 ) pLock = false;

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
			if (powerMetre <= 1) powerMetre+=0.04;
			else powerMetre = 0;
		}
	else 
		{
			//std::cout << "Setting drawmtre false" << std::endl;
			mDrawMetre=false;
			//if (!mIsLaunched) powerMetre=0;
		}
}

//checks if x is touching a portal, returns portal if touching, -1 if not.	
int Game::isTouchingPortal(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x)
{
	for (int a=0; a<stages[currentStage]->portalCount; a++)
	{
		 if (entities[x]->rightCircle[1] >= stages[currentStage]->portals[a]->eBounds.y &&
			entities[x]->rightCircle[1] <= stages[currentStage]->portals[a]->eBounds.y + stages[currentStage]->portals[a]->eTextureSize.y &&
			entities[x]->rightCircle[0] >= stages[currentStage]->portals[a]->eBounds.x &&
			entities[x]->rightCircle[0] <= stages[currentStage]->portals[a]->eBounds.x + stages[currentStage]->portals[a]->eTextureSize.x)
			{
				//entities[x]->cCircle.setPosition(stages[currentStage]->portals[a]->eBounds.x-entities[x]->cRadius, entities[x]->cCircle.getPosition().y);
				return a;
			}

		 if (entities[x]->bottomCircle[1] >= stages[currentStage]->portals[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->portals[a]->eBounds.y + stages[currentStage]->portals[a]->eTextureSize.y &&
			entities[x]->bottomRCircle[0] >= stages[currentStage]->portals[a]->eBounds.x &&
			entities[x]->bottomRCircle[0] <= stages[currentStage]->portals[a]->eBounds.x + stages[currentStage]->portals[a]->eTextureSize.x)
			{
				//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->portals[a]->eBounds.y-(entities[x]->cRadius));
				return a;
			}
		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->portals[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->portals[a]->eBounds.y + stages[currentStage]->portals[a]->eTextureSize.y &&
			entities[x]->bottomLCircle[0] >= stages[currentStage]->portals[a]->eBounds.x &&
			entities[x]->bottomLCircle[0] <= stages[currentStage]->portals[a]->eBounds.x + stages[currentStage]->portals[a]->eTextureSize.x)
			{
				//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->portals[a]->eBounds.y-(entities[x]->cRadius));
				return a;
			}
		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->portals[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->portals[a]->eBounds.y + stages[currentStage]->portals[a]->eTextureSize.y &&
			entities[x]->bottomLLCircle[0] >= stages[currentStage]->portals[a]->eBounds.x &&
			entities[x]->bottomLLCircle[0] <= stages[currentStage]->portals[a]->eBounds.x + stages[currentStage]->portals[a]->eTextureSize.x)
			{
				//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->portals[a]->eBounds.y-(entities[x]->cRadius));
				return a;
			}
		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->portals[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->portals[a]->eBounds.y + stages[currentStage]->portals[a]->eTextureSize.y &&
			entities[x]->bottomRRCircle[0] >= stages[currentStage]->portals[a]->eBounds.x &&
			entities[x]->bottomRRCircle[0] <= stages[currentStage]->portals[a]->eBounds.x + stages[currentStage]->portals[a]->eTextureSize.x)
			{
				//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->portals[a]->eBounds.y-(entities[x]->cRadius));
				return a;
			}
		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->portals[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->portals[a]->eBounds.y + stages[currentStage]->portals[a]->eTextureSize.y &&
			entities[x]->bottomCircle[0] >= stages[currentStage]->portals[a]->eBounds.x &&
			entities[x]->bottomCircle[0] <= stages[currentStage]->portals[a]->eBounds.x + stages[currentStage]->portals[a]->eTextureSize.x)
			{
				//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->portals[a]->eBounds.y-entities[x]->cRadius);
				return a;
			}

		else if (entities[x]->leftCircle[1] >= stages[currentStage]->portals[a]->eBounds.y &&
			entities[x]->leftCircle[1] <= stages[currentStage]->portals[a]->eBounds.y + stages[currentStage]->portals[a]->eTextureSize.y &&
			entities[x]->leftCircle[0] >= stages[currentStage]->portals[a]->eBounds.x &&
			entities[x]->leftCircle[0] <= stages[currentStage]->portals[a]->eBounds.x + stages[currentStage]->portals[a]->eTextureSize.x)
			{
				//entities[x]->cCircle.setPosition(stages[currentStage]->portals[a]->eBounds.x+stages[currentStage]->portals[a]->eTextureSize.x+entities[x]->cRadius, entities[x]->cCircle.getPosition().y);
				return a;
			}
		else if (entities[x]->topCircle[1] >= stages[currentStage]->portals[a]->eBounds.y &&
			entities[x]->topCircle[1] <= stages[currentStage]->portals[a]->eBounds.y + stages[currentStage]->portals[a]->eTextureSize.y &&
			entities[x]->topCircle[0] >= stages[currentStage]->portals[a]->eBounds.x &&
			entities[x]->topCircle[0] <= stages[currentStage]->portals[a]->eBounds.x + stages[currentStage]->portals[a]->eTextureSize.x)
			{

				//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->portals[a]->eBounds.y+entities[x]->cRadius);
				//entities[x]->gCurrent = 0;	
				return a;
			}
	}
	return -1;
}

int Game::isTouchingBread(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x)
{
	for (int a=0; a<ENTITIES_MAX; a++)
	{
		if (a==x) continue;
		if (entities[x]->rightCircle[1] >= entities[a]->eBounds.y &&
			entities[x]->rightCircle[1] <= entities[a]->eBounds.y + entities[a]->eTextureSize.y &&
			entities[x]->rightCircle[0] >= entities[a]->eBounds.x &&
			entities[x]->rightCircle[0] <= entities[a]->eBounds.x + entities[a]->eTextureSize.x)
		{
			return a;
		}
		else if (entities[x]->bottomCircle[1] >= entities[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= entities[a]->eBounds.y + entities[a]->eTextureSize.y &&
			entities[x]->bottomLCircle[0] >= entities[a]->eBounds.x &&
			entities[x]->bottomLCircle[0] <= entities[a]->eBounds.x + entities[a]->eTextureSize.x)
		{
			return a;
		}
		else if (entities[x]->bottomCircle[1] >= entities[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= entities[a]->eBounds.y + entities[a]->eTextureSize.y &&
			entities[x]->bottomRCircle[0] >= entities[a]->eBounds.x &&
			entities[x]->bottomRCircle[0] <= entities[a]->eBounds.x + entities[a]->eTextureSize.x)
		{
			return a;
		}
		else if (entities[x]->bottomCircle[1] >= entities[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= entities[a]->eBounds.y + entities[a]->eTextureSize.y &&
			entities[x]->bottomRRCircle[0] >= entities[a]->eBounds.x &&
			entities[x]->bottomRRCircle[0] <= entities[a]->eBounds.x + entities[a]->eTextureSize.x)
		{
			return a;
		}
		else if (entities[x]->bottomCircle[1] >= entities[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= entities[a]->eBounds.y + entities[a]->eTextureSize.y &&
			entities[x]->bottomLLCircle[0] >= entities[a]->eBounds.x &&
			entities[x]->bottomLLCircle[0] <= entities[a]->eBounds.x + entities[a]->eTextureSize.x)
		{
			return a;
		}
		else if (entities[x]->leftCircle[1] >= entities[a]->eBounds.y &&
			entities[x]->leftCircle[1] <= entities[a]->eBounds.y + entities[a]->eTextureSize.y &&
			entities[x]->leftCircle[0] >= entities[a]->eBounds.x &&
			entities[x]->leftCircle[0] <= entities[a]->eBounds.x + entities[a]->eTextureSize.x)
		{
			return a;
		}
		else if (entities[x]->topCircle[1] >= entities[a]->eBounds.y &&
			entities[x]->topCircle[1] <= entities[a]->eBounds.y + entities[a]->eTextureSize.y &&
			entities[x]->topCircle[0] >= entities[a]->eBounds.x &&
			entities[x]->topCircle[0] <= entities[a]->eBounds.x + entities[a]->eTextureSize.x)
		{
			return a;
		}
		else if (entities[x]->bottomCircle[1] >= entities[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= entities[a]->eBounds.y + entities[a]->eTextureSize.y &&
			entities[x]->bottomCircle[0] >= entities[a]->eBounds.x &&
			entities[x]->bottomCircle[0] <= entities[a]->eBounds.x + entities[a]->eTextureSize.x)
		{
			return a;
		}

	}	
	return -1;
}

bool Game::isTouchingRotiSurface(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x)
{
	for (int a=0; a<stages[currentStage]->platformCount; a++)
	{
		if (entities[x]->topCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->topCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->topCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->topCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{

				//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y+entities[x]->cRadius);
				std::cout << "t circle" << std::endl;
				entities[x]->gCurrent = 0;	
				return true;
			}

 		if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->bottomRCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->bottomRCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				std::cout << "br circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}
		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->bottomLCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->bottomLCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				std::cout << "bl circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}
		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->bottomLLCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->bottomLLCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				std::cout << "bll circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}

		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->bottomRRCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->bottomRRCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				std::cout << "brr circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}


		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->bottomCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->bottomCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				std::cout << "b circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-entities[x]->cRadius);
				return true;
			}
		
	}


	for (int a=0; a<stages[currentStage]->lineCount; a++)
	{

		 if (entities[x]->topCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->topCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->topCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->topCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{

				//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y+entities[x]->cRadius);
				std::cout << "t circle" << std::endl;
				entities[x]->gCurrent = 0;	
				return true;
			}

		 if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->bottomRCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->bottomRCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				std::cout << "br circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}
		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->bottomLCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->bottomLCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				std::cout << "bl circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}
		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->bottomLLCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->bottomLLCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				std::cout << "bll circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}

		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->bottomRRCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->bottomRRCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				std::cout << "brr circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}

		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->bottomCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->bottomCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				std::cout << "b circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-entities[x]->cRadius);
				return true;
			}

	}

	return false;
	
}



bool Game::isTouchingSurface(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x)
{
	
	for (int a=0; a<stages[currentStage]->platformCount; a++)
	{

		 if (entities[x]->rightCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->rightCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->rightCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->rightCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				std::cout << "r circle" << std::endl;
				entities[x]->cCircle.setPosition(stages[currentStage]->platforms[a]->eBounds.x-entities[x]->cRadius, entities[x]->eBounds.y+entities[x]->cRadius);
				return true;
			}
		else if (entities[x]->leftCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->leftCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->leftCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->leftCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				std::cout << "l circle" << std::endl;
				entities[x]->cCircle.setPosition(stages[currentStage]->platforms[a]->eBounds.x+stages[currentStage]->platforms[a]->eTextureSize.x+entities[x]->cRadius, entities[x]->eBounds.y+entities[x]->cRadius);
				return true;
			}
		if (entities[x]->topCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->topCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->topCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->topCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{

				//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y+entities[x]->cRadius);
				std::cout << "t circle" << std::endl;
				entities[x]->gCurrent = 0;	
				return true;
			}

 		if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->bottomRCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->bottomRCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				std::cout << "br circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}
		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->bottomLCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->bottomLCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				std::cout << "bl circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}
		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->bottomLLCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->bottomLLCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				std::cout << "bll circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}

		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->bottomRRCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->bottomRRCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				std::cout << "brr circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}


		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->bottomCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->bottomCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				std::cout << "b circle" << std::endl;
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-entities[x]->cRadius);
				return true;
			}
		
	}


	for (int a=0; a<stages[currentStage]->lineCount; a++)
	{


		if (entities[x]->rightCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->rightCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->rightCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->rightCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(stages[currentStage]->lines[a]->eBounds.x-entities[x]->cRadius, entities[x]->eBounds.y+entities[x]->cRadius);
				return true;
			}

		else if (entities[x]->leftCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->leftCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->leftCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->leftCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(stages[currentStage]->lines[a]->eBounds.x+stages[currentStage]->lines[a]->eTextureSize.x+entities[x]->cRadius, entities[x]->eBounds.y+entities[x]->cRadius);
				return true;
			}
		 if (entities[x]->topCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->topCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->topCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->topCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{

				//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y+entities[x]->cRadius);
				entities[x]->gCurrent = 0;	
				return true;
			}

		 if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->bottomRCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->bottomRCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}
		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->bottomLCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->bottomLCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}
		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->bottomLLCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->bottomLLCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
				return true;
			}

		else if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->bottomRRCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->bottomRRCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
				return true;
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



bool Game::rightCircleCollision(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x)
{
	for (int a=0; a<stages[currentStage]->lineCount; a++)
	{
		if (entities[x]->rightCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->rightCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->rightCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->rightCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(stages[currentStage]->lines[a]->eBounds.x-entities[x]->cRadius, entities[x]->eBounds.y+entities[x]->cRadius);
				return true;
			}
	}

	for (int a=0; a<stages[currentStage]->platformCount; a++)
	{
		if (entities[x]->rightCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->rightCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->rightCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->rightCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(stages[currentStage]->platforms[a]->eBounds.x-entities[x]->cRadius, entities[x]->eBounds.y+entities[x]->cRadius);
				return true;
			}
	}
	return false;
}

bool Game::leftCircleCollision(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x)
{
	for (int a=0; a<stages[currentStage]->lineCount; a++)
	{
		if (entities[x]->leftCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
			entities[x]->leftCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
			entities[x]->leftCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
			entities[x]->leftCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(stages[currentStage]->lines[a]->eBounds.x+stages[currentStage]->lines[a]->eTextureSize.x+entities[x]->cRadius, entities[x]->eBounds.y+entities[x]->cRadius);
				return true;
			}
	}

	for (int a=0; a<stages[currentStage]->platformCount; a++)
	{
		if (entities[x]->leftCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
			entities[x]->leftCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
			entities[x]->leftCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
			entities[x]->leftCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
			{
				entities[x]->cCircle.setPosition(stages[currentStage]->platforms[a]->eBounds.x+stages[currentStage]->platforms[a]->eTextureSize.x+entities[x]->cRadius, entities[x]->eBounds.y+entities[x]->cRadius);
				return true;
			}
	}
	return false;
}

//returns true if bottom of circle is touching stuff.
//NEED +2 so it doesn't "mini bounce"
bool Game::bottomCircleCollision(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x)
{
	for (int a=0; a<stages[currentStage]->lineCount; a++)
		{
			if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
				entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
				entities[x]->bottomCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
				entities[x]->bottomCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
				{
					entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-entities[x]->cRadius);
					return true;
				}
			if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
				entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
				entities[x]->bottomRCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
				entities[x]->bottomRCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
				{
					entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
					return true;
				}
			if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
				entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
				entities[x]->bottomRRCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
				entities[x]->bottomRRCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
				{
					entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
					return true;
				}
			if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
				entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
				entities[x]->bottomLLCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
				entities[x]->bottomLLCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
				{
					entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
					return true;
				}
			if (entities[x]->bottomCircle[1] >= stages[currentStage]->lines[a]->eBounds.y &&
				entities[x]->bottomCircle[1] <= stages[currentStage]->lines[a]->eBounds.y + stages[currentStage]->lines[a]->eTextureSize.y &&
				entities[x]->bottomLCircle[0] >= stages[currentStage]->lines[a]->eBounds.x &&
				entities[x]->bottomLCircle[0] <= stages[currentStage]->lines[a]->eBounds.x + stages[currentStage]->lines[a]->eTextureSize.x)
				{
					entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
					return true;
				}
		}

	for (int a=0; a<stages[currentStage]->platformCount; a++)
		{
			if ( entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
				entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
				entities[x]->bottomCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
				entities[x]->bottomCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
				{
 					 entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-entities[x]->cRadius+2);
					return true;
				}
			if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
				entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
				entities[x]->bottomRCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
				entities[x]->bottomRCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
				{
					entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-entities[x]->cRadius+2);
					return true;
				}
			if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
				entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
				entities[x]->bottomRRCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
				entities[x]->bottomRRCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
				{
					entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-entities[x]->cRadius+2);
					return true;
				}
			if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
				entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
				entities[x]->bottomLLCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
				entities[x]->bottomLLCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
				{
					entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-entities[x]->cRadius+2);
					return true;
				}
			if (entities[x]->bottomCircle[1] >= stages[currentStage]->platforms[a]->eBounds.y &&
				entities[x]->bottomCircle[1] <= stages[currentStage]->platforms[a]->eBounds.y + stages[currentStage]->platforms[a]->eTextureSize.y &&
				entities[x]->bottomLCircle[0] >= stages[currentStage]->platforms[a]->eBounds.x &&
				entities[x]->bottomLCircle[0] <= stages[currentStage]->platforms[a]->eBounds.x + stages[currentStage]->platforms[a]->eTextureSize.x)
				{
					entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y-entities[x]->cRadius+2);
					return true;
				}
		}

	return false;
}


void Game::checkGravity(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int character)
{
		bool isOnGround = true;
		//need this to reset gravity if touching a surface
		if ( (entities[character]->cCircle.getPosition().y >=  785-entities[character]->cRadius) )  NULL;
		//else if (isTouchingSurface(entities, stages, character)) NULL;
		else if (bottomCircleCollision(entities,stages,character))
		{
			NULL;
		} 
		else 
		{
			isOnGround = false;
			//std::cout << "gravity at work on: " << character << std::endl;
			if ( !pauseMenu[currentStage]->isPaused) entities[character]->cCircle.move(0,entities[character]->gCurrent+entities[character]->weight);
			//else entities[character]->gCurrent = g;
		}


		if (isOnGround) entities[character]->gCurrent = g;
		checkBounds(entities);

}




//left side return = 2;
//right side return = 3;
//ambiguous return = 1;
//not touching return = 0;
void Game::checkHitting(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int airborneEntity, bool isSwitch, int* data)
{

	if (isSwitch)
	{
		/*
		for (int x=0; x<stages[currentStage]->switchCount; x++)
		{

			if (
			(((entities[airborneEntity]->eBounds.x <= stages[currentStage]->switches[x]->eBounds.x+stages[currentStage]->switches[x]->eTextureSize.x) &&
			 (entities[airborneEntity]->eBounds.x >= stages[currentStage]->switches[x]->eBounds.x)) && 
			((entities[airborneEntity]->eBounds.y+entities[airborneEntity]->eTextureSize.y >= stages[currentStage]->switches[x]->eBounds.y) && //+8 is give/take value
			 (entities[airborneEntity]->eBounds.y <= stages[currentStage]->switches[x]->eBounds.y+stages[currentStage]->switches[x]->eTextureSize.y)))
			)
			{
				data[0]=x;
				std::cout << x << std::endl;
				return; //returns which switch it is touching
			}

			else if	(
			((entities[airborneEntity]->eBounds.x + entities[airborneEntity]->eTextureSize.x >= stages[currentStage]->switches[x]->eBounds.x) &&
			 (entities[airborneEntity]->eBounds.x + entities[airborneEntity]->eTextureSize.x <= stages[currentStage]->switches[x]->eBounds.x+stages[currentStage]->switches[x]->eTextureSize.x)) &&
			((entities[airborneEntity]->eBounds.y + entities[airborneEntity]->eTextureSize.y >= stages[currentStage]->switches[x]->eBounds.y+8) &&
			 (entities[airborneEntity]->eBounds.y <= stages[currentStage]->switches[x]->eBounds.y+stages[currentStage]->switches[x]->eTextureSize.y-8))
			)	   
			{
				data[0]=x;
				std::cout << x << std::endl;
				return; //returns which switch it is touching
			}

		}
		*/
		for (int a=0; a<stages[currentStage]->switchCount; a++)
		{
			if (entities[airborneEntity]->bottomCircle[1] >= stages[currentStage]->switches[a]->eBounds.y &&
				entities[airborneEntity]->bottomCircle[1] <= stages[currentStage]->switches[a]->eBounds.y + stages[currentStage]->switches[a]->eTextureSize.y &&
				entities[airborneEntity]->bottomRCircle[0] >= stages[currentStage]->switches[a]->eBounds.x &&
				entities[airborneEntity]->bottomRCircle[0] <= stages[currentStage]->switches[a]->eBounds.x + stages[currentStage]->switches[a]->eTextureSize.x)
				{
					//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
					std::cout << "brc" << std::endl;
					data[0] = a;
					return;
				}
			else if (entities[airborneEntity]->bottomCircle[1] >= stages[currentStage]->switches[a]->eBounds.y &&
				entities[airborneEntity]->bottomCircle[1] <= stages[currentStage]->switches[a]->eBounds.y + stages[currentStage]->switches[a]->eTextureSize.y &&
				entities[airborneEntity]->bottomLCircle[0] >= stages[currentStage]->switches[a]->eBounds.x &&
				entities[airborneEntity]->bottomLCircle[0] <= stages[currentStage]->switches[a]->eBounds.x + stages[currentStage]->switches[a]->eTextureSize.x)
				{
					//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
					std::cout << "blc" << std::endl;
					data[0] = a;
					return;
				}
			else if (entities[airborneEntity]->bottomCircle[1] >= stages[currentStage]->switches[a]->eBounds.y &&
				entities[airborneEntity]->bottomCircle[1] <= stages[currentStage]->switches[a]->eBounds.y + stages[currentStage]->switches[a]->eTextureSize.y &&
				entities[airborneEntity]->bottomLLCircle[0] >= stages[currentStage]->switches[a]->eBounds.x &&
				entities[airborneEntity]->bottomLLCircle[0] <= stages[currentStage]->switches[a]->eBounds.x + stages[currentStage]->switches[a]->eTextureSize.x)
				{
					//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
					std::cout << "bllc" << std::endl;
					data[0] = a;
					return;
				}

			else if (entities[airborneEntity]->bottomCircle[1] >= stages[currentStage]->switches[a]->eBounds.y &&
				entities[airborneEntity]->bottomCircle[1] <= stages[currentStage]->switches[a]->eBounds.y + stages[currentStage]->switches[a]->eTextureSize.y &&
				entities[airborneEntity]->bottomRRCircle[0] >= stages[currentStage]->switches[a]->eBounds.x &&
				entities[airborneEntity]->bottomRRCircle[0] <= stages[currentStage]->switches[a]->eBounds.x + stages[currentStage]->switches[a]->eTextureSize.x)
				{
					//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-(entities[x]->cRadius));
					std::cout << "brrc" << std::endl;
					data[0] = a;
					return;
				}

			else if (entities[airborneEntity]->bottomCircle[1] >= stages[currentStage]->switches[a]->eBounds.y &&
				entities[airborneEntity]->bottomCircle[1] <= stages[currentStage]->switches[a]->eBounds.y + stages[currentStage]->switches[a]->eTextureSize.y &&
				entities[airborneEntity]->bottomCircle[0] >= stages[currentStage]->switches[a]->eBounds.x &&
				entities[airborneEntity]->bottomCircle[0] <= stages[currentStage]->switches[a]->eBounds.x + stages[currentStage]->switches[a]->eTextureSize.x)
				{
					//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->lines[a]->eBounds.y-entities[x]->cRadius);
					std::cout << "bc" << std::endl;
					data[0] = a;
					return;
				}
			if (entities[airborneEntity]->rightCircle[1] >= stages[currentStage]->switches[a]->eBounds.y &&
				entities[airborneEntity]->rightCircle[1] <= stages[currentStage]->switches[a]->eBounds.y + stages[currentStage]->switches[a]->eTextureSize.y &&
				entities[airborneEntity]->rightCircle[0] >= stages[currentStage]->switches[a]->eBounds.x &&
				entities[airborneEntity]->rightCircle[0] <= stages[currentStage]->switches[a]->eBounds.x + stages[currentStage]->switches[a]->eTextureSize.x)
				{
					//entities[x]->cCircle.setPosition(stages[currentStage]->lines[a]->eBounds.x-entities[x]->cRadius, entities[x]->eBounds.y+entities[x]->cRadius);
					std::cout << "rc" << std::endl;
					std::cout << stages[currentStage]->switches[a]->eBounds.y << "," << stages[currentStage]->switches[a]->eBounds.y+stages[currentStage]->switches[a]->eTextureSize.y << std::endl;
					data[0] = a;
					return;
				}

			else if (entities[airborneEntity]->leftCircle[1] >= stages[currentStage]->switches[a]->eBounds.y &&
				entities[airborneEntity]->leftCircle[1] <= stages[currentStage]->switches[a]->eBounds.y + stages[currentStage]->switches[a]->eTextureSize.y &&
				entities[airborneEntity]->leftCircle[0] >= stages[currentStage]->switches[a]->eBounds.x &&
				entities[airborneEntity]->leftCircle[0] <= stages[currentStage]->switches[a]->eBounds.x + stages[currentStage]->switches[a]->eTextureSize.x)
				{
					//entities[x]->cCircle.setPosition(stages[currentStage]->lines[a]->eBounds.x+stages[currentStage]->lines[a]->eTextureSize.x+entities[x]->cRadius, entities[x]->eBounds.y+entities[x]->cRadius);
					std::cout << "lc" << std::endl;
					data[0] = a;
					return;
				}
			 if (entities[airborneEntity]->topCircle[1] >= stages[currentStage]->switches[a]->eBounds.y &&
				entities[airborneEntity]->topCircle[1] <= stages[currentStage]->switches[a]->eBounds.y + stages[currentStage]->switches[a]->eTextureSize.y &&
				entities[airborneEntity]->topCircle[0] >= stages[currentStage]->switches[a]->eBounds.x &&
				entities[airborneEntity]->topCircle[0] <= stages[currentStage]->switches[a]->eBounds.x + stages[currentStage]->switches[a]->eTextureSize.x)
				{

					//entities[x]->cCircle.setPosition(entities[x]->cCircle.getPosition().x , stages[currentStage]->platforms[a]->eBounds.y+entities[x]->cRadius);
					//entities[x]->gCurrent = 0;	
					std::cout << "tc" << std::endl;
					data[0] = a;
					return;
				}

		
		}

		data[0]=-1;
		return;
	}

	for (int x=0; x< stages[currentStage]->lineCount; x++)
	{


		if ( ceil(entities[airborneEntity]->rightCircle[1]) >= stages[currentStage]->lines[x]->eBounds.y &&
			ceil(entities[airborneEntity]->rightCircle[1]) <= stages[currentStage]->lines[x]->eBounds.y + stages[currentStage]->lines[x]->eTextureSize.y &&
			ceil(entities[airborneEntity]->rightCircle[0]) >= stages[currentStage]->lines[x]->eBounds.x &&
			ceil(entities[airborneEntity]->rightCircle[0]) <= stages[currentStage]->lines[x]->eBounds.x + stages[currentStage]->lines[x]->eTextureSize.x)
			{
				//entities[x]->cCircle.setPosition(stages[currentStage]->lines[a]->eBounds.x-entities[x]->cRadius, entities[x]->cCircle.getPosition().y);
				data[0] = x;
				data[1] = 3;
				//make third index which tells us either line [0] or platform [1];
				data[2]=0;
				return;
			}
		if (ceil(entities[airborneEntity]->leftCircle[1]) >= stages[currentStage]->lines[x]->eBounds.y &&
			ceil(entities[airborneEntity]->leftCircle[1]) <= stages[currentStage]->lines[x]->eBounds.y + stages[currentStage]->lines[x]->eTextureSize.y &&
			ceil(entities[airborneEntity]->leftCircle[0]) >= stages[currentStage]->lines[x]->eBounds.x &&
			ceil(entities[airborneEntity]->leftCircle[0]) <= stages[currentStage]->lines[x]->eBounds.x + stages[currentStage]->lines[x]->eTextureSize.x)
			{
				//entities[x]->cCircle.setPosition(stages[currentStage]->lines[a]->eBounds.x+stages[currentStage]->lines[a]->eTextureSize.x+entities[x]->cRadius, entities[x]->cCircle.getPosition().y);
				data[0] = x;
				data[1] = 2;
				data[2] = 0;
				return;
			}

	}

	for (int x=0; x< stages[currentStage]->platformCount; x++)
	{
		
		if ( ceil(entities[airborneEntity]->rightCircle[1]) >= stages[currentStage]->platforms[x]->eBounds.y &&
			ceil(entities[airborneEntity]->rightCircle[1]) <= stages[currentStage]->platforms[x]->eBounds.y + stages[currentStage]->platforms[x]->eTextureSize.y &&
			ceil(entities[airborneEntity]->rightCircle[0]) >= stages[currentStage]->platforms[x]->eBounds.x &&
			ceil(entities[airborneEntity]->rightCircle[0]) <= stages[currentStage]->platforms[x]->eBounds.x + stages[currentStage]->platforms[x]->eTextureSize.x)
			{
				//entities[x]->cCircle.setPosition(stages[currentStage]->lines[a]->eBounds.x-entities[x]->cRadius, entities[x]->cCircle.getPosition().y);
				data[0] = x;
				data[1] = 3;
				data[2] = 1;
				return;
			}
		if (ceil(entities[airborneEntity]->leftCircle[1]) >= stages[currentStage]->platforms[x]->eBounds.y &&
			ceil(entities[airborneEntity]->leftCircle[1]) <= stages[currentStage]->platforms[x]->eBounds.y + stages[currentStage]->platforms[x]->eTextureSize.y &&
			ceil(entities[airborneEntity]->leftCircle[0]) >= stages[currentStage]->platforms[x]->eBounds.x &&
			ceil(entities[airborneEntity]->leftCircle[0]) <= stages[currentStage]->platforms[x]->eBounds.x + stages[currentStage]->platforms[x]->eTextureSize.x)
			{
				//entities[x]->cCircle.setPosition(stages[currentStage]->lines[a]->eBounds.x+stages[currentStage]->lines[a]->eTextureSize.x+entities[x]->cRadius, entities[x]->cCircle.getPosition().y);
				data[0] = x;
				data[1] = 2;
				data[2] = 1;
				return;
			}

	}


	data[0]=-1;
	data[1]=0;
	data[2]=-1;
	return;
}





void Game::trajectory(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX])
{
	sf::Vector2f motion(0.f, 0.f);
	double xDirection = mArrow.getPosition().x - traj_pos.x;
	double yDirection = mArrow.getPosition().y - traj_pos.y;
	if (debug) std::cout << "arrow pos: " <<  mArrow.getPosition().x << " , " <<  mArrow.getPosition().y << std::endl;

	if (mIsLaunched && !(entities[shotChooser]->isCreated))
	{
		motion.y += yDirection*(powerMetre)*30;
		motion.x += xDirection*(powerMetre)*30;
		if (debug) std::cout << "motion vector x: " << motion.x << ", y: " << motion.y << std::endl;
		if (debug) std::cout << "traj elapsed time: " << elapsedTime.asSeconds() << std::endl;
		if (!pauseMenu[currentStage]->isPaused) entities[shotChooser]->cCircle.move(motion * elapsedTime.asSeconds());
	}
}



void Game::processEvents(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX])
{
	entitySelector(entities);
	sf::Event event;
	if (!pauseMenu[currentStage]->isPaused)
	{
		activateRotiPowerAlpha(elapsedTime, entities,stages);
		activateBoulePower(entities,stages,elapsedTime);
	}

	
		while (mWindow->pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::KeyPressed:

					handlePlayerInput(event.key.code, true);
					std::cout << "after hpi" << std::endl;
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
						case sf::Keyboard::L:
							currentStage+=1;
							break;
							//powerMetre=0;

					}
					handlePlayerInput(event.key.code, false);
					break;

				case sf::Event::MouseMoved:
					break;


				case sf::Event::MouseButtonPressed:
					std::cout << "mouse button pressed" << std::endl;
					activateAnpanPower(entities,stages);
					if (event.mouseButton.button == sf::Mouse::Right && currentEntityIndex==3 ) 
						{
							swapBackground(entities,stages);
						}
					break;

				case sf::Event::MouseButtonReleased:
	    				if (event.mouseButton.button == sf::Mouse::Right)
	    				{
	    					activateRotiPowerBeta(elapsedTime,entities,stages);
	    				} 
					break;

				case sf::Event::Closed:
					mWindow->close();
					break;
			}
		}
	
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (!pauseMenu[currentStage]->isPaused)
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
		if (key == sf::Keyboard::M)
		{
			music[currSong]->stop();
			currSong+=1;
			if (currSong >= 5) currSong = 0;
		}
	}
	if (key == sf::Keyboard::P)
	{
		std::cout << "p pressed main" << std::endl;
		if (pauseMenu[currentStage]->isPaused) 
			{
				std::cout << "pause is false" << std::endl;
				pauseMenu[currentStage]->isPaused = false;
			}

		else
		{
			std::cout << "pause is true " << std::endl;
			pauseMenu[currentStage]->isPaused = true;
		} 
		if (pauseMenuRun() == 1) handlePlayerInput(sf::Keyboard::P, true);

	}
}

int Game::pauseMenuRun()
{
	if (pauseMenu[currentStage]->isPaused)
	{
	    while (pauseMenu[currentStage]->win->isOpen())
	    {
	    	//std::cout << "iteration in pause: " << itrnum << std::endl;
		    pauseMenu[currentStage]->render();

		    elapsedTime = clock.restart();
			timeSinceLastUpdate += elapsedTime;

			if (timeSinceLastUpdate > TimePerFrame) timeSinceLastUpdate -= TimePerFrame;

		    sf::Event event2;
		    while (pauseMenu[currentStage]->win->pollEvent(event2))
		    {
		    	switch (event2.type)
		    	{
		    		case sf::Event::KeyPressed:
		    			if (event2.key.code == sf::Keyboard::Escape)
		    			{
		    				//pauseMenu[currentStage]->isPaused = false;
		    				pauseMenu[currentStage]->win->close();
		    			}
		    			if (event2.key.code == sf::Keyboard::P) 
		    			{
		    				//pauseMenu[currentStage]->isPaused = false;
		    				negateGravity = false;
		    				return 0;
		    			}
		    			break;

					case sf::Event::Closed:
		    			pauseMenu[currentStage]->isPaused = false;
						pauseMenu[currentStage]->win->close();
						break;

		    		case sf::Event::MouseButtonPressed:
		    			if (pauseMenu[currentStage]->isTouchingOption() == 0)
		    			{
		    				std::cout << "mbp in pause " << std::endl;
		    				negateGravity = false;
		    				return 1;
		    			}
		    			if (pauseMenu[currentStage]->isTouchingOption() == 1)
		    			{
		    				pauseMenu[currentStage]->win->close();
		    			}
		    			break;
		    	}
		    }
    	}

	}
	return 0;

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

	if (bouleActivated && currentEntityIndex!=3) swapBackground(entities,stages);

	if (mIsSpaceBar && currentEntityIndex == 0) //Space only works, if TheBaker is selected.
	{
		std::cout << "creation check: " << currentlySelected%3 << ", " << shotChooser << ", " << positionLock << std::endl;
		if (currentlySelected%3 == 1 && !entities[1]->isCreated && !positionLock)
		{

			if (shotChooser != 1) currentPoints+=1;
			entities[1]->create();
			entities[1]->cCircle.setPosition(entities[0]->cCircle.getPosition().x, entities[0]->cCircle.getPosition().y);
			shotChooser = 1;
		}

		else if (currentlySelected%3 == 2 && !entities[2]->isCreated && !positionLock)
		{
			if (shotChooser != 2) currentPoints+=1;
			entities[2]->create();
			entities[2]->cCircle.setPosition(entities[0]->cCircle.getPosition());
			shotChooser = 2;
		}
		
		else if (currentlySelected%3 == 0 && !entities[3]->isCreated && !positionLock)
		{
			if (shotChooser != 3) currentPoints+=1;
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
		else if (entities[currentEntityIndex]->canMoveDown)
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
		entities[0]->cCircle.setPosition(mMousePos.x,mMousePos.y);
		entities[1]->cCircle.setPosition(mMousePos.x,mMousePos.y);
	}

	entities[currentEntityIndex]->cCircle.move(movement * elapsedTime.asSeconds());
	entities[currentEntityIndex]->cCircle.rotate(rotateangle*elapsedTime.asSeconds());
	
	
}



void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;
	currentStageTime = stageTime.getElapsedTime();
	stageTimeText.setString("Elapsed Time: " + toString(currentStageTime.asSeconds()));
	currentPointsText.setString("Current points: " + toString(currentPoints));


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
	mWindow->clear();	
	mWindow->draw(stages[currentStage]->background);
	mWindow->draw(mStatisticsText);
	
	if (currentlySelected%3 == 1) 
	{
		entities[1]->cCircle.setOutlineThickness(5);
		entities[1]->cCircle.setOutlineColor(sf::Color(60, 129, 113));
		mWindow->draw(entities[1]->eSprite2);
		entities[2]->cCircle.setOutlineThickness(0);
		entities[3]->cCircle.setOutlineThickness(0);
	}
	else if (currentlySelected%3 == 2) 
	{
		entities[2]->cCircle.setOutlineThickness(5);
		entities[2]->cCircle.setOutlineColor(sf::Color(60, 129, 113));
		mWindow->draw(entities[2]->eSprite2);
		entities[1]->cCircle.setOutlineThickness(0);
		entities[3]->cCircle.setOutlineThickness(0);

	}
	else
	{
		entities[3]->cCircle.setOutlineThickness(5);
		entities[3]->cCircle.setOutlineColor(sf::Color(60, 129, 113));
		mWindow->draw(entities[3]->eSprite2);
		entities[1]->cCircle.setOutlineThickness(0);
		entities[2]->cCircle.setOutlineThickness(0);

	}
	
	for (int x=0; x<ENTITIES_MAX; x++) 
	{
		mWindow->draw(entities[x]->cCircle);
		//else mWindow->draw(entities[x]->eSprite);
	}


	for (int x=0; x<stages[currentStage]->lineCount; x++)
	{
		mWindow->draw(stages[currentStage]->lines[x]->eSprite);
	}

	for (int x=0; x<stages[currentStage]->platformCount; x++)
	{
		mWindow->draw(stages[currentStage]->platforms[x]->eSprite);
	}

	for (int x=0; x<stages[currentStage]->switchCount; x++)
	{
		if (bouleActivated) mWindow->draw(stages[currentStage]->switches[x]->eSprite);
	}

	for (int x=0; x<stages[currentStage]->portalCount; x++)
	{
		if (bouleActivated) mWindow->draw(stages[currentStage]->portals[x]->eSprite);
	}
	mWindow->draw(stages[currentStage]->oven->eSprite);
	mPowerGaugeMetre.setScale(powerMetre,powerMetre);
	if (mDrawMetre && currentEntityIndex == 0)
	{
		mWindow->draw(mPowerGaugeShell);
		mWindow->draw(mPowerGaugeMetre);
	}
	if (mDrawPostScreen) 
	{
		postScreenText.setPosition(422,300);
		postScreenText.setString(toString(currentPoints) + "\n\n\n" + "50+(50-" + toString(currentPoints) + ") = " + toString(50+(50-currentPoints)));
		mWindow->draw(postScreen);
		mWindow->draw(postScreenText);
	}

	mWindow->draw(currentPointsText);
	mWindow->draw(stageTimeText);
	//for (int x=7; x<ENTITIES_MAX; x++) mWindow->draw(entities[x]->eSprite);


	//mWindow->draw(entities[9]->eSprite);
	//mWindow->draw(entities[10]->eSprite);

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
	if (mDrawNull) mWindow->draw(mNullSign);

	sf::Time removeMissingSign = missingSignTime.getElapsedTime();
	if (!mMissing) removeMissingSign = missingSignTime.restart();

	if (removeMissingSign.asSeconds() <= 2.0)
	{
		removeMissingSign = missingSignTime.getElapsedTime();
	}
	else
	{
		mMissing = false;
		removeMissingSign = missingSignTime.restart();
	}
	if (mMissing) 
	{
		mWindow->draw(entities[mEntityMissing]->eNotCreated);
	}

	if (currentEntityIndex == 0) mWindow->draw(mArrow);
	else 
	{
		//std::cout << currentEntityIndex << std::endl;
		mWindow->draw(arrowTail);
	}
	mWindow->display();
}


Game::~Game()
{
	//pauseMenu = new Pause_Menu* [STAGES_MAX];

		for (int x=0; x<STAGES_MAX; x++)
		{
			delete pauseMenu[x];
		}
		delete[] pauseMenu;
		delete transitList[0];
		delete[] transitList;
		std::cout << "game destroyed" << std::endl;


}
#endif