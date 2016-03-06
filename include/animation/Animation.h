#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>


class Animation : public sf::Drawable, public sf::Transformable
{
	public:
								Animation();

		explicit 				Animation(const sf::Texture& texture);

        void 					SetTexture(const sf::Texture& texture);
        const sf::Texture* 		GetTexture() const;

        void 					SetFrameSize(sf::Vector2i m_frameSize);
        sf::Vector2i		 	GetFrameSize() const;

        void 					SetNumFrames(std::size_t numFrames);
        std::size_t 			GetNumFrames() const;

        void 					SetDuration(sf::Time duration);
        sf::Time 				GetDuration() const;

        void 					SetRepeating(bool flag);
		bool 					isRepeating() const;

        void 					Restart();
        bool 					IsFinished() const;

		sf::FloatRect 			GetLocalBounds() const;
		sf::FloatRect 			GetGlobalBounds() const;

		void 					Update(sf::Time dt);


	private:
        virtual void 			draw(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
        sf::Sprite 				m_sprite;
        sf::Vector2i 			m_frameSize;
        std::size_t 			m_numFrames;
        std::size_t 			m_currentFrame;
        sf::Time 				m_duration;
        sf::Time 				m_elapsedTime;
        bool 					m_repeat;
};

#endif // ANIMATION_H
