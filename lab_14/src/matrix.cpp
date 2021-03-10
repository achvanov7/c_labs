#include "../include/matrix.h"

#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

namespace matrix {
static char add_dimensions[] = "ADD: dimensions do not match.";
static char mul_dimensions[] = "MUL: #arg1.columns != #arg2.rows.";
static char access_bad_index[] = "ACCESS: bad index.";
static char load_unable[] = "LOAD: unable to open file.";
static char load_invalid[] = "LOAD: invalid file format.";
static char unable_allocate[] = "Unable to allocate memory.";

MatrixException::MatrixException(const char* msg){
  msg_ = new char[strlen(msg) + 1];
  strcpy(msg_, msg);
}

MatrixException::~MatrixException(){
  delete [] msg_;
}

const char* MatrixException::what() const throw() {
  return msg_;
}

matrix::matrix() : matrix::matrix((std::size_t)0, (std::size_t)0) {
}

matrix::matrix(std::size_t n, std::size_t m){
  n_ = n;
  m_ = m;
  matrix_ = NULL;
  if(n!=0 && m!=0){
    matrix_ = new int[n*m];
  }
}

matrix::~matrix(){
  if(matrix_ != NULL){
    delete [] matrix_;
  }
}

matrix& operator+(const matrix& a, const matrix& b) {
  if((a.n_ != b.n_) || (a.m_ != b.m_)){
    throw MatrixException(add_dimensions);
  }
  matrix* new_matrix = new matrix(a.n_, a.m_);
  for(std::size_t i=0; i<a.n_; i++){
    for(std::size_t j=0; j<a.m_; j++){
      (*new_matrix)(i, j) = a(i, j) + b(i, j);
    }
  }
  return *new_matrix;
}

matrix& operator*(const matrix& a, const matrix& b) {
  if(a.m_ != b.n_){
    throw MatrixException(mul_dimensions);
  }
  matrix* new_matrix = new matrix(a.n_, b.m_);
  for(std::size_t i=0; i<a.n_; i++){
    for(std::size_t j=0; j<b.m_; j++){
      (*new_matrix)(i, j) = 0;
      for(std::size_t k=0; k<a.m_; k++){
        (*new_matrix)(i, j) += (a(i, k) * b(k, j));
      }
    }
  }
  return *new_matrix;
}

std::ostream& operator<<(std::ostream& out, const matrix& a){
  for(std::size_t i=0; i<a.n_; i++){
    for(std::size_t j=0; j<a.m_; j++){
      out << a(i, j) << " ";
    }
    out << std::endl;
  }
  if(a.n_==0){
    out << std::endl;
  }
  return out;
}

std::ifstream& operator>>(std::ifstream& infile, matrix& a) {
  std::string line;
  std::stringstream is;
  std::size_t i, j, n, m;
  int x;
  if(!getline(infile, line)) throw MatrixException(load_invalid);
  is.str(line);
  n = (std::size_t)0;
  m = (std::size_t)0;
  for(i=(std::size_t)0; (is>>x); i++){
    if(i==2) throw MatrixException(load_invalid);
    if(i==0){
      n = (std::size_t)x;
    }
    else {
      m = (std::size_t)x;
    }
  }
  if(i!=2) throw MatrixException(load_invalid);
  matrix new_matrix = matrix(n, m);
  for(i=(std::size_t)0; getline(infile, line); i++){
    if(i==n) throw MatrixException(load_invalid);
    is.clear();
    is.str(line);
    for(j=(std::size_t)0; (is>>x); j++){
      if(j==m) throw MatrixException(load_invalid);
      new_matrix(i, j) = x;
    }
    if(j!=m) throw MatrixException(load_invalid);
  }
  if(i!=n) throw MatrixException(load_invalid);
  std::swap(new_matrix.n_, a.n_);
  std::swap(new_matrix.m_, a.m_);
  std::swap(new_matrix.matrix_, a.matrix_);
  return infile;
}

const int& matrix::operator()(std::size_t row, std::size_t col) const {
  if((row >= n_) || (col >= m_)){
    throw MatrixException(access_bad_index);
  }
  return matrix_[row*m_+col];
}

int& matrix::operator()(std::size_t row, std::size_t col) {
  if((row >= n_) || (col >= m_)){
    throw MatrixException(access_bad_index);
  }
  return matrix_[row*m_+col];
}

const int matrix::get_rows() const {
  return n_;
}

const int matrix::get_cols() const {
  return m_;
}

matrix_assembler::matrix_assembler(){
  for(std::size_t i=0; i<MAX_REGS; i++){
    regs_[i] = new matrix();
  }
}

matrix_assembler::~matrix_assembler(){
  for(std::size_t i=0; i<MAX_REGS; i++){
    delete regs_[i];
  }
}

void matrix_assembler::load(std::size_t reg, std::string fname){
  std::ifstream infile;
  matrix* result = NULL;
  try {
    infile.open(fname.c_str(), std::ios::in);
    if(infile){
      result = new matrix();
      infile >> *(result);
      std::swap(result, regs_[reg]);
    }
    else {
      throw MatrixException(load_unable);
    }
  }
  catch(std::bad_alloc& e){
    std::cout << unable_allocate << std::endl;
  }
  catch(const std::exception& e){
    std::cout << e.what() << std::endl;
  }
  if(result!=NULL){
    delete result;
  }
}

void matrix_assembler::print(std::size_t reg) const {
  std::cout << *(regs_[reg]);
}

void matrix_assembler::add(std::size_t reg1, std::size_t reg2){
  matrix* result = NULL;
  try {
    result = &(*(regs_[reg1]) + *(regs_[reg2]));
    std::swap(result, regs_[reg1]);
  }
  catch(std::bad_alloc& e){
    std::cout << unable_allocate << std::endl;
  }
  catch(const std::exception& e){
    std::cout << e.what() << std::endl;
  }
  if(result!=NULL){
    delete result;
  }
}

void matrix_assembler::mul(std::size_t reg1, std::size_t reg2){
  matrix* result = NULL;
  try {
    result = &(*(regs_[reg1]) * *(regs_[reg2]));
    std::swap(result, regs_[reg1]);
  }
  catch(std::bad_alloc& e){
    std::cout << unable_allocate << std::endl;
  }
  catch(const std::exception& e){
    std::cout << e.what() << std::endl;
  }
  if(result!=NULL){
    delete result;
  }
}

void matrix_assembler::elem(std::size_t reg, int row, int col){
  try {
    if (row < 0 || col < 0){
      throw MatrixException(access_bad_index);
    }
    std::size_t r = (std::size_t)row;
    std::size_t c = (std::size_t)col;
    int result = (*(regs_[reg]))(r, c);
    std::cout << result << std::endl;
  }
  catch(const std::exception& e){
    std::cout << e.what() << std::endl;
  }
}
}
