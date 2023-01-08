#include "GameEnginePath.h"

GameEnginePath::GameEnginePath() 
{
	Path = std::filesystem::current_path();
}

GameEnginePath::~GameEnginePath() 
{
}

