#pragma once

#include "Game.h"
#include "PaddlePlayer.h"
#include "Ball.h"
#include "score.h"
#include "PaddleAI.h"
#include "Obstacle.h"
class MainMatch : public MatchState
{
public:
	MainMatch(int mode);
	void Initiallize(sf::RenderWindow *window);
	void Update(sf::RenderWindow *window);
	void Render(sf::RenderWindow *window);
	void Destory(sf::RenderWindow *window);
private:
	PaddlePlayer* player1;
	PaddlePlayer* player2;
	PaddleAI* AI;
	Obstacle* Rock;
	Ball* ballObejct;
	Score* score1;
	Score* score2;
	sf::Font* font;
	sf::Text *EndName;
	int modeType;
	bool MatchEnd;
	bool WinSoundPlay;
	sf::SoundBuffer* bf;
	sf::Sound* sound;
};