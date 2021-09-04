#include "tree.h"
#include <iostream>

node::node(){
	previous=NULL;
	next=NULL;
}

bst::bst(){
	root=NULL;
	caller();
}

bst::~bst(){
	delete_tree(root);
}

void bst::caller(){
	char c;
	cout<<"Pick an option below"<<endl;
	cout<<"1. Input data"<<endl;
	cout<<"2. Display data sorted."<<endl;
	cout<<"3. Display organized"<<endl;
	cout<<"4. Display height"<<endl;
	cout<<"5. Exit"<<endl;
	do{
		cin>>c;
		switch(c){
			case '1':
				input();
			case '2':
				display_traditional();
			case '3':
				display_new();
			case '4':
				cout<<height()<<endl;
			case '5':
				cout<<"Program Terminated."<<endl;
		}
	}while();
}

int bst::input(){
	//
}

int input(node* head,int data){
	//
}

int bst::height(){
	//
}

int height(node* head){
	//
}

int bst::display_traditional(){
	//
}

int bst::count(){
	//
}

int bst::display_new(){
	//
}

int bst::delete_tree(node* head){
	//
}
