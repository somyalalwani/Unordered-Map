#include<iostream>
using namespace std;

template<class T>
T maxo(T a, T b)
{
    return (a > b) ? a : b;
}
	

template <typename T, typename U>
class AVL
{
public:
	struct Node
	{
		T data;
        U value;
		struct Node* left;
		struct Node* right;
		int height;
	
	};
	
    unsigned long int mpSize = 0;
	struct Node* root=NULL;
	U df;


	
	Node* newnode(T x, U y)
	{
		Node* node = new Node();
		node->data = x;
		node->value = y;
        node->left = NULL;
		node->right = NULL;	
		node->height = 1;
		df = y;
		mpSize++;

		return node;
	}

	int height(Node* n)
	{
		if (n == NULL)
			return 0;
		return n->height;
	}
	Node* rotateLeft(Node* a)
	{
		Node* b = a->right;
		Node* c = b->left;
		
		b->left = a;
		a->right = c;
		
        a->height =1+ maxo(height(a->right),height(a->left)) ;
		b->height =1+ maxo(height(b->right),height(b->left)) ;
		
        return b;
	}

	Node* rotateRight(Node* node)
	{
		Node* head = node->left;
		Node* r = head->right;
		
		head->right = node;
		head->left = r;
		
		node->height =1+ maxo(height(node->right),height(node->left));
		head->height =1 +maxo(height(head->right),height(head->left));
		return head;
	}

	int getBalance(Node* node)
	{
		if (node == NULL)
			return 0;
		return height(node->left) - height(node->right);
	}
    
    void inOrder(Node* root)
	{cout<<"inorder::";
		if (root!=NULL)
		{
			
			inOrder(root->left);
				cout << root->data <<"  ";
			inOrder(root->right);
		}
	}

    Node* minValueNode(Node* node)
	{
		Node* p = node;
		while (p->left != NULL)
			p = p->left;
		return p;
	}
	Node* insertNode(Node* node, T x,U y)
	{
		if (node == NULL)
			return newnode(x,y);

		if (x < node->data)
			node->left = insertNode(node->left,x,y);
		
		else if (x > node->data)
			node->right = insertNode(node->right,x,y);
		
		node->height = 1 + maxo(height(node->right),height(node->left));
		
        int balance = getBalance(node);
		
    
		if (balance < -1 && x < node->right->data)
		{
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}
		if (balance > 1 && x > node->left->data)
		{
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
	
        if (balance > 1 && x < node->left->data)
			return rotateRight(node);
		
        if (balance < -1 && x > node->right->data)
			return rotateLeft(node);
	
    	return node;
	}

	void insert(T x, U y)
	{
		root = insertNode(root, x,y);
	}

	Node* erase(Node* root, T data)
	{
		if (root == NULL)
			return root;
        if (data > root->data)
			root->right = erase(root->right, data);
		else if (data < root->data)
			root->left = erase(root->left, data);
		
		else
		{
			if ((root->right!=NULL) || (root->left!= NULL))
                {
					Node* temp = minValueNode(root->right);
					root->data = temp->data;
					root->right = erase(root->right, temp->data);
				}
                else 
  				{
					Node* temp;
					if (root->left == NULL)
						temp = root->right;
					else
						temp = root->left;
					
                    if (temp == NULL) 
					{
						temp = root;
						root = NULL;
					}
					else
						*root = *temp;
				
                	free(temp);	
				}
		mpSize--;
		}

		if (root == NULL)
			return root;
		
        root->height = 1 + maxo(height(root->left), height(root->right));
		int balance = getBalance(root);
		if (balance < -1 && data < root->right->data)
		{
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
		if (balance > 1 && data > root->left->data)
		{
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
		if (balance > 1 && data < root->left->data)
			return rotateRight(root);

		if (balance < -1 && data > root->right->data)
			return rotateLeft(root);
		return root;
	}
    
	void erase(T data)
	{
		root = erase(root, data);
	}


	int size() {
		return mpSize;
	}
	void clear()
	{
		mpSize = 0;
		Node *temp= root;
		free(temp);
		root = NULL;
	}
	bool search(Node* root, T x) 
	{
		if (root == NULL)
			return false;

		if (x == root->data)
			return true;
		else if (x > root->data)
			return search(root->right,x);
		else
			return search(root->left,x);
	}

    bool find(T x)
	{
		return search(root,x);
	}
	
	struct Node* f(struct Node* node, T x)
	{
		if (node->data == x)
			return node;
		else if (x < node->data)
			return f(node->left, x);
		else if (x < node->data)
			return f(node->right, x);
	}

	U& findValueWRTKey(struct Node* node, T x)
	{
		if (node == NULL)
		{	
			(*this).root = insertNode((*this).root,x,df);
			Node* temp=f(root,x);
			//cout<<"aaaaaaaaaa";
			return temp->value;
			
		}

		if (node->data == x)
			{//cout<<"bbbbbbbbb";
				return node->value;
			}
		else if (x < node->data)
	{
	//cout<<"ccccc";	
		return findValueWRTKey(node->left,x);}
		else if (x > node->data)
			{//cout<<"ddddddd";
		return findValueWRTKey(node->right,x);}
	}

	U& operator [](T x)
	{
		return findValueWRTKey(root, x);
	}	
	
};

int main()
{
	AVL <string,float> ii;
	ii.insert("x",12);

	ii.insert("y",4);
    
	ii.erase("y");
	ii.insert("y",3);
    

  	ii["x"]=ii["y"]*2;
	cout<<ii["x"]<<endl<<ii["y"]<<endl;

  	ii["x"]=ii["x"]*2;
    cout<<ii["x"]<<endl<<ii["y"]<<endl;

    cout<<ii.find("x")<<endl; //if found returns 1, else 0
	cout<<ii.find("abc")<<endl;//if found returns 1, else 0

	cout<<ii.size()<<endl;
	ii.clear();
	cout<<"size="<<ii.size()<<endl;
	ii.insert("y",3);
	cout<<"size="<<ii.size()<<endl;

	
}