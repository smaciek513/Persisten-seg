#include <memory>
#include <climits>
#include "prev.h"

// To solve the problem we'll use Persistent Segment Tree
// Nodes are described by a numeric range [low, high] for which they hold the prevInRange() value
struct Node{
    int prev;
    int low, high;
    std::shared_ptr<Node> left_child = nullptr, right_child = nullptr;

    Node(int i, int lo, int hi){
        prev = i;
        low = lo;
        high = hi;
    }
};

// Vector of roots of Persisten Segment Tree
std::vector<std::shared_ptr<Node>> roots;

// Updates the nodes, which ranges include value (or creates them if they didn't exist before)
void add(std::shared_ptr<Node> node, std::shared_ptr<Node> old, int i, int value){
    if(node->low == node->high) return;

    int mid = node->low + (int)(((long long)node->high - (long long)node->low) / 2LL);
    if(value <= mid){
        node->left_child = std::make_shared<Node>(i, node->low, mid);
        if(old){
            node->right_child = old->right_child;
            add(node->left_child, old->left_child, i, value);
        }
        else{
            node->right_child = std::make_shared<Node>(-1, mid+1, node->high);
            add(node->left_child, old, i, value);
        }
    }
    else{
        node->right_child = std::make_shared<Node>(i, mid+1, node->high);
        if(old){
            node->left_child = old->left_child;
            add(node->right_child, old->right_child, i, value);
        }
        else{
            node->left_child = std::make_shared<Node>(-1, node->low, mid);
            add(node->right_child, old, i, value);
        }
    }
}

void pushBack(int value){ 
    int n = (int)roots.size();
    std::shared_ptr<Node> new_root = std::make_shared<Node>(n, INT_MIN, INT_MAX);
    roots.push_back(new_root);
    if(n == 0) add(roots[n], nullptr, n, value); 
    else add(roots[n], roots[n-1], n, value);
}

// We can initialize the elements from the given vector by using pushBack()
void init(const std::vector<int> &seq){
    for(unsigned int i = 0; i < seq.size(); i++){
        pushBack(seq[i]);
    }
}

// Finds nodes which ranges cover whole range [lo, hi] and returns max prev value from them
int find_max_prev(std::shared_ptr<Node> node, int lo, int hi){
    if(!node || node->low > hi || node->high < lo) return -1;
    if(node->low >= lo && node->high <= hi) return node->prev;
    return std::max(find_max_prev(node->left_child, lo, hi), find_max_prev(node->right_child, lo, hi));        
}

int prevInRange(int i, int lo, int hi){
    return find_max_prev(roots[i], lo, hi);
}

void done(){
    roots.clear();
}
