#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// Ό³Έν :
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
	void Loading() override;
	void Update(float _DeltaTime) override;

	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) override {}
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) override {}

private:
	int m_iMapNumber = 0;

	void SetCandle(float _X, float _Y);
	void SetCandleMiddle(float _X, float _Y);
	void SetCandleLarge(float _X, float _Y);

	void SoundLoad();
	void ImageLoad();
	void KeyLoad();
};

