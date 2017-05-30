#ifndef RESULT_H
#define RESULT_H

#include <boost/thread/mutex.hpp>

#include "./classes.h"
#include "./submatrix.h"

class Result : public SubMatrix {
  private:
    boost::mutex mutex;
  public:
    explicit Result(const SubMatrix & source);
    void SetAndCheck(const SubMatrix & source);
    friend bool operator< (const Result & first, const SubMatrix & second);    
    friend std::ostream & operator<< (std::ostream & out, const Result & item);
};

#endif