#include <iostream>
#include "QuadTree.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
    // 메모리 누수 검사.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // 0, 0을 왼쪽 상단으로, (200, 200) 크기를 가지는 영역 선언.
    QuadTree tree(Bounds(0, 0, 200, 200));

    // 삽입.
    tree.Insert(new Node(Bounds(50, 50)));
    tree.Insert(new Node(Bounds(60, 80)));
    tree.Insert(new Node(Bounds(90, 120)));
    tree.Insert(new Node(Bounds(150, 150)));
    tree.Insert(new Node(Bounds(10, 10)));

    std::cout << "노드 삽입 완료.\n";

    Node testNode(Bounds(45, 45, 20, 20));
    std::vector<Node*> intersects = tree.Query(&testNode);
    if (intersects.size() == 0)
    {
        std::cout << "겹치는 노드를 찾지 못했습니다.\n";
    }
    else
    {
        std::cout << "겹치는 노드를 " << intersects.size() << "개 찾았습니다.\n";
    }

    std::cin.get();
}