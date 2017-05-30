#include "./scoreboard.h"

ScoreBoard::ScoreBoard(unsigned X, unsigned Y) : 
    std::vector<
        std::vector<
            std::vector<
                std::vector<bool> > > >
                (X, std::vector<std::vector<std::vector<bool> > >(Y)) {
    total = 0;
    size = 0;
    for (unsigned x = 0; x < X; ++x) {
        for (unsigned y = 0; y < Y; ++y) {
            (*this)[x][y].resize(X - x, std::vector<bool>(Y - y, false));
            size += (X - x) * (Y - y);
        }
    }
}

bool ScoreBoard::CheckAndAdd(unsigned x1, unsigned y1, unsigned x2, unsigned y2) {
    boost::mutex::scoped_lock lock(mutex, boost::defer_lock);
    lock.lock();
    if ((*this)[x1][y1][x2 - x1 - 1][y2 - y1 - 1]) { 
        lock.unlock();
        return true;
    }
    else {
        ++total;
        (*this)[x1][y1][x2 - x1 - 1][y2 - y1 - 1] = true;
        lock.unlock();
        return false;
    }
}

bool ScoreBoard::IsFinished() const {
    boost::mutex::scoped_lock lock(mutex, boost::defer_lock);
    lock.lock();
    return total == size;
    lock.unlock();
}