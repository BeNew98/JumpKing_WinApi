#pragma once
#include <list>
#include <string_view>
#include <Windows.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineObject.h"

// 설명 : 스크린에 존재 및 그려질것들의 기본기능 지원클래스.
class GameEngineRender;
class GameEngineLevel;
class GameEngineCollision;

class GameEngineActor : public GameEngineObject
{
	friend GameEngineLevel;
public:
	// constrcuter destructer
	GameEngineActor();
	~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	float4 GetPos()
	{
		return Pos;
	}

	void SetPos(const float4& _MovePos)
	{
		Pos = _MovePos;
	}

	void SetMove(const float4& _MovePos)
	{
		Pos += _MovePos;
	}

	GameEngineLevel* GetLevel();


#pragma	region CreateRenderEnumOverLoadings
	template<typename EnumType>
	GameEngineRender* CreateRender(const std::string_view& _Image, EnumType _Order)
	{
		return CreateRender(_Image, static_cast<int>(_Order));
	}

	template<typename EnumType>
	GameEngineRender* CreateRender(EnumType _Order)
	{
		return CreateRender(static_cast<int>(_Order));
	}
#pragma endregion

	GameEngineRender* CreateRender(const std::string_view& _Image, int _Order = 0);
	GameEngineRender* CreateRender(int _Order = 0);

	template<typename EnumType>
	GameEngineCollision* CreateCollision(EnumType _GroupIndex)
	{
		return CreateCollision(static_cast<int>(_GroupIndex));
	}

	GameEngineCollision* CreateCollision(int _GroupIndex = 0);

protected:
	// 구현을 안할수도 있어야함.

	// 시작하기전에 뭔가 준비해야할것이 있을때
	virtual void Start() {}

	// 키입력을 받거나 인공지능을 점수를 계산하거나 하는 등
	virtual void Update(float _DeltaTime) {}

	//
	virtual void LateUpdate(float _DeltaTime) {}

	// 화면에 그려지는 기능
	virtual void Render(float _DeltaTime) {}

	inline float GetLiveTime()
	{
		return LiveTime;
	}

	virtual void LevelChangeEnd(GameEngineLevel* _PrevLevel);
	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel);

private:
	float TimeScale = 0.0;
	GameEngineLevel* Level = nullptr;
	
	float LiveTime = 0.0;
	float4 Pos = { 0.0f, 0.0f };
	std::list<GameEngineRender*>RenderList;
	std::list<GameEngineCollision*> CollisionList;

	void Release();
};

