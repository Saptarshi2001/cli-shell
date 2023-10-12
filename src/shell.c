#define LSH_RL_BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
#include <windows.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<tchar.h>
#include<conio.h>
#include<unistd.h>
#include<assert.h>
#include<sys/stat.h>
#include"shell.h"
#include"test.h"
const char *builtins[] = {"cd","mkdir","help", "exit","echo","cls","color","grp"};
int (*builtins_fun[])(char **) =
    {
        &sh_cd,
        &sh_mkdir,
        &sh_help,
        &sh_exit,
        &sh_echo,
        &sh_clear,
        &sh_color,
        &sh_grep
};

int size()
{
    return sizeof(builtins) / sizeof(char *);
}

int sh_cd(char **args)
{
    char* store;
    DWORD DW;
    if (args[1] == NULL)
    {
        fprintf(stderr, "Error");
    }
    else if(args[1]=="..")
    {
       chdir(".."); 
    }
    else
    {

        if (chdir(args[1])!=0)
        {
            fprintf(stderr, "Oops");
            printf("\n");
            return 0;
        }

    }
    store=_getcwd(store,sizeof(MAX_PATH));
   /* printf("Directory changed ");*/
    printf("%s ",store);
    return 1;
}

int sh_mkdir(char **args)
{
int result;
result=CreateDirectory(args[1],NULL);
if(args[1]==NULL)
{
    fprintf(stderr,"No directory created \n");
    return 0;
}
else if(result==0)
{
if(errno==ERROR_ALREADY_EXISTS)
{
    fprintf(stderr,"Directory already present \n"); 
    return 0;
}
else if(errno==ERROR_PATH_NOT_FOUND)
{
    fprintf(stderr,"Path not found \n");
    return 0;
}
else
{
printf("Directory created \n");
}
}
return 1;
}

int sh_help()
{
    printf("\n");
    printf("HERE ARE THE COMMANDS \n");
    for (int j = 0; j < size(); j++)
    {
        printf("%s\n", builtins[j]);
        printf("\n");
    }
    printf("Please refer to man pages for documentation \n");
    return 1;
}

int sh_exit()
{
    return 0;
}

int sh_echo(char**args)
{
char ch;
 if(args[1]=="NULL")
{
    printf("ECHO MODE ON!! BUT TYPE SOMETHING PLEASE"); 
}
else
{
 int k=1; 
  while(k<LSH_TOK_BUFSIZE && args[k]!=NULL)
    {   
   printf("%s ",args[k]);
   k++;
    }
   printf("\n");
}
return 1;
}

int sh_clear()
{
    system("cls");
    return 1;
}

int sh_color()
{
    char col;
    char backcol;
    printf("Press any of the keys in the table for seting background and foreground color \n");
    printf("Here's the table \n");
    printf("Color id	Color	Color id	Color \n"); 
    printf( "1	        Aqua	A	        Light  Green \n");
    printf( "2	        Green	0	        Black \n");
    printf( "3	        Blue	9	        Light  Blue \n");
    printf( "4	        Red	    B	        Light  Aqua \n");
    printf( "5	        Purple	C	        Light  Red \n");
    printf( "6	        Yellow	D	        Light  Purple \n");
    printf( "7	        White	E	        Light  Yellow \n");
    printf( "8	        Gray	F	        Bright White \n");
    printf("Enter the background color >>");
    scanf(" %c",&backcol);
    printf("Enter the foreground color >>");
    scanf(" %c",&col);
    char command[50];
    snprintf(command,sizeof(command),"Color %c%c",backcol,col);
    system(command);
    return 1;
}
int sh_grep(char **args)
{
    char ch[200];
    
    if(args[1]==NULL||args[2]==NULL)
    {
        fprintf(stderr,"No pattern to be searched");
        return 0;
    }
    
    else 
    {  
    FILE *point=fopen(args[2],"r");
    if(!point)
    {
    fprintf(stderr,"Unable to locate file");
    return 0;
    }
            
    while(fgets(ch,200,point))
    {
    char *found;
             found=strstr(ch,args[1]);
             if(found)
             { 
              for(int j=0;j<strlen(ch);j++)
            {    
            printf("%c",ch[j]);
              }
             }
            }
            fclose(point);
    }
        
    return 1;
}
int sh_launch(char **args)
{
STARTUPINFO si;
PROCESS_INFORMATION pi;
ZeroMemory(&si,sizeof(si));
si.cb=sizeof(si);
ZeroMemory(&pi,sizeof(pi));
if(!CreateProcess(NULL,
        args[0],        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi 

))
{
printf("Process Creation failed");
return 0;
}
WaitForSingleObject(pi.hProcess,INFINITE);
CloseHandle(pi.hProcess);
CloseHandle(pi.hThread);
return 1;
}

int sh_execute(char **splitline)
{
    if (splitline[0] == NULL)
    {
        return 1;
    }
    for (int i = 0; i < size(); i++)
    {
        if (strcmp(splitline[0], builtins[i]) == 0)
        {
            return (*builtins_fun[i])(splitline);
        }
    }
    return sh_launch(splitline);
}

char *readline()
{
    int status;
    char *line;
    int buff_size = LSH_RL_BUFSIZE;
    int position = 0;
    int c;
    line = (char *)malloc(buff_size * sizeof(char));
    if (!line)
    {
        printf("No space allocated");
    }

    while (1)
    {
        
        c = getchar();
        if (c == EOF || c =='\n')
        {
         
         line[position] = '\0';
         break;
        }
     else if((GetAsyncKeyState(VK_MENU)&0x8000)&&(GetAsyncKeyState('U')&0x8000))
       {
        printf("Hello");
       }
        else if (position > buff_size)
        {
            buff_size+=LSH_RL_BUFSIZE;
            line = (char *)realloc(line, sizeof(char) * buff_size);
            if(!line)
            {
                fprintf(stderr,"Reallocation unsuccesfull");
            }
        }
        
        else
        {
            line[position] = c;
            position++;
        }
        
    }    
    return line;
}


char **splitline(char *line)
{

    int buff_size = LSH_TOK_BUFSIZE;
    char **tokens;
    char *token;
    int pos = 0;
    tokens = malloc(sizeof(char *) * buff_size);
    if (!tokens)
    {
        fprintf(stderr, "Allocation unsuccesfull");
    }
    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL)
    {
        tokens[pos] = token;
        pos++;

        if (pos >= buff_size)
        {
            buff_size+=LSH_TOK_BUFSIZE;
            tokens = (char **)realloc(tokens, sizeof(char *) * buff_size);
            if (!tokens)
            {
                fprintf(stderr, "Allocation unsuccesfull");
            }
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[pos] = NULL;
    return tokens;
}

void read_all()
{
    char *line;
    char **split;
    int status;
    printf("Welcome to the holy command line \n");
    do
    {
        printf(">>");
        line = readline();
        split = splitline(line);
        status= sh_execute(split);
    } while (status);
    free(line);
    free(split);
}

int main()
{
    test_cls();
    test_grep();
    test_echo();
    test_cd();
    test_mkdir();
    test_help();
    test_exit();
    test_color();
    read_all();
}