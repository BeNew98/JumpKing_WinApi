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
	ENDING
};