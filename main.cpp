#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

// Simple in-memory implementation first to test logic
// We'll later convert to file-based B+ Tree

struct Entry {
    string key;
    int value;

    Entry(const string& k, int v) : key(k), value(v) {}

    bool operator<(const Entry& other) const {
        if (key != other.key) return key < other.key;
        return value < other.value;
    }
};

class SimpleBPT {
private:
    // For simplicity, using map of sets
    // In actual B+ Tree, we'd have disk-based nodes
    vector<Entry> entries;

public:
    void insert(const string& key, int value) {
        entries.emplace_back(key, value);
        // Sort to maintain order
        sort(entries.begin(), entries.end());
    }

    void remove(const string& key, int value) {
        for (auto it = entries.begin(); it != entries.end(); ++it) {
            if (it->key == key && it->value == value) {
                entries.erase(it);
                break;
            }
        }
    }

    vector<int> find(const string& key) {
        vector<int> result;
        for (const auto& entry : entries) {
            if (entry.key == key) {
                result.push_back(entry.value);
            }
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    SimpleBPT db;

    string line;
    getline(cin, line);
    int n = stoi(line);

    for (int i = 0; i < n; i++) {
        getline(cin, line);
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "insert") {
            string index;
            int value;
            ss >> index >> value;
            db.insert(index, value);
        }
        else if (cmd == "delete") {
            string index;
            int value;
            ss >> index >> value;
            db.remove(index, value);
        }
        else if (cmd == "find") {
            string index;
            ss >> index;
            vector<int> values = db.find(index);

            if (values.empty()) {
                cout << "null" << endl;
            } else {
                // Sort values (they should already be sorted by our implementation)
                sort(values.begin(), values.end());

                for (size_t j = 0; j < values.size(); j++) {
                    if (j > 0) cout << " ";
                    cout << values[j];
                }
                cout << endl;
            }
        }
    }

    return 0;
}