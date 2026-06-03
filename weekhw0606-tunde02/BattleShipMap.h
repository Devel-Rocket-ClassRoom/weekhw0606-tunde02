#pragma once
#include "Position.h"
#include "Direction.h"
#include "ShipType.h"
#include "Ship.h"

class BattleShipMap
{
private:
    int RowSize = 0;
    int ColumnSize = 0;
    int* Map = nullptr;
    bool* IsRevealeds = nullptr;
    int ShipTypeLength = 0;
    Ship* Ships = nullptr;

public:
    BattleShipMap() = default;
    BattleShipMap(int InRowSize, int InColumnSize);
    ~BattleShipMap();

    void Initialize();
    bool IsShipAt(Position InPosition) const;
    bool IsRevealedAt(Position InPosition) const;
    bool AttackPlaceAt(Position InPosition);
    int GetAliveShipCount() const;
    std::string GetShipNameAt(Position InPosition) const;

    void PrintMap() const;
    void PrintOriginalMap() const;

private:
    bool CanPlaceShipAt(Position InPosition, ShipType InShipType, Direction InDirection) const;
    bool IsOutOfMap(Position InPosition) const;
    Ship PlaceShipAt(Position InPosition, ShipType InShipType, Direction InDirection);
};
