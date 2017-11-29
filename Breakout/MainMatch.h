#pragma once

#include "StateMachine.h"
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "BrickManager.h"
#include "Life.h"
#include <memory>
#include <vector>
class MainMatch : public MatchState
{
public:
	MainMatch(int BrickRowNum, int BrickColumnNum, float NewSpeed, int level);
	void Initiallize(sf::RenderWindow *window);
	void Update(sf::RenderWindow *window);
	void Render(sf::RenderWindow *window);
	void Destory(sf::RenderWindow *window);

private:
	Paddle* paddle;
	Ball* ball;
	std::vector<std::unique_ptr<Brick>> bricks;
	//Brick* brick[100];
	Life* myLife;
	Score* myScore = 0;
	float NewSpeed;
	int MaxBrickNum;
	int BrickNum;
	int level;
	bool MatchEnd;
	bool WinSoundPlay;
	int BrickRowNum;
	int BrickColumnNum;
	sf::SoundBuffer* bf;
	sf::Sound* sound;
	sf::Font* font;
	sf::Text *EndName;

};
