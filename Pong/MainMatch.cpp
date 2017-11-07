#include "MainMatch.h"
#include "MainMenu.h"

MainMatch::MainMatch(int mode)
{
	if (mode == 0)
	{
		modeType = 0;
	}
	if (mode == 1)
	{
		modeType = 1;
	}
}
void MainMatch::Initiallize(sf::RenderWindow *window)
{
	this->bf = new sf::SoundBuffer();
	this->bf->loadFromFile("Sound/BGM.flac");
	this->sound = new sf::Sound(*this->bf);
	this->sound->setLoop(true);
	this->sound->setVolume(10);
	this->sound->play();

	WinSoundPlay = false;
	MatchEnd = false;
	this->font = new sf::Font();
	this->font->loadFromFile("Image/myFont.ttf");
	this->score1 = new Score(*font, 32U);
	this->score2 = new Score(*font, 32U);
	this->score2->setPosition(window->getSize().x - this->score2->getGlobalBounds().width, 0);
	this->Rock = new Obstacle();
	///Player
	this->player1 = new PaddlePlayer(0);
	if (modeType == 0)
	{
		this->AI = new PaddleAI(1);
		this->ballObejct = new Ball(this->score1, this->score2, this->player1, this->AI, this->Rock);
		this->AI->SetBall(ballObejct);
	}
	if (modeType == 1)
	{
	this->player2 = new PaddlePlayer(1);
	this->ballObejct = new Ball(this->score1, this->score2, this->player1, this->player2, this->Rock);
	}
	///Ball

	this->ballObejct->Reset(window);
}
void MainMatch::Update(sf::RenderWindow *window)
{
	if (!MatchEnd)
	{
		this->ballObejct->Update(window);
		this->player1->Update();
		if (modeType == 0)
		{
			this->AI->Update();
		}
		if (modeType == 1)
		{
			this->player2->Update();
		}
		this->score1->Update();
		this->score2->Update();
		this->Rock->Update();
	}
	if (this->score1->myScore >= 5)
	{
		MatchEnd = true;
		this->EndName = new sf::Text("Player1 Win\n Press Space to Continue", *this->font, 32U);
		this->EndName->setOrigin(this->EndName->getGlobalBounds().width / 2, this->EndName->getGlobalBounds().height / 2);
		this->EndName->setPosition(window->getSize().x / 2, 300);
		if (!WinSoundPlay)
		{
			this->bf->loadFromFile("Sound/Win.wav");
			this->sound = new sf::Sound(*this->bf);
			this->sound->setLoop(false);
			this->sound->setVolume(100);
			this->sound->play();
			WinSoundPlay = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			CoreState.SetState(new MainMenu());
		}
	}
	if (this->score2->myScore >= 5)
	{
		MatchEnd = true;
		this->EndName = new sf::Text("Player2 Win\n Press Space to Continue", *this->font, 32U);
		this->EndName->setOrigin(this->EndName->getGlobalBounds().width / 2, this->EndName->getGlobalBounds().height / 2);
		this->EndName->setPosition(window->getSize().x / 2, 300);

		if (!WinSoundPlay)
		{
			this->bf->loadFromFile("Sound/Win.wav");
			this->sound = new sf::Sound(*this->bf);
			this->sound->setLoop(false);
			this->sound->setVolume(100);
			this->sound->play();
			WinSoundPlay = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			CoreState.SetState(new MainMenu());
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		CoreState.SetState(new MainMenu());
	}
}
void MainMatch::Render(sf::RenderWindow *window)
{
	if (!MatchEnd)
	{
		window->draw(*this->score1);
		window->draw(*this->score2);
		window->draw(*this->player1);
		if (modeType == 0)
		{
			window->draw(*this->AI);
		}
		if (modeType == 1)
		{
			window->draw(*this->player2);
		}
		window->draw(*this->ballObejct);
		window->draw(*this->Rock);
	}
	else
	{
		window->draw(*this->EndName);
	}
}
void MainMatch::Destory(sf::RenderWindow *window)
{
	delete this->player1;
	if (modeType == 0)
	{
		delete this->AI;
	}
	if (modeType == 1)
	{
		delete this->player2;
	}
	delete this->ballObejct;
	delete this->score1;
	delete this->score2;
	delete this->Rock;
	delete this->sound;
	delete this->bf;

	if (MatchEnd)
	{
		delete this->EndName;
	}
}
