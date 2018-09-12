

#include<iostream>
#include<pthread.h>
#include"AVLTree.h"

using namespace std;
using namespace mylib;

AVLTree::AVLTree()
{
    root=NULL;
    dns=new DNSPacket;
}

AVLTree::~AVLTree()
{
    del();
}

void AVLTree::del()
{
   pthread_mutex_lock(&lock);
   del_(root);
   pthread_mutex_unlock(&lock);
}

void AVLTree::del_(struct AVLNode *root)
{
    if(root==NULL) return;
    del_(root->left);
    del_(root->right);
    delete(root);
}


	
void AVLTree::createTree(char *file)
{
	pthread_mutex_lock(&lock);
	fstream f;
	f.open (file);
	string s,s1;
	while(f)
	{
		getline(f,s);
		s1=s;
		char *key=strtok(&s1[0],", ");
		if(s!="") root=insert(root,key,s);
	}
	pthread_mutex_unlock(&lock);
	
}

struct AVLNode * AVLTree:: insert(struct AVLNode *root,string key,string tuple)
{
    if(root==NULL)
    {
        root=new AVLNode;
	root->key = key;
	char *tok=strtok(&tuple[0],", ");
	int i=0;
	while(tok!=NULL)
	{
            root->tuple[i++]=tok;
	    //cout<<root->tuple[i-1]<<endl;
            tok=strtok(NULL,", ");
	}
	root->left=NULL;
	root->right=NULL;
	root->height=1;
	return root;
    }
   // char *a=&key[0];
    //char *b=&root->key[0];
    if(key<root->key)//if(strcmp(a,b)<0)
    {
        root->left=insert(root->left,key,tuple);
    }  
    else if (key>root->key)//else if( strcmp(a,b)>0)
    {
	root->right=insert(root->right,key,tuple);
    }
    else return root;
    root->height=1+max(height(root->left),height(root->right));
    int balance = getBalance(root);
    // cout<<balance<<" <- balance "<<endl;

    if (balance > 1 && key < root->left->key)
    return rightRotate(root);

    if (balance < -1 && key > root->right->key)
    return leftRotate(root );

    if (balance > 1 && key >root->left->key)
    {
        root->left = leftRotate(root->left);
	return rightRotate(root);
    }
    if (balance < -1 && key < root->right->key)
    {
	root->right = rightRotate(root->right);
	return leftRotate(root);
    }
    return root;
}

void AVLTree::inorder()
{
	pthread_mutex_lock(&lock);
	inorder(root);
	pthread_mutex_unlock(&lock);
}
void AVLTree:: inorder(struct AVLNode *root)
{
    if(root!=NULL)				       
    {
	inorder(root->left);
	cout<<root->tuple[0]<<" "<<root->tuple[1]<<" "<<root->tuple[2]<<" "<<root->tuple[3]<<" height"<<root->height<<"\n";
	inorder(root->right);
    }
}



int AVLTree:: height(struct AVLNode *root)
{
   
    if(root==NULL) return 0;
    else return root->height;
   
}



int AVLTree:: getBalance(struct AVLNode *root)
{

    if(root==NULL) return 0;	
    else return height(root->left)-height(root->right);	

}



struct AVLNode * AVLTree:: rightRotate(struct AVLNode *y)
{

    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
  
}



struct AVLNode * AVLTree:: leftRotate(struct AVLNode *x)
{

    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
  
}




int AVLTree::findlength(string ip)
{
	char *key=strtok(&ip[0],"-");
	int i=0;
	while(key!=NULL)
	{
		key=strtok(NULL,"-");
		i++;
	}
	return i;
}
//struct DNSPacket * AVLTree::search(string key)
string AVLTree::search(string key)
{
	pthread_mutex_lock(&lock);
	string s=search(root,key);
	//dns=search(root,key);
	pthread_mutex_unlock(&lock);
	return s;
	//return dns;
}
//struct DNSPacket * AVLTree:: search(struct AVLNode *root,string key)
string AVLTree:: search(struct AVLNode *root,string key)
{
    while(root!=NULL)			      
    {
        if(key<root->key)
	{
	    return search(root->left,key);
	}
	else if(key>root->key)
	{
	    return search(root->right,key);
	}
	else 
	{
/*		dns->website=root->tuple[0];
		dns->type=root->tuple[1];
		dns->ttl=root->tuple[2];
		dns->ipaddress=root->tuple[3];
		dns->length=findlen(root->tuple[3]);
		return dns;*/
		return "query: "+root->tuple[0]+"\ntype: "+root->tuple[1]+"\nttl: "+root->tuple[2]+"\nIPaddr: "+root->tuple[3];
	}
    }
    return "not found";
    /*
        dns->website=key;
	dns->type="not found";
	dns->ttl="not found";
	dns->ipaddress="not found";
	dns->length=0;
	return dns;
	
    */
}

