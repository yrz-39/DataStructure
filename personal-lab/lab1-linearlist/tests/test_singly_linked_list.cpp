#include "ds/singly_linked_list.hpp"
#include <cassert>
#include <utility>

int main() {
    SinglyLinkedList<int> list1;
    // Empty-list checks.
    assert(list1.empty());
    assert(list1.size() == 0);

    // Insert, access, update, erase, and find checks.
    list1.insert(0, 10);
    list1.insert(1, 20);
    list1.insert(2, 30);
    list1.insert(3, 40);
    list1.insert(4, 50);
    assert(!list1.empty());
    assert(list1.size() == 5);
    assert(list1.at(0) == 10);
    assert(list1.at(1) == 20);
    assert(list1.at(2) == 30);
    assert(list1.at(3) == 40);
    assert(list1.at(4) == 50);

    list1.insert(2, 25);
    assert(list1.size() == 6);
    assert(list1.at(0) == 10);
    assert(list1.at(1) == 20);
    assert(list1.at(2) == 25);
    assert(list1.at(3) == 30);
    assert(list1.at(4) == 40);
    assert(list1.at(5) == 50);

    list1.set(2, 100);
    assert(list1.size() == 6);
    assert(list1.at(2) == 100);

    const int erased = list1.erase(2);
    assert(erased == 100);
    assert(list1.size() == 5);
    assert(list1.at(0) == 10);
    assert(list1.at(1) == 20);
    assert(list1.at(2) == 30);
    assert(list1.at(3) == 40);
    assert(list1.at(4) == 50);

    assert(list1.find(10) == 0);
    assert(list1.find(30) == 2);
    assert(list1.find(50) == 4);
    assert(list1.find(999) == list1.size());
    list1.insert(list1.size(), 30);
    assert(list1.find(30) == 2);

    // push_back checks.
    SinglyLinkedList<int> list2;
    list2.push_back(10);
    list2.push_back(20);
    list2.push_back(30);
    assert(list2.size() == 3);
    assert(list2.at(0) == 10);
    assert(list2.at(1) == 20);
    assert(list2.at(2) == 30);

    // Copy construction and deep-copy checks.
    SinglyLinkedList<int> list3(list2);
    assert(list3.size() == 3);
    assert(!list3.empty());
    assert(list3.at(0) == 10);
    assert(list3.at(1) == 20);
    assert(list3.at(2) == 30);
    list2.set(1, 999);
    list2.erase(0);
    list2.insert(0, 555);
    assert(list2.size() == 3);
    assert(list2.at(0) == 555);
    assert(list3.size() == 3);
    assert(list3.at(0) == 10);
    assert(list3.at(1) == 20);
    assert(list3.find(999) == list3.size());

    SinglyLinkedList<int> empty_list;
    SinglyLinkedList<int> empty_copy(empty_list);
    assert(empty_copy.empty());
    empty_copy.push_back(100);
    assert(empty_copy.size() == 1);
    assert(empty_copy.at(0) == 100);
    assert(empty_list.empty());

    // Copy assignment, including self-assignment and chained assignment.
    SinglyLinkedList<int> list4;
    list4 = list1;
    assert(list4.size() == 6);
    assert(list4.at(0) == 10);
    assert(list4.at(5) == 30);

    SinglyLinkedList<int> list5;
    list5.push_back(1);
    list5.push_back(2);
    list5 = list2;
    assert(list5.size() == 3);
    assert(list5.at(0) == 555);
    assert(list5.at(1) == 999);
    assert(list5.at(2) == 30);
    list2.set(0, 777);
    list2.erase(1);
    assert(list2.size() == 2);
    assert(list5.size() == 3);
    assert(list5.at(0) == 555);

    list5 = list5;
    assert(list5.size() == 3);
    assert(list5.at(1) == 999);
    SinglyLinkedList<int> list6;
    list6.push_back(1);
    list6 = empty_list;
    assert(list6.empty());

    SinglyLinkedList<int> list7;
    SinglyLinkedList<int> list8;
    list8 = list7 = list3;
    assert(list7.size() == 3 && list8.size() == 3);
    assert(list7.at(0) == 10 && list8.at(2) == 30);

    // Move construction and reuse of moved-from lists.
    SinglyLinkedList<int> source;
    source.push_back(1);
    source.push_back(2);
    source.push_back(3);
    SinglyLinkedList<int> destination(std::move(source));
    assert(destination.size() == 3);
    assert(destination.at(0) == 1);
    assert(destination.at(2) == 3);
    assert(source.empty());
    source.push_back(100);
    source.push_back(200);
    assert(source.size() == 2);
    assert(source.at(0) == 100);

    SinglyLinkedList<int> empty_source;
    SinglyLinkedList<int> empty_destination(std::move(empty_source));
    assert(empty_destination.empty());
    assert(empty_source.empty());
    SinglyLinkedList<int> from_temporary(SinglyLinkedList<int>{});
    assert(from_temporary.empty());

    SinglyLinkedList<int> big;
    for (int i = 0; i < 100; ++i) {
        big.push_back(i);
    }
    SinglyLinkedList<int> stolen(std::move(big));
    assert(stolen.size() == 100);
    assert(stolen.at(0) == 0);
    assert(stolen.at(99) == 99);
    assert(big.empty());
    assert(stolen.find(50) == 50);
    assert(stolen.find(999) == stolen.size());

    // Move assignment, including replacement, self-move, and an empty source.
    SinglyLinkedList<int> source1;
    source1.push_back(10);
    source1.push_back(20);
    source1.push_back(30);
    SinglyLinkedList<int> destination1;
    destination1 = std::move(source1);
    assert(destination1.size() == 3);
    assert(destination1.at(0) == 10);
    assert(source1.empty());

    SinglyLinkedList<int> destination2;
    destination2.push_back(1);
    SinglyLinkedList<int> source2;
    source2.push_back(100);
    source2.push_back(200);
    destination2 = std::move(source2);
    assert(destination2.size() == 2);
    assert(destination2.at(0) == 100);
    assert(source2.empty());
    SinglyLinkedList<int>& destination2_ref = destination2;
    destination2 = std::move(destination2_ref);
    assert(destination2.size() == 2);
    assert(destination2.at(1) == 200);

    SinglyLinkedList<int> destination3;
    destination3.push_back(1);
    destination3.push_back(2);
    destination3 = std::move(empty_source);
    assert(destination3.empty());

    // clear and reuse.
    SinglyLinkedList<int> list9;
    list9.push_back(10);
    list9.push_back(20);
    list9.push_back(30);
    list9.clear();
    assert(list9.empty());
    assert(list9.size() == 0);
    list9.push_back(10);
    assert(list9.at(0) == 10);
    return 0;
}
