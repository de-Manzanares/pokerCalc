#include "header.h"

using namespace std;

int main() {

    // simulation();

    vector<Card> holeCards[9];
    vector<Card> communityCards;
    vector<Card> deck;
    vector<Card> knownCards;
    vector<Hand> hands(9);
    int numberOfPlayers = 2;

    initializeDeck(deck);

    preflop(deck,holeCards[0],"5h","5c");
    preflop(deck, holeCards[1],"4c", "4h");
    flop(deck,communityCards,"4s","4d","5d");
    turn(deck,communityCards,"5s");
    river(deck, communityCards, "9c");

    // Populate known cards with community cards
    for (int i = 0; i < 5; i++) {
        knownCards.push_back(communityCards[i]);
    }

    for (int i = 0; i < numberOfPlayers; i++) {
        // Clear hole cards
        // Going to have to modify this based on stage of play.
        // TODO: > 3 flop, >4 turn, >5 river
        while (knownCards.size() > 5) {
            knownCards.pop_back();
        }

        // Populate known cards with hole cards
        for (int j = 0; j < 2; j++) {
            knownCards.push_back(holeCards[i][j]);
        }

        findHand_FourOfAKind(knownCards, hands, i);
    }

    return 0;
}

int mainOld() {

    vector<Card> deck = {};
    vector<Card> hand = {};
    vector<Card> table = {};
    int HANDS_IN_PLAY = 1;
    int SAMPLES = 100'000;

    vector<int> handValues;
    vector<int> tableValues;
    vector<int> deckValues;
    vector<int> handAndTableValues;
    int highCard;

    initializeDeck(deck);

    // Random
    // HANDS_IN_PLAY = randomHandsInPlay();
    // randomHandAndCommunityCards(hand, table, deck);

    // ----------------------------------
    // Preflop
    // ----------------------------------

    preflop(deck, hand, "13h", "12d");

    handValues = getValues(hand);
    tableValues = getValues(table);
    deckValues = getValues(deck);
    handAndTableValues = getValues(hand, table);
    highCard = myHighCard_fromCards(hand);

    cout << "\n---------------------------------------------------------------\n"
         << "Preflop\n";
    cout << "\nYour high card: " << highCard << endl;
    cout << "\nProbability that your high card is the highest card in play: \n";
    cout << "---------------------------------------------------------------\n" << endl;
    header(hand, table, deck, HANDS_IN_PLAY);

    analyticalHigherCard(handValues, tableValues, deckValues, HANDS_IN_PLAY);
    simulationHigherCard(SAMPLES, highCard, deckValues, HANDS_IN_PLAY);
    cout << endl << endl;

    // ----------------------------------
    // Flop
    // ----------------------------------

    flop(deck, table, "5s", "12c", "11d");

    cout << "\n---------------------------------------------------------------\n"
         << "Flop\n";
    cout << "\nYour high card: " << highCard << endl;
    cout << "\nProbability that your high card is the highest card in play: \n";
    cout << "---------------------------------------------------------------\n" << endl;

    handValues = getValues(hand);
    tableValues = getValues(table);
    deckValues = getValues(deck);
    handAndTableValues = getValues(hand, table);
    highCard = myHighCard_fromCards(hand);

    header(hand, table, deck, HANDS_IN_PLAY);

    analyticalHigherCard(handValues, tableValues, deckValues, HANDS_IN_PLAY);
    simulationHigherCard(SAMPLES, highCard, deckValues, HANDS_IN_PLAY);
    cout << endl << endl;

    // ----------------------------------
    // Turn
    // ----------------------------------

    turn(deck, table, "14h");

    cout << "\n---------------------------------------------------------------\n"
         << "Turn\n";
    cout << "\nYour high card: " << highCard << endl;
    cout << "\nProbability that your high card is the highest card in play: \n";
    cout << "---------------------------------------------------------------\n" << endl;

    handValues = getValues(hand);
    tableValues = getValues(table);
    deckValues = getValues(deck);
    handAndTableValues = getValues(hand, table);
    highCard = myHighCard_fromCards(hand);

    header(hand, table, deck, HANDS_IN_PLAY);

    analyticalHigherCard(handValues, tableValues, deckValues, HANDS_IN_PLAY);
    simulationHigherCard(SAMPLES, highCard, deckValues, HANDS_IN_PLAY);
    cout << endl << endl;

    // ----------------------------------
    // River
    // ----------------------------------

    river(deck, table, "9h");

    cout << "\n---------------------------------------------------------------\n"
         << "River\n";
    cout << "\nYour high card: " << highCard << endl;
    cout << "\nProbability that your high card is the highest card in play: \n";
    cout << "---------------------------------------------------------------\n" << endl;

    handValues = getValues(hand);
    tableValues = getValues(table);
    deckValues = getValues(deck);
    handAndTableValues = getValues(hand, table);
    highCard = myHighCard_fromCards(hand);

    header(hand, table, deck, HANDS_IN_PLAY);

    analyticalHigherCard(handValues, tableValues, deckValues, HANDS_IN_PLAY);
    simulationHigherCard(SAMPLES, highCard, deckValues, HANDS_IN_PLAY);
    cout << endl << endl;

    return 0;

    // Pair stuff
    /*
    vector<int> pair = getPair(handValues, tableValues);

    cout << "Your pair: " << pair[0] << " " << pair[1] << endl << endl;
    cout << "Probability that your pair is the highest in play:\n";
    cout << "---------------------------------------------------------------\n" << endl;
    //simulationPairOld(100'000);
    simulationPair(1'000'000, handValues, tableValues, deckValues,HANDS_IN_PLAY);
    analyticalPair(handValues, tableValues, deckValues, HANDS_IN_PLAY);
    */

}