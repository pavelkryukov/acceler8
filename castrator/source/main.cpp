#include "./matrix.h"
#include "./submatrix.h"
#include "./result.h"

#include <iostream>

int main() {
    Matrix* matrix = new Matrix(3, 3);
    matrix->FillRandom();
    std::cout << *matrix << std::endl;
    
    SubMatrix* allMatrix = new SubMatrix(matrix);
    allMatrix->CreateChildren();
    
    while (1) { // FIXME condition is true, but final threads
                // have not finished yet.
        if (matrix->scoreBoard->IsFinished())
            break;
    }
    
    std::cout << *(SubMatrix::result) << std::endl;
    
    delete SubMatrix::result;
    delete allMatrix;
    delete matrix;
}
