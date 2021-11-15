#include "test_generator.h"

void generatefile(int inputsize, int ops_before_expand, int ops_before_shrink, int rand_range, const string& filename) {
    int randomNumber;
    ofstream file;
    file.open(filename);
    for (int i = 0; i < inputsize; i++) {
        randomNumber = rand() % rand_range;
        file << "update " << randomNumber << endl;
        if (i != 0) {
            if (i % ops_before_expand == 0) {
                file << "expand" << endl;
            }
            if (i % ops_before_shrink == 0) {
                file << "shrink" << endl;
            }
        }
    }
}

void generatefile_random(int inputsize, int ops_before_expand, int ops_before_shrink, int rand_range, const string& filename) {
    int randomNumber;
    ofstream file;
    file.open(filename);
    for (int i = 0; i < inputsize; i++) {
        randomNumber = rand() % rand_range;
        file << "update " << randomNumber << endl;
        if (i != 0) {
            if (randomNumber % ops_before_expand == 0) {
                file << "expand" << endl;
            }
            if (randomNumber % ops_before_shrink == 0) {
                file << "shrink" << endl;
            }
        }
    }
}