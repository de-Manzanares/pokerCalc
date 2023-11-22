#include "header.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <gmp.h>
#include <gmpxx.h>

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

void simulationHigherCard(int SAMPLES, int myHighCard, vector<int> &deckValues, int handsInPlay) {
    random_device rd;
    mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
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
    for (int j = 0; j < SAMPLES; j++) {

        // Reset deck
        deckValues = copy;
        int cardsDealt = 0;

        // Deal the hands
        for (int i = 0; i < handsInPlay; i++) {
            for (int k = 0; k < 2; k++) {
                uniform_int_distribution<> dis(0, indexLimit - cardsDealt);
                index = dis(gen);
                card = deckValues[index];
                hands[i].push_back(card);
                deckValues.erase(deckValues.begin() + index);
                cardsDealt++;
            }
        }

        // Find 1 higher card from the hands.
        foundHigher = false;
        for (int i = 0; i < handsInPlay; i++) {
            for (int k = 0; k < 2; k++) {
                if (hands[i][k] > myHighCard) {
                    if (!foundHigher) {
                        countHigher++;
                        foundHigher = true;
                    }
                }
            }
        }

        // Find one equal card from the hands if
        // a higher card was not found.
        foundEqual = false;
        if (!foundHigher) {
            for (int i = 0; i < handsInPlay; i++) {
                for (int k = 0; k < 2; k++) {
                    if (hands[i][k] == myHighCard) {
                        if (!foundEqual) {
                            countEqual++;
                            foundEqual = true;
                        }
                    }
                }
            }
        }

        countSamples++;

        for (int i = 0; i < handsInPlay; i++) {
            hands[i].clear();
        }
    }

    // reset deck for next simulation
    deckValues = copy;

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

void simulationPairOld(int SAMPLES) {
    random_device rd;
    mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    vector<Card> deck = {};
    vector<int> handValues = {};
    vector<int> tableValues = {};
    int card;
    int index;
    int countSamples = 0;
    int countPair = 0;

    // Create full deck of cards, make list of values
    initializeDeck(deck);
    vector<int> deckValues = getValues(deck);
    int indexLimit = deckValues.size() - 1;

    // To reset the deckValues in the loop
    vector<int> copy = deckValues;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int j = 0; j < SAMPLES; j++) {

        // Reset deck, hole cards, and table
        deckValues = copy;
        handValues = {};
        tableValues = {};
        int cardsDealt = 0;

        // Deal hole cards
        for (int i = 0; i < 2; i++) {
            uniform_int_distribution<> dis(0, indexLimit - cardsDealt);
            index = dis(gen);
            card = deckValues[index];
            handValues.push_back(card);
            deckValues.erase(deckValues.begin() + index);
            cardsDealt++;
        }

        // Deal community cards
        for (int i = 0; i < 5; i++) {
            uniform_int_distribution<> dis(0, indexLimit - cardsDealt);
            index = dis(gen);
            card = deckValues[index];
            tableValues.push_back(card);
            deckValues.erase(deckValues.begin() + index);
            cardsDealt++;
        }

        // Check for pair
        if (getPair_bool(handValues, tableValues)) {
            countPair++;
        }

        countSamples++;
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    cout << "Frequency : " << (double) countPair / countSamples << endl;
    cout << "Pair found: " << countPair << endl;
    cout << "Samples   : " << countSamples << endl;
    cout << "Time:  " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms"
         << std::endl;
}

void simulationPair(int SAMPLES, vector<int> &handValues, vector<int> &tableValues, vector<int> &deckValues,
                    int handsInPlay) {
    random_device rd;
    mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    vector<int> hands[handsInPlay];
    vector<int> myPair = getPair(handValues, tableValues);
    vector<int> theirPair = {};
    vector<int> temp = {};
    int card;
    int index;
    int countSamples = 0;
    int countNoOtherPairs = 0;
    int countLowerPair = 0;
    int countEqualPair = 0;
    int countHigherPair = 0;
    double probabilityLose;
    double probabilityDraw;

    // To reset the deckValues in the loop
    vector<int> copy = deckValues;

    int indexLimit = deckValues.size() - 1;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    for (int j = 0; j < SAMPLES; j++) {

        // Reset deck and opponent hole cards
        deckValues = copy;
        int cardsDealt = 0;
        theirPair = {0, 0};
        temp = {0, 0};
        for (int i = 0; i < handsInPlay; i++) {
            hands[i].clear();
        }

        // Deal the hands
        for (int i = 0; i < handsInPlay; i++) {
            for (int k = 0; k < 2; k++) {
                uniform_int_distribution<> dis(0, indexLimit - cardsDealt);
                index = dis(gen);
                card = deckValues[index];
                hands[i].push_back(card);
                deckValues.erase(deckValues.begin() + index);
                cardsDealt++;
            }
        }

        // Find the highest pair from the opponents hands
        for (int i = 0; i < handsInPlay; i++) {
            temp = getPair(hands[i], tableValues);
            if (temp[0] > theirPair[0]) {
                theirPair = temp;
                // cout << "Hand " << i << ": " << theirPair[0] << " " << theirPair[1] << endl;
            }
        }

        // Compare to your pair
        if (theirPair[0] == 0) {
            countNoOtherPairs++;
        } else if (theirPair[0] < myPair[0]) {
            countLowerPair++;
        } else if (theirPair[0] == myPair[0]) {
            countEqualPair++;
        } else if (theirPair[0] > myPair[0]) {
            countHigherPair++;
        }
        countSamples++;
    }

    // Reset deck for next simulation
    deckValues = copy;

    probabilityLose = (double) countHigherPair / countSamples;
    probabilityDraw = (double) countEqualPair / countSamples;

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    cout << "Experimental   Win:  " << 1 - probabilityLose - probabilityDraw << endl;
    cout << "               Draw: " << probabilityDraw << endl;
    cout << "               Lose: " << probabilityLose;
    cout << endl << endl;

    cout << "Higher Pair  : " << countHigherPair << endl
         << "Equal Pair   : " << countEqualPair << endl
         << "Lower Pair   : " << countLowerPair << endl
         << "No Pair      : " << countNoOtherPairs << endl
         << "Samples      : " << SAMPLES << endl
         << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms"
         << std::endl;
}

void simulationHighCardWithRiver() {

}
//----------------------------------------------------------------------------------------------------------------------
// ANALYTICAL
//----------------------------------------------------------------------------------------------------------------------

void analyticalPair(vector<int> &hand, vector<int> &table, vector<int> &deck, int handsInPlay) {
    int deckSize = deck.size();
    int equalCardsLeftInDeck = 4;
    int higherCardsLeftInDeck;
    int higherCardsOnTable = 0;
    int lowerCardsLeftInDeck = 0;
    double probabilityDraw = 0;
    double probabilityNotLose = 1;
    vector<int> myPair = getPair(hand, table);

    // for concise expressions
    double p;
    double q;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    // -----------------------------------------------
    // Calculate the probability of losing
    // -----------------------------------------------

    // Count the higher cards on the table
    for (int i = 0; i < table.size(); i++) {
        if (table[i] > myPair[0]) {
            higherCardsOnTable++;
        }
    }

    // Calculate higher cards left in deck
    higherCardsLeftInDeck = ((14 - myPair[0]) * 4 - higherCardsOnTable);

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    // Output
    cout << "Analytical     Win:  " << probabilityNotLose - probabilityDraw << endl
         << "               Draw: " << probabilityDraw << endl
         << "               Lose: " << 1 - probabilityNotLose << endl;
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl << endl;

}

void analyticalHigherCard(vector<int> &hand, vector<int> &table, vector<int> &deck, int handsInPlay) {
    int deckSize = deck.size();
    int equalCardsLeftInDeck = 4;
    int higherCardsLeftInDeck;
    int higherCardsOnTable = 0;
    int lowerCardsLeftInDeck = 0;
    double probabilityDraw = 0;
    double probabilityNotLose = 1;

    // For concise expressions
    double p;
    double q;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    // -----------------------------------------------
    // Calculate the probability of not losing
    // -----------------------------------------------

    int highCard = myHighCard_fromValues(hand);

    // Count the higher cards on the table
    for (int i = 0; i < table.size(); i++) {
        if (table[i] > highCard) {
            higherCardsOnTable++;
        }
    }

    // Calculate higher cards left in deck
    higherCardsLeftInDeck = ((14 - highCard) * 4 - higherCardsOnTable);

    // For concise expressions
    p = deckSize - higherCardsLeftInDeck;
    q = deckSize;

    // Probability of not losing
    for (int i = 0; i < handsInPlay; i++) {
        probabilityNotLose = probabilityNotLose * (p / q) * ((p - 1) / (q - 1));
        p = p - 2;
        q = q - 2;
    }

    // -----------------------------------------------
    // Calculate the probability of drawing
    // -----------------------------------------------

    for (int i = 0; i < hand.size(); i++) {
        if (hand[i] == highCard) {
            equalCardsLeftInDeck--;
        }
    }
    for (int i = 0; i < table.size(); i++) {
        if (table[i] == highCard) {
            equalCardsLeftInDeck--;
        }
    }

    // Count the lower cards left in the deck
    lowerCardsLeftInDeck = deckSize - higherCardsLeftInDeck - equalCardsLeftInDeck;

    int a = handsInPlay * 2;
    int b = 3;
    int c = a - b;
    int e = equalCardsLeftInDeck;
    int l = lowerCardsLeftInDeck;
    int L = deckSize;
    double quotient_D;

    mpf_t prod_e;           // to store \prod_{j=0}^{b-i-1} (e-j)
    mpf_t prod_l;           // to store \prod_{k=0}^{c+i-1} (l-k)
    mpf_t prod_L;           // to store \prod_{m=0}^{a-1}   (L-m)
    mpf_t numerator;        // to store a! * prod_e * prod_l
    mpf_t denominator;      // to store (b-i)! * (c+i)! * prod_L
    mpf_t quotient;         // to store numerator/denominator
    mpf_t aFac;
    mpf_t bFac;
    mpf_t cFac;

    mpf_init(prod_e);
    mpf_init(prod_l);
    mpf_init(prod_L);
    mpf_init(numerator);
    mpf_init(denominator);
    mpf_init(quotient);
    mpf_init(aFac);
    mpf_init(bFac);
    mpf_init(cFac);

    // begin sigma loop
    for (int i = 0; i < b; i++) {

        // product loop for equal cards
        mpf_set_ui(prod_e, 1);  // reset
        for (int j = 0; j <= (b - i - 1); j++) {
            mpf_mul_ui(prod_e, prod_e, (e - j));
            // for debugging
            // cout << "prod_e: " << prod_e << endl;
        }

        // product loop lower cards
        mpf_set_ui(prod_l, 1);  // reset
        for (int k = 0; k <= (c + i - 1); k++) {
            mpf_mul_ui(prod_l, prod_l, (l - k));
            // for debugging
            // cout << "prod_l: " << prod_l << endl;
        }

        // product loop cards left in deck
        // prod_L = 1; // reset
        mpf_set_ui(prod_L, 1);
        for (int m = 0; m <= (a - 1); m++) {
            mpf_mul_ui(prod_L, prod_L, (L - m));
            // for debugging
            // cout << "prod_L: " << prod_L << endl;
        }

        // Calculate factorials
        factorial_mpf(a, aFac);
        factorial_mpf(b - i, bFac);
        factorial_mpf(c + i, cFac);

        // a! * prod_e * prod_l
        mpf_mul(numerator, prod_e, prod_l);
        mpf_mul(numerator, aFac, numerator);

        // (b-i)! * (c+i)! * prod_L
        mpf_mul(denominator, bFac, cFac);
        mpf_mul(denominator, denominator, prod_L);

        // quotient
        mpf_div(quotient, numerator, denominator);
        quotient_D = mpf_get_d(quotient);

        // store the cumulative sum
        probabilityDraw += quotient_D;
    }

    // free memory
    mpf_clear(prod_e);
    mpf_clear(prod_l);
    mpf_clear(prod_L);
    mpf_clear(numerator);
    mpf_clear(denominator);
    mpf_clear(quotient);
    mpf_clear(aFac);
    mpf_clear(bFac);
    mpf_clear(cFac);

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Analytical     Win:  " << probabilityNotLose - probabilityDraw << endl
         << "               Draw: " << probabilityDraw << endl
         << "               Lose: " << 1 - probabilityNotLose << endl;
    // for checking precision
    // cout << "a = " << a << endl;
    // cout << "b = " << b << endl;
    // cout << "e = " << e << endl;
    // cout << "l = " << l << endl;
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << " ms" << endl << endl;
}
