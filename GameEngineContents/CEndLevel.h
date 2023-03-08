#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class CEndLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CEndLevel();
	~CEndLevel();

	// delete Function
	CEndLevel(const CEndLevel& _Other) = delete;
	CEndLevel(CEndLevel&& _Other) noexcept = delete;
	CEndLevel& operator=(const CEndLevel& _Other) = delete;
	CEndLevel& operator=(CEndLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:

};

