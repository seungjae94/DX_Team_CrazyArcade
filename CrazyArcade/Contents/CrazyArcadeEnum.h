#pragma once

enum class ECharacterType
{
	Random,
	Dao,
	Dizni,
	Mos
};

enum class ERenderOrder
{
	None,
	Map,
	Block,
	Shadow,
	Bomb,
	Item,
	Player,
	Debug,
};

enum class EBlockType
{
	Wall,
	Box	,
	MoveBox
};

enum class EPlayerItem
{
	Bubble,
	Fluid,
	Ultra,
	Roller,
	RedDevil,
	Glove,
	Shoes,
};