//
// Created by tuuli on 03/01/2026.
//

#ifndef LAB8_COUNTER_CLASSES_H
#define LAB8_COUNTER_CLASSES_H

//COUNTER CLASS
class Counter{
public:
    Counter(int count, int upLimit);
    virtual ~Counter() = default;
    virtual void inc() = 0;
    virtual void dec() = 0;

    friend std::ostream& operator<<(std::ostream& out, const Counter& ctr);

protected:
    int count;
    const int upLimit;
};


//LIMITED COUNTER CLASS
class LimitedCounter : public Counter{
public:
    LimitedCounter(int initial, int limit);
    ~LimitedCounter() override = default;
    void inc() override;
    void dec() override;
private:
    //int count;
    //int upLimit;
};


//OVERFLOW COUNTER CLASS
class OverflowCounter : public Counter
{
public:
    OverflowCounter(int count, int limit);
    ~OverflowCounter() override = default;
    void inc() override;
    void dec() override;
private:
    //int count;
    //int upLimit;
};


//USE COUNTER FUNCTION
void UseCounter(Counter& ctr, int num);



#endif //LAB8_COUNTER_CLASSES_H
