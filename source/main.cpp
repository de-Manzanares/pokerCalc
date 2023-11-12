#include "header.h"

using namespace std;

int main() {

    vector<Card> deck = {};
    vector<Card> hand = {};
    vector<Card> table = {};

    initializeDeck(deck);

    //randomHandAndCommunityCards(hand, table, deck);

    preflop(deck, hand,"9c", "12d");
    flop(deck, table, "6c", "10s", "13c");
    turn(deck, table,"4s");
    river(deck, table, "12h");

    printCards(hand);
    printCards(table);
    printCards(deck);

    vector<int> known;
    getKnownValues(known, hand, table);

    simulationHigherCard(10'000'000, myHighCard(hand), known);

    return 0;
}