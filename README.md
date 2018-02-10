# Basic_Data_Structure_Cpp

BinNode.h和 BinTree.h这两个header存放的是基本数据结构中二叉树的链式存储结构，同时也包含了基本的遍历算法(Pre, In, Post)
BinNode.h提供了二叉树的节点的模板类，实现简单的插入删除功能，并且宏定义了一些判断函数
BinTree.h提供了二叉树的模板类，分别实现了递归版和迭代版的三大遍历以及层次遍历
BST.h中的BST模板类继承了BinTree，并在原有功能上添加了BST的查找、插入、删除操作。
AVL.h中的AVL模板类继承了BST，并在原有功能上实现了插入删除操作（左旋右旋什么的）