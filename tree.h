//Nahom Ketema

/*
Display as such

		12
	7		15
3		9 13	18
*/


struct node{
	node();//constructor sets the right and left node to null
	int data;
	node* right;
	node* left;
};

class bst{
	public:
		bst();//
		~bst();
	private:
		void caller();
		int insert(int data);
		int height();//returns height of the tree
		int display_traditional();//
		int count();
		int display_new();
		int delete_node(int value);
		int number_of_characters();
		int* array_by_level(int level);
		int insert_random_data();
		// The functions below are going to be used as wrapper functions for the recursive functions
		int number_of_characters(node*& root);//This returns the number of characters of the largest number
		int delete_node(node*& root, int value);
		int delete_tree(node*& root);
		int count(node*& root);
		int display_traditional(node*& root);
		int height(node*& root);
		int insert(node*& root,int data);
		int in_order_successor(node*& root);
		void array_by_level(node*& root, int current_height, int start_index, int level, int*& data);
		node* root;
};
