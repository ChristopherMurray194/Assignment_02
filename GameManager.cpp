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

void GameManager::Draw()
{
	sphere_asset->Draw(getProgramToken());
}

