#include <iostream>
#include <vector>

void SelectionSort(std::vector<int> &arr) {
    int length = arr.size();
    for (int i = 0; i < length; i++) {
        int currentminindex = i;

        for (int j = i + 1; j < length; j++) {
            if (arr[j] < arr[currentminindex]) {
                currentminindex = j;
            }
        }
        if (currentminindex != i) {
            int temp = arr[i];
            arr[i] = arr[currentminindex];
            arr[currentminindex] = temp;
        }
    }
}
int main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    SelectionSort(arr);

    for (int num : arr) {
        std::cout << num << " ";
    }
    system("pause");
    return 0;
}