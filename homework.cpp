//Yi Ling
//NetID : yiling
//SUID : 9254508221

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
	head = new node(rand() % m);
	node* next_node{ head };
	for (int i = 1; i < n; i++) {
		next_node->next = new node{rand() % m};
		next_node = next_node->next;
	}
}

struct custom_funtor_class_0_inside_map {
	bool operator()(const int* V1, const int* V2) const {
		return *V1 < *V2;
	}
};

struct custom_funtor_class_1_inner_map {
	bool operator()(const map <int*, string, custom_funtor_class_0_inside_map>* V1, const map <int*, string, custom_funtor_class_0_inside_map>* V2) const {
		int value_1{ 0 };
		int value_2{ 0 };
		for (const auto& k : (*V1)) {
			value_1 += *(k.first);
		}
		for (const auto& k : (*V2)) {
			value_2 += *(k.first);
		}
		return value_1 < value_2;
	}
};

struct custom_funtor_class_1_outer_map {
	bool operator()(const map < map <int*, string, custom_funtor_class_0_inside_map>*, set <int>*, custom_funtor_class_1_inner_map> V1, const map < map <int*, string, custom_funtor_class_0_inside_map>*, set <int>*, custom_funtor_class_1_inner_map> V2) const {
		int value_1{ 0 };
		int value_2{ 0 };
		for (const auto& j : V1) { // map < map <int*, string >*, set <int>*>
			for (const auto& k : *(j.first)) {
				value_1 += *(k.first);
			}
			for (const auto& l : *(j.second)) {
				value_1 += l;
			}
		}

		for (const auto& j : V2) { // map < map <int*, string >*, set <int>*>
			for (const auto& k : *(j.first)) {
				value_2 += *(k.first);
			}
			for (const auto& l : *(j.second)) {
				value_2 += l;
			}
		}
		return value_1 < value_2;
	}
};

struct custom_funtor_class_2 {
	unsigned int operator()(const map < map <int*, string, custom_funtor_class_0_inside_map >*, set <int>*, custom_funtor_class_1_inner_map>& V) const {
		int value{ 1 };
		for (const auto& j : V) { // map < map <int*, string >*, set <int>*>
			for (const auto& k : *(j.first)) {
				value += hash<int>{}(*(k.first));
				value += hash<string>{}(k.second);
			}
			for (const auto& l : *(j.second)) {
				value += hash<int>{}(l);
			}
		}
		return ( hash<int>{}(value) % 5 + 7 ) % 8;
	}

	bool operator()(const map < map <int*, string, custom_funtor_class_0_inside_map >*, set <int>*, custom_funtor_class_1_inner_map>& V1, const map < map <int*, string, custom_funtor_class_0_inside_map >*, set <int>*, custom_funtor_class_1_inner_map>& V2) const {
		int value_1{ 1 };
		for (const auto& j : V1) { // map < map <int*, string >*, set <int>*>
			for (const auto& k : *(j.first)) {
				value_1 *= hash<int>{}(*(k.first));
				value_1 *= hash<string>{}(k.second);
			}
			for (const auto& l : *(j.second)) {
				value_1 *= hash<int>{}(l);
			}
		}

		int value_2{ 1 };
		for (const auto& j : V2) { // map < map <int*, string >*, set <int>*>
			for (const auto& k : *(j.first)) {
				value_2 *= hash<int>{}(*(k.first));
				value_2 *= hash<string>{}(k.second);
			}
			for (const auto& l : *(j.second)) {
				value_2 *= hash<int>{}(l);
			}
		}
		return value_1 == value_2;
	}
};


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

ostream& operator<<(ostream& str, const set<map < map <int*, string, custom_funtor_class_0_inside_map>*, set <int>*, custom_funtor_class_1_inner_map>, custom_funtor_class_1_outer_map> c) {
	str << "<" << "\n";
	for (const auto& i : c) { // set
		str << "{" << "\n";
		for (const auto& j : i) { // map < map <int*, string >*, set <int>*>
			str << "{" << " ";
			for (const auto& k : *(j.first)) {
				str << *(k.first) << " " << k.second << " ";
			}
			str << "}" << "  " << "<" << " ";
			for (const auto& l : *(j.second)) {
				str << l << " ";
			}
			str << ">" << "  ";
		}
		str << "\n" << "}" << "\n";
	}
	str << ">" << "\n";
	return str;
}

ostream& operator<<(ostream& str, const unordered_set<map < map <int*, string, custom_funtor_class_0_inside_map>*, set <int>*, custom_funtor_class_1_inner_map>, custom_funtor_class_2, custom_funtor_class_2> d) {
	for (unsigned int cnt = 0; cnt < d.bucket_count(); cnt++) {
		str << "Bucket " << cnt << ":" << "\n";
		for (const auto& i : d) { // set
			if (custom_funtor_class_2{}(i) == cnt){
				str << "{" << "\n";
				for (const auto& j : i) { // map < map <int*, string >*, set <int>*>
					str << "{" << " ";
					for (const auto& k : *(j.first)) {
						str << *(k.first) << " " << k.second << " ";
					}
					str << "}" << "  " << "<" << " ";
					for (const auto& l : *(j.second)) {
						str << l << " ";
					}
					str << ">" << "  ";
				}
				str << "\n" << "}" << "\n";
			}
		}
		str << "\n";
	}
	str << "\n";
	return str;
}

ostream& operator<<(ostream& str, const LinkedList& g) {
	node* p1{ g.head };
	while (p1) {
		str << p1->value << " ";
		p1 = p1->next;
	}
	cout << "\n";
	return str;
}


int main() {
	//The following statement won't compile. Fix it. 
	//Set initial values for S1.  Every structure, set or map, needs to have at least 3 elements.

	set<map < map <int*, string, custom_funtor_class_0_inside_map>*, set <int>*, custom_funtor_class_1_inner_map>, custom_funtor_class_1_outer_map> S1;
	map<map<int*, string, custom_funtor_class_0_inside_map>*, set<int>*, custom_funtor_class_1_inner_map>* new_map_1;
	int num{ 9 };

	for (int i = 0; i < 3; i++) {
		new_map_1 = new map < map <int*, string, custom_funtor_class_0_inside_map>*, set <int>*, custom_funtor_class_1_inner_map>;
		map <int*, string, custom_funtor_class_0_inside_map>* new_map_2;
		set <int>* new_set;
		for (int j = 0; j < 3; j++) {
			new_map_2 = new map <int*, string, custom_funtor_class_0_inside_map>;
			new_set = new set <int>;
			if (num == 9) {
				new_map_2->insert(make_pair(new int{ 1 }, "Drew"));
				new_map_2->insert(make_pair(new int{ 2 }, "Bud"));
				new_map_2->insert(make_pair(new int{ 3 }, "Doug"));
				new_set->insert(0);
				new_set->insert(1);
				new_set->insert(6);
			}
			else if (num == 8) {
				new_map_2->insert(make_pair(new int{ 1000 }, "Ray"));
				new_map_2->insert(make_pair(new int{ 2 }, "Tim"));
				new_map_2->insert(make_pair(new int{ 3 }, "Tracy"));
				new_set->insert(1);
				new_set->insert(2);
				new_set->insert(5);
			}
			else if (num == 7) {
				new_map_2->insert(make_pair(new int{ 2 }, "Jacob"));
				new_map_2->insert(make_pair(new int{ 4 }, "Chris"));
				new_map_2->insert(make_pair(new int{ 7 }, "Ken"));
				new_set->insert(0);
				new_set->insert(1);
				new_set->insert(7);
			}
			else if (num == 6) {
				new_map_2->insert(make_pair(new int{ 2 }, "Nancy"));
				new_map_2->insert(make_pair(new int{ 5 }, "Jeff"));
				new_map_2->insert(make_pair(new int{ 7 }, "Bob"));
				new_set->insert(1);
				new_set->insert(5);
				new_set->insert(9);
			}
			else if (num == 5) {
				new_map_2->insert(make_pair(new int{ 3 }, "Mary"));
				new_map_2->insert(make_pair(new int{ 12 }, "Jim"));
				new_map_2->insert(make_pair(new int{ 15 }, "Dan"));
				new_set->insert(0);
				new_set->insert(1);
				new_set->insert(2);
			}
			else if (num == 4) {
				new_map_2->insert(make_pair(new int{ 17 }, "William"));
				new_map_2->insert(make_pair(new int{ 6 }, "Paullus"));
				new_map_2->insert(make_pair(new int{ 9 }, "Quinctius"));
				new_set->insert(5);
				new_set->insert(12);
				new_set->insert(4);
			}
			else if (num == 3) {
				new_map_2->insert(make_pair(new int{ 1 }, "Bill"));
				new_map_2->insert(make_pair(new int{ 2 }, "Mike"));
				new_map_2->insert(make_pair(new int{ 5 }, "Steve"));
				new_set->insert(1);
				new_set->insert(3);
				new_set->insert(6);
			}
			else if (num == 2) {
				new_map_2->insert(make_pair(new int{ 1 }, "Jerry"));
				new_map_2->insert(make_pair(new int{ 8 }, "Joe"));
				new_map_2->insert(make_pair(new int{ 9 }, "Zach"));
				new_set->insert(1);
				new_set->insert(2);
				new_set->insert(4);
			}
			else if (num == 1) {
				new_map_2->insert(make_pair(new int{ 7 }, "Wendy"));
				new_map_2->insert(make_pair(new int{ 9 }, "Marty"));
				new_map_2->insert(make_pair(new int{ 12 }, "Ed"));
				new_set->insert(0);
				new_set->insert(1);
				new_set->insert(3);
			}
			num--;
			(*(new_map_1))[new_map_2] = new_set;
		}

		S1.insert(*new_map_1);
	}




	//You need to support the following statement.
	cout << S1 << endl;


	////The following statement won't compile. Fix it.
	////Set initial values for H1.  Every structure, set or map, needs to have at least 3 elements.
	unordered_set<map < map <int*, string, custom_funtor_class_0_inside_map>*, set <int>*, custom_funtor_class_1_inner_map>, custom_funtor_class_2, custom_funtor_class_2> H1;
	unordered_set<map < map <int*, string, custom_funtor_class_0_inside_map>*, set <int>*, custom_funtor_class_1_inner_map>, custom_funtor_class_2, custom_funtor_class_2>* marker{ &H1 };

	map < map <int*, string, custom_funtor_class_0_inside_map>*, set <int>*, custom_funtor_class_1_inner_map>* new_map_3;
	int num1{ 9 };
	int cnt1{ 0 };
	for (int i = 0; i < 3; i++){
		new_map_3 = new map < map <int*, string, custom_funtor_class_0_inside_map>*, set <int>*, custom_funtor_class_1_inner_map>;
		map <int*, string, custom_funtor_class_0_inside_map >* new_map_4;
		set <int>* new_set1;
		for (int j = 0; j < 3; j++) {
			new_map_4 = new map <int*, string, custom_funtor_class_0_inside_map >;
			new_set1 = new set <int>;
			if (num1 == 9) {
				new_map_4->insert(make_pair(new int{ 1 }, "Drew"));
				new_map_4->insert(make_pair(new int{ 2 }, "Bud"));
				new_map_4->insert(make_pair(new int{ 3 }, "Doug"));
				new_set1->insert(0);
				new_set1->insert(1);
				new_set1->insert(6);
			}
			else if (num1 == 8) {
				new_map_4->insert(make_pair(new int{ 1000 }, "Ray"));
				new_map_4->insert(make_pair(new int{ 2 }, "Tim"));
				new_map_4->insert(make_pair(new int{ 3 }, "Tracy"));
				new_set1->insert(1);
				new_set1->insert(2);
				new_set1->insert(5);
			}
			else if (num1 == 7) {
				new_map_4->insert(make_pair(new int{ 2 }, "Jacob"));
				new_map_4->insert(make_pair(new int{ 4 }, "Chris"));
				new_map_4->insert(make_pair(new int{ 7 }, "Ken"));
				new_set1->insert(0);
				new_set1->insert(1);
				new_set1->insert(7);
			}
			else if (num1 == 6) {
				new_map_4->insert(make_pair(new int{ 2 }, "Nancy"));
				new_map_4->insert(make_pair(new int{ 5 }, "Jeff"));
				new_map_4->insert(make_pair(new int{ 7 }, "Bob"));
				new_set1->insert(1);
				new_set1->insert(5);
				new_set1->insert(9);
			}
			else if (num1 == 5) {
				new_map_4->insert(make_pair(new int{ 3 }, "Mary"));
				new_map_4->insert(make_pair(new int{ 12 }, "Jim"));
				new_map_4->insert(make_pair(new int{ 15 }, "Dan"));
				new_set1->insert(0);
				new_set1->insert(1);
				new_set1->insert(2);
			}
			else if (num1 == 4) {
				new_map_4->insert(make_pair(new int{ 17 }, "William"));
				new_map_4->insert(make_pair(new int{ 6 }, "Paullus"));
				new_map_4->insert(make_pair(new int{ 9 }, "Quinctius"));
				new_set1->insert(5);
				new_set1->insert(12);
				new_set1->insert(4);
			}
			else if (num1 == 3) {
				new_map_4->insert(make_pair(new int{ 1 }, "Bill"));
				new_map_4->insert(make_pair(new int{ 2 }, "Mike"));
				new_map_4->insert(make_pair(new int{ 5 }, "Steve"));
				new_set1->insert(1);
				new_set1->insert(3);
				new_set1->insert(6);
			}
			else if (num1 == 2) {
				new_map_4->insert(make_pair(new int{ 1 }, "Jerry"));
				new_map_4->insert(make_pair(new int{ 8 }, "Joe"));
				new_map_4->insert(make_pair(new int{ 9 }, "Zach"));
				new_set1->insert(1);
				new_set1->insert(2);
				new_set1->insert(4);
			}
			else if (num1 == 1) {
				new_map_4->insert(make_pair(new int{ 7 }, "Wendy"));
				new_map_4->insert(make_pair(new int{ 9 }, "Marty"));
				new_map_4->insert(make_pair(new int{ 12 }, "Ed"));
				new_set1->insert(0);
				new_set1->insert(1);
				new_set1->insert(3);
			}
			num1--;

			(*(new_map_3))[new_map_4] = new_set1;
		}
		H1.insert(*new_map_3);
	}

	////You need to support the following statement.
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