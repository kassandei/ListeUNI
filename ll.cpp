#include <iostream>
#include <stdexcept>

using namespace std;

// A single node of the singly-linked list.
struct cell {
    int   value;  // data
    cell* next;   // link: pointer to the next node (nullptr if last)
};

class ll {
    public:
        ll();                    // default constructor
        ll(const ll& other);         // copy constructor
        ~ll();                   // destructor

        void prepend(int e);            // O(1) – insert at head
        void append(int e);             // O(N) – insert at tail
        void print() const;             // forward print
        void print_rev() const;         // reverse print (recursive)
        bool is_present(int e) const;   // true if e appears at least once

        int&       at(int pos);         // writable  indexed access; throws out_of_range
        const int& at(int pos) const;   // read-only indexed access; throws out_of_range

        void remove     (int e);        // remove first  occurrence of e
        void remove_last(int e);        // remove last   occurrence of e

        // ── Exercise methods ─────────────────────────────────────────────────

        int  sum() const;               // sum of all elements (recursive)
        void remove_all (int e);        // remove all    occurrences of e
        void remove_up_to_sum(int s);   // remove nodes whose suffix-sum is <= s
        void flip();                          // reverse the list in place (recursive)
        void double_even();                   // insert a copy after every even node (recursive)
        bool equal(const ll& other) const;    // recursive element-wise equality
        bool countfrom0(int& count) const;    // count elements after the last 0

        bool operator==(const ll& other) const;  // element-wise equality
        ll   operator+ (const ll& other) const;  // concatenation (new list)
        ll&  operator= (const ll& other);         // copy-assignment (copy-and-swap)
    private:
        cell* head;  // pointer to the first node; nullptr when the list is empty

        // ── Private helpers ──────────────────────────────────────────────────
        void print_rev_rec(cell* curr) const;
        int  sum_rec(cell* curr) const;
        bool remove_last_rec(int e, cell* curr, cell* previous);  // version 1 (with prev ptr)
        bool remove_last_rec(int e, cell*& curr);                 // version 2 (ref-to-ptr)
        int  remove_up_to_sum_rec(int s, cell*& curr);
        bool equal    (cell* head,  cell* head_other)  const;  // iterative equality
        bool equal_rec(cell* curr,  cell* curr_other)  const;  // recursive equality
        void flip_rec        (cell*& curr);
        void double_even_rec (cell*& curr);
        bool countfrom0_rec  (cell* curr, int& count) const;
};

// Default constructor: initialise an empty list.
ll::ll(){
    head = nullptr;  // no nodes yet
}

// Copy constructor: build a deep copy of l, preserving element order.
ll::ll(const ll& other){
    head = nullptr;
    cell* curr = nullptr;   // tail of the list being built (for O(1) append)
    cell* curr_other   = other.head;    // iterator over the source list
    while(curr_other != nullptr){
        cell* nc = new cell{curr_other->value, nullptr};  // allocate a new node with same value
        if(head == nullptr){
            // first node: both head and curr point to it
            head = nc;
            curr = nc;
        }else{
            // link new node at the tail and advance curr
            curr->next = nc;
            curr = curr->next;
        }
        curr_other = curr_other->next;  // move to the next source node
    }
}

// Destructor: free every node iteratively to avoid stack overflow on long lists.
ll::~ll(){
    while(head != nullptr){
        cell* tmp = head;       // save pointer to the node to delete
        head = head->next;      // advance head before deletion
        delete tmp;
    }
}

// prepend: insert e at the front of the list – O(1).
void ll::prepend(int e){
    cell* nc = new cell{e, head};  // new node points to the current head
    head = nc;                     // head now points to the new node
}

// append: insert e at the tail of the list – O(N).
void ll::append(int e){
    cell* curr = head;
    cell* nc   = new cell{e, nullptr};  // new node with no successor
    if(curr == nullptr){
        head = nc;              // empty list: new node becomes the head
    }else{
        // walk to the last node
        while(curr->next != nullptr){
            curr = curr->next;
        }
        curr->next = nc;        // link the new node after the last one
    }
}

// print: iterate from head and print each value, then a newline.
void ll::print() const{
    cell* curr = head;
    while(curr != nullptr){
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl;
}

// is_present: linear scan from head; returns true on the first match.
bool ll::is_present(int e) const{
    cell* curr = head;
    while(curr != nullptr){
        if(curr->value == e)
            return true;        // found: stop early
        curr = curr->next;
    }
    return false;               // reached end without a match
}

// at (writable): walk pos steps from head and return a reference to the value.
// Throws std::out_of_range if pos >= list length.
int& ll::at(int pos){
    cell* curr = head;
    for(int i = 0; curr != nullptr && i != pos; i++){
        curr = curr->next;
    }
    if(curr == nullptr){
        throw std::out_of_range("OOR Error");  // pos was beyond the last node
    }
    return curr->value;  // reference allows both read and write: list.at(2) = 5
}

// at (read-only): const overload used when the list object is const.
const int& ll::at(int pos) const{
    cell* curr = head;
    for(int i = 0; curr != nullptr && i != pos; i++){
        curr = curr->next;
    }
    if(curr == nullptr){
        throw std::out_of_range("OOR Error");
    }
    return curr->value;
}

// remove: remove the FIRST occurrence of n.
void ll::remove(int n){
    cell* curr     = head;
    cell* previous = nullptr;
    // walk until we find n or reach the end
    while(curr != nullptr && curr->value != n){
        previous = curr;
        curr     = curr->next;
    }
    if (curr != nullptr){           // n was found
        if(previous == nullptr)
            head = curr->next;      // removing the head: update head
        else
            previous->next = curr->next; // bypass the found node
        delete curr;
    }
}

// print_rev: public wrapper that starts the recursion and prints the final newline.
void ll::print_rev() const{
    print_rev_rec(head);
    cout << endl;
}

// print_rev_rec: recurse to the end of the list, then print on the way back.
// This reverses the print order without extra data structures.
void ll::print_rev_rec(cell* curr) const{
    if (curr != nullptr){
        print_rev_rec(curr->next);  // go deeper first
        cout << curr->value << " "; // print after the recursive call returns
    }
}

// remove_last: public wrapper – delegates to one of the two recursive helpers.
void ll::remove_last(int e){
    // remove_last_rec(e, head, nullptr);  // version 1 (explicit prev pointer)
    remove_last_rec(e, head);              // version 2 (reference-to-pointer)
}

// remove_last_rec (version 1, with explicit prev pointer):
// Recurse to the end first; on the way back, remove the node only if no
// deeper call already removed one (removed == false).
bool ll::remove_last_rec(int e, cell* curr, cell* previous){
    if (curr == nullptr){
        return false;   // base case: end of list, nothing removed yet
    }
    bool removed = remove_last_rec(e, curr->next, curr);  // recurse deeper
    if(!removed && curr->value == e){
        // this is the last (rightmost) occurrence not yet removed
        if(previous == nullptr)
            head = curr->next;        // removing the head
        else
            previous->next = curr->next;
        delete curr;
        return true;
    }
    return removed;
}

// remove_last_rec (version 2, reference-to-pointer):
// Uses cell*& curr so we can relink the caller's pointer without a separate prev.
bool ll::remove_last_rec(int e, cell*& curr){
    if (curr == nullptr){
        return false;   // base case: end of list
    }
    // NOTE: pass curr (not curr->next) as the *previous* pointer to next call
    bool removed = remove_last_rec(e, curr->next, curr);  // still uses version 1 internally
    if(!removed && curr->value == e){
        cell* tmp = curr;
        curr = curr->next;  // relink caller's pointer to skip this node
        delete tmp;
    }
    return removed;
}


// ─────────────────────────────────────────────────────────────────────────────
// EXERCISE – remove_last alternative version (reference-to-pointer)
// ─────────────────────────────────────────────────────────────────────────────
// Implement an alternative version of remove_last_rec with the following recursive function:
// bool ll::remove_last_rec(int e, cell*& curr)

bool ll::remove_last_rec(int e, cell*& curr){

}

// ─────────────────────────────────────────────────────────────────────────────
// EXERCISE – operator== (element-wise equality)
// ─────────────────────────────────────────────────────────────────────────────
// Return true iff the two lists have the same length and the same values in
// the same order.  Implement both an iterative version (equal) and a recursive
// version (equal_rec); operator== delegates to equal_rec.
//
// Examples:
//   [1 2 3] == [1 2 3]  → true
//   [1 2 3] == [1 2]    → false  (different lengths)
//   [1 2]   == [1 3]    → false  (different values)
//   []      == []       → true
// ─────────────────────────────────────────────────────────────────────────────

bool ll::operator==(const ll& other) const{

}

bool ll::equal(cell* head, cell* head_other) const{
    
}

bool ll::equal_rec(cell* curr, cell* curr_other) const{
  
}

// ─────────────────────────────────────────────────────────────────────────────
// EXERCISE – operator+ (list concatenation)
// ─────────────────────────────────────────────────────────────────────────────
// Return a NEW list that is the concatenation of *this followed by other.
// Both source lists must remain unchanged.
//
// Examples:
//   [1 2] + [3 4]  → [1 2 3 4]
//   []    + [1 2]  → [1 2]
//   [1 2] + []     → [1 2]
//   []    + []     → []
// ─────────────────────────────────────────────────────────────────────────────

ll ll::operator+(const ll& other) const{
   
}

// ─────────────────────────────────────────────────────────────────────────────
// EXERCISE – operator= (copy-assignment)
// ─────────────────────────────────────────────────────────────────────────────
// Implement the copy-assignment operator so that *this becomes a deep copy of
// other, correctly freeing the current content.  Handle self-assignment safely.
//
// Examples:
//   ll a = [1 2 3]; ll b; b = a;  → b == [1 2 3], a unchanged
//   a = a;                        → no-op (self-assignment)
// ─────────────────────────────────────────────────────────────────────────────

ll& ll::operator=(const ll& other){

}

// ─────────────────────────────────────────────────────────────────────────────
// EXERCISE – sum (sum of all elements, recursive)
// ─────────────────────────────────────────────────────────────────────────────
// Compute the sum of all values in the list using recursion.
//
// Examples:
//   []              → 0
//   [1]             → 1
//   [1, 2, 3]       → 6
//   [0, 1, 2, 3, 4] → 10
// ─────────────────────────────────────────────────────────────────────────────

int ll::sum() const{

}

int ll::sum_rec(cell* curr) const{

}

// ─────────────────────────────────────────────────────────────────────────────
// EXERCISE – remove_all (remove every occurrence of a value)
// ─────────────────────────────────────────────────────────────────────────────
// Remove ALL nodes whose value equals e from the list.
//
// Examples:
//   [1 2 1 1 3], remove_all(1) → [2 3]
//   [1 1 1],     remove_all(1) → []
//   [1 2 3],     remove_all(9) → [1 2 3]  (not present – no change)
// ─────────────────────────────────────────────────────────────────────────────

void ll::remove_all(int e){

}

// ─────────────────────────────────────────────────────────────────────────────
// EXERCISE – remove_up_to_sum (remove nodes by suffix-sum threshold)
// ─────────────────────────────────────────────────────────────────────────────
// Remove every node whose suffix-sum (the node's value plus all values to its
// right) is <= s.
//
// Examples:
//   [3 1 2 4 5], remove_up_to_sum(6)  → [3 1 2 4]
//   [1 2 3],     remove_up_to_sum(10) → []
//   [1 2 3],     remove_up_to_sum(0)  → [1 2 3]
// ─────────────────────────────────────────────────────────────────────────────

void ll::remove_up_to_sum(int s){

}

int ll::remove_up_to_sum_rec(int s, cell*& curr){

}

// ─────────────────────────────────────────────────────────────────────────────
// EXERCISE – flip (reverse a list in place)
// ─────────────────────────────────────────────────────────────────────────────
// Reverse the list in-place using recursion.
//
// Examples:
//   []          → []
//   [1]         → [1]
//   [1 2]       → [2 1]
//   [1 2 3]     → [3 2 1]
//   [1 2 3 4 5] → [5 4 3 2 1]
// ─────────────────────────────────────────────────────────────────────────────

void ll::flip(){

}

void ll::flip_rec(cell*& curr){

}

// ─────────────────────────────────────────────────────────────────────────────
// EXERCISE – double_even (duplicate every even-valued node in place)
// ─────────────────────────────────────────────────────────────────────────────
// Traverse the list recursively and, for each node holding an even value,
// insert a new node with the same value immediately after it.
//
// Examples:
//   [2 7 0 5]  → [2 2 7 0 0 5]
//   [1 3 5]    → [1 3 5]         (no evens, unchanged)
//   [2 4 6]    → [2 2 4 4 6 6]
//   []         → []
//   [0]        → [0 0]
// ─────────────────────────────────────────────────────────────────────────────

void ll::double_even_rec(cell*& curr){

}

void ll::double_even(){

}

// ─────────────────────────────────────────────────────────────────────────────
// EXERCISE – equal (recursive element-wise equality)
// ─────────────────────────────────────────────────────────────────────────────
// Return true iff the two lists contain the same values in the same order.
// Implement it recursively.
//
// Examples:
//   []    vs []         → true
//   [1 2] vs [1 2]      → true
//   [1 2] vs [1 2 3]    → false  (different lengths)
//   [1 2] vs [1 3]      → false  (different values)
//   [1]   vs []         → false
// ─────────────────────────────────────────────────────────────────────────────

bool ll::equal(const ll& other) const{

}

// ─────────────────────────────────────────────────────────────────────────────
// EXERCISE – countfrom0 (count elements after the last zero)
// ─────────────────────────────────────────────────────────────────────────────
// Recursively scan the list and count the number of elements that appear after
// the LAST zero.  Use an output parameter for the count.
//
// Returns true  + count = number of elements after the last 0
//         false + count = total length of the list  (no 0 found)
//
// Examples:
//   [3 0 5 2]      → true,  count = 2  (5 and 2 are after last 0)
//   [1 0 2 0 7]    → true,  count = 1  (7 is after last 0)
//   [1 2 3]        → false, count = 3  (no 0, full length)
//   [0 0 0]        → true,  count = 0  (last 0 is the last node)
//   []             → false, count = 0
// ─────────────────────────────────────────────────────────────────────────────

bool ll::countfrom0(int& count) const{

}

bool ll::countfrom0_rec(cell* curr, int& count) const{

}

///// MAIN /////
int main(){
    return 0;
}
