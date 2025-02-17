#include <iostream>
#include <stack>
#include <vector>

// 미로 탐색에 사용할 좌표 구조체.
struct Location2D
{
    Location2D(int row = 0, int col = 0)
        : row(row), col(col)
    {
    }

    // 행.
    int row;
    // 열.
    int col;
};

// 맵 배열.
int mapSize = 0;
std::vector<std::vector<char>> map;//=
//{
//    {'1','1','1','1','1','1'},
//    {'e','0','1','0','0','1'},
//    {'1','0','0','0','1','1'},
//    {'1','0','1','0','1','1'},
//    {'1','0','1','0','0','x'},
//    {'1','1','1','1','1','1'}
//};

// 이동 가능 여부 판단 함수.
bool IsValidLocation(int row, int col)
{
    if (row < 0 || row >= mapSize || col < 0 || col >= mapSize)
    {
        return false;
    }

    return map[row][col] == '0' || map[row][col] == 'x';
}

// 시작 지점 검색 함수.
void FindStartLocation(int& row, int& col)
{
    for (int ix = 0; ix < mapSize; ++ix)
    {
        for (int jx = 0; jx < mapSize; ++jx)
        {
            // 맵 출력.
            std::cout << map[ix][jx] << " ";

            // 시작 지점을 나타내는 문자 검색.
            if (map[ix][jx] == 'e')
            {
                row = ix;
                col = jx;
                //return;
            }
        }

        std::cout << "\n";
    }
}

// 미로 탈출 함수.
void EscapeMaze()
{
    //// 맵 크기 확인.
    //mapSize = (int)map.size();

    // 위치 저장을 위한 변수 선언.
    int row = 0;
    int col = 0;

    // 탐색 시작을 위해 시작 위치 찾기.
    FindStartLocation(row, col);

    // 스택 선언.
    std::stack<Location2D> stack;

    // 탐색 시작을 위해 시작 위치 스택에 삽입.
    stack.push(Location2D(row, col));

    // 미로 탐색.
    while (!stack.empty())
    {
        // 현재 위치 반환.
        Location2D current = stack.top();
        stack.pop();

        // 값 저장.
        row = current.row;
        col = current.col;

        // 탐색 위치 출력.
        std::cout << "(" << row << "," << col << ") ";

        // 탈출 조건 확인.
        if (map[row][col] == 'x')
        {
            std::cout << " \n미로 탐색 성공\n";
            return;
        }

        // 탐색 진행.
        // 방문한 현재 위치는 재방문 방지를 위해 표시.
        map[row][col] = '.';

        // 상/하/좌/우 위치 중 이동 가능한 위치를 스택에 삽입.
        if (IsValidLocation(row - 1, col))
        {
            stack.push(Location2D(row - 1, col));
        }
        if (IsValidLocation(row + 1, col))
        {
            stack.push(Location2D(row + 1, col));
        }
        if (IsValidLocation(row, col - 1))
        {
            stack.push(Location2D(row , col - 1));
        }
        if (IsValidLocation(row, col + 1))
        {
            stack.push(Location2D(row, col + 1));
        }
    }

    std::cout << " \n미로 탐색 실패\n";
}

// 맵을 불러와 해석(파싱, Parsing).
bool ParseMap(const char* path)
{
    // 파일 열기.
    FILE* file = nullptr;
    fopen_s(&file, path, "r");
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

    // 맵 크기 설정.
    sscanf_s(buffer, "size %d", &mapSize);
    if (mapSize == 0)
    {
        fclose(file);
        return false;
    }
    
    map.reserve(mapSize);

    // 줄 데이터 저장을 위한 임시 배열 선언.
    std::vector<char> line;
    line.reserve(mapSize);

    int eCount = 0, xCount = 0;
    // 맵 데이터 해성을 위한 루프.
    while (fgets(buffer, 256, file))
    {
        // 첫 칸 처리.
        char* context = nullptr;
        char* splitString = strtok_s(buffer, ",", &context);
        if (splitString)
        {
            line.emplace_back(splitString[0]);
        }

        if (line.back() == 'e')
        {
            ++eCount;
        }
        else if (line.back() == 'x')
        {
            ++xCount;
        }

        // 둘째부터는 루프.
        while (context)
        {
            splitString = strtok_s(nullptr, ",", &context);
            if (!splitString)
            {
                break;
            }

            line.emplace_back(splitString[0]);

            if (line.back() == 'e')
            {
                ++eCount;
            }
            else if (line.back() == 'x')
            {
                ++xCount;
            }
        }

        // 처리된 라인 데이터를 맵에 추가.
        map.emplace_back(line);
        line.clear();
    }

    if (eCount != 1 || xCount != 1)
    {
        fclose(file);
        return false;
    }

    fclose(file);
    return true;
}

bool MakeMap(const char* path)
{
    std::cout << "맵의 크기를 입력해주세요.\n";
    std::cout << "맵의 크기는 한 변이 128이하인 정사각형입니다.\n";
    while (mapSize <= 0 || mapSize > 128)
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> mapSize;

        if (mapSize <= 0 || mapSize > 128)
        {
            std::cout << "다시 입력해주세요.\n";
        }
    }

    map.assign(mapSize, std::vector<char>(mapSize, '1'));

    std::cout << "맵 데이터를 입력해주세요.\n";
    std::cout << "띄워쓰기로 열을 구분하고 줄바꿈으로 행을 구분해주세요.\n";
    std::cout << "e는 시작점, x는 도착점입니다.\n";
    std::cout << "0는 이동 가능한 길, 나머지 문자는 벽입니다.\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    char input;
    int eCount = 0, xCount = 0;
    for (int ix = 0; ix < mapSize; ++ix)
    {
        for (int jx = 0; jx < mapSize; ++jx)
        {
            std::cin >> input;

            if (input == 'e' || input == 'x' || input == '0')
            {
                map[ix][jx] = input;

                if (input == 'e')
                {
                    ++eCount;
                }

                if (input == 'x')
                {
                    ++xCount;
                }
            }
        }
    }

    if (eCount != 1 || xCount != 1)
    {
        return false;
    }

    // 파일 열기.
    FILE* file = nullptr;
    fopen_s(&file, path, "w");

    if (file == nullptr)
    {
        return false;
    }

    char buffer[257] = { };
    sprintf_s(buffer, "size %d\n", mapSize);
    fputs(buffer, file);

    for (int ix = 0; ix < mapSize; ++ix)
    {
        for (int jx = 0; jx < mapSize; ++jx)
        {
            buffer[jx * 2] = map[ix][jx];

            if (jx != mapSize - 1)
            {
                buffer[jx * 2 + 1] = ',';
                continue;
            }
            
            buffer[jx * 2 + 1] = '\n';
            buffer[jx * 2 + 2] = '\0';
        }

        fputs(buffer, file);
    }

    fclose(file);

    return true;
}

int main()
{
    int input;
    bool isValid = false;
    while (!isValid)
    {
        map.clear();
        std::cout << "0: 맵 만들기, 1: 파일 불러오기\n";
        std::cin >> input;

        system("cls");
        if (input == 0)
        {
            isValid = MakeMap("../Assets/DFSMap.txt");
            if (isValid)
            {
                break;
            }

            system("cls");
            std::cout << "맵 생성에 실패했습니다.\n";
        }
        else if (input == 1)
        {
            isValid = ParseMap("../Assets/DFSMap.txt");
            if (isValid)
            {
                break;
            }
            
            std::cout << "맵 로딩에 실패했습니다.\n";
        }
        else
        {
            std::cout << "잘못된 입력입니다.\n";
        }

        std::cout << "다시 입력해주세요\n";
    }

    system("cls");

    // 미로 탐색.
    EscapeMaze();

    std::cin.get();
}