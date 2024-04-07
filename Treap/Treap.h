#pragma once
struct node {
	double key = 0;
	double priority =0;
	node* left = nullptr;
	node* right = nullptr;
};
class Treap
{
	node* root;
	node* merge(node* root1, node* root2);
	node* split(node* root, double key);
	node* del(double key, node* root);
	void print(node* root) const;
	void deleteTree(node* root);
public:
	Treap();
	~Treap();
	void add(node* nod);
	void add(double key, double priority);
	void del(double key);
	void print() const;
};

