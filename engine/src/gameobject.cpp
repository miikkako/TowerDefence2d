#include "include/gameobject.hpp"
#include "include/scene.hpp"
#include <typeinfo>

AnimatedGameObject::AnimatedGameObject(float x_pos
                                      ,float y_pos
                                      ,const TextureList* t
                                      ,short unsigned animation_tick_interval
                                      ,float rotation_angle_degrees
                                      ,bool centerize_origin)
        :animationTickInterval(animation_tick_interval)
        ,centerizeOrigin(centerize_origin)
        ,textures(t)
{
    sprite.setPosition(x_pos, y_pos);
    this->initializeAnimation();
    sprite.setRotation(rotation_angle_degrees);
}

AnimatedGameObject::AnimatedGameObject(sf::Vector2f pos
                                      ,const TextureList* t
                                      ,short unsigned animation_tick_interval
                                      ,float rotation_angle_degrees
                                      ,bool centerize_origin)
        :animationTickInterval(animation_tick_interval)
        ,centerizeOrigin(centerize_origin)
        ,textures(t)
{
    sprite.setPosition(pos);
    this->initializeAnimation();
    sprite.setRotation(rotation_angle_degrees);
}

void AnimatedGameObject::addChildDrawable(std::shared_ptr<sf::Shape> obj)
{
    childrenShapes.push_back(obj);
}

void AnimatedGameObject::removeChildDrawable(sf::Shape* obj_ptr)
{
    for(auto iter = childrenShapes.begin(); iter != childrenShapes.end(); ++iter)
    {
        if(iter->get() == obj_ptr)
        {
            iter = childrenShapes.erase(iter);
            --iter;
        }
    }
}

bool AnimatedGameObject::insideBoundingBox(const sf::Vector2f& coord) const
{
    return sprite.getGlobalBounds().contains(coord);
}

void AnimatedGameObject::move(sf::Vector2f&& movement)
{
    sprite.move(movement);
    for(auto iter = childrenShapes.begin(); iter != childrenShapes.end(); ++iter)
        (*iter)->move(movement);
}

void AnimatedGameObject::setRotation(const sf::Vector2f& direction)
{
    sprite.setRotation(angleDeg(direction)); // angle in degrees inside setRotation
    //@TODO: rotate the bounding box
}

bool AnimatedGameObject::draw(sf::RenderWindow& w)
{
    updateAnimation();
    onDraw(w);
    return true;
}

void AnimatedGameObject::onDraw(sf::RenderWindow& w)
{
    w.draw(sprite);
    for(auto iter = childrenShapes.begin(); iter != childrenShapes.end(); ++iter)
        w.draw(**iter);
}

void AnimatedGameObject::drawDebugThings(sf::RenderWindow& w) const
{
    drawBoundingBox(w);
    drawOrigin(w);
}

void AnimatedGameObject::drawBoundingBox(sf::RenderWindow& w) const
{
    sf::RectangleShape bbox(sf::Vector2f(sprite.getLocalBounds().width,
                                         sprite.getLocalBounds().height));
    bbox.setFillColor(sf::Color::Transparent);
    bbox.setOutlineThickness(2);
    bbox.setOutlineColor(sf::Color::Red);
    bbox.setPosition(sprite.getGlobalBounds().left, sprite.getGlobalBounds().top);
    w.draw(bbox);
}

void AnimatedGameObject::drawOrigin(sf::RenderWindow& w) const
{
    sf::CircleShape circle = sf::CircleShape(3);
    circle.setFillColor(sf::Color::Cyan);
    setShapeOriginToCenter(&circle);
    circle.setPosition(sprite.getPosition());
    w.draw(circle);
}

void AnimatedGameObject::onMouseOverDebugDraw(sf::RenderWindow& w ,const sf::Font& f)
{
    drawDebugTooltip(w, f);
    this->drawDebugTooltip(w, f);
}

void AnimatedGameObject::drawDebugTooltip(sf::RenderWindow& w, const sf::Font& f) const
{
    // First create the tooltip box and draw it
    float tooltip_height(100), tooltip_width(150);
    short unsigned font_size(12), line_spacing(font_size + 2);
    sf::RectangleShape tooltip_box(sf::Vector2f(tooltip_width, tooltip_height));
    tooltip_box.setFillColor(sf::Color(180,180,180));
    tooltip_box.setOutlineThickness(2);
    tooltip_box.setOutlineColor(sf::Color::Black);
    setShapeOriginToCenter(&tooltip_box);
    tooltip_box.setPosition(sprite.getPosition().x, sprite.getPosition().y - tooltip_height);
    w.draw(tooltip_box);
    // Then create the tooltip text
    sf::Text text;
    text.setFont(f);
    text.setCharacterSize(font_size);
    text.setColor(sf::Color::Black);
    text.setStyle(sf::Text::Regular);
    // Finally draw different texts
    text.setString(typeid(*this).name());
    text.setPosition(tooltip_box.getGlobalBounds().left + 0.02f * tooltip_height,
                     tooltip_box.getGlobalBounds().top + 0.02f * tooltip_height);
    w.draw(text);
    text.setString("Position: " + std::to_string((int)sprite.getPosition().x) + ", "
                   + std::to_string((int)sprite.getPosition().y));
    text.setPosition(tooltip_box.getGlobalBounds().left + 0.02f * tooltip_height,
                     tooltip_box.getGlobalBounds().top + line_spacing);
    w.draw(text);
    text.setString("Rotation: " + std::to_string((int)sprite.getRotation()));
    text.setPosition(tooltip_box.getGlobalBounds().left + 0.02f * tooltip_height,
                     tooltip_box.getGlobalBounds().top + 2 * line_spacing);
    w.draw(text);
    text.setString("Children shapes: " + std::to_string(childrenShapes.size()));
    text.setPosition(tooltip_box.getGlobalBounds().left + 0.02f * tooltip_height,
                     tooltip_box.getGlobalBounds().top + 3 * line_spacing);
    w.draw(text);
    text.setString("Textures: " + std::to_string(textures->size()));
    text.setPosition(tooltip_box.getGlobalBounds().left + 0.02f * tooltip_height,
                     tooltip_box.getGlobalBounds().top + 4 * line_spacing);
    w.draw(text);
    text.setString("Anim interval: " + std::to_string(animationTickInterval));
    text.setPosition(tooltip_box.getGlobalBounds().left + 0.02f * tooltip_height,
                     tooltip_box.getGlobalBounds().top + 5 * line_spacing);
    w.draw(text);
    // @TODO: Get additional texts from derived classes?
}

void AnimatedGameObject::updateAnimation()
{
//    if(!textures) // Think we don't need to check the validity here
//        throw std::runtime_error(std::string("Object ") + typeid(*this).name() + "'s 'textures'-member points to null");
    if(animationTickInterval > 0 && ++ticksFromLastFrameUpdate >= animationTickInterval)
    {
        sprite.setTexture(getNextTexture(), true);
        this->setOriginToCenter();
        ticksFromLastFrameUpdate = 0;
    }
}

const sf::Texture& AnimatedGameObject::getNextTexture()
{
    if(currentFrameIndex >= textures->size() - 1)
        currentFrameIndex = 0;
    else
        ++currentFrameIndex;
    return textures->at(currentFrameIndex);
}

void AnimatedGameObject::initializeAnimation()
{
    if(!textures)
        throw std::runtime_error(std::string("Tried to set object ")
                + typeid(*this).name() + "'s 'textures'-member to nullptr");
    sprite.setTexture(textures->at(0), true); // start with the first texture in the list
    if(centerizeOrigin)
    {
        this->setOriginToCenter();
    }
}

void AnimatedGameObject::setOriginToCenter()
{
    sf::FloatRect rect = sprite.getLocalBounds();
    sprite.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
}

void AnimatedGameObject::setAnimation(const TextureList* t)
{
    textures = t;
    initializeAnimation();
}

void AnimatedGameObject::setShapeOriginToCenter(sf::Shape* s)
{
    sf::FloatRect rect(s->getLocalBounds());
    s->setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
}

void AnimatedGameObject::setTextOriginToCenter(sf::Text& s)
{
    sf::FloatRect rect(s.getLocalBounds());
    s.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
}


/* Explosions, etc. */
StaticAnimation::StaticAnimation(float x_pos
                                ,float y_pos
                                ,const TextureList* t
                                ,short unsigned animation_loops_lifetime
                                ,short unsigned animation_tick_interval
                                ,float rotation_angle_degrees
                                ,bool centerize_origin)
        :AnimatedGameObject(x_pos
                           ,y_pos
                           ,t
                           ,animation_tick_interval
                           ,rotation_angle_degrees
                           ,centerize_origin)
        ,animationLoopsLifetime(animation_loops_lifetime)
{ }

StaticAnimation::StaticAnimation(const sf::Vector2f pos
                                ,const TextureList* t
                                ,short unsigned animation_loops_lifetime
                                ,short unsigned animation_tick_interval
                                ,float rotation_angle_degrees
                                ,bool centerize_origin)
        :AnimatedGameObject(pos
                           ,t
                           ,animation_tick_interval
                           ,rotation_angle_degrees
                           ,centerize_origin)
        ,animationLoopsLifetime(animation_loops_lifetime)
{ }

bool StaticAnimation::draw(sf::RenderWindow& w)
{
    /* First, check if the animation has lived enough */
    if(animationLoopsLifetime > 0 && currentLoop++ > animationLoopsLifetime)
        return false;
    updateAnimation();
    onDraw(w);
    return true;
}


std::ostream& operator<<(std::ostream& os, const AnimatedGameObject& obj)
{
    os << "AnimatedGameObject " << typeid(obj).name() << ": "
       << "Position = " << obj.sprite.getPosition() << ". "
       << "Rotation = " << obj.sprite.getRotation() << ". "
       << "Origin = " << obj.sprite.getOrigin() << ". "
       ;
    obj.print(os);
    return os;
}
