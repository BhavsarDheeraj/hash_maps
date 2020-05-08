#include <string>
using namespace std;

template <typename V>
class MapNode {
 public:
  string key;
  V value;
  MapNode* next;

  MapNode(string key, V value) {
    this->key = key;
    this->value = value;
    this->next = NULL;
  }

  ~MapNode() { delete next; }
};

template <typename V>
class mymap {
  MapNode<V>** buckets;
  int count;
  int numBuckets;

 public:
  mymap() {
    count = 0;
    numBuckets = 5;
    buckets = new MapNode<V>*[numBuckets];
    for (int i = 0; i < numBuckets; i++) buckets[i] = NULL;
  }

  ~mymap() {
    for (int i = 0; i < numBuckets; i++) {
      delete buckets[i];
    }
    delete[] buckets;
  }

  int size() { return count; }

  V getValue(string key) {
    int bucketIndex = getBucketIndex(key);
    MapNode<V>* head = buckets[bucketIndex];
    while (head != NULL) {
      if (head->key == key) {
        return head->value;
      }
      head = head->next;
    }
    return 0;
  }

  void insert(string key, V value) {
    int bucketIndex = getBucketIndex(key);
    MapNode<V>* head = buckets[bucketIndex];
    while (head != NULL) {
      if (head->key == key) {
        head->value = value;
        return;
      }
      head = head->next;
    }
    head = buckets[bucketIndex];
    MapNode<V>* node = new MapNode<V>(key, value);
    node->next = head;
    buckets[bucketIndex] = node;
    count++;
    double loadFactor = double(count) / double(numBuckets);
    if (loadFactor > 0.7) {
      rehash();
    }
  }

  V remove(string key) {
    int bucketIndex = getBucketIndex(key);
    MapNode<V>* head = buckets[bucketIndex];
    MapNode<V>* prev = NULL;
    while (head != NULL) {
      if (head->key == key) {
        if (prev) {
          prev->next = head->next;
        } else {
          buckets[bucketIndex] = head->next;
        }
        head->next = NULL;
        V deleted = head->value;
        delete head;
        count--;
        return deleted;
      }
      prev = head;
      head = head->next;
    }
    return 0;
  }

  double getLoadFactor() { return double(count) / double(numBuckets); }

 private:
  int getBucketIndex(string key) {
    int hashCode = 0;
    int currentCoeff = 1;
    for (int i = key.size() - 1; i >= 0; i--) {
      hashCode += key[i] * currentCoeff;
      hashCode = hashCode % numBuckets;
      currentCoeff *= 37;  // Can be any prime number.
      currentCoeff = currentCoeff % numBuckets;
    }
    return hashCode % numBuckets;
  }

  void rehash() {
    MapNode<V>** temp = buckets;
    buckets = new MapNode<V>*[2 * numBuckets];
    for (int i = 0; i < 2 * numBuckets; i++) buckets[i] = NULL;
    int oldBucketCount = numBuckets;
    numBuckets = 2 * numBuckets;
    count = 0;
    for (int i = 0; i < oldBucketCount; i++) {
      MapNode<V>* head = temp[i];
      while (head != NULL) {
        string key = head->key;
        V value = head->value;
        insert(key, value);
        head = head->next;
      }
    }
    for (int i = 0; i < oldBucketCount; i++) {
      delete temp[i];
    }
    delete[] temp;
  }
};