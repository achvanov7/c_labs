#include "../include/matrix.h"
#include <iostream>
#include <string>

static int get_reg(std::string s){
  return (s[1]-'0');
}

int main(){
  matrix::matrix_assembler ma;
  std::string action, p0, p1;
  int i0, i1;
  std::cin >> action;
  while(action != "exit"){
    if(action == "load"){
      std::cin >> p0 >> p1;
      ma.load(get_reg(p0), p1);
    }
    else if(action == "print"){
      std::cin >> p0;
      ma.print(get_reg(p0));
    }
    else if(action == "add"){
      std::cin >> p0 >> p1;
      ma.add(get_reg(p0), get_reg(p1));
    }
    else if(action == "mul"){
      std::cin >> p0 >> p1;
      ma.mul(get_reg(p0), get_reg(p1));
    }
    else if(action == "elem"){
      std::cin >> p0 >> i0 >> i1;
      ma.elem(get_reg(p0), i0, i1);
    }
    else {
      break;
    }
    std::cin >> action;
  }
  return 0;
}
