#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class CCandle : public GameEngineActor
{
public:
	// constrcuter destructer
	CCandle();
	~CCandle();

	// delete Function
	CCandle(const CCandle& _Other) = delete;
	CCandle(CCandle&& _Other) noexcept = delete;
	CCandle& operator=(const CCandle& _Other) = delete;
	CCandle& operator=(CCandle&& _Other) noexcept = delete;

protected:
	virtual void Start() override;

private:

};

