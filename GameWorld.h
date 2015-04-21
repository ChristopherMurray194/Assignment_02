/*
 * GameWorld.h
 *
 *  Created on: 21 Apr 2015
 *      Author: cmurray
 */

#ifndef GAMEWORLD_H_
#define GAMEWORLD_H_

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "GameManager.h"
#include "SphereAsset.h"
#include "Camera.h"

class GameWorld {
public:
	GameWorld();
	virtual ~GameWorld();

	/**
	 * Draw the game world
	 *
	 */
	void Draw();

private:
	boost::shared_ptr<GameManager> game_manager;
};

#endif /* GAMEWORLD_H_ */
