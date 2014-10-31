#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#ifndef ENTITY_H
#define ENTITY_H


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

	int maxHeight;

	float gCurrent;

	int platformToActivate;
	
	virtual void create(){};
	virtual void power(){};
	//virtual void swapTexture(sf::Texture){};


};


struct Switch : public Entity
{
	Switch(int startPosX, int startPosY, int platformNumber)
	{
		eTexture.loadFromFile("../../Stage_Images/Switch_Up.png");
		eTextureSize = eTexture.getSize();
		eSprite.setTexture(eTexture);
		eSprite.setOrigin(eTextureSize.x/2,eTextureSize.y/2);

		eTexture2.loadFromFile("../../Stage_Images/Switch_Down.png");

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

	}

};



struct Oven : public Entity
{
	Oven(int startPosX, int startPosY)
	{
		eTexture.loadFromFile("../../Stage_Images/Oven.png");
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

		eStartPos.x = 700;
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



	Platform(const char* filename, int startPosX, int startPosY, int maxHeight)
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


	Line(const char* filepath, int start_x, int start_y, bool oven)
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

		nextStage = oven;
	}

};

struct Baker : public Entity
{
	Baker()
	{
		eTexture.loadFromFile("../../Character_Images/TheBaker.png");

		eTextureSize = eTexture.getSize();
		cRadius=eTextureSize.x/2;

		cCircle.setTexture(&eTexture);
		cCircle.setRadius(cRadius);
		cCircle.setOrigin(cRadius,cRadius);

		eStartPos.x=490;
		eStartPos.y=600;

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
		eTexture2.loadFromFile("../../Stage_Images/Roti_Selected.png");
		eTextureSize2 = eTexture2.getSize();
		eSprite2.setTexture(eTexture2);
		eSprite2.setOrigin(eTextureSize2.x/2,eTextureSize2.y/2);

		eStartPos2.x = 599;
		eStartPos2.y = 70-eTextureSize2.y/2;

		eSprite2.setPosition(eStartPos2);
		//---------------------------- 
	}
	void create() //blank constructor, same for other 2
	{
	

		eTexture.loadFromFile("../../Character_Images/Roti.png");		

		eTextureSize = eTexture.getSize();
		cRadius = eTextureSize.x/2;

		cCircle.setTexture(&eTexture);
		cCircle.setRadius(cRadius);
		cCircle.setOrigin(cRadius,cRadius);

		eStartPos.x = 900;
		eStartPos.y = 600;

		eBounds.x = cCircle.getPosition().x - cRadius;
		eBounds.y = cCircle.getPosition().y - cRadius;

		cCircle.setPosition(eStartPos.x,eStartPos.y);

		//isCreated = true;
		gCurrent = 0.6;

		weight = 1.f;

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
		eTexture2.loadFromFile("../../Stage_Images/Anpan_Selected.png");
		eTextureSize2 = eTexture2.getSize();
		eSprite2.setTexture(eTexture2);
		eSprite2.setOrigin(eTextureSize2.x/2,eTextureSize2.y/2);

		eStartPos2.x = 600;
		eStartPos2.y = 70-eTextureSize2.y/2;

		eSprite2.setPosition(eStartPos2);
		//----------------------------
	}
	void create()
	{

		eTexture.loadFromFile("../../Character_Images/Anpan.png");

		eTextureSize = eTexture.getSize();
		cRadius = eTextureSize.x/2;

		cCircle.setTexture(&eTexture);
		cCircle.setRadius(cRadius);
		cCircle.setOrigin(cRadius,cRadius);

		eStartPos.x = 1000;
		eStartPos.y = 600;

		eBounds.x = cCircle.getPosition().x - cRadius;
		eBounds.y = cCircle.getPosition().y - cRadius;

		cCircle.setPosition(eStartPos.x,eStartPos.y);

		//isCreated = true;
		gCurrent = 0.6;
		weight =0.5;
	}
	void power()
	{
		NULL;

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
		eTexture2.loadFromFile("../../Stage_Images/Boule_Selected.png");
		eTextureSize2 = eTexture2.getSize();
		eSprite2.setTexture(eTexture2);
		eSprite2.setOrigin(eTextureSize2.x/2,eTextureSize2.y/2);

		eStartPos2.x = 600;
		eStartPos2.y = 70-eTextureSize2.y/2;

		eSprite2.setPosition(eStartPos2);
		//----------------------------
	}


	void create()
	{

		eTexture.loadFromFile("../../Character_Images/Boule.png");

		eTextureSize = eTexture.getSize();
		cRadius=eTextureSize.x/2;

		cCircle.setTexture(&eTexture);
		cCircle.setRadius(cRadius);
		cCircle.setOrigin(cRadius,cRadius);

		eStartPos.x=1100;
		eStartPos.y=400;

		eBounds.x = cCircle.getPosition().x - cRadius;
		eBounds.y = cCircle.getPosition().y - cRadius;

		cCircle.setPosition(eStartPos.x,eStartPos.y);

		//isCreated = true;
		gCurrent = 0.6;

		weight = 0.4;
	}
};


#endif

