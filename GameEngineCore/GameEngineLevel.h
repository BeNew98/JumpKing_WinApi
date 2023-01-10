#pragma once
#include <list>
#include <map>

// Ό³Έν :
class GameEngineCore;
class GameEngineActor;

class GameEngineLevel
{
	friend GameEngineCore;

public:
	// constrcuter destructer
	GameEngineLevel();
	virtual ~GameEngineLevel() = 0;

	// delete Function
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	template<typename ActorType>
	void CreateActor(int _Order = 0)
	{
		GameEngineActor* Actor = new ActorType();

		ActorStart(Actor, _Order);

		Actors[_Order].push_back(Actor);
	}
protected:
	virtual void Loading() = 0;
	virtual void Update() = 0;

private:
	std::map<int,std::list<GameEngineActor*>> Actors;

	void ActorsUpdate();
	void ActorsRender();

	void ActorStart(GameEngineActor* _Actor,int _Order);

};

