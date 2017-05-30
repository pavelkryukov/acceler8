#include "./matrix.h"

Matrix::Matrix(unsigned X, unsigned Y) : 
        std::vector<std::vector<TYPE> >(X, std::vector<TYPE>(Y, 0)),
        scoreBoard(new ScoreBoard(X, Y)),
        maxWidth(X),
        maxHeight(Y) {
}

Matrix::~Matrix() {
    delete scoreBoard;
}

void Matrix::FillRandom() {
    int l = 1;
    for (unsigned i = 0; i < maxHeight; i++) {
        for (unsigned j = 0; j < maxWidth; j++) {
            (*this)[j][i] = (l) * (l % 2 ? -1 : 1);
            ++l;
        }
    }
}
 
std::ostream & operator<< (std::ostream & out, const Matrix & item) {
    for (unsigned y = 0; y < item.maxHeight; y++) {
        for (unsigned x = 0; x < item.maxWidth; x++) { 
            out << item[x][y] << " ";
        }
        out << std::endl;
    }
    return out;
}