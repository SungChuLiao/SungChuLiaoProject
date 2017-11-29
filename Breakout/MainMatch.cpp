#include "MainMatch.h"
#include "MainMenu.h"



MainMatch::MainMatch(int BrickRowNum, int BrickColumnNum, float NewSpeed, int Level)
{
	this->level = Level;
	this->BrickColumnNum = BrickColumnNum;
	this->BrickRowNum = BrickRowNum;
	this->BrickNum = 0;
	this->MatchEnd = false;
	this->WinSoundPlay = false;
	this->myScore = 0;
	this->NewSpeed = NewSpeed;
}
void MainMatch::Initiallize(sf::RenderWindow *window)
{
	this->bf = new sf::SoundBuffer();
	this->bf->loadFromFile("Sound/BGM.flac");
	this->sound = new sf::Sound(*this->bf);
	this->sound->setLoop(true);
	this->sound->setVolume(10);
	this->sound->play();
	this->font = new sf::Font();
	this->font->loadFromFile("Image/myFont.ttf");
	this->myScore = new Score(*font, 32U);
	this->myScore->setPosition(window->getSize().x / 6 - this->myScore->getGlobalBounds().width, window->getSize().y - this->myScore->getGlobalBounds().height - 200);
	this->myLife = new Life(*font, 32U, 3);
	this->myLife->setPosition(window->getSize().x/6 - this->myLife->getGlobalBounds().width, window->getSize().y - this->myLife->getGlobalBounds().height - 150);
	
	this->paddle = new Paddle(this->NewSpeed);
	
	this->ball = new Ball(this->paddle, 2, this->myLife, this->NewSpeed);
	
	for (int i = 0; i < BrickRowNum; ++i)
	{
		for (int k = 0; k < BrickColumnNum; k++)
		{
			this->bricks.push_back(std::unique_ptr<Brick>(new Brick(1, this->ball, this->myScore)));
			this->bricks[bricks.size() - 1]->setPosition(i * this->bricks[bricks.size() - 1]->getGlobalBounds().width * 1 + 75,
				k * this->bricks[bricks.size() - 1]->getGlobalBounds().height * 1.05 + 50);
			//this->brick[this->BrickNum] = new Brick(1, this->ball, this->myScore);
			/*this->brick[this->BrickNum]->setPosition(i * this->brick[this->BrickNum]->getGlobalBounds().width * 1 + 75, 
													 k * this->brick[this->BrickNum]->getGlobalBounds().height * 1.05 + 50);
			BrickNum++;*/
		
		}
	}
	if (this->level == 1)
	{
		this->bricks[0]->MoreHP();
		this->bricks[1]->MoreHP();
		this->bricks[2]->MoreHP();
		this->bricks[3]->MoreHP();
		this->bricks[4]->MoreHP();
		this->bricks[5]->MoreHP();
		this->bricks[9]->MoreHP();
		this->bricks[10]->MoreHP();
		this->bricks[14]->MoreHP();
		this->bricks[15]->MoreHP();
		this->bricks[19]->MoreHP();
		this->bricks[20]->MoreHP();
		this->bricks[24]->MoreHP();
		this->bricks[25]->MoreHP();
		this->bricks[29]->MoreHP();
		this->bricks[30]->MoreHP();
		this->bricks[31]->MoreHP();
		this->bricks[32]->MoreHP();
		this->bricks[33]->MoreHP();
		this->bricks[34]->MoreHP();
		//this->brick[0]->MoreHP();
		//this->brick[BrickNum -1]->MoreHP();
		//Remember
	}
	if (this->level == 2)
	{
		this->bricks[7]->MoreHP();
		this->bricks[10]->MoreHP();
		this->bricks[31]->MoreHP();
		this->bricks[34]->MoreHP();
		this->bricks[14]->speedBall();
		this->bricks[15]->speedBall();
		this->bricks[20]->speedBall();
		this->bricks[21]->speedBall();
		this->bricks[26]->speedBall();
		this->bricks[27]->speedBall();

	}
	this->ball->Reset(window);

}
void MainMatch::Update(sf::RenderWindow *window)
{
	if (!this->MatchEnd)
	{
		this->paddle->Update();
		this->ball->Update(window);
		this->myLife->Update();
		this->myScore->Update();
		for (int i = 0; i < bricks.size(); ++i)
		{
			bricks[i]->Update();
			//this->brick[i]->Update();
		}
		//GameOver
		if (this->myLife->myLife <= 0)
		{
			this->MatchEnd = true;
			this->EndName = new sf::Text("\n\n\n\n\nGameOver\n Press Space to Continue", *this->font, 32U);
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
		}
		if (this->myScore->myScore >= bricks.size())
		{
			this->MatchEnd = true;
			this->EndName = new sf::Text("\n\n\n\n\nPlayerWin!\n Press Space to Continue", *this->font, 32U);
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
				BrickColumnNum += 1;
				this->level += 1;
				NewSpeed = NewSpeed * 1.2;
				if (BrickColumnNum > 6)
				{
					BrickColumnNum = 4;
				}
				if (this->level > 2)
				{
					this->level = 0;
				}
			}
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			CoreState.SetState(new MainMatch(BrickRowNum, BrickColumnNum,NewSpeed,this->level));
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		CoreState.SetState(new MainMenu());
	}

}
void MainMatch::Render(sf::RenderWindow *window)
{
	if (!this->MatchEnd)
	{
		window->draw(*this->paddle);
		window->draw(*this->ball);
		window->draw(*this->myLife);
		for (int i = 0; i < bricks.size(); ++i)
		{
			//window->draw(*this->brick[i]);
			window->draw(*this->bricks[i]);
		}

	}
	else
	{
		window->draw(*this->EndName);
	}
	window->draw(*this->myScore);
}
void MainMatch::Destory(sf::RenderWindow *window)
{
	delete this->paddle;
	delete this->ball;
	delete this->myLife;
	delete this->myScore;
	delete this->sound;
	delete this->bf;
	bricks.erase(bricks.begin(), bricks.end());
	if (MatchEnd)
	{
		delete this->EndName;
	}
}
