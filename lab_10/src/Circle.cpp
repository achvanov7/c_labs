#include "Circle.hpp"

Circle::Circle(int id, int x, int y, int radius, const char* label)
    : Figure(id, x, y) {
        this->radius = radius;
        int len = strlen(label);
        this->label = new char[len + 1];
        for (int i = 0; i < len; i++)
            this->label[i] = label[i];
        this->label[len] = '\0';
}

 

Circle:: ~Circle() {
    delete[] label;
    label = nullptr;
}
 
void Circle:: print() const{
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, label);
}
 
void Circle:: zoom(int factor) {
    radius = radius * factor;
}

bool Circle:: is_inside(int x1, int y1) const {
    return ((x - x1) * (x - x1) + (y - y1) * (y - y1) <= radius * radius);
}
