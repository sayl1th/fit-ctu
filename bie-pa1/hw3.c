#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#define INVALID_DATE (-1)
#endif /* __PROGTEST__ */

int isLeapYear(int y);
long int convertToAllDays(int y, int m, int d);
int convertToYear(long int days);
int convertToMonth(long int days);
int convertToDay(long int days);
int invalidInput(int y, int m, int d);
int isFullMoon ( int y, int m, int d );
int prevFullMoon ( int y, int m, int d,
                   int * prevY, int * prevM, int * prevD );
int nextFullMoon ( int y, int m, int d,
                   int * nextY, int * nextM, int * nextD );

const double MOONPERIOD = 29.53059027;
const double FIRSTFULLMOON = 21.4; 
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
 
  int y,m,d;


  return 0;
}
#endif /* __PROGTEST__ */

int isLeapYear(int year) {
	
	if ((year % 4 == 0 && year % 100 != 0)  || (year % 400 == 0 && year % 4000 != 0)) {	
		return 1;
	}
	else {
		return 0;
	}
		
		
}

long int convertToAllDays(int y, int m, int d)
{

	long int convertedDays = 0;
	
	long int year = y - 1;
	
	while (year >= 2000) {
		
		if (isLeapYear(year))
			convertedDays+=366;	
		else
			convertedDays+=365;
		
		year--;
	}
	
	if (isLeapYear(y)) {
		if (m == 12)
			convertedDays+=335;
		else if (m == 11) 
			convertedDays+=305;
		else if (m == 10)
			convertedDays+=274;
		else if (m == 9)
			convertedDays+=244;
		else if (m == 8)
			convertedDays+=213;
		else if (m == 7)
			convertedDays+=182;
		else if (m == 6)
			convertedDays+=152;
		else if (m == 5)
			convertedDays+=121;
		else if (m == 4)
			convertedDays+=91;
		else if (m == 3)
			convertedDays+=60;
		else if (m == 2)
			convertedDays+=31;
		else if (m == 1)
			convertedDays+=0;
	}
	
	else {
			if (m == 12)
			convertedDays+=334;
		else if (m == 11) 
			convertedDays+=304;
		else if (m == 10)
			convertedDays+=273;
		else if (m == 9)
			convertedDays+=243;
		else if (m == 8)
			convertedDays+=212;
		else if (m == 7)
			convertedDays+=181;
		else if (m == 6)
			convertedDays+=151;
		else if (m == 5)
			convertedDays+=120;
		else if (m == 4)
			convertedDays+=90;
		else if (m == 3)
			convertedDays+=59;
		else if (m == 2)
			convertedDays+=31;
		else if (m == 1)
			convertedDays+=0;
	}

	convertedDays+=d;
	
	return convertedDays;
}

int convertToYear (long int days) {
	
	int date = 2000;	
	
	while (days >= 365) {
    	
    	if (isLeapYear(date))
    		days -= 366;
    	 
    	else 
    		days -= 365;
    		
    	date++;	
    	
    	}
	
	return date;
}


int convertToMonth (long int days) {
	
	int date = 2000;	
	
	int month = 0;
	
	while (days >= 365) {
    	
    	if (isLeapYear(date))
    		days -= 366;
    	 
    	else 
    		days -= 365;
    		
    	date++;	
    	
    	}
	
	if (isLeapYear(date)) {
		
		if (days > 335 ) {
			month = 12;
		}
		else if (days > 305) {
			month = 11;	
		}
		else if (days > 274) {
			month = 10;	
		}	
		else if (days > 244) {
			month = 9;
		}
		else if (days > 213) {
			month = 8;	
		}
		else if (days > 182) {
			month = 7;	
		}
		else if (days > 152) {
			month = 6;
		}
		else if (days > 121) {
			month = 5;
		}
		else if (days > 91) {
			month = 4;	
		}
		else if (days > 60) {
			month = 3;	
		}
		else if (days > 31) {
			month = 2;	
		}
		else if (days > 0)
			month = 1;
	}
	
	else {
	
		if (days > 334 ) {
			month = 12;	
		}
		else if (days > 304) {
			month = 11;	
		}
		else if (days > 273) {
			month = 10;	
		}
		else if (days > 243) {
			month = 9;	
		}
		else if (days > 212) {
			month = 8;	
		}
		else if (days > 181) {
			month = 7;
		}
		else if (days > 151) {
			month = 6;	
		}
		else if (days > 120) {
			month = 5;	
		}
		else if (days > 90) {
			month = 4;	
		}
		else if (days > 59) {
			month = 3;	
		}
		else if (days > 31) {
			month = 2;
		}
		else if (days > 0)
			month = 1;
	}
	
	return month;
	
}

int convertToDay (long int days) {
	
	int date = 2000;	
	
	int day = 0;
	
	while (days >= 365) {
    	
    	if (isLeapYear(date))
    		days -= 366;
    	 
    	else 
    		days -= 365;
    		
    	date++;	
    	
    	}
	
	if (isLeapYear(date)) {
		
		if (days > 335 ) {
			days -= 335;
		}
		else if (days > 305) {
			days -= 305;	
		}
		else if (days > 274) {
			days -= 274;	
		}	
		else if (days > 244) {
			days -= 244;
		}
		else if (days > 213) {
			days -= 213;	
		}
		else if (days > 182) {
			days -= 182;	
		}
		else if (days > 152) {
			days -= 152;
		}
		else if (days > 121) {
			days -= 121;
		}
		else if (days > 91) {
			days -= 91;	
		}
		else if (days > 60) {
			days -= 60;	
		}
		else if (days > 31) {
			days -= 31;	
		}
	}
	
	else {
	
		if (days > 334 ) {
			days -= 334;	
		}
		else if (days > 304) {
			days -= 304;	
		}
		else if (days > 273) {
			days -= 273;	
		}
		else if (days > 243) {
			days -= 243;	
		}
		else if (days > 212) {
			days -= 212;	
		}
		else if (days > 181) {
			days -= 181;
		}
		else if (days > 151) {
			days -= 151;	
		}
		else if (days > 120) {
			days -= 120;	
		}
		else if (days > 90) {
			days -= 90;	
		}
		else if (days > 59) {
			days -= 59;	
		}
		else if (days > 31) {
			days -= 31;	
		}
	}
	
	day = days;
	
	return day;
    
}

int invalidInput(int y, int m , int d) {
	
	if (y < 2000)
		return 1;
		
	else if (m > 12 || m < 1)
		return 1;
	else if (m == 11 && d > 30)
		return 1;
	else if (m == 9 && d > 30) 
		return 1;
	else if (m == 6 && d > 30)
		return 1;
	else if (m == 4 && d > 30)
		return 1;
	else if (isLeapYear(y) && m == 2 &&  d > 29)
		return 1;
	else if (!isLeapYear(y) && m == 2 && d > 28)
		return 1;
	else if (d > 31)
		return 1;
	else 
		return 0;
}

int isFullMoon ( int y, int m, int d ) {
	
	if (invalidInput(y,m,d)) {
		return INVALID_DATE;
	}
	
	else {
		long int days = convertToAllDays(y,m,d);
		double fullMoon = FIRSTFULLMOON;
	
		while (fullMoon <= days) {
			fullMoon += MOONPERIOD;
		}
	
		if ((int)fullMoon == days)
			return 1;
	
		else 
			return 0;	
	}
	
}
int nextFullMoon ( int y, int m, int d,
                   int * nextY, int * nextM, int * nextD ) {
                   
   	if (invalidInput(y,m,d)) {
		return INVALID_DATE;
	}
    
    else {
    	long int days = convertToAllDays(y,m,d);
    
    	double fullMoon = FIRSTFULLMOON;
    
    	while ((int)fullMoon <= days) {
    		fullMoon += MOONPERIOD;
    	}
        
        * nextY = convertToYear((int)fullMoon);
        * nextM = convertToMonth((int)fullMoon);
        * nextD = convertToDay((int)fullMoon);
    	return 1;
     }
	
}

int prevFullMoon (int y, int m, int d, int * prevY, int * prevM, int * prevD) {

	if (invalidInput(y,m,d)) {
		return INVALID_DATE;
	}

	else {

		long int days = convertToAllDays(y,m,d);
		
		double fullMoon = FIRSTFULLMOON;
	
		if (days <= fullMoon) {
			* prevY = 1999;
			* prevM = 12;
			* prevD = 22;
		}
		
		else {
			
            while (fullMoon <= days - MOONPERIOD) {
                fullMoon += MOONPERIOD;
            }
        
            * prevY = convertToYear((int)fullMoon);
            * prevM = convertToMonth((int)fullMoon);
            * prevD = convertToDay((int)fullMoon);
            
        }
        
    return 1;
    }
}
