/*
 * GameManager.cpp
 *
 *  Created on: 2 Apr 2015
 *      Author: cmurray
 */

#include "GameManager.h"

GameManager::GameManager() {
	// TODO Auto-generated constructor stub

}

GameManager::~GameManager() {
	// TODO Auto-generated destructor stub
}

GLint GameManager::getProgramToken()
{
	GLint program_token = load_shader->getProgram_token();
	return program_token;
}

void GameManager::AddAsset(boost::shared_ptr<GameAsset> asset)
{
	draw_list.push_back(asset);	// Add the asset to the draw list
}

void GameManager::Draw()
{
	for(auto ga : draw_list)
	{
		ga->Draw(getProgramToken());	// Draw all the assets
	}
}
