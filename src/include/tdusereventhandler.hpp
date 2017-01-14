#ifndef TDUSEREVENTHANDLER_HPP
#define TDUSEREVENTHANDLER_HPP

#include "usereventhandler.hpp"
#include "towerdefencescene.hpp"

class TdUserEventHandler : public UserEventHandler
{
public:
    TdUserEventHandler(SceneHandler& sh
                      ,TowerDefenceScene* current_scene
                      ,bool use_virtual_debug_methods);
    
    void handleKeyPressedDebug() override;
    
private:
    TowerDefenceScene* currentScene;
};

#endif /* TDUSEREVENTHANDLER_HPP */

