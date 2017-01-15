#include "towerdefencescene.hpp"

int main()
{
    /* @TODO: make this shorter? */
    SceneHandler SH(true);
    Scene* scene = new TowerDefenceScene(SH, "FirstMap");
    SH.setScene(scene);
    SH.run();
    return EXIT_SUCCESS;
}

