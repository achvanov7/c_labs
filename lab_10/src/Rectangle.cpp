#include "Rectangle.hpp"
#include <algorithm>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y) {
    this->width = width;
    this->height = height;
}
 
Rectangle:: ~Rectangle() {
       
}

void Rectangle:: print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id, x, y, width, height);
}
 
void Rectangle::zoom(int factor) {
    width = width * factor;
    height = height * factor;
}
 
bool Rectangle::is_inside(int x1, int y1) const {
    return (abs(x - x1) <= width / 2 && abs(y - y1) <= height / 2);
}


