#include "include/gameobject.hpp"

AnimatedGameObject::AnimatedGameObject(float x_pos, float y_pos,
    TextureList* t, short unsigned animation_tick_interval, bool centerize_origin)
        :textures(t)
        ,animationTickInterval(animation_tick_interval)
        ,centerizeOrigin(centerize_origin)
{
    sprite.setPosition(x_pos, y_pos);
    this->initializeAnimation();
}

AnimatedGameObject::AnimatedGameObject(float x_pos, float y_pos, float rotation_angle_degrees,
    TextureList* t, short unsigned animation_tick_interval, bool centerize_origin)
        :textures(t)
        ,animationTickInterval(animation_tick_interval)
        ,centerizeOrigin(centerize_origin)
{
    sprite.setPosition(x_pos, y_pos);
    this->initializeAnimation();
    sprite.setRotation(rotation_angle_degrees);
}

bool AnimatedGameObject::draw(sf::RenderWindow& w)
{
    this->updateAnimation();
    w.draw(sprite);
    return true;
}

void AnimatedGameObject::updateAnimation()
{
    if(animationTickInterval > 0 && ++ticksFromLastFrameUpdate >= animationTickInterval)
    {
        sprite.setTexture(this->getNextTexture(), true);
        ticksFromLastFrameUpdate = 0;
    }
}

sf::Texture& AnimatedGameObject::getNextTexture()
{
    if(currentFrameIndex >= textures->size() - 1)
        currentFrameIndex = 0;
    else
        ++currentFrameIndex;
    return (*textures)[currentFrameIndex];
}

void AnimatedGameObject::initializeAnimation()
{
    sprite.setTexture((*textures)[0], true); // start with the first texture in the list
    if(centerizeOrigin)
    {
        sf::FloatRect textRect = sprite.getLocalBounds();
        sprite.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    } 
}

//void AnimatedGameObject::setAnimation(TextureList& t)
//{
//    sprite.setTexture(t[0]);
//}


/* Explosions, etc. */
StaticAnimation::StaticAnimation(float x_pos, float y_pos, float rotation_angle_degrees,
    short unsigned animation_loops_lifetime, TextureList* t,
    short unsigned animation_tick_interval, bool centerize_origin)
        :AnimatedGameObject(x_pos, y_pos, rotation_angle_degrees, t,
            animation_tick_interval, centerize_origin)
        ,animationLoopsLifetime(animation_loops_lifetime)
{ }

bool StaticAnimation::draw(sf::RenderWindow& w)
{
    /* First, check if the animation has lived enough */
    if(animationLoopsLifetime > 0 && currentLoop++ > animationLoopsLifetime)
        return false;
    this->updateAnimation();
    w.draw(sprite);
    return true;
}
