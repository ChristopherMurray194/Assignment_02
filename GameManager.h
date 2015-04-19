/*
 * GameManager.h
 *
 *  Created on: 2 Apr 2015
 *      Author: cmurray
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "SphereAsset.h"
#include "LoadShader.h"
#include "Camera.h"

class GameManager {
public:
	GameManager();
	virtual ~GameManager();

	void Draw();

private:
	boost::shared_ptr<SphereAsset> sphere_asset = boost::make_shared<SphereAsset>();
	boost::shared_ptr<LoadShader> load_shader   = boost::make_shared<LoadShader>();
	boost::shared_ptr<Camera> camera_ptr        = boost::make_shared<Camera>();

	/**
	 * Get the program token from load shader
	 */
	GLint getProgramToken();
};

#endif /* GAMEMANAGER_H_ */
