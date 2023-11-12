#include "header.h"
#include <random>
#include <chrono>

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

void preflop (vector<Card> &deck, vector<Card> &hand, const string cardID_1, const string cardID_2) {

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

void flop (vector<Card>& deck, vector<Card>& table, const string cardID_1, const string cardID_2, const string cardID_3) {

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

void turn (vector<Card>& deck, vector<Card>& table, const string cardID_1) {

    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].id == cardID_1) {
            table.push_back(deck[i]);
            deck.erase(deck.begin() + i);
        }
    }
}

void river (vector<Card>& deck, vector<Card>& table, const string cardID_1) {

    for (int i = 0; i < deck.size(); i++) {
        if (deck[i].id == cardID_1) {
            table.push_back(deck[i]);
            deck.erase(deck.begin() + i);
        }
    }
}

void printCards (const vector<Card> &cards) {
    for (const auto & card : cards) {
        cout << card.id << " ";
    }
    cout << endl;
}

void getKnownValues (vector<int> &known, const vector<Card> &hand, const vector<Card> &table) {
    for (const auto & card : hand) {
        known.push_back(card.value);
    }
    for (const auto & card : table) {
        known.push_back(card.value);
    }
}

void randomHandAndCommunityCards(vector<Card> &hand, vector<Card> &table, vector<Card> &deck) {
    random_device rd;
    mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    int index;
    vector<Card> randoms = {};
    Card card;

    for (int i = 0; i < 2; i++) {
        uniform_int_distribution<> dis(0,  deck.size() - 1);
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

int myHighCard(vector<Card> hand){
    int highCard = 0;
    for (const auto & card : hand) {
        if (card.value > highCard) {
            highCard = card.value;
        }
    }
    return highCard;
}