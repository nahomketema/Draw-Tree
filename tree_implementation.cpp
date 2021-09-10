#include "tree.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <string>
using namespace std;


node::node(){
	left=NULL;
	right=NULL;
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
	do{
		cout<<"      21000   "<<endl;
		cout<<"     /     \\  "<<endl;
		cout<<"12          52000"<<endl;
		cout<<"Pick an option below. Note that this program only works with positive numbers for now."<<endl;
		cout<<"1. Input data"<<endl;
		cout<<"2. Display data sorted."<<endl;
		cout<<"3. Display organized"<<endl;
		cout<<"4. Delete certain value(all matches)"<<endl;
		cout<<"5. Exit"<<endl;
		cin>>c;
		if(c == '1'){
			int number;
			cout<<"Please input the number you want to add to the tree: ";
			cin>>number;
			cin.ignore(100,'\n');
			int retval = insert(number);
			if(retval == 0){
				cout<<"The number "<<number<<" has been inserted to the tree"<<endl;
			}
			else{
				cout<<"Something wrong happened. Please try again."<<endl;
			}
		}	
		else if(c == '2'){
			//display_traditional();
			insert_random_data();
			int tree_height = height();
			cout<<"Height: "<<tree_height<<endl;
			for(int k=0; k<tree_height; ++k){
				int level = k;
				int* tmp = array_by_level(level);
				int square = pow(2,level);
				for(int i=0; i<square; ++i){
					cout<<tmp[i]<<" ";
				}
				cout<<"\n"<<endl;
				delete [] tmp;
			}
		}
		else if(c == '3'){
			display_new();
		}
		else if(c == '4'){
			cout<<height()<<endl;
		}
		else if(c == '5'){
			cout<<"Program Terminated."<<endl;
		}
		else{
			cout<<"Invalid input. Please try again."<<endl;
		}
	}while(c != '5');
}

int bst::insert(int data){
	//	Return values
	//	0: Success
	//	1: Failure to make node
	return insert(root, data);
}

int bst::insert(node*& root,int data){
	if(root == NULL){
		root = new node;
		if(root == NULL){
			return 1;
		}
		root->data = data;
		return 0;
	}
	if(data < root->data){
		return insert(root->left, data);
	}
	//Goes here if data >= root->data
	return insert(root->right, data);
}

int bst::height(){
	return height(root);
}

int bst::height(node*& root){
	if(root == NULL){
		return 0;
	}
	int left = 1 + height(root->left);
	int right = 1 + height(root->right);
	if(left > right){
		return left;
	}
	//Goes here if left <= right
	return right;
}

int bst::display_traditional(){
	return display_traditional(root);
}

int bst::display_traditional(node*& root){
	if(root == NULL){
		return 0;
	}
	display_traditional(root->left);
	cout<<root->data<<"  ";
	display_traditional(root->right);
	cout<<endl;
	return 0;
}

int bst::count(){
	return count(root);
}

int bst::count(node*& root){
	if(root == NULL){
		return 0;
	}
	return 1 + count(root->left) + count(root->right);
}

int bst::display_new(){
	return 0;
}

int bst::delete_tree(node*& root){
	if(root == NULL){
		return 0;
	}
	delete_tree(root->right);
	delete_tree(root->left);
	if((root->left == NULL) && (root->right == NULL)){
		delete root;
	}
	return 0;
}

int bst::delete_node(int value){
	//	Return values
	//	0: Success
	//	1: value not found
	return delete_node(root,value);
}

int bst::delete_node(node*& root, int value){//double check whether the return values work
	if(root == NULL){
		return 1;
	}
	if(root->data == value){
		if((root->right == NULL) && (root->left == NULL)){
			delete root;
			root = NULL;
		}
		if((root->right == NULL) && (root->left != NULL)){
			node* tmp = root->left;//It doesn't matter if it is null or not
			delete root;
			root = tmp;
		}
		else if((root->right != NULL) && (root->left == NULL)){
			node* tmp = root->right;
			delete root;
			root = tmp;
			delete_node(root, value);//In case of duplicate data
		}
		else{
			root->data = in_order_successor(root->right);
		}
		return 0;
	}
	if(root->data > value){
		return delete_node(root->left, value);
	}
	//Goes here if root->data < value
	return delete_node(root->right, value);
}

int bst::in_order_successor(node*& root){
	if(root == NULL){
		return -1;
	}
	if(root->left == NULL){
		int value = root->data;
		node* tmp = root->right;
		delete root;
		root = tmp;
		return value;
	}
	return in_order_successor(root->left);
}

int bst::number_of_characters(){
	return number_of_characters(root);
}

int bst::number_of_characters(node*& root){
	if(root == NULL){
		return 0;
	}
	if(root->right == NULL){
		//Find the number of characters of root->data here and return it
		return to_string(root->data).length();
	}
	return number_of_characters(root->right);
}

int* bst::array_by_level(int level){
	//The level argument starts at zero
	int size = pow(2,level);
	int* array = new int[size];
	array_by_level(root, 0, 0, level, array);
	return array;
}

void bst::array_by_level(node*& root, int current_height, int start_index, int level, int*& data){
	//Returns a full array where null values get represented by -1
	if(root == NULL){
		//set values to -1 here
		int how_many_zeroes = pow(2, level-current_height);
		for(int counter = start_index; counter < start_index+how_many_zeroes; ++counter){
			//cout<<counter<<endl;
			data[counter] = -1;
		}
		return;
	}
	if(current_height == level){
		data[start_index] = root->data;
	}
	array_by_level(root->left, ++current_height, 2*start_index, level, data);
	array_by_level(root->right, ++current_height, (2*start_index)+1, level, data);
	return;
}

int bst::insert_random_data(){
	//This function inserts random data in order to help avoid having to type in data everytime
	srand(time(0));
	int count = rand() %100 +1;
	for(int i=0; i<count; ++i){
		int retval = insert(rand() %100 +1);
		if(retval != 0){
			cout<<"Something wrong happened. Please try again."<<endl;
			return 1;
		}
	}
	return 0;
}