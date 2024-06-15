#include <iostream>
#include <vector>
#include <thread>


class MergeSort {
public:
    void sort(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int middle = left + (right - left) / 2;

            // Создаем два потока для сортировки левой и правой половины массива
            std::thread leftThread(&MergeSort::sort, this, std::ref(arr), left, middle);
            std::thread rightThread(&MergeSort::sort, this, std::ref(arr), middle + 1, right);

            // Дожидаемся завершения сортировки в дочерних потоках
            leftThread.join();
            rightThread.join();

            // Объединяем отсортированные половины массива
            merge(arr, left, middle, right);
        }
    }

private:
    void merge(std::vector<int>& arr, int left, int middle, int right) {
        int leftSize = middle - left + 1;
        int rightSize = right - middle;

        std::vector<int> leftArr(leftSize), rightArr(rightSize);

        for (int i = 0; i < leftSize; i++)
            leftArr[i] = arr[left + i];
        for (int j = 0; j < rightSize; j++)
            rightArr[j] = arr[middle + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < leftSize && j < rightSize) {
            if (leftArr[i] <= rightArr[j]) {
                arr[k] = leftArr[i];
                i++;
            }
            else {
                arr[k] = rightArr[j];
                j++;
            }
            k++;
        }

        while (i < leftSize) {
            arr[k] = leftArr[i];
            i++;
            k++;
        }

        while (j < rightSize) {
            arr[k] = rightArr[j];
            j++;
            k++;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    std::vector<int> arr(10);
    std::cout << "Введите 10 целых чисел: ";
    for (int i = 0; i < 10; i++)
        std::cin >> arr[i];

    MergeSort mergeSort;

    // Создаем поток для сортировки массива
    std::thread mergeSortThread(&MergeSort::sort, &mergeSort, std::ref(arr), 0, arr.size() - 1);

    // Дожидаемся завершения сортировки в дочернем потоке
    mergeSortThread.join();

    std::cout << "Сортированный массив: ";
    for (int i = 0; i < 10; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;

    return 0;
}
