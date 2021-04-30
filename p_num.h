/*
 * p_num.h
 *
 *  Created on: 20 okt. 2020
 *      Author: Johannes Ahlström
 */

#ifndef SRC_P_NUM_H_
#define SRC_P_NUM_H_

/******************************************************************
******************                       **************************
******************     DOCUMENTATION     **************************
******************                       **************************
****************************************************************//*

Contents:

Macros
Structures
Comments to main().
Prototypes for functions 1-15, with explanations.

*//****************************************************************
 *****************                        *************************
 *****************        MACROS          *************************
 *****************                        *************************
 ******************************************************************/
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define TEN 10
#define ELEVEN 11
#define TWELVE 12
#define THIRTEEN 13
#define FOURTEEN 14
#define TWENTY 20
#define TWENTYONE 21
#define TWENTYEIGHT 28
#define TWENTYNINE 29
#define THIRTY 30
#define THIRTYONE 31
#define THIRTYTWO 32
#define HUNDRED 100 				//Used to limit the number of characters taken as input.
#define HUNDREDTEN 110
#define NINETEENHUNDRED 1900
#define TWENTYTWENTY 2020
#define FOURHUNDRED 400 			//Used in the calculation of leap-years.
#define ASCIIOFFSET 48 				//This is used to handle the transition from characters to digits.

/******************************************************************
 ********************                       ***********************
*********************        Structures     ***********************
*********************                       ***********************
*******************************************************************/

           /*This struct uses bit-fields to save space
         The structure is type-defined to Alias: pnumber */

typedef struct{
	unsigned int year: SEVEN;
	unsigned int month: SEVEN;
	unsigned int day: SEVEN;
	unsigned int control[FOUR];
	unsigned int lastdigit;					 //Separates the control-digit.
	_Bool leap; 							 //Flag: leap = true or leap = false.
	unsigned int inputarray[TEN]; 			 //Stores the raw string of digits.
}pnumber; 									 //Structure Alias.

/*__________________________________________________________________
*********************************************************************
*******************[                      ]**************************
*******************[   Comments to main   ]**************************
*******************[                      ]**************************
*********************************************************************

The main function is wrapped in a Switch allowing the user to select between 5 modes.

The first one contains the solution to the assignment.

The second allows the computer to randomize a number consisting of 10 digits and
then check to see how many tries it takes until it has randomized a number which passes
the input-control.

The third uses dynamic memory allocation to allow the user to create a series of randomized
digits of the chosen size, with no maximum. The digits are displayed as blocks of 10.

The fourth choice asks the user for an integer, then sends the address to that integer to a function,
the function then prints out the value of the integer it found in the address.

The fifth choice exits the program by changing the boolean flag stop to true.

The program repeats for as long as the user wants it to.*/

/*__________________________________________________________________
*********************************************************************
*******************[                      ]**************************
*******************[      FUNCTIONS       ]**************************
*******************[                      ]**************************
*********************************************************************

Contents:
1  take_input()
2  date_calc()
3  input_control()
4  input_control_year()
5  input_control_month()
6  input_control_day()
7  input_control_control()
8  input_control_leap_calc()
9  create_control_algorithm()
10 handle_array()
11 present_output()
12 create_random()
13 dynamic_input()
14 match()
15 pointless_function()

*********************************************************************
************            Number 1 / 15             *******************
*********************************************************************
************                                      *******************
************/       pnumber take_input();        /*******************
************                                      *******************
*********************************************************************
*********************************************************************

Purpose:
Asks the user for input, then stores the input in a structure format
called pnumber, specifically the member: <name>.inputarray.
Returns filled struct.


Prerequisite:
Variable existing in main() of type: Struct pnumber for holding
the input taken.


Input:
This function takes no information in the function call.
The input is created within the function as specified by the user.
Takes maximum 100 characters, saves 10 digits.


Handling:
Asks user for input, stores in stdin.
Uses getchar() and checks if the entered input is a digit, discards if not.
Uses pointers within the function to store values into temporary array
and then if the character is a digit, it is stored in a spot in the
<name>.inputarray member variable.
Turns value from ASCII to Digit via use of offset 48.
Iterates for next input.


Output:
The output is a struct pnumber in which the <name>.inputarray has been filled
and consists of only of digits, any dashes or non-digit input has been removed.


*********************************************************************
*********************************************************************/


/********************************************************************
************            Number 2 / 15             *******************
*********************************************************************
************                                      *******************
************/ pnumber date_calc(pnumber person); /*******************
************                                      *******************
*********************************************************************
*********************************************************************

PURPOSE:
Separates the input data in the pnumber.inputarray into year, months and days.
Furthermore, the control digits are stored in a special array.

PREREQUISITE:
Function take_input();

INPUT:
The function call takes a pnumber variable with values entered into the inputarray member.

HANDLING:
Via use of pointers: points to each of the values in the array of input-digits and subsequently
uses their values to put into the fitting slot.
This is done by taking the first value and multiplying by a factor of ten and then add
the value of pointer+1 (next value). Thus, the number 88 is treated as 8*10 + 8.
Values for YY MM and DD are handled via Pointer+NUMBERVALUE, however the control-digits are
handled using a For-loop to enter them into an array of integers.
The last digit is stored in the <name>.lastdigit member of the structure for use later.

OUTPUT:
Returns a filled pnumber with values entered for year, months, days, control and last-control.

*********************************************************************
*********************************************************************/


/********************************************************************
************            Number 3 / 15             *******************
*********************************************************************
***********                                       *******************
***********/ _Bool input_control(pnumber person);/*******************
***********                                       *******************
*********************************************************************
*********************************************************************

PURPOSE:
This function is used as a batch, calling several sub-functions handling input-control.

PREREQUISITE:
1 take_input();
2 date_calc();

INPUT:
The function call takes a filled pnumber struct which is passed through.

HANDLING:
Calls several functions, if any function returns stop,
the subsequent functions are called but exited before checking, saving time.

OUTPUT:
Returns Boolean flag stop = true or stop = false. Stop = true allows the program to continue.


*********************************************************************
*********************************************************************/

/********************************************************************
************            Number 4 / 15             *******************
*********************************************************************
****                                                       **********
****/ _Bool input_control_year(pnumber person,_Bool stop);/**********
****                                                       **********
*********************************************************************
*********************************************************************

PURPOSE:
Checks if the year is to be accepted.

PREREQUISITE:
input_control()

INPUT:
Function call takes a pnumber struct and the Boolean flag "stop".

HANDLING:
Takes the pnumber and stop variables, if stop = false it does not run.
Using pointers, checks through Demorgans theorem that the entered digits are within the range of 1-99.
Hence "If Not over 100 and less than 1 or zero" -> continue.
if failed, set Bool-flag stop to "false" and prints out message.

CORNER CASE CHECK: Year == 0, you can be born in 2000.

OUTPUT:
Returns Boolean-flag stop true or false.


*********************************************************************
*********************************************************************/

/********************************************************************
************            Number 5 / 15             *******************
*********************************************************************
****													   **********
****/_Bool input_control_month(pnumber person,_Bool stop);/**********
****                                                       **********
*********************************************************************
*********************************************************************

PURPOSE:
Checks if the month is to be accepted.

PREREQUISITE:
input_control();

INPUT:
Function call takes a pnumber struct and the Boolean flag "stop".


HANDLING:
Takes the pnumber and stop variables, if stop = false it does not run.
Using pointers, checks through Demorgans theorem that the entered digits are within the range of 1-12.
Hence "If Not over 12 and below 1" -> continue.
If failed, set Bool-flag stop to "false" and prints out message.


CORNER CASE CHECK: Month = 0.

OUTPUT:
Returns Boolean-flag stop true or false.


*********************************************************************
*********************************************************************/

/********************************************************************
************            Number 6 / 15             *******************
*********************************************************************
*****                                                     ***********
*****/_Bool input_control_day(pnumber person,_Bool stop);/***********
*****                                                     ***********
*********************************************************************
*********************************************************************

PURPOSE:
Checks that the entered date is possible and acceptable, using information on leap-years.

PREREQUISITE:
Input_control();
Input_control_leap_calc();  **NB**

INPUT:
Function call takes a pnumber struct and the Boolean flag "stop".

HANDLING:
Creates an enum containing all the months and their corresponding value of days.
Uses specific "Febraury leap" = 29 days.
Uses information found in Boolean flag <name>.leap to set the entered year as leap or not.
Checks that the number of days entered exceeds 0, or is rejected if below 1.
Through the use of pointers, checks if the value entered in
<name>.year and <name>.month corresponds to the number of days.
This is done through a set of if-else-if statements specifying
if the year is leap, month is X then the days should not exceed: Y.

CORNER CASE CHECK: In leap years, february 29 is possible.

OUTPUT:
Returns Boolean-flag stop true or false.


*********************************************************************
*********************************************************************/

/********************************************************************
************            Number 7 / 15             *******************
*********************************************************************
****                                                           ******
****/  _Bool input_control_control(pnumber person,_Bool stop);/******
****                                                           ******
*********************************************************************
*********************************************************************

PURPOSE:
Checks that the control digits is more than 1. hence, that 0000 is not possible.


PREREQUISITE:
input_control();

INPUT:
Function call takes pnumber and Bool flag stop.

HANDLING:
Checks if stop = false, doesn't run otherwise.
checks that not all of the digits in the array are 0 at the same time.

CORNER CASE CHECK: Do not allow "0000".

OUTPUT:
Returns Boolean-flag stop true or false.



*********************************************************************
*********************************************************************/

/********************************************************************
************            Number 8 / 15             *******************
*********************************************************************
********                                                  ***********
********/pnumber input_control_leap_calc(pnumber person);/***********
********                                                  ***********
*********************************************************************
*********************************************************************

PURPOSE:
Calculates if the entered year is a leap year.

PREREQUISITE:
Input_control();

INPUT:
Function call takes pnumber struct variable with entered value for Year.

HANDLING:
Calculates if the entered year is a leap year through algorithm
if the year is divisible by four but not by 100 then it is a leap year, however
if it is not divisible by 100 and but IS divisible by 400 then it is a leap year.
Sets Boolean flag leap in the struct at <name>.leap = true;

OUTPUT:
Returns Boolean-flag stop = true or false

*********************************************************************
*********************************************************************/

/********************************************************************
************            Number 9 / 15             *******************
*********************************************************************
************                                      *******************
************/ void create_control_algorithm();   /*******************
************                                      *******************
*********************************************************************
*********************************************************************

PURPOSE:
Creates an array containing 9 digits of a pattern of "2,1" repeated.
To be used when calculating the array used in the algorithm.

PREREQUISITE:
Empty variable in main() of type int array of size 9.

INPUT:
No input.

HANDLING:
Through the use of pointers in a for-loop, places digits 2 and 1 in a pattern 9 times.
Stores in array which is returned.

OUTPUT:
Returns an integer array of 9 digits in pattern 2,1 repeated.

*********************************************************************
*********************************************************************/

/********************************************************************
************            Number 10 / 15             ******************
*********************************************************************
******                                                     **********
******/ int handle_array(int algoarray[], pnumber person);/**********
******                                                     **********
*********************************************************************
*********************************************************************

PURPOSE:
Implements the algorithm calculating what the expected control-digit should be.


PREREQUISITE:
1 take_input()
2 calc_date()
3 input_control()
4 create_control_array()

INPUT:
Function call takes a filled variable of type struct pnumber
and the integer array containing the array used in the algorithm.

HANDLING:
Through the use of pointers, takes the first values of each array using for-loop to multiply
them and stores in a new array.
Checks if the values stored in the new array is OVER 10, through modulus, and if so,
saves the rest in variable. Then it checks if the value stored is Exactly 10.
This is done to counter the corner case of adding 10 instead of 1+0.
If it finds rest on modulus 10, Add the rest and increment a counter variable.
Add together all the variables in the new variable and add the number of counters.
Remove the digit holding the factor 10s through use of modulus 10.
Check how far the sum is from the nearest ten value, and save the distance in the sum variable.

CORNER CASE CHECK: if it ends with 5 or 0

OUTPUT:
Returns an integer containing the distance in the variable sum.


*********************************************************************
*********************************************************************/

/********************************************************************
************            Number 11 / 15             ******************
*********************************************************************
*****                                                    ************
*****/  void present_output(pnumber person, int sum);    /***********
*****                                                    ************
*********************************************************************
*********************************************************************

PURPOSE:
Checks if last digit is the same as the calculated control digit and reports the findings.

PREREQUISITE:
1 take_input()
2 calc_date()
3 input_control()
4 create_control_array()
5 handle array()


INPUT:
Function call takes the int variable sum and the pnumber struct.

HANDLING:
Through the use of pointers, checks whether the calculated sum is equal to the last digit.
and reports the findings.
Also: Prints out a full version of the entered personal-number including the year, assuming 1-99 years old.
Pads the months and days if a number less than 10 is entered.

OUTPUT:
This function prints out the answer to the question if the entered 10 digit
value is an acceptable combination of a Swedish personal number.


*********************************************************************
*********************************************************************/


/********************************************************************
************            Number 12 / 15             ******************
*********************************************************************
*****                                                    ************
*****/               pnumber create_random();            /***********
*****                                                    ************
*********************************************************************
*********************************************************************

PURPOSE
This function creates a randomized personal-number.

PREREQUISITE
Requires a living pnumber struct variable in main();
That the counter variable sets back to 0 after each run of the main while() function.

INPUT
None, creates input to other functions.

HANDLING
Through the use of pointers and a for-loop, puts a random digit between
0-9 in the <name>.inputarray member.

OUTPUT
Returns the pnumber variable filled with random digits.
*/

/********************************************************************
************            Number 13 / 15             ******************
*********************************************************************
*****                                                    ************
*****/            void dynamic_input();                  /***********
*****                                                    ************
*********************************************************************
*******************************************************************//*
PURPOSE
Allows the user to request a series of numbers, no limitations on size.

PREREQUISITE
That the malloc() pointer doesn't get "NULL", otherwise none.

INPUT
Takes input of how many numbers should be in the series, uses int.

HANDLING
Takes the input of size, uses malloc() to assign a pointer to a memory area
of that size. Allocates a malloc()-pointer to an int variable.
Fills up the size of the area with randomized numbers.
Frees the memory allocated afterwards in free();

OUTPUT
Prints out strings of numbers in blocks of 10 to mimic personal numbers.*/

/********************************************************************
************            Number 14 / 15             ******************
*********************************************************************
*****                                                    ************
*****/                   void match();                   /***********
*****                                                    ************
*********************************************************************
*******************************************************************//*

PURPOSE
The only purpose is to present the final "OK" in a more graphic manner.

PREREQUISITE
Take_input()
date_calc()
input_control()
create_control_algorithm()
handle_array()
present_output()
ALSO Requires the last digit and calculated control digit to be the same.

INPUT
None

HANDLING
Prints out Johannes seal of approval.

OUTPUT
Prints the seal of approval to console.
*/

/********************************************************************
************            Number 15 / 15             ******************
*********************************************************************
*****                                                    ************
*****/          void pointless_function(int *ptr);       /***********
*****                                                    ************
*********************************************************************
*******************************************************************//*


PURPOSE
This function is for educational purposes, taking input, storing in pointer and
making a function call take a pointer, check the contents and print out the contents.

PREREQUISITES
A value stored in a variable in main, and a pointer to the address of that value.

INPUT
Function call takes an address in the form of a pointer.

HANDLING
The function receives an address and checks the contents of the dereferenced memory.

OUTPUT
The function prints out the value it finds in the allocated address.

*/
#endif /* SRC_P_NUM_H_ */
