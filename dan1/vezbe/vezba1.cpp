// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>

struct NodeIterator;

struct Node {
	Node() {}
	Node(int e, Node* n) : elem(e), next(n) {}
	NodeIterator begin();
	NodeIterator end();
	int elem = 0;
	Node* next = nullptr;
};

void add(Node& n, int x) {
	n.next = new Node(x, n.next);
}

struct NodeIterator {
	NodeIterator() {};
	NodeIterator(Node* x) : p(x) {}
	int& operator*() { return p->elem; }
	NodeIterator operator++() { p = p->next; return p; }
	NodeIterator operator++(int) { NodeIterator iterator = p; p = p->next; return iterator; }
	bool operator==(const NodeIterator& other) const { return p == other.p; }
	bool operator!=(const NodeIterator& other) const { return p != other.p; }
	//friend NodeIterator begin() { return NodeIterator(p); }
	//friend NodeIterator end() { return NodeIterator(nullptr); }
	Node* p = nullptr;	
};

NodeIterator Node::begin() {
	return NodeIterator(this->next);
}

NodeIterator Node::end() {
	return NodeIterator(nullptr);
}

int main() {
	Node head;
	add(head, 1);
	add(head, 2);
	add(head, 3);
	add(head, 4);
	add(head, 5);

	for (Node* p = head.next; p != nullptr; p = p->next) {
		std::cout << p->elem << " ";
	}
	std::cout << std::endl;

	for (int x : head) { // for( int x = head.begin(); x != head.end(); ++x)
		std::cout << x << " ";
	}
	std::cout << std::endl;
	for (int& x : head) {
		x = 7;
	}
	for (const int& x : head) {
		std::cout << x << " ";
	}
	std::cout << std::endl;

	return 0;
}
