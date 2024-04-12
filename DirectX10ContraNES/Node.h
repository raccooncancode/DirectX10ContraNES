#pragma once
#ifndef __NODE_H__
#define __NODE_H__
#include <iostream>
#include "RectF.h"
#include <vector>
#include "GameObject.h"
using namespace std;
class Node {
public:
	Bound bound;
	std::vector<GameObject*> GameObjects;
	Node* left;
	Node* right;
	int level;
	Node() {
		this->level = 0;
		this->bound = NULL;
		this->left = NULL;
		this->right = NULL;
	}
	Node(int level, float x, float y, float w, float h) {
		this->level = level;
		this->bound = new RectF(x, y, w, h);
		this->left = NULL;
		this->right = NULL;
	}
	void print() {
		if (bound != NULL) {
			cout << "\nLevel: " << level;
			cout << "\nBound Left:" << bound->x;
			cout << "\nBound Right:" << bound->x + bound->w;
			cout << "\nBound Width:" << bound->w;
		}
	}
};
typedef Node* Nodeptr;
#endif // !__NODE_H__
