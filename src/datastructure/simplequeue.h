#pragma once

template <class T> struct SimpleQueue {
    V<T> payload;
    size_t pos = 0;
    void reserve(size_t) { payload.reserve(size); }
    bool empty() const { return pos == payload.size(); }
    void push(const T& t) { payload.push_back(t); }
    T& front() {
        assert(!empty());
        return payload[pos];
    }
    void clear() {
        payload.clear();
        pos = 0;
    }
    void pop() {
        assert(!empty());
        pos++;
    }
};
