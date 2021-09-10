#include "bits/stdc++.h"
using namespace std;

unordered_map<int, int>lineTracker;

class node {
public:
	string id, scope, type;
	int lineNumber;
	node *next;
	node()
	{
		next = NULL;
	}
	node(string key, string value, string type, int ln) {
		next = NULL;
		id = key;
		scope = value;
		this->type = type;
		lineNumber = ln;
	}
	void print()
	{
		cout << "Identifier Name:" << id << endl << "Type:" << type << endl << "Scope:" << scope << endl << "Line Number:" << lineNumber << endl;
	}
};

class symbolTable
{
public:
	node *head[1000];
	symbolTable() {
		for (int i = 0; i < 1000; i++)
		{
			head[i] = NULL;
		}
	}

	int hashFn(string id)
	{
		int asciiSum = 0;
		for (int i = 0; i < id.size(); i++) {
			asciiSum += id[i];
		}
		return asciiSum % 1000;
	}


	bool validate(string id, string scope, string type, int ln) {
		if (lineTracker.count(ln)) {
			return 0;
		}
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


	bool insert(string id, string scope, string type, int ln) {
		if (!validate(id, scope, type, ln)) {
			cout << "Can not insert! FAILURE" << endl;
			return 0;
		}
		int idx = hashFn(id);
		node *newNode = new node(id, scope, type, ln);
		if (!head[idx]) {
			lineTracker[ln] = 1;
			head[idx] = newNode;
			cout << id << " inserted" << endl;
			return 1;
		}
		else {
			lineTracker[ln] = 1;
			node *start = head[idx];
			head[idx] = newNode;
			newNode->next = start;
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
		return "-1";
	}



	bool modify(string id, string s, string t, int l)
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
				lineTracker.erase(lineTracker.find(x));
				start->scope = s;
				start->type = t;
				start->lineNumber = l;
				lineTracker[l] = 1;
				return 1;
			}
			start = start->next;
		}

		return 0;

	}


	bool deleteEntry(string id, string scope) {
		int idx = hashFn(id);
		node *par = head[idx];
		node *temp = head[idx];
		if (!temp) {
			return 0;
		}
		if (temp->id == id && temp->scope == scope && temp->next == NULL) {
			temp->next = NULL;
			int x = temp->lineNumber;
			lineTracker.erase(lineTracker.find(x));
			delete temp;
			return 1;
		}
		while ((temp->id != id && temp->scope != scope) && temp->next != NULL) {
			par = temp;
			temp = temp->next;
		}
		if (temp->id == id && temp->scope == scope && temp->next != NULL) {
			par->next = temp->next;
			temp->next = NULL;
			int x = temp->lineNumber;
			lineTracker.erase(lineTracker.find(x));
			delete temp;
			return 1;
		}
		else if (temp->id == id && temp->scope == scope) {
			par->next = NULL;
			temp->next = NULL;
			int x = temp->lineNumber;
			lineTracker.erase(lineTracker.find(x));
			delete temp;
			return 1;
		}
		return 0;

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
			string id, scope, type;
			int ln ;
			cin >> id >> scope >> type >> ln;
			st.insert(id, scope, type, ln);
			cout << endl;
			break;
		}
		case 2: {
			string id, scope, type;
			int ln ;
			cin >> id >> scope >> type >> ln;
			st.modify(id, scope, type, ln);
			cout << "Modified Successfully" << endl;
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
