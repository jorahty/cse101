// James Tennant • jtennant • pa5

#include "List.h"

// ██ Private Constructors ██

List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

// ██ Class Constructors & Destructors ██

// Creates new List in the empty state
List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;

    beforeCursor = frontDummy;
    afterCursor = backDummy;

    pos_cursor = 0;
    num_elements = 0;
}

// Copy constructor
List::List(const List& L) {
    // Make this an empty List
    frontDummy = new Node(0);
    backDummy = new Node(0);
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;

    // Load elements of L into this List
    for (Node* N = L.frontDummy->next; N != L.backDummy; N = N->next) {
        this->insertAfter(N->data);
        this->moveNext();
    }
}

// Destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

// ██ Access functions ██

// Returns the length of this List
int List::length() const {
    return num_elements;
}

// Returns the front element in this List
// pre: length()>0
ListElement List::front() const {
    if (num_elements == 0) {
        throw std::length_error("List: front(): empty list");
    }
    return frontDummy->next->data;
}

// Returns the back element in this List
// pre: length()>0
ListElement List::back() const {
    if (num_elements == 0) {
        throw std::length_error("List: back(): empty list");
    }
    return backDummy->prev->data;
}

// Returns the position of cursor in this List: 0 <= position() <= length()
int List::position() const {
    return pos_cursor;
}

// Returns the element after the cursor
// pre: position()<length()
ListElement List::peekNext() const {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: peekNext(): cursor at back");
    }
    return afterCursor->data;
}

// Returns the element before the cursor
// pre: position()>0
ListElement List::peekPrev() const {
    if (pos_cursor <= 0) {
        throw std::range_error("List: peekPrev(): cursor at front");
    }
    return beforeCursor->data;
}

// ██ Manipulation procedures ██

// Deletes all elements in this List, setting it to the empty state
void List::clear() {
    moveBack();
    while (num_elements > 0) {
        eraseBefore();
    }
}

// Moves cursor to position 0 in this List
void List::moveFront() {
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
    pos_cursor = 0;
}

// Moves cursor to position length() in this List
void List::moveBack() {
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
    pos_cursor = num_elements;
}

// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext() {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: moveNext(): cursor at back");
    }
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;
    pos_cursor++;
    return beforeCursor->data;
}

// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev() {
    if (pos_cursor <= 0) {
        throw std::range_error("List: movePrev(): cursor at front");
    }
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

// Inserts x after cursor
void List::insertAfter(ListElement x) {
    Node* N = new Node(x);

    // Hook up the new node
    N->next = afterCursor;
    N->prev = beforeCursor;

    // Hook up surrounding nodes
    beforeCursor->next = N;
    afterCursor->prev = N;

    // Update fields
    afterCursor = N;
    num_elements++;
}

// Inserts x before cursor
void List::insertBefore(ListElement x) {
    Node* N = new Node(x);

    // Hook up the new node
    N->next = afterCursor;
    N->prev = beforeCursor;

    // Hook up surrounding nodes
    beforeCursor->next = N;
    afterCursor->prev = N;

    // Update fields
    beforeCursor = N;
    num_elements++;
    pos_cursor++;
}

// Overwrites the List element after the cursor with x
// pre: position()<length()
void List::setAfter(ListElement x) {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: setAfter(): cursor at back");
    }
    afterCursor->data = x;
}

// Overwrites the List element before the cursor with x
// pre: position()>0
void List::setBefore(ListElement x) {
    if (pos_cursor == 0) {
        throw std::range_error("List: setBefore(): cursor at front");
    }
    beforeCursor->data = x;
}

// Deletes element after cursor
// pre: position()<length()
void List::eraseAfter() {
    if (pos_cursor >= num_elements) {
        throw std::range_error("List: eraseAfter(): cursor at back");
    }

    Node* N = afterCursor;
    afterCursor = afterCursor->next;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;

    num_elements--;
    delete N;
}

// Deletes element before cursor
// pre: position()>0
void List::eraseBefore() {
    if (pos_cursor == 0) {
        throw std::range_error("List: eraseBefore(): cursor at front");
    }

    Node* N = beforeCursor;
    beforeCursor = beforeCursor->prev;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;

    pos_cursor--;
    num_elements--;
    delete N;
}

// ██ Other Functions ██

// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1
int List::findNext(ListElement x) {
    while (pos_cursor != num_elements) {
        moveNext();
        if (beforeCursor->data == x) {
            return pos_cursor;
        }
    }
    return -1;
}

// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1
int List::findPrev(ListElement x) {
    while (pos_cursor != 0) {
        movePrev();
        if (afterCursor->data == x) {
            return pos_cursor;
        }
    }
    return -1;
}

// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called
void List::cleanup() {

    // For each element N:
    for (Node* N = frontDummy->next; N != backDummy; N = N->next) {

        // For each element M that follows N:
        for (Node* M = N->next; M != backDummy;) {

            Node* R = M;
            M = M->next;

            // Is R a repeat of N?
            if (R->data == N->data) { // Then delete it!

                // 1. Adjust cursor (if necessary)

                // Is R directly after the cursor? Move afterCursor next
                if (R == afterCursor) afterCursor = afterCursor->next;

                // Is R directly before the cursor? Move beforeCursor prev
                if (R == beforeCursor) beforeCursor = beforeCursor->prev;

                // 2. Splice out R
                R->prev->next = R->next;
                R->next->prev = R->prev;

                // 3. Delete R
                delete R;
                num_elements--;
            }
        }
    }

    // Set pos_cursor
    pos_cursor = 0;
    for (Node* N = frontDummy->next; N != backDummy; N = N->next) {
        if (N == afterCursor) break;
        pos_cursor++;
    }
}

// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0
List List::concat(const List& L) const {
    List R;
    for (Node* N = frontDummy->next; N != backDummy; N = N->next) {
        R.insertBefore(N->data);
    }
    for (Node* N = L.frontDummy->next; N != L.backDummy; N = N->next) {
        R.insertBefore(N->data);
    }
    R.moveFront();
    return R;
}

// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses
std::string List::to_string() const {
    if (num_elements == 0) return "()";
    std::string s = "(";

    Node* N = frontDummy->next;
    s += std::to_string(N->data);

    for (N = N->next; N != backDummy; N = N->next) {
        s += ", " + std::to_string(N->data);
    }

    return s + ")";
}

// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged
bool List::equals(const List& R) const {
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = (this->num_elements == R.num_elements);
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while (eq && N != this->backDummy) {
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return eq;
}

// ██ Overriden Operators ██

// operator<<()
// Inserts string representation of L into stream
std::ostream& operator<<(std::ostream& stream, const List& L) {
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged
bool operator==(const List& A, const List& B) {
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L
List& List::operator=(const List& L) {
    if (this != &L) { // Not self assignment
        // Make a temporary copy of L
        List temp = L;

        // Swap fields
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(num_elements, temp.num_elements);
        std::swap(pos_cursor, temp.pos_cursor);
    }

    return *this;
}
