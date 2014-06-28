#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


#ifndef ENTITY_H
#define ENTITY_H


struct Entity
{
	
	sf::Texture eTexture;
	sf::Vector2u eTextureSize;
	sf::Sprite eSprite;
	int cRadius;
	sf::CircleShape cCircle;
	sf::Vector2f eStartPos;
	sf::Vector2f eBounds; //give current position x and y boundries for entity
	float weight;

	bool isCurrentEntity;
	float isClickable;
	bool isCircle;

	float gCurrent;
	
	virtual void create(){};


};


struct PortalBox : public Entity
{
	PortalBox()
	{
		eTexture.loadFromFile("../../Stage_Images/Portal_Box.png");
		eTextureSize = eTexture.getSize();
		eSprite.setTexture(eTexture);
		eSprite.setOrigin(eTextureSize.x/2,eTextureSize.y/2);

		eStartPos.x = 600;
		eStartPos.y = 400-eTextureSize.y/2;

		eSprite.setPosition(eStartPos);

		eBounds.x = eSprite.getPosition().x - eTextureSize.x/2;
		eBounds.y = eSprite.getPosition().y - eTextureSize.y/2;

		isCurrentEntity = false;
		isClickable = false;
		isCircle = false;
		gCurrent = 0;


	}
};


struct Line : public Entity
{
	Line()
	{
		eTexture.loadFromFile("../../Stage_Images/Standing_Border.png");
		eTextureSize = eTexture.getSize();
		eSprite.setTexture(eTexture);
		eSprite.setOrigin(eTextureSize.x/2,eTextureSize.y/2);

		eStartPos.x = 300;
		eStartPos.y = 400-eTextureSize.y/2;

		eSprite.setPosition(eStartPos);

		eBounds.x = eSprite.getPosition().x - eTextureSize.x/2;
		eBounds.y = eSprite.getPosition().y - eTextureSize.y/2;

		isCurrentEntity = false;
		isClickable = false;
		isCircle = false;
		gCurrent = 0;


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

		isCurrentEntity = false;
		isCircle = true;
		isClickable = true;

		gCurrent = 0.6;

		weight = 10.f;
	}


};

struct Roti : public Entity
{

	Roti(){}
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

		isCurrentEntity = false;
		isCircle = true;
		isClickable = true;

		gCurrent = 0.6;

		weight = 1.f;

	}

};


struct Anpan : public Entity
{
	Anpan(){}
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

		isCurrentEntity = false;
		isCircle = true;
		isClickable = true;

		gCurrent = 0.6;

		weight =0.5;
	}

};


struct Boule : public Entity
{
	Boule(){}
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

		isCurrentEntity = false;
		isCircle = true;
		isClickable = true;


		gCurrent = 0.6;

		weight = 0.4;
	}
};


#endif

