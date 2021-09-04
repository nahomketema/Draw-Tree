//Nahom Ketema


struct node{
	node();//constructor sets the next and previous node to null
	int data;
	node* next;
	node* previous;
};

class bst{
	public:
		bst();//
		~bst();
	private:
		void caller();
		int input();
		int input(node* head,int data);
		int height();//returns height of the tree
		int height(node* head);
		int display_traditional();//
		int count();
		int display_new();
		int delete_tree(node* head);
		node* root;
};
