#include <iostream>
#include <set>
#include <random>
#include <fstream>
#include <vector>

#include <iostream>
#include <set>
#include <random>
#include <utility>
#include <chrono>
#include <fstream>
using namespace std;
class State
{
public:
    virtual bool contains(int s) const { return false; }
};

class DiscreteState : public State
{
private:
    int const state;
public:
    DiscreteState(int state) : state(state) { }
    bool contains(int s) const {return s == state;}
};

class SegmentState : public State
{
private:
    int const beg, end;
public:
    SegmentState(int beg, int end) : beg(beg), end(end) { }
    bool contains(int s) const {return s >= beg && s <= end;}
};

class SetState : public State
{
private:
    std::set<int> const states;
public:
    SetState(std::set<int> const& src) : states(src) { }
    bool contains(int s) const {return states.count(s) > 0;}
};


class ProbabilityTest {
    private:
        unsigned seed;
        int test_min, test_max;
        unsigned test_count;

    public:
        ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count):
            seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }

        float operator()(State const &s) const {
            std::default_random_engine rng(seed);
            std::uniform_int_distribution<int> dstr(test_min,test_max);
            unsigned good = 0;
            for (unsigned cnt = 0; cnt != test_count; ++cnt)
                if (s.contains(dstr(rng))) ++good;

            return static_cast<float>(good)/static_cast<float>(test_count);
        }

};

int main()
{
    DiscreteState d(20);
    SegmentState s(15,30);
    SetState ss({2, 4, 8, 22, 23, 24, 57, 66, 70, 78});
    ProbabilityTest pt(10,0,100,100000);
    std::cout << pt(d) << std::endl;
    std::cout << pt(s) << std::endl;
    std::cout << pt(ss) << std::endl;
}


