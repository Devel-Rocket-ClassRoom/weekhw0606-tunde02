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
            // 주어진 좌표를 가진 함선이 있다면 해당 함선의 해당 좌표를 공격
            Ships[i].DestroyAt(InPosition);

            // 공격을 마친 후에 함선의 파괴 여부를 저장
            IsDestroyed = !Ships[i].IsAlive();
        }
    }

    // 공격을 시도한 좌표는 맵 상에서 공개하도록 변경
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
                // 맵의 좌표의 내용이 함선이라면 해당 함선 문자열을 출력
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
        // 시작 좌표에서 주어진 방향으로 i만큼 나아간 좌표
        Position CheckPosition = InPosition + GetDirectionPosition(InDirection) * i;

        // 함선을 배치할 좌표가 맵을 벗어나거나, 이미 다른 함선이 있는 좌표라면 함선을 배치할 수 없다
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
    int ShipSize = ShipType2Int(InShipType);
    Position* Positions = new Position[ShipSize]{};

    for (int i = 0; i < ShipSize; i++)
    {
        // 시작 좌표에서 주어진 방향으로 i만큼 나아간 좌표
        Position ShipPosition = InPosition + GetDirectionPosition(InDirection) * i;

        Positions[i] = ShipPosition;

        // 맵에 함선을 표시
        Map[ShipPosition.GetY() * ColumnSize + ShipPosition.GetX()] = ShipSize;
    }

    return Ship{ Positions, InShipType };
}
