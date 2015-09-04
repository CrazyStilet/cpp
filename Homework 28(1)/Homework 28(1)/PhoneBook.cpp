#include<iostream>
#include<io.h>
//#include<stdlib.h>
using namespace std;

#define MAX_NAME_LEN 32			// ������������ ����� ����� ��������
#define PATH_OF_BASE "Base.dat"	// ���� � ����� � �����

struct PhoneBook {
	char Name[MAX_NAME_LEN];	// ��� ��������
	int Number;		// ����� ��������

	PhoneBook*left, *right, *parent;
};

class Tree {
	PhoneBook*root;
public:
	Tree();
	~Tree();
	void AddMenu();
	void Add(PhoneBook*pb);
	void PrintMenu();
	void Print(PhoneBook*Node);
	void DelMenu();
	void Del(PhoneBook*pb = 0);
	PhoneBook*Next(PhoneBook*Node);
	PhoneBook*Min(PhoneBook*Node);
	PhoneBook*GetRoot();
	void SearchMenu();
	PhoneBook*Search(PhoneBook*Node, char*Name);
	//PhoneBook*Search(PhoneBook*Node, int Number);
	void Save();
	void FileWrite();
	void FileWrite(PhoneBook*Node);
	void FileAdd();
	void Read();
};

Tree t;

Tree::Tree() {
	root = NULL;
}
Tree::~Tree() {
	Del();
}
void Tree::AddMenu() {
	PhoneBook*newPhoneBook = new PhoneBook;
	cin.ignore(10, '\n');
	cout << "������� ��� ��������: ";
	cin >> newPhoneBook->Name;
	cout << "������� ����� ��������: ";
	cin >> newPhoneBook->Number;
	Add(newPhoneBook);
}
void Tree::Add(PhoneBook*pb) {
	pb->left = NULL;
	pb->right = NULL;

	PhoneBook*y = NULL;
	PhoneBook*Node = root;

	while(Node != 0) {
		y = Node;
		if(strcmp(pb->Name, Node->Name) < 0) {
			Node = Node->left;
		}
		else {
			Node = Node->right;
		}
	}
	pb->parent = y;

	if(y == 0) {
		root = pb;
	}
	else if(strcmp(pb->Name, y->Name) < 0) {
		y->left = pb;
	}
	else {
		y->right = pb;
	}
}
void Tree::PrintMenu() {
	char answerPrint;
	cout << "\na ��� 1 - ��� ������ �������� ��� ���� ���������"
		"\nn ��� 2 - �� ��������!!! ��� ������ �������� �� ��������� ����"
		"\nt ��� 3 - �� ��������!!! ��� ������ �������� �� ��������� �������"
		"\nx ��� 8 - ��������� �����"
		"\n��� �����: ";
	cin >> answerPrint;
	switch(answerPrint) {
	case 'a':
	case '1':
		cout << "\n����� �������� ��� ���� ���������\n";
		t.Print(GetRoot());
		break;
	case 'n':
	case '2':
		cout << "\n����� �������� �� ������\n";

		break;
	case 't':
	case '3':
		cout << "\n����� �������� �� �������\n";

		break;
	case 'x':
	case '8':
		cout << "\n�����\n";
		break;
	default:
		break;
	}
}
void Tree::Print(PhoneBook*Node) {
	if(Node != 0) {
		Print(Node->left);
		cout << Node->Name
			<< " - "
			<< Node->Number
			<< endl;
		Print(Node->right);
	}
}
void Tree::DelMenu() {
	char answerDel;
	cout << "\na ��� 1 - ��� �������� ���� ���������"
		"\nn ��� 2 - �� ��������!!! ��� �������� �������� �� �����"
		"\nt ��� 3 - �� ��������!!! ��� �������� �������� �� ��������"
		"\nx ��� 8 - ��������� �����"
		"\n��� �����: ";
	cin >> answerDel;
	switch(answerDel) {
	case 'a':
	case '1':
		cout << "\n�������� ���� ���������\n";
		// �������� ������� Del � ���������� �� ��������� 0
		t.Del();
		break;
	case 'n':
	case '2':
		cout << "\n�������� �������� �� �����\n";

		break;
	case 't':
	case '3':
		cout << "\n�������� �������� �� ��������\n";

		break;
	case 'x':
	case '8':
		cout << "\n�����\n";
		break;
	default:
		cout << "\n����������� �������\n";
		break;
	}
}
void Tree::Del(PhoneBook*pb) {
	if(pb != 0) {
		PhoneBook*Node, *y;

		if(pb->left == 0 || pb->right == 0) {
			y = pb;
		}
		else
			y = Next(pb);

		if(y->left != 0) {
			Node = y->left;
		}
		else {
			Node = y->right;
		}

		if(Node != 0) {
			Node->parent = y->parent;
		}
		if(y->parent == 0) {
			root = Node;
		}
		else if(y == y->parent->left) {
			y->parent->left = Node;
		}
		else {
			y->parent->right = Node;
		}

		if(y != pb) {
			strcpy(pb->Name, y->Name);
			pb->Number = y->Number;
		}

		delete y;
	}
	else {	// �������� ����� ������
		while(root != 0) {
			Del(root);
		}
	}
}
PhoneBook*Tree::Next(PhoneBook*Node) {
	PhoneBook*y = 0;
	if(Node != 0) {
		if(Node->right != 0) {
			return Min(Node->right);
		}
		while(y != 0 && Node == y->right) {
			Node = y;
		}
	}
}
PhoneBook*Tree::Min(PhoneBook*Node) {
	if(Node != 0) {
		while(Node->left != 0) {
			Node = Node->left;
		}
	}
	return Node;
}
PhoneBook*Tree::GetRoot() {
	return root;
}
void Tree::SearchMenu() {
	char answerSearch;
	cout << "\nn ��� 1 - ����� �������� �� �����"
		"\nt ��� 2 - ����� �������� �� ������"
		"\nx ��� 8 - �����"
		"\n��� �����:";
	cin >> answerSearch;
	switch(answerSearch) {
	case 'n':
	case '1':
		cout << "\n����� �������� �� �����\n";
		char NameSearch[MAX_NAME_LEN];
		cout << "\n������� ��� ��������\n";
		//cin >> NameSearch;
		// ������-�� �� ���������� ������ ������, � ������ ���� ������
		cin.getline(NameSearch, MAX_NAME_LEN);
		Search(GetRoot(), NameSearch);
		break;
	case 't':
	case '2':
		cout << "\n����� �������� �� ��������\n";

		break;
	case 'x':
	case '8':
		cout << "\n�����\n";
		break;
	default:
		cout << "\n����������� �������\n";
		break;
	}
}
PhoneBook*Tree::Search(PhoneBook*Node, char*Name) {
	while(Node != 0 && strcmp(Name, Node->Name) != 0) {
		if(strcmp(Name, Node->Name) < 0) {
			Node = Node->left;
		}
		else {
			Node = Node->right;
		}
	}
	return Node;
}
void Tree::Save() {
	//char source[_MAX_PATH];
	char answerSave;

	/*cout << "\n������� ���� � �������� ����� � �����:\n";
	cin.getline(PATH_OF_BASE, _MAX_PATH);*/

	if(_access(PATH_OF_BASE, 00) == 0) {
		cout << "\n����� ���� ��� ����������!"
			"\nw ��� 1 - ������������ ����"
			//"\na ��� 2 - �������� � ����"
			"\nx ��� 8 - �����"
			"\n��� �����:";
		cin >> answerSave;
		switch(answerSave) {
		case 'w':
		case '1':
			FileWrite();
			cout << "\n���� �����������\n";
			break;
		/*case 'a':
		case '2':
			cout << "\n���������� ����� �������� � ����\n";
			FileAdd();
			break;*/
		case 'x':
		case '8':
			cout << "\n�����\n";
			break;
		default:
			break;
		}
		//cin.getline(answerSave, 2);
		//if(!strcmp(answerSave,"2")||(!strcmp(answerSave,"y"))) {
		//	cout << "\n�������� � ������������ ���� (y ��� 1 - ��/ n ��� 2 - ���)?\n";
		//	cin >> answerSave2;
		//	//cin.getline(answerSave2, 2);
		//	if(strcmp(answerSave2,"1")||strcmp(answerSave2,"y")) {
		//		cout << "\n������\n";
		//	}
		//	else if(strcmp(answerSave,"1")||strcmp(answerSave,"y")) {
		//		cout << "\n������������ ����\n";
		//	}
		//	else if(!strcmp(answerSave,"1")||(!strcmp(answerSave,"y"))) {
		//		cout << "\n���� ������\n";
		//		FILE*f = fopen(PATH_OF_BASE, "w");
		//		fclose(f);
		//	}
		//	if(_access(PATH_OF_BASE, 02) == -1) {
		//		cout << "\n��� ������� � ������\n";
		//	}
		//}
	}
	else {
		cout << "\n������ �������� � ����\n";
		FileWrite();
	}

	/*FILE*f = fopen(PATH_OF_BASE, "a");
	if(!f) {
		exit(0);
	}

	fwrite(GetRoot(), sizeof(PhoneBook), 1, f);
	fclose(f);*/
}
void Tree::FileWrite() {
	FILE*f = fopen(PATH_OF_BASE, "w+");
	if(!f) {
		exit(0);
	}
	PhoneBook*Node = GetRoot();
	FileWrite(Node);
	fclose(f);
}
void Tree::FileWrite(PhoneBook*Node) {
	FILE*f = fopen(PATH_OF_BASE, "a+");
	if(!f) {
		exit(0);
	}
	if(Node != 0) {
		FileWrite(Node->left);
		fwrite(Node, sizeof(PhoneBook), 1, f);
		FileWrite(Node->right);
	}
	fclose(f);
}
void Tree::FileAdd() {
	FILE*f = fopen(PATH_OF_BASE, "a");
	fclose(f);
}
void Tree::Read() {
	FILE*f = fopen(PATH_OF_BASE, "r+");
	if(f == 0) {
		cout << "\n���� ������� �� ����������\n";
		return;
	}
	if(_access(PATH_OF_BASE, 00) == -1) {
		cout << "\n�� ���������� �������� ������ � �����\n";
		return;
	}
	// ������� ������� ������ ���������
	// �� ��������� ���������� ������� Del � ���������� 0
	Del();
	PhoneBook*newPhoneBook = new PhoneBook;
	while(fread(newPhoneBook, sizeof(PhoneBook), 1, f)) {
		Add(newPhoneBook);
	}
	fclose(f);
}
int main() {
	setlocale(0, "rus");

	char answerMain;
	while(true) {
		cout << "\na ��� 1 - ���������� ������ ��������"
			"\nd ��� 2 - �������� ���������"
			"\nm ��� 3 - �� ��������!!! ��������� ������ ��������"
			"\nf ��� 4 - �� ��������!!! ����� �������� �� ������ ��� �����"
			"\np ��� 5 - ������� �������� � ���� ���������"
			"\nw ��� 6 - �������� ��� ������ � ����"
			"\nr ��� 7 - �� ��������!!! ��������� ��� ������ �� �����"
			"\nx ��� 8 - �����"
			"\n��� �����: ";
		cin >> answerMain;
		switch(answerMain) {
		case 'a':
		case '1':
			cout << "\n���������� ��������\n";
			t.AddMenu();
			break;
		case 'd':
		case '2':
			cout << "\n�������� ���������\n";
			t.DelMenu();
			break;
		case 'm':
		case '3':
			cout << "\n��������� ������ ��������\n";

			break;
		case 'f':
		case '4':
			cout << "\n����� �������� �� ������ ��� �����\n";
			t.SearchMenu();
			break;
		case 'p':
		case '5':
			cout << "\n����� ��������\n";
			t.PrintMenu();
			break;
		case 'w':
		case '6':
			cout << "\n������ ������\n";
			t.Save();
			break;
		case 'r':
		case '7':
			cout << "\n������ ������\n";
			t.Read();
			break;
		case 'x':
		case '8':
			cout << "\n�����\n";
			exit(0);
			break;
		default:
			cout << "\n����������� �������\n";
			break;
		}
	}
	return 0;
}