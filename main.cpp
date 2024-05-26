#include <iostream>
#include <list>
#include <optional>
using namespace std;

template <typename T, typename E, int L>
class SeparateChaining {
public:
    SeparateChaining() {
        hashTableSize = L;
        numElements = 0;
        hashTable = new list<pair<T, E>>[L];
    }

    int hashFunction(T key) {
        return key % hashTableSize;
    }

    void insert(T key, E value) {
        if (!find(key).has_value()) {
            int hashPosition = hashFunction(key);
            hashTable[hashPosition].push_back(make_pair(key, value));
        }
    }

    optional<E> find(T key) {
        int hashPosition = hashFunction(key);
        auto listIterator = hashTable[hashPosition].begin();
        while (listIterator != hashTable[hashPosition].end()) {
            if (*listIterator->first == key) {
                return listIterator->second;
            }
            ++listIterator;
        }
        return nullopt;
    }

private:
    int hashTableSize;
    int numElements;
    list<pair<T, E>>* hashTable;
};
int main() {
    auto* myDictionay = new SeparateChaining<int, string, 14>;
    delete myDictionay;
    return 0;
}
