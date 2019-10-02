#include <iostream>
#include <iomanip>
using namespace std;

struct tree
{
	int inf;
	int value;
	tree* left = NULL, * right = NULL;
};

tree* init(int inf)
{
	tree* new_root = new tree;
	new_root->inf = inf;
	new_root->left = NULL;
	new_root->right = NULL;
	return new_root;
}
void addmas(tree**& mas, tree* t, int& size)
{
	tree** tmp = mas;
	int count = 0;
	tree** tmpp = new tree * [size + 1];
	for (int i = 0; i < size; i++)
		tmpp[i] = mas[i];
	tmpp[size] = t;
	//cout << t->inf << "  ";
	//cout << (*(tmpp+size))->inf << "  ";
	//for (int i = 0; i < size; i++)
		//delete mas[i];
	//tmpp[count - 1] = NULL;
	mas = tmpp;
	size++;
}
void viewmas(tree * *mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << mas[i]->inf << "  ";
	}
	cout << endl;
}
void Add_List(tree * root, int key)
{
	tree* prev = NULL, * t;
	bool find = true;
	t = root;
	while (t && find)
	{
		prev = t;
		if (key == t->inf)
		{
			find = false;
			cout << "find" << endl;
		}
		else
			if (key < t->inf) t = t->left;
			else   t = t->right;
	}
	if (find)
	{
		t = init(key);
		if (key < prev->inf)
			prev->left = t;
		else
			prev->right = t;
	}
}
void View_TreeMax(tree * p, int level, int& count_level)
{
	if (p)
	{
		if (p->left == NULL && p->right == NULL && count_level < level)
		{
			count_level = level;
		}
		View_TreeMax(p->right, level + 1, count_level);
		for (int i = 0; i < level; i++)
			cout << "  ";

		cout << setw(2) << p->inf << endl;
		View_TreeMax(p->left, level + 1, count_level);
	}
}/*
void View_TreeMin(tree *p, int& level)
{
	if (p)
	{
		View_TreeMax(p->left, level + 1);
		for (int i = 0; i < level; i++)
			cout << "  ";
		cout << setw(2) << p->inf << endl;
		View_TreeMax(p->right, level + 1);
	}
}*/
tree* Del_Info(tree * root, int key)
{
	tree* Del, * Prev_Del, * R, * Prev_R;
	Del = root;
	Prev_Del = NULL;
	while (Del != NULL && Del->inf != key)
	{
		Prev_Del = Del;
		if (Del->inf > key)
			Del = Del->left;
		else
			Del = Del->right;
	}
	if (Del == NULL)
	{
		cout << "net takogo key" << endl;
		return root;
	}
	if (Del->right == NULL)
		R = Del->left;
	else
		if (Del->left == NULL)
			R = Del->right;
		else
		{
			Prev_R = Del;
			R = Del->left;
			while (R->right != NULL)
			{
				Prev_R = R;
				R = R->right;
			}
			if (Prev_R == Del)
				R->right = Del->right;
			else
			{
				R->right = Del->right;
				Prev_R->right = R->left;
				R->left = Prev_R;
			}
		}
	if (Del == root)
		root = R;
	else
		if (Del->inf < Prev_Del->inf)
			Prev_Del->left = R;
		else
			Prev_Del->right = R;
	delete Del;
	return root;
}
void Make_Blns(tree * *p, int n, int k, tree * *a)
{
	if (n == k)
	{
		*p = NULL;
		return;
	}
	else
	{
		int m = (n + k) / 2;
		*p = new tree;
		(*p)->inf = (*(a + m))->inf;
		Make_Blns(&(*p)->left, n, m, a);
		Make_Blns(&(*p)->right, m + 1, k, a);
	}
}
void Del_Tree(tree * t)
{
	if (t != NULL)
	{
		Del_Tree(t->left);
		Del_Tree(t->right);
		delete t;
	}
}
void createMass(tree * p, tree * *&mas, int& size)
{
	if (p)
	{
		createMass(p->right, mas, size);
		addmas(mas, p, size);
		createMass(p->left, mas, size);
	}
}
void sortmas(tree * *mas, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		int imin = i;
		for (int j = i + 1; j < size; j++)
		{
			if (mas[j]->inf < mas[imin]->inf)
				imin = j;
		}
		tree* tmp = mas[imin];
		mas[imin] = mas[i];
		mas[i] = tmp;
	}
}
void Search_List(tree * root, int key)
{
	tree* prev = NULL, * t;
	t = root;
	while (t)
	{
		prev = t;
		if (key == t->inf)
		{
			cout << t->inf << endl;
			return;
		}
		else
			if (key < t->inf) t = t->left;
			else   t = t->right;
	}
	cout << "not found" << endl;
}
void List_count(tree * p, int level, int* mas, int count_level)
{

	if (p)
	{

		List_count(p->right, level + 1, mas, count_level);
		if (p->right == NULL && p->left == NULL)
		{
			mas[level] += 1;
			//count_level = level;
		}
		List_count(p->left, level + 1, mas, count_level);
	}
}
int main()
{
	tree* root = init(rand() % 1);
	for (int i = 0; i < 10; i++)
	{
		Add_List(root, rand() % 100 - 50);
	}
	tree** m = new tree * [1];
	m = NULL;
	int size = 0;
	createMass(root, m, size);
	viewmas(m, size);
	sortmas(m, size);
	viewmas(m, size);
	int level = 0;
	int count_level = 0;
	View_TreeMax(root, level, count_level);
	int* mas = new int[count_level + 1];
	for (int i = 0; i < count_level + 1; i++)
	{
		mas[i] = 0;
	}
	List_count(root, 0, mas, count_level); //количество листьев на уровне
	for (int i = 0; i < count_level + 1; i++)
	{
		cout << i << ")" << mas[i] << " elements" << endl;
	}

	Make_Blns(&root, 0, size, m);
	View_TreeMax(root, level, count_level);
	system("pause");
	return 0;
}
