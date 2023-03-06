#pragma once

enum class RenderOrder
{
	COLLIDEMAP,// 삭제예정

	BACKGROUND,
	MIDGROUND,
	PROPS,
	DEBUG, // 삭제예정
	PLAYER,
	BABE,
	FOREGROUND,
	PARTICLE,
};

enum class CollisionOrder
{
	PLAYER,
	BABE,
	ANGEL,
	ENDING
};

struct EndingAct
{
	bool Act0 = false;
	bool Act1 = false;
	bool Act2 = false;
	bool Act3 = false;
	bool Act4 = false;
	bool Act5 = false;
	bool Act6 = false;

};