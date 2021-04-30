/*
 * p_num_main.c
 *
 *  Created on: 20 okt. 2020
 *      Author: Johannes Ahlström
 */

/****************************************************************************************
*****************************************************************************************
******					              Welcome									   ******
******   For information, please see the documentation in the header file p_num.h  ******
******																			   ******
*****************************************************************************************
*****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "p_num.h"


int main()
{
	setbuf(stdout,NULL);
	int sum=0,choice=0,temp=0,counter=0,tempptr,*ptr;
	int control_array[NINE];
	_Bool stop = true;
	pnumber person;
	ptr=&tempptr;
	srand(time(0));
	while(stop !=false)
	{
		do
		{
			counter = 0;
			stop = true;
			printf("\nWelcome to the main program!");
			printf("\n\nPlease make your selection:\n");
			printf("\n1 Manually enter input in the form of a personal number");
			printf("\n2 Randomizes a personal-number, how many tries does it take to find a fitting one?");
			printf("\n3 Request a list of dynamically allocated digits (no matter the size)");
			printf("\n4 Pointless function (Try me)");
			printf("\n5 Exit program");
			printf("\n********************************************************************************************");
			for(int i = 0; i <ONE; i++)
			{
				fflush(stdin);
				temp =getchar();
				if(isdigit(temp))
				{
					temp = temp-ASCIIOFFSET;
				}
				if(!(temp >FIVE || temp <ONE))
				{
					choice = temp;
				}
				else
				{
					printf("\nPlease redo your choice");
					stop = false;
				}
			}
		}while(stop == false);
		stop = true;
		switch (choice)
		{
		case ONE:
		{
			do
			{
				person = take_input();
				person = date_calc(person);
				stop = input_control(person);
			}while(!stop ==true);
			create_control_algorithm(control_array);
			sum = handle_array(control_array, person);
			present_output(person, sum);
			break;
		}
		case TWO:
		{
			do
			{
				person = create_random();
				printf("\nCreated: ");
				for(int i = 0; i<TEN;i++)
				{
					printf(" %d",person.inputarray[i]);
				}
				person = date_calc(person);
				stop = input_control(person);
				counter++;
			}while(!stop ==true);
			printf("\nTried *** %d *** times to get through input-control.\n",counter);
			create_control_algorithm(control_array);
			sum = handle_array(control_array, person);
			present_output(person, sum);
			break;
		}
		case THREE:
		{
			dynamic_input();
			break;
		}
		case FOUR:
		{
			printf("\nPlease insert an integer number:");
			scanf("%d",&tempptr);
			pointless_function(ptr);
			break;
		}
		case FIVE:
		{
			stop = false;
			break;
		}
		default:
		{
			printf("\nError, please try again");
			break;
		}
		}
	}
}
