#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#ifndef ENTITY_H
#define ENTITY_H
#define PI 3.14159265


struct Entity
{
	
	sf::Texture eTexture;
	sf::Vector2u eTextureSize;
	sf::Sprite eSprite;
	
	//D: Part 2. Duplicates of needed variables. Have a -2 suffix
	sf::Texture eTexture2;
	sf::Vector2u eTextureSize2;
	sf::Sprite eSprite2;
	sf::Vector2f eStartPos2;
	sf:: Vector2f eBounds2;

	int cRadius;
	sf::CircleShape cCircle;
	sf::Vector2f eStartPos;
	sf::Vector2f eBounds; //give current position x and y boundries for entity
	float weight;

	bool isCurrentEntity;
	float isClickable;
	bool isCircle;
	bool isCreated;

	bool canMoveRight;
	bool canMoveLeft;
	bool canMoveUp;
	bool canMoveDown;
	
	bool activatePlatform;
	bool nextStage;
	int switchType;
	bool switchUsed;
	sf::Vector2f displacement;

	int maxHeight;

	float gCurrent;

	int platformToActivate;

	int portalType;

	int move;

	float* topCircle;
	float* rightCircle;
	float* bottomCircle;
	float* leftCircle;
	float* bottomRCircle;
	float* bottomLCircle;
	virtual void create(){};
	virtual void power(){};
	//virtual void swapTexture(sf::Texture){};


};


struct Switch : public Entity
{

	//this constructor is for type 0, type 1, type 4, type 5, type 6
	//type 0 for touch switch, 1 for hold switch
	//type 5 for touch switch down, 6 for hold switch down, 
	Switch(int startPosX, int startPosY, int platformNumber, int type)
	{
		eTexture.loadFromFile("../Stage_Images/Stage1/quad4Switch1.png");
		eTextureSize = eTexture.getSize();
		eSprite.setTexture(eTexture);
		eSprite.setOrigin(eTextureSize.x/2,eTextureSize.y/2);

		eTexture2.loadFromFile("../Stage_Images/Stage1/Switch_Hit.png");

		eStartPos.x = startPosX;
		eStartPos.y = startPosY-eTextureSize.y/2;

		eSprite.setPosition(eStartPos);
		eBounds.x = eSprite.getPosition().x - eTextureSize.x/2;
		eBounds.y = eSprite.getPosition().y - eTextureSize.y/2;

		isCurrentEntity = false;
		isClickable = false;
		isCircle = false;
		isCreated = true;
		gCurrent = 0;

		platformToActivate = platformNumber;
		switchType = type;

		switchUsed = false;


	}
	//this constructor is for type 2 (reset) switch and type 3 (displacement) switch.
	//When type 2 is chosen, the displacement moves ROTI.
	//When type 3 is chosen, the displacement moves BAKER.
	Switch(int startPosX, int startPosY, int type, int displacementX, int displacementY)
	{
		eTexture.loadFromFile("../Stage_Images/Stage1/quad4Switch1.png");
		eTextureSize = eTexture.getSize();
		eSprite.setTexture(eTexture);
		eSprite.setOrigin(eTextureSize.x/2,eTextureSize.y/2);

		eTexture2.loadFromFile("../Stage_Images/Stage1/Switch_Hit.png");

		eStartPos.x = startPosX;
		eStartPos.y = startPosY-eTextureSize.y/2;

		eSprite.setPosition(eStartPos);
		eBounds.x = eSprite.getPosition().x - eTextureSize.x/2;
		eBounds.y = eSprite.getPosition().y - eTextureSize.y/2;

		isCurrentEntity = false;
		isClickable = false;
		isCircle = false;
		isCreated = true;
		gCurrent = 0;
		switchType = type;
		switchUsed = false;
		displacement.x = displacementX;
		displacement.y = displacementY;
	}


	//this constructor is for type 3 (displacement) switch. 2 additional arguments


};



struct Oven : public Entity
{
	Oven(int startPosX, int startPosY)
	{
		eTexture.loadFromFile("../Stage_Images/Universal_StageParts/Stage_Oven_Default.png");
		eTextureSize = eTexture.getSize();
		eSprite.setTexture(eTexture);
		eSprite.setOrigin(eTextureSize.x/2,eTextureSize.y/2);

		eStartPos.x = startPosX;
		eStartPos.y = startPosY-eTextureSize.y/2;

		eSprite.setPosition(eStartPos);

		eBounds.x = eSprite.getPosition().x - eTextureSize.x/2;
		eBounds.y = eSprite.getPosition().y - eTextureSize.y/2;

		isCurrentEntity = false;
		isClickable = false;
		isCircle = false;
		isCreated = true;
	}


};

struct Portal : public Entity 
{
	//type refers to either baker, roti or anpan (0, 1 or 2)
	//this makes it easier so we don't have to put the filename as argument
	//as they are the same 3 files.
	Portal(int startPosX, int startPosY, int type)
	{
		if (type==0)
		{
			portalType = 0;
			eTexture.loadFromFile("../Stage_Images/Universal_StageParts/Portal_Baker.png");
		}
		if (type==1)
		{
			portalType = 1;
			eTexture.loadFromFile("../Stage_Images/Universal_StageParts/Portal_Roti.png");
		}
		if (type==2) 
		{
			portalType = 2;
			eTexture.loadFromFile("../Stage_Images/Universal_StageParts/Portal_Anpan.png");
		}

		eTextureSize = eTexture.getSize();
		eSprite.setTexture(eTexture);
		eSprite.setOrigin(eTextureSize.x/2, eTextureSize.y/2);

		eStartPos.x = startPosX;
		eStartPos.y = startPosY-eTextureSize.y/2;

		eSprite.setPosition(eStartPos);

		eBounds.x = eSprite.getPosition().x - eTextureSize.x/2;
		eBounds.y = eSprite.getPosition().y - eTextureSize.y/2;

		isCurrentEntity = false;
		isClickable = false;
		isCircle = false;
		isCreated = true;
		gCurrent = 0;
	}
};

struct Platform : public Entity
{

	Platform(const char* filename)
	{
		eTexture.loadFromFile(filename);
		eTextureSize = eTexture.getSize();
		eSprite.setTexture(eTexture);
		eSprite.setOrigin(eTextureSize.x/2,eTextureSize.y/2);

		eStartPos.x = 750;
		eStartPos.y = 750;

		eSprite.setPosition(eStartPos);

		eBounds.x = eSprite.getPosition().x - eTextureSize.x/2;
		eBounds.y = eSprite.getPosition().y - eTextureSize.y/2;

		isCurrentEntity = false;
		isClickable = false;
		isCircle = false;
		isCreated = true;
		gCurrent = 0;

		activatePlatform = false;
		maxHeight=300;

	}


	//move : 0 = none, 1 = up, 2 = down. ONLY FOR SWITCHES 0 AND 6. USE MOVE=0 FOR EVERYTHING ELSE
	Platform(const char* filename, int startPosX, int startPosY, int maxHeight, int move)
	{
		eTexture.loadFromFile(filename);
		eTextureSize = eTexture.getSize();
		eSprite.setTexture(eTexture);
		eSprite.setOrigin(eTextureSize.x/2,eTextureSize.y/2);

		eStartPos.x = startPosX;
		eStartPos.y = startPosY-eTextureSize.y/2;

		eSprite.setPosition(eStartPos);

		eBounds.x = eSprite.getPosition().x - eTextureSize.x/2;
		eBounds.y = eSprite.getPosition().y - eTextureSize.y/2;

		isCurrentEntity = false;
		isClickable = false;
		isCircle = false;
		isCreated = true;
		gCurrent = 0;

		activatePlatform = false;

		this->maxHeight = maxHeight;
		this->move = move;

	}


};


struct Line : public Entity
{
	Line(const char* filepath)
	{
		eTexture.loadFromFile(filepath);
		eTextureSize = eTexture.getSize();
		eSprite.setTexture(eTexture);
		eSprite.setOrigin(eTextureSize.x/2,eTextureSize.y/2);

		eStartPos.x = 900;
		eStartPos.y = 800-eTextureSize.y/2;

		eSprite.setPosition(eStartPos);

		eBounds.x = eSprite.getPosition().x - eTextureSize.x/2;
		eBounds.y = eSprite.getPosition().y - eTextureSize.y/2;

		isCurrentEntity = false;
		isClickable = false;
		isCircle = false;
		isCreated = true;
		gCurrent = 0;
		nextStage = false;
	}

	Line(const char* filepath, int start_x, int start_y)
	{
		eTexture.loadFromFile(filepath);
		eTextureSize = eTexture.getSize();
		eSprite.setTexture(eTexture);
		eSprite.setOrigin(eTextureSize.x/2,eTextureSize.y/2);

		eStartPos.x = start_x;
		eStartPos.y = start_y-eTextureSize.y/2;

		eSprite.setPosition(eStartPos);

		eBounds.x = eSprite.getPosition().x - eTextureSize.x/2;
		eBounds.y = eSprite.getPosition().y - eTextureSize.y/2;

		isCurrentEntity = false;
		isClickable = false;
		isCircle = false;
		isCreated = true;
		gCurrent = 0;
		nextStage = false;
	}


	Line(const char* filepath, int start_x, int start_y, bool t)
	{
		eTexture.loadFromFile(filepath);
		eTextureSize = eTexture.getSize();
		eSprite.setTexture(eTexture);
		eSprite.setOrigin(eTextureSize.x/2,eTextureSize.y/2);

		eStartPos.x = start_x;
		eStartPos.y = start_y-eTextureSize.y/2;

		eSprite.setPosition(eStartPos);

		eBounds.x = eSprite.getPosition().x - eTextureSize.x/2;
		eBounds.y = eSprite.getPosition().y - eTextureSize.y/2;

		isCurrentEntity = false;
		isClickable = false;
		isCircle = false;
		isCreated = true;
		gCurrent = 0;

		nextStage = t;
	}

};

struct Baker : public Entity
{
	Baker()
	{
		eTexture.loadFromFile("../Character_Images/TheBaker.png");

		eTextureSize = eTexture.getSize();
		cRadius=eTextureSize.x/2;

		cCircle.setTexture(&eTexture);
		cCircle.setRadius(cRadius);
		cCircle.setOrigin(cRadius,cRadius);

		eStartPos.x=580;
		eStartPos.y=700;

		eBounds.x = cCircle.getPosition().x - cRadius;
		eBounds.y = cCircle.getPosition().y - cRadius;

		cCircle.setPosition(eStartPos.x,eStartPos.y);

		isCurrentEntity = true;
		isCircle = true;
		isClickable = true;
		isCreated = true;
		
		canMoveUp = true;
		canMoveDown = true;
		canMoveRight = true;
		canMoveLeft = true;

		gCurrent = 0.6;

		weight = 0.5;

		topCircle = new float[2];
		topCircle[0] = cCircle.getPosition().x + (cRadius*cos(3*PI/2));
		topCircle[1] = cCircle.getPosition().y + (cRadius*sin(3*PI/2));

		rightCircle = new float[2];
		rightCircle[0] = cCircle.getPosition().x + (cRadius*cos(2*PI));
		rightCircle[1] = cCircle.getPosition().y + (cRadius*sin(2*PI));

		bottomCircle = new float[2];
		bottomCircle[0] = cCircle.getPosition().x + (cRadius*cos(PI/2));		
		bottomCircle[1] = cCircle.getPosition().y + (cRadius*sin(PI/2));

		leftCircle = new float[2];
		leftCircle[0] = cCircle.getPosition().x + (cRadius*cos(PI));
		leftCircle[1] = cCircle.getPosition().y + (cRadius*sin(PI));

		bottomRCircle = new float[2];
		bottomRCircle[0] = cCircle.getPosition().x + (cRadius*cos(PI/4));
		bottomRCircle[1] = cCircle.getPosition().y + (cRadius*sin(PI/4));

		bottomLCircle = new float[2];
		bottomLCircle[0] = cCircle.getPosition().x + (cRadius*cos(3*PI/4));
		bottomLCircle[1] = cCircle.getPosition().y + (cRadius*sin(3*PI/4));
	}

	~Baker()
	{
		std::cout << "destructing baker" << std::endl;
		delete[] topCircle;
		delete[] rightCircle;
		delete[] bottomCircle;
		delete[] leftCircle;
		delete[] bottomRCircle;
		delete[] bottomLCircle;
	}
};

struct Roti : public Entity
{
	Roti()
	{
		isCreated = false;
		isCurrentEntity = false;
		isCircle = true;
		isClickable = true;

		canMoveUp = true;
		canMoveDown = true;
		canMoveRight = true;
		canMoveLeft = true;

		//BreadSelector Initialisation
		eTexture2.loadFromFile("../Stage_Images/Universal_StageParts/Roti_Selected.png");
		eTextureSize2 = eTexture2.getSize();
		eSprite2.setTexture(eTexture2);
		eSprite2.setOrigin(eTextureSize2.x/2,eTextureSize2.y/2);

		eStartPos2.x = 599;
		eStartPos2.y = 70-eTextureSize2.y/2;

		eSprite2.setPosition(eStartPos2);
		topCircle = new float[2];
		rightCircle = new float[2];
		bottomCircle = new float[2];
		leftCircle = new float[2];
		bottomRCircle = new float[2];
		bottomLCircle = new float[2];


		//---------------------------- 
	}
	void create() //blank constructor, same for other 2
	{
	

		eTexture.loadFromFile("../Character_Images/Roti.png");		

		eTextureSize = eTexture.getSize();
		cRadius = eTextureSize.x/2;

		cCircle.setTexture(&eTexture);
		cCircle.setRadius(cRadius);
		cCircle.setOrigin(cRadius,cRadius);

		eStartPos.x=-1000;
		eStartPos.y=-1000;

		eBounds.x = cCircle.getPosition().x - cRadius;
		eBounds.y = cCircle.getPosition().y - cRadius;

		cCircle.setPosition(eStartPos.x,eStartPos.y);

		//isCreated = true;
		gCurrent = 0.6;

		weight = 1.f;


		topCircle[0] = cCircle.getPosition().x + (cRadius*cos(3*PI/2));
		topCircle[1] = cCircle.getPosition().y + (cRadius*sin(3*PI/2));

		rightCircle[0] = cCircle.getPosition().x + (cRadius*cos(2*PI));
		rightCircle[1] = cCircle.getPosition().y + (cRadius*sin(2*PI));

		bottomCircle[0] = cCircle.getPosition().x + (cRadius*cos(PI/2));		
		bottomCircle[1] = cCircle.getPosition().y + (cRadius*sin(PI/2));

		leftCircle[0] = cCircle.getPosition().x + (cRadius*cos(PI));
		leftCircle[1] = cCircle.getPosition().y + (cRadius*sin(PI));
//pi/4 = top right
//3pi/4 = top left
		bottomRCircle[0] = cCircle.getPosition().x + (cRadius*cos(PI/4));
		bottomRCircle[1] = cCircle.getPosition().y + (cRadius*sin(PI/4));

		bottomLCircle[0] = cCircle.getPosition().x + (cRadius*cos(3*PI/4));
		bottomLCircle[1] = cCircle.getPosition().y + (cRadius*sin(3*PI/4));
	}
	~Roti()
	{
		std::cout << "destructing roti" << std::endl;
		delete[] topCircle;
		delete[] rightCircle;
		delete[] bottomCircle;
		delete[] leftCircle;
		delete[] bottomRCircle;
		delete[] bottomLCircle;
	}
};


struct Anpan : public Entity
{
	Anpan()
	{
		isCreated = false;
		isCurrentEntity = false;
		isCircle = true;
		isClickable = true;
		
		

		canMoveUp = true;
		canMoveDown = true;
		canMoveRight = true;
		canMoveLeft = true;

		
		//BreadSelector Initialisation
		eTexture2.loadFromFile("../Stage_Images/Universal_StageParts/Anpan_Selected.png");
		eTextureSize2 = eTexture2.getSize();
		eSprite2.setTexture(eTexture2);
		eSprite2.setOrigin(eTextureSize2.x/2,eTextureSize2.y/2);

		eStartPos2.x = 600;
		eStartPos2.y = 70-eTextureSize2.y/2;

		eSprite2.setPosition(eStartPos2);
		topCircle = new float[2];
		rightCircle = new float[2];
		bottomCircle = new float[2];
		leftCircle = new float[2];
		bottomRCircle = new float[2];
		bottomLCircle = new float[2];
		//----------------------------
	}
	void create()
	{

		eTexture.loadFromFile("../Character_Images/Anpan.png");

		eTextureSize = eTexture.getSize();
		cRadius = eTextureSize.x/2;

		cCircle.setTexture(&eTexture);
		cCircle.setRadius(cRadius);
		cCircle.setOrigin(cRadius,cRadius);

		eStartPos.x=-1000;
		eStartPos.y=-1000;

		eBounds.x = cCircle.getPosition().x - cRadius;
		eBounds.y = cCircle.getPosition().y - cRadius;

		cCircle.setPosition(eStartPos.x,eStartPos.y);

		//isCreated = true;
		gCurrent = 0.6;
		weight =0.5;


		topCircle[0] = cCircle.getPosition().x + (cRadius*cos(3*PI/2));
		topCircle[1] = cCircle.getPosition().y + (cRadius*sin(3*PI/2));

		rightCircle[0] = cCircle.getPosition().x + (cRadius*cos(2*PI));
		rightCircle[1] = cCircle.getPosition().y + (cRadius*sin(2*PI));

		bottomCircle[0] = cCircle.getPosition().x + (cRadius*cos(PI/2));		
		bottomCircle[1] = cCircle.getPosition().y + (cRadius*sin(PI/2));

		leftCircle[0] = cCircle.getPosition().x + (cRadius*cos(PI));
		leftCircle[1] = cCircle.getPosition().y + (cRadius*sin(PI));


		bottomRCircle[0] = cCircle.getPosition().x + (cRadius*cos(PI/4));
		bottomRCircle[1] = cCircle.getPosition().y + (cRadius*sin(PI/4));

		bottomLCircle[0] = cCircle.getPosition().x + (cRadius*cos(3*PI/4));
		bottomLCircle[1] = cCircle.getPosition().y + (cRadius*sin(3*PI/4));	
	}
	void power()
	{
		NULL;

	}

	~Anpan()
	{
		std::cout << "destructing Anpan" << std::endl;
		delete[] topCircle;
		delete[] rightCircle;
		delete[] bottomCircle;
		delete[] leftCircle;
		delete[] bottomRCircle;
		delete[] bottomLCircle;
	}
};


struct Boule : public Entity
{
	Boule()
	{
		isCreated = false;
		isCurrentEntity = false;
		isCircle = true;
		isClickable = true;

		

		
		canMoveUp = true;
		canMoveDown = true;
		canMoveRight = true;
		canMoveLeft = true;

		
		//BreadSelector Initialisation
		eTexture2.loadFromFile("../Stage_Images/Universal_StageParts/Boule_Selected.png");
		eTextureSize2 = eTexture2.getSize();
		eSprite2.setTexture(eTexture2);
		eSprite2.setOrigin(eTextureSize2.x/2,eTextureSize2.y/2);

		eStartPos2.x = 600;
		eStartPos2.y = 70-eTextureSize2.y/2;

		eSprite2.setPosition(eStartPos2);
		//----------------------------
		topCircle = new float[2];
		rightCircle = new float[2];
		bottomCircle = new float[2];
		leftCircle = new float[2];
		bottomRCircle = new float[2];
		bottomLCircle = new float[2];
	}


	void create()
	{

		eTexture.loadFromFile("../Character_Images/Boule.png");

		eTextureSize = eTexture.getSize();
		cRadius=eTextureSize.x/2;

		cCircle.setTexture(&eTexture);
		cCircle.setRadius(cRadius);
		cCircle.setOrigin(cRadius,cRadius);

		eStartPos.x=-1000;
		eStartPos.y=-1000;

		eBounds.x = cCircle.getPosition().x - cRadius;
		eBounds.y = cCircle.getPosition().y - cRadius;

		cCircle.setPosition(eStartPos.x,eStartPos.y);

		//isCreated = true;
		gCurrent = 0.6;

		weight = 0.4;

		topCircle[0] = cCircle.getPosition().x + (cRadius*cos(3*PI/2));
		topCircle[1] = cCircle.getPosition().y + (cRadius*sin(3*PI/2));

		rightCircle[0] = cCircle.getPosition().x + (cRadius*cos(2*PI));
		rightCircle[1] = cCircle.getPosition().y + (cRadius*sin(2*PI));

		bottomCircle[0] = cCircle.getPosition().x + (cRadius*cos(PI/2));		
		bottomCircle[1] = cCircle.getPosition().y + (cRadius*sin(PI/2));

		leftCircle[0] = cCircle.getPosition().x + (cRadius*cos(PI));
		leftCircle[1] = cCircle.getPosition().y + (cRadius*sin(PI));

		bottomRCircle[0] = cCircle.getPosition().x + (cRadius*cos(PI/4));
		bottomRCircle[1] = cCircle.getPosition().y + (cRadius*sin(PI/4));

		bottomLCircle[0] = cCircle.getPosition().x + (cRadius*cos(3*PI/4));
		bottomLCircle[1] = cCircle.getPosition().y + (cRadius*sin(3*PI/4));	
	}

	~Boule()
	{
		std::cout << "destructing roti" << std::endl;
		delete[] topCircle;
		delete[] rightCircle;
		delete[] bottomCircle;
		delete[] leftCircle;
		delete[] bottomRCircle;
		delete[] bottomLCircle;
	}
};


#endif

