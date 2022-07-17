#ifndef __ARRAY__
#define __ARRAY__
#include <iostream>
#include <cassert>
#include <string.h>

using namespace std;

// custom implementation of std::vector<T>
template <typename T>
class array {
   public:
    array() {
        buffer = new T[capacity];
    }
    array(T* first, T* last) {
        buffer = new T[capacity];
        insert(buffer, first, last);
    }
    array(const array& org) {
        this->buffer = new T[org.capacity];
        this->capacity = org.capacity;
        this->length = org.length;
        memcpy(this->buffer, org.buffer, sizeof(T) * capacity);
    }
    array(int _size) {
        capacity = (1 + (_size / capacity)) * capacity;
        buffer = new T[capacity];
        length = _size;
    }
    ~array() {
        delete[] buffer;
    }

    size_t size() {
        return length;
    }

    void swap(array<T>& target) {
        size_t t_length = target.length, t_capacity = target.capacity;
        T* t_buff = new T[t_capacity];
        memcpy(t_buff, target.buffer, sizeof(T) * t_capacity);

        target.length = this->length;
        target.capacity = this->capacity;
        delete[] target.buffer;
        target.buffer = new T[target.capacity];
        memcpy(target.buffer, this->buffer, sizeof(T) * target.capacity);
    
        this->length = t_length;
        this->capacity = t_capacity;
        delete[] this->buffer;
        this->buffer = new T[this->capacity];
        memcpy(this->buffer, t_buff, sizeof(T) * this->capacity);

        delete[] t_buff;
    }

    void push_back(T value) {
        if (capacity - length < 2) {
            // capacity multiply by two
            size_t new_capacity = capacity * 2;
            T* new_buffer = new T[new_capacity];

            for (size_t i = 0; i < length; i++) {
                new_buffer[i] = buffer[i];
            }
            delete[] buffer;
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[length] = value;
        length++;
    }

    void append(array<T> src_array) {
        // this_array := [...this_array, ...src_array]

        for (size_t i = 0; i < src_array.length; i++) {
            push_back(src_array.buffer[i]);
        }
    }

    // @returns 0 if no errors, != 0 is errors
    int insert(T* position, T* first, T* last) {
        if (first > last) {
            return -1;
        }

        size_t new_length = position - buffer;
        if (new_length >= capacity) {
            return -2;
        }
        length = new_length;

        T* current = first;
        while (current != last) {
            push_back(*current);
            current++;
        }
        return 0;
    }

    // @returns 0 if no errors, != 0 is errors
    int erase(T* first, T* last) {
        if (first > last) {
            return -1;
        } else if (first < buffer) {
            return -2;
        } else if (last > buffer + length) {
            return -3;
        }

        T *old_begin = begin(), *old_end = end();

        length = 0;
        insert(end(), old_begin, first);
        insert(end(), last, old_end);

        return 0;
    }

    T* data() {
        return buffer;
    }

    T* begin() {
        return buffer;
    }

    T* end() {
        return buffer + length;
    }

    T& operator[](int i) {
        assert(i >= 0 && i < length);
        return buffer[i];
    }

    array<T> operator=(array<T>& org) {
        delete[] this->buffer;
        this->buffer = new T[org.capacity];
        this->capacity = org.capacity;
        this->length = org.length;
        memcpy(this->buffer, org.buffer, sizeof(T) * capacity);
        return (*this);
    }

    void empty() {
        length = 0;
        capacity = 1024;
        delete[] buffer;
        buffer = new T[capacity];
    }

    // for debugging
    void print_array(string s = "") {
        cout << s;
        for (size_t i = 0; i < length; i++) {
            cout << i << ": " << (int)buffer[i] << endl;
        }
    }

   private:
    size_t length = 0;
    size_t capacity = 1024;
    T* buffer = nullptr;
};

#endif  // !__ARRAY__