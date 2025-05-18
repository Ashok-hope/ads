#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int ALPHABET_SIZE = 26;

struct TrieNode {
    TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; ++i)
            children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

    void autocompleteHelper(TrieNode* node, string prefix, vector<string>& suggestions) {
        if (node->isEndOfWord)
            suggestions.push_back(prefix);

        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (node->children[i]) {
                char nextChar = 'a' + i;
                autocompleteHelper(node->children[i], prefix + nextChar, suggestions);
            }
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!curr->children[index])
                curr->children[index] = new TrieNode();
            curr = curr->children[index];
        }
        curr->isEndOfWord = true;
    }

    bool spellCheck(const string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!curr->children[index])
                return false;
            curr = curr->children[index];
        }
        return curr->isEndOfWord;
    }

    vector<string> getAutoCompleteSuggestions(const string& prefix) {
        TrieNode* curr = root;
        vector<string> suggestions;

        for (char ch : prefix) {
            int index = ch - 'a';
            if (!curr->children[index])
                return {};  // No match found
            curr = curr->children[index];
        }

        autocompleteHelper(curr, prefix, suggestions);
        return suggestions;
    }
};

int main() {
    Trie trie;

    // Add dictionary words
    trie.insert("hello");
    trie.insert("help");
    trie.insert("hell");
    trie.insert("heap");
    trie.insert("healthy");
    trie.insert("heal");

    // Spell Check
    string word = "hello";
    cout << "Spell Check: " << word << " -> " << (trie.spellCheck(word) ? "✔ Exists" : "❌ Not Found") << endl;

    // Autocomplete
    string prefix = "he";
    cout << "Autocomplete suggestions for \"" << prefix << "\":" << endl;
    vector<string> suggestions = trie.getAutoCompleteSuggestions(prefix);
    for (const string& s : suggestions) {
        cout << " - " << s << endl;
    }

    return 0;
}
