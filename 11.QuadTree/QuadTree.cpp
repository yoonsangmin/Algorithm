#include "QuadTree.h"

QuadTree::QuadTree(const Bounds& bounds)
{
    // 루트 노드 생성.
    root = new Node(bounds);
}

QuadTree::~QuadTree()
{
    // 루트 노드 삭제.
    SafeDelete(root);
}

void QuadTree::Insert(Node* node)
{
    root->Insert(node);
}

void QuadTree::Remove(Node* node)
{
    root->Remove(node);
}

std::vector<Node*> QuadTree::Query(Node* queryNode)
{
    // 겹칠 가능성이 있는 영역 확인.
    std::vector<Node*> possibleNodes;
    root->Query(queryNode->GetBounds(), possibleNodes);

    // 겹침 가능성 있는 노드에서 실제로 겹치는 노드들만 다시 검사.
    std::vector<Node*> intersects;
    for (Node* node : possibleNodes)
    {
        for (Node* point : node->Points())
        {
            if (point->GetBounds().Intersects(queryNode->GetBounds()))
            {
                intersects.emplace_back(point);
                continue;
            }
        }
    }

    // 검사한 결과 최종 반환.
    return intersects;
}