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
void simulationSameHand(int SAMPLES, int targetValue1, int targetValue2)
{
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
    for (int j = 0; j < SAMPLES; j ++) {

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

        for (int i = 0; i < 2; i ++) {
            uniform_int_distribution<> dis(0, 44 - i);
            index = dis(gen);
            card = unknown[index];
            randHand.push_back(card);
            unknown.erase(unknown.begin() + index);
        }

        if (find(randHand.begin(), randHand.end(), targetValue1) != randHand.end()
                && find(randHand.begin(), randHand.end(), targetValue2) != randHand.end()
                ) {
            countMatch ++;
        }

        countSamples ++;
        randHand.clear();
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Matches: " << countMatch << endl;
    cout << "Samples: " << countSamples << endl;
    cout << "Experimental Probability: " << ((double) countMatch * 100) / (double) countSamples << endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]"
              << std::endl;
}

void simulationHigherCard(int SAMPLES, int myHighCard, vector<int>& deckValues, int handsInPlay)
{
    random_device rd;
    mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    vector<int> randHand = {};
    int card;
    int index;
    int countSamples = 0;
    int countMatch = 0;

    vector<int> hands[handsInPlay];

    // To reset the deckValues in the loop
    vector<int> copy = deckValues;

    int indexLimit = deckValues.size() - 1;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for (int j = 0; j < SAMPLES; j ++) {

        // Reset deck
        deckValues = copy;
        int cardsDealt = 0;

        for (int i = 0; i < handsInPlay; i ++) {
            for (int k = 0; k < 2; k ++) {
                uniform_int_distribution<> dis(0, indexLimit - cardsDealt);
                index = dis(gen);
                card = deckValues[index];
                hands[i].push_back(card);
                deckValues.erase(deckValues.begin() + index);
                cardsDealt ++;
            }
        }

        bool found = false;
        for (int i = 0; i < handsInPlay; i ++) {
            for (int k = 0; k < 2; k ++) {
                if (hands[i][k] > myHighCard) {
                    if (! found) {
                        countMatch ++;
                        found = true;
                    }
                }
            }
        }

        countSamples ++;
        for (int i = 0; i < handsInPlay; i ++) {
            hands[i].clear();
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Experimental: " << 1 - ((double) countMatch) / (double) countSamples << endl;
    cout << "Matches: " << countMatch << endl;
    cout << "Samples: " << countSamples << endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms"
              << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
// ANALYTICAL
//----------------------------------------------------------------------------------------------------------------------

void analyticalHigherCard(int myHighCard, vector<int>& table, vector<int>& deck, int handsInPlay)
{
    int higherCardsLeftInDeck;
    int higherCardsOnTable = 0;

    // Count the higher cards on the table
    for (int i = 0; i < table.size(); i ++) {
        if (table[i] > myHighCard) {
            higherCardsOnTable ++;
        }
    }

    higherCardsLeftInDeck = ((14 - myHighCard) * 4 - higherCardsOnTable);

    double p = deck.size() - higherCardsLeftInDeck;
    double q = deck.size();
    double prob = 1;

    cout << "\nAnalytical:   ";
    for (int i = 0; i < handsInPlay; i ++) {
        prob = prob * (p / q) * ((p - 1) / (q - 1));
        p = p - 2;
        q = q - 2;
    }
    cout << prob << endl;
}