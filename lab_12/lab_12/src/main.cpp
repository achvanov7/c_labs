#include <iostream>
#include <cassert>
#include <sstream>
#include <cstring>

#include "../include/my_vector.h"

namespace product {

class Product {
public:
    Product();
    Product(const char* name, int quantity, double price);
    Product(const Product& a);
    Product& operator=(const Product& other);
    ~Product();

    friend std::ostream& operator<<(std::ostream& out, const Product& p);

    friend bool operator==(const Product& lhs, const Product& rhs);

    const char* name() const;
    int quantity() const;
    double price() const;

private:
    void swap(Product& other);

    char *name_;
    int quantity_;
    double price_;
};


void Product::swap(Product& other) {
    std::swap(name_, other.name_);
    std::swap(quantity_, other.quantity_);
    std::swap(price_, other.price_);
}

Product::Product() : Product::Product("", 0, 0.0) {
}

Product::Product(const char* name, int quantity, double price) {
    size_t n = std::strlen(name);
    name_ = new char[n+1];
    std::strcpy(name_, name);
    quantity_ = quantity;
    price_ = price;
}

Product::Product(const Product& a) : Product::Product(a.name(), a.quantity(), a.price()) {
}

Product& Product::operator=(const Product& other){
    Product tmp(other);
    Product::swap(tmp);
    return *this;
}

Product::~Product(){
    if (name_ != NULL){
        delete [] name_;
    }
}

const char* Product::name() const {
    return name_;
}

int Product::quantity() const {
    return quantity_;
}

double Product::price() const {
    return price_;
}

std::ostream& operator<<(std::ostream& out, const Product& p) {
    out << p.name() << " " << p.quantity() << " " << p.price();
    return out;
}

bool operator==(const Product& lhs, const Product& rhs) {
    return (std::strcmp(lhs.name(), rhs.name()) == 0 && lhs.price() == rhs.price() && lhs.quantity() == rhs.quantity());
}

void print(const my_vector::my_vector<Product>& v) {
    std::cout << v << std::endl;
}

}  // namespace product

namespace test {

template<typename T>
static void test_my_vector(const T& first, const T& second){
    {
        my_vector::my_vector<T> v;
        assert(v.size() == (std::size_t)0);
        assert(v.capacity() == (std::size_t)1);
    }
    {
        my_vector::my_vector<T> v(7);
        assert(v.size() == (std::size_t)7);
        assert(v.capacity() == (std::size_t)8);
    }
    {
        my_vector::my_vector<T> v(8);
        assert(v.size() == (std::size_t)8);
        assert(v.capacity() == (std::size_t)8);
    }
    {
        my_vector::my_vector<T> v(9);
        assert(v.size() == (std::size_t)9);
        assert(v.capacity() == (std::size_t)16);
    }
    {
        my_vector::my_vector<T> v;
        v.push_back(T(first));
        assert(v.size() == (std::size_t)1);
        assert(v.capacity() == (std::size_t)1);
        assert(v[0] == first);
        v.push_back(T(second));
        assert(v.size() == (std::size_t)2);
        assert(v.capacity() == (std::size_t)2);
        assert(v[1] == second);
        v.push_back(T(second));
    }
    {
        my_vector::my_vector<T> v;
        v.push_back(T(first));
        v.push_back(T(second));
        my_vector::my_vector<T> v0(v);
        assert(v.size() == (std::size_t)2);
        assert(v.capacity() == (std::size_t)2);
        assert(v[0] == first);
        assert(v[1] == second);
        assert(v0.size() == (std::size_t)2);
        assert(v0.capacity() == (std::size_t)2);
        assert(v0[0] == first);
        assert(v0[1] == second);
    }
    {
        my_vector::my_vector<T> v1;
        v1.push_back(T(first));
        v1.push_back(T(second));
        my_vector::my_vector<T> v2;
        v2.push_back(T(second));
        v2.push_back(T(first));
        v2.push_back(T(second));
        v1 = v2;
        assert(v1.size() == (std::size_t)3);
        assert(v1.capacity() == (std::size_t)4);
        assert(v1[0] == second);
        assert(v1[1] == first);
        assert(v1[2] == second);
        assert(v2.size() == (std::size_t)3);
        assert(v2.capacity() == (std::size_t)4);
    }
    {
        my_vector::my_vector<T> v;
        v.push_back(T(first));
        v.push_back(T(second));
        std::stringstream actual, expect;
        actual << v;
        expect << "my vector: " << first << " " << second;
        assert(actual.str().compare(expect.str()));
    }
    {
        my_vector::my_vector<T> v;
        v.push_back(T(first));
        v.push_back(T(second));
        v.clear();
        assert(v.size() == (std::size_t)0);
        assert(v.capacity() == (std::size_t)1);
    }
    {
        my_vector::my_vector<T> v;
        v.push_back(T(first));
        v.push_back(T(second));
        v.pop_back();
        assert(v.size() == (std::size_t)1);
        assert(v.capacity() == (std::size_t)2);
        assert(v[0] == first);
        v.pop_back();
        assert(v.size() == (std::size_t)0);
        assert(v.capacity() == (std::size_t)2);
    }
    {
        my_vector::my_vector<T> v;
        v.push_back(T(first));
        v.push_back(T(second));
        v.reserve(100);
        assert(v.size() == (std::size_t)2);
        assert(v.capacity() == (std::size_t)128);
        assert(v[0] == first);
        assert(v[1] == second);
        v.reserve(100);
        assert(v.size() == (std::size_t)2);
        assert(v.capacity() == (std::size_t)128);
        assert(v[0] == first);
        assert(v[1] == second);
    }
    {
        my_vector::my_vector<T> v;
        v.resize(3);
        assert(v.size() == (std::size_t)3);
        assert(v.capacity() == (std::size_t)4);
        v.resize(4);
        assert(v.size() == (std::size_t)4);
        assert(v.capacity() == (std::size_t)4);
        v.resize(5);
        assert(v.size() == (std::size_t)5);
        assert(v.capacity() == (std::size_t)8);
        v.resize(3);
        assert(v.size() == (std::size_t)3);
        assert(v.capacity() == (std::size_t)8);

    }
}

template<typename T>
static void test_my_vector_default_constructible(const T& first, const T& second){
    static_assert(std::is_default_constructible<T>::value, "It is not default constructible type!");
    {
        std::size_t n = 5;
        my_vector::my_vector<T> v(5);
        for(std::size_t i=0; i<n; i++){
            assert(v[i] == T());
        }
    }
    {
        std::size_t n = 5;
        my_vector::my_vector<T> v;
        v.resize(n);
        for(std::size_t i=0; i<n; i++){
            assert(v[i] == T());
        }
    }
    {
        std::size_t n = 5;
        my_vector::my_vector<T> v;
        v.push_back(T(first));
        v.push_back(T(second));
        v.resize(n);
        assert(v[0] == first);
        assert(v[1] == second);
        for(std::size_t i=2; i<n; i++){
            assert(v[i] == T());
        }
    }
}

}

int main() {
    test::test_my_vector<int>(5, 10);
    test::test_my_vector_default_constructible<int>(5, 10);

    product::Product p0 = product::Product("asdf", 4, 12.0);
    product::Product p1 = product::Product("qwe", -1, 7.5);

    test::test_my_vector<product::Product>(p0, p1);
    test::test_my_vector_default_constructible<product::Product>(p0, p1);

    my_vector::my_vector<product::Product> v;
    v.push_back(product::Product(p0));
    v.push_back(product::Product(p1));
    product::print(v);
    return 0;
}
