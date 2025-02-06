#include <iostream>

void SelectionSort(int* array, int length)
{
    for (int ix = 0; ix < length - 1; ++ix)
    {
        // 최소값 저장할 변수.
        int minIndex = ix;
        {
            for (int jx = ix + 1; jx < length; ++jx)
            {
                // 비교.
                if (array[jx] < array[minIndex])
                {
                    minIndex = jx;
                }
            }
        }

        // 값 바꾸기.
        std::swap<int>(array[ix], array[minIndex]);
    }
}

// 출력 함수.
void PrintArray(int* array, int length)
{
    for (int ix = 0; ix < length; ++ix)
    {
        std::cout << array[ix] << " ";
    }

    std::cout << "\n";
}

int main()
{
    // 자료 집합.
    int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

    // 배열 길이.
    int length = sizeof(array) / sizeof(int);

    // 출력.
    std::cout << "정렬 전: ";
    PrintArray(array, length);

    // 정렬.
    SelectionSort(array, length);

    // 출력.
    std::cout << "정렬 후: ";
    PrintArray(array, length);

    std::cin.get();
}