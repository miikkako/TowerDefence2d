#include "towerdefencescene.hpp"
#include "scenehandler.hpp"

int main()
{
    /* @TODO: make this shorter? */
    SceneHandler SH;
    Scene* scene = new TowerDefenceScene(SH);
    SH.setScene(scene);
    SH.run();
    return EXIT_SUCCESS;
}

