#pragma once
#include "Position.h"


class Ship
{
public:
    enum class Direction { Up = 0, Down = 1, Left = 2, Right = 3, DirectionLength = 4 };
    enum class ShipType { None = 0, Babysitter = 2, Cruiser = 3, Battleship = 4, AircraftCarrier = 5 };

private:
    const Position DPos[4]{ Position{ -1, 0 }, Position{ 1, 0 }, Position{ 0, -1 }, Position{ 0, 1 } };
    Position StartPosition{};
    Position* Positions = nullptr;
    Direction ShipDirection = Direction::DirectionLength;
    ShipType Type = ShipType::None;

public:
    Ship() = default;
    Ship(const Position& InPosition, Direction InShipDirection, ShipType InShipType);
    ~Ship();
};
