#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <string>
#include "ArgumentManager.h"

using namespace std;

struct node
{
	string word;
	node* next = NULL;
};

//functions
void lowercase(string& str);
void removeduplicates(struct node* head);
void removenumbers(struct node* head);
void movetoarr(string arr[], struct node* head, int nodecount, int count);
int binsearch(string input_word, string diction_arr[], int nodecount);
void removearrnum(string arr[], int mispcount);
void lowercasenode(struct node* head);

//variables
string diction_link = "dictionary.txt", input_link = "input1.txt";
string diction_word, input_word;
string tempword, tempor, itemp, misp = ""; //temporary strings
string* diction_arr, *input_arr, *misp_arr; //dynamic arrays
ifstream dictionfile, inputfile;
ofstream outputfile;
bool recursiveFlag;

//nodes
node* current = NULL;
node* head = NULL;
node* tail = NULL;
node* temp = NULL;
node* headstart = NULL;

int main(int argc, char* argv[])
{
	int nodecount = 1, inputcount = 1, count = 0, icount = 0, mispcount = 0;//Counters


	/*if (argc < 2) {
		std::cerr << "Usage: spellchecker input=input.txt;dict=dictionary.txt;recursive=y" << std::endl;
		return -1;
	}
	ArgumentManager am(argc, argv);
	ArgumentManager bm(argc, argv);
	ArgumentManager cm(argc, argv);

	const std::string input_file_name = am.get("input");
	std::cout << "input file name is " << input_file_name << std::endl;
	inputfile.open(input_file_name.c_str());

	const std::string diction_file_name = bm.get("dictionary");
	std::cout << "diction file name is " << diction_file_name << std::endl;
	dictionfile.open(diction_file_name.c_str());

	const std::string recursiveFlaginput = cm.get("recursive");
	if (recursiveFlaginput == "y" || recursiveFlaginput == "Y") {
		recursiveFlag = true;
		cout << "Recursive Flag = True" << endl;
	}
	else {
		recursiveFlag = false;
		cout << "Recursive Flag = False" << endl;
	}*/

	dictionfile.open(diction_link);//Opening Dictionary
	inputfile.open(input_link);//opening input file

	if (!dictionfile.is_open())//Checks if dictionary opens
	{
		cout << "Dictionary text file failure." << endl;
	}
	else
	{
		cout << "Dictionary text file opened successfully." << endl;
	}

	while (!dictionfile.eof())//While not the end
	{
		dictionfile >> diction_word;//Place words in diction_word

		if (diction_word != "")//if diction_word is not empty
			tempword = diction_word;

		if (head == NULL) //if head doesn't have anything
		{
			current = new node;
			current->word = tempword; //word in node equals tempword
			head = current;
			tail = current;
			headstart = head;
		}
		else //if head already have something
		{
			current = new node;
			current->word = tempword;
			tail->next = current;
			tail = current;//next node equals tempword
		}

	}

	lowercasenode(head); //lowercase each word in node

	removeduplicates(head); //remove duplicates

	removenumbers(head); //remove numbers

	while (head != NULL) //count number of elements in node
	{
		head = head->next;
		nodecount++;
	}

	diction_arr = new string[nodecount];//create dynamic array size of the element of nodes

	movetoarr(diction_arr, headstart, nodecount, count + 1);//move elements from linked lists to the dynamic array

														//clears linked lists and tempword
	head = NULL;
	tail = NULL;
	current = NULL;
	headstart = NULL;
	tempword = "";

	dictionfile.close();//close dictionary file


	for (int i = 0; i < nodecount - 1; i++) //bubble sort the array alphabetically
	{
		for (int j = i + 1; j < nodecount; j++)
		{
			if (diction_arr[j] < diction_arr[i])
			{
				tempor = diction_arr[j];
				diction_arr[j] = diction_arr[i];
				diction_arr[i] = tempor;
			}
		}
	}



	if (!inputfile.is_open()) //test if file opens
	{
		cout << "Input text file failure." << endl;
	}
	else
	{
		cout << "Input text file opened successfully." << endl;
	}
	while (!inputfile.eof()) //while file doesnt end
	{
		inputfile >> input_word;
		if (input_word != "")
			tempword = input_word;

		if (head == NULL)//placing words in the beginning of the node
		{
			current = new node;
			current->word = tempword;
			head = current;
			tail = current;
			headstart = head;
		}
		else//continue placing words in the linked list
		{
			current = new node;
			current->word = tempword;
			tail->next = current;
			tail = current;
		}

	}

	lowercasenode(head);//lowercasing the nodes

	while (head != NULL) //count number of elements in the input file
	{
		head = head->next;
		inputcount++;
	}

	input_arr = new string[nodecount];//creating dynamic array for input words

	movetoarr(input_arr, headstart, inputcount, icount + 1); //dynamic array created with elements from input file

														 //clears linked lists and tempword
	head = NULL;
	tail = NULL;
	current = NULL;
	headstart = NULL;
	tempword = "";

	inputfile.close();//close input file

	for (int i = 0; i < inputcount - 1; i++) //bubble sort input array alphabetically
	{
		for (int j = i + 1; j < inputcount; j++)
		{
			if (input_arr[j] < input_arr[i])
			{
				itemp = input_arr[j];
				input_arr[j] = input_arr[i];
				input_arr[i] = itemp;
			}
		}
	}

	for (int i = 0; i < inputcount; i++) //count number of mispelled words
	{
		string input_word = input_arr[i];
		int result = binsearch(input_word, diction_arr, nodecount);//recursive binary search
		if (result == -1)
		{
			mispcount++;
		}

	}

	misp_arr = new string[mispcount]; //created array of misspelled words

	int j = 0;

	for (int i = 0; i < inputcount; i++) //place misspelled words to misspelled arrays
	{
		string input_word = input_arr[i];
		int result = binsearch(input_word, diction_arr, nodecount);//recursive binary search
		if (result == -1)
		{
			misp.append(input_word);
			misp_arr[j] = misp;
			j++;
		}
		misp = "";

	}

	string mistemp;

	for (int i = 0; i < mispcount - 1; i++) //recursive bubble sort input array alphabetically
	{
		for (int j = i + 1; j < mispcount; j++)
		{
			if (misp_arr[j] < misp_arr[i])
			{
				mistemp = input_arr[j];
				misp_arr[j] = misp_arr[i];
				misp_arr[i] = mistemp;
			}
		}
	}

	removearrnum(misp_arr, mispcount);//removing the numbers in the input file

	outputfile.open("output.txt");//opening output file

								  //variables
	string last = misp_arr[0];
	int z;
	int dupcount = 1;

	for (z = 1; z < mispcount; z++) //count up the number of misspelled words in the array
	{
		if (misp_arr[z] == last)
		{
			dupcount++;
		}
		else
		{
			if (last != "0")//output
			{
				cout << misp_arr[z - 1] << " " << dupcount << endl;
				outputfile << misp_arr[z - 1] << " " << dupcount << endl;
			}
			last = misp_arr[z];
			dupcount = 1;
		}

	}

	if (last != "0")//outputs the last element
	{
		cout << misp_arr[z - 1] << " " << dupcount << endl;
		outputfile << misp_arr[z - 1] << " " << dupcount << endl;
	}

	// clearing memory
	misp_arr = NULL;
	input_arr = NULL;
	diction_arr = NULL;

	outputfile.close();
	return 0;

}

void lowercase(string& str) {
	for (size_t i = 0; i < str.length(); i++)
		str[i] = tolower(str[i]);
};

void lowercasenode(struct node* head)
{
	struct node *ptr1;
	ptr1 = head;
	while (ptr1 != NULL && ptr1->next != NULL)
	{
		for (size_t i = 0; i < ptr1->word.length(); i++)
		{
			ptr1->word[i] = tolower(ptr1->word[i]);
		}
		ptr1 = ptr1->next;
	}
};

void removeduplicates(struct node* head)
{
	struct node *ptr1, *ptr2, *dup;
	ptr1 = head;

	while (ptr1 != NULL && ptr1->next != NULL)
	{
		ptr2 = ptr1;

		while (ptr2->next != NULL)
		{

			if (ptr1->word == ptr2->next->word)
			{

				dup = ptr2->next;
				ptr2->next = ptr2->next->next;
				delete(dup);
			}
			else
				ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
};
void removenumbers(struct node* head)
{
	struct node *delnum;
	while (head != NULL && head->next != NULL)
	{
		if (isdigit(head->word[0]))
		{
			delnum = head->next;
			head->word = delnum->word;
			head->next = delnum->next;
			delete (delnum);
		}
		else
			head = head->next;
	}
};

void movetoarr(string arr[], struct node* headstart, int nodecount, int count)
{
	while (headstart != NULL)
	{
		arr[count - 1] = headstart->word;
		//cout << arr[count] << endl;
		headstart = headstart->next;
		count++;
	}
};

int binsearch(string input_word, string diction_arr[], int nodecount)
{
	int first = 0;
	int last = nodecount - 1;
	int mid;
	string word;
	while (first <= last)
	{
		mid = (first + last) / 2;
		word = diction_arr[mid];
		if (input_word == word)
		{
			return mid;
		}
		else if (input_word < word)
		{
			last = mid - 1;
		}
		else
			first = mid + 1;
	}
	return -1;
}

void countdup(string misp_arr, int miscount)
{
	for (int x = 1; x < miscount; x++)
	{
		for (int y = x - 1; y >= 0 && misp_arr[y + 1]<misp_arr[y]; y--)
		{
			int temp = misp_arr[y + 1];
			misp_arr[y + 1] = misp_arr[y];
			misp_arr[y] = temp;
		}
	}
}

void removearrnum(string arr[], int mispcount)
{
	string temp;
	for (int i = 0; i < mispcount; i++)
	{
		if (isdigit(arr[i][0]))
		{
			arr[i] = "0";

		}
	}
}
