#include <stdio.h>
#include "validate.h"
#include "contact.h"
#include <string.h>
int validate_name(char *name) //validating input of name field 
{
    int check;
    for(int i=0;name[i]!='\0';i++) //iterating through each character of name
    {   
        check=0;
        //if character is alphabet or space then valid, else invalid
        if(name[i]>='A' && name[i]<='Z' ||
            name[i]>='a' && name[i]<='z' ||
            name[i]==' ')
        {
            check=1; //changing flag to 1 if valid character
        }
        else
        {
            printf("\033[0;31mERROR:Enter a valid name without numeric values or symbols!\033[0m\n");
            return 0;
        }
    }
    if(check==1)
    {
        return 1; //if check is 1 for all characters, return valid
    }
}
int validate_phone(char *phone)//validating input of phone number field
{
    int len=0;
    for (int i = 0;phone[i]!='\0';i++)
    { 
        len++; //deriving length of phone number
    }
    if(len!=10) //if length is not 10 digits, invalid
    {
        printf("\033[0;31mERROR: Enter a Valid 10 digits Phone Number\033[0m\n");
        return 0;
    }
    int count=0;
    for(int i=0;phone[i]!='\0';i++) //iterating through each character of phone number
    {
        if(phone[i]>='0' && phone[i]<='9')//if character is numeric digit
         {
            count++;    //incrementing count of numeric digits
            continue; //continue to next character
        }
        else 
        {
            printf("\033[0;31mERROR: Enter Only Valid Numeric Values\033[0m\n"); 
            return 0;
        }
    }
    if(count==10) //if count of numeric digits is 10 and all characters are valid one, return valid
    {
        return 1;
    }
}
int validate_mail(char *mail) //validating input of email field
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
        if(mail[i]>='A' && mail[i]<='Z') //if uppercase alphabet
        {
            printf("\033[0;31mERROR: Enter Only Lower Case Alphanumeric Characters\033[0m\n");
            return 0;
        }
        if(mail[i]==' ') //if space is found in email
        {
            printf("\033[0;31mERROR: Spaces are not allowed\033[0m");
            return 0;
        }
        if(mail[i]=='@') //if @symbol is found
        {
            if(at_point!=-1)
            {
                printf("\033[0;31mERROR: Multiple @ Symbols Character Found\033[0m");
                return 0;
            }
            at_point=i;
        }
        if(mail[i]=='.') //if dot symbol is found
        {
            dot_point=i; //position of last dot
        }
    }
    if(at_point==-1 || dot_point==-1) //if @ or . symbol is not found
    {
        printf("\033[0;31mERROR: @ or . symbol is not present in given email\033[0m\n");
        return 0;
    }
    if(at_point==0 || at_point==len-1) //if @ is at starting or end
    {
         printf("\033[0;31mERROR: @ symbol cannot be at the end or starting of email\033[0m\n");
        return 0;
    }
    if(dot_point==len-1) //if dot is at the end
    {
        printf("\033[0;31mERROR: Dot(.) symbol cannot be at the end\033[0m\n");
        return 0;
       
    }
    if(dot_point<at_point) //if last dot is before @ symbol
    {
        printf("\033[0;31mERROR: last dot(.) symbol must come after @ symbol\033[0m\n");
        return 0; 
    }
    if(dot_point-at_point<=1) //if there are no characters between @ and last dot
    {
        printf("\033[0;31mERROR: must be characters between @ and last dot\033[0m\n");
        return 0;  
    }
    const char gmail[] = "gmail.com";
    int i=at_point+1;    // index in input mail
    int j=0;               // index in gmail_domain
    while (gmail[j])
    {
        if (mail[i]!=gmail[j]) //comparing each character of domain with gmail.com
        {
            printf("\033[0;31mERROR: Only gmail.com addresses are allowed\033[0m\n");
            return 0;
        }
        i++;
        j++;
    }
    if (mail[i]!='\0') //if there are extra characters after gmail.com
    {
        printf("\033[0;31mERROR: Only gmail.com addresses are allowed\033[0m\n");
        return 0;
    }
    return 1; //if all conditions are satisfied, return valid
}


