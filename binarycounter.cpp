#include <iostream>
#include <vector>
using namespace std;

class BinaryCounter {
    vector<bool> bits;
    int cost = 0;

public:
    void increment() {
        int i = 0;
        // Flip trailing 1s to 0
        while (i < bits.size() && bits[i]) {
            bits[i] = false;
            cost++;
            i++;
        }
        // Flip the first 0 to 1 (or append a new 1 if all were 1)
        if (i == bits.size()) {
            bits.push_back(true);
        } else {
            bits[i] = true;
        }
        cost++;
      // Display output properly
        cout << "Counter: ";
        for (int j = bits.size() - 1; j >= 0; j--) 
            cout << bits[j];
        cout << " (Cost: " << cost << ")" << endl;
    }
};

int main() {
    BinaryCounter counter;
    for (int i = 0; i < 16; i++) {
        counter.increment();
    }
    return 0;
}
