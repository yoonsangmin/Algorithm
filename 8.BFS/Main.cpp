#include <iostream>
#include <queue>
#include <string>
#include <cassert>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// 미로 탐색 예제.
// 위치 구조체.
struct Location
{
    Location(int row = 0, int col = 0)
        : row(row), col(col)
    {
    }

    int& operator[](size_t index)
    {
        if (index == 0)
        {
            return row;
        }
        else if (index == 1)
        {
            return col;
        }

        assert(index == 0 || index == 1);
    }

    int row;
    int col;
};

// 맵 선언.
int mazeSize = 6;
char startMark = 'e';
char destinationMark = 'x';
std::vector<std::vector<char>> map;// =
//{
//    {'1','1','1','1','1','1'},
//    {'e','0','1','0','0','1'},
//    {'1','0','0','0','1','1'},
//    {'1','0','1','0','1','1'},
//    {'1','0','1','0','0','x'},
//    {'1','1','1','1','1','1'}
//};

// 이동하려는 위치가 이동 가능한 위치인지 확인하는 함수.
bool IsValid(int row, int col)
{
    // Out of index 검사.
    if (row < 0 || row >= mazeSize || col < 0 || col >= mazeSize)
    {
        return false;
    }

    return map[row][col] == '0' || map[row][col] == destinationMark;
}

// 맵 출력 및 시작 위치 검색 함수.
void FindStartLocation(int& row, int& col)
{
    // 행.
    for (int ix = 0; ix < mazeSize; ++ix)
    {
        // 열.
        for (int jx = 0; jx < mazeSize; ++jx)
        {
            // 시작 위치를 찾았으면 전달한 파라미터에 출력.
            if (map[ix][jx] == startMark)
            {
                row = ix;
                col = jx;
            }

            // 맵 출력.
            std::cout << map[ix][jx] << " ";
        }

        // 개행.
        std::cout << "\n";
    }
}

void EscapeMaze()
{
    // 시작 위치.
    int row = 0;
    int col = 0;
    FindStartLocation(row, col);

    // 탐색에 사용할 큐 선언.
    std::queue<Location> queue;
    
    // 시작 위치 추가.
    queue.emplace(Location(row, col));

    // 탐색.
    while (!queue.empty())
    {
        // 큐에서 가장 앞에 위치한 데이터를 추출.
        Location current = queue.front();
        queue.pop();

        // 편의를 위해 값 저장.
        //row = current.row;
        //col = current.col;
        row = current[0];
        col = current[1];

        // 탐색한 위치 출력.
        std::cout << "(" << row << "," << col << ") ";

        // 탈출 조건 (목표 지점에 도달한 경우).
        if (map[row][col] == destinationMark)
        {
            std::cout << "\n미로 탐색 성공\n";
            return;
        }

        // 방문한 위치를 다른 문자로 설정.
        map[row][col] = '.';
        
        // 탐색할 위치를 큐에 넣기.
        // 상/하/좌/우.
        if (IsValid(row - 1, col))
        {
            queue.emplace(Location(row - 1, col));
        }
        if (IsValid(row + 1, col))
        {
            queue.emplace(Location(row + 1, col));
        }
        if (IsValid(row, col - 1))
        {
            queue.emplace(Location(row, col - 1));
        }
        if (IsValid(row, col + 1))
        {
            queue.emplace(Location(row, col + 1));
        }
    }

    // 탐색 실패.
    std::cout << "\n미로 탐색 실패\n";
}

// 맵 파일을 열어 필요한 정보를 설정하는 함수.
bool ParseMap(const char* path, char& startMark, char& destinationMark)
{
    // 파일 열기.
    FILE* file = nullptr;
    fopen_s(&file, path, "rb");
    if (file == nullptr)
    {
        return false;
    }

    // 첫 줄 읽기.
    char buffer[256] = { };
    if (!fgets(buffer, 256, file))
    {
        fclose(file);
        return false;
    }

    // 맵 데이터 정리.
    map.clear();

    // 맵 크기 설정 및 시작/목적 지점 문자 설정.
    sscanf_s(buffer, "size: %d start: %c destination: %c", &mazeSize, &startMark, 1, &destinationMark, 1);
    if (mazeSize == 0)
    {
        fclose(file);
        return false;
    }

    map.reserve(mazeSize);

    // 줄 데이터 저장을 위한 임시 배열 선언.
    //std::vector<std::string> lines;
    std::vector<char*> lines;
    lines.reserve(mazeSize);

    // 첫 줄을 제외한 나머지 데이터를 한 번에 읽기.
    // 파일의 현재 위치.
    auto currentPosition = ftell(file);

    // 마지막 위치로 이동.
    fseek(file, 0, SEEK_END);

    // 위치 저장.
    auto endPosition = ftell(file);

    // 크기 계산.
    int size = (int)(endPosition - currentPosition);

    // rewind.
    fseek(file, currentPosition, SEEK_SET);

    // 동적 할당.
    char* mapBuffer = new char[size + 1];

    // 나머지 읽기.
    //if (!fread_s(buffer, 2048, mazeSize * 2 * mazeSize - 1, 1, file))
    if (!fread_s(mapBuffer, size, size, 1, file))
    {
        fclose(file);
        return false;
    }
    
    mapBuffer[size] = '\0';

    // 라인 파싱.
    char* context = nullptr;
    char* splitString = strtok_s(mapBuffer, "\n", &context);

    while (splitString != nullptr)
    {
        lines.emplace_back(splitString);
        splitString = strtok_s(nullptr, "\n", &context);
    }

    // 라인별 파싱 데이터 저장.
    std::vector<char> line;
    line.reserve(mazeSize);

    // 재사용을 위한 null 설정.
    splitString = nullptr;

    // 맵 검증을 위한 변수.
    int startCount = 0;
    int destinationCount = 0;

    // 라인 배열을 순회하면서 파싱 처리.
    for (auto& item : lines)
    {
        // 재사용을 위한 정리.
        context = nullptr;

        // 첫 칸 처리.
        //splitString = strtok_s(const_cast<char*>(item.c_str()), ",", &context);
        splitString = strtok_s(item, ",", &context);

        // 두 번째 칸부터는 루프.
        while (splitString != nullptr)
        {
            line.emplace_back(splitString[0]);

            if (line.back() == startMark)
            {
                ++startCount;
            }
            else if (line.back() == destinationMark)
            {
                ++destinationCount;
            }

            splitString = strtok_s(nullptr, ",", &context);
        }
        
        // 처리된 라인 데이터 맵에 추가.
        map.emplace_back(line);
        line.clear();
    }

    // 정리.
    delete[] mapBuffer;

    if (startCount != 1 || destinationCount != 1)
    {
        fclose(file);
        return false;
    }

    //std::vector<char> line;
    //line.reserve(mazeSize);

    //for (int ix = 0; ix < mazeSize; ++ix)
    //{
    //    for (int jx = 0; jx < mazeSize; ++jx)
    //    {
    //        line.push_back(buffer[ix * mazeSize * 2 + jx * 2]);
    
    //        if (line.back() == startMark)
    //        {
    //            ++startCount;
    //        }
    //        else if (line.back() == destinationMark)
    //        {
    //            ++destinationCount;
    //        }
    //    }
    //    map.emplace_back(line);
    //    line.clear();
    //}

    //if (startCount != 1 || destinationCount != 1)
    //{
    //    fclose(file);
    //    return false;
    //}

    // 파일 닫기.
    fclose(file);
    return true;
}

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // 미로 탐색 데모.
    // 맵 파일 해석.
    if (ParseMap("../Assets/BFSMap.txt", startMark, destinationMark))
    {
        // 미로 탐색 진행.
        EscapeMaze();
    }
    else
    {
        std::cout << "맵 로딩에 실패했습니다.\n";
    }

    std::cin.get();
}