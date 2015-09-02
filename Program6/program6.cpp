//******************  PROGRAM IDENTIFICATION  **************************
//*                                                                    *
//*  PROGRAM FILE NAME: program6.cpp  ASSIGNMENT #:  6    Grade: _____ *
//*   	                                                               *
//*  PROGRAM AUTHOR:   ____________________________________            *
//*                             Alex Knipfer                           *
//*                                                                    *
//*  COURSE #:   CSC 24400 11             DUE DATE: April 21, 2015     *
//*                                                                    *
//**********************************************************************

//********************* PROGRAM DESCRIPTION ****************************
//*								                                       *
//*     Process: This program is designed to read a list of data       *
//*     containing customer names with their personal information.     *
//*     As the data file is read in the program will either add,       *
//*     update, or remove the customer to the database (array). The    *
//*     program will also print all customers or print a specific      *
//*     customer depending on what the data file says.                 *
//*								                                       *
//*     USER DEFINED						                           *
//*      MODULES:     : addCustomer - reads in customers and adds them *
//*                                   to array                         *
//*                     printAllCustomer - prints all customers and    *
//*                                        their information           *
//*                     printOneCustomer - prints a specific customer  *
//*                     changeCustomer - updates customer information  *
//*                     deleteCustomer - deletes customer from array   *
//**********************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

	// Stop reading the file once reading in "Q"
#define Sentinel 'Q'

	// initialize customer type structure
struct CustomerType
{
	char lastName[13];
	char firstName[13];
	char streetAddress[21];
	char city[13];
	char state[3];
	char zipCode[6];
	int tag;
};

void printHeader(ofstream &);
void printFooter(ofstream &);
CustomerType addCustomer(ifstream &, CustomerType[], int);
void printAllCustomer(ofstream &, CustomerType[], int);
void printOneCustomer(ofstream &, ifstream &, CustomerType[], int);
void changeCustomer(ifstream &, ofstream &, CustomerType[], int);
void deleteCustomer(ifstream &, ofstream &, CustomerType[], int);

//****************** START OF MAIN *************************************

int main()
{
	ofstream outputFile("output.txt");
	ifstream inputFile("data6.txt");
	
		// print program header to file
	printHeader(outputFile);	
	
		// Trans type from file
	char transType;
	
		// Value will hold "E" or "S" for what to print
	char whatToPrint;
	
		// Initialize array of customers
	CustomerType customerData[50];
	
		// Initialize count for array
	int counter = 0;
	
		// Holds amount of elements used in array
	int elementsUsed = 0;
	
		// Stores the customer number
	int customerNumber = 1;
	
		// Read in transaction type
	inputFile >> transType;
	
		// Keep reading in data unless trans type is "Q"
	while(transType != Sentinel)
	{
			// If transaction type is "A" add the customer
		if(transType == 'A')
		{
				// Store person returned from addCustomer into array
			customerData[counter] = addCustomer(inputFile, customerData, 
												elementsUsed);
			
				// Don't print any customer that was attempted to be added
				// that was a duplicate
			if(strncmp(customerData[counter].firstName, "duplicate", 13) == 0)
			{
					// Print out error
				outputFile << "Error! Attempt to add a duplicate record." <<
						      " Attempt failed!" << endl;
						      
					// Print out stars to separate output
			    for(int x = 0; x < 70; x++)
			    {
					outputFile << "*";
				}
				outputFile << endl;
			}
			
				// If customer wasn't a duplicate, add the customer and print
			else
			{
				outputFile << "New customer " << customerData[counter].firstName <<
						   " " << customerData[counter].lastName <<
						   "successfully added to database!" << endl;
						
					// Increment customer number for next customer added
				customerData[counter].tag = customerNumber ++;
				
					// Print out stars to separate output
				for(int x = 0; x < 70; x++)
				{
					outputFile << "*";
				}		
				outputFile << endl;				   			
			}
			
				// Increment counter for array
			counter++;
			
				// Increment the amount of elements in the array
			elementsUsed++;		
		}
		
			// If transaction type is "D" delete customer
		else if(transType == 'D')
		{
			deleteCustomer(inputFile, outputFile, customerData, elementsUsed);
		}
		
			// If transaction type is "C" update/change customer
		else if(transType == 'C')
		{
			changeCustomer(inputFile, outputFile, customerData, elementsUsed);
		}
		
			// If transaction type is "P" print customers
		else if(transType == 'P')
		{
				// Get value from file to know what to print
			inputFile >> whatToPrint;
				
				// Print everyting if value is "E"
			if(whatToPrint == 'E')
			{
				printAllCustomer(outputFile, customerData, elementsUsed);
			}
			
				// Print specific customer if value is "S"
			if(whatToPrint == 'S')
			{
				printOneCustomer(outputFile, inputFile, customerData, 
				                 elementsUsed);
			}
			
		}
			
			// Get value for next trans type
		inputFile >> transType;
	}
	
		// prevent output from wrapping to next page
	for(int x = 0; x < 4; x++)
	{
		outputFile << endl;
	}
	
		// print program footer to file
	printFooter(outputFile);
	
	return 0;
}

//*********************** END OF MAIN **********************************

//************************** ADD CUSTOMER ******************************

CustomerType addCustomer(ifstream &inputFile, CustomerType customerData[],
						 int EU)
{
		// Receives - input file, customerData array, elements used
		// Task - add customers to array (mailing list)
		// Returns - Person (customer)
		
		// Initialize customer
	CustomerType Person;
	
		// Get first and last name from data file
	inputFile >> ws;
	inputFile.getline(Person.firstName,13);
	inputFile >> ws;
	inputFile.getline(Person.lastName,13);
		
		// Change first name to "duplicate" if a customer is attempted
		// to be added twice
	for(int x = 0; x < EU; x++)
	{
		if(strncmp(Person.firstName, customerData[x].firstName
				   ,13) == 0)	
	    {
			if(strncmp(Person.lastName, customerData[x].lastName
			   ,13) == 0)	
			{
				strncpy(Person.firstName, "duplicate", 13);
			}		 
		}	
	}	
	
		// Read in remaining customer info from data file
	inputFile >> ws;
	inputFile.getline(Person.streetAddress,21);
	inputFile >> ws;
	inputFile.getline(Person.city,13);
	inputFile >> ws;
	inputFile.getline(Person.state,3);
	inputFile >> ws;
	inputFile.getline(Person.zipCode,6);
	inputFile >> ws;
		
	return Person;
}

//***************** END ADD CUSTOMER ***********************************

//***************** PRINT ALL CUSTOMERS ********************************

void printAllCustomer(ofstream &outputFile, CustomerType customerData[],
                       int EU)
{	
		// Receives - output file, customerData array, elements used
		// Task - print all customers in the array  (mailing list)
		// Returns - nothing
		
		// Print labels for all customers
	outputFile << "                                 MAILING LIST" << endl;
		
	outputFile << "Customer   " << "Last      " << 
	"First       " << "                          " << "            " << 
	"   " << "Zip" << endl;	
	
	outputFile << "Number     " << "Name      " << 
	"Name        " << "  Address           " << "  City      " << 
	"State    " << "Code" << endl;
	
	outputFile << "==================================================="
			   << "================================" << endl;
	
		// Cycle through array to print data (customers)
	for(int x = 0; x < EU; x++)
	{	
			// Do not print customer if name is duplicate
		if(strncmp(customerData[x].firstName, "duplicate", 13) == 0)
		{
			continue;
		}
		
			// If first name is deleted do not print customer
		else if(strncmp(customerData[x].firstName, "deleted", 13) == 0)
		{
			continue;
		}		
		
			// Print out customer information
		outputFile << setw(10) << left << customerData[x].tag;
		outputFile << setw(8) << left << customerData[x].lastName;
		outputFile << setw(6) << customerData[x].firstName;
		outputFile << setw(6) << customerData[x].streetAddress;
		outputFile << setw(6) << customerData[x].city;
		outputFile << setw(6) << customerData[x].state;
		outputFile << setw(6) << customerData[x].zipCode;
		outputFile << endl;
	}
	
		// Print stars to separate (format) output
	for(int x = 0; x < 70; x++)
	{
		outputFile << "*";
	}
	
	outputFile << endl;
}

//**************** END PRINT ALL CUSTOMERS *****************************

//****************** PRINT ONE CUSTOMER ********************************

void printOneCustomer(ofstream &outputFile, ifstream &inputFile, 
                      CustomerType customerData[], int EU)
{
		// Receives - output file, input file, customerData array, 
		//            elements used
		// Task - Print a specific customer (one customer)
		// Returns - nothing
		
	CustomerType currentCustomer;
	bool foundCustomer = true;
	
		// Get last name of what customer to print from file
	inputFile >> ws;
	inputFile.getline(currentCustomer.lastName, 13);
	
		// Cycle through array to search for customer read in from file
	for(int x = 0; x < EU; x++)
	{
		if(strncmp(currentCustomer.lastName, customerData[x].lastName
		   ,13) == 0)
		{	
				// change to false so we know were in loop (true if not found)
			foundCustomer = false;
					
				// Print specific customer information
			outputFile << "Customer Number: " << customerData[x].tag << endl;
			outputFile << "     Name: " << customerData[x].firstName << " " <<
			customerData[x].lastName << "  " <<
			"      Address: " << customerData[x].streetAddress << endl;
			outputFile << "     City: " << customerData[x].city <<  
			"                     " << "State: " << customerData[x].state <<
			"     Zip Code: " << customerData[x].zipCode << endl;
			
				// Print stars to separate output
			for(int i = 0; i < 70; i++)
			{
				outputFile << "*";
			}
			
			outputFile << endl;
			return;
		}
	}	
	
		// If a customer was not found, print a error
	if(foundCustomer == true)
	{
				// Print error
			outputFile << "Error! Attempt to print a non-existent record." <<
					      " Attempt failed!" << endl;
				
				// Print stars to separate output	      
			for(int i = 0; i < 70; i++)
			{
				outputFile << "*";
			}
			
			outputFile << endl;			
	}
}

//****************** END PRINT ONE CUSTOMER ****************************

//********************* CHANGE CUSTOMER ********************************

void changeCustomer(ifstream &inputFile, ofstream &outputFile,
                    CustomerType customerData[], int EU)
{
		// Receives - input file, output file, customerData array, 
		//            elements used
		// Task - change customer information
		// Returns - array data (customer info changed)
		
	CustomerType currentCustomer;
	int fieldID;
		
		// New information that customer info is getting changed to
	char newInfo[21];
	bool foundCustomer = true;
	
		// Read in last name, field ID to change, and new information
		// that is getting replaced (all from file)
	inputFile >> ws;
	inputFile.getline(currentCustomer.lastName,13);
	inputFile >> ws;
	inputFile >> fieldID;
	inputFile >> ws;
	inputFile.getline(newInfo, 21);
	
		// Cycle through file to find customer read in
	for(int x = 0; x < EU; x++)
	{
		if(strncmp(currentCustomer.lastName, customerData[x].lastName
		   ,13) == 0)
		{
				// Print customer first and last name that got updated
			outputFile << "Customer " << customerData[x].firstName << " " <<
			customerData[x].lastName << " successfully updated!" << endl;
			
				// Print stars to separate output
			for(int i = 0; i < 70; i++)
			{
				outputFile << "*";
			}
			
			outputFile << endl;
			
				// Change to false so error isn't printed below
			foundCustomer = false;
			
				// The following field ID's correspond to what specific
				// information needs to be changed on the customer
				// and replaces it with the read in data
			if(fieldID == 1)
			{
				strncpy(customerData[x].lastName, newInfo, 13);
			}
			
			if(fieldID == 2)
			{
				strncpy(customerData[x].firstName, newInfo, 13);			
			}
			
			if(fieldID == 3)
			{
				strncpy(customerData[x].streetAddress, newInfo, 21);				
			}
			
			if(fieldID == 4)
			{
				strncpy(customerData[x].city, newInfo, 13);			
			}			
			
			if(fieldID == 5)
			{
				strncpy(customerData[x].state, newInfo, 3);
			}
			
			if(fieldID == 6)
			{
				strncpy(customerData[x].zipCode, newInfo, 6);
			}			
		}	
	}
	
		// If found customer remains true then print a error
	if(foundCustomer == true)
	{
			// Print error
		outputFile << "Error! Attempt to change a non-existent record. " <<
		"Attempt failed!" << endl;
		
			// Prints stars to separate ouput
		for(int x = 0; x < 70; x++)
		{
			outputFile << "*";
		}
		
		outputFile << endl;
	}
}

//****************** END CHANGE CUSTOMER *******************************

//******************* DELETE CUSTOMER **********************************

void deleteCustomer(ifstream &inputFile, ofstream &outputFile, 
                    CustomerType customerData[], int EU)
{
		// Receives - input file, output file, customerData array,
		//            elements used
		// Task - delete a customer from mailing list
		// Returns - array data (deleted customers)
		
		// Current names read in from file
	CustomerType currentFirstName, currentLastName;
	
		// Used to replace name of customer to identify they are deleted
	char eraseCustomer[] = "deleted";
	
		// Read in first and last name from data file
	inputFile >> ws;
	inputFile.getline(currentFirstName.firstName, 13);
	inputFile >> ws;
	inputFile.getline(currentLastName.lastName, 13);
	
		// Cycle through the array to see if this customer exists
	for(int x = 0; x < EU; x++)
	{
		if(strncmp(currentFirstName.firstName, customerData[x].firstName
		   ,13) == 0) 
		{
			if(strncmp(currentLastName.lastName, customerData[x].lastName
			   ,13) == 0)
		    {			
					// Print out customer name removed
				outputFile << "Customer " << customerData[x].firstName <<
				" " << customerData[x].lastName << " successfully removed "
				<< "from the database" << endl;
				
					// Print stars to separate output
				for(int i = 0; i < 70; i++)
				{
					outputFile << "*";
				}
				outputFile << endl;				
				
					// Replace name to "deleted"
				strncpy(customerData[x].firstName, eraseCustomer, 13);
				
				return;
			}			
		}	
		else
		{
				// Print out error if they don't exist
			outputFile << "Error! Attempt to delete a non-existent record. " << 
			"Attempt failed! " << endl;
		
				// Print stars to separate output
			for(int x = 0; x < 70; x++)
			{
				outputFile << "*";
			}
			
			outputFile << endl;	
			return;	
		}
	}
}

//***************** END DELETE CUSTOMER ********************************

//********************* FUNCTION HEADER ********************************

void printHeader(ofstream &Outfile)
{
		// Receives - the output file
		// Task- Prints the output preamble
		// Returns - Nothing
	Outfile << setw(30) << "Alex Knipfer ";
	Outfile << setw(17) << "CSC 24400";
	Outfile << setw(15) << "Section 11" << endl;
	Outfile << setw(30) << "Spring 2015";
	Outfile << setw(20) << "Assignment #6" << endl;
	Outfile << setw(35) << "--------------------------------------";
	Outfile << setw(35) << "--------------------------------------\n\n";
	return;
}

//******************** END OF FUNCTION HEADER **************************

//******************** FUNCTION FOOTER *********************************

void printFooter(ofstream &Outfile)
{
	Outfile << endl;
	Outfile << setw(35) << "--------------------------------" << endl;
	Outfile << setw(35) << "|    END OF PROGRAM OUTPUT     |" << endl;
	Outfile << setw(35) << "--------------------------------" << endl;

	return;
}

//********************** END OF FUNCTION FOOTER ************************


