#pragma once

// Tile ÁÂÇ¥
struct FPoint
{
public:
	int X;
	int Y;

public:
	bool operator==(FPoint _Other)
	{
		return (_Other.X == X) && (_Other.Y == Y);
	}
};