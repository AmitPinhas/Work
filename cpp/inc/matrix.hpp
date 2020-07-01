#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include "dimension.hpp"

class Matrix
{
public:
    typedef double ElemType;
	
	Matrix(size_t a_size);
    Matrix(size_t a_rows, size_t a_columns);
    Matrix(const Matrix &a_other) ;
    ~Matrix();

    Dimension Dim() const;
    ElemType Get(size_t a_i, size_t a_j) const;
    void Set(size_t a_i, size_t a_j, ElemType a_value);
	
	bool operator==(const Matrix &a_rhs) const;
	
	Matrix& operator=(const Matrix &a_rhs);
	Matrix& operator=(ElemType a_scaler);	
	Matrix operator+(const Matrix &a_rhs) const;
	Matrix operator+(ElemType a_scaler) const;
	Matrix operator-(const Matrix &a_rhs) const;
	Matrix operator-(ElemType a_scaler) const;
	Matrix operator*(const Matrix &a_rhs) const;
	Matrix operator*(ElemType a_scaler) const;
	
	Matrix& operator+=(const Matrix &a_rhs);
	Matrix& operator+=(ElemType a_scaler);
	Matrix& operator-=(const Matrix &a_rhs);
	Matrix& operator-=(ElemType a_scaler);
	Matrix& operator*=(const Matrix &a_rhs);
	Matrix& operator*=(ElemType a_scaler);
	Matrix& operator/=(ElemType a_scaler);
		
    void Square();
    void Transpose();
    void Diagonal(ElemType a_value);
    void Print() const;
    
private:
    ElemType* At(size_t a_i, size_t a_j) const;  
    size_t Rows() const;
    size_t Columns() const;
    bool InRange(size_t a_i, size_t a_j) const;
    size_t Size() const;
    ElemType* Alloc(size_t a_rows, size_t a_columns);
    void Copy(const Matrix &a_matrix);
    void Copy(ElemType a_scaler);
    void Add(const Matrix &a_matrix);
    void Add(ElemType a_scaler);
    void Sub(const Matrix &a_matrix);
    void Sub(ElemType a_scaler);
    void Mul(const Matrix &a_matrix);
    void Mul(ElemType a_scaler);
    void Div(ElemType a_scaler);
    bool EqualTo(const Matrix &a_rhs) const;
    bool IsSameSize(const Matrix &a_rhs) const;
    bool IsNotSameSize(const Matrix &a_rhs) const;
    bool IsSquare() const ;
    bool CanBeMul(const Matrix &a_rhs) const;
    void TransposeSquare();
    void TransposeNotSquare();
    
private:
    Dimension m_dimension;
    ElemType *m_elements;
};


#endif /* MATRIX_HPP */

