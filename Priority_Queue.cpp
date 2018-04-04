///////////////////////////////////////////////////////////////////////////////       
// Title: Priority Queue
// Files: Priority_Queue.cpp
//		  Input_Data.txt
//		  Priority_Out.txt	
// Semester: Spring 2018
// Author: Bryson Brown
// Email: brysonjamalb@yahoo.com
// Description: Make a Priority Queue based on word length where shorter words  
//				are higher priority based on aphebetical order.
/////////////////////////////////////////////////////////////////////////////////
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


// Struct holds the node

struct Node {
	string val;
	Node *next;
	Node() {
		val = " ";
		next = NULL;
	}
	Node(string v) {
		val = v;
		next = NULL;
	}
};

/*className - Queue
*
* Methods:
*   void Queue()
*   void readFile()
*   string pop()
*   void push(string v)
*   bool empty()
*   void print()
*/
class Queue {
//Private Members
private:
	Node *Front;
	Node *Rear;
	string cmd;
	string word;
	ifstream fin;
	ofstream fout;

//Public Memebers
public:
	/*
	* FunctionName :Queue
	*
	* Description:
	*       This is the constructor
	* Params:
	*       None
	* Returns:
	*      None
	*/
	//Read Input File, Output File
  Queue() {
		Front = Rear = NULL;
		cmd = " ";
		word = " ";
		fin.open("Input_Data.txt");
		fout.open("Priority_Out.txt");
	}

	/*
	* FunctionName :readFile
	*
	* Description:
	*       Reads commands and either performs a push or pop method
	* Params:
	*      None
	* Returns:
	*      The item removed
	*/
	void readFile() {
		int i = 1;

		fout << "Animals Popped off the Queue : " << endl << endl;

		while (!fin.eof()) {
			fin >> cmd >> word;

			if (!cmd.compare("push")) {
				push(word);
			}
			if (!cmd.compare("pop")) {
				fout << i << " " << pop() << endl;
				i++;

			}
		}

		fout << endl;
	}

	/*
	* FunctionName :pop
	*
	* Description:
	*       This method removes an item from the list
	* Params:
	*      None
	* Returns:
	*      The item removed
	*/
	string pop() {
		if (!empty()) {
			Node *temp = Front;   // temp pointer so we can delete node
			string v = temp->val; // grab value out of node
			Front = Front->next;  // move pointer to next node
			delete temp;		  // give mem back to system
			return v;
		}
		else {
			fout << "error: cannot pop off empty queue." << endl;
			return " ";
		}
	}

	/*
	* FunctionName : push
	*
	* Description:
	*       This method adds an item to the list and begins to sort the
	*       list everytime a new item is added via the sort method
	* Params:
	*       string v - the item to be added
	* Returns:
	*       none
	*/
	void push(string v) {
		Node *n = new Node(v);

		// Handles empty case
		if (empty()) {
			Front = n;
			Rear = n;
		}
		else {
			// Add to rear
			Rear-> next = n;
			Rear = n;
			sort();
		}
	}

	/*
	* FunctionName : sort
	*
	* Description:
	*       sorts each item in the queue in terms of  priority
	* Params:
	*       none
	* Returns:
	*       none
	*/
	void sort() {
		string tWord = " ";
		Node *temp = Front;
		Node *i;
		Node *j;

		for (i = Front; i != NULL; i = i->next) {
			for (j = i->next; j != NULL; j = j->next) {
				// Handles the number of characters
				if (j->val.length() < i->val.length()) {
					tWord = j->val;
					j->val = i->val;
					i->val = tWord;
				}

				// Handles when the letters are the same
				else if (j->val.length() == i->val.length()) {
					for (int k = 0; k < j->val.length(); k++) {
						if ((int)j->val[k] < (int)i-> val[k]) {
							tWord = j->val;
							j->val = i-> val;
							i->val = tWord;
						}
						break;
					}
				}
			}
		}
	}

	/*
	* @FunctionName :empty
	*
	* @Description:
	*       Checks wheter the list empty or not
	* @Params:
	*       none
	* @Returns:
	*      returns true or false
	*/
	bool empty() {
		return (Front == NULL);
	}

	/*
	* FunctionName : print
	*
	* Description:
	*       Prints all the items currently in the queue
	* Params:
	*      none
	* Returns:
	*    none
	*/

	void print() {


		fout << "Animals Remaining on the Queue (in order of priority) : " << endl << endl;
		Node *temp = Front;
		int i = 1;
		while (temp) {
			fout << i << " " << temp->val << "\n";
			temp = temp->next;
			i++;
		}
		fout << endl;
		fout.close();
	}
};
int main() {
	Queue Q;
	Q.readFile();
	Q.print();
}
