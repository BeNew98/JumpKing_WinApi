#pragma once
#include <string_view>
#include <vector>
#include "GameEnginePath.h"
// 설명 :
class GameEngineDirectory
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	~GameEngineDirectory();

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	//현재 디렉토리에 파일이 있는가
	bool IsFile(const std::string_view& _FileName);

protected:

private:
	GameEnginePath Path;
};

