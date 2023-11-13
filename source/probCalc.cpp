// Calculate probability one hand in play being a 7 and 4

#include "header.h"
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

void simulationHigherCardOld(int SAMPLES, int myHighCard, vector<int>& deckValues, int handsInPlay)
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

    double probabilityLose = ((double) countMatch) / (double) countSamples;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Experimental   Win:  " << 1 - probabilityLose << endl;
    cout << "               Draw: " << endl;
    cout << "               Lose: " << probabilityLose;
    cout << endl;
    cout << "Matches: " << countMatch << endl;
    cout << "Samples: " << countSamples << endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms"
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
    int countHigher = 0;
    int countEqual = 0;
    bool foundHigher = false;
    bool foundEqual = false;

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

        // Find 1 higher card from the hands.
        foundHigher = false;
        for (int i = 0; i < handsInPlay; i ++) {
            for (int k = 0; k < 2; k ++) {
                if (hands[i][k] > myHighCard) {
                    if (! foundHigher) {
                        countHigher ++;
                        foundHigher = true;
                    }
                }
            }
        }

        // Find one equal card from the hands if
        // a higher card was not found.
        foundEqual = false;
        if (! foundHigher) {
            for (int i = 0; i < handsInPlay; i ++) {
                for (int k = 0; k < 2; k ++) {
                    if (hands[i][k] == myHighCard) {
                        if (! foundEqual) {
                            countEqual ++;
                            foundEqual = true;
                        }
                    }
                }
            }
        }

        countSamples ++;

        for (int i = 0; i < handsInPlay; i ++) {
            hands[i].clear();
        }
    }

    double probabilityLose = ((double) countHigher) / (double) countSamples;
    double probabilityDraw = ((double) countEqual) / (double) countSamples;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    cout << "Experimental   Win:  " << 1 - probabilityLose - probabilityDraw << endl;
    cout << "               Draw: " << probabilityDraw << endl;
    cout << "               Lose: " << probabilityLose;
    cout << endl;
    cout << "Higher : " << countHigher << endl;
    cout << "Equal  : " << countEqual << endl;
    cout << "Samples: " << countSamples << endl;
    std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms"
              << std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
// ANALYTICAL
//----------------------------------------------------------------------------------------------------------------------

void analyticalHigherCardOld(int myHighCard, vector<int>& table, vector<int>& deck, int handsInPlay)
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

    for (int i = 0; i < handsInPlay; i ++) {
        prob = prob * (p / q) * ((p - 1) / (q - 1));
        p = p - 2;
        q = q - 2;
    }

    cout << "Analytical:    Win:  " << prob << endl;
    cout << "               Draw: " << endl;
    cout << "               Lose: " << endl << endl;
}

void analyticalHigherCard(vector<int>& hand, vector<int>& table, vector<int>& deck, int handsInPlay)
{
    int higherCardsLeftInDeck;
    int equalCardsLeftInDeck = 4;
    int lowerCardsLeftInDeck = 0;
    int higherCardsOnTable = 0;
    double p;
    double q;
    double probabilityNotLose = 1;
    double probabilityDraw_1 = 1;
    double probabilityDraw;
    int deckSize = deck.size();

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    int highCard = myHighCard_fromValues(hand);

    // Count the higher cards on the table
    for (int i = 0; i < table.size(); i ++) {
        if (table[i] > highCard) {
            higherCardsOnTable ++;
        }
    }

    higherCardsLeftInDeck = ((14 - highCard) * 4 - higherCardsOnTable);

    p = deckSize - higherCardsLeftInDeck;
    q = deckSize;

    for (int i = 0; i < handsInPlay; i ++) {
        probabilityNotLose = probabilityNotLose * (p / q) * ((p - 1) / (q - 1));
        p = p - 2;
        q = q - 2;
    }

    for (int i = 0; i < hand.size(); i ++) {
        if (hand[i] == highCard) {
            equalCardsLeftInDeck --;
        }
    }
    for (int i = 0; i < table.size(); i ++) {
        if (table[i] == highCard) {
            equalCardsLeftInDeck --;
        }
    }

    lowerCardsLeftInDeck = deckSize - higherCardsLeftInDeck - equalCardsLeftInDeck;

    double eqEq;
    double eqLo;
    double LoEq;
    double eqEqEqLo;
    double eqEqLoLo;
    double eqLoLoLo;

    auto el = (double) equalCardsLeftInDeck;
    auto ll = (double) lowerCardsLeftInDeck;
    auto L = (double) deckSize;

    if (handsInPlay == 1) {
        eqEq = ((double) equalCardsLeftInDeck / deckSize) * (((double) equalCardsLeftInDeck - 1) / (deckSize - 1));
        eqLo = ((double) equalCardsLeftInDeck / deckSize) * ((double) lowerCardsLeftInDeck / (deckSize - 1));
        LoEq = ((double) lowerCardsLeftInDeck / deckSize) * ((double) (equalCardsLeftInDeck) / (deckSize - 1));
        probabilityDraw = eqEq + eqLo + LoEq;
    }

    else if (handsInPlay == 2) {
        eqEqEqLo = (4 * (el - 2) * (el - 1) * el * ll) / ((L - 3) * (L - 2) * (L - 1) * L);
        eqEqLoLo = (6 * (el - 1) * (ll - 1) * el * ll) / ((L - 3) * (L - 2) * (L - 1) * L);
        eqLoLoLo = (4 * (ll - 2) * (ll - 1) * el * ll) / ((L - 3) * (L - 2) * (L - 1) * L);
        probabilityDraw = eqEqEqLo + eqEqLoLo + eqLoLoLo;
    }

    else if (handsInPlay == 3) {
        eqEqEqLo = (20 * (el - 2) * (el - 1) * (ll - 2) * (ll - 1) * el * ll) / ((L - 5) * (L - 4) * (L - 3) * (L - 2) * (L - 1) * L);
        eqEqLoLo = (15 * (ll - 3) * (ll - 2) * (ll - 1) * (el - 1 ) * el * ll) / ((L - 5) * (L - 4) * (L - 3) * (L - 2) * (L - 1) * L);
        eqLoLoLo = (6 * (ll - 4) * (ll - 3) * (ll - 2) * (ll - 1) * el * ll) / ((L - 5) * (L - 4) * (L - 3) * (L - 2) * (L - 1) * L);
        probabilityDraw = eqEqEqLo + eqEqLoLo + eqLoLoLo;
    }

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Analytical:    Win:  " << probabilityNotLose - probabilityDraw << endl;
    cout << "               Draw: " << probabilityDraw << endl;
    cout << "               Lose: " << 1 - probabilityNotLose << endl;
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl << endl;
}
