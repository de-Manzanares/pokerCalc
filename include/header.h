#ifndef POKERCALC_HEADER_H
#define POKERCALC_HEADER_H

#include <vector>
#include <iostream>

using namespace std;

struct Card {
    int value;
    char suit;
    string id;
};

void initializeDeck(vector<Card>& deck);

void preflop(vector<Card>& deck, vector<Card>& hand, string cardID_1, string cardID_2);

void flop(vector<Card>& deck, vector<Card>& table, string cardID_1, string cardID_2, string cardID_3);

void turn(vector<Card>& deck, vector<Card>& table, string cardID_1);

void river(vector<Card>& deck, vector<Card>& table, string cardID_1);

void printCards(const vector<Card>& cards);

vector<int> getValues(const vector<Card>& deck_1);

vector<int> getValues(const vector<Card>& deck_1, const vector<Card>& deck_2);

void randomHandAndCommunityCards(vector<Card>& hand, vector<Card>& table, vector<Card>& deck);

int myHighCard(vector<Card> hand);

void simulationSameHand(int SAMPLES, int targetValue1, int targetValue2);

void simulationHigherCard(int SAMPLES, int myHighCard, vector<int>& deckValues, int handsInPlay);

void analyticalHigherCard(int myHighCard, vector<int>& table, vector<int>& deck, int handsInPlay);

#endif //POKERCALC_HEADER_H
