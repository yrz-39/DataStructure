# 个人实验1相关说明

**该实验基于课本上数据结构的前三章内容，包括线性表的四个基本实现：**
- 顺序表，链表，栈，队列


## 1.主题：线性表
- 大概结构：
    - 以最基本的LinearList为抽象类模板，顺序表，链表以此为基础，然后实现栈和队列的模板
    - 分别实现顺序表(SeqList),链表(LinkList),栈(MyStack),队列(MyQueue)以及相关变体,如优先级队列
    - 然后学习C++ STL中的stack,queue和其变体,并将其和我自己实现的做比较
    - 结合课本上的实例应用深化对数据结构的理解
    - 进行洛谷,Leetcode实战训练

## 2.当前阶段
- 7.19 当前还在工程初始化阶段，仅完成 CMake 的简单配置。
- 7.21 完成最基本断言调试，成功运行 CTest，写出模板 `LinearList<T>`。
- 7.22—7.23 完成动态数组顺序表 `ArrayList<T>`：基本线性表接口、几何扩容、`push_back`、`clear` 与 Rule of Five。
- 下一步：在新的对话中进入单链表 `SinglyLinkedList<T>`。

## 3.工具链
- 该实验以 C++20 / CMake / CTest 为基础。

## 4.原则
- 实验先写失败测试，再完成最小实现。

## 5. GitHub 提交记录

### 2026-07-23 — `feat(lab1): complete ArrayList<T>`

对比范围：`3ad8292` → 本次提交。

#### 本次实现内容

- 完成 `ds/linear_list.hpp`：定义 `LinearList<T>` 的长度、判空、访问、修改、插入、删除与查找接口。
- 完成 `ds/array_list.hpp` 中的 `ArrayList<T>`：动态数组表示、几何扩容、中间插入右移、中间删除左移、`find`、`push_back`、`clear`。
- 实现析构、复制构造、复制赋值、移动构造、移动赋值，练习动态资源所有权、深拷贝、右值引用与 `noexcept`。
- 建立 CMake + CTest + `assert` 的基础测试闭环；测试覆盖空表、扩容、插入、删除、查找、复制、移动与清空后复用。

#### 验证

- 使用 Debug 配置执行 `cmake --build build` 与 `ctest --test-dir build --output-on-failure`。
- 提交前现有 2 项 CTest 均通过。

#### 后续验收项

- 与 `std::vector<int>` 的随机差分测试暂缓至后续收束阶段。
- 复制赋值的强异常安全顺序将在后续重构中继续完善。