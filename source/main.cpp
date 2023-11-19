#include "header.h"

using namespace std;

int main()
{
    bool DEBUG = false;

    vector<Card> deck = {};
    vector<Card> hand = {};
    vector<Card> table = {};
    int HANDS_IN_PLAY;

    initializeDeck(deck);

    if (DEBUG) {
        cout << "DEBUG MODE" << endl;
        HANDS_IN_PLAY = 1;
        preflop(deck, hand, "11d", "12d");
        flop(deck, table, "11c", "12h", "8h");
        turn(deck, table, "13h");
        river(deck, table, "7s");
    }
    else if (!DEBUG){
        HANDS_IN_PLAY = randomHandsInPlay();
        randomHandAndCommunityCards(hand, table, deck);
    }

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
    simulationHigherCard(100'000, highCard, deckValues, HANDS_IN_PLAY);

    return 0;
}