#include "BinNode.h"
template <typename T> class BinTree{
	protected:
		int _size;
		BinNodePosi(T) _root;
		virtual int updateHeight(BinNodePosi(T) x);
		void updateHeightAbove(BinNodePosi(T) x);
	public:
		BinTree() : _size(0), _root(NULL){}
		~BinTree(){
			if(0 < _size) remove(_root);
		}
		int size() const{ return _size;}
		bool empty() const{ return !_root;}
		BinNodePosi(T) root() const {return _root;}
		BinNodePosi(T) insertAsRoot(T const& e);
		BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);
		BinNodePosi(T) insertRsLC(BinNodePosi(T) x, T const& e);
		BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T);//子树接入 
		BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T);
		int remove(BinNodePosi(T) x);
		BinTree<T>* secede(BinNodePosi(T) x);//子树分离 
		template <typename VST>
		void travLevel(VST& visit){ if (_root) _root->travLevel(visit);}
		template <typename VST>
		void travPre(VST& visit) { if (_root) _root->travPre(visit);}
		template <typename VST>
		void travIn(VST& visit) { if (_root) _root->travIn(visit);}
		template <typename VST>
		void travPost(VST& visit) { if (_root) _root->travPost(visit);}
		bool operator<(BinTree<T> const& t) { return _root && t._root && lt(_root, t._root);} //
		bool operator==(BinTree<T> const& t) { return _root && t._root && (_root == t._root);}
};

template <typename T> int BinTree<T>::updateHeight(BinNodePosi(T) x)//更新结点高度 
{
	return x->height = 1 + max(stature(x->lchild), stature(x->rchild));
}
template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)//更新x及其祖先高度 
{
	while(x) {
		updateHeight(x);
		x = x->parent;
	}
}
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
	_size = 1; return _root = new BinNode<T>(e);
}
template <typename T> BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lchild;
}
template <typename T> BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
	_size++; x->insertAsRC(e); updateHeightAbove(x); return x->rchild;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S)
{
	if (x->lchild = S->_root) x->lchild->parent = x;//接入，注意判断函数内为赋值 
	_size += S->_size;
	updateHeightAbove(x);
	S->_root = NULL; S->_size = 0; release(S);
	S = NULL; 
	return x;
}
template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S)
{
	if (x->rchild = S->_root) x->rchild->parent = x;//接入，注意判断函数内为赋值 
	_size += S->_size;
	updateHeightAbove(x);
	S->_root = NULL; S->_size = 0; release(S);
	S = NULL;
	return x;
}
template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x){ 
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x);
	_size -= n;
	return n;
}
template <typename T>
static int removeAt(BinNodePosi(T) x){//删除二叉树中位置x处的节点及其后代，返回被删除节点的数值 
	if(!x) return 0;
	int n = 1 + removeAt(x->lchild) + removeAt(x->rchild);
	release(x->data);
	release(x);
	return n;
}

//子树分离
template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x){
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	BinTree<T>* S = new BinTree<T>;
	S->_root = x;
	x->parent = NULL;
	S->_size = x->size();
	_size -= S->_size;
	return S;
}

//遍历
template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit){//递归版先序遍历 
	if(!x) return;
	visit(x->data);
	travPre_R(x->lchild, visit);
	travPre_R(x->rchild, visit);
}
template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit){//递归版中序遍历 
	if(!x) return;
	travIn_R(x->lchild, visit);
	visit(x->data);
	travIn_R(x->rchild, visit);
}
template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit){//递归版后序遍历 
	if(!x) return;
	travPost_R(x->lchild, visit);
	travPost_R(x->rchild, visit);
	visit(x->data);
}
template <typename T, typename VST>
void travLevel(BinNodePosi(T) x, VST& visit){
	queue<BinNodePosi(T)> q;
	q.push(this);
	while(!q.empty()){
		BinNodePosi(T) x = q.pop();
		visit(x->data);
		if(HasLchild(*x)) q.push(x->lchild);
		if(HasRchild(*x)) q.push(x->rchild);
	}
}
