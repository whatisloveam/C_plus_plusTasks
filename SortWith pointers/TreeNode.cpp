#include "TreeNode.h"

TreeNode::TreeNode(TreeNode* parent, PlayField newField)
{
	this->parent = parent;
	this->field = newField;
}

bool TreeNode::isTerminal()
{
	return field.checkFieldStatus() != PlayField::fsNormal;
}

PlayField::FieldStatus TreeNode::fieldStatus()
{
	return field.checkFieldStatus();
}

void TreeNode::addChild(TreeNode* child)
{
	child->parent = this;
	childs.push_back(child);
}

TreeNode& TreeNode::operator[](int idx)
{
	return *childs[idx];
}

int TreeNode::childCount()
{
	return childs.size();
}

const PlayField& TreeNode::value()
{
	return field;
}

int TreeNode::childQty()
{
	return field.GetEmptyCells().size();
}
