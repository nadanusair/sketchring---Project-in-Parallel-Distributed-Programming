#ifndef PROJECTMAKBELEMEVOZAR_SKETCHRING_H
#define PROJECTMAKBELEMEVOZAR_SKETCHRING_H

#include <list>
#include <vector>
#include "xxhash/xxhash32.h"
#include <math.h>
#include <cmath>
#include "UF.h"

using namespace std;

template <class T>
class sketchRing {
    int max_sketch;
    int numberSketches;
    int num_elements;
    std::vector<UF<T>*> sketches;
    double accuracy;
    double delta;
    int total_number_elements;
    XXHash32 xxhash;
public:
    sketchRing(int initialk, double accuracy, double delta, int max_sketch, int total_number_elements) : xxhash(XXHash32(42)){
        this->max_sketch = max_sketch;
        this->numberSketches = initialk;
        this->num_elements = 0;
        for (int i = 0; i < initialk; i++){
            if (i == initialk - 1)
                this->sketches.push_back(new UF<T>((max_sketch / initialk)*i,max_sketch - 1, accuracy, delta, total_number_elements));
            else
                this->sketches.push_back(new UF<T>((max_sketch / initialk)*i, (max_sketch / initialk)*(i+1) - 1, accuracy, delta, total_number_elements));
        }
        this->accuracy = accuracy;
        this->delta = delta;
        this->total_number_elements = total_number_elements;
    }
    void Update(T element) {
        uint32_t result2 = this->xxhash.hash(&element, sizeof(T), 42) % this->max_sketch;
        for (int i = 0; i < sketches.size(); i++) {
            if(sketches[i]->getlowerbound() <= result2 && sketches[i]->getUpperbound() >= result2) {
                sketches[i]->insert(result2, element);
                break;
            }
        }
        this->num_elements++;
    }
    double Query (const T element) {
        uint32_t result2 = this->xxhash.hash(&element, sizeof(T), 42) % this->max_sketch;
        for (int i = 0; i < sketches.size(); i++) {
            if(sketches[i]->getlowerbound() <= result2 && sketches[i]->getUpperbound() >= result2) {
                return sketches[i]->query(result2, element) / (double)this->num_elements;
            }
        }
    }
    void Shrink() {
        if (numberSketches == 1)
            return;
        UF<T>* toshrink = sketches[0]->getsmallestleaf();
        int index = 0;
        for (int i = 1 ; i<sketches.size() ; i++){
            UF<T>* temp = sketches[i]->getsmallestleaf();
            if(toshrink->getsize() > temp->getsize()) {
                toshrink = temp;
                index = i;
            }
        }
        double error = (1 - this->accuracy) * 2;
        this->accuracy = 1 - error;
        if (this->accuracy < 0)
            this->accuracy = 0.2;
        bool flag = toshrink->merge();
        if(!flag){
            int tomerge = index - 1;
            if (index == 0) {
                tomerge = 0;
                index = 1;
            }
            int min = sketches[tomerge]->getlowerbound();
            int max = sketches[index]->getUpperbound();
            UF<T>* father = new UF<T>(min, max, accuracy, delta, total_number_elements);
            father->left = sketches[tomerge];
            father->right = sketches[index];
            sketches[tomerge] = father;
            sketches.erase(sketches.begin() + index);
        }
        this->numberSketches--;
    }
    void Expand() {
        if (this->numberSketches == this->max_sketch)
            return;
        double error = 1 - this->accuracy;
        error *= this->numberSketches / (double) (this->numberSketches + 1);
        if (1 - error > this->accuracy) {
            this->accuracy = 1 - error;
            if (this->accuracy > 1)
                this->accuracy = 0.9999999;
        }
        this->numberSketches++;

        UF<T>* toexpand = sketches[0]->getbiggestleaf();
        int index = 0;
        for (int i = 1 ; i<sketches.size() ; i++){
            UF<T>* temp = sketches[i]->getbiggestleaf();
            if(toexpand->getsize() < temp->getsize()) {
                toexpand = temp;
            }
        }
        toexpand->expand(accuracy, delta);
    }
    int get_numberSketches() {
        return numberSketches;
    }
    double get_accuracy() {
        return this->accuracy;
    }
};

#endif //PROJECTMAKBELEMEVOZAR_SKETCHRING_H
