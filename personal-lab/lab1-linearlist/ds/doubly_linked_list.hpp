#pragma once
#include "ds/linear_list.hpp"
#include <stdexcept>

template <typename T> class DoublyLinkedList : public LinearList<T> {
  private:
    struct Node {
        T value;
        Node* prev;
        Node* next;

        Node(T v) : value(v), prev(nullptr), next(nullptr) {
        }
    };

    std::size_t size_;
    Node* head_;
    Node* tail_;

    void copy_from(const DoublyLinkedList<T>& other) {
        if (other.size_ == 0) {
            size_ = 0;
            head_ = nullptr;
            tail_ = nullptr;
            return;
        }
        size_ = other.size_;
        head_ = new Node(other.head_->value);
        Node* other_cur = other.head_;
        Node* cur = head_;
        while (other_cur != other.tail_) {
            cur->next = new Node(other_cur->next->value);
            cur->next->prev = cur;
            cur = cur->next;
            other_cur = other_cur->next;
        }
        tail_ = cur;
        tail_->next = nullptr;
    }

  public:
    DoublyLinkedList() : size_(0), head_(nullptr), tail_(nullptr) {
    }
    DoublyLinkedList(const DoublyLinkedList<T>& other) {
        copy_from(other);
    }
    DoublyLinkedList(DoublyLinkedList<T>&& other) noexcept {
        head_ = other.head_;
        tail_ = other.tail_;
        size_ = other.size_;

        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    virtual ~DoublyLinkedList() {
        if (head_ == nullptr) {
            return;
        }
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
        if (index <= size_ / 2) {
            Node* cur = head_;
            for (std::size_t i = 0; i < index; ++i) {
                cur = cur->next;
            }
            return cur->value;
        } else {
            Node* cur = tail_;
            for (std::size_t i = size_ - 1; i > index; --i) {
                cur = cur->prev;
            }
            return cur->value;
        }
    }

    const T& at(std::size_t index) const override {
        if (index >= size_) {
            throw std::out_of_range("索引超出范围");
        }
        if (index <= size_ / 2) {
            Node* cur = head_;
            for (std::size_t i = 0; i < index; ++i) {
                cur = cur->next;
            }
            return cur->value;
        } else {
            Node* cur = tail_;
            for (std::size_t i = size_ - 1; i > index; --i) {
                cur = cur->prev;
            }
            return cur->value;
        }
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
            if (size_ == 0) {
                head_ = newNode;
                tail_ = newNode;
                size_++;
                return;
            }
            newNode->next = head_;
            head_->prev = newNode;
            head_ = newNode;
        } else if (index == size_) {
            tail_->next = newNode;
            newNode->prev = tail_;
            tail_ = newNode;
        } else {
            Node* cur = head_;
            for (std::size_t i = 1; i < index; ++i) {
                cur = cur->next;
            }
            newNode->next = cur->next;
            newNode->prev = cur;
            cur->next = newNode;
            newNode->next->prev = newNode;
        }
        size_++;
    }
    T erase(std::size_t index) override {
        if (index >= size_) {
            throw std::out_of_range("索引超出范围");
        }
        T value;
        if (index == 0) {
            if (size_ == 1) {
                value = head_->value;
                delete head_;
                head_ = tail_ = nullptr;
                size_--;
                return value;
            }
            Node* erased = head_;
            head_ = head_->next;
            // 这里size_==1要单独说 不然这里nullptr是没有prev的
            head_->prev = nullptr;
            value = erased->value;
            delete erased;

        } else if (index == size_ - 1) {
            if (size_ == 1) {
                value = head_->value;
                delete head_;
                head_ = tail_ = nullptr;
                size_--;
                return value;
            }
            Node* erased = tail_;
            tail_ = tail_->prev;
            tail_->next = nullptr;
            value = erased->value;
            delete erased;
        } else {
            Node* cur = head_;
            for (std::size_t i = 1; i < index; ++i) {
                cur = cur->next;
            }
            Node* erased = cur->next;
            cur->next = erased->next;
            erased->next->prev = cur;
            value = erased->value;
            delete erased;
        }
        size_--;
        return value;
    }
    std::size_t find(const T& value) const override {
        // 原本准备用写好的at 但是at本身就要遍历 然后find再遍历复杂度就是n^2了
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

    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other) {
        if (&other == this) {
            return *this;
        }
        clear();
        copy_from(other);
        return *this;
    }

    DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&& other) noexcept {
        if (&other == this) {
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