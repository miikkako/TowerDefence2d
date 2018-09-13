#include "include/tooltip.hpp"

Tooltip::Tooltip(sf::Vector2f size
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
                ,const sf::Texture* optional_texture
                ,bool centerize_origin)
        :box(sf::RectangleShape(size))
{
    if(centerize_origin)
        AnimatedGameObject::setShapeOriginToCenter(&box);
    box.setOutlineThickness(outline_thickness);
    box.setOutlineColor(outline_color);
    box.setFillColor(fill_color);
    if(optional_texture)
        box.setTexture(optional_texture, true);
    std::shared_ptr<sf::Text> child_text(new sf::Text());
    child_text->setFont(text_font);
    child_text->setStyle(text_style);
    child_text->setOutlineThickness(text_outline_thickness);
    child_text->setOutlineColor(text_outline_color);
    child_text->setCharacterSize(font_size);
    child_text->setFillColor(text_color);
    child_text->setString(str);
    this->addChildText(child_text);
    textPtr = child_text.get();
}

Tooltip::appendString(sf::String appended_str)
{
    textPtr->setString(getString() + appended_str);
}

Tooltip::setPositionWRTobject(sf::RenderWindow& w, const sf::FloatRect& object_bounds)
{
    sf::Vector2f new_pos;
    float tooltip_width(box.getLocalBounds().width), tooltip_height(box.getLocalBounds().height);
    if(object_center_position.x - (2 * tooltip_width) < 0)
        new_pos.x = object_center_position.x + tooltip_width;
    else if(object_center_position.x + (2 * tooltip_width) > w.getSize().x)
        new_pos.x = object_center_position.x - tooltip_width;
    if(object_center_position.y - (2 * tooltip_height) < 0)
        new_pos.y = object_center_position.y + tooltip_height;
    else if(object_center_position.y + (2 * tooltip_height) > w.getSize().y)
        new_pos.y = object_center_position.y - tooltip_height;
    this->move(box.getPosition() - new_pos);
}