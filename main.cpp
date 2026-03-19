#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <fstream>
#include <cstring>

using namespace std;

// Simple file to check if we need to persist data
const char* DATA_FILE = "bpt_data.bin";

class BPT {
private:
    map<string, set<int>> data;
    bool modified = false;

    void saveToFile() {
        // Simple serialization - not efficient but works for now
        ofstream out(DATA_FILE, ios::binary);
        if (!out) return;

        size_t mapSize = data.size();
        out.write(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));

        for (const auto& pair : data) {
            size_t keyLen = pair.first.size();
            out.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
            out.write(pair.first.c_str(), keyLen);

            size_t setSize = pair.second.size();
            out.write(reinterpret_cast<const char*>(&setSize), sizeof(setSize));

            for (int value : pair.second) {
                out.write(reinterpret_cast<const char*>(&value), sizeof(value));
            }
        }

        modified = false;
    }

    void loadFromFile() {
        ifstream in(DATA_FILE, ios::binary);
        if (!in) return; // File doesn't exist

        size_t mapSize;
        in.read(reinterpret_cast<char*>(&mapSize), sizeof(mapSize));

        for (size_t i = 0; i < mapSize; i++) {
            size_t keyLen;
            in.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));

            string key(keyLen, '\0');
            in.read(&key[0], keyLen);

            size_t setSize;
            in.read(reinterpret_cast<char*>(&setSize), sizeof(setSize));

            set<int> values;
            for (size_t j = 0; j < setSize; j++) {
                int value;
                in.read(reinterpret_cast<char*>(&value), sizeof(value));
                values.insert(value);
            }

            data[key] = values;
        }
    }

public:
    BPT() {
        // Try to load existing data
        loadFromFile();
    }

    ~BPT() {
        if (modified) {
            saveToFile();
        }
    }

    void insert(const string& key, int value) {
        data[key].insert(value);
        modified = true;
    }

    void remove(const string& key, int value) {
        auto it = data.find(key);
        if (it != data.end()) {
            it->second.erase(value);
            if (it->second.empty()) {
                data.erase(it);
            }
            modified = true;
        }
    }

    void find(const string& key) {
        auto it = data.find(key);
        if (it == data.end() || it->second.empty()) {
            cout << "null" << endl;
        } else {
            bool first = true;
            for (int value : it->second) {
                if (!first) cout << " ";
                cout << value;
                first = false;
            }
            cout << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BPT db;

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
            db.find(index);
        }
    }

    return 0;
}