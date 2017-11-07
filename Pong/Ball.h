#pragma once
#include <SFML/Audio.hpp>

#include"PaddlePlayer.h"
#include "Score.h"
#include "Obstacle.h"
class Ball : public Object
{
public:
	Ball(Score* score1, Score* score2, Paddle* player1, Paddle* player2, Obstacle* obstacle);
	void Update(sf::RenderWindow* window);
	void Reset(sf::RenderWindow* window);
private:
	Score* score1;
	Score* score2;
	Paddle* player1;
	Paddle* player2;
	Obstacle* obstacle;
	sf::SoundBuffer* bf;
	sf::Sound* sound;
	int timer;
};