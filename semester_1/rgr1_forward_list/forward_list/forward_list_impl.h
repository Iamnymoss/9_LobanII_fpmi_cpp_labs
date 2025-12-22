#pragma once

#include <iostream>
#include <iterator>

class ForwardList {
private:
    struct Node {
        int value_;
        Node* next_;
        explicit Node(int value) : value_(value), next_(nullptr) {}
    };

public:
    class ForwardListIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = int;
        using difference_type   = long long;
        using pointer           = value_type*;
        using reference         = value_type&;

        ForwardListIterator() : position_(nullptr) {}
        explicit ForwardListIterator(Node* position) : position_(position) {}

        ForwardListIterator& operator++() {
            if (position_ != nullptr) {
                position_ = position_->next_;
            }
            return *this;
        }

        
        ForwardListIterator operator++(int) {
            ForwardListIterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const ForwardListIterator& other) const {
            return position_ == other.position_;
        }

        bool operator!=(const ForwardListIterator& other) const {
            return position_ != other.position_;
        }

        reference operator*() const {
            return position_->value_;
        }

        pointer operator->() const {
            return &position_->value_;
        }

    private:
        Node* position_;
        friend class ForwardList;
    };

    ForwardListIterator begin() { return ForwardListIterator(head_); }
    ForwardListIterator end() { return ForwardListIterator(nullptr); }
    ForwardListIterator begin() const { return ForwardListIterator(head_); }
    ForwardListIterator end() const { return ForwardListIterator(nullptr); }

    ForwardList();
    ForwardList(const ForwardList& rhs);

    ForwardList(unsigned long long count, int value);

    template <class... Ints>
    ForwardList(int first, Ints... rest) : head_(nullptr), size_(0ull) {
        int arr[] = { first, static_cast<int>(rest)... };
        const int n = static_cast<int>(sizeof...(rest)) + 1;
        for (int i = n - 1; i >= 0; --i) {
            PushFront(arr[i]);
        }
    }

    ForwardList& operator=(const ForwardList& rhs);
    ~ForwardList();

    void PushFront(int value);
    void PopFront();
    void Remove(int value);
    void Clear();

    
    bool FindByValue(int value) const;
    void Print(std::ostream& out) const;
    int Front() const;
    unsigned long long Size() const;

private:
    Node* head_;
    unsigned long long size_;

    void CopyFrom(const ForwardList& rhs);
};
