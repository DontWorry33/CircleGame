#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "StringHelpers.hpp"
#include "Stage.cpp"
#include "Entity.cpp"
#include "UI.cpp"
#include "Transition.cpp"
#ifndef BOUND_H
#define BOUND_H

#define PI 3.14159265
#define ENTITIES_MAX 4
#define STAGES_MAX 15
#define G_MAX 160.0

class Game
{
	public:
	
		Game(sf::RenderWindow* tmpWin);
		//functions

		//main loop
		void run(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		//updates positions of all entities
		void updateEntityPosition(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);


		//checks if a specific entity has anything touching the bottom of it (mainly for gravity) returns true if anything touching, otherwise false
		bool bottomCircleCollision(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		//checks if a specific entity has anything touching the right side of it (mainly for roti repel power) returns true if anything touching, otherwise false
		bool rightCircleCollision(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		//checks if a specific entity has anything touching the left side of it (mainly for roti repel power) returns true if anything touching, otherwise false
		bool leftCircleCollision(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		//checks if a specific entity has anything touching the top of it (maily for roti attraction power) returns true if anything touching, otherwise false
		bool topCircleCollision(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		//checks if gravity should be applied and does so if needed
		void checkGravity(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int character);
		//specifically for gravity, special checking
		void checkBounds(Entity* entities[ENTITIES_MAX]);
		//checks if a specific entity (boule) is touching any portal on the map, returns index of portal it is touching
		int isTouchingPortal(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		//checks if a specific entity (boule) is touching any other bread on the map, returns index of bread it is touching
		int isTouchingBread(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		//checks if a specific entity (the one being shot) is touching anything on any part of it based on collision points. returns true if so.
		bool isTouchingSurface(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		//just checks top and bottom collision points for a specific entity. returns true if so.
		bool isTouchingRotiSurface(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int x);
		//checks if specific entity is hitting anything. Modifies argument (*data) and fills it with information about what was hit and which side
		void checkHitting(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX], int airborneEntity, bool isSwitch, int* data);
		//sets obejct specific variables to do with movement. Esentially checks if entity can move or not
		void motionCheck(int character, Entity* entities[ENTITIES_MAX],Stage* stages[STAGES_MAX]);


		//checks if the baker is touching portal and initalizes all variables to swap to next stage
		void swapStage(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		//a while loop that exits upon pressing enter (so that we can display stats)
		void initPostStage(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		//does fade actions from current stage screen into the transition screens. After last transition screen loads, press Q to start next stage
		void startTransition(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		//resets level when you press R. Also called after moving on to next stage
		void resetLevel(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);


		//chooses which bread to shoot out upon pressing tab
		void breadSelector(sf::Keyboard::Key key, int selectedEntity);
		//updates power metre as you hold space
		void powerMetreUpdate(sf::Keyboard::Key key);
		//bread is selected upon clicking it
		void entitySelector(Entity* entities[ENTITIES_MAX]);
		//calcules position on the baker to position arrow according to mouse position
		void Arrow(Entity* entities[ENTITIES_MAX]);
		//applies trajectory to bread being shot
		void trajectory(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX]); 


		//activates the attraction part of the roti power
		void activateRotiPowerAlpha(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		//sets variable for repulsion part of roti power based on outcome of activateRotipowerAlpha
		void activateRotiPowerBeta(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		//activates the anpan power (swapping)
		void activateAnpanPower(Entity* entities[ENTITIES_MAX],Stage* stages[STAGES_MAX]);
		//specific for the boule power. swaps background to "negated" and back
		void swapBackground(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		//activates boule power (negation, portals, switches)
		void activateBoulePower(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX],sf::Time elapsedTime);


		//initalizes the pause menu
		int pauseMenuRun();
		//processes events for the game (mouse movements, keypresses, etc)
		void processEvents(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		//handles player key presses
		void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
		//updates many functions of the game including movement, shooting, etc
		void update(sf::Time elapsedTime, Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		//renders everything needed to the window
		void render(Entity* entities[ENTITIES_MAX], Stage* stages[STAGES_MAX]);
		//shows stats at the top of screen (fps, time per update, etc)
		void updateStatistics(sf::Time elapsedTime);	


		//destructor
		~Game();
		
	
		//constants for update statistics
		static const float PlayerSpeed;
		static const sf::Time TimePerFrame;

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


		//currently elapsed time in the stage/text to draw
		sf::Clock stageTime;
		sf::Text stageTimeText;
		//how long has elapsed during the stage
		sf::Time currentStageTime;


		//current points displayed while playing
		sf::Text currentPointsText;
		//display points in the post screen
		sf::Text postScreenText;

		//power gauge
		sf::Sprite mPowerGaugeShell;
		sf::CircleShape mPowerGaugeMetre;
		sf::Texture mPowerGaugeShellTexture;
		sf::Texture mPowerGaugeMetreTexture;

		//power gauge value
		float powerMetre;

		//Gravity
		const float g; //gravity constant initalized in constructor
		const float timePerGravityUpdate;  //amount of time before acceleration update
		float gCurrent; //curent gravity
		sf::Clock gravityClock; //measure time
	
		//the index of which entity is selected
		int currentEntityIndex;

		//which bread is going to be fired % 3
		int currentlySelected; 

		//based on currentlySelected, is the integer value of the index of which bread is going to be fired
		int shotChooser;

		//locks mouse while bread is in the air to avoid complications
		bool mouseLock;
		
		//locks position of the baker when bread is the air to avoid complications
		bool positionLock;

		//if true, resets the game
		bool mResetGame;

		//Drawing the power metre only when needed
		bool mDrawMetre;
		bool mDrawNull;

		//The sign that shows up in the top left of the screen when there is not enough space to swap with the Baker with anpan
		sf::Texture mNullSignTexture;
		sf::Sprite mNullSign;

		bool mMissing; //for drawing missing
		int mEntityMissing; //for getting the index of the missing

		//stores position of baker so we can manipulate  positionLock.
		sf::Vector2f traj_pos;

		//Display the sign for a certain amount of time
		sf::Clock nullSignTime;
		sf::Clock missingSignTime;

		//main game time variables
		sf::Time elapsedTime;
		sf::Clock clock;
		sf::Time timeSinceLastUpdate;

		//negates gravity to move upwards during roti power
		bool negateGravity;

		//checks if roti is pulling the Baker
		bool isBeingAttracted;

		//checks if boule power is active
		bool bouleActivated;

		//variables for moving from portal->bread and bread->portal
		bool portalTeleport;
		bool breadTeleport;
		bool bLock;
		bool pLock;


		//checks if you were just displaced and still touching the displacement object you were sent to
		bool displaced;

		//displaces the platform for platform disappear switch
		bool disp;

		//the current stage you are on.
		int currentStage;

		//for multiple switches next to eachother, needed special logic
		int tSwitch;
		
		//tells you which switch was displaced
		int displacedSwitch;

/*
		std::vector<sf::Music*> music;
   		sf::Music music1;
   		sf::Music music2;
   		sf::Music music3;
   		sf::Music music4;
   		sf::Music music5;
   		sf::Music music6;
*/
   		//current song playing (we dont have any music yet but if we did....)
   		int currSong;
   		
   		//variables for roti power repel
   		bool rotiActive;
   		bool skipRoti;
   		bool skipBaker;

   		//check if a point needs to be added for an action done in game
   		bool pointAdded;

   		//debugging purposes
   		int itrnum;

   		//values of how much baker/roti should be repulsed
  		sf::Vector2f bakerRepulsion;
		sf::Vector2f rotiRepulsion;


		//arrow resources
		sf::Texture arrowTailImage;
		sf::Sprite arrowTail;

		//pause menu and transition arrays of pointers
		Pause_Menu** pauseMenu; 
		Transition** transitList;

		//clock for fading in/out of things
		sf::Clock fadeClock;

		//post screen resources
		sf::Texture postScreen_img;
		sf::Sprite postScreen;
		bool mDrawPostScreen;

		//current points added up
		int currentPoints;

		//prints debug messages
		bool debug;


};

#endif