// James Tennant • jtennant • pa7

#include "Dictionary.h"
#include <iostream>
#include <string>

// ██ Private Contructors ██

Dictionary::Node::Node(keyType k, valType v) {
  key = k;
  val = v;
  parent = nullptr;
  left = nullptr;
  right = nullptr;
  // parent, left, right fields will be set later
  // (probably by whoever called this contructor)
}

// ██ Class Constructors & Destructors ██

Dictionary::Dictionary() {
  nil = new Node("nil", 0);

  root = nil;
  current = nil;

  num_pairs = 0;
}

// Copy constructor.
// Dictionary::Dictionary(const Dictionary& D);

// Destructor
Dictionary::~Dictionary() {
  // delete non-nil nodes
  delete nil;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
  Node* y = nil; // inch worm
  Node* x = root;
  while (x != nil) { // until fallen off
    y = x;
    if (k == x->key) {
      x->val = v; // overwrite
      return;
    } else if (k < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }
  // existing node was not found
  Node* z = new Node(k, v);
  z->parent = y;
  z->left = nil;
  z->right = nil;
  if (y == nil) { // if tree was empty
    root = z;
  } else if (z->key < y->key) {
    y->left = z;
  } else {
    y->right = z;
  }
}