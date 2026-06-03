#include "BattleShipMap.h"

#include <stdlib.h>

BattleShipMap::BattleShipMap(int InRowSize, int InColumnSize)
    : RowSize(InRowSize), ColumnSize(InColumnSize)
{
    Map = new int[RowSize * ColumnSize] { 0 };
    IsRevealeds = new bool[RowSize * ColumnSize] { false };
    ShipTypeLength = ShipType2Int(ShipType::ShipTypeLength);
    Ships = new Ship[ShipTypeLength]{};
}

BattleShipMap::~BattleShipMap()
{
    delete[] Map;
    Map = nullptr;
    delete[] IsRevealeds;
    IsRevealeds = nullptr;
    delete[] Ships;
    Ships = nullptr;
}

void BattleShipMap::Initialize()
{
    for (int i = 0; i < ShipTypeLength; i++)
    {
        Position RandomPosition{ rand() % RowSize, rand() % ColumnSize };
        ShipType CurrentShipType = Int2ShipType(i + 2);
        Direction RandomDirection = Int2Direction(rand() % Direction2Int(Direction::DirectionLength));

        while (!CanPlaceShipAt(RandomPosition, CurrentShipType, RandomDirection))
        {
            RandomPosition= Position(rand() % RowSize, rand() % ColumnSize);
        }

        Ships[i] = PlaceShipAt(RandomPosition, CurrentShipType, RandomDirection);
    }
}

bool BattleShipMap::IsShipAt(Position InPosition) const
{
    return Map[InPosition.GetY() * ColumnSize + InPosition.GetX()] != 0;
}

bool BattleShipMap::IsRevealedAt(Position InPosition) const
{
    return IsRevealeds[InPosition.GetY() * ColumnSize + InPosition.GetX()];
}

bool BattleShipMap::AttackPlaceAt(Position InPosition)
{
    bool IsDestroyed = false;

    for (int i = 0; i < ShipTypeLength; i++)
    {
        if (Ships[i].HasPosition(InPosition))
        {
            Ships[i].DestroyAt(InPosition);
            IsDestroyed = !Ships[i].IsAlive();
        }
    }

    IsRevealeds[InPosition.GetY() * ColumnSize + InPosition.GetX()] = true;

    return IsDestroyed;
}

int BattleShipMap::GetAliveShipCount() const
{
    int AliveShipCount = 0;

    for (int i = 0; i < ShipTypeLength; i++)
    {
        if (Ships[i].IsAlive())
        {
            AliveShipCount++;
        }
    }

    return AliveShipCount;
}

std::string BattleShipMap::GetShipNameAt(Position InPosition) const
{
    for (int i = 0; i < ShipTypeLength; i++)
    {
        if (Ships[i].HasPosition(InPosition))
        {
            return Ships[i].GetShipName();
        }
    }

    return {};
}

void BattleShipMap::PrintMap() const
{
    // 기본적으로 보이지 않는 곳은 " . "
    // 빈 공간이면 " O ", 함선이 있는 자리는 " X "

    printf("y\\x");
    for (int i = 0; i < ColumnSize; i++)
    {
        printf(" %d ", i);
    }
    printf("\n");

    for (int i = 0; i < RowSize; i++)
    {
        printf(" %d ", i);
        for (int j = 0; j < ColumnSize; j++)
        {
            int MapInt = *(Map + i * ColumnSize + j);
            bool IsRevealed = *(IsRevealeds + i * ColumnSize + j);

            if (IsRevealed)
            {
                if (Int2ShipType(MapInt) != ShipType::None)
                {
                    printf(" X ");
                }
                else
                {
                    printf(" O ");
                }
            }
            else
            {
                printf(" . ");
            }
        }
        printf("\n");
    }
}

void BattleShipMap::PrintOriginalMap() const
{
    printf("y\\x");
    for (int i = 0; i < ColumnSize; i++)
    {
        printf(" %d ", i);
    }
    printf("\n");

    for (int i = 0; i < RowSize; i++)
    {
        printf(" %d ", i);
        for (int j = 0; j < ColumnSize; j++)
        {
            int MapInt = *(Map + i * ColumnSize + j);

            if (Int2ShipType(MapInt) != ShipType::None)
            {
                printf(" %s ", Int2ShipTypeString(MapInt).c_str());
            }
            else
            {
                printf(" . ");
            }
        }
        printf("\n");
    }
}

bool BattleShipMap::CanPlaceShipAt(Position InPosition, ShipType InShipType, Direction InDirection) const
{
    bool CanPlace = true;
    int ShipSize = ShipType2Int(InShipType);

    for (int i = 0; i < ShipSize; i++)
    {
        Position CheckPosition = InPosition + GetDirectionPosition(InDirection) * i;
        if (IsOutOfMap(CheckPosition) || IsShipAt(CheckPosition))
        {
            CanPlace = false;
            break;
        }
    }

    return CanPlace;
}

bool BattleShipMap::IsOutOfMap(Position InPosition) const
{
    return !(0 <= InPosition.GetY() && InPosition.GetY() < RowSize
             && 0 <= InPosition.GetX() && InPosition.GetX() < ColumnSize);
}

Ship BattleShipMap::PlaceShipAt(Position InPosition, ShipType InShipType, Direction InDirection)
{
    int ShipSize = static_cast<int>(InShipType);
    Position* Positions = new Position[ShipSize]{};

    for (int i = 0; i < ShipSize; i++)
    {
        Position ShipPosition = InPosition + GetDirectionPosition(InDirection) * i;

        Positions[i] = ShipPosition;
        Map[ShipPosition.GetY() * ColumnSize + ShipPosition.GetX()] = ShipSize;
    }

    return Ship{ Positions, InShipType };
}
