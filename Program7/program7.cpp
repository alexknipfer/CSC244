//******************  PROGRAM IDENTIFICATION  **************************
//*                                                                    *
//*  PROGRAM FILE NAME: program7.cpp  ASSIGNMENT #:  7    Grade: _____ *
//*   	                                                               *
//*  PROGRAM AUTHOR:   ____________________________________            *
//*                             Alex Knipfer                           *
//*                                                                    *
//*  COURSE #:   CSC 24400 11             DUE DATE: May 01, 2015       *
//*                                                                    *
//**********************************************************************

//********************* PROGRAM DESCRIPTION ****************************
//*								                                       *
//*     Process: This program is designed to keep track of budget      *
//*              activities for an organization consisting of five     *
//*              divisions. It will also keep track of all activities  *
//*              for corporate.                                        *
//*								                                       *
//*     USER DEFINED						                           *
//*      MODULES:     : printHeader - print program header             *
//*                     printFooter - print program footer             *
//**********************************************************************


#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

	// defines when to stop reading file
#define Sentinel 'Q'

class BudgetTracker
{
	public:
		BudgetTracker(int);
		void initializeBudget(ifstream &);
		double getCredit();
		double getDebit();
		double getBalance();
		bool getIsInitialized();
		void addCredit(double);
		void addDebit(double);
		void addBalance(double);
		void subtractBalance(double);
		void printEverything(ofstream &);
		void printDivision(ofstream &);

	private:
		int divisionID;
		double credit;
		double debit;
		double balance;
		bool isInitialized;
};

void printHeader(ofstream &);
void printFooter(ofstream &);

//********************************************************************//

int main()
{
	ofstream outputFile("output.txt");
	ifstream inputFile("data7.txt");

	printHeader(outputFile);

		// Initialize divisions with given ID's
		// Initialize corporate with random ID
	BudgetTracker division1(2017);
	BudgetTracker division2(3026);
	BudgetTracker division3(4039);
	BudgetTracker division4(6049);
	BudgetTracker division5(7052);
	BudgetTracker corporate(1111);

		// Trans type to identify what to do with data read in
	char transType;

		// Identifies whether to print everything or specific division
	char whatToPrint;

		// Keeps track of division ID
	int divID;

		// Stores value of credit read in
	double newCredit;

		// Stores value of debit read in
	double newDebit;

		// Read in next transaction type
	inputFile >> transType;

		// Keep reading in data until hitting a "q"
	while(transType != Sentinel)
	{
			// If trans type is an I then initialize the budget
		if(transType == 'I')
		{
				// Read in division ID to initialize
			inputFile >> divID;

				// Check which division ID is read in and initialize
				// all budgets for that division. Also adds credit and
				// debits for corporate to keep a running total
			switch(divID)
			{
				case 2017:
					division1.initializeBudget(inputFile);
					corporate.addCredit(division1.getCredit());
					corporate.addDebit(division1.getDebit());
					corporate.addBalance(division1.getBalance());
				break;

				case 3026:
					division2.initializeBudget(inputFile);
					corporate.addCredit(division2.getCredit());
					corporate.addDebit(division2.getDebit());
					corporate.addBalance(division2.getBalance());
				break;

				case 4039:
					division3.initializeBudget(inputFile);
					corporate.addCredit(division3.getCredit());
					corporate.addDebit(division3.getDebit());
					corporate.addBalance(division3.getBalance());
				break;

				case 6049:
					division4.initializeBudget(inputFile);
					corporate.addCredit(division4.getCredit());
					corporate.addDebit(division4.getDebit());
					corporate.addBalance(division4.getBalance());
				break;

				case 7052:
					division5.initializeBudget(inputFile);
					corporate.addCredit(division5.getCredit());
					corporate.addDebit(division5.getDebit());
					corporate.addBalance(division5.getBalance());
				break;
			}
		}

			// If the transtype is a p then print
		if(transType == 'P')
		{
				// Read in next value to determine to print everything
				// or print a specific division
			inputFile >> whatToPrint;

				// Print everything if value is E
			if(whatToPrint == 'E')
			{
					// Print labels for output
				outputFile << "               Amount of   Amount of";
				outputFile << "   Account";
				outputFile << endl;
				outputFile << left << setw(15) << "Division ID";
				outputFile << left << setw(12) << "Credits";
				outputFile << left << setw(12) << "Debits";
				outputFile << left << setw(12) << "Balance" << endl;

					// Print horizontal line to separate output
				for(int x = 0; x < 50; x++)
				{
					outputFile << "-";
				}

				outputFile << endl;

					// Only print divisions if they have been initialized,
					// do not print if they have not been
				if(division1.getIsInitialized() == true)
				{
					division1.printEverything(outputFile);
				}

				if(division2.getIsInitialized() == true)
				{
					division2.printEverything(outputFile);
				}

				if(division3.getIsInitialized() == true)
				{
					division3.printEverything(outputFile);
				}

				if(division4.getIsInitialized() == true)
				{
					division4.printEverything(outputFile);
				}

				if(division5.getIsInitialized() == true)
				{
					division5.printEverything(outputFile);
				}

					// Print horizontal line to separate output
				for(int x = 0; x < 50; x++)
				{
					outputFile << "-";
				}

				outputFile << endl;

					// Print corporate totals
				corporate.printEverything(outputFile);

				outputFile << endl;

					// Print horizontal line to separate output
				for(int x = 0; x < 50; x++)
				{
					outputFile << "*";
				}

				outputFile << endl;
				outputFile << endl;
			}

				// If value is an S only print specific division
			if(whatToPrint == 'S')
			{
					// Read in division ID to see what to print
				inputFile >> divID;

					// Print labels for output
				outputFile << "               Amount of   Amount of";
				outputFile << "   Account";
				outputFile << endl;
				outputFile << left << setw(15) << "Division ID";
				outputFile << left << setw(12) << "Credits";
				outputFile << left << setw(12) << "Debits";
				outputFile << left << setw(12) << "Balance" << endl;

					// Print horizontal line to separate output
				for(int x = 0; x < 50; x++)
				{
					outputFile << "-";
				}

				outputFile << endl;

					// Print the correct division from which was read in
				switch(divID)
				{
					case 2017:
						division1.printDivision(outputFile);
					break;

					case 3026:
						division2.printDivision(outputFile);
					break;

					case 4039:
						division3.printDivision(outputFile);
					break;

					case 6049:
						division4.printDivision(outputFile);
					break;

					case 7052:
						division5.printDivision(outputFile);
					break;
				}

				outputFile << endl;

					// Print line to separate output
				for(int x = 0; x < 50; x++)
				{
					outputFile << "*";
				}

				outputFile << endl;
				outputFile << endl;
			}
		}

			// If trans type is a C then update specific division credit
		if(transType == 'C')
		{
				// Read in division ID
			inputFile >> divID;

				// Read in value to change
			inputFile >> newCredit;

				// Find division which was read in and add the credit
				// to that specific division and add to corporate to keep
				// a running total
			switch(divID)
			{
				case 2017:
					division1.addCredit(newCredit);
					division1.addBalance(newCredit);
					corporate.addBalance(newCredit);
					corporate.addCredit(newCredit);
				break;

				case 3026:
					division2.addCredit(newCredit);
					division2.addBalance(newCredit);
					corporate.addBalance(newCredit);
					corporate.addCredit(newCredit);
				break;

				case 4039:
					division3.addCredit(newCredit);
					division3.addBalance(newCredit);
					corporate.addBalance(newCredit);
					corporate.addCredit(newCredit);
				break;

				case 6049:
					division4.addCredit(newCredit);
					division4.addBalance(newCredit);
					corporate.addBalance(newCredit);
					corporate.addCredit(newCredit);
				break;

				case 7052:
					division5.addCredit(newCredit);
					division5.addBalance(newCredit);
					corporate.addBalance(newCredit);
					corporate.addCredit(newCredit);
				break;
			}
		}

			// If trans type is D then update specific division debit
		if(transType == 'D')
		{
				// Read in division ID
			inputFile >> divID;

				// Read in debit to update
			inputFile >> newDebit;

				// Find division which was read in and add the debit
				// to that specific division and add to corporate to keep
				// a running total
			switch(divID)
			{
				case 2017:
					division1.addDebit(newDebit);
					division1.subtractBalance(newDebit);
					corporate.subtractBalance(newDebit);
					corporate.addDebit(newDebit);
				break;

				case 3026:
					division2.addDebit(newDebit);
					division2.subtractBalance(newDebit);
					corporate.subtractBalance(newDebit);
					corporate.addDebit(newDebit);
				break;

				case 4039:
					division3.addDebit(newDebit);
					division3.subtractBalance(newDebit);
					corporate.subtractBalance(newDebit);
					corporate.addDebit(newDebit);
				break;

				case 6049:
					division4.addDebit(newDebit);
					division4.subtractBalance(newDebit);
					corporate.subtractBalance(newDebit);
					corporate.addDebit(newDebit);
				break;

				case 7052:
					division5.addDebit(newDebit);
					division5.subtractBalance(newDebit);
					corporate.subtractBalance(newDebit);
					corporate.addDebit(newDebit);
				break;
			}
		}

			// Read in next trans type
		inputFile >> transType;
	}

	printFooter(outputFile);

	return 0;
}

//********************************************************************//

BudgetTracker::BudgetTracker(int divID)
{
		// Receives - division ID
		// Task - initialize private variables
		// Returns - nothing

	divisionID = divID;
	isInitialized = false;
	credit = 0.0;
	debit = 0.0;
	balance = 0.0;

	return;
}

//********************************************************************//

void BudgetTracker::initializeBudget(ifstream &inputFile)
{
		// Receives - input file
		// Task - read in credit, debit, and balance from file
		// Returns - nothing

		// Read in credit, debit, balance from file
	inputFile >> credit;
	inputFile >> debit;
	inputFile >> balance;

		// Set value to true since division has been initialized
	isInitialized = true;

	return;
}

//********************************************************************//

bool BudgetTracker::getIsInitialized()
{
		// Receives - nothing
		// Task - Get the value of isInitialized
		// Returns - isInitialized

	return isInitialized;
}

//********************************************************************//

double BudgetTracker::getCredit()
{
		// Receives - nothing
		// Task - get value of credit
		// Returns - credit

	return credit;
}

//********************************************************************//

double BudgetTracker::getDebit()
{
		// Receives - nothing
		// Task - get value of debit
		// Returns - debit

	return debit;
}

//********************************************************************//

double BudgetTracker::getBalance()
{
		// Recieves - nothing
		// Task - get value of balance
		// Returns - balance

	return balance;
}

//********************************************************************//

void BudgetTracker::printEverything(ofstream &outputFile)
{
		// Receives - output file
		// Task - print all divisions
		// Returns - nothing

		// Don't print division ID for coporate (which is 1111)
	if(divisionID != 1111)
	{
		outputFile << left << "  " << divisionID << " ";
	}

		// If object being delt with is coporate, print label for corporate
	if(divisionID == 1111)
	{
		outputFile << "Corporation" << endl << "Totals" << " ";
	}

		// Print out credits, debits, and balance
	outputFile << fixed << right << setprecision(2) << setw(15) << credit;
	outputFile << fixed << right << setprecision(2) << setw(12) << debit;
	outputFile << fixed << right << setprecision(2) << setw(12) <<
	              balance << endl;

	return;
}

//********************************************************************//

void BudgetTracker::printDivision(ofstream &outputFile)
{
		// Receives - output file
		// Task - print a specific division
		// Returns - nothing

		// Print out all division information (ID, credits, debits, balance)
	outputFile << "  " << divisionID << " ";
	outputFile << fixed << right << setprecision(2) << setw(15) << credit;
	outputFile << fixed << right << setprecision(2) << setw(12) << debit;
	outputFile << fixed << right << setprecision(2) << setw(12) <<
				  balance << endl;

	return;
}

//********************************************************************//

void BudgetTracker::addCredit(double newCredit)
{
		// Receives - newCredit (credit to be added)
		// Task - add a new credit to credit
		// Returns - nothing

		// add read in credit value to the credit total
	credit += newCredit;

	return;
}

//********************************************************************//

void BudgetTracker::addDebit(double newDebit)
{
		// Receives - newDebit (debit to be added)
		// Task - add debit to debit total
		// Returns - nothing

		// add debit to debit total
	debit += newDebit;

	return;
}

//********************************************************************//

void BudgetTracker::addBalance(double addedCredit)
{
		// Receives - addedCredit (credit to be added)
		// Task - add credit to balance total
		// Returns - nothing

		// add credit to balance total
	balance += addedCredit;

	return;
}

//********************************************************************//

void BudgetTracker::subtractBalance(double subtDebit)
{
		// Receives - subtCredit
		// Task - subtract debits from balance
		// Returns - nothing

		// subtract from balance total
	balance -= subtDebit;

	return;
}

//********************************************************************//

void printHeader(ofstream &Outfile)
{
		// Receives - the output file
		// Task- Prints the output preamble
		// Returns - Nothing
	Outfile << setw(30) << "Alex Knipfer ";
	Outfile << setw(17) << "CSC 24400";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2015";
	Outfile << setw(20) << "Assignment #7" << endl;
	Outfile << setw(35) << "--------------------------------------";
	Outfile << setw(35) << "--------------------------------------\n\n";
	return;
}

//********************************************************************//

void printFooter(ofstream &Outfile)
{
	Outfile << endl;
	Outfile << setw(35) << "--------------------------------" << endl;
	Outfile << setw(35) << "|    END OF PROGRAM OUTPUT     |" << endl;
	Outfile << setw(35) << "--------------------------------" << endl;

	return;
}

//*********************** END OF PROGRAM *****************************//

