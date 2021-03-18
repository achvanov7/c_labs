#include "Scheme.hpp"

Scheme::Scheme(int capacity) {
    figures_ = new Figure*[capacity];
    size = 0;
}
    
Scheme::~Scheme() {
    for (int i = 0; i < size; ++i) 
        delete figures_[i];
    delete [] figures_;
}

void Scheme:: push_back_figure(Figure* fg) {
    figures_[size] = fg;
    size++;
}

void Scheme::remove_figure( int id) {
    for (int i = 0; i < size; i++) {
        if (figures_[i]->get_id() == id) {
            delete figures_[i];
            for (int j = i; j < size - 1; j++)
                figures_[j] = figures_[j + 1];
            size--;
            break;
        }
    }
}

void Scheme:: print_all_figures() const {
    for (int i = 0; i < size; i++) {
        figures_[i]->print();
    }
}

void Scheme:: zoom_figure( int id, int factor) {
    for (int i = 0; i < size; i++) {
        if (figures_[i]->get_id() == id)
            figures_[i]->zoom(factor);
        }
}

Figure* Scheme:: is_inside_figure(int x, int y) { // если внутри нескольких фигур, то возвращается любая из них
    for (int i = 0; i < size; i++) {
        if (figures_[i]->is_inside(x, y)) {
            return figures_[i];
        }
    }
    return nullptr;
}

void Scheme:: move(const int id, int new_x, int new_y) {
    for (int i = 0; i < size; i++) {
        if (figures_[i]->get_id() == id) {
            figures_[i]->move(new_x, new_y);
            break;
        }
    }
}
