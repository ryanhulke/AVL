#include <queue>
#include <iostream>
#include <string>
using namespace std;

class AVL {
    public:
    struct node {
        string NAME;
        int ID;
        int height;
        node* left;
        node* right;
        node(string name, int id) : NAME(name), ID(id), left(nullptr), right(nullptr), height(1){}
    };
    node* root = nullptr;
    int nodeCount = 0;
    node* insert(string NAME, int ID){
        if (search(ID) != nullptr) {
            return nullptr;
        }
        return insert(NAME, ID, root);
    }
    bool  remove(int ID){
        node* n = search(ID);
        if (n == nullptr) return false;
        root = remove(ID, root);
        return true;
    }
    node* search(int ID){
        return search(ID, root);
    }
    void search(string name, vector<node*>& v){
        search(name, root, v);
    }
    void printPreorder(){
        vector<node*> v;
        getPreorder(root, v);
        for (int i = 0; i < v.size(); i++){
            cout << v[i]->NAME;
            if (i != v.size() - 1) cout << ", ";
        }
        cout << endl;
    }
    void printInorder(){
        vector<node*> v;
        getInorder(root, v);
        for (int i = 0; i < v.size(); i++){
            cout << v[i]->NAME;
            if (i != v.size() - 1) cout << ", ";
        }
        cout << endl;
    }
    void printPostorder(){
        vector<node*> v;
        getPostorder(root, v);
        for (int i = 0; i < v.size(); i++){
            cout << v[i]->NAME;
            if (i != v.size() - 1) cout << ", ";
        }
        cout << endl;
    }
    void printLevelCount(){
        printLevelCount(root);
    }
    bool removeInorder(int n){
        if (n < 0 || n >= nodeCount) return false;
        removeInorder(root, n);
        return true;
    }
    private:
    node* insert(string NAME, int ID, node* head){
        if (head == nullptr){
            head = new node(NAME, ID);
            if (root == nullptr) root = head;
            nodeCount++;
            return head;
        }
        if(ID < head->ID) head->left = insert(NAME, ID, head->left);
        else if(ID > root->ID) head->right = insert(NAME, ID, head->right);
        // balance
        int balance = height(head->left) - height(head->right);
         if(balance < -1){
            if(ID < head->right->ID) return rlRotate(head);
            else return llRotate(head);
        } else if(balance > 1){
            if(ID > head->left->ID) return lrRotate(head);
            else return rrRotate(head);
        }
        return head;
    }
    node* llRotate(node* head) {
        node* temp = head->right;
        if (head == root) root = temp;
        head->right = temp->left;
        temp->left = head;
        head->height = 1 + max(height(head->left), height(head->right));
        temp->height = 1 + max(height(temp->left), height(temp->right));
        return temp;
    }
    node* rrRotate(node* head) {
        node* temp = head->left;
        if (head == root) root = temp;
        head->left = temp->right;
        temp->right = head;
        head->height = 1 + max(height(head->left), height(head->right));
        temp->height = 1 + max(height(temp->left), height(temp->right));
        return temp;
    }
    node* lrRotate(node* head) {
        head->left = llRotate(head->left);
        return rrRotate(head);
    }
    node* rlRotate(node* head) {
        head->right = rrRotate(head->right);
        return llRotate(head);
    }
    void getInorder(node* head, vector<node*>& v){
        if(head == nullptr) return;
        getInorder(head->left, v);
        v.push_back(head);
        getInorder(head->right, v);
    }
    void getPreorder(node* head, vector<node*>& v){
        if(head == nullptr) return;
        v.push_back(head);
        getPreorder(head->left, v);
        getPreorder(head->right, v);
    }
    void getPostorder(node* head, vector<node*>& v){
        if(head == nullptr) return;
        getPostorder(head->left, v);
        getPostorder(head->right, v);
        v.push_back(head);
    }
    void removeInorder(node* head, int n){
        static int count = 0;
        if(head == nullptr) return;
        if (count <= n){
            removeInorder(head->left, n);
            count++;
            if(count == n+1){
                remove(head->ID);
            }
            removeInorder(head->right, n);
        }
    }
    node* search(int ID, node* head){
        // binary search
        if(head == nullptr || ID == head->ID) {
            return head;
        }
        if(ID < head->ID) return search(ID, head->left);
        else return search(ID, head->right);
    }
    void search(string name, node* head, vector<node*>& v){
        // pre-order traversal since not sorted by name
        if (head == nullptr) return;
        if(head->NAME == name) v.push_back(head);
        search(name, head->left, v);
        search(name, head->right, v);
    }
    node* remove(int ID, node* head){
        if(head == nullptr) return head;
        if(ID < head->ID) head->left = remove(ID, head->left);
        else if(ID > head->ID) head->right = remove(ID, head->right);
        else{
            if(head->left == nullptr){
                node* temp = head->right;
                delete head;
                nodeCount--;
                head = temp;
            } else if(head->right == nullptr){
                node* temp = head->left;
                delete head;
                nodeCount--;
                head = temp;
            } else {
                // find largest node in left subtree, replace removed node with it
                node* temp = head->left;
                while(temp->right != nullptr){
                    temp = temp->right;
                }
                head->ID = temp->ID;
                head->NAME = temp->NAME;
                head->left = remove(temp->ID, head->left);
            }
        }
        if (head == nullptr) return head;
        // update height and balance
        head->height = 1 + max(height(head->left), height(head->right));
        int balance = height(head->left) - height(head->right);
         if(balance < -1){
            if(!(head->right->right)) return rlRotate(head);
            else {
                return llRotate(head);
            }
        } else if(balance > 1){
            if(!(head->left->left)) return lrRotate(head);
            else return rrRotate(head);
        }
        return head;
    }
    int height(node* head){
        if(head == nullptr) 
            return 0;
        return head->height;
    }

    void printLevelCount(node* head){
        if (head == nullptr){
            std::cout << 0 << endl;
            return;
        }
        int level = 0;
        queue<node*> q;
        int nodesOnThisLevel = 1;
        int nodesOnNextLevel = 0;
        q.push(head);
        while(!q.empty()){
            node* node = q.front();
            q.pop();
            nodesOnThisLevel--;
            if (node->left){
                q.push(node->left);
                nodesOnNextLevel++;
            }
            if (node->right){
                q.push(node->right);
                nodesOnNextLevel++;
            }
            if (nodesOnThisLevel == 0){   
                // queue is on the next level
                nodesOnThisLevel = nodesOnNextLevel;
                level++;
                nodesOnNextLevel = 0;
            }
        }
        cout << level << endl;
    }
}; 