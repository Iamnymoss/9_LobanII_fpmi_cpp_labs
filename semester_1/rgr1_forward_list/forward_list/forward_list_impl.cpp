#include "forward_list_impl.h"

ForwardList::ForwardList() : head_(nullptr), size_(0ull) {}

ForwardList::ForwardList(unsigned long long count, int value) : head_(nullptr), size_(0ull) {
    for (unsigned long long i = 0; i < count; ++i) {
        PushFront(value);
    }
}

ForwardList::ForwardList(const ForwardList& rhs) : head_(nullptr), size_(0ull) {
    CopyFrom(rhs);
}

ForwardList& ForwardList::operator=(const ForwardList& rhs) {
    if (this == &rhs) {
        return *this;
    }
    Clear();
    CopyFrom(rhs);
    return *this;
}

ForwardList::~ForwardList() {
    Clear();
}

void ForwardList::PushFront(int value) {
    Node* n = new Node(value);
    n->next_ = head_;
    head_ = n;
    ++size_;
}

void ForwardList::PopFront() {
    if (head_ == nullptr) {
        return;
    }
    Node* tmp = head_;
    head_ = head_->next_;
    delete tmp;
    --size_;
}

void ForwardList::Remove(int value) {
    while (head_ != nullptr && head_->value_ == value) {
        PopFront();
    }
    if (head_ == nullptr) {
        return;
    }

    Node* prev = head_;
    Node* cur = head_->next_;
    while (cur != nullptr) {
        if (cur->value_ == value) {
            prev->next_ = cur->next_;
            delete cur;
            cur = prev->next_;
            --size_;
        } else {
            prev = cur;
            cur = cur->next_;
        }
    }
}

void ForwardList::Clear() {
    while (head_ != nullptr) {
        Node* tmp = head_->next_;
        delete head_;
        head_ = tmp;
    }
    size_ = 0ull;
}

bool ForwardList::FindByValue(int value) const {
    Node* cur = head_;
    while (cur != nullptr) {
        if (cur->value_ == value) {
            return true;
        }
        cur = cur->next_;
    }
    return false;
}

void ForwardList::Print(std::ostream& out) const {
    Node* cur = head_;
    bool first = true;
    while (cur != nullptr) {
        if (!first) {
            out << ' ';
        }
        first = false;
        out << cur->value_;
        cur = cur->next_;
    }
}

int ForwardList::Front() const {
    return head_->value_;
}

unsigned long long ForwardList::Size() const {
    return size_;
}

void ForwardList::CopyFrom(const ForwardList& rhs) {
    if (rhs.head_ == nullptr) {
        head_ = nullptr;
        size_ = 0ull;
        return;
    }

    Node* src = rhs.head_;
    Node* new_head = new Node(src->value_);
    Node* tail = new_head;
    unsigned long long new_size = 1ull;

    src = src->next_;
    while (src != nullptr) {
        tail->next_ = new Node(src->value_);
        tail = tail->next_;
        src = src->next_;
        ++new_size;
    }

    head_ = new_head;
    size_ = new_size;
}
