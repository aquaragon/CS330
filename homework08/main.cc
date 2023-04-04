#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <getopt.h>
#include <omp.h>
#include "numlist.h"

const char* const short_opt = ":ht:s:y:o:";
const struct option long_opt[] = {
    {"help",           0, NULL, 'h'},
    {"test",           1, NULL, 't'},
    {"seed",           1, NULL, 's'},
    {"type",           1, NULL, 'y'},
    {"output",         1, NULL, 'o'},
    {NULL,             0, NULL,  0}
};


void usage(char* argv);
void unittest_sort(unsigned int num_test, unsigned int seed, ostream& to,
                   ImplType type);
// void my_qsort(vector<int>& keys, int low, int high);

/* Main function 
 */
int main(int argc, char **argv)
{
    int c = 0;
    string test = "0";
    string seed_str = "0"; 
    string ofile_name;
    string strtype = "ser";
    ImplType type = serial;

    if(argc < 2) {
        usage(argv[0]);
        return 0;
    }

    while((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {
        switch(c) {
            case 'h':
                usage(argv[0]);
                return 0;
            case 't':
                test = optarg;
                break;
            case 's':
                seed_str = optarg;
                break;
            case 'y':
                strtype = optarg;
                break;
            case 'o':
                ofile_name = optarg;
                break;
            default:
                usage(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Default partitioning stragegy is serial
    // However, if you specify -y but provide no selection, the program quits
    if(strtype.empty()) {
        cerr << "Partition type not specified" << endl;
        usage(argv[0]);
        return -1;
    } else {
        if(strtype == "par") {
            type = parallel;
        }
    }


    // Do the unit test
    unsigned int num_test = stoi(test);
    if(num_test > 0) {
        if(ofile_name.empty()) {
            unsigned int seed = stoi(seed_str);
            unittest_sort(num_test, seed, cout, type);
        } else {
            // Save the output to a file if -o was specified
            unsigned int seed = stoi(seed_str);
            ofstream outFile(ofile_name);
            unittest_sort(num_test, seed, outFile, type);
            outFile.close();
        }
    }


    return 0;
}


/* Print information on how to properly use this program
 */
void usage(char* call)
{
    cout << "Usage: " << call << endl;
    cout << "Options:" << endl;
    cout << "\t-h or --help            Display this information" << endl;
    cout << "\t-t or --test n          Sort Unit Test with n elements" << endl;
    cout << "\t-s or --seed n          Sort Unit Test with seed s" << endl;
    cout << "\t-y or --type <ser/par>  Use serial or parallel partition" << endl;
    cout << "\t-o or --output ofname   Output file" << endl;
}

/* Unit test function for sorting */
void unittest_sort(unsigned int num_test, unsigned int seed, ostream& to,
                   ImplType type)
{
    to << "Unit Test for quick sort" << endl;

    srand(seed);
    vector<int> keys;
    for(unsigned int i = 0; i < num_test; i++) {
        keys.push_back(rand() % num_test);
    }

    // Make a copy and sort it using C++ sort
    vector<int> keys_sorted = keys;
    sort(keys_sorted.begin(), keys_sorted.end());    

    // Quick sort the keys by creating a NumList object
    if(type == serial) { 
        to << "Serial partitioning used" << endl;
    } else {
        to << "Parallel partitioning used" << endl;
    }
    NumList my_list(keys, type);
    my_list.print(to);

    // Verify correctness
    unsigned int cnt = 0;
    for(unsigned int i = 0; i < num_test; i++) {
        if(my_list.get_elem(i) != keys_sorted[i]) {
            cnt++;
        }
    }
    to << "Error cnt: " << cnt << endl;  
}
