#pragma once
#include "Position.h"
#include "Direction.h"
#include "ShipType.h"
#include "Ship.h"

/// <summary>
/// 게임 맵에 대한 정보를 가진 클래스
/// </summary>
class BattleShipMap
{
private:
    int RowSize = 0;
    int ColumnSize = 0;

    /// <summary>
    /// 맵 정보를 저장한 배열. 맵의 각 좌표는 비어 있으면 0, 아니면 함선의 길이 값을 저장
    /// </summary>
    int* Map = nullptr;

    /// <summary>
    /// 맵의 각 좌표의 공개 여부를 저장한 배열
    /// </summary>
    bool* IsRevealeds = nullptr;

    /// <summary>
    /// 함선의 종류 개수
    /// </summary>
    int ShipTypeLength = 0;

    /// <summary>
    /// 맵에 있는 함선 배열
    /// </summary>
    Ship* Ships = nullptr;

public:
    BattleShipMap() = default;
    BattleShipMap(int InRowSize, int InColumnSize);
    ~BattleShipMap();

    /// <summary>
    /// 맵을 초기화하는 함수로, 랜덤한 좌표에 랜덤한 방향으로 함선을 배치한다
    /// </summary>
    void Initialize();

    /// <summary>
    /// 매개변수로 전달된 좌표에 함선이 있는지 없는지 반환하는 함수
    /// </summary>
    /// <param name="InPosition">좌표</param>
    /// <returns>함선이 있으면 true, 없으면 false</returns>
    bool IsShipAt(Position InPosition) const;

    /// <summary>
    /// 매개변수로 전달된 좌표가 공개된 상태인지 아닌지 반환하는 함수
    /// </summary>
    /// <param name="InPosition">좌표</param>
    /// <returns>좌표가 공개되어 있다면 true, 아니라면 false</returns>
    bool IsRevealedAt(Position InPosition) const;

    /// <summary>
    /// 매개변수로 전달된 좌표를 공개 상태로 변경하고, 해당 좌표에 함선이 있었다면 그 함선에 대한 공격을 처리하는 함수
    /// </summary>
    /// <param name="InPosition">공격 좌표</param>
    /// <returns>이 공격으로 함선이 파괴되었다면 true, 파괴되지 않았거나 함선이 공격받지 않았다면 false</returns>
    bool AttackPlaceAt(Position InPosition);

    /// <summary>
    /// 파괴되지 않은 함선의 개수를 반환하는 함수
    /// </summary>
    /// <returns>파괴되지 않은 함선의 개수</returns>
    int GetAliveShipCount() const;

    /// <summary>
    /// 매개변수로 전달된 좌표에 있는 함선의 이름을 반환하는 함수
    /// </summary>
    /// <param name="InPosition">좌표</param>
    /// <returns>함선이 있다면 해당 함선의 이름을, 없다면 빈 문자열을 반환</returns>
    std::string GetShipNameAt(Position InPosition) const;

    /// <summary>
    /// 맵의 현황을 출력하는 함수
    /// </summary>
    void PrintMap() const;

    /// <summary>
    /// 맵의 현황을 모두 공개한 상태로 출력하는 함수
    /// </summary>
    void PrintOriginalMap() const;

private:
    /// <summary>
    /// 지정한 위치에 특정 함선을 주어진 방향으로 배치할 수 있는지 검사하는 함수
    /// </summary>
    /// <param name="InPosition">함선을 배치하려는 시작 위치 좌표</param>
    /// <param name="InShipType">함선의 종류</param>
    /// <param name="InDirection">배치 방향</param>
    /// <returns>함선을 배치할 수 있다면 true, 배치할 수 없다면 false</returns>
    bool CanPlaceShipAt(Position InPosition, ShipType InShipType, Direction InDirection) const;

    /// <summary>
    /// 주어진 좌표가 지도 범위를 벗어났는지 검사하는 함수
    /// </summary>
    /// <param name="InPosition">검사할 좌표</param>
    /// <returns>좌표가 지도 범위를 벗어나면 true, 그렇지 않으면 false</returns>
    bool IsOutOfMap(Position InPosition) const;

    /// <summary>
    /// 함선을 생성해 주어진 좌표에 주어진 방향으로 배치하는 함수
    /// </summary>
    /// <param name="InPosition">함선을 배치하려는 시작 위치 좌표</param>
    /// <param name="InShipType">함선의 종류</param>
    /// <param name="InDirection">배치 방향</param>
    /// <returns>배치한 새로 생성된 함선 객체</returns>
    Ship PlaceShipAt(Position InPosition, ShipType InShipType, Direction InDirection);
};
