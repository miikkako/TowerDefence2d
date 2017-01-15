#ifndef TOWER_HPP
#define TOWER_HPP

#include "enemy.hpp"

class Projectile;

class Tower : public AnimatedGameObject
{
public:
    Tower(TowerDefenceScene* current_scene
         ,sf::Vector2f pos
         ,TextureList* t
         ,short unsigned animation_tick_interval
         ,const StaticAnimation* firing_animation
         ,const sf::SoundBuffer& firing_sound
         ,const Projectile* fired_projectile
         ,float speed);
    
protected:
    TowerDefenceScene*          currentScene;
    const Projectile*           firedProjectile;
    const StaticAnimation*      firingAnimation;
    const sf::SoundBuffer&      firingSound;
};

#endif /* TOWER_HPP */

