#ifndef SCHEME_HPP
#define SCHEME_HPP

#include "Figure.hpp"

class Scheme {
public:
    Scheme(int capacity);
    ~Scheme();
    void push_back_figure(Figure* fg);
    void remove_figure( int id);
    void print_all_figures() const;
    void zoom_figure( int id, int factor);
    Figure* is_inside_figure(int x, int y);
    void move(const int id, int new_x, int new_y);
 
private:
    Figure** figures_; 
    int size;
};

#endif
