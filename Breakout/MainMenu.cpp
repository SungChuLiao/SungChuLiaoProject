#include <iostream>
#include "MainMenu.h"
#include "MainMatch.h"
#include <SFML/Graphics.hpp>


void MainMenu::Initiallize(sf::RenderWindow *window)
{
	this->bf = new sf::SoundBuffer();
	//this->bf->loadFromFile("Sound/BGM.flac");
	this->sound = new sf::Sound(*this->bf);
	this->sound->setLoop(true);
	this->sound->setVolume(10);
	this->sound->play();

	this->selected = 0;
	this->font = new sf::Font();
	this->font->loadFromFile("Image/myFont.ttf");

	this->title = new sf::Text("BreakOut", *this->font, 160U);
	this->title->setOrigin(this->title->getGlobalBounds().width / 2, this->title->getGlobalBounds().height / 2);
	this->title->setPosition(window->getSize().x / 2, window->getSize().y / 6);

	this->Play = new sf::Text("Play", *this->font, 64U);
	this->Play->setOrigin(this->Play->getGlobalBounds().width / 2, this->Play->getGlobalBounds().height / 2);
	this->Play->setPosition(window->getSize().x / 2, window->getSize().y / 2);

	this->quit = new sf::Text("Quit", *this->font, 64U);
	this->quit->setOrigin(this->quit->getGlobalBounds().width / 2, this->quit->getGlobalBounds().height / 2);
	this->quit->setPosition(window->getSize().x / 2, window->getSize().y / 2 + 160);
}
void MainMenu::Update(sf::RenderWindow *window)
{
	if (this->upKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && !this->upKey)
	{
		this->selected -= 1;
	}
	if (this->downKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && !this->downKey)
	{
		this->selected += 1;
	}
	if (this->selected > 1)
	{
		this->selected = 0;
	}
	if (this->selected < 0)
	{
		this->selected = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
	{
		switch (this->selected)
		{
		case 0:
			CoreState.SetState(new MainMatch(7,4,1,0));
			break;
		case 1:
			quitGame = true;
			break;
		}
	}
	this->upKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
	this->downKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);

}
void MainMenu::Render(sf::RenderWindow *window)
{
	this->Play->setFillColor(sf::Color::White);
	this->quit->setFillColor(sf::Color::White);

	switch (this->selected)
	{
	case 0:
		this->Play->setFillColor(sf::Color::Red);
		break;
	case 1:
		this->quit->setFillColor(sf::Color::Red);
		break;
	}
	window->draw(*this->title);
	window->draw(*this->Play);
	window->draw(*this->quit);

}
void MainMenu::Destory(sf::RenderWindow *window)
{
	delete this->font;
	delete this->title;
	delete this->Play;
	delete this->quit;
	delete this->sound;
	delete this->bf;
}