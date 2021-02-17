#pragma once

#include <assert.h>
#include <set>
#include <deque>

// Worklist with "first in first out" order.
// New nodes pushed at back and popped from front.
// Elements in the list are unique as they're recorded by set.
template <typename Data>
class Worklist {
public:
    Worklist();
    inline void push(Data data);
    inline Data pop();
    inline unsigned int size() const;
    inline bool empty() const;
    inline void clear();

private:
    using DataSet = std::set<Data>;
    using DataList = std::deque<Data>;

    DataSet set;
    DataList list;
};

template <typename Data>
Worklist<Data>::Worklist() {}

/**
 *  Push data into back of worklist.
 *  
 *  @param data The data pushed into worklist.
 */
template <typename Data>
void
Worklist<Data>::push(Data data)
{
    if (set.find(data) == set.end()) {  // New data
        set.insert(data);
        list.push_back(data);
    }
}

/**
 *  Pop data at front from worklist.
 *  
 *  @return The data popped from worklist.
 */
template <typename Data>
Data
Worklist<Data>::pop()
{
    assert(!empty() && "list is empty");

    Data data = list.front();
    list.pop_front();
    set.erase(data);
    return data;
}

/**
 *  Return the size of worklist.
 *
 *  @return The size of worklist.
 */
template <typename Data>
unsigned int
Worklist<Data>::size() const
{
    return list.size();
}

/**
 *  Return whether worklist is empty or not.
 *
 *  @return Whether worklist is empty or not.
 */
template <typename Data>
bool
Worklist<Data>::empty() const
{
    return list.empty();
}

/**
 *  Clear all elements of worklist.
 */
template <typename Data>
void
Worklist<Data>::clear()
{
    list.clear();
    set.clear();
}