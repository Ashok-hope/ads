#include <iostream>
#include <vector>
#include<cmath>
#include <climits>
#include<unordered_map>
using namespace std;
struct FibonacciHeapNode {
    int key,degree;
    FibonacciHeapNode* parent,*child,*next,*prev;
    bool marked;
    FibonacciHeapNode(int k) : key(k), parent(nullptr), child(nullptr),next(this), prev(this), degree(0), marked(false) {}
};
class FibonacciHeap {
private:
    FibonacciHeapNode* minNode;
    int nodeCount;
    unordered_map<int, FibonacciHeapNode*> nodeMap;
     void consolidate(){
        if(!minNode) return;
        int maxDegree=log2(nodeCount)+1;
        vector<FibonacciHeapNode*> degrees(maxDegree, nullptr);
        vector<FibonacciHeapNode*>rootlist;
        FibonacciHeapNode* current = minNode;
        do {
            rootlist.push_back(current);
            current=current->prev;
        } while (current != minNode);
        for (FibonacciHeapNode* node : rootlist) {
            int d = node->degree;
            while (degrees[d]) {
                FibonacciHeapNode* other = degrees[d];
                if (node->key > other->key) swap(node, other);
                other->prev->next = other->next;
                other->next->prev = other->prev;
                other->parent = node;
                other->prev = other->next = other;
                if (!node->child)
                    node->child = other;
                else {
                    other->prev = node->child->prev;
                    other->next = node->child;
                    node->child->prev->next = other;
                    node->child->prev = other;
                }
                node->degree++;
                other->marked = false;
                degrees[d] = nullptr;
                d++;
            }
            degrees[d] = node;
        }
        minNode=nullptr;
        for(auto node:degrees){
                if(node &&(!minNode || node->key< minNode->key))
                        minNode=node;
        }
    }
     void cut(FibonacciHeapNode* x, FibonacciHeapNode* y) {
        if (x == x->next)
            y->child = nullptr;
        else {
            x->prev->next = x->next;
            x->next->prev = x->prev;
            if (y->child == x)
                y->child = x->next;
        }
        y->degree--;
        x->next = minNode;
        x->prev = minNode->prev;
        minNode->prev->next = x;
        minNode->prev = x;
        x->parent = nullptr;
        x->marked = false;
    }
    void cascadingCut(FibonacciHeapNode* y) {
        FibonacciHeapNode* z = y->parent;
        if (z != nullptr) {
            if (!y->marked)
                y->marked = true;
            else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }
public:
    FibonacciHeap() : minNode(nullptr), nodeCount(0) {}
    void insert(int key) {
        FibonacciHeapNode* newNode = new FibonacciHeapNode(key);
	nodeMap[key]=newNode;
        if (minNode == nullptr)
            minNode = newNode;
        else {
            minNode->prev->next = newNode;
            newNode->prev = minNode->prev;
            newNode->next = minNode;
            minNode->prev = newNode;
            if (key < minNode->key)
                minNode = newNode;
        }
        nodeCount++;
    }
    FibonacciHeapNode* findMin() {
        return minNode;
    }
    int deleteMin() {
        if (minNode == nullptr) {
            cout << "Heap is empty!" << endl;
            return INT_MIN;
        }
        FibonacciHeapNode* z = minNode;
        int minKey = z->key;
        if (z->child != nullptr) {
            FibonacciHeapNode* child = z->child;
            do {
		FibonacciHeapNode* temp=child->prev;
		child->next=minNode;
		child->prev=minNode->prev;
		minNode->prev->next=child;
		minNode->prev=child;
                child->parent = nullptr;
                child = temp;
            } while (child != z->child);
        }
        if (z == z->next)
            minNode = nullptr;
        else {
            minNode->next->prev=minNode->prev;
	    minNode->prev->next=minNode->next;
	    minNode=minNode->prev;
            consolidate();
        }
	nodeMap.erase(minKey);
        nodeCount--;
        delete z;
        return minKey;
    }
    void decreaseKey(int key, int newKey) {
	if(nodeMap.find(key)==nodeMap.end()){
		cout<<"Key not found!"<<endl;
		return;
	}
        FibonacciHeapNode *x= nodeMap[key];
        if (newKey > x->key) {
            cout << "New key is greater than current key!" << endl;
            return;
        }
	nodeMap.erase(key);
	nodeMap[newKey]=x;
        x->key = newKey;
        FibonacciHeapNode* y = x->parent;
        if (y != nullptr && x->key < y->key) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x->key < minNode->key)
            minNode = x;
    }
    void meld(FibonacciHeap* other) {
        if (other->minNode == nullptr||!other) return;
        if (minNode == nullptr)
            minNode = other->minNode;
        else {
            FibonacciHeapNode* minNodePrev = minNode->prev;
            FibonacciHeapNode* otherMinNodeNext = other->minNode->next;
            minNode->prev = other->minNode;
            other->minNode->next = minNode;
            minNodePrev->next = otherMinNodeNext;
            otherMinNodeNext->prev = minNodePrev;
            if (other->minNode->key < minNode->key)
                minNode = other->minNode;
        }
	FibonacciHeapNode* start = other->minNode;
    	if (start) {
        FibonacciHeapNode* curr = start;
        do {
            nodeMap[curr->key] = curr;
            curr = curr->prev;
        } while (curr != start);
    	}
        nodeCount += other->nodeCount;
        other->minNode = nullptr;
        other->nodeCount = 0;
    }
    void deleteNode(int key) {
        decreaseKey(key,INT_MIN);
	deleteMin();
    }
    void print() {
        if (minNode == nullptr) {
            cout << "Heap is empty!" << endl;
            return;
        }
	cout << "Root List: ";
        FibonacciHeapNode* start = minNode;
        FibonacciHeapNode* temp = start;
        do {
            cout << temp->key << " ";
            temp = temp->next;
        } while (temp != start);
        cout << endl;
    }
    int size() {
        return nodeCount;
    }
    ~FibonacciHeap() {
        while (minNode != nullptr)
            deleteMin();
    }
};
int main() {
    FibonacciHeap heap;
    int choice, key;
    FibonacciHeapNode* node = nullptr;  
    cout << "\n--- Fibonacci Heap Operations ---\n";
    cout << "1. Insert\n";
    cout << "2. Find-Min\n";
    cout << "3. Delete-Min\n";
    cout << "4. Decrease Key\n";
    cout << "5. Meld\n";
    cout << "6. Delete\n";
    cout << "7. Print Heap\n";
    cout << "8. Exit\n";
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                heap.insert(key);break;
	    case 2:
                cout << "Min Element: " << heap.findMin()->key << endl;break;
            case 3:
                cout << "Deleted minimum: " << heap.deleteMin() << endl;break;
            case 4:
		int newkey;
                cout << "Enter key to decrease: ";
                cin >> key;
                cout << "Enter new key: ";
                cin >> newkey;
                heap.decreaseKey(key, newkey);break;
            case 5: {
                FibonacciHeap heap2;
                int n;
                cout << "Enter number of elements to insert into second heap: ";
                cin >> n;
                for (int i = 0; i < n; i++) {
                    cout << "Enter key: ";
                    cin >> key;
                    heap2.insert(key);
                }
                heap.meld(&heap2);
                cout << "Heaps melded successfully!" << endl;break;
            }
            case 6:
                cout << "Enter key of the node to delete: ";
                cin >> key;
                heap.deleteNode(key);break;
            case 7:
                cout << "Fibonacci Heap: ";
                heap.print();break;
            case 8:
                cout << "Exiting program." << endl; return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }
    return 0;
}
