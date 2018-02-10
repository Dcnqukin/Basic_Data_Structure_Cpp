//Binary Tree
#define BinNodePosi(T) BinNode<T>* //重要
#define stature(p) ((p) ? (p)->height : -1)
#define IsRoot(x) (!(x).parent)
#define IsLchild(x) (!IsRoot(x) && (&(x) == (x).parent->lchild))
#define IsRchild(x) (!IsRoot(x) && (&(x) == (x).parent->rchild))
#define HasParent(x) ((x).parent)
#define HasLchild(x) ((x).lchild)
#define HasRchild(x) ((x).rchild)
#define HasChild(x) ((x).lchild || (x).rchild)
#define HasBothChild(x) ((x).lchild && (x).rchild)
#define IsLeaf(x) (!HasChild(x))
#define sibling(p) (\
	IsChild(*(p)) ?\
		(p)->parent->lchild : \
		(p)->parent->rchild \
)
#define uncle(x) (\
	IsLchild(*((x)->parent)) ?\
		(x)->parent->parent->rchild : \
		(x)->parent->parent->lchild \
)
#define FromParentTo(x) ( \
	IsRoot(x) ? _root : ( \
	IsLchild(x) ? (x).parent->lchild : (x).parent->rchild \
	) \
)
typedef enum{
	RB_RED, RB_BLACK
}RBColor; 
template <typename T> struct BinNode{
	T data;
	BinNodePosi(T) parent;
	BinNodePosi(T) lchild;
	BinNodePosi(T) rchild;
	int height;
	int npl;
	RBColor color;
	BinNode() : parent(NULL), lchild(NULL), rchild(NULL), height(0), 
				npl(1), color(RB_RED){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, 
			BinNodePosi(T) rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED): 
			data(e), parent(p), lchild(lc), rchild(rc), height(h), npl(l), color(c){} 
	int size();
	BinNodePosi(T) insertAsLC(T const&);
	BinNodePosi(T) insertRslC(T const&);
	BinNodePosi(T) succ();
	template <typename VST> void travLevel(VST&);
	template <typename VST> void travPre_R(VST&);
	template <typename VST> void travIn_R(VST&);
	template <typename VST> void travPost_R(VST&);
	bool operator<(BinNode const& bn) {
		return data < bn.data;
	}//加上const，则可以接受const和非const的实参。 
	bool operator==(BinNode const& bn){
		return data == bn.data;
	}
	bool operator>(BinNode const& bn){
		return data > bn.data;
	}
}
template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const& e){
	return lchild = new BinNode(e, this);
}
template <typename T>
BinNodePosi(T) BinNode<T>::insertRsLC(T const& e){
	return rchild = new BinNode(e, this);
}
template <typename T, typename VST>
void BinNode<T>::travPre(VST& visit){
	switch(rand() % 2){
		case 1: travPre_I(this, visit);
		default: travPre_R(this, visit);
	}
}
template <typename T, typename VST>
void BinNode<T>::travIn(VST& visit){
	switch(rand() % 2){
		case 1: travIn_I(this, visit);
		default: travIn_R(this, visit);
	}
}
template <typename T, typename VST>
void BinNode<T>::travPost(VST& visit){
	switch(rand() % 2){
		case 1: travPost_I(this, visit);
		default: travPost_R(this, visit);
	}
}
<<<<<<< HEAD
//定位节点v的直接后继 
template <typename T> BinNodePosi(T) BinNode<T>::succ(){
	BinNodePosi(T) s = this;
	if(rchild){
		s = rchild;
		while(HasLchild(*s)) s = s->lchild;
	}else{
		while(IsRChild(*s)) s = s->parent;
		s = s->parent;
	}
	return s;
}
=======
>>>>>>> 05694cf2cda5b4104ebcbfaa1a7ee0ae26d606db

