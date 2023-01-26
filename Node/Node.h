#ifndef NODE_H
#define NODE_H

class Node {
    char ch;
    int frequency;
    Node *left, *right;

    public:
        Node(char, int);

        Node* getLeft() const;
        Node* getRight() const;

        void setLeft(Node*);
        void setRight(Node*);
        
        char getCharacter() const;
        int getFrequency() const;
};

#endif