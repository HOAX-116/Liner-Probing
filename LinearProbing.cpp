#include <iostream>

using namespace std;

struct Node {
  int key;
  int value;
  Node* next;
};

class HashTable {
private:
  Node** table;
  int size;
  int numItems;

public:
  HashTable(int size) {
    this->table = new Node*[size];
    this->size = size;
    this->numItems = 0;

    for (int i = 0; i < size; i++) {
      table[i] = NULL;
    }
  }

  ~HashTable() {
    for (int i = 0; i < size; i++) {
      Node* node = table[i];
      while (node != NULL) {
        Node* temp = node;
        node = node->next;
        delete temp;
      }
    }

    delete[] table;
  }

  int hashFunction(int key) {
    return key % size;
  }

  void insert(int key, int value) {
    int index = hashFunction(key);

    if (table[index] != NULL) {
      int probe = index;

      do {
        probe = (probe + 1) % size;
      } while (table[probe] != NULL);

      index = probe;
    }

    Node* newNode = new Node;
    newNode->key = key;
    newNode->value = value;
    newNode->next = table[index];
    table[index] = newNode;
    numItems++;
  }

  int search(int key) {
    int index = hashFunction(key);

    Node* node = table[index];
    while (node != NULL) {
      if (node->key == key) {
        return node->value;
      }

      node = node->next;
    }

    return -1;
  }

  void remove(int key) {
    int index = hashFunction(key);

    Node* node = table[index];
    Node* prev = NULL;

    while (node != NULL) {
      if (node->key == key) {
        if (prev == NULL) {
          table[index] = node->next;
        } else {
          prev->next = node->next;
        }

        delete node;
        numItems--;
        break;
      }

      prev = node;
      node = node->next;
    }
  }

  void printTable() {
    for (int i = 0; i < size; i++) {
      Node* node = table[i];
      while (node != NULL) {
        cout << "(" << node->key << ", " << node->value << ") ";
        node = node->next;
      }

      cout << endl;
    }
  }
};

int main() {
  HashTable* hashTable = new HashTable(10);

  hashTable->insert(1, 10);
  hashTable->insert(2, 20);
  hashTable->insert(3, 30);
  hashTable->insert(4, 40);
  hashTable->insert(5, 50);

  cout << "Hash table:" << endl;
  hashTable->printTable();

  cout << "Searching for key 3: " << hashTable->search(3) << endl;
  cout << "Searching for key 7: " << hashTable->search(7) << endl;

  hashTable->remove(3);

  cout << "Hash table after removing key 3:" << endl;
  hashTable->printTable();

  return 0;
}
