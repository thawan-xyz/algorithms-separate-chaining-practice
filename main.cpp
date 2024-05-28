#include <iostream>
#include <optional>
#include <list>
using namespace std;

template <typename T, typename E, int L>
class SeparateChaining {
public:
    SeparateChaining() {
        hashTableSize = L;
        numElements = 0;
        hashTable = new list<pair<T, E>>[L];
    }

    void insert(T key, E value) {
        if (!find(key).has_value()) {
            int hashPosition = hashFunction(key);
            hashTable[hashPosition].push_back(make_pair(key, value));
            numElements++;
        }
    }

    optional<E> remove(T key) {
        int hashPosition = hashFunction(key);

        auto listIterator = hashTable[hashPosition].begin();
        while (listIterator != hashTable[hashPosition].end()) {
            if (listIterator->first == key) {
                E tempValue = listIterator->second;
                hashTable[hashPosition].erase(listIterator);
                numElements--;
                return tempValue;
            }
            ++listIterator;
        }

        return nullopt;
    }

    optional<E> find(T key) {
        int hashPosition = hashFunction(key);

        auto listIterator = hashTable[hashPosition].begin();
        while (listIterator != hashTable[hashPosition].end()) {
            if (listIterator->first == key) {
                return listIterator->second;
            }
            ++listIterator;
        }

        return nullopt;
    }

    int getNumElements() {
        return numElements;
    }

    void print() {
        for (int i = 0; i < hashTableSize; ++i) {
            cout << "SeparateChaining[" << i << "] =";

            auto listIterator = hashTable[i].begin();
            while (listIterator != hashTable[i].end()) {
                cout << " {" << listIterator->first << ", " << listIterator->second << "}";
                ++listIterator;
            }

            cout << "\n";
        }
    }

    void clear() {
        delete[] hashTable;

        numElements = 0;
        hashTable = new list<pair<T, E>>[L];
    }

private:
    int hashTableSize;
    int numElements;
    list<pair<T, E>>* hashTable;

    int hashFunction(T key) {
        int modulus = key % hashTableSize;
        return modulus < 0 ? modulus + hashTableSize : modulus;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    auto* myDictionary = new SeparateChaining<int, string, 14>;

    myDictionary->insert(14, "Thawan");

    delete myDictionary;
    return 0;
}
