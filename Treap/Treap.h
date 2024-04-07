#pragma once
#include<concepts>
#include<iostream>
template<typename T>
concept Comparable = requires(T const& a, T const& b) {
	{a > b} -> std::convertible_to<bool>;
	{a < b} -> std::convertible_to<bool>;
	{a == b} -> std::convertible_to<bool>;
};
template <typename T>
concept Printable = requires(T const& t) {
	{ std::cout << t } -> std::convertible_to<std::ostream&>;
};
template< Comparable T>
requires Printable<T>
struct node {
	T key;
	double priority = 0;
	node<T>* left = nullptr;
	node<T>* right = nullptr;
};

template< Comparable T>
	requires Printable<T>
class Treap
{
	node<T>* root;
	node<T>* merge(node<T>* root1, node<T>* root2);
	node<T>* split(node<T>* root, T key);
	node<T>* del(T key, node<T>* root);
	void print(node<T>* root) const;
	void deleteTree(node<T>* root);
public:
	Treap();
	~Treap();
	void add(node<T>* nod);
	void add(T key, double priority);
	void del(T key);
	void print() const;
};

template< Comparable T>
	requires Printable<T>
Treap<T>::Treap() {
	root = nullptr;
}
template< Comparable T>
	requires Printable<T>
Treap<T>::~Treap() {
	deleteTree(root);
}
//Return new merged tree. Node with bigger priority go to root
template< Comparable T>
	requires Printable<T>
node<T>* Treap<T>::merge(node<T>* root1, node<T>* root2) {
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
template< Comparable T>
	requires Printable<T>
node<T>* Treap<T>::split(node<T>* root, T key) {
	if (root == nullptr)
		return nullptr;
	if (root->key == key)
		return root;
	if (root->key > key) {
		node* subTree = root->left;
		if (root->left != nullptr && root->left->key == key)
			root->left = nullptr;
		return split(subTree, key);
	}
	if (root->key < key) {
		node* subTree = root->right;
		if (root->right != nullptr && root->right->key == key)
			root->right = nullptr;
		return split(subTree, key);
	}
}
template< Comparable T>
	requires Printable<T>
void Treap<T>::add(node<T>* nod) {
	node* splres = split(root, nod->key);
	splres = merge(splres, nod);
	root = merge(splres, root);
}
template< Comparable T>
	requires Printable<T>
void Treap<T>::add(T key, double priority) {
	node<T>* nod = new node<T>;
	nod->key = key;
	nod->priority = priority;
	node<T>* splres = split(root, key);
	splres = merge(splres, nod);
	root = merge(splres, root);
}
template< Comparable T>
	requires Printable<T>
void Treap<T>::del(T key) {
	root = del(key, root);
}
template< Comparable T>
	requires Printable<T>
node<T>* Treap<T>::del(T key, node<T>* root) {
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
		node<T>* newRoot = merge(root->left, root->right);
		delete root;
		return newRoot;
	}
}
template< Comparable T>
	requires Printable<T>
void Treap<T>::print(node<T>* root) const {
	if (root == nullptr)
		return;
	std::cout << "(" << root->key << "," << root->priority << ") ";
	print(root->left);
	print(root->right);
}
template< Comparable T>
	requires Printable<T>
void Treap<T>::print() const {
	print(root);
}
template< Comparable T>
	requires Printable<T>
void Treap<T>::deleteTree(node<T>* root) {
	if (root == nullptr)
		return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}