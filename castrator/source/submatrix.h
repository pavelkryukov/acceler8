#ifndef SUBMATRIX_H
#define SUBMATRIX_H

#include <iostream>

#include "./classes.h"
#include "./side.h"

class SubMatrix {
  private:
    static const Matrix* Parent;        
    void CountAllSum();
  protected:
    unsigned _x1;
    unsigned _y1;
    unsigned _x2;
    unsigned _y2;    
    
    TYPE _sum;
  public:
    friend class Result;
  
    static Result* result;
  
    SubMatrix();
    SubMatrix(const Matrix* parent);
    SubMatrix(const SubMatrix & source, Side side);
    
    ~SubMatrix();
    
    void SetAll(const SubMatrix & from);
    friend void SetAll(const SubMatrix & from);
    
    void CreateChild(Side side);
    void CreateChildren();

    friend bool operator< (const Result & first, const SubMatrix & second);    
};        
  
#endif