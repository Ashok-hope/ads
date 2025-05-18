#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;
struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool is_end_of_word;
    TrieNode() : is_end_of_word(false) {}
};
class Trie {
private:
    TrieNode* root;
    void findWords(TrieNode* node, string current_prefix, vector<string>& result) {
        if (node->is_end_of_word) 
            result.push_back(current_prefix);
        for (auto& child : node->children)
            findWords(child.second, current_prefix + child.first, result);
    }
public:
    Trie() {
        root = new TrieNode();
    }
    void insert(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end())
                current->children[c] = new TrieNode();
            current = current->children[c];
        }
        current->is_end_of_word = true;
    }
    bool search(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end())
                return false;
            current = current->children[c];
        }
        return current->is_end_of_word;
    }
    bool startsWith(const string& prefix) {
        TrieNode* current = root;
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return true;
    }
    vector<string> autocomplete(const string& prefix) {
        vector<string> result;
        TrieNode* current = root;
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end())
                return result;
            current = current->children[c];
        }
        findWords(current, prefix, result);
        return result;
    }
    vector<string> suggestSimilarWords(const string& word) {
        vector<string> suggestions;
        vector<string> allWords;
        findWords(root, "", allWords);
        for (const string& w : allWords) {
            int distance = editDistance(w, word);
            if (distance <= 2)
                suggestions.push_back(w);
        }
        return suggestions;
    }
    int editDistance(const string& a, const string& b) {
        int m = a.size(), n = b.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int cost = (a[i - 1] == b[j - 1]) ? 0 : 1;
                dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
            }
        }
        return dp[m][n];
    }
    ~Trie() {
        delete root;
    }
    void deleteNode(TrieNode* node) {
        for (auto& child : node->children)
            deleteNode(child.second);
        delete node;
    }
};
int main() {
    Trie trie;
    int choice;
    string word, prefix;
    vector<string> words = {"apple", "appetizer", "banana", "band", "bat", "ball", "batman"};
    for (const string& word : words)
        trie.insert(word);
    cout << "\n*** Menu ***\n";
    cout << "1. Insert a word\n";
    cout << "2. Spellcheck a word\n";
    cout << "3. Autocomplete a prefix\n";
    cout << "4. Exit\n";
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter the word to insert: ";
                cin >> word;
                trie.insert(word);
                cout << "Word '" << word << "' inserted into the Trie.\n";
                break;
            case 2:
                cout << "Enter the word to spellcheck: ";
                cin >> word;
                if (trie.search(word))
                    cout << "The word '" << word << "' is in the Trie.\n";
                else{
                    cout << "The word '" << word << "' is NOT in the Trie.\n";
                    vector<string> suggestions = trie.suggestSimilarWords(word);
                    if (suggestions.empty())
                        cout << "No similar words found.\n";
                    else {
                        cout << "Did you mean:\n";
                        for (const string& suggestion : suggestions)
                            cout << suggestion << endl;
                    }
                }
                break;
            case 3: {
                cout << "Enter the prefix for autocomplete: ";
                cin >> prefix;
                vector<string> autocompleteResult = trie.autocomplete(prefix);
                if (autocompleteResult.empty())
                    cout << "No words found for the prefix '" << prefix << "'.\n";
                else {
                    cout << "Autocomplete results for '" << prefix << "':\n";
                    for (const string& w : autocompleteResult)
                        cout << w << endl;
                }
                break;
            }
            case 4:
                cout << "Exiting the program.\n";
                return 0;
            default: 
                cout << "Invalid choice. Please try again.\n";break;
        }
    }
}
