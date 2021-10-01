#include <iostream>
#include <set>
#include <random>

#include <algorithm>

class DiscreteState {
protected:
    int const state;

public:
    DiscreteState(int state): state(state) { }

    bool contains(int s) const {
        return s == state;
    }
};

class SegmentState {
protected:
    int const beg, end;

public:
    SegmentState(): beg(0), end(-1) { } //constructor
    SegmentState(int beg, int end): beg(beg), end(end) { } //specific constructor

    bool contains(int s) const {
        return s >= beg && s <= end;
    }
};

class SetState {
private:
    std::set<int> const states;

public:
    SetState(): states() { }
    SetState(std::set<int> const &src): states(src) { }

    bool contains(int s) const {
        return states.count(s) > 0;
    }
};

class SegmentSpaceState: public SegmentState //объединение интервалов;
{
protected:
    std::vector<int> deleted_points;
public:
    SegmentSpaceState(): deleted_points() { } //constructor
    SegmentSpaceState(std::vector<int> del_points): deleted_points(del_points) { } //specific constructor
    bool contains(int s) const
    {
        return (s >= beg && s <= end)&&(std::find(deleted_points.begin(), deleted_points.end(), s) == deleted_points.end());
    }
};

class SegmentAdditionState: public SegmentState
{
protected:
    std::vector<int> additional_points;
public:
    SegmentAdditionState(): additional_points() { } //constructor
    SegmentAdditionState(std::vector<int> add_points): additional_points(add_points) { } //specific constructor
    bool contains(int s) const
    {
        return (s >= beg && s <= end)||(std::find(additional_points.begin(), additional_points.end(), s) != additional_points.end());
    }
};


class SegmentSpaceAdditionState: public SegmentSpaceState, public SegmentAdditionState
{
public:
    bool contains(int s) const
    {
        return ((s >= beg && s <= end)||(std::find(additional_points.begin(), additional_points.end(), s) != additional_points.end()))&&(std::find(deleted_points.begin(), deleted_points.end(), s) == deleted_points.end());
    }
};

class ProbabilityTest {
private:
    unsigned seed;
    int test_min, test_max;
    unsigned test_count;

public:
    ProbabilityTest(unsigned seed, int test_min, int test_max, unsigned test_count): seed(seed), test_min(test_min),test_max(test_max), test_count(test_count) { }

    float operator()(DiscreteState const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good)/static_cast<float>(test_count);
    }

    float operator()(SegmentState const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good)/static_cast<float>(test_count);
    }

    float operator()(SetState const &s) const {
        std::default_random_engine rng(seed);
        std::uniform_int_distribution<int> dstr(test_min,test_max);
        unsigned good = 0;
        for (unsigned cnt = 0; cnt != test_count; ++cnt)
            if (s.contains(dstr(rng))) ++good;

        return static_cast<float>(good)/static_cast<float>(test_count);
    }

    float operator() (SegmentSpaceState const& s) const
    float operator() (SegmentAdditionState const& s) const
    float operator() (SegmentSpaceAdditionState const& s) const

};

int main(int argc, const char * argv[]) {
    DiscreteState d(1);
    SegmentState s(0,10);
    SetState ss({1, 3, 5, 7, 23, 48, 57, 60, 90, 99});
    ProbabilityTest pt(10,0,100,100000);
    std::cout << pt(d) << std::endl;
    std::cout << pt(s) << std::endl;
    std::cout << pt(ss) << std::endl;
    return 0;
}

