#pragma once
#include "PlayField.h"

class TreeNode
{
public:
	explicit TreeNode(TreeNode* parent, PlayField newField);
	bool isTerminal();
	PlayField::FieldStatus fieldStatus();
	void addChild(TreeNode* child);
	TreeNode& operator[](int idx);
	int childCount();
	const PlayField& value();
private:
	int childQty();
	PlayField field;
	std::vector<TreeNode*> childs;
	TreeNode* parent = nullptr;
};

