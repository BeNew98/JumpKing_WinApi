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

	bool MoveParent();

	void MoveParentToDirectory(const std::string_view& _String);

	bool Move(const std::string_view& _String);

	GameEnginePath GetPlusFileName(const std::string_view& _String);

protected:

private:
	GameEnginePath Path;
};
