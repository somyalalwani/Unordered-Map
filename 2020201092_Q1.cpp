#include<iostream>
#include <typeinfo>
#include<bits/stdc++.h>
template<typename T>
T max(T a, T b)  
{  
    return (a > b)? a : b;  
}

template<typename T>
class Node
{
public:
	T key;
	int height=0;
	int count=0;
    int right_count=0;
    int left_count=0;
	Node<T> *right=NULL;
    Node<T> *left=NULL;
};

template<class T>
Node<T> * newNode(T key)  
{  
    Node<T> * node = new Node<T>(); 
    node->key = key;  
    node->right = NULL;  
    node->left = NULL;  
    node->height = 1;
    node->count = 1;
    node->right_count=0;
    node->left_count=0;
    return(node);  
}

template<class T>
Node<T> * minValueNode(Node<T> * node) 
{ 
    Node<T>* current = new Node<T>();
    current=node; 
  
    while (current->left != NULL) 
        current = current->left; 
  
    return current; 
} 
  
template<class T>
int height(Node<T> *N)  
{  
    if (N == NULL)  
        return 0;  
    return N->height;  
}    

template<class T>
int getBalance(Node<T> *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) - height(N->right);  
}

template<class T>  
Node<T> *leftRotate(Node<T> *x)  
{  
    Node<T> *y = new Node<T>();
    y=x->right;  
    Node<T> *T2 = new Node<T>();
    T2=y->left;  
    
    y->left = x;  
    x->right = T2;  
    if(x->right)
    x->right_count=x->right->count + x->right->right_count + x->right->left_count;
    if(y->left)
    y->left_count=y->left->count + y->left->right_count + y->left->left_count;
 
    x->height = max(height(x->left),height(x->right)) + 1;  
    y->height = max(height(y->left),height(y->right)) + 1;  
    
    return y;  
} 

template<class T>
Node<T> *rightRotate(Node<T> *y)  
{  
    Node<T> *x=new Node<T>();
    x = y->left;  
    Node<T> *T2 = new Node<T>();
    T2=x->right;  
    x->right = y;  
    y->left = T2;  
    if(T2)
    y->left_count = T2->count + T2->left_count + T2->right_count;
    if(y)
    x->right_count = y->count + y->right_count + y->left_count;
    
    y->height = max(height(y->left),height(y->right)) + 1;  
    x->height = max(height(x->left),height(x->right)) + 1;  
    return x;  
}  


template<class T>
Node<T> * erase(Node<T>* root,T x)
{
	if(root==NULL)
		return root;

	if(x<root->key)
    {
        root->left_count=root->left_count -1;
		root->left=erase(root->left,x);
    }
    else if(x>root->key)
	{
        root->right_count = root->right_count -1;
    	root->right=erase(root->right,x);
	}

    else
	{
	if(root->count>1)
	{
		--(root->count);
		return root;
	}	
	if((root->left==NULL)||(root->right==NULL))
	{
	Node<T>* temp=new Node<T>();
    temp=root->left?root->left:root->right;	
	
	if(temp==NULL)
	{
	temp=root;
	root=NULL;
	}
	else 
	{*root=*temp;
	free(temp);
	}	
    }
    else {
    Node<T>* temp=new Node<T>();
    temp=minValueNode(root->right);
    root->key = temp->key; 
    root->count = temp->count; 
    temp->count = 1; 
    root->right = erase(root->right, temp->key); 
    }
	}
    if (root == NULL) 
        return root;
	root->height = max(height(root->left), height(root->right)) + 1; 
    int balance = getBalance(root); 
 
    if (balance > 1 && getBalance(root->left) < 0) { 
        root->left = leftRotate(root->left); 
        return rightRotate(root); 
    } 

    if (balance > 1 && getBalance(root->left) >= 0) 
        return rightRotate(root); 
  
  
    if (balance < -1 && getBalance(root->right) > 0) { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 

    if (balance < -1 && getBalance(root->right) <= 0) 
        return leftRotate(root); 
  
    return root;
}

template<class T>
Node<T> * insert(Node<T>* root,T x)
{
	if (root == NULL)  
        return(newNode(x));  

	if(x==root->key)
	{
	(root->count)++;
	return root;
	}
    
    if (x < root->key)  
        {
            ++root->left_count;
            root->left = insert(root->left, x);  
        }
    else 
    {
        ++root->right_count;
        root->right = insert(root->right, x);  
    }
    
    root->height = 1 + max(height(root->left),height(root->right));
	int balance = getBalance(root);  
  
    if (balance < -1 && x > root->right->key) 
        return leftRotate(root);  
  	  
    if (balance > 1 && x < root->left->key) 
        return rightRotate(root);  
  
    if (balance < -1 && x < root->right->key) 
    {  
        root->right = rightRotate(root->right);  
        return leftRotate(root);  
    }  

    if (balance > 1 && x > root->left->key) 
    {  
        root->left = leftRotate(root->left);  
        return rightRotate(root);  
    }  
    
    return root;	
}

template<class T>
void search(Node<T>* root,T x)
{
    Node<T> *temp = new Node<T>();
	temp = root;
	while(temp != NULL)
	{
		if(temp->key == x)
		{
			std::cout<<"\nYes";
			return;
		}
		else if(temp->key < x)
			temp = temp->right;
		else
			temp = temp->left;
	}
 
	std::cout<<"\n No";
	return;
}

template<class T>
void count(Node<T>* root, T x)
{
    Node<T> *temp = new Node<T>();
	temp = root;
	while(temp != NULL)
	{
		if(temp->key == x)
		{
			std::cout<<temp->count;
			return;
		}
		else if(temp->key > x)
			temp = temp->left;
		else
			temp = temp->right;
	}
 
	std::cout<<"0";
	return;
}

template<class T>
T lower_bound(Node<T>* root,T x)
{ Node<T> *temp = new Node<T>();
    temp=root;
    T ans;
    
    while (temp != NULL)
    {
        if(temp->key==x)
            {
                ans= temp->key;
                break;
            } 
    
        else if (temp->key > x)
            {
                ans=temp->key; 
                temp = temp->left;
            }
        
        else{
            temp = temp->right;
            }
    }
    
    return ans;
}

template<class T>
T upper_bound(Node<T>* root,T x)
{ Node <T>*temp = new Node<T>();
temp=root;
    T ans;
    
    while (temp != NULL)
    {
        if (temp->key > x)
            {
                ans=temp->key; 
                temp = temp->left;
            }
        else{
            temp = temp->right;
            }
    }
    
    return ans;
}
template <class T>
void maxDiffUtil(Node<T> *node, T k, T &min_diff,T &min_diff_key) 
{ 
    if (node == NULL) 
        return;  
    if (node->key == k) 
    {   min_diff_key = k; 
        return; 
    } 
  
    if (min_diff > abs(node->key - k)) 
    { 
        min_diff = abs(node->key - k); 
        min_diff_key = node->key; 
    } 
   if (k < node->key) 
        maxDiffUtil(node->left, k, min_diff, min_diff_key); 
    else
        maxDiffUtil(node->right, k, min_diff, min_diff_key); 
}
template<class T>
void preOrder(Node <T>* root) 
{ 
    if (root != NULL) { 
        std::cout<<root->key<<" ("<<root->count<<")  "; 
        preOrder(root->left); 
        preOrder(root->right); 
    } 
} 

template<class T>
void postOrder(Node<T>* root) 
{ 
    if (root != NULL) { 
         
        postOrder(root->left); 
        postOrder(root->right);
        std::cout<<root->key<<" ("<<root->count<<")  "; 
    } 
}

template<class T>
void inOrder(Node<T>* root) 
{ 
    if (root != NULL) { 
        inOrder(root->left); 
        std::cout<<root->key<<" ("<<root->count<<")  "; 
        inOrder(root->right); 
    } 
}
template<class T>
T closest(Node<T> * root, T k) 
{
        T min_diff = INT_MAX;
        T min_diff_key = -1; 
        maxDiffUtil(root, k, min_diff, min_diff_key); 
        
    return min_diff_key;
}

template<class T>
void k_largest(Node <T> * root, int k)
{
    if(root==NULL)
    {
        std::cout<<"dne";
        return;
    }
    if(root)
    {
      Node <T>* temp=new Node<T>();
      temp=root;
      while(temp)
      {
	     if(temp->right_count + temp->count == k)
	        {std::cout<<temp->key;
            return;
            }
	     else if(k>temp->right_count+temp->count)
	     {
	        k = k - (temp->right_count+temp->count);
	        temp=temp->left;
	     }
	    else
	        temp=temp->right;
    }
    }
    std::cout<<"dne";
return;
}

template<class T>
int count_in_range(Node<T> *root,T low,T high)
{
if (!root){
      return 0;
   }
   if (root->key == high && root->key == low){
      return root->count;
   }
   if (root->key <= high && root->key >= low){
      return (root->count) + count_in_range(root->left, low, high) +
      count_in_range(root->right, low, high);
   }
   else if (root->key < low){
      return count_in_range(root->right, low, high);
   }
   else{
      return count_in_range(root->left, low, high);
   }
}


int main()
{
Node<int> *a=NULL;
/*
int choice=0;
while(choice!=13)
{

std::cout<< "Choose a number"<<std::endl;
std::cout<<"	1 : Insertion"<<std::endl;
std::cout<<"	2 : Deletion"<<std::endl;
std::cout<<"    3 : Search"<<std::endl;
std::cout<<"	4 : Count occurrences of element"<<std::endl;
std::cout<<"	5 : lower_bound"<<std::endl;
std::cout<<"	6 : upper_bound"<<std::endl;
std::cout<<"	7 : Closest Element to some value"<<std::endl;
std::cout<<"	8 : K-th largest element"<<std::endl;
std::cout<<"	9 : Count the number of elements in the tree for given range"<<std::endl;
std::cout<<"    10 : PreOrder"<<std::endl;
std::cout<<"    11 : Inorder"<<std::endl;
std::cout<<"    12 : PostOrder"<<std::endl;
std::cout<<"    13 : To end"<<std::endl;

std::cin>>choice;
switch(choice)
{
case 1 : {
		std::cout<<"Enter key to insert : ";
		int x;
        std::cin>>x;
        root=insert(root,x);
        std::cout<<std::endl;
        }
        break;
case 2 : {
		std::cout<<"Enter key to delete : ";
		int x;
        std::cin>>x;
        root=erase(root,x);
        std::cout<<std::endl;
        }
        break;
case 3 :{
        std::cout<<"Enter key to search : ";
		int x;
        std::cin>>x;
        search(root,x);
        std::cout<<std::endl;
        }
        break;
case 4 : {
		std::cout<<"Enter key to count its occurenece : ";
		int x;
        std::cin>>x;
        count(root,x);
        std::cout<<std::endl;
        }
        break;
case 5 : {
		std::cout<<"Enter key to find its lower bound : ";
		int x;
        std::cin>>x;
        std::cout<<lower_bound(root,x)<<std::endl;
        }
        break;
case 6 : {
		std::cout<<"Enter key to find its upper bound : ";
		int x;
        std::cin>>x;
        std::cout<<upper_bound(root,x)<<std::endl;
        }
        break;

case 7 :
        {
        std::cout<<"Enter key to find its closest element : ";
		int x;
        std::cin>>x;
        closest(root,x);
        std::cout<<std::endl;
        }
        break;
case 8 : {
        std::cout<<"Enter k to find k-largest element : ";
		int x;
        std::cin>>x;
        k_largest(root,x);
        std::cout<<std::endl;
        }
        break;
case 9 :{
        std::cout<<"Count the number of elements in the tree whose values fall into a given range. Enter low : ";
		int x;
        std::cin>>x;
        std::cout<<"Enter high";
        int y;
        std::cin>>y;
        count_in_range(root,x,y);
        std::cout<<std::endl;
        }
        break;
case 10 :preOrder(root);break;
case 11 :inOrder(root);break;
case 12 : postOrder(root);   break;  
case 13 : break;   
default : std::cout<<"Wrong choice\n";    
    }
}
*/



/*
root=insert(root,20);
root=insert(root,30);
root=insert(root,25);
root=insert(root,35);
root=insert(root,25);
root=insert(root,10);
root=insert(root,15);
root=insert(root,5);

inOrder(root);

std::cout<<std::endl;
root=erase(root,10);
root=erase(root,1);
root=erase(root,20);
inOrder(root);

search(root,15);
search(root,67);
search(root,35);

root=insert(root,10);
root=insert(root,35);

root=insert(root,20);
inOrder(root);
std::cout<<std::endl;

std::cout<<"count of 12:";
count(root,12);
std::cout<<std::endl;
std::cout<<"count of 30:";
count(root,30);
std::cout<<std::endl;

std::cout<<lower_bound(root,32)<<std::endl;
std::cout<<lower_bound(root,23)<<std::endl;
std::cout<<lower_bound(root,32)<<std::endl;
std::cout<<upper_bound(root,25)<<std::endl;
std::cout<<std::endl;
std::cout<<closest(root,100)<<std::endl;
inOrder(root);
std::cout<<std::endl;
std::cout<<count_in_range(root,3,35)<<std::endl;
k_largest(root,2);

*/

a.insert(30);
    a.insert(10);
    a.insert(25);
    a.insert(20);
    a.insert(40);
    a.insert(50);
    a.insert(25);
    a.insert(35);
    a.insert(50);
    a.insert(25);
    /*a.insert(1);
    a.insert(2);
    a.insert(3);
    a.insert(4);
    a.insert(1);*/
    cout<<"inorder = "<<endl;
    a.inordertrav();
    cout<<endl<<"preorder"<<endl;
    a.preordertrav();
    cout<<endl;
    cout<<a.mainsearch(12);
    cout<<endl;
    cout<<a.mainsearch(50)<<endl;
    cout<<"the occurance of 50 is : - "<<a.countoccurance(50)<<endl;
    cout<<"the occurance of 30 is : - "<<a.countoccurance(30)<<endl;
    cout<<"the occurance of 12 is : - "<<a.countoccurance(12)<<endl;
    cout<<".........................."<<endl;
    cout<<"lower bound of 7 is = "<<a.lowerbound(7)<<endl;
    cout<<"lower bound of 40 is = "<<a.lowerbound(40)<<endl;
    cout<<"lower bound of 22 is = "<<a.lowerbound(22)<<endl;
    cout<<".........................."<<endl;
    cout<<"upper bound of 7 is = "<<a.upperbound(7)<<endl;
    cout<<"upper bound of 40 is = "<<a.upperbound(40)<<endl;
    cout<<"upper bound of 31 is = "<<a.upperbound(31)<<endl;
    cout<<".........................."<<endl;
    cout<<"closest value to 7 is = "<<a.closestvalue(7)<<endl;
    cout<<"closest value to 22 is = "<<a.closestvalue(22)<<endl;
    cout<<"closest value to 7 is = "<<a.closestvalue(7)<<endl;
    cout<<"closest value to 60 is = "<<a.closestvalue(60)<<endl;
    cout<<".........................."<<endl;
    cout<<"1 largest value is = "<<a.kthlargest(1)<<endl;
    cout<<"2 largest value is = "<<a.kthlargest(2)<<endl;
    cout<<"3 largest value is = "<<a.kthlargest(3)<<endl;
    cout<<"4 largest value is = "<<a.kthlargest(4)<<endl;
    cout<<"5 largest value is = "<<a.kthlargest(5)<<endl;
    cout<<"6 largest value is = "<<a.kthlargest(6)<<endl;
    cout<<"7 largest value is = "<<a.kthlargest(7)<<endl;
    cout<<"8 largest value is = "<<a.kthlargest(8)<<endl;
    cout<<"9 largest value is = "<<a.kthlargest(9)<<endl;
    cout<<"10 largest value is = "<<a.kthlargest(10)<<endl;
    a.deletion(25);
    a.deletion(10);
    a.deletion(30);
    cout<<"inorder = "<<endl;
    a.inordertrav();
    cout<<endl<<"preorder"<<endl;
    a.preordertrav();
    cout<<endl;
    cout<<a.mainsearch(12);
    cout<<endl;
    cout<<a.mainsearch(50)<<endl;
    cout<<"the occurance of 50 is : - "<<a.countoccurance(50)<<endl;
    cout<<"the occurance of 30 is : - "<<a.countoccurance(30)<<endl;
    cout<<"the occurance of 12 is : - "<<a.countoccurance(12)<<endl;
    cout<<".........................."<<endl;
    cout<<"lower bound of 7 is = "<<a.lowerbound(7)<<endl;
    cout<<"lower bound of 40 is = "<<a.lowerbound(40)<<endl;
    cout<<"lower bound of 22 is = "<<a.lowerbound(22)<<endl;
    cout<<".........................."<<endl;
    cout<<"upper bound of 7 is = "<<a.upperbound(7)<<endl;
    cout<<"upper bound of 40 is = "<<a.upperbound(40)<<endl;
    cout<<"upper bound of 31 is = "<<a.upperbound(31)<<endl;
    cout<<".........................."<<endl;
    cout<<"closest value to 7 is = "<<a.closestvalue(7)<<endl;
    cout<<"closest value to 22 is = "<<a.closestvalue(22)<<endl;
    cout<<"closest value to 7 is = "<<a.closestvalue(7)<<endl;
    cout<<"closest value to 60 is = "<<a.closestvalue(60)<<endl;
    cout<<".........................."<<endl;
    cout<<"1 largest value is = "<<a.kthlargest(1)<<endl;
    cout<<"2 largest value is = "<<a.kthlargest(2)<<endl;
    cout<<"3 largest value is = "<<a.kthlargest(3)<<endl;
    cout<<"4 largest value is = "<<a.kthlargest(4)<<endl;
    cout<<"5 largest value is = "<<a.kthlargest(5)<<endl;
    cout<<"6 largest value is = "<<a.kthlargest(6)<<endl;
    cout<<"7 largest value is = "<<a.kthlargest(7)<<endl;
    cout<<".........................................."<<endl;
return 0;
}