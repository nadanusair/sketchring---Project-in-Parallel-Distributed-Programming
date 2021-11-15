#include <iostream>
#include <string>
#include <string.h>
#include "test.h"
#include "test_generator.h"
using namespace std;

/* argv[1]: input file name
 * argv[2]: output file name
 * argv[3]: initial number of sketches
 * argv[4]: initial accuracy
 * argv[5]: initial delta
 * argv[6]: maximal number of sketches
 * argv[7]: total number of elements
 * argv[8]: if it's testing mode or not
 * */
int main(int argc, char **argv)
{
    ofstream fout;
    ifstream fin;
    std::string line;
    int initial_k = std::atoi(string(argv[3]).c_str()), max_sketches = std::atoi(string(argv[6]).c_str()),
    total_number_elements = std::atoi(string(argv[7]).c_str());
    double accuracy = std::stof(string(argv[4])), delta =std::stof(string(argv[5]));

    //true when we want to test the accuracy of the current input, false when not.
    bool is_testing = false;
    if (argc > 7) {
        if (strcmp(string(argv[8]).c_str(), "true") == 0)
            is_testing = true;
        if (strcmp(string(argv[8]).c_str(), "false") == 0)
            is_testing = false;
    }
    Test<int> test;
    sketchRing<int>SR = sketchRing<int>(initial_k, 1 -accuracy, delta, max_sketches, total_number_elements);
    int input_number;

    fout.open(string(argv[2]));
    if (!fout)
        return -1;

    fin.open(string(argv[1]));
    if (!fin) {
        fout.close();
        return -1;
    }

    while (true) {
        std::getline(fin, line);
        if(fin.eof())
            break;
        if (line.substr(0,6) == "update") {
            line = line.substr(7, line.size() - 7);
            input_number = std::atoi(line.c_str());
            SR.Update(input_number);
            if (is_testing) {
                test.add(input_number);
            }
        }
        if (line.substr(0,5) == "query") {
            string sub_line = line.substr(6, line.size() - 6);
            input_number = std::atoi(sub_line.c_str());
            std::string occur = std::to_string(SR.Query(input_number));
            fout << "Frequency of " << input_number << " is: " << occur << endl;
        }
        if (line.substr(0,6) == "shrink") {
            SR.Shrink();
            fout << "Shrinked" << endl;
        }
        if (line.substr(0,6) == "expand") {
            SR.Expand();
            fout << "Expanded" << endl;
        }
    }

    if(is_testing) {
        double error = 0;
        error = test.calculate_error(SR);
        ofstream err;
        err.open("error.txt");
        if (!err) {
            return -1;
        }
        err << error;
        err.close();
    }
    fout.close();
    fin.close();
    return 0;
}
