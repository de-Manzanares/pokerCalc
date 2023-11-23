#include "header.h"
#include <random>
#include <chrono>
#include <gmp.h>
#include <gmpxx.h>

void initializeDeck(vector<Card> &deck) {

    for (int i = 2; i < 15; i++) {
        for (int j = 0; j < 4; j++) {
            Card card{};
            card.value = i;
            switch (j) {
                case 0:
                    card.suit = 's';
                    break;
                case 1:
                    card.suit = 'h';
                    break;
                case 2:
                    card.suit = 'd';
                    break;
                case 3:
                    card.suit = 'c';
                    break;
            }
            card.id = to_string(i) + card.suit;
            deck.push_back(card);
        }
    }
}

void preflop(vector<Card> &deck, vector<Card> &hand, const string cardID_1, const string cardID_2) {

    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].id == cardID_1) {
            hand.push_back(deck[i]);
            deck.erase(deck.begin() + i);
        }
    }
    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].id == cardID_2) {
            hand.push_back(deck[i]);
            deck.erase(deck.begin() + i);
        }
    }
}

void
flop(vector<Card> &deck, vector<Card> &table, const string cardID_1, const string cardID_2, const string cardID_3) {

    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].id == cardID_1) {
            table.push_back(deck[i]);
            deck.erase(deck.begin() + i);
        }
    }
    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].id == cardID_2) {
            table.push_back(deck[i]);
            deck.erase(deck.begin() + i);
        }
    }
    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].id == cardID_3) {
            table.push_back(deck[i]);
            deck.erase(deck.begin() + i);
        }
    }
}

void turn(vector<Card> &deck, vector<Card> &table, const string cardID_1) {

    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].id == cardID_1) {
            table.push_back(deck[i]);
            deck.erase(deck.begin() + i);
        }
    }
}

void river(vector<Card> &deck, vector<Card> &table, const string cardID_1) {

    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].id == cardID_1) {
            table.push_back(deck[i]);
            deck.erase(deck.begin() + i);
        }
    }
}

void printCards(const vector<Card> &cards) {
    for (const auto &card: cards) {
        cout << card.id << " ";
    }
    cout << endl;
}

vector<int> getValues(const vector<Card> &deck_1) {
    vector<int> values;
    for (int i = 0; i < deck_1.size(); i++) {
        values.push_back(deck_1[i].value);
    }
    return values;
}

vector<int> getValues(const vector<Card> &deck_1, const vector<Card> &deck_2) {
    vector<int> values;
    for (const auto &card: deck_1) {
        values.push_back(card.value);
    }
    for (const auto &card: deck_2) {
        values.push_back(card.value);
    }
    return values;
}

int randomHandsInPlay() {
    random_device rd;
    mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution<> dis(1, 9);
    return dis(gen);
}

void randomHandAndCommunityCards(vector<Card> &hand, vector<Card> &table, vector<Card> &deck) {
    random_device rd;
    mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    int index;
    vector<Card> randoms = {};
    Card card;

    for (int i = 0; i < 2; i++) {
        uniform_int_distribution<> dis(0, deck.size() - 1);
        index = dis(gen);
        card = deck[index];
        hand.push_back(card);
        deck.erase(deck.begin() + index);
    }

    for (int i = 0; i < 5; i++) {
        uniform_int_distribution<> dis(0, deck.size() - 1);
        index = dis(gen);
        card = deck[index];
        table.push_back(card);
        deck.erase(deck.begin() + index);
    }
}

int myHighCard_fromCards(vector<Card> &hand) {
    int highCard = 0;
    for (const auto &card: hand) {
        if (card.value > highCard) {
            highCard = card.value;
        }
    }
    return highCard;
}

int myHighCard_fromValues(vector<int> &hand) {
    int highCard = 0;
    for (int i = 0; i < hand.size(); i++) {
        if (hand[i] > highCard) {
            highCard = hand[i];
        }
    }
    return highCard;
}

int factorial(int n) {
    int m = 1;

    if (n == 0 || n == 1) {
        m = 1;
    } else {
        // even
        if (!(n % 2)) {
            do {
                m = m * n * (n - 1);
                n = n - 2;
            } while (n > 1);
        }
            // odd
        else if (n % 2) {
            do {
                m = m * n * (n - 1);
                n = n - 2;
            } while (n > 2);
        }
    }
    return m;
}

void factorial_mpf(int n, mpf_t &result) {
    mpf_t factorial;
    mpf_init(factorial);
    mpf_set_ui(factorial, 1);

    if (n == 0 || n == 1) {
        mpf_set_ui(factorial, 1);
    } else {
        // even
        if (!(n % 2)) {
            do {
                mpf_mul_ui(factorial, factorial, n * (n - 1));
                n = n - 2;
            } while (n > 1);
        }
            // odd
        else if (n % 2) {
            do {
                mpf_mul_ui(factorial, factorial, n * (n - 1));
                n = n - 2;
            } while (n > 2);
        }
    }
    mpf_set(result, factorial);
}

vector<int> getPair(vector<int> handValues, vector<int> tableValues) {

    vector<int> pair = {0, 0};
    bool pairFound = false;


    // Check for pair in hole cards
    if (handValues[0] == handValues[1]) {
        pair = handValues;
        pairFound = true;
    }

    // Check for pair with community cards
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
            if (handValues[i] == tableValues[j] && handValues[i] > pair[0]) {
                pair[0] = handValues[i];
                pair[1] = tableValues[j];
                pairFound = true;
            }
        }
    }
    return pair;
}

bool getPair_bool(vector<int> handValues, vector<int> tableValues) {

    vector<int> pair = {0, 0};
    bool pairFound = false;

// Check for pair in hole cards
    if (handValues[0] == handValues[1]) {
        pair = handValues;
        pairFound = true;
    }

// Check for pair with community cards
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
            if (handValues[i] == tableValues[j] && handValues[i] > pair[0]) {
                pair[0] = handValues[i];
                pair[1] = tableValues[j];
                pairFound = true;
            }
        }
    }
    return pairFound;
}

void header(vector<Card> &hand, vector<Card> &table, vector<Card> &deck, int handsInPlay) {
    cout << "Hand:  ";
    printCards(hand);
    cout << "Table: ";
    printCards(table);
    cout << "Deck:  " << deck.size() << " cards left" << endl;
    cout << "Hands in play: " << handsInPlay << endl;
}

int findHand_FourOfAKind(vector<Card> knownCards, vector<Hand> &hands, int playerNumber) {
    // Count cards to find four of a kind
    int testCount = 0;
    int searchNumber;
    int startSearchAt;
    int count;
    bool fourOfAKindFound = false;
    vector<int> indices;

    for (int j = 0; j < 3; j++) {
        searchNumber = knownCards[j].value;
        startSearchAt = 1;
        count = 1;
        indices.clear();

        for (int k = startSearchAt; k < knownCards.size(); k++) {
            if (!fourOfAKindFound) {
                if (searchNumber == knownCards[k].value) {
                    count++;
                    indices.push_back(k);
                }
                if (count == 4) {
                    fourOfAKindFound = true;
                    testCount++;
                    hands[playerNumber].fourOfAKind = 1;
                    for (int i = 0; i<4; i++){
                        hands[playerNumber].fiveCards.push_back(knownCards[indices[i]]);
                    }
                }
            }
        }
    }
    return testCount;
}
