/*
 * GameWorld.cpp
 *
 *  Created on: 21 Apr 2015
 *      Author: cmurray
 */

#include "GameWorld.h"

GameWorld::GameWorld() {
	game_manager = boost::make_shared<GameManager>();

	std::string earth_texture = "textures/earth_texture.png";
	std::string moon_texture = "textures/moon_texture.jpg";
	game_manager->AddAsset(boost::make_shared<Light>());
	game_manager->AddAsset(boost::make_shared<SphereAsset>(earth_texture.c_str(), 3.0, 30, 60));	// Earth
	game_manager->AddAsset(boost::make_shared<SphereAsset>(earth_texture.c_str(), 0.5, 30, 60, 5.0));	// Moon
	game_manager->AddAsset(boost::make_shared<Camera>());
}

GameWorld::~GameWorld() {
	// TODO Auto-generated destructor stub
}

void GameWorld::Draw()
{
	game_manager->Draw();
}


