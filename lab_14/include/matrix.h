#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstddef>
#include <fstream>
#include <exception>

#define MAX_REGS 10

namespace matrix {

class MatrixException : public std::exception {
public:
  MatrixException(const char* msg);
  ~MatrixException();
  virtual const char* what() const throw();
private:
  char* msg_;
};

class matrix {
public:
  matrix();
  matrix(std::size_t n, std::size_t m);
  ~matrix();

  friend matrix& operator+(const matrix& a, const matrix& b);
  friend matrix& operator*(const matrix& a, const matrix& b);

  friend std::ostream& operator<<(std::ostream& out, const matrix& a);
  friend std::ifstream& operator>>(std::ifstream& infile, matrix& a);

  const int& operator()(std::size_t row, std::size_t col) const;
  int& operator()(std::size_t row, std::size_t col);

  const int get_rows() const;
  const int get_cols() const;
private:
  std::size_t n_, m_;
  int* matrix_;
};

class matrix_assembler {
public:
  matrix_assembler();
  ~matrix_assembler();

  void load(std::size_t reg, std::string fname);
  void print(std::size_t reg) const;
  void add(std::size_t reg1, std::size_t reg2);
  void mul(std::size_t reg1, std::size_t reg2);
  void elem(std::size_t reg, int row, int col);
private:
  matrix* regs_[MAX_REGS];
};

}

#endif
