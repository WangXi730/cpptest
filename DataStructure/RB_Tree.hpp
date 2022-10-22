#pragma once
#include<stack>
#include<vector>
namespace wx {
	using namespace std;
	enum color {
		red,
		black
	};

	template<class Type>
	class RB_Tree;

	template<class Type>
	class RB_Node {
	public:
		friend class RB_Tree<Type>;
		//构造方法
		RB_Node(Type val = Type()) :data(val)
		{}
		//析构方法
		~RB_Node() {}
		//清理方法
		void clean() {
			if (left != nullptr)
				left->clean();
			if (right != nullptr)
				right->clean();
			delete this;
		}
	private:
		Type data;
		color node_color = red;
		RB_Node<Type>* left = nullptr;
		RB_Node<Type>* right = nullptr;
		RB_Node<Type>* pr = nullptr;	//红黑树用三岔链实现更好一些
	};

	template<class Type>
	class RB_Tree {
	public:
		typedef void (RB_Tree::* func)(RB_Node<Type>*&);
		//构造空树方法
		RB_Tree() {}
		//析构方法
		virtual~RB_Tree() {
			root->clean();
		}
		//判断空树
		bool empty() {
			if (root == nullptr)
				return true;
			return false;
		}
		//插入方法
		void insert(Type val) {
			//先按照BST树的方式插入
			if (empty()) {
				//空树则直接插入
				root = new RB_Node<Type>(val);
				root->node_color = black;
				root->pr = nullptr;
				return;
			}
			//如果不是空树，先构造结点
			RB_Node<Type>* x = root;
			RB_Node<Type>* p = nullptr;
			stack<RB_Node<Type>*> st;
			while (x != nullptr) {
				st.push(x);
				p = x;
				if (x->data > val)
					x = x->left;
				else
					x = x->right;
			}
			//插入
			if (p->data > val) {
				p->left = new RB_Node<Type>(val);
				x = p->left;
				x->pr = p;
			}
			else {
				p->right = new RB_Node<Type>(val);
				x = p->right;
				x->pr = p;
			}
			if (p->node_color == black) {
				root->pr = nullptr;
				return;
			}
			//如果父结点是红色，就代表有爷爷结点
			st.pop();
			RB_Node<Type>* g = st.top();
			st.pop();
			//创建叔父结点
			RB_Node<Type>* u = p == g->left ? g->right : g->left;
			while (1) {
				//定义曾祖结点
				RB_Node<Type>* gg = st.empty() ? nullptr : st.top();
				if (!st.empty())
					st.pop();
				//判断叔父结点的颜色，空结点视为黑色
				if (u == nullptr || u->node_color == black) {
					//黑色旋转
					//判断插入位置
					if (p == g->left && x == p->left) {//	/
						//右旋
						p->node_color = black;
						g->node_color = red;
						if (gg == nullptr) {
							RotateR(root);
							break;
						}
						else
							RotateR(gg->left == g ? gg->left : gg->right);
						p->pr = gg;
						g->pr = p;
					}
					else if (p == g->right && x == p->right) {//	\
						//左旋
						p->node_color = black;
						g->node_color = red;
						if (gg == nullptr) {
							RotateL(root);
							break;
						}
						else
							RotateL(gg->left == g ? gg->left : gg->right);
						g->pr = p;
						p->pr = gg;
					}
					else if (p == g->left && x == p->right) {//	<
						//先左后右
						x->node_color = black;
						g->node_color = red;
						if (gg == nullptr) {
							RotateLR(root);
							break;
						}
						else
							RotateLR(gg->left == g ? gg->left : gg->right);
						x->pr = gg;
						g->pr = x;
						p->pr = x;
					}
					else if (p == g->right && x == p->left) {//	>
						//先右后左
						x->node_color = black;
						g->node_color = red;
						if (gg == nullptr) {
							RotateRL(root);
							break;
						}
						else
							RotateRL(gg->left == g ? gg->left : gg->right);
						x->pr = gg;
						g->pr = x;
						p->pr = x;
					}
				}
				else {
					//剩下的uncle是红色的
					//红色可以直接修改颜色
					p->node_color = black;
					u->node_color = black;
					g->node_color = red;
				}
				//接下来进行判断
				if (g == root) {
					g->node_color = black;
					break;
				}
				//更新结点
				x = g;
				p = gg;
				if (p->node_color == black)
					break;
				g = st.top();
				st.pop();
			}
			root->pr = nullptr;
		}
		//删除方法
		void remove(Type val) {
			//按照BST的规则删除
			RB_Node<Type>* x = root;
			while (x != nullptr) {
				if (x->data > val)
					x = x->left;
				else if (x->data < val)
					x = x->right;
				else
					break;
			}
			if (x == nullptr)
				return;
			if (x->left != nullptr && x->right != nullptr) {
				RB_Node<Type>* x2 = x;
				x = x->left;
				while (x->right != nullptr)
					x = x->right;
				x2->data = x->data;
			}
			//用d标记要删除的结点，用x指向需要调整平衡的结点
			RB_Node<Type>* d = x;
			//调整平衡
			//如果删除了红色结点，那么相安无事
			if (x->node_color == red) {
				if (x->left != nullptr && x->right == nullptr) {
					if (x->pr->left == x) {
						x->pr->left = x->left;
						x->left->pr = x->pr;
					}
					else if (x->pr->right == x) {
						x->pr->right = x->left;
						x->left->pr = x->pr;
					}
					x = x->left;
				}
				else if (x->left == nullptr && x->right != nullptr) {
					if (x->pr->left == x) {
						x->pr->left = x->right;
						x->right->pr = x->pr;
					}
					else if (x->pr->right == x) {
						x->pr->right = x->right;
						x->right->pr = x->pr;
					}
					x = x->right;
				}
				else if (x->left == nullptr && x->right == nullptr) {
					if (x->pr->left == x) {
						x->pr->left = nullptr;
					}
					else if (x->pr->right == x) {
						x->pr->right = nullptr;
					}
					x = nullptr;
				}
				delete d;
				return;
			}
			//否则需要进行调整
			while (1) {
				if (x->left != nullptr || x->right != nullptr) {
					if (x->left != nullptr) {
						//子树只能是红色，否则不平衡，把子树变成黑色，用来代替x
						x->left->node_color = black;
						//用子结点代替X
						if (x->pr->left == x) {
							x->pr->left = x->left;
						}
						else {
							x->pr->right = x->left;
						}
						x->left->pr = x->pr;
					}
					else {
						x->right->node_color = black;
						if (x->pr->left == x) {
							x->pr->left = x->right;
						}
						else {
							x->pr->right = x->right;
						}
						x->right->pr = x->pr;
					}
					break;
				}
				//剩下的最复杂的情况
				else {
					//x为一颗裸黑结点
					//这个时候应该去考虑它的兄弟结点
					RB_Node<Type>* p = x->pr;
					RB_Node<Type>* b = p->left == x ? p->right : p->left;
					RB_Node<Type>* g = p->pr;
					if (b->node_color == red) {
						//兄弟是红色的，那么兄弟的子女一定都是黑色的，父亲一定是黑色的
						//这个时候根据情况进行旋转
						if (p->left = x) {
							//父结点的左树是删除结点
							//这个时候应该是左旋转
							if (g == nullptr) {
								//说明 p 是根
								RotateL(root);
								root->pr = nullptr;
								p->pr = root;
								p->right->pr = p;
							}
							else {
								if (g->left == p) {
									RotateL(g->left);
								}
								else {
									RotateL(g->right);
								}
								b->pr = g;
								p->pr = b;
								p->right->pr = p;
							}
							//旋转完成之后，应该对颜色进行调整
							p->node_color = red;
							b->node_color = black;
							//然后进行结点名称的更新
							b = p->right;
						}
						else {
							//父结点的右树是删除结点
							//右旋转
							if (g == nullptr) {
								//说明 p 是根
								RotateR(root);
								root->pr = nullptr;
								p->pr = root;
								p->left->pr = p;
							}
							else {
								if (g->left == p) {
									RotateR(g->left);
								}
								else {
									RotateR(g->right);
								}
								b->pr = g;
								p->pr = b;
								p->left->pr = p;
							}
							//旋转完成之后，应该对颜色进行调整
							p->node_color = red;
							b->node_color = black;
							//然后进行结点名称的更新
							b = p->left;
						}

					}
					//走下来的兄弟就是黑色的了
					RB_Node<Type>* bl = b->left;
					RB_Node<Type>* br = b->right;
					if (bl != nullptr) {
						if (p->left == b) {
							//右旋
							if (p == root) {
								RotateR(root);
							}
							else if (g->left == p) {
								RotateR(g->left);
							}
							else if (g->right == p) {
								RotateR(g->right);
							}
							//调整颜色
							b->node_color = p->node_color;
							p->node_color = black;
							bl->node_color = black;
							//调整父亲
							b->pr = g;
							p->pr = b;
							if (br != nullptr)
								br->pr = p;
						}
						else {
							//	>
							//先右后左
							if (p == root) {
								RotateRL(root);
							}
							else if (g->left == p) {
								RotateRL(g->left);
							}
							else if (g->right == p) {
								RotateRL(g->right);
							}
							//调整颜色
							bl->node_color = p->node_color;
							p->node_color = black;
							//调整父亲
							bl->pr = g;
							p->pr = bl;
							b->pr = bl;
						}
						break;
					}
					else if (br != nullptr) {
						if (p->left == b) {
							//	<
							//先左后右
							if (p == root) {
								RotateLR(root);
							}
							else if (g->left == p) {
								RotateLR(g->left);
							}
							else if (g->right == p) {
								RotateLR(g->right);
							}
							//调整颜色
							br->node_color = p->node_color;
							p->node_color = black;
							//调整父亲
							br->pr = g;
							p->pr = br;
							b->pr = br;
						}
						else {
							//	\
							//左旋
							if (p == root) {
								RotateL(root);
							}
							else if (g->left == p) {
								RotateL(g->left);
							}
							else if (g->right == p) {
								RotateL(g->right);
							}
							//调整颜色
							b->node_color = p->node_color;
							p->node_color = black;
							br->node_color = black;
							//调整父亲
							b->pr = g;
							p->pr = b;
							if (bl != nullptr)
								bl->pr = p;
						}
						break;
					}
					else if (p->node_color == red) {
						p->node_color = black;
						b->node_color = red;
						break;
					}
					else if (p->node_color == black) {
						b->node_color = red;
						if (p == root)
							break;
						x = p;
					}
				}
			}
			//删除结点，首先把d孤立起来
			if (d->left != nullptr && d->right == nullptr) {
				if (d->pr->left == d) {
					d->pr->left = d->left;
					d->left->pr = d->pr;
				}
				else if (d->pr->right == d) {
					d->pr->right = d->left;
					d->left->pr = d->pr;
				}
			}
			else if (d->left == nullptr && d->right != nullptr) {
				if (d->pr->left == d) {
					d->pr->left = d->right;
					d->right->pr = d->pr;
				}
				else if (d->pr->right == d) {
					d->pr->right = d->right;
					d->right->pr = d->pr;
				}
			}
			else if (d->left == nullptr && d->right == nullptr) {
				if (d->pr->left == d) {
					d->pr->left = nullptr;
				}
				else if (d->pr->right == d) {
					d->pr->right = nullptr;
				}
			}
			delete d;
		}
	protected:
		//叔父结点是黑色的情况
		//右旋
		void RotateR(RB_Node<Type>*& ptr) {
			RB_Node<Type>* r = ptr;
			ptr = r->left;
			r->left = ptr->right;
			ptr->right = r;
		}
		//左旋
		void RotateL(RB_Node<Type>*& ptr) {
			RB_Node<Type>* l = ptr;
			ptr = l->right;
			l->right = ptr->left;
			ptr->left = l;
		}
		//先左后右
		void RotateLR(RB_Node<Type>*& ptr) {
			//	<
			RB_Node<Type>* r = ptr;
			RB_Node<Type>* l = r->left;
			ptr = l->right;
			l->right = ptr->left;
			ptr->left = l;
			r->left = ptr->right;
			ptr->right = r;
		}
		//先右后左
		void RotateRL(RB_Node<Type>*& ptr) {
			//	>
			RB_Node<Type>* l = ptr;
			RB_Node<Type>* r = l->right;
			ptr = r->left;
			r->left = ptr->right;
			ptr->right = r;
			l->right = ptr->left;
			ptr->left = l;
		}
	private:
		RB_Node<Type>* root = nullptr;
	};

}