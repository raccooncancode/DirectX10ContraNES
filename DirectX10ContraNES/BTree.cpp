#include "BTree.h"
#include "Camera.h"
void BTree::InitTree() {
	root = NULL;
}

Nodeptr BTree::MakeNode(int level, float x, float y, float w, float h) {
	Nodeptr p = new Node(level, x, y, w, h);
	return p;
}
void BTree::Create(int level, float x, float y, float w, float h, bool isVerticalSplit) {
	InitTree();
	this->root = MakeNode(level, x, y, w, h);
	this->isVerticalSplit = isVerticalSplit;
}
void BTree::Insert(Nodeptr root, GameObject* e) {
	if (root != NULL) {
		if (root->bound->IsOverlap(e->GetBound()))
			root->GameObjects.push_back(e);
		if (root->left == NULL && root->right == NULL) {
			if (Split(root)) {
				while (!root->GameObjects.empty()) {
					if (root->left->bound->IsOverlap(root->GameObjects.back()->GetBound()))
						Insert(root->left, root->GameObjects.back());
					if (root->right->bound->IsOverlap(root->GameObjects.back()->GetBound()))
						Insert(root->right, root->GameObjects.back());

					root->GameObjects.pop_back();
				}
			}
			return;
		}
		if (root->left != NULL && root->right != NULL) {
			while (!root->GameObjects.empty()) {
				if (root->left->bound->IsOverlap(root->GameObjects.back()->GetBound()))
					Insert(root->left, root->GameObjects.back());
				if (root->right->bound->IsOverlap(root->GameObjects.back()->GetBound()))
					Insert(root->right, root->GameObjects.back());

				root->GameObjects.pop_back();
			}
		}
	}
}
bool BTree::Split(Nodeptr root) {
	float cameraWidth = Camera::GetInstance()->GetCameraBound()->w;
	float cameraHeight = Camera::GetInstance()->GetCameraBound()->h;
	if (isVerticalSplit) {
		//just the camera is so small so i change the limit is camera w not cam w /2
		if (root->bound->w >= cameraWidth/2) {
			root->left = MakeNode(root->level + 1, root->bound->x, root->bound->y, root->bound->w / 2, root->bound->h);
			root->right = MakeNode(root->level + 1, root->bound->x + root->bound->w / 2, root->bound->y, root->bound->w / 2, root->bound->h);
			return true;
		}
	}
	else {
		if (root->bound->h >= cameraHeight/2) {
			root->left = MakeNode(root->level + 1, root->bound->x, root->bound->y, root->bound->w, root->bound->h/2);
			root->right = MakeNode(root->level + 1, root->bound->x , root->bound->y+ root->bound->h/2, root->bound->w, root->bound->h/2);
			return true;
		}
	}
	return false;
}


void BTree::Retrieve(Nodeptr root, std::vector<GameObject*>& returnObjects,Bound source) {
	if (root != NULL) {
		for (std::vector<GameObject*>::iterator i = root->GameObjects.begin(); i != root->GameObjects.end(); i++)
		{
			if ((*i) != NULL && (*i)->isDeleted == false) {
				bool isExist = false;
				for (GameObject* ptr : returnObjects) {
					if (ptr == (*i)) {
						isExist = true;
					}
				}
				if (!isExist)
				{
					if (!(*i)->isDeleted) {
						returnObjects.push_back(*i);//all objects are stored in leaf node so don't need to check if parent node has any object
					}
				}
			}
		}
		if (root->left != NULL && source->IsOverlap(root->left->bound)) {
			Retrieve(root->left, returnObjects,source);
		}
		if (root->right != NULL && source->IsOverlap(root->right->bound)) {
			Retrieve(root->right, returnObjects,source);
		}
	}
}
void BTree::Traversal(Nodeptr root) {

}
void BTree::RemoveGameObjectForUpdate(Nodeptr root, GameObject* e) {
	if (root != NULL) {
		if (root->bound->IsOverlap(e->GetBound()) && root->left == NULL && root->right == NULL) {
			if (!root->GameObjects.empty()) {

				for (auto i = root->GameObjects.begin(); i != root->GameObjects.end(); ++i) {
					if ((*i) == e && (*i)->isDeleted == false && (*i) != NULL && e!=NULL) {
						root->GameObjects.erase(i);
						return;
					}
				}

			}
		}
		if (root->left != NULL) {
			if (root->left->bound->IsOverlap(e->GetBound())) {
				RemoveGameObjectForUpdate(root->left, e);
			}
		}
		if (root->right != NULL) {
			if (root->right->bound->IsOverlap(e->GetBound())) {
				RemoveGameObjectForUpdate(root->right, e);
			}
		}
	}
}
void BTree::Clear(Nodeptr root) {
	if (root != NULL) {
		Clear(root->left);
		Clear(root->right);

		// Clear entities and then delete the node and its bound
		root->GameObjects.clear();
		delete root->bound;
		delete root;
	}
}