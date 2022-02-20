
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

#define FILENAME "setC.txt"
#define SET_SIZE 5000000

using namespace std;

struct node // node declaration
{
	string d;
	struct node *l;
	struct node *r;
	int height;
};

class avl
{
public:
	struct node *root;

	node *rightrotate(node *p)
	{
		node *temp = p->l;
		p->l = temp->r;
		temp->r = p;

		p->height = max(height(p->l), height(p->r)) + 1;
		temp->height = max(height(temp->l), height(temp->r)) + 1;

		return temp;
	}

	node *leftrotate(node *p)
	{
		node *temp = p->r;
		p->r = temp->l;
		temp->l = p;

		p->height = max(height(p->l), height(p->r)) + 1;
		temp->height = max(height(temp->l), height(temp->r)) + 1;

		return temp;
	}

	int height(node *p)
	{
		if (p == NULL)
			return 0;
		return p->height;
	}

	int balance_factor(node *p)
	{
		if (p == NULL)
			return 0;
		return (height(p->l) - height(p->r));
	}

	node *insert(node *r, string str)
	{
		// recursively call the insert function – refer to algorithm
		if (r == NULL)
		{
			r = new node;
			r->d = str;
			r->l = NULL;
			r->r = NULL;
			r->height = 1;
			return r;
		}
		else if (str.compare(r->d) < 0)
			r->l = insert(r->l, str);
		else if (str.compare(r->d) >= 0)
			r->r = insert(r->r, str);
		r->height = 1 + max(height(r->l), height(r->r));
		int balance = balance_factor(r);

		// If this node becomes unbalanced, then
		// there are 4 cases

		// Left Left Case
		if (balance > 1 && str.compare(r->l->d) < 0)
			return rightrotate(r);

		// Right Right Case
		if (balance < -1 && str.compare(r->r->d) >= 0)
			return leftrotate(r);

		// Left Right Case
		if (balance > 1 && str.compare(r->l->d) >= 0)
		{
			r->l = leftrotate(r->l);
			return rightrotate(r);
		}

		// Right Left Case
		if (balance < -1 && str.compare(r->r->d) < 0)
		{
			r->r = rightrotate(r->r);
			return leftrotate(r);
		}

		/* return the (unchanged) node pointer */
		return r;
	}

	void search(node *p, int lvl, string str)
	{
		if (p == NULL)
		{
			cout << "Value not found\n";
			return;
		}
		if (root->d == str)
			cout << "Value found at root\n";
		else if (p->d <= str)
		{
			if (p->r != NULL && p->r->d == str)
				cout << "Value found at " << lvl << "R\n";
			else
				search(p->r, lvl + 1, str);
		}
		else if (p->d > str)
		{
			if (p->l != NULL && p->l->d == str)
				cout << "Value found at " << lvl << "L\n";
			else
				search(p->l, lvl + 1, str);
		}
	}

	void show(node *p, int lvl)
	{
		int i;
		if (p != NULL)
		{
			if (p == root)
				cout << "Root: " << p->d << endl;
			else
				cout << p->d << endl;
			cout << lvl << "L: ";
			show(p->l, lvl + 1);
			cout << "\n"
				 << lvl << "R: ";
			show(p->r, lvl + 1);
		}
	}

	avl()
	{
		root = NULL;
	}
};

bool exists(string a[], string data)
{
	for (int i = 0; i < 10; i++)
	{
		if (a[i] == data)
			return true;
	}
	return false;
}

// fetch 10 random strings from file
string *generateRandomStrings()
{
	string *randoms = new string[10];
	ifstream file;
	file.open(FILENAME);
	string line;
	int i = 0;
	while (getline(file, line))
	{
		if (i == 10)
			break;
		randoms[i] = line;
		i++;
	}
	file.close();
	return randoms;
}

int main()
{

	int c;
	int x = 0;
	int counter = 0;
	string str;
	avl tree;

	ifstream file(FILENAME);

	if (!file.is_open())
	{
		cout << "Could not open file";
		return 0;
	}

	auto start = high_resolution_clock::now();
	while (getline(file, str))
	{
		file >> str;
		tree.root = tree.insert(tree.root, str);
	}
	auto end = high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	cout << "Insertion Duration: " << duration.count() << "s\n\n";

	while (1)
	{
		cout << "1.Search 10 Random Vales" << endl;
		cout << "2.Show Binary Search Tree" << endl;
		cout << "3.Exit" << endl;
		cout << "Enter your Choice: ";
		cin >> c;
		switch (c)
		{
		case 1:
			cout << "Enter value to be searched: ";
			cin >> str;
			cout << endl;

			start = high_resolution_clock::now();
			tree.search(tree.root, 1, str);
			end = high_resolution_clock::now();

			duration = end - start;
			cout << "Duration: " << duration.count() << "s\n";
			break;
		case 2:
			if (tree.root == NULL)
			{
				cout << "Tree is Empty" << endl;
				continue;
			}
			cout << "Tree:" << endl;
			tree.show(tree.root, 1);
			cout << endl;
			break;
		case 3:
			exit(1);
			file.close();
			break;
		default:
			cout << "Wrong Choice" << endl;
		}
	}
	return 0;
}
