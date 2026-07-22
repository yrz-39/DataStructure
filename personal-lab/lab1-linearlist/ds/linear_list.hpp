#pragma once
#include <cstddef>
template <typename T> class LinearList {
  public:
    LinearList() = default;
    virtual ~LinearList() = default;

    virtual std::size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual T& at(std::size_t index) = 0;
    virtual const T& at(std::size_t index) const = 0;
    virtual void set(std::size_t index, const T& value) = 0;
    virtual void insert(std::size_t index, const T& value) = 0;
    virtual T erase(std::size_t index) = 0;
    virtual std::size_t find(const T& value) const = 0;
};