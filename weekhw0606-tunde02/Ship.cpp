#include "Ship.h"

Ship::Ship(const Position& InPosition, Direction InShipDirection, ShipType InShipType)
    : StartPosition(InPosition), ShipDirection(InShipDirection), Type(InShipType)
{
    int DirectionIndex = static_cast<int>(ShipDirection);
    int ShipLength = static_cast<int>(Type);
    Positions = new Position[ShipLength];

    for (int i = 0; i < ShipLength; i++)
    {
        Positions[i] = Position{ StartPosition + DPos[DirectionIndex] * i };
    }
}

Ship::~Ship()
{
    delete[] Positions;
    Positions = nullptr;
}
