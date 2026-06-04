#include "Homework.h"
#include "BattleShipMap.h"
#include "Ship.h"

#include <iostream>
#include <string>
#include <stdlib.h>

void Homework_Run()
{
    // 시드값 설정
    unsigned int Seed = static_cast<unsigned int>(time(0));
    //Seed = 0;
    srand(Seed);

    // 게임 맵 생성 및 초기화
    BattleShipMap Map{ RowSize, ColumnSize };
    Map.Initialize();

    // 플레이어의 공격 횟수 및 공격 기록 배열 초기화
    int AttackChance = InitialAttackChance;
    Position AttackHistory[InitialAttackChance]{};

    // 이전 공격 결과를 저장할 문자열 선언
    std::string PrevResult{};

    while (true)
    {
        // 현재 맵 출력
        system("cls");
        printf("\n");
        Map.PrintMap();

        // 이전 공격 결과 출력
        printf("\n%s\n", PrevResult.c_str());

        // 공격 횟수가 없거나 모든 함선이 파괴됐다면 게임 종료
        if (!(AttackChance > 0 && Map.GetAliveShipCount() > 0))
        {
            break;
        }

        printf("남은 공격 기회\t: %d\n", AttackChance);
        printf("남은 적 함선 수\t: %d\n", Map.GetAliveShipCount());
        printf("공격할 위치를 입력하세요 (x y): ");

        // 공격 좌표 입력 받기
        std::string Input = InputCoordinates();

        // 입력받은 좌표로 실제 Position 객체를 생성
        Position InputPosition = ToPosition(Input);

        // 만약 이미 공격했던 좌표였다면, 공격하지 않고 반복문의 처음으로
        if (Map.IsRevealedAt(InputPosition))
        {
            PrevResult = "[이미 공격한 위치입니다..]";
            continue;
        }

        // 공격 좌표 기록
        AttackHistory[InitialAttackChance - AttackChance] = InputPosition;
        AttackChance--;

        // Map.AttackPlaceAt()을 통해 실제로 공격을 수행하고,
        // 이 과정에서 함선이 파괴되었는지 아닌지를 IsDestroyed에 저장
        bool IsDestroyed = Map.AttackPlaceAt(InputPosition);

        if (Map.IsShipAt(InputPosition))
        {
            // 공격 좌표에 함선이 있었고, 이번 공격으로 함선이 파괴된 경우
            if (IsDestroyed)
            {
                PrevResult = std::string("[적의 " + Map.GetShipNameAt(InputPosition) + " 격침!!!]");
            }
            // 공격 좌표에 함선이 있었지만 이번 공격으로 함선이 파괴되지는 않은 경우
            else
            {
                PrevResult = "[공격이 명중했습니다!]";
            }
        }
        // 공격 좌표에 함선이 없을 경우
        else
        {
            PrevResult = "[공격이 빗나갔습니다...]";
        }
    }

    // 게임 종료 후 함선이 있던 실제 위치, 플레이어의 공격 기록을 출력
    printf("\n[적 함선의 실제 위치 ↓]\n");
    Map.PrintOriginalMap();
    printf("\n[플레이어의 공격 기록 ↓]\n");
    Map.PrintMap();
    printf("\n");
    PrintAttackHistory(AttackHistory, InitialAttackChance - AttackChance);

    // 맵에 남은 함선 개수를 토대로 플레이어의 승리, 패배를 판단
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

    // 올바른 입력을 받을 때까지 반복
    while (!IsValidCoordinatesString(Input))
    {
        printf("[ERROR] 올바르지 않은 입력 형태입니다: ");
        std::getline(std::cin, Input);
    }

    return Input;
}

bool IsValidCoordinatesString(std::string CoordinatesString)
{
    // 올바르지 않은 입력들 ↓
    // "ab", "a b"
    // "1 ", " 1", "1  ", "  1"
    // "1  1", "2 3 "
    // "111 1", "5 30"

    // 공백 개수
    int SpaceCount = 0;

    // 앞, 뒤 문자열
    std::string XString{};
    std::string YString{};

    int i = -1;

    while (CoordinatesString[++i] != '\0')
    {
        // 공백은 앞에 이미 숫자가 존재해야하고, 공백 개수가 0일 때만 허용
        if (CoordinatesString[i] == ' ' && XString != "" && SpaceCount < 1)
        {
            SpaceCount++;
        }
        else if ('0' <= CoordinatesString[i] && CoordinatesString[i] <= '9')
        {
            // 숫자는 현재 공백 개수에 따라 앞 문자열이나 뒤 문자열에 이어붙이기
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

    // 앞, 뒤 문자열 중 빈 문자열이 있으면 올바르지 않은 입력
    if (XString == "" || YString == "")
    {
        return false;
    }

    int SpaceIndex = CoordinatesString.find(' ');
    int X = std::stoi(XString);
    int Y = std::stoi(YString);

    // 숫자로 변환한 X, Y가 맵의 범위를 벗어나면 올바르지 않은 입력
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
    // 맵의 각 좌표를 표현할 문자열 배열
    std::string* CoordinatesString = new std::string[RowSize * ColumnSize]{};

    // 기본 좌표 문자열로 초기화
    for (int i = 0; i < RowSize; i++)
    {
        for (int j = 0; j < ColumnSize; j++)
        {
            CoordinatesString[i * ColumnSize + j] = " . ";
        }
    }

    // 공격 기록의 좌표에 해당하는 문자열은 숫자로 변경
    for (int i = 0; i < AttackCount; i++)
    {
        int AttackX = AttackHistory[i].GetX();
        int AttackY = AttackHistory[i].GetY();

        // 자릿수 조절
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

    delete[] CoordinatesString;
    CoordinatesString = nullptr;
}
