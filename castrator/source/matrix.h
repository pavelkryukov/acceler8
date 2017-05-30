#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

#include "./classes.h"
#include "./scoreboard.h"

class Matrix : public std::vector<std::vector<TYPE> > {
  public:
    ScoreBoard* const scoreBoard;
    const unsigned maxWidth;
    const unsigned maxHeight;
  
    // Constructor on sizes
    Matrix(unsigned X, unsigned Y);
    ~Matrix();
    
    // Filling with random values
    void FillRandom();

    friend std::ostream & operator<< (std::ostream & out, const Matrix & item);
};
    
#endif