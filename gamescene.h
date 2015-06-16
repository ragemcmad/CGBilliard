#ifndef GAMESCENE_H
#define GAMESCENE_H

#include<vector>
#include "cam.h"
#include "kugel.h"
#include "tisch.h"
#include "koe.h"
#include "gui.h"
#include "lightsources.h"

class GameScene
{
public:
    GameScene();
    ~GameScene();

    Tisch *tischBoden;
    std::vector<GameObject*>* primaryObjects;
    std::vector<Kugel*>* secondaryObjects;
	
	std::vector<Kugel*>* halbeKugeln;
	std::vector<Kugel*>* eingelochteHalbe;
	std::vector<Kugel*>* ganzeKugeln;
    std::vector<Kugel*>* eingelochteGanze;

    std::vector<QVector3D*>* kugelPositions;

    GUI *gui;
    void initScene();
    void renderScene(myCam* cam);
    bool hasMovingBalls();
    LightSources* lights;

};

#endif // GAMESCENE_H
