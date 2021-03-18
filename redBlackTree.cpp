#include<bits/stdc++.h>
#include<chrono>
using namespace std;


template<typename T> 
class LLRBTNode{
public:
    LLRBTNode<T>* left, *right;
    bool colour:1;
    // could expand to count
    T value;
    LLRBTNode(T value): value(value), colour(1){}
    LLRBTNode(T value, bool colour): value(value), colour(colour){}
};

// set

template<typename T> 
class LLRedBlackTree {
    LLRBTNode<T>* root;
    std::size_t sz;
private:

    bool isRed(LLRBTNode<T>* node) {
    if(node==NULL) return false;
    return node->colour;
    }

    bool contain(T value, LLRBTNode<T>* search) {
        if(search==nullptr) return false;
        if(value==search->value) return true;
        if(value > search->value) return contain(value, search->right); 
        return contain(value, search->left);
    }
    LLRBTNode<T>* rotateLeft(LLRBTNode<T>* node) {
        if(!isRed(node->right)) return node;
        LLRBTNode<T>* newPos = node->right, *newInfNode = node->right->left;
        newPos->left = node;
        node->right = newInfNode;
        newPos->colour=node->colour;
        node->colour = 1;
        return newPos;
    }
    LLRBTNode<T>* rotateRight(LLRBTNode<T>* node) {
        if(node->left==NULL||!isRed(node->left->left)) return node;
        LLRBTNode<T>* newPos = node->left, * lright=node->left->right;
        newPos->right = node;
        node->left = lright;
        newPos->colour=node->colour;
        node->colour = 1;
        return newPos;
    }
    void flipColours(LLRBTNode<T>* node) {
        if(isRed(node->left)&&isRed(node->right)) {
            node->left->colour = node->right->colour = 0;
            node->colour = 1;
        }
    }
    LLRBTNode<T>* _insert(LLRBTNode<T>*node, T value) {
        if(node==nullptr){ sz++; return new LLRBTNode<T>(value); }
        if(value > node->value) node->right = _insert(node->right, value); // insert in right side
        if(value < node->value) node->left = _insert(node->left,value); // insert in left side
        // else node->value = (given key) -> this is more for maps...
        if(isRed(node->right)&&!isRed(node->left)) node = rotateLeft(node); // right red link: left rotation
        if(isRed(node->left)&&isRed(node->left->left)) node = rotateRight(node); // two consecutive left links: right rotation
        if(isRed(node->right)&&isRed(node->left)) flipColours(node); // colour flipping
        return node;
    }
    void destroy(LLRBTNode<T>* node) {
        if(node==NULL) return;
        destroy(node->right);
        destroy(node->left);
        delete node;
    }

public:
    bool contains(T value) {return contain(value, root);}
    void insert(T value) { root = _insert(root, value); }
    std::size_t size(){return sz;}
    LLRedBlackTree<T>(): root(nullptr), sz(0){}
    ~LLRedBlackTree<T>(){destroy(root);};
};

void user_interaction() {
        cout<<"How many elements to insert?"<<endl;
    int elem; cin>>elem;
    cout<<"Enter "<<elem<<" integers.\n";
    auto tree = LLRedBlackTree<long long int>();
    for(int i = 0; i<elem; i++) {
        int a; cin>>a;
        if(tree.contains(a)) {
            cout<<"Element already in tree"<<endl;
        }
        else tree.insert(a);
    }
    cout<<"Size of tree: "<<tree.size()<<endl;
}

void test_industrial() {
    int f = 1000000;
    auto tree = LLRedBlackTree<string>();
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<f; i++) {
        tree.insert(to_string(i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    double d = chrono::duration<double, micro>(end-start).count();
    cout<<"Insertion of "<<f<<" elements in "<<d/1000000.0<<" second(s)."<<endl;
    for(int i = 0; i<f; i++) {
        if(!tree.contains(to_string(i))) {
            cout<<"Problem: "<<i<<" is not contained!\n";
        }
    }
}

void test_times(int f) {
    cout<<f<<" ";
    auto tree = LLRedBlackTree<int>();
    auto start_insertion = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<f; i++) {
        tree.insert(i);
    }
    auto end_insertion = std::chrono::high_resolution_clock::now();
    double dur_insertion = chrono::duration<double, micro>(end_insertion-start_insertion).count();
    printf("%.3f ", dur_insertion);
    auto start_search = std::chrono::high_resolution_clock::now();
    for(int i = 0; i<f; i++) {
        if(!tree.contains(i)) {
            cout<<"Problem: "<<i<<" is not contained!\n";
        }
    }
    auto end_search = std::chrono::high_resolution_clock::now();
    double dur_search = chrono::duration<double, micro>(end_search-start_search).count();
    printf("%.3f\n", dur_search);
}

int main(int argc, char** argv) {
    int test;
    if(argc>1) test = atoi(argv[1]);
    else cin>>test;
    test_times(test);
    return 0;
}