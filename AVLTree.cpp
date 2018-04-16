#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<fstream>
#include<string>

using namespace std;
//Creating nodes
struct node
{
    int value;
    struct node *left;
    struct node *right;
}*root;

//Creating the AVL Tree class
class Tree
{
    public:
        int height(node *);
        int check_balance(node *);
        node* balance(node *);
        node *right_rotate(node *);
        node *left_rotate(node *);
        node *lr_rotate(node *);
        node *rl_rotate(node *);
        node* insert(node *, int, ofstream&);
        node* delete_node(node *, int, ofstream&);
        node* inorderpredecessor(node *);
        void search(node *, int, ofstream&);
        void delete_tree(node *);
        void inorder(node *, ofstream&);
        void preorder(node *, ofstream&);
        void postorder(node *, ofstream&);
        void emptyTree(node *, ofstream&);
        void write2TerminalandFile(string, ofstream&);
        Tree()
        {
            root=NULL;
        }
};
int main()
{
    int choice, item;
    Tree t;
    string str;
    ofstream opfile;//Creating output stream file
	opfile.open("Pal-A02237918.txt");//Output file where all output is stored
	do
    {
		ifstream infile;
    	cout<<"\n";
    	cout<<"AVL Tree Menu Options"<<endl;
    	cout<<"---------------------"<<endl;
        cout<<"1.Create a Tree"<<endl;
		cout<<"2.Insert Node into the tree"<<endl;
        cout<<"3.Delete Node from the existing tree"<<endl;
        cout<<"4.Search a Node in the tree"<<endl;
		cout<<"5.Delete entire tree"<<endl;
		cout<<"6.Traversal- Preorder, Postorder and Inorder"<<endl;
        cout<<"7.Check Balance of the tree"<<endl;
		cout<<"8.Exit"<<endl;
        cout<<"Choose the option to be performed: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
        	if(root!=NULL)
        	{
			t.delete_tree(root);
			root=NULL;
			}
			//Existing tree is deleted before taking new input file
			char filename[100];
			cout<<"Enter name of input file"<<endl;
			cin>>filename;
			infile.open(filename, ios::in);//opening input file
			while(infile>>item)
        	{
        		//Inserting nodes in a tree
        		root=t.insert(root,item, opfile);
			}
			str="Preorder Traversal for the new Tree after creation: ";
            t.write2TerminalandFile(str, opfile);
            t.preorder(root,opfile);
            cout<<endl;
            opfile<<endl;
            infile.close();
			break;
        case 2:
            cout<<"Enter value to be inserted: ";
            cin>>item;
            root=t.insert(root, item, opfile);           
			str="Preorder Traversal for the new Tree after Insertion:";
            t.write2TerminalandFile(str, opfile);
            t.preorder(root,opfile);//Traversal to show new tree after insertion
            cout<<endl;
            opfile<<endl;
            break;
        case 3:
        	if(root==NULL)
        	{
        		//When no nodes exist in the tree
        		str="Node cannot be deleted. Empty Tree";
            	t.write2TerminalandFile(str, opfile);
        		break;
        	}
			cout<<"Enter value to be deleted: ";
        	cin>>item;
        	root=t.delete_node(root,item,opfile);
        	str="Preorder Traversal for the new Tree after Deletion:";
            t.write2TerminalandFile(str, opfile);
            t.preorder(root,opfile);
            cout<<endl;
            opfile<<endl;
            break;
        case 4:
        	if(root==NULL)
        	{
        	//If tree is empty then element search cannot be done
			t.emptyTree(root,opfile);
			break;
			}
			cout<<"Enter value to be searched: ";
        	cin>>item;
        	t.search(root,item,opfile);
			break;
        case 5:
        	if(root==NULL)
        	{
        	//Check if tree is empty
        	t.emptyTree(root,opfile);
        	break;
        	}
			t.delete_tree(root);
			str="Tree deleted \n";
            t.write2TerminalandFile(str, opfile);
			root=NULL;
        	break;
        case 6:
        	if(root==NULL)
        	{
			t.emptyTree(root,opfile);
        	break;
        	}
			int trav_choice;
        	cout<<"Enter the preferred type of traversal: \n";
        	cout<<"1.Preorder"<<endl;
        	cout<<"2.Postorder"<<endl;
    	    cout<<"3.Inorder"<<endl;
			cin>>trav_choice;
        	if(trav_choice==1)
       		{
       			str="Preorder Traversal: ";
       			t.write2TerminalandFile(str, opfile);
           		t.preorder(root, opfile);
			}
			else if(trav_choice==2)
			{
				str="Postorder Traversal: ";
				t.write2TerminalandFile(str, opfile);
            	t.postorder(root,opfile);    
			}
			else
			{
				str="Inorder Traversal: ";
				t.write2TerminalandFile(str, opfile);
            	t.inorder(root,opfile);
            	
        	}
        	cout<<endl;
			opfile<<endl;	
            break;
        case 7:
        	if(root==NULL)
        	{
        	//check for empty tree
        	t.emptyTree(root,opfile);
        	break;
        	}
        	int bf;
			bf=t.check_balance(root);
			str="The Balance factor for the tree is";
			t.write2TerminalandFile(str, opfile);
        	cout<<bf<<endl;
        	opfile<<bf<<endl;
        	break;
        case 8:	
            exit(1);    
            break;
        default:
        	str="Wrong Choice";
        	t.write2TerminalandFile(str, opfile);
            cout<<endl;
            opfile<<endl;
        }
    }while(choice!=0);
    opfile.close();
    return 0;
}

//Checks height of the tree or a single node
int Tree::height(node *n)
{
    int h=0;//Height h initialised to 0 for a node which is null
    if (n!=NULL)
    {
        int max_height=max(height(n->left), height(n->right));//Checking the maximum between left and right subtree
        h=max_height+1;
    }
    return h;
}

//Checking the balance factor
int Tree::check_balance(node *n)
{
    int lh=height(n->left);//Height of left subtree
    int rh=height(n->right);//Height of right subtree
    return (lh-rh);//difference between left and right subtree heights
}
 
//If the balance factor is not between -1 and +1 this function is executed
node *Tree::balance(node *n)
{
    int balance=check_balance (n);
    if (balance> 1)
    {
    	//Checking if tree is left heavy
        if (check_balance (n->left) > 0)  //Checking if left subtree is left or right heavy
            n=left_rotate (n);
        else
            n=lr_rotate (n);//left right rotation executed
    }
    else if (balance< -1)
    {
    	//Checking if tree is right heavy
        if (check_balance (n->right) > 0)   //Checking if right subtree is left or right heavy
            n=rl_rotate (n);
        else
            n=right_rotate (n);//right left rotation
    }
    return n;
}

//Left left rotation
node *Tree::left_rotate(node *n)
{
    node *temp;//temp variable for rotation
    temp=n->left;
    n->left=temp->right;
    temp->right=n;
    return temp;
}

//Right right rotation
node *Tree::right_rotate(node *n)
{
    node *temp;
    temp=n->right;
    n->right=temp->left;
    temp->left=n;
    return temp;
}

//Left right rotation 
node *Tree::lr_rotate(node *n)
{
    node *temp;
    temp=n->left;
    n->left=right_rotate (temp);
    return left_rotate (n);
}
 
//Right left rotation
node *Tree::rl_rotate(node *n)
{
    node *temp;
    temp=n->right;
    n->right=left_rotate (temp);
    return right_rotate (n);
}
 
//Insertion of node in AVL Tree 
node *Tree::insert(node *root, int v, ofstream& outfile)
{
    if (root==NULL)
    {
    	//If the tree is empty and new node is inserted
        root=new node;
        root->value=v;
        root->left=NULL;
        root->right=NULL;
        return root;
    }
    else if (v<root->value)
    {
    	//If new value to be inserted is less than the existing node move to left subtree
        root->left=insert(root->left, v, outfile);
        root=balance(root);
    }
    else if (v>root->value)
    {
    	//If new value to be inserted is greater than the existing node move to right subtree
        root->right=insert(root->right, v, outfile);
        root=balance(root);
    }
	else
	{
		//When the node to be inserted has same value as an existing node
		cout<<"A node with value "<<v<<" already exists"<<endl;
		outfile<<"A node with value "<<v<<" already exists"<<endl;
	}
    return root;
}

//Deletion of node from AVL Tree
node *Tree::delete_node(node *root, int v, ofstream& outfile)
{
	if(root==NULL)
	{
		//For node not existing in the tree
		cout<<"Node "<<v<<" not found. Deletion cannot be performed. \n";
		outfile<<"Node "<<v<<" not found. Deletion cannot be performed. \n";
		return root;
 	}
 	if(v<root->value)
 	{
 		//If value to be deleted is less than existing node move to left subtree
 		root->left=delete_node(root->left, v,outfile);
 	}
 	else if(v>root->value)
 	{
 		//If value to be deleted is greater than existing node move to right subtree
 		root->right=delete_node(root->right, v,outfile);

 	}
 	else
 	{
 		//Checking for one or no child of a node
 		if((root->left==NULL) || (root->right==NULL))
 		{
 			node* temp = root->left? root->left : root->right;
 			if(temp==NULL)
 			{
 				//Leaf Node
 				temp=root;
 				root=NULL;
 			}
 			else
 			{
 				//One child
 				*root=*temp;
 			}
 			delete temp;
 			
 		}
 		else
 		{
 			//Two children case
 			node* temp2=inorderpredecessor(root);
 			root->value=temp2->value;//Copy the value of the predecessor to that particular node
 			root->left=delete_node(root->left, temp2->value, outfile);
 		}
 	}
 	if(root==NULL)
 	{
 		//If tree has only one node
 		return root;
 	}
 	root=balance(root);//re-balancing
 	return root;
}

//Finding the largest node in the left subtree
node *Tree::inorderpredecessor(node *n)
{
	node* temp = n->left;//Control exists at the left subtree
	while(temp->right!=NULL)//Traverse the right sub-tree of the left sub-tree
	{
		temp=temp->right;
	}
	return temp;
}

//Searching for a node in AVL Tree
void Tree::search(node *n,int v, ofstream& outfile)
{
	if(n==NULL)
	{
		//When node doesn't exist in the tree
		cout<<"Node "<<v<<" not found.\n"<<endl;
		outfile<<"Node "<<v<<" not found.\n"<<endl;
		return;
	}
	if(v==n->value)
	{
		int h=height(n);//When node is found, height is calculated
		cout<<"Node "<<v<<" found in tree with a height of "<<h<<".\n"<<endl;
		outfile<<"Node "<<v<<" found in tree with a height of "<<h<<".\n"<<endl;
		return;
	}
	else if(v<n->value)
	{
		//Search the left subtree for values less than current node
		return search(n->left,v,outfile);
	}
	else
	{
		//Search the right subtree for values greater than current node
		return search(n->right,v,outfile);
	}
}

//Deleting the entire AVL Tree
void Tree::delete_tree(node *n)
{
	if(n==NULL)
	return;
	delete_tree(n->left);
	delete_tree(n->right);
	delete n;
}

//Inorder Traversal
void Tree::inorder(node *tree, ofstream& outfile)
{
    if (tree==NULL)
        return;
    inorder (tree->left,outfile);
    cout<<tree->value<<"  ";
    outfile<<tree->value<<" ";
    inorder (tree->right,outfile);
}

//Preorder Traversal
void Tree::preorder(node *tree, ofstream& outfile)
{
    if (tree==NULL)
        return;
    cout<<tree->value<<"  ";
    outfile<<tree->value<<" ";
    preorder (tree->left, outfile);
    preorder (tree->right, outfile);
}
 
//Postorder Traversal
void Tree::postorder(node *tree, ofstream& outfile)
{
    if (tree==NULL)
        return;
    postorder ( tree ->left, outfile );
    postorder ( tree ->right, outfile );
    cout<<tree->value<<"  ";
    outfile<<tree->value<<" ";
}

//Checks for empty tree
void Tree::emptyTree(node *n, ofstream& outfile)
{
	if(n==NULL)
	{
		string str;
		str="Empty Tree";
		Tree t;
		t.write2TerminalandFile(str, outfile);
	}
}

//Function to write output to both output file and terminal
void Tree::write2TerminalandFile(string str, ofstream& outfile)
{
	cout<<str<<endl;
	outfile<<str<<endl;
}

