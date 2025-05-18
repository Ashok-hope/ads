#include <iostream>
#include <vector>
using namespace std;

class DynamicTable {
    vector<int> table;
    int size = 0;
    int capacity = 1;
    int total_cost = 0;
    int amortized_cost = 0;

public:
    DynamicTable() {
        table.resize(capacity); // Initialize with initial capacity
    }

    void insert(int value) {
        if (size == capacity) {
            // Double the capacity
            vector<int> new_table(2 * capacity);
            for (int i = 0; i < size; i++) {
                new_table[i] = table[i];
                amortized_cost++;
            }
            table = new_table;
            capacity *= 2;
        }
        table[size++] = value; // Now safe
        amortized_cost++;
        total_cost = amortized_cost;

        cout << "Inserted " << value
             << ", Size: " << size
             << ", Capacity: " << capacity
             << ", Total Cost: " << total_cost << endl;
    }
};

int main() {
    DynamicTable table;
    for (int i = 1; i <= 8; i++) {
        table.insert(i);
    }
    return 0;
}
