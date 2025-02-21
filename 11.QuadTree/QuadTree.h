#pragma once

#include <vector>
#include "Node.h"

// 쿼드 트리 클래스.
class QuadTree
{
public:
    QuadTree(const Bounds& bounds);
    ~QuadTree();

    // 트리에 노드를 추가하는 함수.
    void Insert(Node* node);

    // 전달한 노드와 겹치는 노드를 반환하는 함수.
    std::vector<Node*> Query(Node* queryNode);

public:
    // 나눌 수 있는 트리의 최대 깊이 값.
    static const int maxDepth = 4;

private:
    Node* root = nullptr;
};