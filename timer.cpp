// CPP program to create a timer
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

// hours, minutes, seconds of timer
int hours = 0;
int minutes = 0;
int seconds = 0;

int hoursTarget = 0;
int minutesTarget = 0;
int secondsTarget = 10;

// function to display the timer
void displayClock()
{
	// system call to clear the screen
	system("cls");

	cout << setfill(' ') << setw(47) << "TIMER		 \n";
	cout << setfill(' ') << setw(55) << " --------------------------\n";
	cout << setfill(' ') << setw(29);
	cout << "| " << setfill('0') << setw(2) << hours << " hrs | ";
	cout << setfill('0') << setw(2) << minutes << " min | ";
	cout << setfill('0') << setw(2) << seconds << " sec |" << endl;
	cout << setfill(' ') << setw(55) << " --------------------------\n";
}

void timer()
{
	while (true) {
		
		// display the timer
		displayClock();
		
		// check target
		if(seconds == secondsTarget && 
			minutes == minutesTarget && 
			hours == hoursTarget) 
		return;

		// sleep system call to sleep 
		// for 1 second
		sleep(1);

		// increment seconds
		seconds++;

		// if seconds reaches 60
		if (seconds == 60) {
		
			// increment minutes
			minutes++;

			// if minutes reaches 60
			if (minutes == 60) {
		
				// increment hours
				hours++;
				minutes = 0;
			}
			seconds = 0;
		}


	}
}

// Driver Code
int main()
{
	// start timer from 00:00:00
	timer();
	return 0;
}

