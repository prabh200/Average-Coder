#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <vector>
/**
   Computes the hash code for a string.
   @param str a string
   @return the hash code
*/
int hash_code(const std::string &str);
class LatLngMap;
class Node {
    private:
        std::string lat_lng;
        int aqi;
        Node *next;

    friend class LatLngMap;
};
// Hash Table with separate chaining
class LatLngMap {
    public:
        LatLngMap(int nbuckets);
        ~LatLngMap();
        int count(const std::string &x); // 1 if found, 0 if not found.
        void insert(const std::string &x, int aqi); // if does not exist, insert. if exists, update.
        void erase(const std::string &x); // remove an element if present.
        int find(std::string find_lat_lng); // -2 if not found, aqui level if found.
        void clear(); // clear all contents
        int size() const; // get number of items in the Hash Table
        void exporthash(); // export as cache
    private:
        std::vector<Node *> buckets; // calling the buckets that contains Node Objects.
        int current_size; // declaring a current size variable.
};
LatLngMap importhash(std::string);// taking in a string and it returns the hashtable.
#endif