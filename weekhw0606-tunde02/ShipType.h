#pragma once
#include <string>

/// <summary>
/// 함선의 종류를 나타내는 열거체로, 열거자의 값은 해당 함선의 길이를 의미
/// <para>구축함 : 2</para>
/// <para>순양함 : 3</para>
/// <para>전함 : 4</para>
/// <para>항공모함 : 5</para>
/// </summary>
enum class ShipType
{
    Babysitter      = 2,
    Cruiser         = 3,
    Battleship      = 4,
    AircraftCarrier = 5,

    None            = 0,
    ShipTypeLength  = 4
};

inline int ShipType2Int(ShipType InShipType)
{
    if (InShipType == ShipType::Babysitter)
    {
        return 2;
    }
    else if (InShipType == ShipType::Cruiser)
    {
        return 3;
    }
    else if (InShipType == ShipType::Battleship)
    {
        return 4;
    }
    else if (InShipType == ShipType::AircraftCarrier)
    {
        return 5;
    }
    else if (InShipType == ShipType::ShipTypeLength)
    {
        return 4;
    }
    else
    {
        return 0;
    }
}

inline ShipType Int2ShipType(int InInt)
{
    switch (InInt)
    {
        case 2:
            return ShipType::Babysitter;
        case 3:
            return ShipType::Cruiser;
        case 4:
            return ShipType::Battleship;
        case 5:
            return ShipType::AircraftCarrier;
        default:
            return ShipType::None;
    }
}

inline std::string ShipType2ShipTypeString(ShipType InShipType)
{
    switch (InShipType)
    {
        case ShipType::Babysitter:
            return std::string{ "2" };
        case ShipType::Cruiser:
            return std::string{ "3" };
        case ShipType::Battleship:
            return std::string{ "4" };
        case ShipType::AircraftCarrier:
            return std::string{ "5" };
        default:
            return{};
    }
}

inline std::string Int2ShipTypeString(int InInt)
{
    return ShipType2ShipTypeString(Int2ShipType(InInt));
}
