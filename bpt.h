#ifndef BPT_H
#define BPT_H

#include <string>
#include <vector>
#include <fstream>

class BPlusTree {
private:
    static const int MAX_KEYS = 100;  // Adjust based on performance
    static const char* DATA_FILE;
    static const char* INDEX_FILE;

    struct IndexNode {
        bool isLeaf;
        int keyCount;
        std::string keys[MAX_KEYS];
        int children[MAX_KEYS + 1];  // For internal nodes
        int values[MAX_KEYS];        // For leaf nodes
        int nextLeaf;                // For leaf nodes

        IndexNode() : isLeaf(false), keyCount(0), nextLeaf(-1) {
            for (int i = 0; i < MAX_KEYS + 1; i++) {
                children[i] = -1;
            }
        }
    };

    struct DataRecord {
        std::string key;
        int value;

        DataRecord() : value(0) {}
        DataRecord(const std::string& k, int v) : key(k), value(v) {}
    };

    int rootNode;
    std::fstream indexFile;
    std::fstream dataFile;

    // Helper methods
    void readIndexNode(int pos, IndexNode& node);
    void writeIndexNode(int pos, const IndexNode& node);
    void readDataRecord(int pos, DataRecord& record);
    void writeDataRecord(int pos, const DataRecord& record);

    int findLeaf(const std::string& key);
    void splitLeaf(int leafPos, IndexNode& leaf);
    void splitInternal(int nodePos, IndexNode& node);
    void insertInternal(const std::string& key, int childPos, int parentPos, IndexNode& parent);

public:
    BPlusTree();
    ~BPlusTree();

    void insert(const std::string& key, int value);
    void remove(const std::string& key, int value);
    std::vector<int> find(const std::string& key);

    void initializeFiles();
};

#endif // BPT_H