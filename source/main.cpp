#include "header.h"

using namespace std;

int main()
{
    int HANDS_IN_PLAY = 2;

    vector<Card> deck = {};
    vector<Card> hand = {};
    vector<Card> table = {};

    initializeDeck(deck);

    randomHandAndCommunityCards(hand, table, deck);

    // preflop(deck, hand, "6c", "7s");
    // flop(deck, table, "2h", "13h", "6d");
    // turn(deck, table, "12s");
    // river(deck, table, "12c");

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

    int highCard = myHighCard_fromCards(hand);

    cout << "\nYour high card: " << highCard << endl;
    cout << "\nProbability that your high card is the highest card in play: \n" << endl;

    analyticalHigherCard(handValues, tableValues, deckValues, HANDS_IN_PLAY);
    simulationHigherCard(1'000'000'000, highCard, deckValues, HANDS_IN_PLAY);

    return 0;
}