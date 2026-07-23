#pragma once
#include "ds/linear_list.hpp"
#include <stdexcept>

template <typename T> class ArrayList : public LinearList<T> {
  private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void ensure_capacity(std::size_t required_capacity) {
        if (required_capacity <= capacity_) {
            return;
        }
        if (capacity_ == 0) {
            data_ = new T[4];
            capacity_ = 4;
            if (required_capacity > capacity_) {
                ensure_capacity(required_capacity);
            }
            return;
        }
        T* new_data = new T[capacity_ * 2];
        for (std::size_t i = 0; i < size_; i++) {
            new_data[i] = data_[i];
        }
        capacity_ *= 2;
        delete[] data_;
        data_ = new_data;
        ensure_capacity(required_capacity);
    }

  public:
    ArrayList() : data_(nullptr), size_(0), capacity_(0) {
    }
    ArrayList(const ArrayList<T>& other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        if (capacity_ == 0) {
            data_ = nullptr;
            return;
        }
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    ArrayList(ArrayList<T>&& other) noexcept {
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    virtual ~ArrayList() {
        delete[] data_;
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
        return data_[index];
    }
    const T& at(std::size_t index) const override {
        if (index >= size_) {
            throw std::out_of_range("索引超出范围");
        }
        return data_[index];
    }
    void set(std::size_t index, const T& value) override {
        if (index >= size_) {
            throw std::out_of_range("索引超出范围");
        }
        data_[index] = value;
    }
    void insert(std::size_t index, const T& value) override {
        if (index > size_) {
            // 这里抛出异常 超出范围
            throw std::out_of_range("索引超出范围");
        }
        ensure_capacity(size_ + 1);

        if (index == size_) {
            data_[size_] = value;
            size_++;
        } else {
            for (std::size_t i = size_; i > index; --i) {
                data_[i] = data_[i - 1];
            }
            data_[index] = value;
            size_++;
        }
    }
    T erase(std::size_t index) override {
        // 删除的范围也是0-size_-1
        if (index >= size_) {
            throw std::out_of_range("索引超出范围");
        }
        T erased_data = data_[index];
        for (std::size_t i = index + 1; i < size_; ++i) {
            data_[i - 1] = data_[i];
        }
        size_--;
        return erased_data;
    }
    std::size_t find(const T& value) const override {
        for (std::size_t i = 0; i < size_; ++i) {
            if (data_[i] == value) {
                return i;
            }
        }
        return size_;
    }
    void push_back(const T& value) {
        insert(size(), value);
    }
    ArrayList<T>& operator=(const ArrayList<T>& other) {
        if (&other == this) {
            return *this;
        }
        // 先准备新资源，再释放旧的
        size_ = other.size_;
        capacity_ = other.capacity_;
        T* new_data;
        if (capacity_ == 0) {
            new_data = nullptr;
        } else {
            new_data = new T[capacity_];
            for (std::size_t i = 0; i < size_; ++i) {
                new_data[i] = other.data_[i];
            }
        }

        delete[] data_;
        data_ = new_data;
        return *this;
    }
    ArrayList<T>& operator=(ArrayList<T>&& other) noexcept {
        if (&other == this) {
            return *this;
        }

        delete[] data_;

        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = other.data_;

        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

        return *this;
    }
    void clear() {
        size_ = 0;
    }
};