#include <iostream>
#include <string>
#include "AVLTree.h"
using namespace std;


bool checkName(string name){
	for (int i = 0; i < name.length(); i++){
		char l = name[i];
		if (l < 65 || (l > 90 && l < 97 && l != 94) || l > 122)
			return false;
	}
	return true;
}

int main(){
	AVL avl;
	int numCommands;
	cin >> numCommands;
	for (int i = 0; i < numCommands; i++){
		string cmd;
		cin >> cmd;
		if (cmd == "insert"){
			string name;
			string tempID;
			try {
				cin >> name;
				cin >> tempID;
				name = name.substr(1, name.length() - 2);
				if (tempID.length() != 8) {
					throw invalid_argument("invalid ID");
				}
				if (checkName(name) == false) {
					throw invalid_argument("invalid name");
				}
				int id = stoi(tempID);
				AVL::node* insertedNode = avl.insert(name, id);
				if (insertedNode == nullptr) cout << "unsuccessful" << endl;
				else cout << "successful" << endl;
			} catch(exception& e){
				cout << "unsuccessful" << endl;
			}
		} else if (cmd == "remove"){
			int id;
			try {
				cin >> id;
				bool removed = avl.remove(id);
				if (removed) cout << "successful" << endl;
				else cout << "unsuccessful" << endl;
			} catch(exception& e){
				cout << "unsuccessful" << endl;
			}
		} else if (cmd == "search"){
			int id;
			try {
				string input;
				cin >> input;
				if (input.substr(0, 1) == "\""){
					string name = input.substr(1, input.length() - 2);
					vector<AVL::node*> n;
					avl.search(name, n);
					if (n.size() == 0)
						cout << "unsuccessful" << endl;
					else {
						for (int i = 0; i < n.size(); i++){
							cout << n[i]->ID << endl;
						}
					}
				} else {
					id = stoi(input);
					AVL::node* n = avl.search(id);
					if (n != nullptr && n->ID == id)
						cout << n->NAME << endl;
					else cout << "unsuccessful" << endl;
				}
			} catch(exception& e){
				cout << "unsuccessful" << endl;
			}
		} else if (cmd == "printInorder"){
			avl.printInorder();
		} else if (cmd == "printPreorder"){
			avl.printPreorder();
		} else if (cmd == "printPostorder"){
			avl.printPostorder();
		} else if (cmd == "printLevelCount"){
			avl.printLevelCount();
		} else if (cmd == "removeInorder"){
			int n;
			cin >> n;
			bool removed = avl.removeInorder(n);
			if (removed) cout << "successful" << endl;
			else cout << "unsuccessful" << endl;
		} else {
			cout << "unsuccessful" << endl;
		}
	}
	return 0;
}