#include "Treap.h"
#include<iostream>
using namespace std;
int main() {
	Treap tree;
	tree.add(7, 4);
	tree.print();
	cout << endl;
	tree.add(13, 2);
	tree.print();
	cout << endl;
	tree.add(2, 3);
	tree.print();
	cout << endl;
	tree.add(5, 2);
	tree.print();
	cout << endl;
	tree.add(34, 6);
	tree.print();
	cout << endl;
	tree.add(0, 0);
	tree.print();
	cout << endl;
	tree.del(2);
	tree.print();
	cout << endl;
	return 0;
}