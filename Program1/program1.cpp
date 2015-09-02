//******************  PROGRAM IDENTIFICATION  **************************
//*                                                                    *
//*  PROGRAM FILE NAME: program1.cpp  ASSIGNMENT #:  1    Grade: _____ *
//*   	                                                               *
//*  PROGRAM AUTHOR:   ____________________________________            *
//*                             Alex Knipfer                           *
//*                                                                    *
//*  COURSE #:   CSC 24400 11             DUE DATE: February 12, 2015  *
//*                                                                    * 
//**********************************************************************

//********************* PROGRAM DESCRIPTION ****************************
//*																	   *
//*     Process: This program is designed to read a list of data       *
//*     containing a type of vehicle and the amount of hours they were *
//*     parking at Missouri Western University. It will then print out *
//*     the ticket for their parking fee on campus based on the        *
//*     University's prices for parking for a particular vehicle.      *
//*																	   *
//*     USER DEFINED											       *
//*      MODULES:     : readData - reads the vehicle type and amount   *
//*                                of hours they were parked           *
//*                     calculateFee - calculate their parking fee     *
//*									   based on the school prices      *
//*                     printData - prints the tickets of the vehicles *
//*                                 for the parking fees they owe      *
//*                                 based on their time parked         *
//**********************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

void printHeader(ofstream &);
void printFooter(ofstream &);
void readData(ifstream &, char &, int &, int &);
void calculateFee(char, int, int, double &, int &);
void printData(char, int, int, double &, int &, ofstream &);

//******************** START OF MAIN ***********************************

int main()
{
	ofstream outputFile("output.txt");
	ifstream inputFile("DATA1.TXT");
	
	char customerCategory = 'a';
	int timeIn;
	int timeOut;
	int totalTime = 0;		// initialize total time to 0
	double parkFee = 0.00;  // initialize parking fee to 0
		
	printHeader(outputFile); // print program header to file
	
	readData(inputFile, customerCategory, timeIn, timeOut);
	
		// as long as the vehicle type doesn't consist of 'x' in the 
		// data file, calculate the fee, print the data, then read then
		// continue reading file
	while(customerCategory != 'X')
	{
			// calcuate current price based on type of car and hours
			// read in from file
		calculateFee(customerCategory, timeIn, timeOut, parkFee, 
						totalTime);
			// print ticket based on type of car, their hours parked,
			// and the parking fee calculated
		printData(customerCategory, timeIn, timeOut, parkFee, 
						totalTime, outputFile);
			// read data from file to get vehicle type, time in, and
			// time out
        readData(inputFile, customerCategory, timeIn, timeOut);
	}
	
	printFooter(outputFile); // print program footer to file
	
	return 0;
}

//********************** END OF MAIN ***********************************

//********************** READ DATA *************************************

void readData(ifstream &inputFile, 
			  char &customerCategory, int &timeIn, int &timeOut)
{
		// Receives- input file, customer category, time in, time out
		// Task - Read the data from input file
		// Returns - customer category, time in , time out
	
	inputFile >> customerCategory;
		
		// if the value reading in for vehicle type is not a 'x', then
		// read in time in and time out
	if(customerCategory != 'X')
	{
		inputFile >> timeIn;
		inputFile >> timeOut;
	}
}

//************************ END OF READ DATA ****************************

//************************ CALCULATE FEE *******************************

void calculateFee(char customerCategory, int timeIn, int timeOut, 
				  double &parkFee, int &totalTime)
{
		// Receives - customer cateogory, time in , time out, 
		//			  parking fee (0), total time (0)
		// Task - calculate parking fee based on hours parked on campus
		// Returns - parking fee and total time
	
	int placeHolderTime;
	int remainingMin;
	parkFee = 0.00;
	
	totalTime = timeOut - timeIn;
	placeHolderTime = totalTime;	// keep value of total time stored
	totalTime = totalTime / 60;		// calculates amount of hours parked
	
	remainingMin = placeHolderTime % 60; // calculate minutes
	
		// all remaining minutes round to the next hour, so this adds
		// one to the hour if there are any minutes (ie. rounds hour up)
	if(remainingMin > 0)
	{
		totalTime += 1;
	}
	
		// if the vehicle type is a car, calculate fees based on 'car'
		// any other vehicle type will not be calculated here
		// all fees are based on university pricing
	if(customerCategory == 'C')
	{
			// add parking fee of .20 for 1 hour
		if(totalTime == 1)
		{
			parkFee += 0.20;
		}
	  
			// add parking fee of .40 for 2 hours
		else if(totalTime == 2)
		{
			parkFee += 0.40;
		}
			
			// add parking fee of .55 for 3 hours
		else if(totalTime == 3)
		{
			parkFee += 0.55;
		}
	
			// add parking fee of .70 for 4 hours
		else if(totalTime == 4)
		{
			parkFee += 0.70;
		}
	
			// add parking fee of .85 for 5 hours
		else if(totalTime == 5)
		{
			parkFee += 0.85;
		}
	
			// add parking fee of .90 for 6 hours
		else if(totalTime == 6)
		{
			parkFee += 0.90;
		}
	
			// add parking fee of .95 for 7 hours
		else if(totalTime == 7)
		{
			parkFee += 0.95;
		}
		
			// add parking fee of 1.00 for 8 hours
		else if(totalTime == 8)
		{
			parkFee += 1.00;
		}
		
			// add parking fee of 1.05 for 9 hours
		else if(totalTime == 9)
		{
			parkFee += 1.05;
		}
		
			// add parking fee of 1.10 for 10 hours
		else if(totalTime == 10)
		{
			parkFee += 1.10;
		}
		
			// add parking fee of 1.15 for 11 hours
		else if(totalTime == 11)
		{
			parkFee += 1.15;
		}
		
			// add parking fee of 1.20 for 12 hours
		else if(totalTime == 12)
		{
			parkFee += 1.20;
		}
		
			// add parking fee of 1.25 for 13 hours
		else if(totalTime == 13)
		{
			parkFee += 1.25;
		}
		
			// add parking fee of 1.30 for 14 hours
		else if(totalTime == 14)
		{
			parkFee += 1.30;
		}
		
			// add parking fee of 1.35 for 15 hours
		else if(totalTime == 15)
		{
			parkFee += 1.35;
		}
	}

		// if the vehicle type is a truck, calculate based on 'truck'
		// any other vehicle type will not be calculated here
		// all fees are based on university pricing
	if(customerCategory == 'T')
	{
			// add parking fee of .40 for 1 hour
		if(totalTime == 1)
		{
			parkFee += 0.40;
		}
		
			// add parking fee of .65 for 2 hours
		else if(totalTime == 2)
		{
			parkFee += 0.65;
		}
		
			// add parking fee of .90 for 3 hours
		else if(totalTime == 3)
		{
			parkFee += 0.90;
		}
		
			// add parking fee of 1.15 for 4 hours
		else if(totalTime == 4)
		{
			parkFee += 1.15;
		}
		
			// add parking fee of 1.25 for 5 hours
		else if(totalTime == 5)
		{
			parkFee += 1.25;
		}
		
			// add parking fee of 1.35 for 6 hours
		else if(totalTime == 6)
		{
			parkFee += 1.35;
		}
		
			// add parking fee of 1.45 for 7 hours
		else if(totalTime == 7)
		{
			parkFee += 1.45;
		}
		
			// add parking fee of 1.55 for 8 hours
		else if(totalTime == 8)
		{
			parkFee += 1.55;
		}
		
			// add parking fee of 1.65 for 9 hours
		else if(totalTime == 9)
		{
			parkFee += 1.65;
		}
		
			// add parking fee of 1.75 for 10 hours
		else if(totalTime == 10)
		{
			parkFee += 1.75;
		}
		
			// add parking fee of 1.85 for 11 hours
		else if(totalTime == 11)
		{
			parkFee += 1.85;
		}
		
			// add parking fee of 1.95 for 12 hours
		else if(totalTime == 12)
		{
			parkFee += 1.95;
		}
		
			// add parking fee of 2.05 for 13 hours
		else if(totalTime == 13)
		{
			parkFee += 2.05;
		}
		
			// add parking fee of 2.15 for 14 hours
		else if(totalTime == 14)
		{
			parkFee += 2.15;
		}
		
			// add parking fee of 2.25 for 15 hours
		else if(totalTime == 15)
		{
			parkFee += 2.25;
		}
		
			// add parking fee of 2.35 for 16 hours
		else if(totalTime == 16)
		{
			parkFee += 2.35;
		}
	}
	
		// if the parking is for a senior citizen calculate add fee
		// based on university parking for senior citizens
	if(customerCategory == 'S')
	{
			// cycle through the hours they were parked and add .12
			// for every hour parked to their total fee
		for(int counter = 0; counter < totalTime; counter++)
		{
			parkFee += 0.12;
		}
	}
}

//********************** END CALCULATE FEE *****************************

//********************** PRINT DATA ************************************

void printData(char customerCategory, int timeIn, int timeOut, 
				  double &parkFee, int &totalTime, ofstream &Outfile)
{
		// Receives - customer category, time in, time out, current 
		//			  parking fee, and total time
		// Task - Print out ticket based on parking fee
		// Returns - Nothing
		
	string customerType;
	
		// create string "car" if customer category is "c" to print in
		// ticket
	if(customerCategory == 'C')
	{
		customerType = "Car";
	}
	
		// create string "truck" if the customer category is "t" to 
		// print in ticket
	if(customerCategory == 'T')
	{
		customerType = "Truck";
	}
	
		// create string "Snr Citzn" (Senior Citizen) if the customer
		// category is "s" to print in ticket
	if(customerCategory == 'S')
	{
		customerType = "Snr Citzn";
	}
	
		// print origial input data for each vehicle
	Outfile << "The input data was:" << endl;
	Outfile << customerCategory << " " << timeIn << " " << 
			timeOut << endl;
	Outfile << endl;
	
		// the following formats and simulates the printout of the 
		// ticket for in which is owed for a specific vehicle type.
		// the ticket displays the customer category (vehicle type),
		// total hours parked, and the amount they owe
	Outfile << "$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	Outfile << "$                       $" << endl;
	Outfile << "$   MISSOURI WESTERN    $" << endl;
	Outfile << "$   UNIVERSITY          $" << endl;
	Outfile << "$                       $" << endl;
	Outfile << "$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	Outfile << "$     PARKING FEE       $" << endl;
	Outfile << "$                       $" << endl;
	Outfile << "$   Customer            $" << endl;
	Outfile << "$   Category: " << left << setw(10) << customerType 
			<< "$" << endl;
	Outfile << "$                       $" << endl;
	Outfile << "$   Time: " << left << setw(3) << totalTime 
			<< "hours" << "      $" << endl;
	Outfile << "$                       $" << endl;
	Outfile << "$   Amount              $" << endl;
	Outfile << fixed << setprecision(2) << "$   Paid: $" << left 
			<< setw(13) << parkFee << "$" <<endl;
	Outfile << "$                       $" << endl;
	Outfile << "$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	
		// create a space between tickets, also making one not spilling
		// from one page to another
	for(int count = 0; count < 2; count++)
	{
		Outfile << endl;
	}
}

//******************* END PRINT DATA ***********************************

//********************* FUNCTION HEADER ********************************

void printHeader(ofstream &Outfile) 
{	
		// Receives - the output file
		// Task- Prints the output preamble
		// Returns - Nothing
	Outfile << setw(30) << "Alex Knipfer ";
	Outfile << setw(17) << "CSC 2400";
	Outfile << setw(15) << "Section 12" << endl;
	Outfile << setw(30) << "Fall 2014";
	Outfile << setw(20) << "Assignment #1" << endl;
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
