﻿#include <iostream>
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
    Node* a = new Node(Bounds(50.1f, 50.1f));
    tree.Insert(a);
    Node* b = new Node(Bounds(60, 80));
    tree.Insert(b);
    Node* c = new Node(Bounds(90, 120));
    tree.Insert(c);
    Node* d = new Node(Bounds(150, 150));
    tree.Insert(d);
    Node* e = new Node(Bounds(10, 10));
    tree.Insert(e);

    std::cout << "노드 삽입 완료.\n";

    tree.Remove(b);

    Node testNode(Bounds(45, 45, 20, 40));
    std::vector<Node*> intersects = tree.Query(&testNode);
    if (intersects.size() == 0)
    {
        std::cout << "겹치는 노드를 찾지 못했습니다.\n";
    }
    else
    {
        std::cout << "겹치는 노드를 " << intersects.size() << "개 찾았습니다.\n";
        for (Node* node : intersects)
        {
            std::cout << "(" << node->GetBounds().X() << "," << node->GetBounds().Y() << ")\n";
        }
    }

    delete a;
    delete b;
    delete c;
    delete d;
    delete e;

    std::cin.get();
}