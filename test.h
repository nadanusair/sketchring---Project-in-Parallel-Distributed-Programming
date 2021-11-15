#ifndef PROJECTMAKBELEMEVOZAR_TEST_H
#define PROJECTMAKBELEMEVOZAR_TEST_H
#include <map>
#include <vector>
#include "scketchRing.h"

using namespace std;

/*
 * Test is a class that aims to count the exact appearances of each item, in order to compare it with the results of
 * the sketch ring.
 * Class fields:
 * counter: it saves the exact appearances of each item, counter[element] = number of appearances of the element.
 * It's aim is to compare it with the results of the sketch ring, and use it to calculate the error and the accuracy.
 * num_elements: number of the elements.
 * */
template <class T>
class Test{
    std::map<T,int> counter;
    int num_elements;
public:
    Test() {
        num_elements = 0;
    }

    // adds another appearance for the element that it got as a parameter.
    void add(T element){
        this->num_elements++;
        typename std::map<T,int>::iterator it = this->counter.find(element);
        if (it == this->counter.end()){
            this->counter[element] = 1;
        }
        else {
            this->counter[element]++;
        }
    }

    // returns the real number of appearances of the element that it got as a parameter.
    int query(T element) {
        typename std::map<T,int>::iterator it = this->counter.find(element);
        if (it == this->counter.end()){
            return 0;
        }
        return this->counter[element];
    }

    /*
    * given a sketch ring the function returns:
    * sum on all elements of |real number of appearnaces - number of appearances that the sketch ring returned|
    * divided by the number of different elements
     * */
    double calculate_error(sketchRing<T> SR){
        typename std::map<T,int>::iterator it;
        double error = 0;
        for (it = this->counter.begin(); it != this->counter.end(); it++) {
            double acc1 = SR.Query(it->first) * this->num_elements;
            double acc2 = (it->second);
            if (acc1 > acc2) {
                error += (acc1 - acc2);
            }
            else {
                error += (acc2 - acc1);
            }
        }
        return error / counter.size();
    }
};
#endif //PROJECTMAKBELEMEVOZAR_TEST_H
