#include "BinTree.h"
template <typename T> class BST : public BinTree<T>{
	protected:
		BinNodePosi(T) _hot;
		BinNodePosi(T) connect34(
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T),
		BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));
	BinNodePosi(T) rotateAt(BinNodePosi(T) x);
	public:
		virtual BinNodePosi(T) & search(const T& e);
		virtual BinNodePosi(T) insert(const T& e);
		virtual bool remove(const T& e);
};

//查找操作
template <typename T>
static BinNodePosi(T) & searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot){
	if(!v || (e == v->data)) return v;
	hot = v;
	return searchIn(((e < v->data) ? v->lchild : v->rchild), e, hot);
}
template <typename T> BinNodePosi(T) & BST<T>::search(const T& e)
{
	return searchIn(_root, e, _root = NULL);
}
//插入操作
template <typename T> BinNodePosi(T) BST<T>::insert(const T& e)
{
	BinNodePosi(T) & x = search(e); if (x) return x;
	x = new BinNode<T>(e, _hot);
	_size++;
	updateHeightAbove(x);
	return x;
}
//删除操作 
template <typename T> bool BST<T>::remove(const T& e){
	BinNodePosi(T) & x = search(e); if(!x) return false;
	removeAt(x, _hot);
	_size--;
	updateHeightAbove(_hot);
	return true;
}
//重点 
template <typename T>
static BinNodePosi(T) removeAt(BinNodePosi(T)& x, BinNodePosi(T)& hot){
	BinNodePosi(T) w = x;
	BinNodePosi(T) succ = NULL;
	if(!HasLchild(*x))//左子树为空
		succ = x = x->rchild;
	else if(!HasRchild(*x))
		succ = x = x->lchild;
	else{
		w = w->succ();
		swap(x->data, w->data);
		BinNodePosi(T) u = w->parent;
		((u == x) ? u->rchild : r->lchild) = succ = w->rchild;
	}
	hot = w->parent;
	if(succ) succ->parent = hot;
	release(w->data);
	release(w);
	return succ;
}
