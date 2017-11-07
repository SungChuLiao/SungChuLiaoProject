#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Object : public sf::Sprite
{
public:

	sf::Vector2f velocity;

	Object()
	{
		this->texture = new sf::Texture();
	}
	void Load(std::string fileName)
	{
		this->texture->loadFromFile("Image/Sprite/" + fileName);
		this->setTexture(*this->texture);
	}
	virtual void Update()
	{
		this->move(this->velocity);
	}

	bool CheckCollision(Object *object)
	{
		return this->getGlobalBounds().intersects(object->getGlobalBounds());
	}
	~Object()
	{
		delete this->texture;
	}
private:
	sf::Texture* texture;
};