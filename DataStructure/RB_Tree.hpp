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
		//���췽��
		RB_Node(Type val = Type()) :data(val)
		{}
		//��������
		~RB_Node() {}
		//������
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
		RB_Node<Type>* pr = nullptr;	//�������������ʵ�ָ���һЩ
	};

	template<class Type>
	class RB_Tree {
	public:
		typedef void (RB_Tree::* func)(RB_Node<Type>*&);
		//�����������
		RB_Tree() {}
		//��������
		virtual~RB_Tree() {
			root->clean();
		}
		//�жϿ���
		bool empty() {
			if (root == nullptr)
				return true;
			return false;
		}
		//���뷽��
		void insert(Type val) {
			//�Ȱ���BST���ķ�ʽ����
			if (empty()) {
				//������ֱ�Ӳ���
				root = new RB_Node<Type>(val);
				root->node_color = black;
				root->pr = nullptr;
				return;
			}
			//������ǿ������ȹ�����
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
			//����
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
			//���������Ǻ�ɫ���ʹ�����үү���
			st.pop();
			RB_Node<Type>* g = st.top();
			st.pop();
			//�����常���
			RB_Node<Type>* u = p == g->left ? g->right : g->left;
			while (1) {
				//����������
				RB_Node<Type>* gg = st.empty() ? nullptr : st.top();
				if (!st.empty())
					st.pop();
				//�ж��常������ɫ���ս����Ϊ��ɫ
				if (u == nullptr || u->node_color == black) {
					//��ɫ��ת
					//�жϲ���λ��
					if (p == g->left && x == p->left) {//	/
						//����
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
						//����
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
						//�������
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
						//���Һ���
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
					//ʣ�µ�uncle�Ǻ�ɫ��
					//��ɫ����ֱ���޸���ɫ
					p->node_color = black;
					u->node_color = black;
					g->node_color = red;
				}
				//�����������ж�
				if (g == root) {
					g->node_color = black;
					break;
				}
				//���½��
				x = g;
				p = gg;
				if (p->node_color == black)
					break;
				g = st.top();
				st.pop();
			}
			root->pr = nullptr;
		}
		//ɾ������
		void remove(Type val) {
			//����BST�Ĺ���ɾ��
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
			//��d���Ҫɾ���Ľ�㣬��xָ����Ҫ����ƽ��Ľ��
			RB_Node<Type>* d = x;
			//����ƽ��
			//���ɾ���˺�ɫ��㣬��ô�ల����
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
			//������Ҫ���е���
			while (1) {
				if (x->left != nullptr || x->right != nullptr) {
					if (x->left != nullptr) {
						//����ֻ���Ǻ�ɫ������ƽ�⣬��������ɺ�ɫ����������x
						x->left->node_color = black;
						//���ӽ�����X
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
				//ʣ�µ���ӵ����
				else {
					//xΪһ����ڽ��
					//���ʱ��Ӧ��ȥ���������ֵܽ��
					RB_Node<Type>* p = x->pr;
					RB_Node<Type>* b = p->left == x ? p->right : p->left;
					RB_Node<Type>* g = p->pr;
					if (b->node_color == red) {
						//�ֵ��Ǻ�ɫ�ģ���ô�ֵܵ���Ůһ�����Ǻ�ɫ�ģ�����һ���Ǻ�ɫ��
						//���ʱ��������������ת
						if (p->left = x) {
							//������������ɾ�����
							//���ʱ��Ӧ��������ת
							if (g == nullptr) {
								//˵�� p �Ǹ�
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
							//��ת���֮��Ӧ�ö���ɫ���е���
							p->node_color = red;
							b->node_color = black;
							//Ȼ����н�����Ƶĸ���
							b = p->right;
						}
						else {
							//������������ɾ�����
							//����ת
							if (g == nullptr) {
								//˵�� p �Ǹ�
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
							//��ת���֮��Ӧ�ö���ɫ���е���
							p->node_color = red;
							b->node_color = black;
							//Ȼ����н�����Ƶĸ���
							b = p->left;
						}

					}
					//���������ֵܾ��Ǻ�ɫ����
					RB_Node<Type>* bl = b->left;
					RB_Node<Type>* br = b->right;
					if (bl != nullptr) {
						if (p->left == b) {
							//����
							if (p == root) {
								RotateR(root);
							}
							else if (g->left == p) {
								RotateR(g->left);
							}
							else if (g->right == p) {
								RotateR(g->right);
							}
							//������ɫ
							b->node_color = p->node_color;
							p->node_color = black;
							bl->node_color = black;
							//��������
							b->pr = g;
							p->pr = b;
							if (br != nullptr)
								br->pr = p;
						}
						else {
							//	>
							//���Һ���
							if (p == root) {
								RotateRL(root);
							}
							else if (g->left == p) {
								RotateRL(g->left);
							}
							else if (g->right == p) {
								RotateRL(g->right);
							}
							//������ɫ
							bl->node_color = p->node_color;
							p->node_color = black;
							//��������
							bl->pr = g;
							p->pr = bl;
							b->pr = bl;
						}
						break;
					}
					else if (br != nullptr) {
						if (p->left == b) {
							//	<
							//�������
							if (p == root) {
								RotateLR(root);
							}
							else if (g->left == p) {
								RotateLR(g->left);
							}
							else if (g->right == p) {
								RotateLR(g->right);
							}
							//������ɫ
							br->node_color = p->node_color;
							p->node_color = black;
							//��������
							br->pr = g;
							p->pr = br;
							b->pr = br;
						}
						else {
							//	\
							//����
							if (p == root) {
								RotateL(root);
							}
							else if (g->left == p) {
								RotateL(g->left);
							}
							else if (g->right == p) {
								RotateL(g->right);
							}
							//������ɫ
							b->node_color = p->node_color;
							p->node_color = black;
							br->node_color = black;
							//��������
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
			//ɾ����㣬���Ȱ�d��������
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
		//�常����Ǻ�ɫ�����
		//����
		void RotateR(RB_Node<Type>*& ptr) {
			RB_Node<Type>* r = ptr;
			ptr = r->left;
			r->left = ptr->right;
			ptr->right = r;
		}
		//����
		void RotateL(RB_Node<Type>*& ptr) {
			RB_Node<Type>* l = ptr;
			ptr = l->right;
			l->right = ptr->left;
			ptr->left = l;
		}
		//�������
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
		//���Һ���
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