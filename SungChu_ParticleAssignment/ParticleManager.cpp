#include "ParticleManager.h"

ParticleManager::ParticleManager(sf::RenderWindow* window)
{
	//m_particlesCount = new sf::Text;
	//m_font = new sf::Font;
	m_particleCount = new sf::Text;
	m_font = new sf::Font;
	m_font->loadFromFile("Fonts/georgiab.ttf");
	m_particleCount->setFont(*m_font);
	m_particleCount->setCharacterSize(24);
	m_particleCount->setString("Next particles Count: " + std::to_string(particleCount));
	m_particleCount->setPosition(window->getSize().x - m_particleCount->getGlobalBounds().width - 40, 20);
}

ParticleManager::~ParticleManager()
{

}

void ParticleManager::Update(sf::Time deltaTime)
{
	int temperaryCount = 0;
	for (std::size_t i = 0; i < m_particleSystem.size(); ++i)
	{
		m_particleSystem[i].Update(deltaTime);
		temperaryCount += m_particleSystem[i].GetParticleCount();
	}
	particleCount = temperaryCount;

	m_particleCount->setString("Particles Count: " + std::to_string(particleCount));

}

void ParticleManager::Draw(sf::RenderWindow* window)
{
	for (std::size_t i = 0; i < m_particleSystem.size(); ++i)
	{
		window->draw(m_particleSystem[i]);
	}
	window->draw(*m_particleCount);

}

void ParticleManager::newParticleSystem(sf::Vector2f position, int mode)
{
	if (mode == 0)
	{
		ParticleSystem* FirstParticleSystem;
		int baseCount = 100;
		if (m_particleSystem.size() == 0)
		{
			FirstParticleSystem = new ParticleSystem(baseCount, "mytexture.png", mode, 0.2f, 0.2f, 256, 256);
		}
		else
		{
			FirstParticleSystem = new ParticleSystem(particleCount/ m_particleSystem.size(), "mytexture.png", mode, 0.2f, 0.2f, 256, 256);
		}
		FirstParticleSystem->SetEmitter(position);
		FirstParticleSystem->SetEmitterAngle(240, 300);
		FirstParticleSystem->SetInitialSpeed(800,200);
		FirstParticleSystem->SetPLifeTime(500, 800);
		FirstParticleSystem->setSpeedChange(true, 0.2f, 2.0f);
		FirstParticleSystem->scaleChange(true, 0.05f, 0.05f, 1000.0f);
		FirstParticleSystem->rotateOverTime(true, 0.1f);
		if (m_particleSystem.size() > 2)
		{
			m_particleSystem.erase(m_particleSystem.begin());
			//m_particleSystem.clear();
		}
		m_particleSystem.emplace_back(*FirstParticleSystem);
	}
	if (mode == 1)
	{
		ParticleSystem* FirstParticleSystem;
		int baseCount = 80;
		if (m_particleSystem.size() == 0)
		{
			FirstParticleSystem = new ParticleSystem(baseCount, "Star_06.png", mode, 0.01f, 0.01f, 256, 256);
		}
		else
		{
			FirstParticleSystem = new ParticleSystem(particleCount / m_particleSystem.size(), "Star_06.png", mode, 0.01f, 0.01f, 256, 256);
		}
		FirstParticleSystem->SetEmitter(position);
		FirstParticleSystem->SetEasingMode(ParticleSystem::easingMode::quad);
		FirstParticleSystem->SetEmitterAngle(120, 220);
		FirstParticleSystem->SetInitialSpeed(200, 400);
		FirstParticleSystem->SetPLifeTime(350, 700);
		FirstParticleSystem->setSpeedChange(true, 0.1f, -0.1f);
		FirstParticleSystem->scaleChange(true, 0.5f, 0.5f, 1000.0f);
		FirstParticleSystem->rotateOverTime(true, 0.15f);
		FirstParticleSystem->SetParticleColor(200, 255, 255);
		if (m_particleSystem.size() > 2)
		{
			m_particleSystem.erase(m_particleSystem.begin());
			//m_particleSystem.clear();
		}
		m_particleSystem.emplace_back(*FirstParticleSystem);
	}
	if (mode == 2)
	{
		ParticleSystem* FirstParticleSystem;
		int baseCount = 60;
		if (m_particleSystem.size() == 0)
		{
			FirstParticleSystem = new ParticleSystem(baseCount, "Fire_01.png", mode, 0.5f, 0.5f, 256, 256);
		}
		else
		{
			FirstParticleSystem = new ParticleSystem(particleCount / m_particleSystem.size(), "Fire_01.png", mode, 0.5f, 0.5f, 256, 256);
		}
		FirstParticleSystem->SetEmitter(position);
		FirstParticleSystem->SetEasingMode(ParticleSystem::easingMode::sin);
		FirstParticleSystem->SetEmitterAngle(60, 150);
		FirstParticleSystem->SetInitialSpeed(200, 150);
		FirstParticleSystem->SetPLifeTime(200, 800);
		FirstParticleSystem->setSpeedChange(true, 0.2f, -0.5f);
		FirstParticleSystem->scaleChange(true, 1.0f, 1.0f, 1000.0f);
		FirstParticleSystem->rotateOverTime(true, 0.1f);
		FirstParticleSystem->SetParticleColor(std::rand() % (255 - 240 + 1) + 240, std::rand() % (120 - 100 + 1) + 100, std::rand() % (30 - 20 + 1) + 20);
		if (m_particleSystem.size() > 2)
		{
			m_particleSystem.erase(m_particleSystem.begin());
			//m_particleSystem.clear();
		}
		m_particleSystem.emplace_back(*FirstParticleSystem);
	}
	//ToDo
	//Allow 3 particle system spawn together
	//Press 1,2,3 to select particle

	//Do something here
	/*ParticleSystem* particleSystemToAdd = new ParticleSystem(m_textureManager);
	particleSystemToAdd->SetEmitter(position);
	particleSystemToAdd->SetEmitAngle(rand() % 360);
	particleSystemToAdd->SetInitialSpeed(rand() % 200);
	m_particleSystem.emplace_back(*particleSystemToAdd);*/
}
