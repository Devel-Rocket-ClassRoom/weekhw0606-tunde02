#include "Position.h"

Position Position::operator+(const Position& other) const
{
    Position Result;

    Result.X = this->X + other.X;
    Result.Y = this->Y + other.Y;

    return Result;
}

Position Position::operator-(const Position& other) const
{
    Position Result;

    Result.X = this->X - other.X;
    Result.Y = this->Y - other.Y;

    return Result;
}

Position Position::operator*(int other) const
{
    Position Result;

    Result.X = this->X * other;
    Result.Y = this->Y * other;

    return Result;
}

std::string Position::ToString() const
{
    return "(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
}
