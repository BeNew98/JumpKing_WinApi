#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CAngel
{
public:
	// constrcuter destructer
	CAngel();
	~CAngel();

	// delete Function
	CAngel(const CAngel& _Other) = delete;
	CAngel(CAngel&& _Other) noexcept = delete;
	CAngel& operator=(const CAngel& _Other) = delete;
	CAngel& operator=(CAngel&& _Other) noexcept = delete;

protected:

private:

};

