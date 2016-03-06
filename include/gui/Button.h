
#ifndef BUTTON_H
#define BUTTON_H

#include "gui/Component.h"
#include "resource/ResourceIdentifiers.h"
#include "resource/ResourceHolder.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>


namespace GUI
{

class Button : public Component
{
    public:
        typedef std::shared_ptr<Button>		Ptr;
        typedef std::function<void()>		Callback;


	public:
								Button(const FontHolder& fonts, const TextureHolder& textures);

        void					setCallback(Callback callback);
        void					setText(const std::string& text);
        void					setToggle(bool flag);

        virtual bool			IsSelectable() const;
        virtual void			select();
        virtual void			deselect();

        virtual void			activate();
        virtual void			deactivate();

        virtual void			HandleEvent(const sf::Event& event);


    private:
        virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        Callback				mCallback;
        const sf::Texture&		mNormalTexture;
        const sf::Texture&		mSelectedTexture;
        const sf::Texture&		mPressedTexture;
        sf::Sprite				m_sprite;
        sf::Text				m_text;
        bool					mIsToggle;
};

}

#endif // BUTTON_H
