#pragma once

enum class RenderOrder
{
	COLLIDEMAP,// ��������

	BACKGROUND,
	MIDGROUND,
	PROPS,
	DEBUG, // ��������
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