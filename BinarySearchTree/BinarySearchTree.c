//Name: Gargi Sontakke
//GNo: G01334018

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct address_t
{
    int comp[4]; 
    char alias[10];
    struct address_t *leftchild ;
    struct address_t *rightchild;
};
struct address_t* rootnode = NULL;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Defining Functions

//Function to save the addresses to a text file
void save_address(struct address_t * temp_var,FILE *fileptr)
{
    if(temp_var != NULL)
    {
        save_address(temp_var->leftchild,fileptr);
        fprintf(fileptr, "%d. %d. %d. %d %s \n", temp_var->comp[0], temp_var->comp[1], temp_var->comp[2], temp_var->comp[3], temp_var->alias);
        save_address(temp_var->rightchild,fileptr);
    }
}

//Function to return address for the entered locality
int display_aliasaddress(struct address_t * temp_var,int var1,int var2,int n)
{
    int var = 0;
    if(temp_var == NULL)
    {
        return n;
    } 
    var = display_aliasaddress(temp_var->leftchild,var1,var2,n);
    if(temp_var->comp[0] == var1 && temp_var->comp[1] == var2 )
    {
        printf("Alias for the entered locality is %s \n",temp_var->alias);
        n += 1;
    }
    var = display_aliasaddress(temp_var->rightchild,var1,var2,n);    
}

//Function to define the inOrder Traversal
void displayaddress_IOtraversal(struct address_t * temp_var)
{
    if(temp_var != NULL)
    {
        displayaddress_IOtraversal(temp_var->leftchild);
        printf("%d.%d.%d.%d %s\n",temp_var->comp[0],temp_var->comp[1],temp_var->comp[2],temp_var->comp[3],temp_var->alias);
        displayaddress_IOtraversal(temp_var->rightchild);
    }
}
//Function to find the address with the minimum value in the BST
struct address_t* MinValue(struct address_t* value)
{
    struct address_t* temp_var = value;
    
    while (temp_var->leftchild != NULL) 
    {
        temp_var = temp_var->leftchild;
    }
    return(temp_var);
}

//Function to delete the alias based on the alias entered
struct address_t* delete_address(struct address_t* value, char alias[])
{
    if(value == NULL)
    {
        printf("The entered alias does not exist\n");
        return value;
    }
    else if(strcmp(alias,value->alias) < 0)
    {
        value->leftchild = delete_address(value->leftchild,alias);
    }
    else if(strcmp(alias,value->alias) > 0)
    {
        value->rightchild = delete_address(value->rightchild,alias);
        }
        else
        {
            printf("The address for the entered alias is deleted\n");
            if(rootnode->leftchild == NULL)
            {
                struct address_t* temp_var = value;
                value = value -> rightchild;
                free(temp_var);
                return value;
            }
            else if(rootnode->rightchild == NULL)
            {
                struct address_t* temp_var = value;
                value = value -> leftchild;
                free(temp_var);
                return value;
            }
            else if(value->leftchild == NULL && value->rightchild == NULL)
            {
                free(value);
                value = NULL;
                return value;
            }
            else
            {
                struct address_t* temp_var = MinValue(value->rightchild);
                strcpy(value->alias,temp_var->alias);
                value->rightchild = delete_address(value->rightchild,temp_var->alias);
            }
        }
   return value;
}

//Function to update the address based on the entered alias
void update_address(char alias[],int set[4])
{
    struct address_t* value = rootnode;
    if(set[0]<0 || set[1]<0 || set[2]<0 || set[3]<0 || set[0]>255 || set[1]>255 || set[2]>255 || set[3]>255)
    {
        printf("The address is out of range\n");
        return;
    }
    while(value != NULL) 
    {
        if(strcmp(value->alias,alias) == 0)
        {
            value->comp[0] = set[0]; 
            value->comp[1] = set[1]; 
            value->comp[2] = set[2]; 
            value->comp[3] = set[3]; 
            return;
        }else 
        if(strcmp(alias,value->alias) > 0)
        {
            value = value->rightchild;
        }
        else
        {
            value = value->leftchild;
        }      
        }
        printf("Alias and its address does not exist\n");
}

//Function to display Ip address for given alias
void lookup_address(char alias[])
{
    struct address_t *value = rootnode; 
    while(value != NULL)
    {
        if(strcmp(value->alias,alias) == 0)
        {
            printf("Address for alias %s is %d.%d.%d.%d\n",value->alias,value->comp[0],value->comp[1],value->comp[2],value->comp[3]);
            return;
        }
        else if(strcmp(value->alias,alias) > 0)
        {
            value = value->rightchild;
        }else
        {
            value = value->leftchild;
        }
    }
    printf("Address for the entered alias does not exist\n");
}

//Defining a function to check duplicate entries
int duplicate_check(struct address_t * temp_var,int group1,int group2,int group3,int group4,int n)
{
    int var ;
    if(temp_var!=NULL)
    { 
        var = duplicate_check(temp_var->leftchild,group1,group2,group3,group4,n);
        if(temp_var->comp[0] == group1 && temp_var->comp[1] == group2 && temp_var->comp[2] == group3 && temp_var->comp[3] == group4)
        {
            n = 1;
            return n;
        }
        var = duplicate_check(temp_var->rightchild,group1,group2,group3,group4,n);
    }
        else
        {
            return n;
        }
   
}

//function to add new addresses to the Binary tree

void add_address(int group1,int group2,int group3,int group4,char alias[])
{//Checking for valid inputs
    if(strlen(alias) > 10)
    {
        printf("The alias entered is out of range.\n");
        return;
    }
    if(group1<0 || group2<0 || group3<0 || group4<0 ||group1>255 || group2>255 || group3>255 || group4>255 )
    {
        printf("The address entered is out of range\n");
        return;
    }
//Creating a new node and assigning values
    struct address_t *bst_node = (struct address_t*)malloc(sizeof(struct address_t)); 
  
    bst_node->comp[0] = group1; 
    bst_node->comp[1] = group2;
    bst_node->comp[2] = group3;
    bst_node->comp[3] = group4;
    
    strcpy(bst_node->alias, alias);
    
    bst_node->leftchild = NULL;
    bst_node->rightchild = NULL;
    
    if(rootnode == NULL)
    {
        rootnode =  bst_node;  
        return;
    } 
    struct address_t* value = rootnode;
    struct address_t* pnode = rootnode; 
    
    if(duplicate_check(rootnode,group1,group2,group3,group4,0) > 0)
    {
        printf("Duplicate Entry");
        return;
    }
    while(value != NULL)
    {
        if(strcmp(value->alias,alias) > 0)
        {
            pnode = value;
            value = value->leftchild;
        }
        else if(strcmp(value->alias,alias) < 0)
        {
            pnode = value;
            value = value->rightchild;
        }
        else if(strcmp(value->alias,alias) == 0)
        {
            printf("Duplicate Entry");
            return;
        } 
    }
    if(strcmp(pnode->alias,alias) > 0)
    {
        pnode->leftchild = bst_node;
    }
    else
    {
        pnode->rightchild = bst_node;
    }  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Main Function
int main(void)  
{   
   char* group;
   char fname[50]; 
   int i =0,p;
   FILE *fileptr; 
   fileptr = fopen("CS531_Inet.txt","r");
   
   while(fgets(fname,sizeof(fname),fileptr) != NULL)
   {
       int set[4] = {};
       int i =0;
       char* line_var; 
       char alias[20] = {};
       char *stringtoken = strtok(fname," .");
       
       while(stringtoken != NULL)
       {
           if(i != 4)
           {
               set[i] = atoi(stringtoken);
            }else
            { 
                if(stringtoken[strlen(stringtoken)-1] =='\n')   
                stringtoken[strlen(stringtoken)-1] = '\0';
                strcpy(alias,stringtoken);  
            }
            i++;
            stringtoken = strtok(NULL, " .");
        }
        add_address(set[0],set[1],set[2],set[3],alias);  
    }

    while(1)
    {
        printf("\n Menu Options: \n\n1) Add address \n2) Lookup address \n3) Update address \n4) Delete address \n5) Display list \n6) Display aliases for location \n7) Save to file \n8) Quit \n");
        int option ;
        scanf("%d",&option);

        //Option to add new address to the binary tree
        if(option == 1)
        {
            char str_arr[20],c;
            char temp_string[50]="";
            int set[4];
            printf("Enter the IP address and its alias: \n");
            fflush(stdin);
            fgets(temp_string,50,stdin);
            sscanf(temp_string, "%d.%d.%d.%d %s" ,&set[0],&set[1],&set[2],&set[3],str_arr);
            printf("The IP address %d.%d.%d.%d %s is entered successfully\n" ,set[0],set[1],set[2],set[3],str_arr);
            add_address(set[0],set[1],set[2],set[3],str_arr);
        }
        //Option to display address based on the alias entered by the user
        else if(option == 2)
        {
            char alias_str[20];
            printf("Enter the Alias \n");
            scanf("%s",alias_str);
            lookup_address(alias_str);
        }    
        //Option to update the existing address based on the alias entered
        else if(option == 3)
        { 
            char alias[25];
            char temp_string[25];
            int set[4];
            char ch;

            printf("Enter the alias of the address you wish to update: \n");
            scanf("%s",alias); 
            printf("Enter the new address: \n ");    
            fflush(stdin);        
            fgets(temp_string,50,stdin);
            sscanf(temp_string, "%d.%d.%d.%d" , &set[0],&set[1],&set[2],&set[3]);              
            update_address(alias,set);
        }
        //Option to delete an address based on the alias
        else if(option == 4)
        {
            char alias_str[25];
            printf("Enter the alias of the address you wish to delete: \n");
            scanf("%s",alias_str);
            rootnode = delete_address(rootnode,alias_str);
        }   
        //Display all the addresses using inOrder Traversal
        else if(option == 5)
        {
            printf("The addresses present in the BST are : \n");
            displayaddress_IOtraversal(rootnode);   
        }
        //Option to display address based on locality
        else if(option == 6)
        {
            char loc[25]; 
            int loc_set[2];
            printf("Enter the locality of the addresses you wish to display\n");
            scanf("%s",loc);
            sscanf(loc, "%d.%d" , &loc_set[0],&loc_set[1]);
            if(loc_set[0]<0 || loc_set[1]<0 || loc_set[0]>255 || loc_set[1]>255 )
            {
                printf("The locality entered is out of range\n");
            }else
            {
                int n = display_aliasaddress(rootnode,loc_set[0],loc_set[1],0);
                if(n == 0)
                {
                    printf("The address for the given locality not found\n");
                }
            }
        }
        else if(option == 7)
        {
            FILE * fptr;    
            char file[20];
            printf("Enter the file name : \n");
            scanf("%s",file); 
            fptr = fopen (file, "w+");     
            save_address(rootnode,fptr);
            fclose(fptr); 
        }
        else if(option == 8)
        {
            printf("Thank You!");
            break;
        }else
        {
            printf("Invalid input.");
        }
    }
}
