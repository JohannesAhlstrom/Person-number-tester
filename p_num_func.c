/*
 * p_num_func.c
 *
 *  Created on: 20 okt. 2020
 *      Author: Johannes Ahlström
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "p_num.h"

/****************************************************************************************
*****************************************************************************************
******					             											   ******
******   							   Functions                                   ******
******																			   ******
*****************************************************************************************
*****************************************************************************************/

pnumber create_random()
{
	pnumber person;
	unsigned int *ptr;
	ptr = &person.inputarray[0];

	for(int i = 0; i < TEN; i++, ptr++)
	{
		*ptr = rand() %TEN;
	}
	return person;
}

pnumber take_input()
{
	pnumber person, *personptr;
	char temp;
	personptr=&person;
	printf("\nWelcome!\nThis program will verify the correctness \nof the control digit in your personal number\n");
	printf("\nPlease enter your personal number in the form of: YYMMDD-NNNN");
	printf("\nThe program will not run until at least 10 digits has been inserted.");
	fflush(stdin);
	for(int i = 0, j= 0;i<HUNDRED && j<TEN; i++)
	{
		temp=getchar();
		if(isdigit(temp))
		{
			personptr->inputarray[j]= temp;
			personptr->inputarray[j] = personptr->inputarray[j]-ASCIIOFFSET;
			j++;
		}
	}
	return person;
}

pnumber date_calc(pnumber person)
{
	unsigned int *ptr;
	pnumber *personptr;
	ptr = person.inputarray;
	personptr = &person;
	personptr->year = ((*ptr*TEN)+*(ptr+ONE));
	personptr->month = (*(ptr+TWO)*TEN)+*(ptr+THREE);
	personptr->day = (*(ptr+FOUR)*TEN)+*(ptr+FIVE);

	for(int i = SIX, j = 0; i <TEN; i++,j++)
	{
		personptr->control[j]=personptr->inputarray[i];
	}
	personptr->lastdigit = *(ptr+NINE);
	return person;
}

_Bool input_control(pnumber person)
{
	_Bool stop = true;
	person = input_control_leap_calc(person);
	stop = input_control_year(person,stop);
	stop = input_control_month(person,stop);
	stop = input_control_day(person,stop);
	stop = input_control_control(person,stop);
	if(stop ==false)
	{
		printf("\nThis will end the current run to allow you to try again.\n\n");
	}
	return stop;
}

_Bool input_control_year(pnumber person, _Bool stop)
{
	pnumber *personptr;
	personptr = &person;
	if(stop == true)
	{
		if(!(personptr->year <HUNDRED && personptr->year >0))
		{
			printf("\nPlease insert a proper year (%d-%d)", ONE, HUNDRED-ONE);
			stop = false;
		}
	}
	if(personptr->year == 0) //CORNER CASE HANDLING
	{
		stop = true;
	}
	return stop;
}

_Bool input_control_month(pnumber person,_Bool stop)
{
	pnumber *personptr;
	personptr = &person;
	if(stop == true)
	{
		if(!(personptr->month < THIRTEEN && personptr->month >0))
		{
			printf("\nError, valid months are %d-%d", ONE, TWELVE);
			stop = false;
		}
	}
	return stop;
}

_Bool input_control_day(pnumber person,_Bool stop)
{
	enum days{january = THIRTYONE, february = TWENTYEIGHT, februaryleap = TWENTYNINE, march =THIRTYONE, april = THIRTY, may =THIRTYONE, june = THIRTY, july =THIRTYONE, august =THIRTYONE, september = THIRTY, october =THIRTYONE, november =THIRTY, december =THIRTYONE};
	pnumber *personptr;
	personptr =&person;
	if(stop == true)
	{
		if(personptr->day <ONE)
		{
			printf("Valid dates must be over the value 1");
			stop = false;
		}
		if(personptr->month == ONE && personptr->day > january)
		{
			printf("\nError, %d days in january ", january);
			stop = false;
		}
		else if(personptr->month == TWO && personptr->day > february && personptr->leap != true)
		{
			printf("\nError, %d days in normal february", february);
			stop = false;
		}
		else if(personptr->month == TWO && personptr->day >februaryleap && personptr->leap ==true)
		{
			printf("\nError, %d days in a leap-year february", februaryleap);
			stop = false;
		}
		else if(personptr->month == THREE && personptr->day > march)
		{
			printf("\nError, %d days in march", march);
			stop = false;
		}
		else if(personptr->month == FOUR && personptr->day > april)
		{
			printf("\nError, %d days in april", april);
			stop = false;
		}

		else if(personptr->month == FIVE && personptr->day > may)
		{
			printf("\nError, %d days in may", may);
			stop = false;
		}

		else if(personptr->month == SIX && personptr->day > june)
		{
			printf("\nError, %d days in june", june);
			stop = false;
		}
		else if(personptr->month == SEVEN && personptr->day > july)
		{
			printf("\nError, %d days in july", july);
			stop = false;
		}
		else if(personptr->month == EIGHT && personptr->day > august)
		{
			printf("\nError, %d days in august", august);
			stop = false;
		}
		else if(personptr->month == NINE && personptr->day > september)
		{
			printf("\nError, %d days in september", september);
			stop = false;
		}
		else if(personptr->month == TEN && personptr->day > october)
		{
			printf("\nError, %d days in october", october);
			stop = false;
		}
		else if(personptr->month == ELEVEN && personptr->day> november)
		{
			printf("\nError, %d days in november ", november);
			stop = false;
		}
		else if(personptr->month == TWELVE && personptr->day > december)
		{
			printf("\nError, %d days in december", december);
			stop = false;
		}
	}
	return stop;
}
_Bool input_control_control(pnumber person,_Bool stop)
{
	pnumber *personptr;
	personptr = &person;
	if(stop==true)
	{
		if(personptr->control[ONE] ==0 && personptr->control[TWO] ==0 && personptr->control[THREE] ==0 && personptr->control[FOUR] ==0)
		{
			printf("\nControl needs to be at least 0001 or higher, please try again");
			stop = false;
		}
	}
	return stop;
}

pnumber input_control_leap_calc(pnumber person)
{
	pnumber *personptr;
	personptr = &person;
	if((personptr->year %FOUR ==0 && personptr->year %HUNDRED !=0) || personptr->year%FOURHUNDRED ==0)
	{
		printf("\nInformation: This year IS a leap year");
		personptr->leap = true;
	}
	else
	{
		printf("\nInformation: This year is NOT leap year");
		personptr->leap = false;
	}
	return person;
}

void create_control_algorithm(int algorithm_array[])
{
	int *ptr;
	ptr = &algorithm_array[0];
	for (int i = 0; i <NINE ; i++,ptr++)
	{
		*ptr=TWO;
		*(ptr+ONE)=ONE;
		i++;
		ptr++;
	}
}

int handle_array(int algoarray[], pnumber person)
{
	int *controlptr;
	int *sumptr;
	unsigned int *personptr;
	pnumber *newpersonptr;
	controlptr = &algoarray[0];
	personptr = &person.inputarray[0];
	newpersonptr = &person;

	int sum=0, counter=0;
	int newarray[NINE];
	int *newarrayptr;
	newarrayptr=&newarray[0];
	sumptr=&sum;
	for(int i = 0; i < NINE; i++)
	{
		newarray[i] = *controlptr * *(personptr);
		controlptr++;
		personptr++;
	}
	for(int j = 0; j < NINE; j++)
	{
		if(*newarrayptr %TEN != 0 && *newarrayptr >NINE)
		{
			*newarrayptr = *newarrayptr%TEN;
			counter++;
		}
		else if(*newarrayptr%TEN ==0 && *newarrayptr >NINE )
		{
			*newarrayptr = *newarrayptr%TEN;
			counter++;
		}

		*sumptr += *newarrayptr;
		newarrayptr++;
	}
	*sumptr=(*sumptr)+counter;

	if(newpersonptr->lastdigit == 0 && *sumptr%TEN ==0) //NB CORNER CASE HANDLING
	{
		*sumptr = *sumptr%TEN;
		return sum;
	}
	else
	{
		*sumptr = *sumptr%TEN;
		*sumptr = TEN-*sumptr;
		return sum;
	}
}

void present_output(pnumber person, int sum)
{
	int *sumptr;
	sumptr =&sum;
	pnumber *personptr;
	personptr = &person;
	if((TWENTYTWENTY-(personptr->year+NINETEENHUNDRED)) >= TWENTYONE && (TWENTYTWENTY-(personptr->year +NINETEENHUNDRED))<HUNDRED)
	{
	printf("\nThe date of birth is: 19%d - %02d- %02d",personptr->year,personptr->month,personptr->day);
	}
	else if((TWENTYTWENTY-(personptr->year+NINETEENHUNDRED)) >HUNDREDTEN)
	{
	printf("\nThe date of birth is: 200%d - %02d -%02d",personptr->year, personptr->month, personptr->day);
	}
	else if((TWENTYTWENTY-(personptr->year+NINETEENHUNDRED)) >=HUNDRED)
	{
	printf("\nThe date of birth is: 20%d - %02d -%02d",personptr->year, personptr->month, personptr->day);
	}
	printf("\nControl input as:  %d \nControl should be: %d", personptr->lastdigit, *sumptr);
	if(personptr->lastdigit == *sumptr)
	{
		printf("\n*******  This is correct!  ********\n");
		match();

	}
	else
	{
		printf("\n*******  This is not correct ******\n");
	}
	printf("\n********************************************************************************************");
}

void dynamic_input()
{
	int temp;
	fflush(stdin);
	printf("\nPlease choose how many numbers to insert:");
	scanf("%d", &temp);
	int newperson = (int *)malloc(temp * sizeof(int));
	if(newperson == NULL)
	{
		printf("\nMemory allocation failed.\nPlease try again.");
		free(newperson);
	}

	for(int i = ONE; i<temp+ONE;i++,newperson++)
	{
		newperson = rand() %TEN;
		printf(" %d",newperson);
		if(i%TEN==0)
		{
			printf("\n");
		}
	}
	printf("\n\nCreated: %d numbers dynamically", temp);
	printf("\n********************************************************************************************");
	free(newperson);
}

void match()
{
	printf("\n");
	printf("\n  ________________________\n");
	printf(" |************************|  ****     ******\n");
	printf(" |************************|  ****    *****\n");
	printf(" |****|   Johannes   |****|  ****   *****\n");
	printf(" |****|     seal     |****|  **** ****\n");
	printf(" |****|      of      |****|  ****\n");
	printf(" |****|   approval   |****|  **** ****\n");
	printf(" |************************|  ****   *****\n");
	printf(" |************************|  ****     ******\n");
}

void pointless_function(int *ptr)
{
	printf("\nSURPRISE!");
	printf("\nThis is actually not a pointless function.");
	printf("\nIt takes a pointer input, and will now print out what it found in the memory.");
	printf("\nIt found ***  %d  *** in the memory.",*ptr);
	printf("\n********************************************************************************************");
	printf("\n");
}
