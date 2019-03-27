/**
 * @file ParticleEmitter.hpp
 * @author Pablo Rodríguez Zurro (przuro@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2019-03-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef BOX2D_ANIMATED_SCENE_PARTICLE_SYSTEM_H_
#define BOX2D_ANIMATED_SCENE_PARTICLE_SYSTEM_H_

#include "internal/declarations/Declarations.hpp"
#include "internal/Utilities.hpp"

#include "Particle.hpp"
#include "FireParticle.hpp"

namespace prz
{
	template<class P>
	class ParticleEmitter
	{
	public:

		ParticleEmitter
		(
			size_t nParticles,
			float particlesLifeTime,
			size_t nResetedParticles,
			float timeToRefresh,
			PBuffer<PString>& texturePaths,
			float segmentPointAX, float segmentPointAY,
			float segmentPointBX, float segmentPointBY
		)
		{
			for (PString & path : texturePaths)
			{
				Texture texture;
				texture.loadFromFile(path);
				textures_[path] = texture;
				texturesByName_[split_file_name(path)] = &textures_[path];
			}

			for (size_t i = 0; i < nParticles; ++i)
			{
				particles_[i].set_id(i);
				inactiveParticles_[i] = &particles_[i];
			}
		}
		

	public:

		void update(float deltaTime)
		{
			// Re-establishing inactive particles 
			if (timer_ >= resetFrequency_)
			{
				size_t i = 0;

				auto iter = inactiveParticles_.begin(), end = inactiveParticles_.end();
				for (size_t i = 0; iter != end && i < nResetedParticles_; ++iter, ++i)
				{
					P* particle = iter->second;
					activeParticles_.push_back(particle);
					inactiveParticles_.erase(inactiveParticles_.find(particle->id()));
					particle_restablished(particle);
				}

				timer_ = 0.f;
			}

			for (auto& pair : activeParticles_)
			{
				P* particle = pair->second;

				if (particle->currentTimeOfLife() < particlesLifeTime_)
				{
					particle->update(deltaTime);
				}
				else
				{
					particle.set_active(false);
					inactiveParticles_[particle->id()] = particle;
					activeParticles_.erase(activeParticles_.find(particle->id()));
				}
			}

			auxiliar_update(deltaTime);
		}
		
	protected:

		virtual void auxiliar_update(float deltaTime) = 0;
		virtual void particle_restablished(P& particle) = 0;

	protected:

		bool exists_texture(const PString& texturePath) const
		{
			if (textures_.find(texturePath) != textures_.end())
				return true;

			return false;
		}

		bool exists_texture_with_name(const PString& textureName) const
		{
			if (texturesByName_.find(textureName) != texturesByName_.end())
				return true;

			return false;
		}

	protected:

		PBuffer< P >				particles_;
		PMap< int, Particle* >		activeParticles_; // 4 bytes + 1 byte, the value does nothing
		PMap< int, Particle* >		inactiveParticles_; // 4 bytes + 1 byte, the value does nothing

		PMap< PString, Texture >     textures_;
		PMap< PString, Texture* >	 texturesByName_;

	protected:

		size_t nParticles_;
		size_t particlesLifeTime_;
		size_t nResetedParticles_;
		float resetFrequency_; // In seconds
		float timer_;

	protected:

		float segmentPointAX;
		float segmentPointAY;

		float segmentPointBX;
		float segmentPointBY;
	};
}
#endif // !BOX2D_ANIMATED_SCENE_PARTICLE_SYSTEM_H_