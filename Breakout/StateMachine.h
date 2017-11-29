#pragma once

#include <SFML/Graphics.hpp>

class MatchState
{
public:
	virtual void Initiallize(sf::RenderWindow *window)
	{

	}
	virtual void Update(sf::RenderWindow *window)
	{

	}
	virtual void Render(sf::RenderWindow *window)
	{

	}
	virtual void Destory(sf::RenderWindow *window)
	{

	}
	~MatchState()
	{

	}
};

class GameState
{
public:
	GameState()
	{
		this->state = NULL;
	}

	void setWindow(sf::RenderWindow* window)
	{
		this->window = window;
	}

	void SetState(MatchState* state)
	{
		if (this->state != NULL)
		{
			this->state->Destory(this->window);
		}
		this->state = state;
		if (this->state != NULL)
		{
			this->state->Initiallize(this->window);
		}
	}
	void Update()
	{
		if (this->state != NULL)
		{
			this->state->Update(this->window);
		}

	}
	void Render()
	{
		if (this->state != NULL)
		{
			this->state->Render(this->window);
		}

	}
	~GameState()
	{
		if (this->state != NULL)
		{
			this->state->Destory(this->window);
		}
	}
private:
	sf::RenderWindow* window;
	MatchState* state;
};
extern GameState CoreState;
extern bool quitGame;