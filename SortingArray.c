/*
 Name: Gargi Sunil Sontakke
 GNumber:G01334018
 NETID: gsontakk
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int check_string_size(char* str);
int check_special_characters(char* str);
int check_duplicate_string(char* strings[10],char* string,int index);
void bubble_sort(char* strings[10]);
void print_array(char* strings[10]);


/*
  taking an input string from the user
  Checking if the string length is between 1 and 25 included
  Check for special charecters
*/

int main(){

 const int maxLen = 50;
 char* strings[10] ;


 printf("Enter 10 strings\n");
 for(int i=0;i<10;i++){
    strings[i] = malloc(maxLen);  // allocating memory and returning a pointer//

    printf("Enter String %d :",i);
    fgets(strings[i],maxLen,stdin);

//checking the string size using the check_string_size function
    while(check_string_size(strings[i]) == 1){
      printf("String is either empty or length is greater 25 characters.\n Please enter the new string:");
      fgets(strings[i],maxLen,stdin);
    }
//checking for special characters using the check_special_characters function
    while(check_special_characters(strings[i]) == 1){
      printf("Invalid character present in string.\n Please re-enter string:");
      fgets(strings[i],maxLen,stdin);
    }

//checking for duplicate characters using the check_duplicate_string function
    while(check_duplicate_string(strings,strings[i],i) == 1){
      printf("Duplicate string found.\n Please re-enter string:");
      fgets(strings[i],maxLen,stdin);
    }

 }

//calling the print function to print the strings
//calling the sorting function to give a sorted list as per user input
 print_array(strings);
 bubble_sort(strings);
 return(0);
}

//writing a function to check the string size
int check_string_size(char* str){
  //Check for the string length using the library function strlen().
  //if it lies between 1 to 25 return 0. Else return 1
    if( strlen(str)==0 || strlen(str)>25){
        return 1;
    }
    else 0;
}

//checking the input for special charecters
int check_special_characters(char* str){
    char check_char[7] ={'#', '$', '%', '^', '@', '(',  ')'};  //creating an array of characters that are invalid
    for(int i=0;i<7;i++){
      for(int j=0;j<strlen(str);j++){
        if(check_char[i] == str[j]){
            return 1;
        }
      }
    }
    return 0;
}

//checking for a duplicate string
int check_duplicate_string(char* strings[10],char* string,int index){

    for(int i=0;i<index;i++){
            if((strcmp(string,strings[i])==0) ){
                if(index == i){}
                else {
                  return 1;
                }
            }
    }
    return 0;
}

//function to perform sorting and print the sorted array.Also display the lowest and largest value
void bubble_sort(char* strings[10]){
 printf("To sort strings in ascending order, press 'A'\n To sort strings in descending order, press 'D' ");
 char order_value;

 scanf("%c",&order_value);
 char* temp;

 //sorting in ascending order
 if(order_value == 'A'){
   for(int i=0;i<10-1;i++){
   for(int j=0;j<10-i-1;j++){
    if(strcmp(strings[j],strings[j+1]) >0){
       temp= strings[j];
       strings[j]=strings[j+1];
       strings[j+1]=temp;
    }
   }
  }
  printf("The ordered list is:");
  print_array(strings);

//printing the lowest and highest ascii values of the elements: lowest will be strings[0], highest strings[9]
  printf("*************\n");
  printf("The element with lowest ascii value is: %s",strings[0]);
  printf("The element with highest ascii value is: %s",strings[9]);

 }
//sorting the strings in descending order
 else if(order_value == 'D'){
	for(int i=0;i<10-1;i++){
	  for(int j=0;j<10-i-1;j++){
		 if(strcmp(strings[j],strings[j+1]) <0){
	          temp= strings[j];
		      strings[j]=strings[j+1];
		      strings[j+1]=temp;
		 }
	  }
	 }
	 printf("The ordered list is:\n");
	 print_array(strings);

   //printing the lowest and highest ascii values of the elements: lowest will be strings[9], highest strings[0]

    printf("**");
  printf("The element with lowest ascii value is: %s",strings[9]);
  printf("The element with highest ascii value is: %s",strings[0]);
 }

 //In case of invalid input, i.e other than A or D, print a message
 else{
    printf("Invalid input.\n Please enter 'A' for ascending or 'D' for descending ");
 }

}

//printing all the array elements
void print_array(char* strings[10]){
printf("The strings are:");
 for(int i=0;i<10;i++){
   printf("%s ",strings[i]);
 }
}
