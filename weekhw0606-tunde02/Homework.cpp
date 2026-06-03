#include "Homework.h"
#include "BattleShipMap.h"
#include "Ship.h"

#include <iostream>
#include <string>
#include <stdlib.h>

void Homework_Run()
{
    unsigned int Seed = static_cast<unsigned int>(time(0));
    //Seed = 0;
    srand(Seed);

    BattleShipMap Map{ RowSize, ColumnSize };
    Map.Initialize();

    int AttackChance = InitialAttackChance;
    Position AttackHistory[InitialAttackChance]{};
    std::string PrevResult{};

    while (true)
    {
        system("cls");
        printf("\n");
        Map.PrintMap();

        printf("\n%s\n", PrevResult.c_str());

        if (!(AttackChance > 0 && Map.GetAliveShipCount() > 0))
        {
            break;
        }

        printf("남은 공격 기회\t: %d\n", AttackChance);
        printf("남은 적 함선 수\t: %d\n", Map.GetAliveShipCount());
        printf("공격할 위치를 입력하세요 (x y): ");

        std::string Input = InputCoordinates();
        Position InputPosition = ToPosition(Input);

        if (Map.IsRevealedAt(InputPosition))
        {
            PrevResult = "[이미 공격한 위치입니다..]";
            continue;
        }

        AttackHistory[InitialAttackChance - AttackChance] = InputPosition;
        AttackChance--;
        bool IsDestroyed = Map.AttackPlaceAt(InputPosition);

        if (Map.IsShipAt(InputPosition))
        {
            if (IsDestroyed)
            {
                PrevResult = std::string("[적의 " + Map.GetShipNameAt(InputPosition) + " 격침!!!]");
            }
            else
            {
                PrevResult = "[공격이 명중했습니다!]";
            }
        }
        else
        {
            PrevResult = "[공격이 빗나갔습니다...]";
        }
    }

    printf("\n[적 함선의 실제 위치 ↓]\n");
    Map.PrintOriginalMap();
    printf("\n[플레이어의 공격 기록 ↓]\n");
    Map.PrintMap();
    printf("\n");
    PrintAttackHistory(AttackHistory, InitialAttackChance - AttackChance);

    if (Map.GetAliveShipCount() == 0)
    {
        printf("\n모든 함선을 격침했습니다!!!\n");
    }
    else
    {
        printf("\n플레이어의 패배...\n");
    }
}

std::string InputCoordinates()
{
    std::string Input{};
    std::getline(std::cin, Input);

    while (!IsValidCoordinatesString(Input))
    {
        printf("[ERROR] 올바르지 않은 입력 형태입니다: ");
        std::getline(std::cin, Input);
    }

    return Input;
}

bool IsValidCoordinatesString(std::string CoordinatesString)
{
    // 유효하지 않은 입력들 ↓
    // "ab", "a b"
    // "1 ", " 1", "1  ", "  1"
    // "1  1", "2 3 "
    // "111 1", "5 30"

    int SpaceCount = 0;
    std::string XString{};
    std::string YString{};
    bool IsNumberInputted = false;
    int i = -1;

    while (CoordinatesString[++i] != '\0')
    {
        if (CoordinatesString[i] == ' ' && IsNumberInputted && SpaceCount < 1)
        {
            SpaceCount++;
        }
        else if ('0' <= CoordinatesString[i] && CoordinatesString[i] <= '9')
        {
            IsNumberInputted = true;
            if (SpaceCount == 0)
            {
                XString += CoordinatesString[i];
            }
            else
            {
                YString += CoordinatesString[i];
            }
        }
        else
        {
            return false;
        }
    }

    if (XString == "" || YString == "")
    {
        return false;
    }

    int SpaceIndex = CoordinatesString.find(' ');
    int X = std::stoi(XString);
    int Y = std::stoi(YString);

    if (!(0 <= X && X < ColumnSize && 0 <= Y && Y < RowSize))
    {
        return false;
    }

    return true;
}

Position ToPosition(std::string ValidInput)
{
    int SpaceIndex = ValidInput.find(' ');
    std::string XString{ ValidInput.substr(0, SpaceIndex) };
    std::string YString{ ValidInput.substr(SpaceIndex + 1) };

    return Position{ std::stoi(XString), std::stoi(YString) };
}

void PrintAttackHistory(const Position* AttackHistory, int AttackCount)
{
    std::string* CoordinatesString = new std::string[RowSize * ColumnSize]{};

    for (int i = 0; i < RowSize; i++)
    {
        for (int j = 0; j < ColumnSize; j++)
        {
            CoordinatesString[i * ColumnSize + j] = " . ";
        }
    }

    for (int i = 0; i < AttackCount; i++)
    {
        int AttackX = AttackHistory[i].GetX();
        int AttackY = AttackHistory[i].GetY();

        if (i + 1 < 10)
        {
            CoordinatesString[AttackY * ColumnSize + AttackX] = " " + std::to_string(i + 1) + " ";
        }
        else
        {
            CoordinatesString[AttackY * ColumnSize + AttackX] = " " + std::to_string(i + 1);
        }
    }

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
            printf("%s", CoordinatesString[i * ColumnSize + j].c_str());
        }
        printf("\n");
    }
}
