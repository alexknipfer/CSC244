//******************  PROGRAM IDENTIFICATION  **************************
//*                                                                    *
//*  PROGRAM FILE NAME: program4.cpp  ASSIGNMENT #:  4    Grade: _____ *
//*   	                                                               *
//*  PROGRAM AUTHOR:   ____________________________________            *
//*                             Alex Knipfer                           *
//*                                                                    *
//*  COURSE #:   CSC 24400 11             DUE DATE: March 26, 2015     *
//*                                                                    *
//**********************************************************************

//********************* PROGRAM DESCRIPTION ****************************
//*								                                       *
//*     Process: This program is designed to read a list of data       *
//*     containing a student ID's with their corresponding four test   *
//*     scores. It will then calculate their averages with their       *
//*     grade. The program will sort the data in two different ways:   *
//*     From high to low based on their student ID, then high to low   *
//*     based on their averages.                                       *
//*								                                       *
//*     USER DEFINED						                           *
//*      MODULES:     : readData - read in file with student scores    *
//*                                and student ID                      *
//*                     printData - prints all data from arrays        *
//*                     sortHighLow - sorts arrays based on student ID *
//*                                   from high to low                 *
//*                     calcAverage - Calculates the average of all 4  *
//*                                   student test scores              *
//*                     calcLetterGrade - corresponds letter grade     *
//*                                       based on average             *
//*                     sortAverage - sorts array from high to low     *
//*                                   based on average                 *
//**********************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void printHeader(ofstream &);
void printFooter(ofstream &);
void readData(ifstream &, int [], float [][6], int &, int &, int &);
void printData(ofstream &, int [], float[][6], int, int, int,
		       char[]);
void sortHighLow(int [], float[][6], int);
void calcAverage(float[][6], int, int &);
void calcLetterGrade(char[], float[][6], int);
void sortAverage(int[], float[][6], char[], int);

//******************** START OF MAIN ***********************************

int main()
{
	ofstream outputFile("output.txt");
	ifstream inputFile("DATA4.TXT");

	printHeader(outputFile); 		// print program header to file

	int maxElements = 50;			// set max value for array to 50

		// initialize elements in array to 0
		// keeps track of elements that are used in the array
	int elementsUsed = 0;

		// keeps track of how many rows in student score array
	int rowsUsed = 0;
	
		// keeps track of how many columns in the student score array
	int columnsUsed = 0;

	int studentID[maxElements];		// create array for student ID's

		// create array for test scores
	float studentScore[maxElements][6];
	
		// create array for student letter grade
	char studentGrade[maxElements];

		// Read the data in from input file into two arrays
	readData(inputFile, studentID, studentScore, elementsUsed,
	         rowsUsed, columnsUsed);

		// Print labels for ouput
	outputFile << "The original student data is: " << endl;
	outputFile << "Student ID     " << "Test 1  " << "Test 2  "
			   << "Test 3  " << "Test 4  " << endl;
	outputFile << "------------   " << "------  " << "------  "
	           << "------  " << "------  " << endl;

		// Print student ID and score in two columns below labels
	printData(outputFile, studentID, studentScore, rowsUsed,
	          columnsUsed, elementsUsed, studentGrade);

		// Sort student ID's from highest to lowest
	sortHighLow(studentID, studentScore, elementsUsed);

		// Print labels for output
	outputFile << "The list of students sorted by ID Number ";
	outputFile << "high to low is: " << endl;
	outputFile << "Student ID     " << "Test 1  " << "Test 2  "
			   << "Test 3  " << "Test 4  " << endl;
	outputFile << "------------   " << "------  " << "------  "
	           << "------  " << "------  " << endl;

		// Print Student ID and scores after being sorted
	printData(outputFile, studentID, studentScore, rowsUsed,
	          columnsUsed, elementsUsed, studentGrade);
	          
		// Print labels for output with average and grade
	outputFile << "The list of students with their test average and ";
	outputFile << "course grade is:" << endl;
	outputFile << "                                           " <<
	              "    Test     Course" << endl;
	outputFile << "Student ID     " << "Test 1  " << "Test 2  "
			   << "Test 3  " << "Test 4  " << "Average  " << 
			   "Grade" << endl;
	outputFile << "------------   " << "------  " << "------  "
	           << "------  " << "------  " << "-------  " << 
	           "------" << endl;
	           
		// Calculate average of scores for all students
	calcAverage(studentScore, rowsUsed, columnsUsed);
	
		// Calculate letter grade based on average score
	calcLetterGrade(studentGrade, studentScore, elementsUsed);
		
		// Print data with averages
	printData(outputFile, studentID, studentScore, rowsUsed,
	          columnsUsed, elementsUsed, studentGrade);
	    
	    // Sort averages highest to lowest for all students      
	sortAverage(studentID, studentScore, studentGrade, elementsUsed);
	
		// Print labels for data with averages and grades
	outputFile << "The list of students sorted by test average high ";
	outputFile << "to low is:" << endl;
	outputFile << "                                           " <<
	              "    Test     Course" << endl;
	outputFile << "Student ID     " << "Test 1  " << "Test 2  "
			   << "Test 3  " << "Test 4  " << "Average  " << 
			   "Grade" << endl;
	outputFile << "------------   " << "------  " << "------  "
	           << "------  " << "------  " << "-------  " << 
	           "------" << endl;
	           
		// Print data with averages sorted
	printData(outputFile, studentID, studentScore, rowsUsed,
	          columnsUsed, elementsUsed, studentGrade);

	printFooter(outputFile); // print program footer to file

	return 0;
}

//********************** END OF MAIN ***********************************

//********************** READ DATA *************************************
void readData(ifstream &inputFile, int array1[],
			  float array2[][6], int &EU, int &REU, int &CEU)
{
		// Receives - input file, studentID array, score array, elements
		//            used, rows used, columns used
		// Task - Read in data from input file
		// Returns - Elements used, rows used, columns used and 
		//           array data

	int studentID, x;
	float studentScore;

	inputFile >> studentID;

		// As long as the studentID is a valid number ( > 0) then
		// continue reading from input file
	while(studentID > 0)
	{
			// read student ID's into array
		array1[EU] = studentID;

		for(x = 0; x < 4; x++)
		{
				// read scores
			inputFile >> studentScore;
			
				// store scores in array
			array2[REU][x] = studentScore;
		}
			// increase rows used
		REU++;
		
			//increase elements used
		EU++;

		inputFile >> studentID;
	}
		// set columns equal to x
	CEU = x;
	return;
}

//********************* END READ DATA **********************************

//********************* PRINT DATA *************************************

void printData(ofstream &outputFile, int array1[], float array2[][6],
              int RU, int CU, int EU, char letterGrade[])
{
			// Receives - output file, studentID array, score array
			// Task - Print data from input file into two columns
			// Returns - elements used

		for(int i = 0; i < RU; i++)
		{
			outputFile << setw(16) << left << array1[i];
			
				// print student scores (4 tests)
			for(int j = 0; j < 4; j++)
			{
				outputFile << fixed  << setprecision(1) <<
				setw(8) << array2[i][j];
			}
			
				// if there is 5 columns , print averages
			if(CU == 5)
			{
					// print column 4 (averages)
				for(int y = 4; y < 5; y++)
				{
					outputFile << fixed << setprecision(2) <<
					setw(8) << array2[i][y];			
				}
			}
			
				// if there is more than 4 columns, print a letter grade
			if(CU > 4)
			{
				outputFile << "  " << letterGrade[i];	
			}
					
			outputFile << endl;
		}
		outputFile << endl;
}

//********************* END PRINT DATA *********************************

//********************* SORT HIGH LOW **********************************

void sortHighLow(int array1[], float array2[][6], int EU)
{
		// Receives - studentID array, score array, elements used
		// Task - sort data high to low based on student ID numbers
		// Returns - array data
			
	int temp;   // temporary variable for student scores
	float temp2;	  // temporary variable for student ID's

		// Sort the data from highest to lowest based on student ID
	for(int x = 0; x < EU - 1; x++)
	{
		for(int y = EU - 1; y > x; y--)
		{
			if(array1[y] > array1[y-1])
			{
					// swap student ID's
				temp = array1[y];
				array1[y] = array1[y-1];
				array1[y-1] = temp;

					// swap student scores when sorting ID's
				for(int z = 0; z < 4; z++)
				{
					temp2 = array2[y][z];
		            array2[y][z] = array2[y-1][z];
		            array2[y-1][z] = temp2;
				}
			}
		}
	}
	return;
}

//*********************** END SORT HIGH LOW ****************************

//*********************** SORT AVERAGE *********************************

void sortAverage(int studID[], float studentScores[][6], char grade[],
                  int EU)
{
		// Receives - studentID array, studentScore array, grade array,
		//            elements used
		// Task - sort data high to low based on average score
		// Returns - array data
		
		
		
    float temp;   // temporary variable for student scores
	float temp2;	  // temporary variable for student ID's
	int temp3;
	float temp4;

		// Sort the data from highest to lowest
	for(int x = 0; x < EU - 1; x++)
	{
		for(int y = EU - 1; y > x; y--)
		{
				// compare data in column four (averages in col 4)
			if(studentScores[y][4] > studentScores[y-1][4])
			{
					// Swap student averages
				temp = studentScores[y][4];
				studentScores[y][4] = studentScores[y-1][4];
				studentScores[y-1][4] = temp;
				
					// Swap student ID's
				temp2 = studID[y];
				studID[y] = studID[y-1];
				studID[y-1] = temp2;
				
					// Swap student grades
				temp3 = grade[y];
				grade[y] = grade[y-1];
				grade[y-1] = temp3;
				
					// Swap student score rows
				for(int z = 0; z < 4; z++)
				{
					temp4 = studentScores[y][z];
		            studentScores[y][z] = studentScores[y-1][z];
		            studentScores[y-1][z] = temp4;
				}
			}
		}
	}
	return;
}

//*********************** END SORT AVERAGE *****************************

//*********************** CALCULATE AVERAGE ****************************

void calcAverage(float scoreArray[][6], int rowsUsed, int &colsUsed)
{
		// initialize sum
	float sum = 0;
	
		// initialize average
	float average = 0;
	
		// loop through amounts of rows used (student amount)
	for(int x = 0; x < rowsUsed; x++)
	{
			// reset sum and average everytime it cycles through a 
			// different student
		sum = 0;
		average = 0;
		
			// add student scores in the array to sum
		for(int y = 0; y < 4; y++)
		{
			sum += scoreArray[x][y];
		}
		
			// divide average by four for average of test scores
		average = sum / 4;
		
			// store averages in the fourth column of array
		scoreArray[x][4] = average;
	}
	
		// increase columns used for average column
	colsUsed++;
}

//******************* END CALCULATE AVERAGE ****************************

//******************* CALCULATE LETTER GRADE ***************************

void calcLetterGrade(char letterGrade[], float studentScore[][6], 
                      int EU)
{
		// cycle through all students in array
	for(int x = 0; x < EU; x++)
	{
			// for each student average calculate the corresponding 
			// letter grade from the grade point scale
			
		if(studentScore[x][4] > 89.99)
			letterGrade[x] = 'A';
			
		else if(studentScore[x][4] > 79.99)
			letterGrade[x] = 'B';
			
		else if(studentScore[x][4] > 69.99)
			letterGrade[x] = 'C';
			
		else if(studentScore[x][4] > 59.99)
			letterGrade[x] = 'D';
			
		else
			letterGrade[x] = 'F';			
	}
}

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
	Outfile << setw(20) << "Assignment #4" << endl;
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
