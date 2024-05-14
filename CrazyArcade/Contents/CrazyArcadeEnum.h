#pragma once

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
	Box	
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