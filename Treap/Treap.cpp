#include "Treap.h"
#include<iostream>
Treap::Treap() {
	root = nullptr;
}
Treap::~Treap() {
	deleteTree(root);
}
//Return new merged tree. Node with bigger priority go to root
node* Treap::merge(node* root1, node* root2) {
	if (root1 == nullptr)
		return root2;
	if (root2 == nullptr)
		return root1;
	if (root1->key < root2->key) {
		if (root1->priority > root2->priority) {
			root1->right = merge(root1->right, root2);
			return root1;
		}
		else {
			root2->left = merge(root1, root2->left);
			return root2;
		}
	}
	else {
		if (root1->priority > root2->priority) {
			root1->left = merge(root2, root1->left);
			return root1;
		}
		else {
			root2->right = merge(root2->right, root1);
			return root2;
		}
	}
}
node* Treap::split(node* root, double key) {
	if (root == nullptr)
		return nullptr;
	if (root->key == key)
		return root;
	if (root->key > key) {
		if (root->left != nullptr && root->left->key == key)
			root->left = nullptr;
		return split(root->left, key);
	}
	if (root->key < key) {
		if (root->right != nullptr && root->right->key == key)
			root->right = nullptr;
		return split(root->right, key);
	}
}
void Treap::add(node* nod) {
	node* splres = split(root,nod->key);
	splres = merge(splres, nod);
	root = merge(splres, root);
}
void Treap::add(double key, double priority) {
	node* nod = new node;
	nod->key = key;
	nod->priority = priority;
	node* splres = split(root, key);
	splres = merge(splres, nod);
	root = merge(splres, root);
}
void Treap::del(double key) {
	root = del(key, root);
}
node* Treap::del(double key,  node* root) {
	if (root == nullptr)
		return nullptr;
	if (root->key > key) {
		root->left = del(key, root->left);
		return root;
	}
	if (root->key < key) {
		root->right = del(key, root->right);
		return root;
	}
	if (root->key == key) {
		node* newRoot = merge(root->left, root->right);
		delete root;
		return newRoot;
	}
}
void Treap::print(node* root) const{
	if (root == nullptr)
		return;
	std::cout << "(" << root->key << "," << root->priority << ") ";
	print(root->left);
	print(root->right);
}
void Treap::print() const{
	print(root);
}
void Treap::deleteTree(node* root){
	if (root == nullptr)
		return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}