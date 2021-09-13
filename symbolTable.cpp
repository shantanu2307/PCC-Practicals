#include "bits/stdc++.h"
using namespace std;

int hashFn(string id)
{
	int asciiSum = 0;
	for (int i = 0; i < id.size(); i++) {
		asciiSum += (id[i] * id[i] + 1000) % 1000;
	}
	return (asciiSum + 1000) % 1000;
}


class node {
public:
	string id, scope, type, value;
	int lineNumber;
	node *next, *prev;
	node()
	{
		next = NULL;
		prev = NULL;
	}
	node(string key, string scope, string type, string value, int ln) {
		next = NULL;
		prev = NULL;
		id = key;
		this->scope = scope;
		this->type = type;
		this->value = value;
		lineNumber = ln;
	}
	void print()
	{
		cout << "Identifier Name:" << id << endl << "Value:" << value << endl << "Type:" << type << endl << "Scope:" << scope << endl << "Line Number:" << lineNumber << endl;
	}
};

class symbolTable
{

private:
	int pow(int y) {
		if (y & 1) {
			return -1;
		}
		return 1;
	}

public:
	node *head[1000];
	symbolTable() {
		for (int i = 0; i < 1000; i++)
		{
			head[i] = NULL;
		}
	}


	bool validate(string id, string scope, string type, int ln) {
		int idx = hashFn(id);
		node *start = head[idx];
		while (start)
		{
			if (start->id == id && start->scope == scope) {
				return 0;
			}
			start = start->next;
		}
		return 1;
	}


	bool insert(string id, string scope, string type, string value, int ln) {
		if (!validate(id, scope, type, ln)) {
			cout << "Can not insert! FAILURE" << endl;
			return 0;
		}
		int idx = hashFn(id);
		node *newNode = new node(id, scope, type, value, ln);
		if (!head[idx]) {
			head[idx] = newNode;
			cout << id << " inserted" << endl;
			return 1;
		}
		else {
			node *start = head[idx];
			head[idx] = newNode;
			newNode->next = start;
			start->prev = newNode;
			cout << id << " inserted" << endl;
			return 1;
		}
		return 0;
	}

	string find(string id, string scope)
	{
		int idx = hashFn(id);
		node *start = head[idx];
		if (!start) {
			cout << "Identifier doesn't exist" << endl;
			return "-1";
		}
		while (start != NULL) {
			if (start->id == id && start->scope == scope)
			{
				start->print();
				return start->scope;
			}
			start = start->next;
		}
		cout << "Identifier doesn't exist" << endl;
		return "-1";
	}



	bool modify(string id, string s, string t, string v, int l)
	{
		int indexValue = hashFn(id);
		node* start = head[indexValue];
		if (start == NULL) {
			cout << "No Entry Exists" << endl;
			return 0;
		}
		while (start != NULL) {
			if (start->id == id) {
				int x = start->lineNumber;
				start->scope = s;
				start->type = t;
				start->lineNumber = l;
				start->value = v;
				return 1;
			}
			start = start->next;
		}

		return 0;

	}


	bool deleteEntry(string id, string scope) {
		int idx = hashFn(id);
		node *temp = head[idx];
		while (temp != NULL)
		{
			if (temp->id == id && temp->scope == scope)
				break;
			temp = temp->next;
		}
		node *par;
		if (temp == NULL)
			return 0;
		if (temp == head[idx])
		{
			head[idx] = temp->next;
			if (temp->next != NULL)
				temp->next->prev = NULL;
		}
		else
		{
			par = temp->prev;
			par->next = temp->next;
			if (temp->next != NULL)
				temp->next->prev = par;
		}
		delete temp;
		return 1;
	}


};


int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	symbolTable st;
	cout << "MENU" << endl;
	cout << "1. Insert" << endl;
	cout << "2. Modify" << endl;
	cout << "3. Find" << endl;
	cout << "4. Delete" << endl;
	cout << "5. Exit" << endl;
	cout << endl;
	while (1) {
		int opt = 0;
		cin >> opt;
		switch (opt) {
		case 1: {
			string id, scope, value = "No Value", type;
			int ln ;
			cin >> id >> scope >> type >> value >> ln;
			st.insert(id, scope, type, value, ln);
			cout << endl;
			break;
		}
		case 2: {
			string id, scope, value, type;
			int ln ;
			cin >> id >> scope >> value >> type >> ln;
			st.modify(id, scope, value, type, ln);
			cout << "Modified Successfully" << endl << endl;
			break;
		}
		case 3: {
			string id, scope;
			cin >> id >> scope;
			st.find(id, scope);
			cout << endl;
			break;
		}
		case 4: {
			string id, scope;
			cin >> id >> scope;
			bool b = st.deleteEntry(id, scope);
			if (b) {
				cout << "Deleted Successfully" << endl;
			}
			else {
				cout << "Failed to Delete" << endl;
			}
			cout << endl;
			break;
		}
		case 5: {

			cout << "Exitted Successfully" << endl;
			return 0;
		}
		default: {

			cout << "Choose another option" << endl;
		}

		}
	}

	return 0;
}
