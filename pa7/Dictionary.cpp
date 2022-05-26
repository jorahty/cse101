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
Dictionary::Dictionary(const Dictionary& D) {
  nil = new Node("nil", 0);
  root = nil;
  current = nil;
  num_pairs = 0;

  preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
  clear();
  delete nil;
}

// ██ Helper Functions ██

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
  if (R != nil) {
    inOrderString(s, R->left);
    s += (R->key + " : " + std::to_string(R->val) + " \n");
    inOrderString(s, R->right);
  }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
  if (R != nil) {
    s += (R->key + "\n");
    preOrderString(s, R->left);
    preOrderString(s, R->right);
  }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
  if (R != N) {
    setValue(R->key, R->val);
    preOrderCopy(R->left, N);
    preOrderCopy(R->right, N);
  }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
  if (R != nil) {
    postOrderDelete(R->left);
    postOrderDelete(R->right);
    transplant(R, R->right);
    delete R;
    num_pairs--;
  }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
  if (R == nil || k == R->key) {
    return R;
  } else if (k < R->key) {
    return search(R->left, k);
  } else {
    return search(R->right, k);
  }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
  if (R == nil) return nil;
  while (R->left != nil) {
    R = R->left;
  }
  return R;
}

// transplant()
// Replaces subtree rooted at u with subtree rooted at v.
void Dictionary::transplant(Node* u, Node* v) {
  if (u->parent == nil) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  if (v != nil) {
    v->parent = u->parent;
  }
}

// ██ Access Functions ██

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
  return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
  Node* N = search(root, k);
  return N && N != nil;
}

// ██ Manipulation Procedures ██

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
  postOrderDelete(root);
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
  num_pairs++;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
  if (contains(k) == false) {
    throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
  }
  Node* z = search(root, k);

  if (z->left == nil) {
    transplant(z, z->right);
    delete z;
  } else if (z->right == nil) {
    transplant(z, z->left);
    delete z;
  } else {
    Node* y = findMin(z->right);
    if (y->parent != z) {
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    delete z;
  }

  num_pairs--;
}

// ██ Other Functions ██

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
  std::string s = "";
  inOrderString(s, root);
  return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
  std::string s = "";
  preOrderString(s, root);
  return s;
}

// ██ Overloaded Operators ██

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<(std::ostream& stream, Dictionary& D) {
  return stream << D.Dictionary::to_string();
}
