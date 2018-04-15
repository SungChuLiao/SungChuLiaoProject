#include "ParticleSystem.h"
#include <math.h>
#include <iostream>
#define PI 3.1415926

ParticleSystem::ParticleSystem(unsigned int count, std::string imageName, int mode, float scaleSizeX, float scaleSizeY, float imageSizeX, float imageSizeY)
{
	m_particles.resize(count);
	m_count = count;
	//m_shapes.resize(count);
	m_emiterLifetime = sf::seconds(3);
	m_emitter.x = 0;
	m_emitter.y = 0;
	this->movementMode = mode;
	this->m_imageSizeX = imageSizeX;
	this->m_imageSizeY = imageSizeY;
	this->m_scaleSizeX = scaleSizeX;
	this->m_scaleSizeY = scaleSizeY;
	LoadTexture(imageName);
	/*for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		ResetParticle(i);
	}*/
}
void ParticleSystem::LoadTexture(std::string imageName)
{
	m_texture.loadFromFile("Image/Sprite/" + imageName);
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		m_particles[i].sprite.setTexture(m_texture);
		m_particles[i].sprite.setTextureRect(sf::IntRect(0, 0, m_imageSizeX, m_imageSizeY));
		//sf::Vector2f size;
		m_particles[i].sprite.setScale(sf::Vector2f(m_scaleSizeX, m_scaleSizeY));
	}
}
void ParticleSystem::SetEmitter(sf::Vector2f position)
{
	m_emitter = position;
}
void ParticleSystem::Update(sf::Time deltaTime)
{
	if (actTimer < 0.8f)
		actTimer += deltaTime.asSeconds();
	else
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			m_count += 20;
			m_particles.resize(m_count);
			actTimer = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			if (m_count >= 20)
			{
				for (int i = 0; i < 20; i++)
				{
					m_particles.pop_back();
				}
				m_count -= 20;
				m_particles.resize(m_count);
			}
			actTimer = 0;
		}
	}
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		// update the particle lifetime
		Particle& p = m_particles[i];
		p.lifetime -= deltaTime;
		p.timePassed += deltaTime;

		// if the particle is dead, respawn it
		if (p.lifetime <= sf::Time::Zero)
			ResetParticle(i);

		//Give it Acceleration

		switch (currentEasing)
		{
		case liner:
			p.VelocityAcceleration = 0;
			p.addSpeed = 0;
			p.rotationAcceleration = 0;
		break;
		case quad:
			p.VelocityAcceleration = QuadraticEasingIn(p.timePassed) / 10 + p.VelocityAcceleration;
			p.addSpeed = QuadraticEasingIn(p.timePassed) / 10 + p.addSpeed;
			p.rotationAcceleration = QuadraticEasingIn(p.timePassed) + p.rotationAcceleration;
		break;
		case sin:
			p.VelocityAcceleration = SinEasingIn(p.timePassed) / 100 + p.VelocityAcceleration;
			p.addSpeed = SinEasingIn(p.timePassed) / 10 + p.addSpeed;
			p.rotationAcceleration = SinEasingIn(p.timePassed) / 10 + p.rotationAcceleration;
		break;

		}

		/*if (haveSpeedUp)
		{
			p.velocity.y += m_speedValueY;
			p.velocity.x += m_speedValueX;
		}*/

		/*if (canRotate)
		{
			p.sprite.setOrigin(m_imageSizeX / 2, m_imageSizeY / 2);
			p.sprite.rotate(this->rotateValue);
		}*/

		//Scale Changed
		if (haveScaleChange)
		{
			sf::Vector2f resultScale = p.sprite.getScale();
			resultScale += (p.newSize - resultScale) / scaleSpeedDuration;
			p.sprite.setScale(resultScale);
			//resultScale.x += ((p.lifetime - p.timePassed) / p.lifetime) * m_particles[i].newSize.x;
			//resultScale.y += ((p.lifetime - p.timePassed) / p.lifetime) * m_particles[i].newSize.y;
		}
		//update position(x,y. m_speedValueX and m_speedValueY is using for extra force)
		p.velocity += sf::Vector2f(p.VelocityAcceleration * deltaTime.asMilliseconds() + m_speedValueX * std::cos(p.angle), p.VelocityAcceleration * deltaTime.asMilliseconds() * std::sin(p.angle) + m_speedValueY);
		sf::Vector2f lastFramePos = p.sprite.getPosition();
		sf::Vector2f newPos = lastFramePos + p.velocity * deltaTime.asSeconds();
		p.sprite.setPosition(newPos);
		// update rotation (this->rotateValue is a value for strength)
		p.rotation += p.rotationAcceleration * this->rotateValue * deltaTime.asSeconds();
		p.sprite.rotate(p.rotation);
		// update the alpha (transparency) of the particle according to its lifetime
		float ratio = p.lifetime.asSeconds() / deltaTime.asSeconds();
		p.sprite.setColor(sf::Color(p.colorR, p.colorB, p.colorG, static_cast<sf::Uint8>(ratio * 255)));
	}
}
void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= sf::Transformable::getTransform();

	// Set texture
	states.texture = &m_texture;

	// draw the vertex array
	for (int i = 0; i < m_particles.size(); i++)
		target.draw(m_particles[i].sprite, states);
}
void ParticleSystem::ResetParticle(std::size_t index)
{
	// give a random velocity and lifetime to the particle
	float angle = (std::rand() % (emitterAngleMax - emitterAngleMin + 1) + emitterAngleMin) * 3.14f / 180.0f;
	float speed = (std::rand() % 60) + initialSpeed;

	m_particles[index].timePassed = sf::Time::Zero;
	m_particles[index].angle = angle;
	m_particles[index].rotation = 0;
	m_particles[index].sprite.setScale(m_scaleSizeX, m_scaleSizeY);
	m_particles[index].StartSpeed = 0;
	m_particles[index].size = sf::Vector2f(1.0f, 1.0f);
	m_particles[index].VelocityAcceleration = 0;
	m_particles[index].rotationAcceleration = 0;
	//m_particles[index].lifetime = sf::milliseconds(p_lifetime);
	//Movement
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
	m_particles[index].lifetime = sf::milliseconds((std::rand() % p_lifetimeBase) + p_lifetimeAdd);

	m_particles[index].sprite.setPosition(m_emitter);

}
int ParticleSystem::GetParticleCount()
{
	return m_count;
}
void ParticleSystem::SetEmitterAngle(int angleMin, int angleMax)
{
	this->emitterAngleMin = angleMin;
	this->emitterAngleMax = angleMax;

}
void ParticleSystem::SetInitialSpeed(int BaseinitialSpeed, int AddinitialSpeed)
{
	m_baseinitialSpeed = BaseinitialSpeed;
	m_addinitialSpeed = AddinitialSpeed;
	this->initialSpeed = (rand() % m_baseinitialSpeed + m_addinitialSpeed);
}
void ParticleSystem::SetPLifeTime(int newLifeTimeBase, int newLifeTimeAdd)
{
	this->p_lifetimeBase = newLifeTimeBase;
	this->p_lifetimeAdd = newLifeTimeAdd;
}
void ParticleSystem::setSpeedChange(bool havespeedUp, float speedValueX, float speedValueY)
{
	this->haveSpeedUp = havespeedUp;
	this->m_speedValueX = (rand()) / (float)RAND_MAX * speedValueX;
	this->m_speedValueY = (rand()) / (float)RAND_MAX * speedValueY;
}
void ParticleSystem::SetNewCount(int count)
{
	this->m_count = count;
}
void ParticleSystem::scaleChange(bool haveChange, float newScaleX, float newScaleY, float scaleSpeed)
{
	this->haveScaleChange = haveChange;
	this->scaleSpeedDuration = scaleSpeed;
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		m_particles[i].newSize = sf::Vector2f(newScaleX, newScaleY);
	}
}
void ParticleSystem::rotateOverTime(bool haveRotation, float rotationValue)
{
	this->canRotate = haveRotation;
	this->rotateValue = rotationValue;
}
void ParticleSystem::SetParticleColor(int r, int b, int g)
{
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		m_particles[i].colorR = r;
		m_particles[i].colorB = b;
		m_particles[i].colorG = g;
	}
}
void ParticleSystem::SetEasingMode(easingMode easingMode)
{
	currentEasing = easingMode;
}
float ParticleSystem::QuadraticEasingIn(sf::Time timePassed)
{
	float t = timePassed.asMilliseconds();
	t /= (std::rand() % p_lifetimeBase) + p_lifetimeAdd;
	return 0.01f *t*t*t + 0.01f;
}
float ParticleSystem::SinEasingIn(sf::Time timePassed)
{
	float t = timePassed.asMilliseconds();
	t /= (std::rand() % p_lifetimeBase) + p_lifetimeAdd;
	return 0.1f * std::cos(t/ p_lifetimeAdd * PI/2) + .1f + 0.01f;
}
