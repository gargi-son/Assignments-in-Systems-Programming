#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
//Name: Gargi Sontakke
//Gnumber:G01334018
//Creating structure
struct address_t
{
   int oct[4];
   char alias[20];
   struct address_t *nxt ;
};

struct address_t *head = NULL;

//function to add new addresses to the text file
void insert_address(int ip1,int ip2,int ip3,int ip4,char alias[]){
    if(strlen(alias)>10){
       printf("The alias is more than 10 charecters. Retry\n");
       return;
    }
     if(ip1>255 || ip2>255 || ip3>255 || ip4>255 || ip1<0 || ip2<0 || ip3<0 || ip4<0){
         printf("ipv4 has a value larger than 255 or less than 0 please retry!!!\n");
         return;
     }

   struct address_t* chk_node = head;
   while(chk_node != NULL){
      if(strcmp(chk_node->alias,alias) == 0 && ipv4_1 == chk_node->oct[0] && ipv4_2 == chk_node->oct[1] && ipv4_3 == chk_node->oct[2] && ipv4_4 == chk_node->oct[3]){
        printf("This ipv4 already exists. Please retry");
        return;
     }
     chk_node = chk_node->nxt;
   }


   struct address_t* node = (struct address_t*)malloc(sizeof(struct address_t));
   node->oct[0] = ipv4_1;
   node->oct[1] = ipv4_2;
   node->oct[2] = ipv4_3;
   node->oct[3] = ipv4_4;
   strcpy(node->alias, alias);
   node->nxt = NULL;

   if(head == NULL){
       head = node;
   }else{
      struct address_t* node;
      node = head;
      while(node->nxt != NULL){
         node = node->nxt;
      }
      node->nxt = node;
   }
   printf("The element inserted is: %d.%d.%d.%d \t %s \n",node->oct[0],node->oct[1],node->oct[2],node->oct[3],node->alias);
   printf("IPV4 address successfully added \n" );
}

//function to look up for the corresponding address of the user fes alias
void address_lookup(char alias[]){
   struct address_t* node = head;
   while(node != NULL){
      if(strcmp(node->alias,alias) == 0){
        printf("%d.%d.%d.%d\n",node->oct[0],node->oct[1],node->oct[2],node->oct[3]);
        return;
     }
     node = node->nxt;
   }

  printf("the alias is not found in the linked list\n");

}
//function to delete the entry of the alias that user inputs
void del_address(char* alias){
  struct address_t* prev_node = head;
  struct address_t* node = head;
  if(node == head){
    if(strcmp(node->alias,alias) == 0){
        head = node->nxt;
        free(node);
        return;
    }else{
      node = node->nxt;
    }
  }
  while(node->nxt != NULL){
     if(strcmp(node->alias,alias) == 0){
        prev_node->nxt = node->nxt;
        return;
     }
     node = node->nxt;
  }
printf("The given alias was not found!!\n");
}

//function to display all the entries in the text file
void display_list(){
 struct address_t* node = head;
 int i =1;
 while(node != NULL){
    printf("Node Number = %d\n", i);
    printf("Address = %d.%d.%d.%d\n",node->oct[0],node->oct[1],node->oct[2],node->oct[3]);
    printf("Alias = %s\n",node->alias);
    i=i+1;
    node = node->nxt;
  }

}
//function that takes the locality from the user and displays the corresponding aliases
void display_alias_loc(int loc1,int loc2){
  struct address_t* node = head;
  int count =0;
  while(node != NULL){
    if(node->oct[0] == loc1 && node->oct[1] == loc2 ){
     printf("Alias for the given location = %s \n",node->alias);
     count++;
    }
     node = node->nxt;
  }
  if(count==0){
        printf("No aliases for given address\n");
  }
}

//function that updates the address of the existing entry with the entry that user inserts
void update_address(char alias[],int arr[4]){
   struct address_t* node = head;
   if(arr[0]>255 || arr[1]>255 || arr[2]>255 || arr[3]>255 || arr[0]<0 || arr[1]<0 || arr[2]<0 || arr[3]<0){
         printf("ipv4 has a value larger than 255 or less than 0 please retry!!!");
         return;
     }
    while(node != NULL){
       if(strcmp(node->alias,alias) == 0){
           printf("Address at entered alias = %d.%d.%d.%d\n",node->oct[0],node->oct[1],node->oct[2],node->oct[3]);
           node->oct[0] = arr[0];
           node->oct[1] = arr[1];
           node->oct[2] = arr[2];
           node->oct[3] = arr[3];
           return;
       }
       node = node->nxt;
    }
    printf("The given alias was not found!!\n");
}


void clear_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n');
}
//main function
void main()
{
   //printf("Create file of name CS531_Inet.txt locally in same folder as given file and add ipv4 addess and alias in the file example entry 111.22.3.44 platte\n\n");
   printf("The code is reading values from the file.\n\n");
   FILE *fptr; //creating a file with a pointer to the file 
   char str[50];
   char* ipv4;
   int i =0,p;


    fptr = fopen("CS531_Inet.txt","r"); //opening the file as readable 

// while the user input 

    while(fgets(str,sizeof(str),fptr) != NULL){
        char* line;
        char alias[20] = {};
       int a[4] = {};
       i =0;

       char *token = strtok(str," .");

       while(token!=NULL){
          if(i!=4){
            a[i] = atoi(token);
         }else{
            if(token[strlen(token)-1]=='\n')
            token[strlen(token)-1]='\0';
            strcpy(alias,token);
         }
         i++;
         token = strtok(NULL, " .");

       }
       //calling function insert function for all the 4 components and alias
        insert_address(a[0],a[1],a[2],a[3],alias);
    }


    while(1){
            printf("\nEnter the Menu\n1) Add address \n2) Look up address \n3) Update address \n4) Delete address \n5) Display list \n6) Display aliases for location \n7) Save to file \n8) Quit \n");
            int input ;
            scanf("%d",&input);

            if(input == 1){
                char temp_str[50]="";
                char tmp_str[20],c;
                int a[4];
                printf("Enter IPV4 address in the form a.b.c.d alias where a,b,c,d are numbers between 0 to 255 and alias is a textual name\n");
                clear_stdin();
                fgets(temp_str,50,stdin);

                sscanf(temp_str, "%d.%d.%d.%d %s" , &a[0],&a[1],&a[2],&a[3],tmp_str);
                printf("ipv4 entered is %d %d %d %d %s\n" , a[0],a[1],a[2],a[3],tmp_str);
                insert_address(a[0],a[1],a[2],a[3],tmp_str);

            }else if(input == 2){
                char look_up[20];
                printf("enter look up/alias \n");
                scanf("%s",look_up);
                address_lookup(look_up);
            }
            else if(input == 3){
                int a[4];
                char c;
                char alias[25];
                char temp_str[25];
                printf("Enter the alias\n");
                scanf("%s",alias);
                printf("Enter the new address: ");

               clear_stdin();
                fgets(temp_str,50,stdin);

                sscanf(temp_str, "%d.%d.%d.%d" , &a[0],&a[1],&a[2],&a[3]);
                update_address(alias,a);
            }
            else if(input == 4){
                char look_up[25];
                printf("enter look up address\n");
                scanf("%s",look_up);
                del_address(look_up);
            }
            else if(input == 5){
                display_list();
            }else if(input == 6){
                   char add[25];
                   int int_add[2];
                    printf("enter address location or locality  in for x.y where x and y are integers betwee 0-255 inclusive:\n");
                    scanf("%s",add);
                    sscanf(add, "%d.%d" , &int_add[0],&int_add[1]);
                    if(int_add[0]>255 || int_add[1]>255 || int_add[0]<0 || int_add[1]<0){
                        printf("address location or locality has a value larger than 255 or less than please retry!!!\n");
                    }else{
                       display_alias_loc(int_add[0],int_add[1]);
                    }
            }else if(input == 7){
                save();
            }
            else if(input == 8){
                break;
            }
    }
}
