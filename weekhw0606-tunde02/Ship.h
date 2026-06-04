#pragma once
#include "Position.h"
#include "ShipType.h"

/// <summary>
/// 함선을 표현하는 클래스로, 함선의 종류, 체력, 사이즈, 맵 상의 좌표 배열, 각 좌표가 파괴되었는지 여부 배열을 가지고 있다
/// </summary>
class Ship
{
private:
    /// <summary>
    /// 맵 상의 좌표 배열
    /// </summary>
    Position* Positions = nullptr;

    /// <summary>
    /// 함선을 이루는 각 좌표가 파괴되었는지 아닌지 저장한 배열
    /// </summary>
    bool* IsDestroyedPositions = nullptr;

    /// <summary>
    /// 함선의 종류
    /// </summary>
    ShipType Type = ShipType::None;

    /// <summary>
    /// 함선의 크기
    /// </summary>
    int ShipSize = 0;

    /// <summary>
    /// 함선의 체력
    /// </summary>
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

    /// <summary>
    /// 함선이 매개변수로 전달받은 좌표를 가지고 있는지 여부를 반환하는 함수
    /// </summary>
    /// <param name="InPosition">좌표</param>
    /// <returns>Positions에 좌표가 있다면 true, 없다면 false</returns>
    bool HasPosition(Position InPosition) const;

    /// <summary>
    /// 매개변수로 전달받은 좌표에 해당하는 IsDestroyedPositions를 true 로 바꾸고, 체력을 갱신하는 함수
    /// </summary>
    /// <param name="InPosition">좌표</param>
    void DestroyAt(Position InPosition);

    /// <summary>
    /// 함선의 종류에 따라 알맞은 문자열을 반환하는 함수
    /// </summary>
    /// <returns>함선의 종류 문자열</returns>
    std::string GetShipName() const;
};
