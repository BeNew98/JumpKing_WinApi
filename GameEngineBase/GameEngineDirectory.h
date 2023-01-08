#pragma once
#include <string_view>
#include <vector>
#include "GameEnginePath.h"
// ���� :
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

	//���� ���丮�� ������ �ִ°�
	bool IsFile(const std::string_view& _FileName);

protected:

private:
	GameEnginePath Path;
};

