#pragma once
#ifndef __BTREE_H__
#define __BTREE_H__
#include "Node.h"

class BTree {
private:
	void InitTree();
	bool isVerticalSplit;
public:
	Nodeptr root;
	BTree(int level, float x, float y, float w, float h, bool isVerticalSplit) {
		Create(level, x, y, w, h, isVerticalSplit);
	}

	Nodeptr MakeNode(int level, float x, float y, float w, float h);
	void Create(int level, float x, float y, float w, float h, bool isVerticalSplit);
	void Insert(Nodeptr root, GameObject* e);
	bool Split(Nodeptr root);
	void Retrieve(Nodeptr root, std::vector<GameObject*>& objects,Bound source);
	void Traversal(Nodeptr root);
	void RemoveGameObjectForUpdate(Nodeptr root, GameObject* e);
	void Clear(Nodeptr root);
};
#endif // !__BTREE_H__
