#include "Homework.h"
#include "Ship.h"
#include <iostream>

void Homework_Run()
{
    printf("Battle Ship game started! Sink all enemy ships within 50 turns.\n");

    int* Map = new int[RowSize * ColumnSize] { 0 };
    bool* IsRevealeds = new bool[RowSize * ColumnSize] { false };

    *(Map + 2 * ColumnSize + 1) = 2;
    Map[2 * ColumnSize + 2] = 2;
    Map[2 * ColumnSize + 3] = 2;

    *(IsRevealeds + 2 * ColumnSize + 1) = true;
    IsRevealeds[2 * ColumnSize + 2] = true;
    IsRevealeds[2 * ColumnSize + 3] = false;
    IsRevealeds[0 * ColumnSize + 0] = true;

    PrintDebugMap(Map, RowSize, ColumnSize);
    PrintOriginalMap(Map, RowSize, ColumnSize);
    PrintMap(Map, IsRevealeds, RowSize, ColumnSize);

    delete[] Map;
    Map = nullptr;
    delete[] IsRevealeds;
    IsRevealeds = nullptr;
}

void PrintDebugMap(const int* InMap, int InRowSize, int InColumnSize)
{
    printf("   ");
    for (int i = 0; i < ColumnSize; i++)
    {
        printf(" %d ", i);
    }
    printf("\n");

    for (int i = 0; i < InRowSize; i++)
    {
        printf(" %d ", i);
        for (int j = 0; j < InColumnSize; j++)
        {
            printf(" %d ", *(InMap + i * InColumnSize + j));
        }
        printf("\n");
    }
}

void PrintMap(const int* InMap, const bool* InIsRevealeds, int InRowSize, int InColumnSize)
{
    // 기본적으로 보이지 않는 곳은 .
    // 빈 공간이면 O, Ship이 있는 자리는 X
    printf("   ");
    for (int i = 0; i < ColumnSize; i++)
    {
        printf(" %d ", i);
    }
    printf("\n");

    for (int i = 0; i < InRowSize; i++)
    {
        printf(" %d ", i);
        for (int j = 0; j < InColumnSize; j++)
        {
            int MapInt = *(InMap + i * InColumnSize + j);
            bool IsRevealed = *(InIsRevealeds + i * InColumnSize + j);

            if (IsRevealed)
            {
                if (Int2ShipType(MapInt) != Ship::ShipType::None)
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

void PrintOriginalMap(const int* InMap, int InRowSize, int InColumnSize)
{
    printf("   ");
    for (int i = 0; i < ColumnSize; i++)
    {
        printf(" %d ", i);
    }
    printf("\n");

    for (int i = 0; i < InRowSize; i++)
    {
        printf(" %d ", i);
        for (int j = 0; j < InColumnSize; j++)
        {
            int MapInt = *(InMap + i * InColumnSize + j);

            if (Int2ShipType(MapInt) != Ship::ShipType::None)
            {
                printf(" %s ", Int2ShipString(MapInt).c_str());
            }
            else
            {
                printf(" . ");
            }
        }
        printf("\n");
    }
}

Ship::ShipType Int2ShipType(int InInt)
{
    switch (InInt)
    {
        case 2:
            return Ship::ShipType::Babysitter;
        case 3:
            return Ship::ShipType::Cruiser;
        case 4:
            return Ship::ShipType::Battleship;
        case 5:
            return Ship::ShipType::AircraftCarrier;
        default:
            return Ship::ShipType::None;
    }
}

std::string Int2ShipString(int InInt)
{
    return ShipType2ShipString(static_cast<Ship::ShipType>(InInt));
}

std::string ShipType2ShipString(Ship::ShipType InShipType)
{
    switch (InShipType)
    {
        case Ship::ShipType::Babysitter:
            return std::string{ "S" };
        case Ship::ShipType::Cruiser:
            return std::string{ "S" };
        case Ship::ShipType::Battleship:
            return std::string{ "S" };
        case Ship::ShipType::AircraftCarrier:
            return std::string{ "S" };
        default:
            return{};
    }
}
