#pragma once

#include "Bounds.h"
#include <unordered_set>
#include <cmath>

template<typename T>
void SafeDelete(T*& t)
{
    if (t)
    {
        delete t;
        t = nullptr;
    }
}

// 영역 구분을 위한 열거형.
enum class NodeIndex
{
    TopLeft,        // 경계선에 걸치지 않고 완전 포함.
    TopRight,
    BottomLeft,
    BottomRight,
    Straddling,     // 경계선에 걸친 경우.
    OutOfArea       // 영역을 벗어난 경우.
};

class Node
{
public:
    struct NodeHash
    {
        size_t operator()(const Node* node) const
        {
            size_t h1 = std::hash<float>()(node->GetBounds().X());
            size_t h2 = std::hash<float>()(node->GetBounds().Y());
            size_t h3 = std::hash<float>()(node->GetBounds().Width());
            size_t h4 = std::hash<float>()(node->GetBounds().Height());

            // 해시 값들을 조합해서 유니크한 해시 값 생성.
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };

    struct NodeEqual
    {
        bool operator()(const Node* left, const Node* right) const
        {
            const float EPSILON = 1e-6f;

            return std::fabs(left->GetBounds().X() - right->GetBounds().X()) < EPSILON &&
                std::fabs(left->GetBounds().Y() - right->GetBounds().Y()) < EPSILON &&
                std::fabs(left->GetBounds().Width() - right->GetBounds().Width()) < EPSILON &&
                std::fabs(left->GetBounds().Height() - right->GetBounds().Height()) < EPSILON;
        }

    };

public:
    Node(const Bounds& bounds, int depth = 0);
    ~Node();

    // 삽입(Insert).
    void Insert(Node* node);

    // 질의(Query).
    void Query(const Bounds& queryBounds, std::vector<Node*>& possibleNodes);

    // 정리.
    void Clear();

    // Getter.
    // 현재 노드의 영역.
    Bounds GetBounds() const { return bounds; }

    // 현재 영역에 포함된 노드.
    const std::unordered_set<Node*, NodeHash, NodeEqual>& Points() const { return points; }

    // 자식 노드.
    Node* TopLeft() const { return topLeft; }
    Node* TopRight() const { return topRight; }
    Node* BottomLeft() const { return bottomLeft; }
    Node* BottomRight() const { return bottomRight; }

private:
    // 영역을 4분할할 때 사용할 함수.
    bool Subdivde();

    // 영역이 분할됐는지 확인하는 함수.
    bool IsDivded();

    // 자식 노드 정리 함수.
    void ClearChildren();

    // 전달한 영역과 겹치는 영역을 반환하는 함수.
    NodeIndex TestRegion(const Bounds& bounds);

    // 전달한 영역이 포함되거나 결치는 영역을 모두 구할 때 사용하는 함수.
    std::vector<NodeIndex> GetQuads(const Bounds& bounds);

private:
    // 현재 노드의 깊이.
    int depth = 0;

    // 현재 노드의 영역.
    Bounds bounds;

    // 현재 영역에 포함된 노드.
    std::unordered_set<Node*, NodeHash, NodeEqual> points;

    // 자식 노드.
    Node* topLeft = nullptr;
    Node* topRight = nullptr;
    Node* bottomLeft = nullptr;
    Node* bottomRight = nullptr;
};