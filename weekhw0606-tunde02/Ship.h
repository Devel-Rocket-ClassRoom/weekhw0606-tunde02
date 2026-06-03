#pragma once
#include "Position.h"
#include "Direction.h"
#include "ShipType.h"

class Ship
{
private:
    Position* Positions = nullptr;
    bool* IsDestroyedPositions = nullptr;
    ShipType Type = ShipType::None;
    int ShipSize = 0;
    int Hp = 0;

public:
    Ship() = default;
    ~Ship();

    Ship(Position* InPositions, ShipType InShipType);
    Ship(Ship&& other) noexcept;
    Ship(const Ship& other) = delete;
    Ship& operator=(const Ship& other) = delete;
    Ship& operator=(Ship&& other) noexcept;

    bool IsAlive() const;
    bool HasPosition(Position InPosition) const;
    void DestroyAt(Position InPosition);
    std::string GetShipName() const;
};
