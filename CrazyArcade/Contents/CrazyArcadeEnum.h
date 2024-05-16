#pragma once

enum class ERenderOrder
{
	BackGround,
	Shadow
};

// 0 ~ 999
enum class ECharacterType
{
	Random,
	Dao,
	Dizni,
	Mos,
	Ethi,
	Marid,
	Bazzi,
	Uni,
	Kephi,
	Su,
	HooU,
	Ray
};

// 1000 ~ 1999
enum class EBlockType
{
	Wall = 1000,
	Box,
	MoveBox
};

// 2000 ~ 2999
enum class EPlayerItem
{
	Bubble = 2000,
	Fluid,
	Ultra,
	Roller,
	RedDevil,
	Glove,
	Shoes,
};