/**
 * @file Particle.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-03-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef BOX2D_ANIMATED_SCENE_PARTICLE_H_
#define BOX2D_ANIMATED_SCENE_PARTICLE_H_

#include "internal/declarations/Declarations.hpp"
#include "Entity.hpp"

#include <SFML/Graphics.hpp>

using namespace sf;

constexpr float MIN_SPEED			= 0.5f;
constexpr float MAX_SPEED			= 5.0f;
constexpr float MIN_AMPLITUDE		= 0.5f;
constexpr float MAX_AMPLITUDE		= 5.0f;
constexpr float MIN_FREQUENCY		= 0.5f;
constexpr float MAX_FREQUENCY		= 5.0f;
constexpr float MIN_PHASE			= 0.5f;
constexpr float MAX_PHASE			= 5.0f;

namespace prz
{
	class Particle
	{
	public:

		Particle(const Texture & texture, float posX, float posY)
			:
			curTimeOfLife_(.0f),
			sprite_(new Sprite(texture))
		{}
		
	public:

		void update(float deltaTime)
		{
			if (isActive_)
			{
				curTimeOfLife_ += deltaTime;
				
				auxiliar_update(deltaTime);
			}
		}

		virtual void auxiliar_update(float deltaTime) = 0;

	public:

		void set_sprite_texture(const Texture & texture)
		{
			sprite_->setTexture(texture);
		}

		void set_sprite(Sprite * sprite)
		{
			sprite_.reset(sprite);
		}

	public:

		inline bool isActive()
		{
			return isActive_;
		}

		inline float positionX()
		{
			return positionX_;
		}

		inline float positionY()
		{
			return positionY_;
		}

	protected:

		PShared_ptr<Sprite> sprite_;

		float curTimeOfLife_;
		bool isActive_;

	protected:

		float positionX_;
		float positionY_;
	};
}

#endif // !BOX2D_ANIMATED_SCENE_PARTICLE_H_
