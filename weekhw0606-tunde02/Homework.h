#pragma once
#include "Position.h"

#include <string>

/*
Battle Ship 게임 만들기
  1. 목표
    - 플레이어는 컴퓨터가 숨겨놓은 적 함선을 찾아 격침시킨다.
  2. 맵 크기는 10 x 10이다.
    - 각 칸에는 함선 또는 빈 칸이 위치한다.
  3. 적 함선 종류
    - 총 4척: 크기 5, 4, 3, 2 (항공모함, 전함, 순양함, 구축함 등)
  4. 함선 배치
    - 함선은 맵에 겹치지 않게 가로 또는 세로로 랜덤 배치된다.
  5. 플레이어의 목표
    - 제한된 공격 횟수(30회) 내에 모든 적 함선을 명중시켜 격침시키는 것.
  6. 게임 진행 방식
    - 플레이어는 (x, y) 좌표를 입력해 공격한다.
    - 공격 결과(명중/실패)는 바로 표시되고, 플레이어의 맵에 기록된다.
    - 이미 공격한 좌표는 다시 공격할 수 없다.
  7. 함선 격침
    - 한 함선의 모든 칸을 명중시키면 "격침" 메시지가 출력된다.
  8. 게임 종료 조건
    - 모든 적 함선을 격침시키면 승리.
    - 주어진 횟수 내에 격침하지 못하면 패배하며, 패배 시 적 함선의 실제 위치가 공개된다.
  9. 추가 정보
    - 남은 공격 횟수와 남은 적 함선 수가 항상 안내된다.
  10. 제출 방식
    - 리포지토리 링크와 플레이 영상 링크 올리기
*/

/// <summary>
/// 프로그램 실행 함수
/// </summary>
void Homework_Run();

/// <summary>
/// 맵의 행 개수
/// </summary>
const int RowSize               = 10;

/// <summary>
/// 맵의 열 개수
/// </summary>
const int ColumnSize            = 10;

/// <summary>
/// 플레이어가 공격할 수 있는 횟수
/// </summary>
const int InitialAttackChance   = 30;

/// <summary>
/// 공격할 좌표를 입력받는 함수
/// <para>올바른 형태: "x y"</para>
/// </summary>
/// <returns>올바른 형태의 좌표 문자열</returns>
std::string InputCoordinates();

/// <summary>
/// 매개변수로 전달된 문자열이 올바른 좌표 형태인지 검사하는 함수
/// </summary>
/// <param name="CoordinatesString">좌표 문자열</param>
/// <returns>올바른 형태라면 true, 아니라면 false</returns>
bool IsValidCoordinatesString(std::string CoordinatesString);

/// <summary>
/// 올바른 형태의 좌표 문자열을 이용하여 Position 객체를 만들어 반환하는 함수
/// </summary>
/// <param name="ValidInput">올바른 형태의 좌표 문자열</param>
/// <returns>좌표 문자열을 분리하여 만든 Position 객체</returns>
Position ToPosition(std::string ValidInput);

/// <summary>
/// 플레이어가 공격한 기록을 맵에 순서대로 표시하여 출력하는 함수
/// </summary>
/// <param name="AttackHistory">플레이어가 공격한 기록인 Position 배열</param>
/// <param name="AttackCount">플레이어가 공격한 횟수</param>
void PrintAttackHistory(const Position* AttackHistory, int AttackCount);
