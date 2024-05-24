#pragma once

enum class ERenderOrder
{
	BackGround,
	Shadow
};

enum class EMapType
{
	Village,
	Forest,
	Pirate,
	Pirate02,
	Test,
	None
};

enum class EWaveType
{
	None,
	Left,
	LeftEnd,
	Right,
	RightEnd,
	Up,
	UpEnd,
	Down,
	DownEnd,
	UnderBlock,
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
	Ray,
	None,
};

// 3000 ~ 3999 (색 타입)
enum class ECharacterColor
{
	Red = 3000,
	Yellow,
	Orange,
	Green,
	Skyblue,
	Blue,
	Purple,
	Pink,
	None,
};

// 1000 ~ 1999 (맵 블록 타입)
enum class EBlockType
{
	None = 1000,
	Wall,
	Box,
	MoveBox
};

// 2000 ~ 2999 (아이템 타입)
enum class EItemType
{
	None = 2000,
	Bubble,
	Devil,
	Fluid,
	Glove,
	RedDevil,
	Roller,
	Shoes,
	Ultra,
	Superman,
	Owl,
	Turtle,
	UFO,
	Needle,
};