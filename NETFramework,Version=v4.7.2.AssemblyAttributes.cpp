//Header file
#pragma once

#ifndef SUDUKO_H
#define SUDUKO_H

#include <ctime>
#include <cstring> // For strcmp

const int MAXSIZE = 81;

struct Cell {
    int row;
    int col;

    bool operator==(const Cell& other) const {
        return row == other.row && col == other.col;
    }
};

template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node* next;

    Node(K k, V v) : key(k), value(v), next(nullptr) {}
};

template <typename K, typename V>
class HashMap {
private:
    Node<K, V>** table;

    int hashFunction(const K& key) const {
        // Hash function using the (row, col) values
        return (key.row * 9 + key.col) % MAXSIZE;
    }

public:
    HashMap() {
        table = new Node<K, V>* [MAXSIZE];
        for (int i = 0; i < MAXSIZE; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashMap() {
        for (int i = 0; i < MAXSIZE; ++i) {
            Node<K, V>* entry = table[i];
            while (entry != nullptr) {
                Node<K, V>* temp = entry;
                entry = entry->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(const K& key, const V& value) {
        int hash = hashFunction(key);
        Node<K, V>* entry = table[hash];
        Node<K, V>* prev = nullptr;

        while (entry != nullptr) {
            if (entry->key == key) {
                entry->value = value;
                return;
            }
            prev = entry;
            entry = entry->next;
        }

        Node<K, V>* newNode = new Node<K, V>(key, value);
        if (prev == nullptr) {
            table[hash] = newNode;
        }
        else {
            prev->next = newNode;
        }
    }

    bool get(const K& key, V& value) const {
        int hash = hashFunction(key);
        Node<K, V>* entry = table[hash];

        while (entry != nullptr) {
            if (entry->key == key) {
                value = entry->value;
                return true;
            }
            entry = entry->next;
        }
        return false;
    }
};

class Sudoku {
private:
    HashMap<Cell, int> userMoves;
    int grid[9][9];
    int solution[9][9];
    int prefilledCells;
    int heartsRemaining;

    bool solve(int row = 0, int col = 0);
    void generatePuzzle();
    void initializeGrid();

public:
    Sudoku();
    void setDifficulty(const char* difficulty);
    void displayGrid() const;
    void startGame(const char* difficulty);
    void play();
    bool hasUniqueSolution();
    void resetGame();
    bool isValid(int row, int col, int num); // Make isValid public

    int getGridValue(int row, int col) const { return grid[row][col]; }
    int getSolutionValue(int row, int col) const { return solution[row][col]; }
    void setGridValue(int row, int col, int value) { grid[row][col] = value; }
    HashMap<Cell, int>& getUserMoves() { return userMoves; }
    int getHeartsRemaining() const { return heartsRemaining; }
    void decreaseHearts() { if (heartsRemaining > 0) heartsRemaining--; }
};

#endif