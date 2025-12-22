#pragma once

#include <initializer_list>
#include <cstddef>
#include <stdexcept>
#include <ostream>

class Vector {
public:
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    explicit Vector(std::size_t size)
        : data_(size ? new int[size]() : nullptr), size_(size), capacity_(size) {}

    Vector(std::initializer_list<int> init)
        : data_(init.size() ? new int[init.size()] : nullptr),
          size_(init.size()),
          capacity_(init.size()) {
        std::size_t i = 0;
        for (int v : init) {
            data_[i++] = v;
        }
    }

    Vector(const Vector& other)
        : data_(other.size_ ? new int[other.size_] : nullptr),
          size_(other.size_),
          capacity_(other.size_) {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }
        Vector tmp(other);
        Swap(tmp);
        return *this;
    }

    ~Vector() {
        delete[] data_;
    }

    void Swap(Vector& other) {
        int* tmp_data = data_;
        data_ = other.data_;
        other.data_ = tmp_data;

        std::size_t tmp_size = size_;
        size_ = other.size_;
        other.size_ = tmp_size;

        std::size_t tmp_capacity = capacity_;
        capacity_ = other.capacity_;
        other.capacity_ = tmp_capacity;
    }

    int& operator[](std::size_t index) {
        return data_[index];
    }

    const int& operator[](std::size_t index) const {
        return data_[index];
    }

    int& At(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Vector::At");
        }
        return data_[index];
    }

    const int& At(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Vector::At");
        }
        return data_[index];
    }

    std::size_t Size() const {
        return size_;
    }

    std::size_t Capacity() const {
        return capacity_;
    }

    void PushBack(int value) {
        if (size_ == capacity_) {
            std::size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
            Reserve(new_capacity);
        }
        data_[size_++] = value;
    }

    void PopBack() {
        if (size_ > 0) {
            --size_;
        }
    }

    void Clear() {
        size_ = 0;
    }

    void Reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) {
            return;
        }
        int* new_data = new int[new_capacity];
        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

private:
    int* data_;
    std::size_t size_;
    std::size_t capacity_;
};

inline std::ostream& operator<<(std::ostream& os, const Vector& v) {
    os << "[";
    for (std::size_t i = 0; i < v.Size(); ++i) {
        if (i > 0) {
            os << ", ";
        }
        os << v[i];
    }
    os << "]";
    return os;
}

