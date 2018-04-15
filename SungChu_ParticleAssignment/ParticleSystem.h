#pragma once
#include <SFML/Graphics.hpp>
//#include <string>
class ParticleSystem : public sf::Transformable, public sf::Sprite
{
public:

	enum easingMode
	{
		liner,
		quad,
		sin,
	};

	ParticleSystem(unsigned int count, std::string imageName, int Movementmode , float scaleSizeX, float scaleSizeY, float imageSizeX, float imageSizeY);

	//~ParticleSystem();

	void LoadTexture(std::string imageName);

	void Update(sf::Time deltaTime);

	void SetEmitter(sf::Vector2f position);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int GetParticleCount();

	void SetEmitterAngle(int angleMin, int angleMax);

	void SetInitialSpeed(int BaseinitialSpeed, int AddinitialSpeed);

	void SetPLifeTime(int newLifeTimeBase, int newLifeTimeAdd);

	void setSpeedChange(bool canSpeedUp, float speedValueX, float speedValueY);

	void SetNewCount(int count);

	void scaleChange(bool haveChange, float newScaleX, float newScaleY, float ScaleSpeed);

	void rotateOverTime(bool haveRotate, float rotationValue);

	void SetParticleColor(int r, int b, int g);

	void SetEasingMode(easingMode easingMode);

	//void CanSpeedUp(bool canSpeedup, float speedChangeValue);
private:
	float actTimer = 0;
	easingMode currentEasing = liner;

	struct Particle
	{
		sf::Sprite sprite;
		//sf::Vector2f Currentposition;
		sf::Vector2f velocity;
		sf::Vector2f size;
		sf::Vector2f newSize;
		sf::Time lifetime;
		sf::Time timePassed;
		int colorR = 255;
		int colorB = 255;
		int colorG = 255;
		float StartSpeed;
		float rotation;
		float angle;
		float VelocityAcceleration;
		float rotationAcceleration;
		float addSpeed;
		float sizeIncrease;
	};
	void ResetParticle(std::size_t index);

	std::vector<Particle> m_particles;
	//std::vector<sf::CircleShape> m_shapes;
	sf::Texture m_texture;

	sf::Time m_emiterLifetime;
	sf::Vector2f m_emitter;
	float easingLifeTime = 1000.0f;
	float QuadraticEasingIn(sf::Time timePassed);
	float SinEasingIn(sf::Time timePassed);


	int emitterAngleMax = 300;
	int emitterAngleMin = 240;
	float initialSpeed = 600;
	int m_count = 0;
	int p_lifetimeBase = 2000;
	int p_lifetimeAdd = 1000;
	int m_baseinitialSpeed = 0;
	int m_addinitialSpeed = 0;
	float m_speedValueX = 0.0f;
	float m_speedValueY = 0.0f;
	bool haveSpeedUp = false;
	bool haveScaleChange = false;
	bool canRotate = false;
	float rotateValue = 0;
	float scaleSpeedDuration = 0;
	float m_scaleSizeX = 0;
	float m_scaleSizeY = 0;
	float m_imageSizeX = 0;
	float m_imageSizeY = 0;
	int movementMode = 0;
};