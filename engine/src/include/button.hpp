#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "scene.hpp"

template<typename Obj>
class OnOffButton : public AnimatedGameObject
{
public:
    typedef void (Obj::*FunctionType)(bool);
    
    ////////////////////////////////////////////////////////////
    /// \brief Construct an on-off button
    /// The button calls a void function with a boolean parameter when pressed
    /// \param pos position
    /// \param passive_textures textures when the button is not pressed down
    /// \param on_mousebutton_pressed_textures textures when the button is about to be pressed
    /// \param active_textures textures when the button is pressed down
    /// \param animation_tick_interval \see AnimatedGameObject
    /// \param method the member function to be called when the button is pressed
    /// \param object_of_function the object of the template type where the method is called
    /// \param scene Scene, this is used to get the mouse position
    /// \param rotation_angle_degrees \see AnimatedGameObject
    /// \param centerize_origin \see AnimatedGameObject
    ////////////////////////////////////////////////////////////
    OnOffButton(sf::Vector2f pos 
               ,const TextureList* passive_textures
               ,const TextureList* on_mousebutton_pressed_textures
               ,const TextureList* active_textures
//                       ,const sf::SoundBuffer& activation_sound
               ,short unsigned animation_tick_interval
               ,FunctionType method
               ,Obj* object_of_function
               ,Scene* scene
               ,float rotation_angle_degrees = 0
               ,bool centerize_origin = true)
        :AnimatedGameObject(pos
                           ,passive_textures
                           ,animation_tick_interval
                           ,rotation_angle_degrees
                           ,centerize_origin)
        ,method(method)
        ,objectOfFunction(object_of_function)
        ,scene(scene)
        ,passiveTextures(passive_textures)
        ,onMousebuttonPressedTextures(on_mousebutton_pressed_textures)
        ,activeTextures(active_textures)
{
    (objectOfFunction->*method)(pressed); // Ensure that the member function starts with the initial value 
}
    
protected:
    bool update() override
    {
        if(this->getAnimation() == onMousebuttonPressedTextures &&
           !this->insideBoundingBox(scene->getMouseWorldPos()))
        {
            this->setAnimation(passiveTextures);
        }
        return true;
    }
    
    void onMouseButtonPressedAction() override
    {
        if(this->insideBoundingBox(scene->getMouseWorldPos()))
        {
            this->setAnimation(onMousebuttonPressedTextures);
        }
    }
    
    void onMouseButtonReleasedAction() override
    {
        
        if(this->getAnimation() == onMousebuttonPressedTextures &&
            this->insideBoundingBox(scene->getMouseWorldPos()))
        {
            pressed = !pressed;
            (objectOfFunction->*method)(pressed);
            this->setAnimation(pressed ? activeTextures : passiveTextures);
            // @TODO: play sound
        }
    }
    
private:
    bool                pressed = false;
    FunctionType        method;
    Obj*                objectOfFunction;
    Scene*              scene;
    const TextureList*  passiveTextures;
    const TextureList*  onMousebuttonPressedTextures;
    const TextureList*  activeTextures;
};

#endif /* BUTTON_HPP */

