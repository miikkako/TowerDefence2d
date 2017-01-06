#include "include/soundhandler.hpp"

void SoundHandler::playSound(sf::SoundBuffer& sb, int volume, bool is_important)
{
    /* This method is a little bit faster if we don't initialize the sound before the if-else */
    if(!is_important && importantSounds.size() + normalSounds.size() < maxSoundsPlayingSimultaneously)
    {
        sf::Sound sound;
        sound.setBuffer(sb);
        sound.play();
        sound.setVolume(volume);
        normalSounds.push_back(sound);
    }
    else if(is_important)
    {
        sf::Sound sound;
        sound.setBuffer(sb);
        sound.play();
        sound.setVolume(volume);
        importantSounds.push_back(sound);
    }
}

void SoundHandler::deletePlayedSounds()
{ 
    for(auto it = normalSounds.begin(); it != normalSounds.end(); ++it)
    {
        if(it->getStatus() == sf::Sound::Stopped)
        {
            it = normalSounds.erase(it);
            --it;
        } 
    }
    for(auto it = importantSounds.begin(); it != importantSounds.end(); ++it)
    {
        if(it->getStatus() == sf::Sound::Stopped)
        {
            it = importantSounds.erase(it);
            --it;
        } 
    }
}
