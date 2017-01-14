#include "towerdefencescene.hpp"

int main()
{
    /* @TODO: make this shorter? */
//    std::ostream os(nullptr);
//    SceneHandler SH(true, os);
    SceneHandler SH(true, std::cout);
    Scene* scene = new TowerDefenceScene(SH, "FirstMap");
    SH.setScene(scene);
    SH.run();
    return EXIT_SUCCESS;
}

