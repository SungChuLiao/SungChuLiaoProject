#pragma once
#include <SFML/Audio.hpp>

#include"Paddle.h"
#include "Life.h"

class Ball : public Object
{
public:
	Ball(Paddle* player1, float speed, Life* myLife, float NewSpeed);
	void Update(sf::RenderWindow* window);
	void BallActive(sf::RenderWindow * window);
	void Reset(sf::RenderWindow* window);
	float ExSpeed;
	float speed;
private:
	bool GameStart;
	Paddle* paddle;
	Life* mylife;
	sf::SoundBuffer* bf;
	sf::Sound* sound;
	sf::SoundBuffer* bf2;
	sf::Sound* sound2;
	int timer;
	float PI;
	float ballangle;
};