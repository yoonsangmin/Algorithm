#pragma once

// 사각형 영역을 표시하는 클래스.
class Bounds
{
public:
    Bounds(float x, float y, float width = 1.0f, float height = 1.0f)
        : x(x), y(y), width(width), height(height)
    {
    }

    // Getter.
    float X() const { return x; }
    float Y() const { return y; }
    float Width() const { return width; }
    float Height() const { return height; }

    float MaxX() const { return x + width; }
    float MaxY() const { return y + height; }

    // 겹침 판정 함수.
    bool Intersects(const Bounds& other) const;

private:
    // 왼쪽 상단 기준.
    float x = 0;
    float y = 0;
    float width = 1;
    float height = 1;
};