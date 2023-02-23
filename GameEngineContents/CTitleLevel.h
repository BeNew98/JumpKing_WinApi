#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

// Ό³Έν :
class CTitleLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	CTitleLevel();
	~CTitleLevel();

	// delete Function
	CTitleLevel(const CTitleLevel& _Other) = delete;
	CTitleLevel(CTitleLevel&& _Other) noexcept = delete;
	CTitleLevel& operator=(const CTitleLevel& _Other) = delete;
	CTitleLevel& operator=(CTitleLevel&& _Other) noexcept = delete;

protected:
	void Loading()override;
	void Update(float _DeltaTime) override;

	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel);
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel);


	GameEngineSoundPlayer BGMPlayer;

private:
	GameEngineSound* Intro = nullptr;
};

