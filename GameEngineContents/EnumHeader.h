#pragma once

enum class RenderOrder
{
	COLLIDEMAP,

	BACKGROUND,
	MIDGROUND,
	PROPS,
	PLAYER,
	BABE,
	FOREGROUND,
	PARTICLE,
	DEBUG, 
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
	bool Act7 = false;
	bool Act8 = false;
	bool Act9 = false;

};