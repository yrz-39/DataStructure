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
- 7.24—8.3 完成单链表 `SinglyLinkedList<T>`：`head_`/`tail_`/`size_` 链式表示、`LinearList<T>` 全部抽象接口、`push_back`、`clear`、`copy_from` 复用与完整 Rule of Five。
- 8.5 完成双向链表 `DoublyLinkedList<T>`：以 `prev`/`next` 双向链接维护首尾节点，支持从较近端访问元素。
- 下一步：补齐 `push_front()` 与 `reverse()`，并在线性表收束阶段完成随机差分测试与异常安全改进。

## 3.工具链
- 该实验以 C++20 / CMake / CTest 为基础。

## 4.原则
- 实验先写失败测试，再完成最小实现。

## 5. GitHub 提交记录

### 2026-08-05 — `feat(lab1): implement DoublyLinkedList<T> linked list`

对比范围：`3bc5155` → 本次提交。

#### 本次实现内容

- 完成 `ds/doubly_linked_list.hpp` 中的 `DoublyLinkedList<T>`：私有嵌套 `Node` 同时维护 `prev` 与 `next`，并以 `head_`/`tail_`/`size_` 保存链表状态。
- 实现 `LinearList<T>` 全部抽象接口、`push_back()`、`clear()` 与 `copy_from()`；`at()` 会根据索引位置从头或尾择近遍历。
- 实现 Rule of Five（析构、复制构造、复制赋值、移动构造、移动赋值），含自赋值与自移动保护、移动后源对象复用。
- 在 `CMakeLists.txt` 注册 `test_doubly_linked_list`；同步删除单链表 `copy_from()` 中遗留的无效注释。

#### 验证

- 使用 Debug 配置执行 `cmake --build build` 与 `ctest --test-dir build --output-on-failure`，4/4 通过（`ds_tests`、`test_array_list`、`test_singly_linked_list`、`test_doubly_linked_list`）。
- 双向链表测试覆盖空表、头/中/尾插删、单节点删除与复用、尾删后复用、反向访问路径、越界异常、const 访问、查找、深拷贝、复制赋值、移动语义、清空后复用及 100 节点规模。

#### 后续验收项

- 与顺序表、单链表共同保留的 `erase()` 默认构造限制、`copy_from()` 强异常安全，以及随机差分测试，在线性表实现收束时统一处理。
- `push_front()` 与 `reverse()` 尚未实现，待三个线性表实现完成后统一补齐并比较实现差异。

### 2026-08-03 — `feat(lab1): implement SinglyLinkedList<T> linked list`

对比范围：`92194af` → 本次提交。

#### 本次实现内容

- 完成 `ds/singly_linked_list.hpp` 中的 `SinglyLinkedList<T>`：私有嵌套 `Node`、`head_`/`tail_`/`size_` 表示、`LinearList<T>` 全部抽象接口（`size`/`empty`/`at`/`set`/`insert`/`erase`/`find`）。
- 实现 `push_back`、`clear`，并抽出私有 `copy_from()` 供拷贝构造与复制赋值共用。
- 实现完整 Rule of Five（析构、复制构造、复制赋值、移动构造、移动赋值），含自赋值保护与 `noexcept`。
- 在 `CMakeLists.txt` 注册 `test_singly_linked_list` 测试目标；测试覆盖空表、头尾与中间插删、单节点删除后复用、`erase` 返回值、深拷贝互不影响、自赋值/链式赋值、移动后源对象复用、`clear` 后复用、100 节点规模。

#### 验证

- `cmake --build build` 零警告零错误；`ctest --test-dir build --output-on-failure` 3/3 通过（`ds_tests`、`test_array_list`、`test_singly_linked_list`）。

#### 后续验收项

- 与 `std::list`/`std::vector` 的随机差分测试暂缓至线性表收束阶段。
- `reverse()` 与 `push_front()` 尚未实现，待双向链表完成后一并补齐。
- `erase()` 中 `T value;` 要求 `T` 可默认构造（已用非默认构造类型探针复现）；后续改为 `T value = head_->value;` 或分支内直接初始化，以支持任意可拷贝类型。
- `copy_from` 在 `new` 抛异常时的强异常安全保证，与顺序表复制赋值同批处理。

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