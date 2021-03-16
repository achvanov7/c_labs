#ifndef REGTANGLE_HPP
#define RECTANGLE_HPP

#include "Figure.hpp"
#include <cstdio>
#include <cmath>

class Rectangle : public Figure {
public:
    Rectangle(int id, int x, int y, int width, int height);

    ~Rectangle();
 
    void print() const;
 
    void zoom(int factor);
 
    bool is_inside(int x1, int y1) const;
 
private:
    int width, height;
};

#endif
