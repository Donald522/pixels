#ifndef SOUND_NODE_H
#define SOUND_NODE_H

#include "nodes/SceneNode.h"
#include "resource/ResourceIdentifiers.h"


class SoundPlayer;

class SoundNode : public SceneNode {
public:

    explicit                    SoundNode();
    void                        PlaySound(SoundEffect::ID sound, sf::Vector2f pos);

    virtual Category::Type_t    GetCategory() const;

private:

    SoundPlayer& m_sounds;
};

#endif //SOUND_NODE_H
