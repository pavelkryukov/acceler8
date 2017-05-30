#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <vector>

#include <boost/thread/mutex.hpp>

#include "./classes.h"

class ScoreBoard : private std::vector<std::vector<std::vector<std::vector<bool> > > > {
    mutable boost::mutex mutex;
    unsigned total;
    unsigned size;
  public:
    ScoreBoard(unsigned X, unsigned Y);
    bool CheckAndAdd(unsigned x1, unsigned y1, unsigned x2, unsigned y2);
    bool IsFinished() const;
};

#endif