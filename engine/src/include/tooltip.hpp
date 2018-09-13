#ifndef TOOLTIP_HPP
#define TOOLTIP_HPP

#include "animated.hpp"

// @TODO: differently shaped tooltips?
class Tooltip : public Animated
{
public:
    /// Note: the tooltip does not support automatic scaling yet
    Tooltip(sf::Vector2f size
           ,short unsigned font_size
           ,short unsigned line_spacing
           ,float outline_thickness
           ,sf::Color outline_color
           ,sf::Color fill_color
           ,float text_outline_thickness
           ,sf::Color text_outline_color
           ,sf::Color text_color
           ,const sf::Font& text_font
           ,sf::Uint32 text_style
           ,sf::String str
           ,const Animated::TextureList* t
           ,bool centerize_origin);
    
    const sf::String& getString() { return textPtr->getString(); };
    void setString(sf::String new_str) { textPtr->setString(new_str); };
    void appendString(sf::String appended_str);
    
    /// \brief 
    void setPositionWRTobject(sf::RenderWindow& w, const sf::FloatRect& object_bounds);
    
private:
    sf::RectangleShape   box;
    short unsigned       fontSize;
    short unsigned       lineSpacing;
    sf::Text*            textPtr;
    
};

#endif /* TOOLTIP_HPP */

