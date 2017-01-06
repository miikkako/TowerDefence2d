#ifndef SOUNDHANDLER_HPP
#define SOUNDHANDLER_HPP

#include <SFML/Audio.hpp>

class SoundHandler
{
public:
    explicit SoundHandler(unsigned max_sounds_simultaneously):
        maxSoundsPlayingSimultaneously(max_sounds_simultaneously)
    {};
    
    ~SoundHandler() {};
    
    void playSound(sf::SoundBuffer& sb, int volume, bool is_important);
    
    friend class SceneHandler;
    
private:
    void deletePlayedSounds(); // friend method
    
    std::vector<sf::Sound> normalSounds;
    std::vector<sf::Sound> importantSounds;
    unsigned maxSoundsPlayingSimultaneously;
};

#endif /* SOUNDHANDLER_HPP */

