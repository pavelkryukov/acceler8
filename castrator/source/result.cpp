#include "./result.h"

Result::Result(const SubMatrix & source) {
    this->_x1 = source._x1;
    this->_y1 = source._y1;
    this->_x2 = source._x2;
    this->_y2 = source._y2;
    this->_sum = source._sum;
}

void Result::SetAndCheck(const SubMatrix & source) {
    boost::mutex::scoped_lock lock(mutex, boost::defer_lock);
    lock.lock();
    if (this->_sum < source._sum){
        this->_x1 = source._x1;
        this->_y1 = source._y1;
        this->_x2 = source._x2;
        this->_y2 = source._y2;
        this->_sum = source._sum;
    }
    lock.unlock();
}


std::ostream & operator<< (std::ostream & out, const Result & item) {
    return out << item._x1 << " " << item._x2 << " " << item._y1 << " " << item._y2;
}