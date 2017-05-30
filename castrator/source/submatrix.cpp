#include <boost/thread.hpp>

#include "./submatrix.h"
#include "./result.h"
#include "./matrix.h"

const Matrix* SubMatrix::Parent = 0;
Result* SubMatrix::result = 0;

SubMatrix::SubMatrix() {
}

SubMatrix::~SubMatrix() {
}

SubMatrix::SubMatrix(const Matrix* parent) {
    SubMatrix::Parent = parent;
    
    this->_x1 = 0;
    this->_y1 = 0;
    this->_x2 = parent->maxWidth;
    this->_y2 = parent->maxHeight;
    
    this->CountAllSum();
    
    Parent->scoreBoard->CheckAndAdd(_x1, _y1, _x2, _y2);
    
    result = new Result(*this);
}

SubMatrix::SubMatrix(const SubMatrix & source, Side side) {
    this->_x1 = source._x1;
    this->_y1 = source._y1;
    this->_x2 = source._x2;
    this->_y2 = source._y2;
    this->_sum = source._sum;
    
    switch (side) {
        case TOP:
            for (unsigned i = this->_x1; i < this->_x2; ++i) {
                _sum -= (*Parent)[i][_y1];
            }
            ++_y1;
            break;
        case BOTTOM:
            for (unsigned i = this->_x1; i < this->_x2; ++i) {
                _sum -= (*Parent)[i][_y2 - 1];
            }
            --_y2;
            break;
        case LEFT:
            for (unsigned i = this->_y1; i < this->_y2; ++i) {
                _sum -= (*Parent)[_x1][i];
            }
            ++_x1;
            break;
        case RIGHT:
            for (unsigned i = this->_y1; i < this->_y2; ++i) {
                _sum -= (*Parent)[_x2 - 1][i];
            }
            --_x2;
            break;
        default:
            break;
    }
}

void SubMatrix::CreateChild(Side side) {
    SubMatrix* child = new SubMatrix(*this, side);
    result->SetAndCheck(*child);
    child->CreateChildren();
    delete child;
}

void SubMatrix::CreateChildren() {
    if (_x2 - _x1 != 1) {
        if (!Parent->scoreBoard->CheckAndAdd(_x1 + 1, _y1, _x2, _y2)) {
           boost::thread t(&SubMatrix::CreateChild, *this, LEFT);
        }
        if (!Parent->scoreBoard->CheckAndAdd(_x1, _y1, _x2 - 1, _y2)) { 
           boost::thread t(&SubMatrix::CreateChild, *this, RIGHT);
        }
    }
    if (_y2 - _y1 != 1) {
        if (!Parent->scoreBoard->CheckAndAdd(_x1, _y1 + 1, _x2, _y2)) {
           boost::thread t(&SubMatrix::CreateChild, *this, TOP);
        }
        if (!Parent->scoreBoard->CheckAndAdd(_x1, _y1, _x2, _y2 - 1)) {
           boost::thread t(&SubMatrix::CreateChild, *this, BOTTOM);
        }
    }
}

void SubMatrix::CountAllSum() {
    this->_sum = 0;
    
    for (unsigned i = this->_x1; i < this->_x2; ++i) {
        for (unsigned j = this->_y1; j < this->_y2; ++j) {
            this->_sum += (*Parent)[i][j];
        }
    }
}