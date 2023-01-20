#pragma once
#include <list>
#include <map>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineObject.h>

// 설명 :
class GameEngineCore;
class GameEngineActor;
class GameEngineRender;

class GameEngineLevel : public GameEngineObject
{
	friend GameEngineCore;
	friend GameEngineRender;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	/// <summary>
	/// Actor 생성 함수
	/// </summary>
	/// <typeparam name="ActorType">
	/// GameEngineActor 상속받은 클래스 타입</typeparam>
	/// <param name="_Order">
	/// Order가 작을수록 먼저 업데이트</param>
	template<typename ActorType>
	ActorType* CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType();

		ActorStart(Actor, _Order);

		Actors[_Order].push_back(Actor);

		return dynamic_cast<ActorType*>(Actor);
	}

	void SetCameraMove(const float4& _MoveValue)
	{
		CameraPos += _MoveValue;
	}

	void SetCameraPos(const float4& _CameraPos)
	{
		CameraPos = _CameraPos;
	}

	float4 GetCameraPos()
	{
		return CameraPos;
	}

protected:
	virtual void Loading() = 0;
	virtual void Update(float _DeltaTime) = 0;

	virtual void LevelChangeStart(GameEngineLevel* _PrevLevel) = 0;
	virtual void LevelChangeEnd(GameEngineLevel* _NextLevel) = 0;


 private:
	float4 CameraPos = float4::Zero;

	std::map<int,std::list<GameEngineActor*>> Actors;

	void ActorsUpdate(float _DeltaTime);
	void ActorsRender(float _DeltaTime);

	void ActorStart(GameEngineActor* _Actor,int _Order);

	std::map<int, std::list<GameEngineRender*>> Renders;

	void PushRender(GameEngineRender* _Render);
	

};

