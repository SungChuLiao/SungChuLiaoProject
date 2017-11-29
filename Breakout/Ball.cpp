#include "ball.h"
#include "iostream"
using namespace std;
Ball::Ball(Paddle* paddle, float speed, Life* myLife, float NewSpeed)
{
	this->Load("myBall.png");
	this->paddle = paddle;
	this->bf = new sf::SoundBuffer();
	this->bf->loadFromFile("Sound/Bounce.wav");
	this->sound = new sf::Sound(*this->bf);
	this->bf2 = new sf::SoundBuffer();
	this->bf2->loadFromFile("Sound/Lose.wav");
	this->sound2 = new sf::Sound(*this->bf2);
	this->GameStart = false;
	this->PI = 3.14159265359f;
	this->ballangle = 0;
	this->speed = speed;
	this->mylife = myLife;
	this->ExSpeed = NewSpeed;
}
void Ball::Update(sf::RenderWindow* window)
{
	sf::Clock clock;

	float deltaTime = clock.restart().asSeconds();

	if (GameStart == false)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			GameStart = true;
			BallActive(window);
		}
	}
	if (!GameStart)
	{
		this->setPosition(paddle->getPosition().x + paddle->getGlobalBounds().width/2 - this->getGlobalBounds().width/2, 
						  paddle->getPosition().y - paddle->getGlobalBounds().height / 2 - this->getGlobalBounds().height/2 - 10);
	}
	else
	{
		if (this->CheckCollision(this->paddle))
		{
			this->sound->play();
			sf::Vector2f p(this->paddle->getPosition().x + this->paddle->getGlobalBounds().width / 2, this->paddle->getPosition().y + this->paddle->getGlobalBounds().height + 30); //point position
			sf::Vector2f b(this->getPosition().x + this->getGlobalBounds().width / 2, this->getPosition().y + this->getGlobalBounds().height/2); // ball position
			sf::Vector2f v = b - p;
			float l = sqrtf(v.x*v.x + v.y*v.y); // 5
			v = v / l;
			this->velocity= v * this->speed * ExSpeed;
		}
	}
	if (this->getPosition().y < 0 )
	{
		this->sound->play();
		this->velocity.y *= -1;
	}
	if (this->getPosition().y + this->getGlobalBounds().height > 900)
	{
		sound2->play();
		this->mylife->LoseLife();
		Reset(window);
	}
	if (this->getPosition().x < 0 || (this->getPosition().x + this->getGlobalBounds().width > 1200))
	{
		this->sound->play();

		this->velocity.x *= -1;
	}
	Object::Update();
}
void Ball::Reset(sf::RenderWindow * window)
{
	this->paddle->setPosition(window->getSize().x / 2 - this->paddle->getGlobalBounds().width / 2, window->getSize().y - 100);
	this->setPosition(paddle->getPosition().x + paddle->getGlobalBounds().width / 2 - this->getGlobalBounds().width / 2,
		  paddle->getPosition().y - paddle->getGlobalBounds().height / 2 - this->getGlobalBounds().height / 2 - 10);
	GameStart = false;
}
void Ball::BallActive(sf::RenderWindow * window)
{
	sf::Vector2f p( window->getSize().x/2, window->getSize().y + 200); //point position
	sf::Vector2f b(this->getPosition().x + this->getGlobalBounds().width / 2, this->getPosition().y + this->getGlobalBounds().height / 2); // ball position
	sf::Vector2f v = b - p;
	float l = sqrtf(v.x*v.x + v.y*v.y); // 5
	v = v / l;
	this->velocity = v * this->speed * ExSpeed;
}
