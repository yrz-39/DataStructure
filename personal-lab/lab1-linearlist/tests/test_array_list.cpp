#include "ds/array_list.hpp"
#include <cassert>

int main() {
    ArrayList<int> arr1;
    // 空顺序表检测
    assert(arr1.empty());
    assert(arr1.size() == 0);

    // 插入测试
    arr1.insert(0, 10);
    arr1.insert(1, 20);
    arr1.insert(2, 30);
    arr1.insert(3, 40);
    arr1.insert(4, 50);
    assert(!arr1.empty());
    assert(arr1.size() == 5);
    assert(arr1.at(0) == 10);
    assert(arr1.at(1) == 20);
    assert(arr1.at(2) == 30);
    assert(arr1.at(3) == 40);
    assert(arr1.at(4) == 50);
    arr1.insert(2, 25);
    assert(arr1.size() == 6);
    assert(arr1.at(0) == 10);
    assert(arr1.at(1) == 20);
    assert(arr1.at(2) == 25);
    assert(arr1.at(3) == 30);
    assert(arr1.at(4) == 40);
    assert(arr1.at(5) == 50);

    // 修改元素检测
    arr1.set(2, 100);
    assert(arr1.size() == 6);
    assert(arr1.at(2) == 100); // arr1 : 10 20 100 30 40 50

    // 删除元素检测
    int a = arr1.erase(2);
    assert(arr1.size() == 5);
    assert(a == 100);
    assert(arr1.at(0) == 10);
    assert(arr1.at(1) == 20);
    assert(arr1.at(2) == 30);
    assert(arr1.at(3) == 40);
    assert(arr1.at(4) == 50);

    //find 检测
    assert(arr1.find(10) == 0);
    assert(arr1.find(30)==2);
    assert(arr1.find(50)==4);
    assert(arr1.find(999)==arr1.size());

    arr1.insert(arr1.size(),30);
    assert(arr1.find(30) == 2); //arr1 : 10 20 30 40 50 30
    return 0;
}