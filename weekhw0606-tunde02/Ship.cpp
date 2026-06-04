#include "Ship.h"

Ship::~Ship()
{
    delete[] Positions;
    Positions = nullptr;
    delete[] IsDestroyedPositions;
    IsDestroyedPositions = nullptr;
}

Ship::Ship(Position* InPositions, ShipType InShipType)
    : Positions(InPositions), Type(InShipType)
{
    ShipSize = ShipType2Int(Type);
    IsDestroyedPositions = new bool[ShipSize] { false };
    Hp = ShipSize;
}

Ship::Ship(Ship&& other) noexcept
    : Positions(other.Positions), IsDestroyedPositions(other.IsDestroyedPositions), Type(other.Type), ShipSize(other.ShipSize), Hp(other.Hp)
{
    other.Positions = nullptr;
    other.IsDestroyedPositions = nullptr;
}

Ship& Ship::operator=(Ship&& other) noexcept
{
    if (this != &other)
    {
        // 깊은 복사

        delete[] Positions;
        delete[] IsDestroyedPositions;

        Positions = other.Positions;
        IsDestroyedPositions = other.IsDestroyedPositions;
        Type = other.Type;
        ShipSize = other.ShipSize;
        Hp = other.Hp;

        other.Positions = nullptr;
        other.IsDestroyedPositions = nullptr;
    }

    return *this;
}

bool Ship::IsAlive() const
{
    return Hp > 0;
}

bool Ship::HasPosition(Position InPosition) const
{
    for (int i = 0; i < ShipSize; i++)
    {
        if (Positions[i] == InPosition)
        {
            return true;
        }
    }

    return false;
}

void Ship::DestroyAt(Position InPosition)
{
    for (int i = 0; i < ShipSize; i++)
    {
        if (Positions[i] == InPosition && !IsDestroyedPositions[i])
        {
            IsDestroyedPositions[i] = true;
            Hp--;
        }
    }
}

std::string Ship::GetShipName() const
{
    switch (Type)
    {
        case ShipType::Babysitter:
            return std::string{ "구축함" };
        case ShipType::Cruiser:
            return std::string{ "순양함" };
        case ShipType::Battleship:
            return std::string{ "전함" };
        case ShipType::AircraftCarrier:
            return std::string{ "함공모함" };
        default:
            return {};
    }
}
