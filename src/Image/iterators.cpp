#include <iostream>

using namespace std;

#include <vector>
#include <string>
#include <sstream>

template<typename Itr>
string to_string(Itr start, Itr end) {
    string result;
    ostringstream sresult;
    sresult << "[ ";
    for (Itr iterator = start; iterator < end; iterator++) {

        sresult << *iterator;
        sresult << " ";
    }

    sresult << "]";
    result = sresult.str();
    return result;

}

template<typename Itr, typename T>
int replace(Itr start, Itr end, const T &a, const T &b) {
    int counter = 0;
    for (Itr iterator = start; iterator < end; iterator++) {
        if (*iterator == a) *iterator = b;
        counter++;
    }
    return counter;
}