#pragma once
#include <string>

class Position
{
private:
    int X = -1;
    int Y = -1;

public:
    Position() = default;
    Position(int InX, int InY) : X(InX), Y(InY) {}
    Position(const Position& other) = default;

    Position operator+(const Position& other) const;
    Position operator-(const Position& other) const;
    Position operator*(int other) const;
    bool operator==(const Position& other) const;

    std::string ToString() const;

    inline int GetX() const { return X; }
    inline int GetY() const { return Y; }
    inline void SetX(int InX) { X = InX; }
    inline void SetY(int InY) { Y = InY; }
};
