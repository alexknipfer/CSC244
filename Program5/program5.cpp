//******************  PROGRAM IDENTIFICATION  **************************
//*                                                                    *
//*  PROGRAM FILE NAME: program5.cpp  ASSIGNMENT #:  5    Grade: _____ *
//*   	                                                               *
//*  PROGRAM AUTHOR:   ____________________________________            *
//*                             Alex Knipfer                           *
//*                                                                    *
//*  COURSE #:   CSC 24400 11             DUE DATE: April 09, 2015     *
//*                                                                    *
//**********************************************************************

//********************* PROGRAM DESCRIPTION ****************************
//*								                                       *
//*     Process: This program is designed to read a list of data       *
//*     containing student names with their corresponding four test    *
//*     scores. It will then calculate their averages with their       *
//*     grade. The program print the original data then sort and print *
//*     the data by sorting their last names from A to Z and sorting   *
//*     their average from high to low                                 *
//*								                                       *
//*     USER DEFINED						                           *
//*      MODULES:     : readData - read in file with student scores    *
//*                                and student ID                      *
//*                     printData - prints all data from arrays        *
//*                     sortLastName - sorts arrays based on last name *
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
#include <cstring>

using namespace std;

void printHeader(ofstream &);
void printFooter(ofstream &);
void readData(ifstream &, char *[], char *[], float[][6],
              int &, int &, int &);
void printData(ofstream &, char *[], char *[], float[][6], int,
                int, int, char[]);                
void sortLastName(char *[], char *[], float[][6], int, int, int);
void calcAverage(float[][6], int, int &);
void calcLetterGrade(char [], float[][6], int);
void sortAverage(float[][6], char [], int, char *[], char *[]);

//******************** START OF MAIN ***********************************

int main()
{
	ofstream outputFile("output.txt");
	ifstream inputFile("DATA5.TXT");

	printHeader(outputFile); 		// print program header to file

	int maxElements = 50;			// set max value for array to 50

		// initialize elements in array to 0
		// keeps track of elements that are used in the array
	int elementsUsed = 0;
	
	
		// keeps track of rows in score array
	int rowsUsed = 0;
	
		// keeps track of columns in score array
	int columnsUsed = 0;

		// initialize pointer array to store first names
	char *firstName[maxElements] = {0};
	
		// initialize pointer array to store last names
	char *lastName[maxElements] = {0};
	
		// create array for student scores
	float studentScore[maxElements][6];
	
		// create array for student letter grades
	char studentGrade[maxElements];

		// Read the data in from input file into two arrays
	readData(inputFile, firstName, lastName, studentScore, rowsUsed, 
	         columnsUsed, elementsUsed);
	         
		// Print labels for output
	outputFile << "The original student data is: " << endl;
	outputFile << "       Student Name" << endl;
	outputFile << "   First        " << "Last            " << "Test 1  "
			   << "Test 2  " << "Test 3  " << "Test 4" << endl;
	outputFile << " ----------    " << "----------       " << "------  "
	           << "------  " << "------  " << "------  " << endl;	   
	                 
		// Print original data from file
	printData(outputFile, firstName, lastName, studentScore, rowsUsed,
	          columnsUsed, elementsUsed, studentGrade);
	      
		// create spacing so output doesn't spill to next page			
	for(int x = 0; x < 10; x++)
	{
		outputFile << endl;
	}
	          
	   // Print labels for output
	outputFile << "The list of students sorted A thru Z " << 
			      "by Last Name is: " << endl;
	outputFile << "       Student Name" << endl;
	outputFile << "   First        " << "Last            " << "Test 1  "
			   << "Test 2  " << "Test 3  " << "Test 4" << endl;
	outputFile << " ----------    " << "----------       " << "------  "
	           << "------  " << "------  " << "------  " << endl;	            
	        
	   // Sort arrays based on student last name
	sortLastName(firstName, lastName, studentScore, rowsUsed,
	             columnsUsed, elementsUsed);
	             	          
	   // Print data after being sorted          	          
	printData(outputFile, firstName, lastName, studentScore, rowsUsed,
	          columnsUsed, elementsUsed, studentGrade);
	          
	   // create spacing so output doesn't spill to next page	       
	for(int x = 0; x < 14; x++)
	{
		outputFile << endl;
	}	          
	          
	  // Print labels for output
	outputFile << "The list of students with their test average and " << 
			      "course grade is: " << endl;
	outputFile << "       Student Name" << endl;
	outputFile << "   First        " << "Last            " << "Test 1  "
			   << "Test 2  " << "Test 3  " << "Test 4  " << "Average  " 
			   << "Grade" << endl;
	outputFile << " ----------    " << "----------       " << "------  "
	           << "------  " << "------  " << "------  " << 
	           "-------  " << "------" << endl;	
	                     
		// Calculate average of all student test scores
	calcAverage(studentScore, rowsUsed, columnsUsed);
	
		// Calculate a letter grade based on average
	calcLetterGrade(studentGrade, studentScore, elementsUsed);
	   
	   // Print data after calculating average and letter grade       
	printData(outputFile, firstName, lastName, studentScore, rowsUsed,
	          columnsUsed, elementsUsed, studentGrade);
	          
		// create spacing so output doesn't spill to next page		          
	for(int x = 0; x < 14; x++)
	{
		outputFile << endl;
	}	          
	 
	   // Print labels for output          
	outputFile << "The list of students sorted by test average high " << 
			      "to low is: " << endl;
	outputFile << "       Student Name" << endl;
	outputFile << "   First        " << "Last            " << "Test 1  "
			   << "Test 2  " << "Test 3  " << "Test 4  " << "Average  " 
			   << "Grade" << endl;
	outputFile << " ----------    " << "----------       " << "------  "
	           << "------  " << "------  " << "------  " << 
	           "-------  " << "------" << endl;		          
	          
		// Sort arrays based on student average
	sortAverage(studentScore, studentGrade, elementsUsed, firstName,
	            lastName);
	            
	    // Print data after being sorted by average      
	printData(outputFile, firstName, lastName, studentScore, rowsUsed,
	          columnsUsed, elementsUsed, studentGrade);	          	          	          
	          
	return 0;
}

//********************** END OF MAIN ***********************************


//********************** READ DATA *************************************
void readData(ifstream &inputFile, char *firstName[], 
              char *lastName[], float studScore[][6], int &RU, 
              int &CU, int &EU)
{
		// Receives - input file, firstName and lastName pointer arrays,
		//            score array, rows used, columns used, elements 
		//            used
		// Task - Read in data from input file
		// Returns - array data, rows used, columns used, elements used
	
	float studentScore = 0.0;
		
		// initialize character arrays for first and last names
	char fName[15];
	char lName[15];
	
		// intialize character pointers for first and last names
	char *newPtr = NULL;
	char *newPtr2 = NULL;
	
	int count = 0;
	int x;
	
		// get first line of characters from file and store in fName
	inputFile.getline(fName, 15);
	
		// continue reading in the file until you hit "no" or "more"
	while((strncmp(fName,"No",2)!=0) && (strncmp(lName,"More",4)!=0))
	{
			// store the name read into firstName array
		newPtr = new char[15];
		strcpy(newPtr, fName);
		firstName[count] = newPtr;
		
			// get the next name in the file (last name)
		inputFile.getline(lName, 15);	
		
			// store the last name read in to the lastName array
		newPtr2 = new char[15];
		strcpy(newPtr2, lName);
		lastName[count] = newPtr2;	
		
			// read student scores from file into studScore array
		for(x = 0; x < 4; x++)
		{
			inputFile >> studentScore;
			
			studScore[RU][x] = studentScore;
		}
		
			// increase row and elements used count
		RU++;
		EU++;
		
			// ignore line
		inputFile.ignore();
		
			// read in next name from file
		inputFile.getline(fName, 15);
				
			// increment count for use with first and last name arrays
		count++;

	}
		// increase column count
	CU = x;
	return;	
}

//********************* END READ DATA **********************************

//********************* PRINT DATA *************************************

void printData(ofstream &outputFile, char *firstName[], char *lastName[], 
                float studScore[][6], int RU, int CU, int EU,
                char letterGrade[])
{
		// Receives - output file, firstName and lastName pointer arrays,
		//            score array, rows used, columns used, elements 
		//            used, grade array
		// Task - Print data from input file
		// Returns - array data


	for(int i = 0; i < RU; i++)
	{
			// print first and last names
		outputFile << " " << firstName[i];
		outputFile << " " << lastName[i];
			
			// print student scores (4 tests)
		for(int j = 0; j < 4; j++)
		{
			outputFile << fixed  << setprecision(2) <<
			setw(8) << studScore[i][j];
		}
			
			// if there is 5 columns , print averages
		if(CU == 5)
		{
				// print column 4 (averages)
			for(int y = 4; y < 5; y++)
			{
				outputFile << fixed << setprecision(2) <<
				setw(8) << studScore[i][y];			
			}
		}	
			
			// if there is more than 4 columns, print a letter grade
		if(CU > 4)
		{
			outputFile << "     " << letterGrade[i];	
		}			
								
		outputFile << endl;
	}
	outputFile << endl;
}

//********************* END PRINT DATA *********************************

//********************* SORT LAST NAME *********************************

void sortLastName(char *firstName[], char *lastName[],
                  float studScore[][6], int RU, int CU, int EU)
{
		// Receives - first name and last name pointer arrays, score
		//            array, rows used, columns used, elements used
		// Task - Sort arrays based on student last names
		// Returns - array data
		
		// intitialize temp variables for swapping
	char *temp = NULL;
	char *temp2 = NULL;
	float scoreTemp;
	
	for(int x = 0; x < EU - 1; x++)
	{
		for(int y = EU - 1; y > x; y--)
		{
				// compare last names
			if(strcmp(lastName[y], lastName[y-1]) < 0)
			{
					// swap last names
				temp = lastName[y];
				lastName[y] = lastName[y-1];
				lastName[y-1] = temp;
				
					// swap first names
				temp2 = firstName[y];
				firstName[y] = firstName[y-1];
				firstName[y-1] = temp2;
				
					// swap student scores
				for(int z = 0; z < 4; z++)
				{
					scoreTemp = studScore[y][z];
		            studScore[y][z] = studScore[y-1][z];
		            studScore[y-1][z] = scoreTemp;
				}
			}
	    }  
	}
	
}

//******************** END SORT LAST NAME ******************************

//******************** CALCULATE AVERAGE *******************************

void calcAverage(float scoreArray[][6], int rowsUsed, int &colsUsed)
{
		// Receives - score array, rows used, columns used
		// Task - calculate student test score averages
		// Returns - array data, columns used
		
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
		// Receives - letter grade array, score array, elements used
		// Task - calculate letter grade based on average
		// Returns - array data		
		
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

//******************** END LETTER GRADE ********************************

//*********************** SORT AVERAGE *********************************

void sortAverage(float studentScores[][6], char grade[],
                  int EU, char *firstName[], char *lastName[])
{
		// Receives - score array, grade array, elements used,
		//            first and last name pointer arrays
		// Task - sort arrays based on student average
		// Returns - array data

		// temp variables for swapping
    float scoreTemp1;
    float scoreTemp2;
    int gradeTemp;
    char *lNameTemp;
    char *fNameTemp;
    

		// Sort the data from highest to lowest
	for(int x = 0; x < EU - 1; x++)
	{
		for(int y = EU - 1; y > x; y--)
		{
				// compare data in column four (averages in col 4)
			if(studentScores[y][4] > studentScores[y-1][4])
			{
					// Swap student averages
				scoreTemp1 = studentScores[y][4];
				studentScores[y][4] = studentScores[y-1][4];
				studentScores[y-1][4] = scoreTemp1;
				
					// Swap student grades
				gradeTemp = grade[y];
				grade[y] = grade[y-1];
				grade[y-1] = gradeTemp;
				
					// Swap student last names
				lNameTemp = lastName[y];
				lastName[y] = lastName[y-1];
				lastName[y-1] = lNameTemp;
				
					// Swap student first names
				fNameTemp = firstName[y];
				firstName[y] = firstName[y-1];
				firstName[y-1] = fNameTemp;
				
					// Swap student score rows
				for(int z = 0; z < 4; z++)
				{
					scoreTemp2 = studentScores[y][z];
		            studentScores[y][z] = studentScores[y-1][z];
		            studentScores[y-1][z] = scoreTemp2;
				}
			}
		}
	}
	return;
}

//*********************** END SORT AVERAGE *****************************


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
	Outfile << setw(20) << "Assignment #5" << endl;
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

