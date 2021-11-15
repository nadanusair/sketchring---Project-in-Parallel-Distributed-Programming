#ifndef PROJECTMAKBELEMEVOZAR_UF_H
#define PROJECTMAKBELEMEVOZAR_UF_H


#include "countmin/countmin.h"

template <class T>
class UF {
public:
    CM_type *sketch;
    int size;
    UF* left;
    UF* right;
    UF* parent;
    int min, max;
    bool isLastupper;
    bool isLastlower;
    int total_elements_number;

    UF(int Lowerbound,int Upperbound, double accuracy, double delta, int total_elements_number){
        min = Lowerbound;
        max = Upperbound;
        isLastupper = true;
        isLastlower = true;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        size = 0;
        this->total_elements_number = total_elements_number;
        sketch = CM_Init(4/(1-accuracy), log(1/delta), 42);
    }
    UF(int Lowerbound,int Upperbound, UF* p, double accuracy, double delta) {
        min = Lowerbound;
        max = Upperbound;
        isLastupper = true;
        isLastlower = true;
        left = nullptr; // lower
        right = nullptr; // higher
        parent = p;
        size = 0;
        total_elements_number = p->total_elements_number;
        sketch = CM_Init(4/(1-accuracy), log(1/delta), 42);
    }
    void insert(uint32_t p, T element){
        if(p<=(min+max)/2 && !isLastlower){
            this->left->insert(p, element);
            return;
        }
        if(p>(min+max)/2 && !isLastupper){
            this->right->insert(p, element);
            return;
        }
        CM_Update(sketch, element, 1);
        size++;
    }
    bool merge() {
        if(parent == nullptr){
            return false; // mutual father
        }
        if(this == parent->left) {
            parent->changeLastlower(true);
            isLastlower = false;
        }
        else if(this == parent->right) {
            parent->changeLastupper(true);
            isLastupper = false;
        }

        return true;
    }
    void expand(double accuracy, double delta) {
        if(left == nullptr && right==nullptr) {
            UF* newright = new UF((min + max) / 2 + 1, max, this, accuracy, delta);
            UF* newleft = new UF(min, (min + max) / 2, this, accuracy, delta);
            left = newleft;
            right = newright;
        }
        changeLastlower(false);
        changeLastupper(false);
        right->changeLastlower(true);
        right->changeLastupper(true);
        left->changeLastlower(true);
        left->changeLastupper(true);
    }
    UF* getsmallestleaf(){
        if (isLastupper && isLastlower)
            return this;
        if (!isLastlower && isLastupper)
            return this->left->getsmallestleaf();
        if (!isLastupper && isLastlower)
            return this->right->getsmallestleaf();
        UF* rightson = this->right->getsmallestleaf();
        UF* leftson = this->left->getsmallestleaf();
        if(rightson->size>leftson->size){
            return leftson;
        }
        return rightson;
    }
    UF* getbiggestleaf(){
        if (isLastupper && isLastlower)
            return this;
        if (!isLastlower && isLastupper)
            return this->left->getbiggestleaf();
        if (!isLastupper && isLastlower)
            return this->right->getbiggestleaf();
        UF* rightson = this->right->getbiggestleaf();
        UF* leftson = this->left->getbiggestleaf();
        if(rightson->size>leftson->size){
            return rightson;
        }
        return leftson;
    };
    int query(int p ,T element){
        if(left == nullptr && right == nullptr)
            return CM_PointEst(sketch, element);
        if(p > (min+max)/2) {
            return CM_PointEst(sketch, element) + this->right->query(p, element);
        }
        else{
            return CM_PointEst(sketch, element) + this->left->query(p, element);
        }

    }
    int getsize(){
        return this->size;
    }
    int getlowerbound(){
        return min;
    }
    int getUpperbound(){
        return max;
    }
    void changeLastlower(bool flag) {
        this->isLastlower = flag;
    }
    void changeLastupper(bool flag) {
        this->isLastupper = flag;

    }
};

#endif //PROJECTMAKBELEMEVOZAR_UF_H
