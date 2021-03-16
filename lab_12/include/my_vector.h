#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>

namespace my_vector {

template<typename T>
class my_vector {
public:
    my_vector();
    my_vector(std::size_t n);
    my_vector(const my_vector<T>& other);
    my_vector<T>& operator=(const my_vector<T>& other);
    ~my_vector();

    template<typename U>
    friend std::ostream& operator<<(std::ostream& out, const my_vector<U>& v);

    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;

    void resize(std::size_t n);
    void reserve(std::size_t n);

    T& operator[](std::size_t index) const;

    void push_back(const T& t);
    void pop_back();
    void clear();

private:
    void swap(my_vector<T>& other);

    size_t capacity_;
    size_t size_;
    T* array_;
};

#include "my_vector_impl.h"

}


#endif  // MY_VECTOR_H_
