#include "AStar.h"

AStar::AStar()
{
}

AStar::~AStar()
{
    // 메모리 해제.
    while (!openList.empty())
    {
        Node* deleteNode = openList.top();
        openList.pop();
        SafeDelete(deleteNode);
    }

    for (auto& posNode : closedList)
    {
        SafeDelete(posNode.second);
    }

    closedList.clear();
}

std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, const std::vector<std::vector<int>>& grid)
{
    // 시작 지점/목표 지점 저장.
    this->startNode = startNode;
    this->goalNode = goalNode;

    // 시작 위치를 열린 리스트에 추가.
    openList.emplace(startNode);

    // 상하좌우 및 대각선 이동 방향 및 비용 계산.
    std::vector<Direction> directions =
    {
        // 하상우좌 이동.
        { 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

        // 대각선 이동.
        { 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.1414f }, { -1, -1, 1.414f }
    };

    // 이웃 노드 탐색(열린 리스트가 비어 있지 않으면 반복).
    while (!openList.empty())
    {
        // 현재 열린 리스트에서 비용(fCost)이 가장 낮은 노드를 현재 노드로 선택.
        Node* currentNode = openList.top();

        // 방문 처리를 위해 현재 노드를 열린 리스트에서 제거.
        openList.pop();

        // 방문한 노드인지 확인.
        if (closedList.find(currentNode->position) != closedList.end())
        {
            SafeDelete(currentNode);
            continue;
        }

        // 방문 처리를 위해 닫힌 리스트에 추가.
        closedList.emplace(currentNode->position, currentNode);

        // 현재 노드가 목표 노드인지 확인.
        if (IsDestination(currentNode))
        {
            // 목표 지점으로부터 역추적해서 경로를 생성 후 반환.
            return ConstructPath(currentNode);
        }

        // 이웃 노드 방문 (하상우좌 .. 차례로 방문).
        for (const Direction& direction : directions)
        {
            // 다음에 이동할 위치 확인.
            int newX = currentNode->position.x + direction.x;
            int newY = currentNode->position.y + direction.y;

            // 그리드 벗어나면 무시.
            if (!IsInRange(newX, newY, grid))
            {
                continue;
            }

            // 이동할 노드가 이동 가능한지 확인.
            if (grid[newY][newX] == 1)
            {
                continue;
            }

            // 방문한 노드인지 확인. - 없어도 되지만 처리해도 좋음.
            if (closedList.find({ newX , newY }) != closedList.end())
            {
                continue;
            }

            // 방문할 노드 생성(비용 계산).
            Node* neighborNode = new Node(newX, newY, currentNode);
            neighborNode->gCost = currentNode->gCost + direction.cost;
            neighborNode->hCost = CaculateHeuristic(neighborNode, goalNode);
            neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

            // 열린 리스트에 추가.
            openList.emplace(neighborNode);
        }
    }

    // 탐색 실패.
    // initializer_list (c++).
    //return {};
    return std::vector<Node*>();
}

void AStar::DisplayGridWithPath(std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
    // 경로에 있는 위치는 2로 표기.
    for (const Node* node : path)
    {
        grid[node->position.y][node->position.x] = 2;
    }

    // 맵 출력.
    for (int y = 0; y < (int)grid.size(); ++y)
    {
        for (int x = 0; x < (int)grid[0].size(); ++x)
        {
            // 장애물.
            if (grid[y][x] == 1)
            {
                std::cout << "1 ";
            }
            // 경로.
            else if (grid[y][x] == 2)
            {
                std::cout << "+ ";
            }
            // 맵.
            else if (grid[y][x] == 0)
            {
                std::cout << "0 ";
            }
        }
        std::cout << "\n";
    }
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
    // 목표 노드로부터 부모 노드를 따라 역추적하면서 경로 설정.
    std::vector<Node*> path;
    Node* currentNode = goalNode;
    while (currentNode != nullptr)
    {
        path.emplace_back(currentNode);
        currentNode = currentNode->parent;
    }

    // 시작 지점부터 목표 지점으로 향하도록 배열 뒤집기.
    std::reverse(path.begin(), path.end());
    return path;
}

float AStar::CaculateHeuristic(Node* currentNode, Node* goalNode)
{
    // 현재 노드에서 목표 노드까지의 차이 계산.
    Position diff = *currentNode - *goalNode;
    return std::sqrtf(diff.x * diff.x + diff.y * diff.y);
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
    // 벗어난 경우인지 확인.
    if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size())
    {
        return false;
    }

    return true;
}

bool AStar::IsDestination(const Node* node)
{
    return *node == *goalNode;
}
