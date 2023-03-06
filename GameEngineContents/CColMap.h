#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class GameEngineRender;
class CColMap : public GameEngineActor
{
public:
	// constrcuter destructer
	CColMap();
	~CColMap();

	static float4 m_MapSize;

	// delete Function
	CColMap(const CColMap& _Other) = delete;
	CColMap(CColMap&& _Other) noexcept = delete;
	CColMap& operator=(const CColMap& _Other) = delete;
	CColMap& operator=(CColMap&& _Other) noexcept = delete;

protected:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

private:
	GameEngineRender* m_pColMap = nullptr;

};

