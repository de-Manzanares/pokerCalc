// Calculate probability one hand in play being a 7 and 4

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

using namespace std;
//----------------------------------------------------------------------------------------------------------------------
// SIMULATION
//----------------------------------------------------------------------------------------------------------------------
void simulationSameHand(int SAMPLES, int targetValue1, int targetValue2) {
    random_device rd;
    mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    vector<int> randHand = {};
    int card;
    int index;
    int countSamples = 0;
    int countMatch = 0;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    targetValue1 = 7;
    targetValue2 = 4;
    for (int j = 0; j < SAMPLES; j++) {

        vector<int> unknown = {2, 2, 2, 2,
                               3, 3, 3, 3,
                               4, 4,
                               5, 5, 5, 5,
                               6, 6, 6, 6,
                               7, 7,
                               8, 8, 8, 8,
                               9, 9, 9, 9,
                               10, 10, 10,
                               11, 11, 11,
                               12, 12, 12, 12,
                               13, 13, 13,
                               14, 14, 14, 14};

        for (int i = 0; i < 2; i++) {
            uniform_int_distribution<> dis(0, 44 - i);
            index = dis(gen);
            card = unknown[index];
            randHand.push_back(card);
            unknown.erase(unknown.begin() + index);
        }

        if (find(randHand.begin(), randHand.end(), targetValue1) != randHand.end()
            && find(randHand.begin(), randHand.end(), targetValue2) != randHand.end()
                ) {
            countMatch++;
        }

        countSamples++;
        randHand.clear();
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Matches: " << countMatch << endl;
    cout << "Samples: " << countSamples << endl;
    cout << "Experimental Probability: " << ((double) countMatch * 100) / (double) countSamples << endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]"
              << std::endl;
}

void simulationHigherCard(int SAMPLES, int myHighCard, vector<int> &known) {
    cout << "\nMy high card: " << myHighCard << endl;
    cout << "Experimental probability that my opponent has a higher card: " << endl;
    random_device rd;
    mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    vector<int> randHand = {};
    int card;
    int index;
    int countSamples = 0;
    int countMatch = 0;

    vector<int> unknown = {2, 2, 2, 2,
                           3, 3, 3, 3,
                           4, 4, 4, 4,
                           5, 5, 5, 5,
                           6, 6, 6, 6,
                           7, 7, 7, 7,
                           8, 8, 8, 8,
                           9, 9, 9, 9,
                           10, 10, 10, 10,
                           11, 11, 11, 11,
                           12, 12, 12, 12,
                           13, 13, 13, 13,
                           14, 14, 14, 14};

    // remove known cards from unknown
    for (int i : known) {
        auto it = find(unknown.begin(), unknown.end(), i);
        if (it != unknown.end()) {
            unknown.erase(it);
        }
    }

    // To the deck in the loop
    vector<int> copy = unknown;

    int indexLimit = unknown.size() - 1;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int j = 0; j < SAMPLES; j++) {

        unknown = copy;

        for (int i = 0; i < 2; i++) {
            uniform_int_distribution<> dis(0,  indexLimit - i);
            index = dis(gen);
            card = unknown[index];
            randHand.push_back(card);
            unknown.erase(unknown.begin() + index);
        }

        if (randHand[0] > myHighCard || randHand[1] > myHighCard) {
            countMatch++;
        }

        countSamples++;
        randHand.clear();
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Matches: " << countMatch << endl;
    cout << "Samples: " << countSamples << endl;
    cout << "Experimental Probability: " << ((double) countMatch * 100) / (double) countSamples << endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms"
              << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
// ANALYTICAL
//----------------------------------------------------------------------------------------------------------------------

void analyticalHigherCard(int myHighCard, vector<int>& known){

}