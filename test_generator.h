#ifndef PROJECTMAKBELEMEVOZAR_TEST_GENERATOR_H
#define PROJECTMAKBELEMEVOZAR_TEST_GENERATOR_H
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

/*
 * input:
 * inputsize: number of elements that will be added to the sketch ring.
 * ops_before_expand: we'll add ops_before_expand elements to the sketch ring before an expand.
 * ops_before_shrink: we'll add ops_before_shrink elements to the sketch ring before a shrink.
 * rand_range: numbers between 0 and rand_range - 1.
 * filename: output's file name.
 * */
void generatefile(int inputsize, int ops_before_expand, int ops_before_shrink, int rand_range, const string& filename);

/*
 * input:
 * inputsize: number of elements that will be added to the sketch ring.
 * ops_before_expand: we'll add ops_before_expand elements to the sketch ring before an expand.
 * ops_before_shrink: we'll add ops_before_shrink elements to the sketch ring before a shrink.
 * rand_range: numbers between 0 and rand_range - 1.
 * filename: output's file name.
 * It's like the last function but it stochastically, we don't insert expand or shrink immediately, we generate
 * a random parameter and add expand if randomNumber % ops_before_expand == 0, same thing about shrink,
 * we add shrink if randomNumber % ops_before_shrink == 0.
 * */
void generatefile_random(int inputsize, int ops_before_expand, int ops_before_shrink, int rand_range, const string& filename);
#endif //PROJECTMAKBELEMEVOZAR_TEST_GENERATOR_H
