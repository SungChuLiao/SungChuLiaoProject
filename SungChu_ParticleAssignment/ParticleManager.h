#pragma once
#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"

class ParticleManager
{
public:
	ParticleManager(sf::RenderWindow* window);
	~ParticleManager();
	void Update(sf::Time deltaTime);
	void Draw(sf::RenderWindow* window);
	void newParticleSystem(sf::Vector2f position, int mode);
private:
	std::vector<ParticleSystem> m_particleSystem;
	int particleSystemCount = 0;
	sf::Text* m_particleCount = new sf::Text;
	sf::Font* m_font = new sf::Font;
	int particleCount = 0;
};