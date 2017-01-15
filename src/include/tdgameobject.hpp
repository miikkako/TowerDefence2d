#ifndef TDGAMEOBJECT_HPP
#define TDGAMEOBJECT_HPP

#include "towerdefencescene.hpp"

class TdGameObject
{
public:
    TdGameObject(TowerDefenceScene* current_scene
                ,StaticAnimation* action_animation
                ,sf::SoundBuffer* action_sound)
            :currentScene(current_scene)
            ,actionAnimation(action_animation)
            ,actionSound(action_sound)
    { };
    
    StaticAnimation* getActionAnimation() { return actionAnimation; };
    sf::SoundBuffer* getActionSound()     { return actionSound; };
    
protected:
    TowerDefenceScene*   currentScene;
    StaticAnimation*     actionAnimation;
    sf::SoundBuffer*     actionSound;
};


#endif /* TDGAMEOBJECT_HPP */

