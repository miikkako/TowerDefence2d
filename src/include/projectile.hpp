#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "tower.hpp"

class Projectile : public AnimatedGameObject
{
public:
    Projectile(TowerDefenceScene* current_scene
              ,sf::Vector2f pos
              ,TextureList* t
              ,short unsigned animation_tick_interval
              ,const StaticAnimation* hit_animation
              ,const sf::SoundBuffer& hit_sound
              ,float speed
              ,float damage);
    
protected:
    TowerDefenceScene*          currentScene;
    const StaticAnimation*      hitAnimation;
    const sf::SoundBuffer&      hitSound;
};

#endif /* PROJECTILE_HPP */

