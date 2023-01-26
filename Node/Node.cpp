#include "Node.h"

Node::Node(char ch, int frequency) {
    this->ch = ch;
    this->frequency = frequency;
    left = right = nullptr;
}

char Node::getCharacter() const {
    return ch;
}

int Node::getFrequency() const {
    return frequency;
}

void Node::setLeft(Node* node) {
    left = node;
}

void Node::setRight(Node* node) {
    right = node;
}

Node* Node::getLeft() const {
    return left;
}

Node* Node::getRight() const {
    return right;
}