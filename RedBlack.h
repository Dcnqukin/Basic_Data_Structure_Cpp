#include "BST.h"
#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color))
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) (\
	(stature((x).lchild) == stature((x).rchild)) && \
	((x).height == (IsRed(&x) ? stature((x).lchild) : stature((x).lchild) + 1)) \
)
template <typename T> class RedBlack : public BST<T>{
	protected:
		void solveDoubleRed(BinNodePosi(T) x);
		void solveDoubleBlack(BinNodePosi(T) x);
		int updateHeight(BinNodePosi(T) x);
	public:
		BinNodePosi(T) insert(const T& e);
		bool remove(const T& e);
}

template <typename T> int RedBlack<T>::updateHeight(BinNodePosi(T) x){
	x->height = max(stature(x->lchild), stature(x->rchild));
	return IsBlack(x) ? x->height++ : x->height;
}
template <typename T> BinNodePosi(T) RedBlack<T>::insert(const T& e){
	BinNodePosi(T) & x = search(e); if(x) return x;
	x = new BinNodePosi(T)(e, _hot, NULL, NULL, -1);
	_size++;
	solveDoubleRed(x);
	return x;
}
template <typename T> void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x){
	if(IsRoot(*x)){
		_root->color = RB_BLACK; _root->height++; return;
	}
	BinNodePosi(T) p = x->parent; if(IsBlack(p)) return;
	BinNodePosi(T) g = p->parent;
	BinNodePosi(T) u = uncle(x);
	if(IsBlack(u)){
		if(IsLchild(*x) == IsLchild(*p))
			p->color = RB_BLACK;
		else
			x->color = RB_BLACK;
		g->color = RB_RED;
		
		BinNodePosi(T) gg = g->parent;
		BinNodePosi(T) r = FromParentTo(*g) = rotateAt(x);
		r->parent = gg;
	}else{
		p->color = RB_BLACK; p->height++;
		u->color = RB_BLACK; u->height++;
		if(!IsRoot(*g)) g->color = RB_RED;
		solveDoubleRed(g);
	}
}
template <typename T> bool RedBlack<T>::remove(const T& e){
	BinNodePosi(T) & x = search(e); if(!x) return false;
	BinNodePosi(T) r = removeAt(x, _hot);
	if( 0 >= --_size) return true;
	if(!_hot)
	{
		_root->color = RB_BLACK; updateHeight(_root); return true;
	}
	if(BlackHeightUpdated(*(_hot)))
		return true;
	if(IsRed(r))
	{
		r->color = RB_BLACK; r->height++; return true;
	}
	solveDoubleBlack(r); return true;
}
template <typename T> void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) x){
	BinNodePosi(T) p = x ? x->parent : _hot; if(!p) return;
	BinNodePosi(T) s = (x == p->lchild) ? p->rchild : p->lchild;
	if(IsBlack(s)){
		BinNodePosi(T) t = NULL;
		if(HasLchild(*s) && IsRed(s->lchild)) t = s->lchild;
		else if(HasRchild(*s) && IsRed(s->rchild)) t = s->rchild;
		if(t){
			RBColor oldColor = p->color;
			BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t);
			if(HasLchild(*b)) b->lchild->color = RB_BLACK;
			updateHeight(b->lchild);
			if(HasRchild(*b)) b->rchild->color = RB_BLACK;
			updateHeight(b->rchild);
			b->color = oldColor;
			updateHeight(b);
		}else{
			s->color = RB_RED;
			s->height--;
			if(IsRed(p)){
				p->color = RB_BLACK;
			}else{
				p->height--;
				solveDoubleBlack(p);
			}
		}
	}else{
		s->color = RB_BLACK;
		p->color = RB_RED;
		BinNodePosi(T) t = IsLchild(*s) ? s->lchild : s->rchild;
		_hot = p; FromParentTo(*p) = rotateAt(t);
		solveDoubleBlack(x);
	}
}
