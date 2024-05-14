#pragma once

enum class ERenderOrder
{
	None,
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