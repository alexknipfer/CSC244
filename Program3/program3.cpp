//******************  PROGRAM IDENTIFICATION  **************************
//*                                                                    *
//*  PROGRAM FILE NAME: program3.cpp  ASSIGNMENT #:  3    Grade: _____ *
//*   	                                                               *
//*  PROGRAM AUTHOR:   ____________________________________            *
//*                             Alex Knipfer                           *
//*                                                                    *
//*  COURSE #:   CSC 24400 11             DUE DATE: March 12, 2015     *
//*                                                                    * 
//**********************************************************************

//********************* PROGRAM DESCRIPTION ****************************
//*																	   *
//*     Process: This program is designed to read a list of data       *
//*     containing a student ID's with their corresponding test score, *
//*     the program will read the data and print out the list three    *
//*     times, first unsorted, then sorted high to low, and then low   *
//*     to high. The program will then print out the lowest and        *
//*     highest grade from the data and print out the average as well  *                                                 
//*																	   *
//*     USER DEFINED											       *
//*      MODULES:     : readData - reads student ID and grade from     *
//*                                input file						   *
//*                     sortHighLow - sorts the test scores and        *
//*                                 corresponding ID's from high to low*
//*                     sortLowHigh - sorts the test scores and        *
//*                                corresponding ID's from low to high *
//*                     calcAverage - Calculates the average score     *
//*                     printData - prints the data from the input     *
//*                                 file, this includes the student ID *
//*                                 and their test score               *
//**********************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void printHeader(ofstream &);
void printFooter(ofstream &);
void readData(ifstream &, int [], float [], int &);
void printData(ofstream &, int [], float [], int);
float calcAverage(float[], int);
void sortHighLow(int[], float[], int);
void sortLowHigh(int[], float[], int);

//******************** START OF MAIN ***********************************

int main()
{
	ofstream outputFile("output.txt");
	ifstream inputFile("DATA3.TXT");
	
	printHeader(outputFile); 		// print program header to file
	
	int maxElements = 50;			// set max value for array to 50
	
		// initialize elements in array to 0
		// keeps track of elements that are used in the array
	int elementsUsed = 0;			
	
	int studentID[maxElements];		// create array for student ID's
	
	float studentScore[maxElements];	// create array for test scores
	
	float minValue, maxValue;
	
	int lowStudID, highStudID;
	
	
	float scoreAverage;
	
		// Read the data in from input file into two arrays
	readData(inputFile, studentID, studentScore, elementsUsed);
	
		// Print labels in two columns for student ID and test score
	outputFile << "The original list of test scores is: " << endl;
	outputFile << endl;
	outputFile << setw(15) << left << "Student ID #";
	outputFile << "Test Score" << endl;
	
		// Print student ID and score in two columns below labels
	printData(outputFile, studentID, studentScore, elementsUsed);
	
		// Sort data from high grade to low grade
	sortHighLow(studentID, studentScore, elementsUsed);
	
	minValue = studentScore[elementsUsed - 1];     // store lowest test score
	maxValue = studentScore[0];   // store highest score
	
		// store lowest and highest corresponding student ID's
	lowStudID = studentID[elementsUsed - 1];   
	highStudID = studentID[0];
	
		// Print labels in two columns for student ID and test score
	outputFile << "The test scores sorted highest to lowest are: " 
			   << endl;
	outputFile << endl;
	outputFile << setw(15) << left << "Student ID #";
	outputFile << "Test Score" << endl;
	
		// Print student ID and score in two columns below labels
	printData(outputFile, studentID, studentScore, elementsUsed);
	
		// Sort data from low grade to high grade
	sortLowHigh(studentID, studentScore, elementsUsed);
	
		// Print labels in two columns for student ID and test score
	outputFile << "The student ID's sorted lowest to highest are: " 
			   << endl;
	outputFile << endl;
	outputFile << setw(15) << left << "Student ID #";
	outputFile << "Test Score" << endl;
		
		// Print student ID and score in two columns below labels
	printData(outputFile, studentID, studentScore, elementsUsed);		
	
		// Print lowest score from grades
	outputFile << "The lowest test score was " << 
				   minValue << " achieved by student #" <<
				   lowStudID << endl << endl;	
		
		// Print highest score from grades
	outputFile << "The highest test score was " << 
				   maxValue << " achieved by student #" <<
				   highStudID << endl << endl;	
				  
		// Calculate average and store in scoreAverage
	scoreAverage = calcAverage(studentScore, elementsUsed);		   
	
		// Print the test score average
	outputFile << "The average test score for the group is: " << 
	              scoreAverage;
	
	printFooter(outputFile); // print program footer to file
	
	return 0;
}

//********************** END OF MAIN ***********************************

//********************** READ DATA *************************************
void readData(ifstream &inputFile, int array1[], float array2[], 
			  int &EU)
{
		// Receives - input file, studentID array, score array, elements
		//            used
		// Task - Read in data from input file
		// Returns - Elements used and array data
		
	int studentID;
	float studentScore;
	
	inputFile >> studentID;
	
		// As long as the studentID is a valid number ( > 0) then 
		// continue reading from input file
	while(studentID > 0)
	{
		array1[EU] = studentID;
		
		inputFile >> studentScore;
		array2[EU] = studentScore;	// storing scores into array
		
		EU++;
		
		inputFile >> studentID;
	}
	return;
}

//********************* END READ DATA **********************************

//********************* PRINT DATA *************************************

void printData(ofstream &outputFile, int array1[], float array2[], 
              int EU)
{	
		// Receives - output file, studentID array, score array 

		// Task - Print data from input file into two columns
		// Returns - elements used
		
		// cycle through the number of elements used in the array
		// and print the values from array
	for(int x = 0; x < EU; ++x)
	{
			// create spacing to align under middle of label
		outputFile << "   ";
		
			// print the values to the left with set spacing of 15
		outputFile << setw(15) << left << array1[x];
		
			// print test scores with 2 decimals
		outputFile << fixed << setprecision(1) << array2[x];
		
		outputFile << endl;
	}
	outputFile << endl;
}

//********************* END PRINT DATA *********************************

//********************* CALCULATE AVERAGE ******************************

float calcAverage(float array2[], int EU)
{
		// Receives - score array, elements used
		// Task - Calculate the highest test score from data
		// Returns - average
		
	float average = 0.00;	// initialize average
	
		// cycle through score array
	for(int x = 0; x < EU; x++)
	{
			// add values to average to keep total
		average += array2[x];
	}
	
		// divide by number of array elements to calculate average
	average = average / EU;
	
	return average;
}

//********************* END CALCULATE AVERAGE **************************

//********************* SORT HIGH TO LOW *******************************

void sortHighLow(int array1[], float array2[], int EU)
{
		// Receives - studentID array and score array
		// Task - Sort the data from high to low (based on test score)
		// Returns - data from both arrays
		
	float temp;   // temporary variable for student scores
	int temp2;	  // temporary variable for student ID's
	
		// Sort the data from highest to lowest
	for(int x = 0; x < EU - 1; x++)
	{
		for(int y = EU - 1; y > x; y--)
		{
			if(array2[y] > array2[y-1])
			{
					// Swap student scores when sorting
				temp = array2[y];
				array2[y] = array2[y-1];
				array2[y-1] = temp;
				
					// Swap student ID's to match with correct score
				temp2 = array1[y];
				array1[y] = array1[y-1];
				array1[y-1] = temp2;
			}
		}
	}	
	return;
}

//********************* END SORT HIGHT TO LOW **************************

//********************* SORT LOW TO HIGH *******************************

void sortLowHigh(int array1[], float array2[], int EU)
{
		// Receives - studentID array and score array
		// Task - Sort the data from low to high (based on student ID)
		// Returns - data from both arrays
		
	int temp;   // temporary variable for student scores
	float temp2;    // temporary variable for student ID's
	
		// Sort the data from lowest to highest
	for (int x = 0 ; x < EU - 1; x++)
    {
		int Max = x;
		
		for(int y = EU - 1; y > x; y--)
		{
			if(array1[y] < array1[Max])
			{
				Max = y;
			}
		}
			// Swap student scores when sorting
		temp = array1[x];
		array1[x] = array1[Max];
		array1[Max] = temp;
			// Swap student ID's to match with correct score
		temp2 = array2[x];
		array2[x] = array2[Max];
		array2[Max] = temp2;
    }
}

//********************* END SORT LOW TO HIGH ***************************

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
	Outfile << setw(20) << "Assignment #2" << endl;
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
