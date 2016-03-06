#ifndef POST_EFFECT_H
#define POST_EFFECT_H
#include <SFML/System/NonCopyable.hpp>


namespace sf
{
	class RenderTarget;
	class RenderTexture;
	class Shader;
}

class PostEffect : private sf::NonCopyable {
public:

	virtual			~PostEffect();

	virtual void	Apply( const sf::RenderTexture& input, sf::RenderTarget& output ) = 0;

protected:

	static void		ApplyShader( const sf::Shader& shader, sf::RenderTarget& output );

};

#endif // POST_EFFECT_H
