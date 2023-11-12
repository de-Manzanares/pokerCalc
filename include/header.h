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

void initializeDeck(vector<Card> &deck);
void preflop(vector<Card> &deck, vector<Card> &hand, string cardID_1, string cardID_2);
void flop (vector<Card>& deck, vector<Card>& table, string cardID_1, string cardID_2, string cardID_3);
void turn (vector<Card>& deck, vector<Card>& table, string cardID_1);
void river (vector<Card>& deck, vector<Card>& table, string cardID_1);
void printCards (const vector<Card> &cards);

void getKnownValues (vector<int> &known, const vector<Card> &hand, const vector<Card> &table);

void randomHandAndCommunityCards(vector<Card> &hand, vector<Card> &table, vector<Card> &deck);

int myHighCard(vector<Card> hand);

void simulationSameHand(int SAMPLES, int targetValue1, int targetValue2);
void simulationHigherCard(int SAMPLES, int myHighCard, vector<int> &known);


#endif //POKERCALC_HEADER_H
