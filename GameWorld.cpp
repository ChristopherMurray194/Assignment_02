/*
 * GameWorld.cpp
 *
 *  Created on: 21 Apr 2015
 *      Author: cmurray
 */

#include "GameWorld.h"

GameWorld::GameWorld() {
	game_manager = boost::make_shared<GameManager>();
	game_manager->AddAsset(boost::make_shared<SphereAsset>(3.0, 30, 60));
	game_manager->AddAsset(boost::make_shared<Camera>());
}

GameWorld::~GameWorld() {
	// TODO Auto-generated destructor stub
}

void GameWorld::Draw()
{
	game_manager->Draw();
}


