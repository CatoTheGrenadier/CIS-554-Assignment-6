//HW6.  Due: Monday, Nov. 27 at 11:59pm

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>
#include <functional>

using namespace std;


class node {
public:
	int value;
	node* next;
	node(int i) { value = i; next = nullptr; }//construct
	node() { next = nullptr; }//default constructor

};

class LinkedList {
public:
	node* head;
	LinkedList(int n, int m);//Constructor for an n-node linked list
	//with values randomly in 0 ... m-1


	LinkedList() { head = nullptr; } //default constructor

	void Sort();
	void Sort(function<bool(int, int)> key_method);//You need to change this to allow the Sort examples in the main functions.
	//You can re-use code from lecture 2023_09_07 .

};




//When sorting structures, always sort the sums of all numbers within the structure.
//when comparing equality of two structures, always compare sums of all int values in the structures
//When Hashing a structure, always hash the sum of all int values in the structure
//For printing, following the following natations.  map: { ...}   set(or unordered set): <...>  

LinkedList::LinkedList(int n, int m) {
	node* next_node{ head };
	for (int i = 1; i < n; i++) {
		next_node->next = new node{rand() % m};
		next_node = next_node->next;
	}
}


void LinkedList::Sort() {
	if (!head || !head->next) {
		return;
	}
	node* p1{ head };
	while (p1->next) {
		int min_value{ p1->value };
		node* p2 = p1->next;
		node* pmin{ p1 };
		while (p2) {
			if (p2->value < min_value) {
				min_value = p2->value;
				pmin = p2;
			}
			p2 = p2->next;
		}
		pmin->value = p1->value;
		p1->value = min_value;
		p1 = p1->next;
	}
	return;
}

void LinkedList::Sort(function<bool(int,int)> key_method) {
	if (!head || !head->next) {
		return;
	}
	node* p1{ head };
	while (p1->next) {
		int min_value{ p1->value };
		node* p2 = p1->next;
		node* pmin{ p1 };
		while (p2) {
			if (key_method(p2->value,min_value)) {
				min_value = p2->value;
				pmin = p2;
			}
			p2 = p2->next;
		}
		pmin->value = p1->value;
		p1->value = min_value;
		p1 = p1->next;
	}
	return;
}

ostream& operator<<(ostream& str, const set<map < map <int*, string >*, set <int>*>> c) {
	str << "<" << "\n";
	for (const auto& i : c) { // set
		str << "{" << "\n";
		for (const auto& j : i) { // map < map <int*, string >*, set <int>*>
			str << "{" << " ";
			for (const auto& k : *(j.first)) {
				str << *(k.first) << " " << k.second << " ";
			}
			str << "}" << " " << "<" << " ";
			for (const auto& l : *(j.second)) {
				str << l << " ";
			}
			str << ">" << " ";
		}
		str << "\n" << "}" << "\n";
	}
}




int main() {
	//The following statement won't compile. Fix it. 
	//Set initial values for S1.  Every structure, set or map, needs to have at least 3 elements.

	set<map < map <int*, string >*, set <int>*>> S1;
	map<map<int*, string >*, set<int>*>* new_map_1;
	int count{ 9 };

	for (int i = 0; i < 3; i++) {
		new_map_1 = new map < map <int*, string >*, set <int>*>;
		map <int*, string >* new_map_2;
		set <int>* new_set;
		for (int j = 0; j < 3; j++) {
			new_map_2 = new map <int*, string >;
			new_set = new set <int>;
			(*(new_map_1))[new_map_2] = new_set;
		}
		S1.insert(*new_map_1);
	}



	//You need to support the following statement.
	cout << S1 << endl;


	//The following statement won't compile. Fix it.
	//Set initial values for H1.  Every structure, set or map, needs to have at least 3 elements.
	unordered_set<map < map <int*, string >*, set <int>*  >> H1;

	//You need to support the following statement.
	cout << H1 << endl; //Print bucket.  See sample screenshots.



	LinkedList L1{ 20, 10 };
	cout << L1 << endl;
	L1.Sort();
	cout << L1 << endl;

	L1.Sort([](int a, int b) { return a % 3 < b % 3; });
	cout << L1 << endl;
	L1.Sort(greater<int>{});
	cout << L1 << endl;


	return 0;
}    