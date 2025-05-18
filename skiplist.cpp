#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

const int MAX_LEVEL = 4;
const float P = 0.5f;

class Node {
public:
    int value;
    vector<Node*> forward;

    Node(int val, int level) : value(val), forward(level + 1, nullptr) {}
};

class SkipList {
    Node* head;
    int level;

    int randomLevel() {
        int lvl = 0;
        while ((float)rand() / RAND_MAX < P && lvl < MAX_LEVEL)
            lvl++;
        return lvl;
    }

public:
    SkipList() {
        level = 0;
        head = new Node(-1, MAX_LEVEL);
        srand(time(0)); // Seed for randomness
    }

    void insert(int value) {
        vector<Node*> update(MAX_LEVEL + 1);
        Node* curr = head;

        // Find position to insert
        for (int i = level; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->value < value)
                curr = curr->forward[i];
            update[i] = curr;
        }

        curr = curr->forward[0];

        if (!curr || curr->value != value) {
            int randLvl = randomLevel();
            if (randLvl > level) {
                for (int i = level + 1; i <= randLvl; i++)
                    update[i] = head;
                level = randLvl;
            }

            Node* newNode = new Node(value, randLvl);
            for (int i = 0; i <= randLvl; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }

            cout << "Inserted " << value << " at level " << randLvl << endl;
        }
    }

    bool search(int value) {
        Node* curr = head;
        for (int i = level; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->value < value)
                curr = curr->forward[i];
        }
        curr = curr->forward[0];
        return curr && curr->value == value;
    }

    void display() {
        cout << "\nSkip List:\n";
        for (int i = level; i >= 0; i--) {
            Node* curr = head->forward[i];
            cout << "Level " << i << ": ";
            while (curr) {
                cout << curr->value << " ";
                curr = curr->forward[i];
            }
            cout << "\n";
        }
    }
};

int main() {
    SkipList list;

    list.insert(3);
    list.insert(6);
    list.insert(7);
    list.insert(9);
    list.insert(12);
    list.insert(19);
    list.insert(17);
    list.insert(26);
    list.insert(21);
    list.insert(25);

    list.display();

    int target = 19;
    cout << "\nSearch " << target << ": " << (list.search(target) ? "Found" : "Not Found") << endl;

    return 0;
}
