#pragma once

enum class ERenderOrder
{
	BackGround,
	Shadow
};

// 0 ~ 999 (캐릭터 타입)
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

// 1000 ~ 1999 (맵 블록 타입)
enum class EBlockType
{
	Wall = 1000,
	Box,
	MoveBox
};

// 2000 ~ 2999 (아이템 타입)
enum class EPlayerItem
{
	None = 2000,
	Bubble,
	Devil,
	Fluid,
	Glove,
	RedDevil,
	Roller,
	Shoes,
	Ultra
};