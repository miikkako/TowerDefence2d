#include "include/enemy.hpp"
#include "include/towerdefencescene.hpp"

Enemy::Enemy(TowerDefenceScene* current_scene
            ,sf::Vector2f pos
            ,TextureList* t
            ,short unsigned animation_tick_interval
            ,float rotation_angle_degrees
            ,float health
            ,float speed)
        :AnimatedGameObject(pos, t, animation_tick_interval, rotation_angle_degrees)
        ,currentScene(current_scene)
        ,health(health)
        ,originalHealth(health)
        ,speed(speed)
{
    if(currentScene->drawHealthBars)
        healthbarRectangle = this->createHealthBarAndReturnRef();
}

sf::RectangleShape* Enemy::createHealthBarAndReturnRef()
{
    // First, create the rectangle as a shared_ptr and add it to the drawing list.
    // Then, return the reference pointer so that it can be accessed.
    std::shared_ptr<sf::RectangleShape> rectangle(new sf::RectangleShape(currentScene->healthBarSize));
    rectangle->setFillColor(currentScene->healthBarColor);
    float healthbar_vertical_offset = sprite.getLocalBounds().height * 1.f;
    this->setShapeOriginToCenter(rectangle.get());
    rectangle->setPosition(sprite.getPosition().x, sprite.getPosition().y - healthbar_vertical_offset);
    this->addChildDrawable(rectangle);
    return rectangle.get();
}

void Enemy::updateHealthbar()
{
    if(healthbarRectangle)
        healthbarRectangle->setScale(health / originalHealth, 1.f);
}


MapWaypointEnemy::MapWaypointEnemy(TowerDefenceScene* current_scene
                                  ,TextureList* t
                                  ,short unsigned animation_tick_interval
                                  ,short unsigned map_path_index
                                  ,float health
                                  ,float speed)
        :Enemy(current_scene
              ,current_scene->getMap()->getWaypoint(map_path_index, 0)
              ,t
              ,animation_tick_interval
              ,angleDeg(current_scene->getMap()->getWaypoint(map_path_index, 1)
                        - current_scene->getMap()->getWaypoint(map_path_index, 0))
              ,health
              ,speed)
        ,mapPathIndex(map_path_index)
{ }

bool MapWaypointEnemy::moveWithWaypointsAndCheckIfGoaled()
{
    Map* map = currentScene->getMap();
    if(!map->isWaypointIndexInBound(mapPathIndex, currentWaypointIndex + 1))
        return true;
    sf::Vector2f current_waypoint(map->getWaypoint(mapPathIndex, currentWaypointIndex));
    sf::Vector2f next_waypoint(map->getWaypoint(mapPathIndex, currentWaypointIndex + 1));
    sf::Vector2f vec_from_current_to_next(next_waypoint - current_waypoint);
    sf::Vector2f new_position(sprite.getPosition() + normalize(vec_from_current_to_next) * speed);
    sf::Vector2f vec_from_current_to_new(new_position - current_waypoint);
    /* Check if the new calculated position is out of bounds from the waypoints */
    if(length(vec_from_current_to_new) > length(vec_from_current_to_next))
    {
        if(!map->isWaypointIndexInBound(mapPathIndex, currentWaypointIndex + 2))
        {
            this->move(next_waypoint - sprite.getPosition());
            return true;
        }
        /* Calculate the remaining distance */
        sf::Vector2f nextnext_waypoint(map->getWaypoint(mapPathIndex, currentWaypointIndex + 2));
        sf::Vector2f vec_from_next_to_nextnext(nextnext_waypoint - next_waypoint);
        float new_position_offset_length(length(vec_from_current_to_new) - length(vec_from_current_to_next));
        new_position = sprite.getPosition() + normalize(vec_from_next_to_nextnext) * new_position_offset_length;
        ++currentWaypointIndex;
        this->setRotation(nextnext_waypoint - next_waypoint);
    }
    this->move(new_position - sprite.getPosition());
    return false;
}

/* Derived classes */
bool MapWaypointEnemy::update()
{
    if(this->moveWithWaypointsAndCheckIfGoaled())
    {
        currentScene->enemyThrough(this);
        return false;
    }
    this->updateHealthbar();
    return true;
}

int MapWaypointEnemy::getPointsFromKill()
{
    int ret(originalHealth * speed);
    return ret;
}

