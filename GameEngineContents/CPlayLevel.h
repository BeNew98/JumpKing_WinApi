#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� :
class CPlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CPlayLevel();
	~CPlayLevel();

	// delete Function
	CPlayLevel(const CPlayLevel& _Other) = delete;
	CPlayLevel(CPlayLevel&& _Other) noexcept = delete;
	CPlayLevel& operator=(const CPlayLevel& _Other) = delete;
	CPlayLevel& operator=(CPlayLevel&& _Other) noexcept = delete;

protected:

private:

};

