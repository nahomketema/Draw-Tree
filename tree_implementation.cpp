#include "tree.h"
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <cstring>
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
		cout<<"Pick an option below. Note that this program only works with positive numbers for now."<<endl;
        cout<<"         - Works best when tree height is less than 4. Try sample data to see that"<<endl;
        cout<<"**************************************************************************************"<<endl;
		cout<<"1. Input data manually"<<endl;
		cout<<"2. Input random data"<<endl;
        cout<<"3. Input sample data"<<endl;
		cout<<"4. Display data sorted(Old)"<<endl;
		cout<<"5. Display organized(New)"<<endl;
		cout<<"6. Delete certain value(all matches)"<<endl;
		cout<<"7. Exit"<<endl;
		cin>>c;
		if(c == '1'){
			int number;
			cout<<"Please input the number you want to add to the tree: ";
			cin>>number;
			cin.ignore(100,'\n');
			int retval = insert(number);
			if(retval == 0){
				cout<<"The number "<<number<<" has been inserted to the tree."<<endl;
			}
			else{
				cout<<"Something wrong happened. Please try again."<<endl;
			}
		}	
		else if(c == '2'){//realized that there is no good way to represent a lot of data on the terminal so i preset the amount of random data to 10
			int retval = insert_random_data(10);
			if(retval == 0){
				cout<<"Ten random numbers have been inserted to the tree."<<endl;
			}
			else{
				cout<<"Something wrong happened. Please try again."<<endl;
			}
		}
        else if(c == '3'){
            sample_data();
        }
		else if(c == '4'){
			display_traditional();
		}
		else if(c == '5'){
			display_new();
		}
		else if(c == '6'){
			int number;
			cout<<"Please input the data you want to remove from the tree: ";
			cin>>number;
			int retval = delete_node(number);
			if(retval == 0){
				cout<<"The number has been removed from the tree."<<endl;
			}
			else if(retval == 1){
				cout<<"The number you were looking for was not found. Please try again."<<endl;
			}
		}
		else if(c == '7'){
			cout<<"Program Terminated."<<endl;
		}
		else{
			cout<<"Invalid input. Please try again."<<endl;
		}
	}while(c != '7');
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
	int retval = display_traditional(root);
	cout<<endl;
	return retval;
}

int bst::display_traditional(node*& root){
	if(root == NULL){
		return 0;
	}
	display_traditional(root->left);
	cout<<root->data<<" -> ";
	display_traditional(root->right);
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
	int tree_height = height();
	for(int k=0; k<tree_height; ++k){
		int level = k;
		int* tmp = array_by_level(level);
		int square = pow(2,level);
		for(int i=0; i<square; ++i){
			int character_count = number_of_characters();
			if(i == 0){
				string space(character_count * (pow(2, tree_height - 1 - level)-1),' ');
				if(tmp[i] != -1){
					char* printable_number = to_maximum(tmp[i]);
					cout<<space<<printable_number;
					delete [] printable_number;
				}
				else{
					string num_space(character_count, ' ');
					cout<<space<<num_space;
				}
			}
			else{
				string space(character_count * (pow(2, tree_height - level)-1),' ');
				if(tmp[i] != -1){
					char* printable_number = to_maximum(tmp[i]);
					cout<<space<<printable_number;
					delete [] printable_number;
				}
				else{
					string num_space(character_count, ' ');
					cout<<space<<num_space;
				}
			}
		}
		cout<<"\n"<<endl;
		delete [] tmp;
	}
	return 0;
}

char* bst::to_maximum(int data){
	int maximum = number_of_characters();
	string this_number = to_string(data);
	string zeroes;
	for(int i=0; i<maximum - (int)this_number.length(); ++i){
		zeroes.append("0");
	}
	zeroes.append(this_number);
	char* value = new char[zeroes.length() + 1];
	strcpy(value, zeroes.c_str());
	return value;
}

int bst::delete_tree(node*& root){
	if(root == NULL){
		return 0;
	}
	delete_tree(root->right);
	delete_tree(root->left);
	if((root->left == NULL) && (root->right == NULL)){
		delete root;
        root = NULL;
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
        else if((root->right == NULL) && (root->left != NULL)){
			node* tmp = root->left;//It doesn't matter if it is null or not
			delete root;
			root = tmp;
		}
		else{
			root->data = in_order_successor(root->right);
		    delete_node(root, value);//In case of duplicate data
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
		if(current_height <= level){
			int how_many_zeroes = pow(2, level-current_height);
			int start = start_index*how_many_zeroes;
			int end = start + how_many_zeroes;
			while(start < end){
				data[start] = -1;
				++start;
			}
		}
		return;
	}
	array_by_level(root->left, current_height + 1, 2*start_index, level, data);
	if(current_height == level){
		data[start_index] = root->data;
	}
	array_by_level(root->right, current_height + 1, (2*start_index)+1, level, data);
	return;
}

int bst::insert_random_data(int count){
	//This function inserts random data in order to help avoid having to type in data everytime
	srand(time(0));
	for(int i=0; i<count; ++i){
		int retval = insert(rand() %100 +1);
		if(retval != 0){
			cout<<"Something wrong happened. Please try again."<<endl;
			return 1;
		}
	}
	return 0;
}

void bst::sample_data(){
    delete_tree(root);
    insert(50);
    insert(25);
    insert(75);
    insert(12);
    insert(37);
    insert(63);
    insert(87);
}
