#include "BST.h"
#define Balanced(x) (stature((x).lchild) == stature((x).rchild))
#define BalFac(x) (stature((x).lchild) - stature((x).rchild))
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))//����ƽ������ 
#define tallerChild(x) ( \
	stature((x)->lchild) > stature((x)->rchild) ? (x)->lchild : ( \
	stature((x)->rchild) > stature((x)->lchild) ? (x)->rchild : ( \
	IsLchild(*(x)) ? (x)->lchild : (x)->rchild \
	) \
	) \
) 
template <typename T> class AVL : public BST<T>{
	public:
		BinNodePosi(T) insert(const T& e);
		bool remove(const T& e);
}
//������� 
template <typename T> BinNodePosi(T) AVL<T>::insert(const T& e){
	BinNodePosi(T) & x = search(e); if(x) return x;
	x = new BinNodePosi(T)(e, _hot); _size++;
	for(BinNodePosi(T) g = _hot; g; g = g->parent){
		if(!AvlBalanced(*g)){
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
			break;
		}else{
			updateHeight(g);
		}
	}
	return x;
}
//ɾ������
template <typename T> bool AVL<T>::remove(const T& e){
	BinNodePosi(T) & x = search(e); if(!x) return false;
	removeAt(x, _hot);_size--;
	for(BinNodePosi(T) g = _hot; g; g = g->parent){
		if(!AvlBalanced(*g))
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
		updateHeight(g);
	}
	return true;
}
template <typename T>BinNodePosi(T) BST<T>::connect34(
	BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
	BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
{
	a->lchild = T0; if(T0) T0->parent = a;
	a->rchild = T1; if(T1) T1->parent = a; updateHeight(a);
	c->lchild = T2; if(T2) T2->parent = c;
	c->rchild = T3; if(T3) T3->parent = c; updateHeight(c);
	b->lchild = a; a->parent = b;
	b->rchild = c; c->parent = b; updateHeight(b);
}
template <typename T>BinNodePosi BST<T>::rotateAt(BinNodePosi(T) v){
	BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent;
	if (IsLchild(*p))
		if(IsLchild(*v)){
			p->parent = g->parent;
			return connect34(v, p, g, v->lchild, v->rchild, p->rchild, g->rchild);
		}else{
			v->parent = g->parent;
			return connect34(p, v, g, p->lchild, v->lchild, v->rchild, g->rchild);
		}
	else
		if(IsRchild(*v)){
			p->parent = g->parent;
			return connect34(g, p, v, g->lchild, p->lchild, v->lchild, v->rchild);
		}else{
			v->parent = g->parent;
			return connect34(g, v, p, g->lchild, v->lchild, v->rchild, p->rchild);
		}
}
/*AVL�������ԣ� 
	ƽ���ԣ�AVL����ÿ���ڵ��ƽ��������[-1��1]֮�� 
	�߶�Ϊ h ��AVL�����ٰ��� Fib(h+3) - 1���ڵ㡣
	���� n ���ڵ��AVL���ĸ߶�ӦΪO(log n) 
