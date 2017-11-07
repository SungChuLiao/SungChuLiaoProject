#include "ball.h"

Ball::Ball(Score* score1, Score* score2, Paddle* player1, Paddle* player2, Obstacle* obstacle)
{
	this->Load("myBall.png");
	this->score1 = score1;
	this->score2 = score2;
	this->player1 = player1;
	this->player2 = player2;
	this->obstacle = obstacle;
	this->timer = 0;
	this->bf = new sf::SoundBuffer();
	this->bf->loadFromFile("Sound/Bounce.wav");
	this->sound = new sf::Sound(*this->bf);
}
void Ball::Update(sf::RenderWindow* window)
{
	if (this->timer > 0)
	{
		this->timer--;
	}
	if (this->CheckCollision(this->player1))
	{
		if (this->timer > 0)
		{
			this->velocity.y *= -1;
		}
		if (this->timer <= 0)
		{
			this->sound->play();
			this->timer = 20.0f;
			this->velocity.x *= -1.05f;
			if (this->velocity.y > 0)
			{
				if (this->player1->velocity.y > 0)
				{
					this->velocity.y += this->velocity.y * 0.15f;
				}
				else if (this->player1->velocity.y < 0)
				{
					this->velocity.y += this->velocity.y * -0.15f;
				}
			}
			else if (this->velocity.y < 0)
			{
				if (this->player1->velocity.y > 0)
				{
					this->velocity.y += this->velocity.y * -0.15f;
				}
				else if (this->player1->velocity.y < 0)
				{
					this->velocity.y += this->velocity.y * 0.15f;
				}
			}
		}
		/*sf::Vector2f a(this->getPosition().x, this->getPosition().y);
		sf::Vector2f b(this->player1->getPosition().x - 200, this->player1->getPosition().y + 256);
		float c = atan2f(a.y, a.x)- atan2f(b.y, b.x);
		this->velocity.y *= c;*/
	}
	if (this->CheckCollision(this->player2))
	{
		if (this->timer > 0)
		{
			this->velocity.y *= -1;
		}
		if (this->timer <= 0)
		{
			this->sound->play();
			this->timer = 20.0f;
			this->velocity.x *= -1.05f;
			/*sf::Vector2f a(this->getPosition().x, this->getPosition().y);
			sf::Vector2f b(this->player2->getPosition().x + 264, this->player2->getPosition().y + 256);
			float c = atan2f(a.y, a.x) - atan2f(b.y, b.x);
			this->velocity.y *= c;*/
			if (this->velocity.y > 0)
			{
				if (this->player2->velocity.y > 0)
				{
					this->velocity.y += this->velocity.y * 0.15f;
				}
				else if (this->player2->velocity.y < 0)
				{
					this->velocity.y += this->velocity.y * -0.15f;
				}
			}
			else if (this->velocity.y < 0)
			{
				if (this->player2->velocity.y > 0)
				{
					this->velocity.y += this->velocity.y * -0.15f;
				}
				else if (this->player2->velocity.y < 0)
				{
					this->velocity.y += this->velocity.y * 0.15f;
				}
			}
		}
	}
	if (this->CheckCollision(this->obstacle))
	{
		if (this->timer > 0)
		{
			this->velocity.y *= -1;
			this->obstacle->velocity.y *= -1;

			//this->obstacle->Stop();
		}
		if (this->timer <= 0)
		{
			this->sound->play();
			this->timer = 30.0f;
			this->velocity.x *= -1.0f;
		}
		/*if (this->getPosition().x >= this->obstacle->getPosition().x + this->obstacle->getGlobalBounds().width) // check obstacle right
		{
			if (this->velocity.x <= 0)
			{
				this->velocity.x *= -1.0f;
			}
		}
		if (this->getPosition().x + this->getGlobalBounds().width <= this->obstacle->getPosition().x) // check obstacle left
		{
			if (this->velocity.x >= 0)
			{
				this->velocity.x *= -1.0f;
			}
		}
		if (this->getPosition().y >= this->obstacle->getPosition().y + this->obstacle->getGlobalBounds().height) //check obstacle button
		{
			if (this->velocity.y <= 0)
			{
				this->velocity.y *= -1.0f;
			}
		}
		if (this->getPosition().y + this->getGlobalBounds().height <= this->obstacle->getPosition().y) //check obstacle top
		{
			if (this->velocity.y >= 0)
			{
				this->velocity.y *= -1.0f;
			}
		}*/
	}
	if (this->getPosition().y < 0 || this->getPosition().y + this->getGlobalBounds().height > 900)
	{
		this->velocity.y *= -1;
		//Do SOMETHING

	}

	if (this->getPosition().x < 58)
	{
		this->score2->AddScore();
		this->Reset(window);

	}
	if (this->getPosition().x + this->getGlobalBounds().width > 1142)
	{
		this->score1->AddScore();
		this->Reset(window);
	}
	Object::Update();
}
void Ball::Reset(sf::RenderWindow * window)
{
	this->velocity.x = ((rand() % 2) == 0) ? 1.0f : -1.0f;
	this->velocity.y = ((rand() % 2) == 0) ? 1.0f : -1.0f;
	this->setPosition(window->getSize().x / 2, window->getSize().y / 2);
	this->player1->setPosition(0, 350);
	this->player2->setPosition(window->getSize().x - this->player2->getGlobalBounds().width, 350);
	this->obstacle->setPosition(window->getSize().x / 2, ((rand() % 2) == 0) ? 172 : 600);
	this->obstacle->velocity.y = ((rand() % 2) == 0) ? 0.4f : -0.4f;
}