#pragma once
#include "ds/linear_list.hpp"
#include <stdexcept>

template <typename T> class SinglyLinkedList : public LinearList<T> {
  private:
    struct Node {
        T value;
        Node* next;

        Node(T v) : value(v), next(nullptr) {
        }
    };

    std::size_t size_;
    Node* head_;
    Node* tail_;

    void copy_from(const SinglyLinkedList<T>& other){
        if (other.size() == 0) {
            head_ = nullptr;
            tail_ = nullptr;
            size_ = 0;
            return;
        }
        size_ = other.size_;
        head_ = new Node(other.head_->value);
        // tail_=new Node(other.tail_->value);
        Node* other_cur = other.head_;
        Node* cur = head_;
        while (other_cur != other.tail_) {
            cur->next = new Node(other_cur->next->value);
            cur = cur->next;
            other_cur = other_cur->next;
        }
        tail_ = cur;
        tail_->next = nullptr;
    }
  public:
    SinglyLinkedList() : size_(0), head_(nullptr), tail_(nullptr) {
    }
    SinglyLinkedList(const SinglyLinkedList<T>& other) {
        copy_from(other);
    }
    SinglyLinkedList(SinglyLinkedList<T>&& other) noexcept {
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    virtual ~SinglyLinkedList() {
        if (head_ == nullptr)
            return;
        Node* cur = head_->next;
        Node* erased = head_;
        while (cur != nullptr) {
            delete erased;
            erased = cur;
            cur = cur->next;
        }
        delete erased;
        head_ = nullptr;
        tail_ = nullptr;
    }

    std::size_t size() const override {
        return size_;
    }

    bool empty() const override {
        return size_ == 0;
    }

    T& at(std::size_t index) override {
        if (index >= size_) {
            throw std::out_of_range("索引超出范围");
        }
        Node* cur = head_;
        for (std::size_t i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->value;
    }

    const T& at(std::size_t index) const override {
        if (index >= size_) {
            throw std::out_of_range("索引超出范围");
        }
        Node* cur = head_;
        for (std::size_t i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->value;
    }
    void set(std::size_t index, const T& value) override {
        at(index) = value;
    }
    void insert(std::size_t index, const T& value) override {
        if (index > size_) {
            throw std::out_of_range("索引超出范围");
        }
        Node* newNode = new Node(value);
        if (index == 0) {
            if (head_ == nullptr) {
                head_ = newNode;
                tail_ = head_;
                size_++;
                return;
            }

            newNode->next = head_;
            head_ = newNode;
        } else if (index == size_) {

            tail_->next = newNode;
            tail_ = newNode;
        } else {
            Node* cur = head_;
            for (std::size_t i = 1; i < index; ++i) {
                cur = cur->next;
            }
            newNode->next = cur->next;
            cur->next = newNode;
        }
        size_++;
    }
    T erase(std::size_t index) override {
        if (index >= size_) {
            throw std::out_of_range("索引超出范围");
        }
        T value;
        if (index == 0) {
            Node* erased = head_;
            head_ = head_->next;
            value = erased->value;
            delete erased;

        } else if (index == size_ - 1) {
            Node* cur = head_;
            while (cur->next != tail_) {
                cur = cur->next;
            }
            value = tail_->value;
            delete tail_;
            tail_ = cur;
            tail_->next = nullptr;
        } else {
            Node* cur = head_;
            for (std::size_t i = 1; i < index; ++i) {
                cur = cur->next;
            }
            Node* erased = cur->next;
            cur->next = erased->next;
            value = erased->value;
            delete erased;
        }
        size_--;
        if (size_ == 0) {
            head_ = nullptr;
            tail_ = nullptr;
        }
        return value;
    }
    std::size_t find(const T& value) const override {
        Node* cur = head_;
        std::size_t index = 0;
        while (cur != nullptr) {
            if (cur->value == value) {
                return index;
            }
            cur = cur->next;
            index++;
        }
        return size_;
    }
    void push_back(const T& value) {
        insert(size_, value);
    }
    void clear() {
        if (head_ == nullptr)
            return;
        Node* cur = head_->next;
        Node* erased = head_;
        while (cur != nullptr) {
            delete erased;
            erased = cur;
            cur = cur->next;
        }
        delete erased;
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }
    SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other){
        if(&other == this){
            return *this;
        }
        clear();
        copy_from(other);
        return *this;
    }
    SinglyLinkedList<T>& operator=(SinglyLinkedList<T>&& other) noexcept{
        if(&other == this){
            return *this;
        }

        clear();

        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;

        return *this;
    }
};