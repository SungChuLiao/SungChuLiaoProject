#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include "ParticleManager.h"
int particleMode = 1;
int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SungChuLiao_Particle");

	// create the particle system
	//ParticleSystem particles(50, "mytexture.png",0,0.1f,0.1f,256,256);
	ParticleManager* myParticleManager = new ParticleManager(&window);
	// create a clock to track the elapsed time
	sf::Clock clock;
	sf::Clock m_timer;
	sf::Clock m_actTimer;
	float timer = 0.8f;
	float actTimer = 0.08f;
	sf::Text* m_guild = new sf::Text;
	sf::Text* m_mode = new sf::Text;
	sf::Font* m_font = new sf::Font;
	m_font->loadFromFile("Fonts/georgiab.ttf");
	m_guild->setFont(*m_font);
	m_guild->setCharacterSize(16);
	m_guild->setString("Press left mouse button to create particle with particle mode \nPress '+' to add particles \nPress '-' to remove particles \nPress '1' or '2' or '3' to switch particle mode \n mode 0 is linear, mode 1 is quadIn, mode 2 is SinIn \n\nAfter press '+' to add particle\nneed to press left mouse button to generate a new particle to see result");
	m_guild->setPosition(20, 20);
	m_mode->setFont(*m_font);
	m_mode->setCharacterSize(16);
	m_mode->setString("Mode: " + std::to_string(particleMode));
	m_mode->setPosition(100, 600);

	// run the main loop
	while (window.isOpen())
	{

		// handle events
		sf::Event event;
		if (actTimer < 0.1f)
			actTimer += m_timer.restart().asSeconds();
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				particleMode = 0;
				m_mode->setString("Mode: " + std::to_string(particleMode));
				actTimer = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				particleMode = 1;
				m_mode->setString("Mode: " + std::to_string(particleMode));
				actTimer = 0;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				particleMode = 2;
				m_mode->setString("Mode: " + std::to_string(particleMode));
				actTimer = 0;
			}
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (timer < 1.0f)
				timer += m_timer.restart().asSeconds();
			else
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i mouse = sf::Mouse::getPosition(window);
					myParticleManager->newParticleSystem((sf::Vector2f)mouse, particleMode);
					timer = 0;
				}
			}
		}	
		// update it
		sf::Time deltaTime = clock.restart();
		myParticleManager->Update(deltaTime);

		// draw it
		window.clear();
		myParticleManager->Draw(&window);
		window.draw(*m_guild);
		window.draw(*m_mode);
		//window.draw(particles);
		window.display();
	}
	//ToDo

	//pART 1
	//Tell player to press e or q to increase particle count
	//UI

	return 0;
}
