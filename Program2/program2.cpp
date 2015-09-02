//******************  PROGRAM IDENTIFICATION  **************************
//*                                                                    *
//*  PROGRAM FILE NAME: program2.cpp  ASSIGNMENT #:  2    Grade: _____ *
//*   	                                                               *
//*  PROGRAM AUTHOR:   ____________________________________            *
//*                             Alex Knipfer                           *
//*                                                                    *
//*  COURSE #:   CSC 24400 11             DUE DATE: February 26, 2015  *
//*                                                                    * 
//**********************************************************************

//********************* PROGRAM DESCRIPTION ****************************
//*																	   *
//*     Process: This program is designed to read a list of data       *
//*     containing a student ID's with their corresponding test score, *
//*     the program will read the data and print out the student ID's  *
//*     for the grade their received (A, B, C, D, F and below). The    *
//*     lowest, highest, and average scores will be calculated as well *
//*     and printed.                                                   *
//*																	   *
//*     USER DEFINED											       *
//*      MODULES:     : readData - reads student ID and grade from     *
//*                                input file						   *
//*                     gradeA - Searches through grades to find all   *
//*									   A's in the data                 *
//*                     gradeB - Searches through grades to find all   *
//*                                    B's in the data                 *
//*                     gradeC - Searches through grades to find all   *
//*                                    C's in the data                 *
//*                     gradeD - Searches through grades to find all   *
//*                                    D's in the data                 *
//*                     gradeF - Searches through grades to find all   *
//*                                 F's and below in the data          *
//*                     lowestScore - calculates the lowest score      *
//*                     highestScore - calculates the highest score    *
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
void printData(ofstream &, int [], float [], int &);
void gradeA(ofstream &, int [], float [], float, int);
void gradeB(ofstream &, int [], float [], float, float, int);
void gradeC(ofstream &, int [], float [], float, float, int);
void gradeD(ofstream &, int [], float [], float, float, int);
void gradeF(ofstream &, int [], float [], float, int);
int lowestScore(float[], int);
int highestScore(float[], int);
float calcAverage(float[], int);

//******************** START OF MAIN ***********************************

int main()
{
	ofstream outputFile("output.txt");
	ifstream inputFile("DATA2.TXT");
	
	printHeader(outputFile); 		// print program header to file
	
	int maxElements = 50;			// set max value for array to 50
	
		// initialize elements in array to 0
		// keeps track of elements that are used in the array
	int elementsUsed = 0;			
	
	int studentID[maxElements];		// create array for student ID's
	
	float studentScore[maxElements];	// create array for test scores
	
	int minValue;
	
	int maxValue;
	
	float scoreAverage;
	
		// Read the data in from input file into two arrays
	readData(inputFile, studentID, studentScore, elementsUsed);
	
		// Print labels in two columns for student ID and test score
	outputFile << "The original list of test scores is: " << endl;
	outputFile << setw(15) << left << "Student ID #";
	outputFile << "Test Score" << endl;
	
		// Print student ID and score in two columns below labels
	printData(outputFile, studentID, studentScore, elementsUsed);
	
		// Find grades below 90 (A) from array
	gradeA(outputFile, studentID, studentScore, 90.0, elementsUsed);
	
		// Find grades between 80-89 (B) from array
	gradeB(outputFile, studentID, studentScore, 80.0, 89.99, 
	       elementsUsed); 
	       
		// Find grades between 70-79 (C) from array
	gradeC(outputFile, studentID, studentScore, 70.0, 79.99, 
	       elementsUsed);	

		// Find grades between 60-69 (D) from array
	gradeD(outputFile, studentID, studentScore, 60.0, 69.99, 
	       elementsUsed);	
	       
		// Find grades 60 and below (F) from array
	gradeF(outputFile, studentID, studentScore, 60.0, elementsUsed);
	
		// Calculate lowest score and store in minValue
	minValue = lowestScore(studentScore, elementsUsed);
	
		// Print lowest score from grades
	outputFile << "The lowest test score was " << 
				   studentScore[minValue] << " achieved by student #" <<
				   studentID[minValue] << endl << endl;
	
		// Calculate highest score and store in maxValue
	maxValue = highestScore(studentScore, elementsUsed);	
		
		// Print highest score from grades
	outputFile << "The highest test score was " << 
				   studentScore[maxValue] << " achieved by student #" <<
				   studentID[maxValue] << endl << endl;	
				  
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
		// Returns - Elements used
		
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
              int &EU)
{	
		// Receives - output file, studentID array, score array, 
		//            elements used
		// Task - Print data from input file into two columns
		// Returns - elements used
		
		// cycle through the number of elements used in the array
		// and print the values from array
	for(int x = 0; x < EU; ++x)
	{
			// print the values to the left with set spacing of 15
		outputFile << setw(15) << left << array1[x];
		
			// print test scores with 2 decimals
		outputFile << fixed << setprecision(2) << array2[x];
		
		outputFile << endl;
	}
	outputFile << endl;
}

//********************* END PRINT DATA *********************************

//********************* GRADE A ****************************************

void gradeA(ofstream &outputFile, int array1[], float array2[],
            float grade, int EU)
{	
		// Receives - output file, studentID array, score array,
		//            grade, elements used
		// Task - Find grades of 90+ (A) and print corresponding 
		//        student ID
		// Returns - Nothing
		
	outputFile << "Students receiving a grade of A are: ";
	
		// Go through score array and print out student ID's based on  
		// grades above 90
	for(int x = 0; x < EU; x++)
	{		
			// Check to see if current array value is > 90
		if(array2[x] >= grade)
		{
			outputFile << array1[x] << " ";
		}
	}
	
	outputFile << endl;
}

//********************* END GRADE A ************************************

//********************* GRADE B ****************************************

void gradeB(ofstream &outputFile, int array1[], float array2[],
            float minGrade, float maxGrade, int EU)
{	
		// Receives - output file, studentID array, score array, 
		//            min grade, max grade, elements used
		// Task - Find grades between 80-89 and prints corresponding
		//        student ID
		// Returns - Nothing
		
	outputFile << "Students receiving a grade of B are: ";
	
		// Go through score array and print out student ID's based on 
		// grades between 80-89
	for(int x = 0; x < EU; x++)
	{	
			// check to see if grade is between 80-89
		if(array2[x] >= minGrade && array2[x] <= maxGrade)
		{
			outputFile << array1[x] << " ";
		}
	}
	
	outputFile << endl;
}

//********************* END GRADE B ************************************

//********************* GRADE C ****************************************

void gradeC(ofstream &outputFile, int array1[], float array2[],
            float minGrade, float maxGrade, int EU)
{	
		// Receives - output file, studentID array, score array,
		//            min grade, max grade, elements used
		// Task - Find grades between 70-79 and prints corresponding
		//        student ID
		// Returns - Nothing
		
	outputFile << "Students receiving a grade of C are: ";
	
		// Go through score array and print out student ID's based on 
		// grades between 70-79
	for(int x = 0; x < EU; x++)
	{		
			// check to see if grade is between 70-79
		if(array2[x] >= minGrade && array2[x] <= maxGrade)
		{
			outputFile << array1[x] << " ";
		}
	}
	
	outputFile << endl;
}

//********************* END GRADE C ************************************

//********************* GRADE D ****************************************

void gradeD(ofstream &outputFile, int array1[], float array2[],
            float minGrade, float maxGrade, int EU)
{
		// Receives - output file, studentID array, score array,
		//            min grade, max grade, elements used
		// Task - Find grades between 60-69 and prints corresponding
		//        student ID
		// Returns - Nothing
		
	outputFile << "Students receiving a grade of D are: ";
	
		// Go through score array and print out student ID's based on 
		// grades between 60-69	
	for(int x = 0; x < EU; x++)
	{		
			// check to see if grade is between 60-69
		if(array2[x] >= minGrade && array2[x] <= maxGrade)
		{
			outputFile << array1[x] << " ";
		}
	}
	
	outputFile << endl;
}

//********************* END GRADE D ************************************

//********************* GRADE F ****************************************

void gradeF(ofstream &outputFile, int array1[], float array2[],
            float grade, int EU)
{
		// Receives - output file, studentID array, score array,
		//            grade, elements used
		// Task - Find grades between 50 and below, prints corresponding
		//        student ID
		// Returns - Nothing
			
	outputFile << "Students receiving a grade of F are: ";
	
		// Go through score array and print out student ID's based on 
		// grades 50 and below
	for(int x = 0; x < EU; x++)
	{		
		if(array2[x] < grade)
		{
			outputFile << array1[x] << " ";
		}
	}
	
	outputFile << endl;
	outputFile << endl;
}

//********************* END GRADE F ************************************

//********************* LOWEST SCORE ***********************************

int lowestScore(float array2[], int EU)
{
		// Receives - student score array, elements used
		// Task - Calculate lowest test score from data
		// Returns - minLoc: location in array that holds lowest score
		
	int minLoc = 0;			// initialize minLoc
	
		// initialize minVal to test values in array
		// compare to a value of a score that is too high (105)
	float minVal = 105.0;	
	
		// cycle through score array to find lowest score in array
	for(int x = 0; x < EU; x++)
	{
			// check to see if minVal is greater than current score
		if(minVal > array2[x])
		{
				// set minVal = to that value
			minVal = array2[x];		
			
				// set current  location in array to x
			minLoc = x;				
		}
	}
	
	return minLoc;
}

//********************* END LOWEST SCORE *******************************

//********************* HIGHEST SCORE **********************************

int highestScore(float array2[], int EU)
{
		// Receives - student score array, elements used
		// Task - Calculate highest score from data
		// Returns - maxLoc: location in array that holds highest score
		
	int maxLoc = 0;		// initialize maxLoc
	
	float maxVal = 0.0;	// initialize maxVal
	
		// cycle through score array to find highest value in array
	for(int x = 0; x < EU; x++)
	{
			// check to see if maxVal is greater than current score
		if(maxVal < array2[x])
		{
				// set score = to max value
			maxVal = array2[x];
			
				// set current location in array to x
			maxLoc = x;
		}
	}
	
	return maxLoc;
}

//********************* END HIGHEST SCORE ******************************

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
