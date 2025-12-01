#include <stdio.h>
#include "validate.h"
#include "contact.h"
#include <string.h>
int validate_name(char *name)
{
    int flag;
    for(int i=0;name[i]!='\0';i++)
    {   
        flag=0;
        if(name[i]>='A' && name[i]<='Z' || 
            name[i]>='a' && name[i]<='z' ||
            name[i]==' ')
        {
            flag =1;
        }
        else
        {
            printf("\033[0;31mERROR:Enter a valid name without numeric values or symbols!\033[0m\n");
            return 0;
        }
    }
    if(flag==1)
    {
        return 1;
    }
}
int validate_phone(char *phone)
{
    int len=0;
    for (int i = 0;phone[i]!='\0';i++)
    { 
        len++;
    }
   // printf("%d",len);
    if(len!=10)
    {
        printf("\033[0;31mERROR: Enter a Valid 10 digits Phone Number\033[0m\n");
        return 0;
    }
    int count=0;
    for(int i=0;phone[i]!='\0';i++)
    {
        count++;
        if(phone[i]<'0')
        {
            printf("\033[0;31mERROR: Enter Only Valid Numeric Values\033[0m\n");
            return 0;
        }
    }
    
    if(count==10)
    {
        return 1;
    }
}
int validate_mail(char *mail)
{
    int len=0;
    for (int i = 0;mail[i]!= '\0';i++)
    { 
        len++;
    }
    int space=0;
    int at_point=-1;
    int dot_point=-1;

    for(int i=0;mail[i]!='\0';i++)
    {
        if(mail[i]>='A' && mail[i]<='Z')
        {
            printf("\033[0;31mERROR: Enter Only Lower Case Alphanumeric Characters\033[0m\n");
            return 0;
        }
        if(mail[i]==' ')
        {
            printf("\033[0;31mERROR: Spaces are not allowed\033[0m");
            return 0;
        }
        if(mail[i]=='@')
        {
            if(at_point!=-1)
            {
                printf("\033[0;31mERROR: Multiple @ Symbols Character Found\033[0m");
                return 0;
            }
            at_point=i;
        }
        if(mail[i]=='.')
        {
            dot_point=i; //position of last dot
        }
    }
    if(at_point==-1 || dot_point==-1)
    {
        printf("\033[0;31mERROR: no @ or . symbol are present\033[0m\n");
        return 0;
    }
    if(at_point==0 || at_point==len-1)
    {
         printf("\033[0;31mERROR: @ symbol cannot be at the end or starting\033[0m\n");
        return 0;
    }
    if(dot_point==len-1)
    {
        printf("\033[0;31mERROR: Dot symbol cannot be at the end\033[0m\n");
        return 0;
       
    }
    if(dot_point<at_point)
    {
        printf("\033[0;31mERROR: last dot must come after at symbol\033[0m\n");
        return 0; 
    }
    if(dot_point-at_point<=1)
    {
        printf("\033[0;31mERROR: must be characters between @ and last dot\033[0m\n");
        return 0;  
    }
   const char gmail[] = "gmail.com";
    int i=at_point+1;    // index in input mail
    int j=0;               // index in gmail_domain
    while (gmail[j])
    {
        if (mail[i]!=gmail[j])
        {
            printf("\033[0;31mERROR: Only gmail.com addresses are allowed\033[0m\n");
            return 0;
        }
        i++;
        j++;
    }
    if (mail[i]!='\0')
    {
        printf("\033[0;31mERROR: Only gmail.com addresses are allowed\033[0m\n");
        return 0;
    }
    return 1;
}


