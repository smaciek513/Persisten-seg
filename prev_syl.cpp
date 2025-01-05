#include <climits>
#include <memory>
#include "prev.h"

using namespace std;
#define node_ptr shared_ptr<struct Node>

// Node structure : the maximum index in the range and pointers to low and high children
struct Node{
    int max_index;
    node_ptr leftChild, rightChild;

    Node(int i) : max_index(i), leftChild(nullptr), rightChild(nullptr) {}
};

// Vector of roots of a persistent segment tree
vector<node_ptr>SegmentTree;

// Adds a new root to the segment tree
void addRoot(int i){
    node_ptr root = make_shared<Node>(i);
    SegmentTree.push_back(root);
}

bool Leaf(node_ptr node){
    return node->leftChild == nullptr && node->rightChild == nullptr;
}

void pushBack(int value){
    int i = (int)SegmentTree.size();
    addRoot(i-1);
    node_ptr prev = SegmentTree[i-1];    
    node_ptr curr = SegmentTree[i];
    int lo = INT_MIN, hi = INT_MAX;
    while (lo < hi){
        long long mid = (long long)lo + ((long long)hi - lo)/2;
        node_ptr nxt = make_shared<Node>(i);
        if (value <= mid){
            if (prev) curr->rightChild = prev->rightChild;
            curr->leftChild = nxt;
            hi = (int)mid;
            if (prev) prev = prev->leftChild;
        } else {  
            if (prev) curr->leftChild = prev->leftChild;
            lo = (int)mid+1;
            curr->rightChild = nxt;
            if (prev) prev = prev->rightChild;
        }
        curr = nxt;
    } 
}

void init(const std::vector<int> &seq){
    // Added a dummy root with index -1 for easier implementation
    addRoot(-1);
    for (int i = 0; i<(int)seq.size(); i++){
        pushBack(seq[i]);
    }
}

// Recursive function to get the maximum index in the range [lo, hi], 
// given the current node and its range [curr_lo, curr_hi].
int get_max(node_ptr node, int lo, int hi, int curr_lo, int curr_hi){
    if (curr_lo > hi || curr_hi < lo) return 0;
    if (curr_lo >= lo && curr_hi <= hi) return node->max_index;
    long long mid = (long long)curr_lo + ((long long)curr_hi - curr_lo)/2;
    int low = (node->leftChild ? get_max(node->leftChild, lo, hi, curr_lo, (int)mid) : 0);
    int high = (node->rightChild ? get_max(node->rightChild, lo, hi, (int)mid+1, curr_hi) : 0);
    return max(low, high);
}

int prevInRange(int i, int lo, int hi){
    return get_max(SegmentTree[i+1], lo, hi, INT_MIN, INT_MAX) - 1;
}

void done(){
    SegmentTree.clear();
}