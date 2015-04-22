/*
 * GameManager.h
 *
 *  Created on: 2 Apr 2015
 *      Author: cmurray
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <iostream>
#include <vector>
#include <memory>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "GameAsset.h"
#include "LoadShader.h"

class GameManager {
public:
	GameManager();
	virtual ~GameManager();

	/**
	 * Add an asset to the game
	 *
	 * @param asset to be added so it can be drawn
	 */
	void AddAsset(boost::shared_ptr<GameAsset>);

	/**
	 * Draw the assets
	 */
	void Draw();

private:
	boost::shared_ptr<LoadShader> load_shader   = boost::make_shared<LoadShader>();

	std::vector<boost::shared_ptr<GameAsset> > draw_list;	// List of assets to be drawn

	/**
	 * Get the program token from load shader
	 */
	GLint getProgramToken();
};

#endif /* GAMEMANAGER_H_ */
