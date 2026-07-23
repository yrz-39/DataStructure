#include "ds/array_list.hpp"
#include <cassert>
#include <utility>

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

    // find 检测
    assert(arr1.find(10) == 0);
    assert(arr1.find(30) == 2);
    assert(arr1.find(50) == 4);
    assert(arr1.find(999) == arr1.size());

    arr1.insert(arr1.size(), 30);
    assert(arr1.find(30) == 2); // arr1 : 10 20 30 40 50 30

    // push_back检测
    ArrayList<int> arr2;
    arr2.push_back(10);
    arr2.push_back(20);
    arr2.push_back(30);
    assert(arr2.size() == 3);
    assert(arr2.at(0) == 10);
    assert(arr2.at(1) == 20);
    assert(arr2.at(2) == 30);

    // 拷贝构造函数检测
    // 1. 空顺序表的拷贝
    ArrayList<int> arr3(arr2); // arr2: 10, 20, 30
    assert(arr3.size() == 3);
    assert(!arr3.empty());
    assert(arr3.at(0) == 10);
    assert(arr3.at(1) == 20);
    assert(arr3.at(2) == 30);

    // 2. 深拷贝验证：修改原表不影响副本
    arr2.set(1, 999); // arr2: 10, 999, 30
    assert(arr2.at(1) == 999);
    assert(arr3.at(1) == 20); // 副本不受影响

    arr2.erase(0); // arr2: 999, 30
    assert(arr2.size() == 2);
    assert(arr3.size() == 3); // 副本 size 不变

    arr2.insert(0, 555); // arr2: 555, 999, 30
    assert(arr2.at(0) == 555);
    assert(arr3.at(0) == 10); // 副本首元素不变

    // 3. 空表拷贝
    ArrayList<int> empty_arr;
    ArrayList<int> empty_copy(empty_arr);
    assert(empty_copy.empty());
    assert(empty_copy.size() == 0);

    // 4. 从空拷贝构造后再独立操作
    empty_copy.push_back(100);
    assert(empty_copy.size() == 1);
    assert(empty_copy.at(0) == 100);
    assert(empty_arr.empty()); // 原空表仍为空

    // 5. 拷贝后 find 验证
    assert(arr3.find(10) == 0);
    assert(arr3.find(20) == 1);
    assert(arr3.find(30) == 2);
    assert(arr3.find(999) == arr3.size()); // 999 不在副本中

    // = 运算符重载检测
    // 1. 非空赋给空
    ArrayList<int> arr4;
    arr4 = arr1; // arr1: 10, 20, 30, 40, 50, 30 (6元素)
    assert(arr4.size() == 6);
    assert(arr4.at(0) == 10);
    assert(arr4.at(1) == 20);
    assert(arr4.at(2) == 30);
    assert(arr4.at(3) == 40);
    assert(arr4.at(4) == 50);
    assert(arr4.at(5) == 30);

    // 2. 非空赋给非空（覆盖原有数据）
    ArrayList<int> arr5;
    arr5.push_back(1);
    arr5.push_back(2); // arr5: 1, 2
    arr5 = arr2;       // arr2: 555, 999, 30
    assert(arr5.size() == 3);
    assert(arr5.at(0) == 555);
    assert(arr5.at(1) == 999);
    assert(arr5.at(2) == 30);

    // 3. 深拷贝验证：修改原表不影响赋值后的副本
    arr2.set(0, 777); // arr2: 777, 999, 30
    assert(arr2.at(0) == 777);
    assert(arr5.at(0) == 555); // 副本不受影响

    arr2.erase(1); // arr2: 777, 30
    assert(arr2.size() == 2);
    assert(arr5.size() == 3); // 副本 size 不变

    // 4. 自赋值检测
    arr5 = arr5; // 自赋值不应崩溃
    assert(arr5.size() == 3);
    assert(arr5.at(0) == 555);
    assert(arr5.at(1) == 999);
    assert(arr5.at(2) == 30);

    // 5. 空表赋给非空表
    ArrayList<int> arr6;
    arr6 = empty_arr; // 空表覆盖非空表
    assert(arr6.empty());
    assert(arr6.size() == 0);

    // 6. 赋值后 find 验证
    assert(arr4.find(10) == 0);
    assert(arr4.find(30) == 2); // 找第一个出现的 30
    assert(arr4.find(50) == 4);
    assert(arr4.find(999) == arr4.size());

    // 7. 链式赋值
    ArrayList<int> arr7, arr8;
    arr8 = arr7 = arr3; // arr3: 10, 20, 30
    assert(arr7.size() == 3);
    assert(arr7.at(0) == 10);
    assert(arr7.at(1) == 20);
    assert(arr7.at(2) == 30);
    assert(arr8.size() == 3);
    assert(arr8.at(0) == 10);
    assert(arr8.at(1) == 20);
    assert(arr8.at(2) == 30);

    // 移动构造函数检测
    // 1. 从非空表移动构造
    ArrayList<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);                   // src: 1, 2, 3
    ArrayList<int> dst(std::move(src)); // 移动构造
    assert(dst.size() == 3);
    assert(!dst.empty());
    assert(dst.at(0) == 1);
    assert(dst.at(1) == 2);
    assert(dst.at(2) == 3);

    // 2. 移动后源对象变为空（仍可安全使用）
    assert(src.empty());
    assert(src.size() == 0);

    // 3. 被移走资源的对象仍可正常复用
    src.push_back(100);
    src.push_back(200);
    assert(src.size() == 2);
    assert(src.at(0) == 100);
    assert(src.at(1) == 200);

    // 4. 空表移动构造
    ArrayList<int> empty_src;
    ArrayList<int> empty_dst(std::move(empty_src));
    assert(empty_dst.empty());
    assert(empty_dst.size() == 0);
    assert(empty_src.empty()); // 源仍为空

    // 5. 从临时对象移动构造
    ArrayList<int> arr_from_temp(ArrayList<int>{});
    assert(arr_from_temp.empty());

    // 6. 深拷贝 vs 移动对比：移动后原表不影响新表（因为资源已转移）
    ArrayList<int> big;
    for (int i = 0; i < 100; ++i) {
        big.push_back(i);
    }
    assert(big.size() == 100);
    ArrayList<int> stolen(std::move(big));
    assert(stolen.size() == 100);
    assert(stolen.at(0) == 0);
    assert(stolen.at(99) == 99);
    assert(big.empty()); // 资源已被偷走
    assert(big.size() == 0);

    // 7. 移动后 find 验证
    assert(stolen.find(0) == 0);
    assert(stolen.find(50) == 50);
    assert(stolen.find(99) == 99);
    assert(stolen.find(999) == stolen.size());

    // 移动赋值运算符检测
    // 1. 非空表移动赋值给空表
    ArrayList<int> src1;
    src1.push_back(10);
    src1.push_back(20);
    src1.push_back(30); // src1: 10, 20, 30
    ArrayList<int> dst1;
    dst1 = std::move(src1);
    assert(dst1.size() == 3);
    assert(dst1.at(0) == 10);
    assert(dst1.at(1) == 20);
    assert(dst1.at(2) == 30);
    assert(src1.empty()); // 源被掏空
    assert(src1.size() == 0);

    // 2. 非空表移动赋值给非空表（覆盖旧数据）
    ArrayList<int> dst2;
    dst2.push_back(1); // dst2: 1
    ArrayList<int> src2;
    src2.push_back(100);
    src2.push_back(200); // src2: 100, 200
    dst2 = std::move(src2);
    assert(dst2.size() == 2);
    assert(dst2.at(0) == 100);
    assert(dst2.at(1) == 200);
    assert(src2.empty());

    // 3. 自移动赋值
    ArrayList<int>& dst2_self = dst2;
    dst2 = std::move(dst2_self); // 自移动赋值不应崩溃
    assert(dst2.size() == 2);
    assert(dst2.at(0) == 100);
    assert(dst2.at(1) == 200);

    // 4. 被掏空的源对象可复用
    src1.push_back(42);
    assert(src1.size() == 1);
    assert(src1.at(0) == 42);

    // 5. 空表移动赋值给空表
    ArrayList<int> empty_a;
    ArrayList<int> empty_b;
    empty_b = std::move(empty_a);
    assert(empty_b.empty());
    assert(empty_b.size() == 0);
    assert(empty_a.empty());

    // 6. 空表移动赋值给非空表（覆盖清空）
    ArrayList<int> dst3;
    dst3.push_back(1);
    dst3.push_back(2);
    dst3.push_back(3); // dst3: 1, 2, 3
    dst3 = std::move(empty_src);
    assert(dst3.empty());
    assert(dst3.size() == 0);

    // 7. 移动赋值后 find 验证
    assert(dst1.find(10) == 0);
    assert(dst1.find(20) == 1);
    assert(dst1.find(30) == 2);
    assert(dst1.find(999) == dst1.size());

    // clear
    ArrayList<int> arr9;
    arr9.push_back(10);
    arr9.push_back(20);
    arr9.push_back(30);
    arr9.clear();
    assert(arr9.size() == 0);
    arr9.push_back(10);
    assert(arr9.at(0)==10);
    return 0;
}