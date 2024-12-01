#ifndef ELLIOT_DATA
#define ELLIOT_DATA
#pragma once
#include <iostream>

namespace dataE {

class node {
public:
    node* next = nullptr;
    std::string data;
};

class queue {
public:
    queue();
    ~queue();
    std::string getItem();
    void pop();
    void push(std::string data);
private:
    node* hp = nullptr;
    node* tp = nullptr;

};
}
#endif