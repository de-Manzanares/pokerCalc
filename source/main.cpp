#include "header.h"

using namespace std;

int main()
{
    int HANDS_IN_PLAY = 1;

    vector<Card> deck = {};
    vector<Card> hand = {};
    vector<Card> table = {};

    initializeDeck(deck);

    randomHandAndCommunityCards(hand, table, deck);

    // preflop(deck, hand, "9c", "12d");
    // flop(deck, table, "6c", "10s", "13c");
    // turn(deck, table, "4s");
    // river(deck, table, "12h");

    cout << "Hand:  ";
    printCards(hand);
    cout << "Table: ";
    printCards(table);
    cout << "Deck:  " << deck.size() << " cards left" << endl;
    cout << "Hands in play: " << HANDS_IN_PLAY << endl;


    vector<int> handValues = getValues(hand);
    vector<int> tableValues = getValues(table);
    vector<int> deckValues = getValues(deck);
    vector<int> handAndTableValues = getValues(hand, table);

    cout << "\nYour high card: " << myHighCard(hand) << endl;
    cout << "\nProbability that your high card is the highest card in play: " << endl;

    analyticalHigherCard(myHighCard(hand), tableValues, deckValues);
    simulationHigherCard(1'000'000, myHighCard(hand), deckValues, HANDS_IN_PLAY);


    return 0;
}