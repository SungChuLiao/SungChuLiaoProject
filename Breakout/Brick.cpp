#include "Brick.h"

Brick::Brick(int hp, Ball* ball, Score* myScore)
{
	this->hp = hp;

	this->ball = ball;
	this->Load("Brick.png");
	this->isDead = false;
	this->myScore = myScore;
	this->Mode = 0;
	OriginalColor = this->getColor();
	this->bf = new sf::SoundBuffer();
	this->bf->loadFromFile("Sound/Break.wav");
	this->sound = new sf::Sound(*this->bf);
}
void Brick::Update()
{
	if (this->CheckCollision(this->ball))
	{
		this->sound->play();

		sf::Vector2f p(this->getPosition().x + this->getGlobalBounds().width / 2, this->getPosition().y + this->getGlobalBounds().height/2); //point position
		sf::Vector2f b(this->ball->getPosition().x + this->ball->getGlobalBounds().width / 2, this->ball->getPosition().y + this->ball->getGlobalBounds().height / 2); // ball position
		sf::Vector2f v = b - p;
		float l = sqrtf(v.x*v.x + v.y*v.y); // 5
		v = v / l;
		if (this->Mode == 2)
		{
			this->ball->velocity.y = v.y / sqrtf(v.y * v.y) * this->ball->speed * this->ball->ExSpeed * 1.5;
		}
		else
		{
			this->ball->velocity.y = v.y / sqrtf(v.y * v.y) * this->ball->speed * this->ball->ExSpeed;
		}
		GetHit();

		if (this->hp <= 0)
		{
			this->setPosition(-500, 0);
			this->myScore->AddScore();
		}
	}
}
void Brick::GetHit()
{
	if (this->Mode == 1 )
	{
		this->setColor(OriginalColor);
	}
	this->hp -= 1;
}
void Brick::Draw(sf::RenderWindow *window)
{

}
void Brick::MoreHP()
{
	this->hp = 2;
	this->Mode = 1;
	this->setColor(sf::Color::Color(90, 90, 140, 255));
}
void Brick::speedBall()
{
	this->Mode = 2;
	this->setColor(sf::Color::Red);
}
