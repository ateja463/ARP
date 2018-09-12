#ifndef AVL_TREE_H
#define AVL_TREE_H





#include<bits/stdc++.h>
#include<cstring>
#include<iostream>
#include<pthread.h>

using namespace std;

namespace mylib
{
    struct DNSPacket	
    {
        string website;	
	
	string type;
	
	string ttl;
	
	string ipaddress;

	int length;  
    };

    struct AVLNode 
    {
	string key;

	string tuple[4];

	AVLNode *left;

	AVLNode *right;

	int height;
    };
    class AVLTree
    {
	private:        
	    
	    struct DNSPacket *dns;
	   
    	    struct AVLNode * root;

	    pthread_mutex_t lock;

	    void del_(struct AVLNode *t);

	    struct AVLNode *rightRotate(struct AVLNode *y);

	    struct AVLNode *leftRotate(struct AVLNode *x);

	    struct AVLNode * insert(struct AVLNode *t,string key,string tuple);

   	    int height(struct AVLNode *t);

	    int getBalance(struct AVLNode *t);

	    string search(struct AVLNode *t,string key);
	    //struct DNSPacket * search(struct AVLNode *t,string key)
	    void del();
	
	    void inorder(struct AVLNode *t);
		
	    int findlength(string ip);

	public:

	    AVLTree();

	    ~AVLTree();
	 
	    void createTree(char *file);

	    void inorder();

            string search(string key);
	    //struct DNSPacket *search(string key)
	};

}

#endif



