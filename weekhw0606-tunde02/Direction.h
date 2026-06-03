#pragma once
#include "Position.h"

enum class Direction
{
    Up              = 0,
    Down            = 1,
    Left            = 2,
    Right           = 3,

    None            = -1,
    DirectionLength = 4
};

inline Direction Int2Direction(int InInt)
{
    switch (InInt)
    {
        case 0:
            return Direction::Up;
        case 1:
            return Direction::Down;
        case 2:
            return Direction::Left;
        case 3:
            return Direction::Right;
        case 4:
            return Direction::DirectionLength;
        default:
            return Direction::None;
    }
}

inline int Direction2Int(Direction InDirection)
{
    switch (InDirection)
    {
        case Direction::Up:
            return 0;
        case Direction::Down:
            return 1;
        case Direction::Left:
            return 2;
        case Direction::Right:
            return 3;
        case Direction::DirectionLength:
            return 4;
        default:
            return -1;
    }
}

inline Position GetDirectionPosition(Direction InDirection)
{
    switch (InDirection)
    {
        case Direction::Up:
            return Position{ 0, -1 };
        case Direction::Down:
            return Position{ 0, 1 };
        case Direction::Left:
            return Position{ -1, 0 };
        case Direction::Right:
            return Position{ 1, 0 };
        default:
            return Position{};
    }
}
