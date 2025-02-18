#pragma once

#include <iostream>
#include <string>

// 메모리 삭제 함수.
template<typename T>
void safeDelete(T*& t)
{
    if (t)
    {
        delete t;
        t = nullptr;
    }
}

// 노드 색상 열거형.
enum class Color : char
{
    Red,
    Black
};

// 노드 클래스.
class Node
{
public:
    //생성자.
    Node(int data = 0, Color color = Color::Red);
    ~Node() = default;

    // Getter/Setter.
    inline int Data() const { return data; }
    inline void SetData(int newData) { data = newData; }

    // 색상.
    inline const Color GetColor() const { return color; }
    inline void SetColor(Color newColor) { color = newColor; }
    const char* ColorString() const;

    // 부모 노드.
    inline Node* Parent() const { return parent; }
    inline void SetParent(Node* newParent) { parent = newParent; }

    // 왼쪽 자식 노드.
    inline Node* Left() const { return left; }
    inline void SetLeft(Node* newLeft) { left = newLeft; }

    // 오른쪽 자식 노드.
    inline Node* Right() const { return right; }
    inline void SetRight(Node* newRight) { right = newRight; }

private:
    // 데이터.
    int data = 0;

    // 색상.
    Color color = Color::Red;

    // 부모 노드.
    Node* parent = nullptr;

    // 왼쪽 자식 노드.
    Node* left = nullptr;

    // 오른쪽 자식 노드.
    Node* right = nullptr;
};