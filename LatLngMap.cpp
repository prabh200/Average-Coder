#include <fstream>
#include <iostream>
#include "LatLngMap.h"
//computing a hash code for a given string
int hash_code(const std::string &str) {
    int h = 0;// Initialize the hash value to 0
    for (int i = 0; i < str.length(); i++) {
        h = 31 * h + str[i];// Multiply the current hash value by 31 and add the ASCII value of the current character 
    }
    return abs(h % 60); //h can be negative if it overflows.
}

// Constructs a new LatLngMap with the given number of buckets
LatLngMap::LatLngMap(int nbuckets) {
    for (int i = 0; i < nbuckets; i++) {
        buckets.push_back(nullptr);// Add a null pointer to the end of the buckets vector for each bucket
    }
    current_size = 0; // Set the current size to 0
}

// Destructor for LatLngMap
LatLngMap::~LatLngMap() {
    clear(); // Call the clear() function to delete all the elements in the map and free any associated memory
}

// Counts the number of elements in the map that have the given key
int LatLngMap::count(const std::string &x) {
    int h = hash_code(x); // Compute the hash code for the given key
    h = h % buckets.size(); 
    if (h < 0) {
        h = -h; // If the remainder is negative, make it positive
    }
    Node *current = buckets[h];
    while (current != nullptr) {
        if (current->lat_lng == x) {
        return 1;
        }
        current = current->next; // Move to the next element in the linked list
    }
    return 0; // If the key wasn't found, return 0
}

/**
Insert a new element into the LatLngMap with a given latitude-longitude string and AQI value.
@param x the latitude-longitude string to be inserted
@param aqi the AQI value to be inserted
*/
void LatLngMap::insert(const std::string &x, int aqi) {
    // Get the hash code of the latitude-longitude string
    int h = hash_code(x);
    // Get the index of the corresponding bucket using the hash code
    h = h % buckets.size();
    // Handle negative hash code values
    if (h < 0) {
        h = -h;
    }
    // Start at the head of the linked list in the corresponding bucket
    Node *current = buckets[h];
    // Traverse the linked list to check if the latitude-longitude string already exists in the map
    while (current != nullptr) {
        if (current -> lat_lng == x) {
            // If it does, update the AQI value and return
            current -> aqi = aqi;
            return;
        }
        // Already in the set
        current = current->next;
    }
    // If the latitude-longitude string does not exist in the map, create a new node and insert it at the head of the linked list
    Node *new_node = new Node;
    new_node->lat_lng = x;
    new_node->aqi = aqi;
    new_node->next = buckets[h];
    buckets[h] = new_node;
    current_size++;
}

/**
Removes the node with the given latitude and longitude from the hash table.
@param x The latitude and longitude string of the node to remove.
*/
void LatLngMap::erase(const std::string &x) 
{
    // Compute the hash code of the latitude and longitude string
    int h = hash_code(x); 
    // Map the hash code to a bucket index
    h = h % buckets.size(); 
    // Ensure that the bucket index is non-negative
    if (h < 0) {
        h = -h;
    } 
    // Search for the node with the given latitude and longitude string in the linked list in the corresponding bucket
    Node *current = buckets[h];
    Node *previous = nullptr;
    while (current != nullptr) {
        if (current->lat_lng == x) {
        // Remove the node from the linked list
        if (previous == nullptr) {
            buckets[h] = current->next;
        } else {
            previous->next = current->next;
        }
        // Delete the removed node
        delete current; 
        // Decrement the current size of the hash table
        current_size--;
        return;
    }
    // Move to the next node in the linked list
    previous = current;
    current = current->next;
  }
}

/**
Find the AQI (air quality index) of the given city in the hash table.
@param city The name of the city to find the AQI of.
@return The AQI of the city if found, or -2 if not found.
*/
int LatLngMap::find(std::string city)
{
    // Calculate the hash code of the city name
    int h = hash_code(city);
    // Traverse the linked list in the corresponding bucket
    Node* trav = buckets[h];
    
    while(trav != nullptr)
    { 
        // If the city is found, return its AQI
        if(city == trav->lat_lng)
        {
            return trav->aqi;
        } else {
            // If the city is not found, check the next node in the linked list
            if (trav->next != nullptr) {
                trav = trav->next;
            } else {
            // If the end of the linked list is reached, the city is not in the hash table
return -2;
              return -2;
            }
        }
   }
   // If the key is not found, return -2.
   return -2;
} 

/**
Clear all elements from the hash table.
This function removes all elements from the hash table, freeing the memory
allocated to store the nodes. It does not deallocate the memory used by the
hash table itself.
*/
void LatLngMap::clear() {
    // Pointer to traverse the linked list
    Node* walker = nullptr;
    // Pointer to remove nodes from the linked list
    Node* remover = nullptr;
    // Loop through each bucket
    for (int i = 0; i < buckets.size(); i++) {
        // Set the walker to the head of the linked list in this bucket
        walker = buckets[i];
        // Traverse the linked list
        while (walker != nullptr) {
            // Set the remover to the current node
            remover = walker;
            // Move the walker to the next node in the linked list
            walker = walker -> next;
            // Delete the current node.
            delete remover;
        }
    }
}
// Return the number of elements in the hash table.
int LatLngMap::size() const { return current_size; }
/**
 * Export the contents of the hash table to a file called "cache".
 * This function will overwrite any existing contents of the file.
 */

// Input for long map 
void LatLngMap::exporthash() { 
    // Open the "cache" file for writing, and truncate any existing contents
    std::ofstream outfile;
    outfile.open("./data/cache", std::ofstream::trunc);
    // Iterate over each bucket in the hash table
    Node* walker = nullptr;
    for (int i = 0; i < buckets.size(); i++) {
        walker = buckets[i];
         // Traverse the linked list in each bucket
        while (walker != nullptr) {
        // Write the key-value pair to the file, separated by a space and followed by a newline character
            outfile << walker->lat_lng << " " << walker->aqi << "\n";
             // Move to the next node in the linked list
            walker = walker->next;
        }
    }
    // Close the output file
    outfile.close();
}
/**
 * Reads a file containing key-value pairs separated by whitespace and
 * inserts them into a new `LatLngMap` hash table.
 * @param filename the name of the file to read
 * @return a `LatLngMap` hash table containing the key-value pairs from the file
 */
LatLngMap importhash(std::string filename) 
{
    LatLngMap hashtable(60); // Create a hash table with 60 buckets
    std::ifstream file(filename); // Open the file for reading

    std::string key;
    std::string value;

    // Read each line of the file and insert the key-value pair into the hash table
    while (file >> key >> value) {
        hashtable.insert(key, std::stoi(value));
    }

    return hashtable; // Return the populated hash table
}