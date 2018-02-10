# Basic_Data_Structure_Cpp
---
* BinNode.h提供了二叉树的节点的模板类，实现简单的插入删除功能，并且宏定义了一些判断函数
+ BinTree.h提供了二叉树的模板类，分别实现了递归版和迭代版的三大遍历以及层次遍历
	- BST.h中的BST模板类继承了BinTree，并在原有功能上添加了BST的查找、插入、删除操作。
		- AVL.h中的AVL模板类继承了BST，并在原有功能上实现了插入删除操作（左旋右旋什么的）
	- RedBlack.h中定义了RedBlack模板类，该类继承BST，并自定义了三个功能，分别是RedBlack双红调整算法、RedBlack双黑调整算法、节点高度动态变换算法。
---
三种高级搜索树
*Splay.h
*BTree.h