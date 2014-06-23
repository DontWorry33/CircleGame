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

		float gCurrent;
		//Entity& operator= (const Entity &cSource);

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
			gCurrent = 0.6;

			weight = 2.f;
		}


};


class Roti : public Entity
{
	public:

		Roti()
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
			gCurrent = 0.6;

			weight = 1.f;

		}

};


class Anpan : public Entity
{
	public:
		Anpan()
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
			gCurrent = 0.6;

			weight =0.5;
		}

};


#endif