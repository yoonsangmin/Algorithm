#include <iostream>
#include <vector>

#include "AStar.h"
#include "Node.h"

int main()
{
    // 그리드 생성.
    // 0: 이동 가능.
    // 1: 이동 불가(장애물).
    // 2: 시작 위치.
    // 3: 목표 위치.
    std::vector<std::vector<int>> grid =
    {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    };

    // 맵에서 시작 위치 목표 위치 검색.
    Node* startNode = nullptr;
    Node* goalNode = nullptr;

    bool initialized = false;
    for (int y = 0; y < (int)grid.size(); ++y)
    {
        // 이미 찾았으면 종료.
        if (startNode && goalNode)
        {
            initialized = true;
            break;
        }

        for (int x = 0; x < (int)grid[0].size(); ++x)
        {
            // 이미 찾았으면 종료.
            if (startNode && goalNode)
            {
                initialized = true;
                break;
            }

            // 시작 지점.
            if (grid[y][x] == 2)
            {
                startNode = new Node(x, y);
                grid[y][x] = 0;
                continue;
            }

            if (grid[y][x] == 3)
            {
                goalNode = new Node(x, y);
                grid[y][x] = 0;
                continue;
            }
        }
    }

    // AStar 객체.
    AStar aStar;

    // 경로 탐색.
    std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grid);

    // 결과 확인.
    if (!path.empty())
    {
        std::cout << "경로를 찾았습니다. 탐색 경로: \n";
        for (Node* node : path)
        {
            std::cout << "(" << node->position.x << "," << node->position.y << ") -> ";
        }
        std::cout << "도착\n";

        // 맵 출력.
        std::cout << "경로를 맵에 표시한 결과 : \n";
        aStar.DisplayGridWithPath(grid, path);
    }
    else
    {
        std::cout << "경로를 찾지 못했습니다.\n";
    }

    // 목표 노드만 제거.
    SafeDelete(goalNode);

    std::cin.get();
}