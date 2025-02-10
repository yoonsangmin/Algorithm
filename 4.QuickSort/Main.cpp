#include <iostream>

// 피벗(pivot) 선택 함수.
int Partition(int* array, int left, int right)
{
    // 피벗 선택.
    // 3개 이상의 값에서 중간 값을 피벗으로 설정한다면 첫 번째 값(array[left])과 스왑.
    int first = left;
    int pivot = array[first];

    // 다음 위치로 이동.
    ++left;

    // 두 인덱스가 서로 교차할 때까지 진행.
    // left == right 도 고려해야 함 - 길이가 2인 파티션인 경우.
    while (left <= right)
    {
        // left는 pivot보다 큰 값 검색.
        while (array[left] <= pivot)
        {
            ++left;
        }

        // right는 pivot보다 작은 값 검색.
        while (array[right] > pivot)
        {
            --right;
        }

        // left와 right가 교차하지 않았을 때만 값 교환.
        if (left >= right)
        {
            break;
        }

        std::swap(array[left], array[right]);

        //if (left < right)
        //{
        //    std::swap(array[left], array[right]);
        //}
        //else
        //{
        //    break;
        //}
    }

    // 교환.
    // 왼쪽 배열의 마지막 위치 - 교차가 됐기 때문에.
    std::swap(array[first], array[right]);

    // 피벗 반환.
    return right;
}

// 퀵 정렬 함수.
void QuickSort(int* array, int left, int right)
{
    // 탈출 조건.
    if (left >= right) // || left < 0 || right >= length
    {
        return;
    }

    // 분할.
    int partition = Partition(array, left, right);

    // 왼쪽 배열 퀵 정렬.
    QuickSort(array, left, partition - 1); 

    // 오른쪽 배열 퀵 정렬.
    QuickSort(array, partition + 1, right);
}

void PrintArray(int array[], int length)
{
    for (int ix = 0; ix < length; ++ix)
    {
        std::cout << array[ix] << (ix < length - 1 ? ", " : "");
    }

    std::cout << "\n";
}

// 메인 함수(진입점).
int main()
{
    //int array[] = { 10, 7, 8, 9, 1, 5 };
    //int array[] = { 18, 19, 21, 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16, 11, 25, 30 };
    int array[] = { 18, 19, 21, 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16, 11, 25, 30, 18, 18, 18, 18, 18, 18 };


    // 크기.
    //int length = sizeof(array) / sizeof(int);
    int length = _countof(array);

    std::cout << "정렬 전: ";
    PrintArray(array, length);

    // 정렬.
    QuickSort(array, 0, length - 1);

    std::cout << "정렬 후: ";
    PrintArray(array, length);

    std::cin.get();
}