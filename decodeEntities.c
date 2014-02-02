#include <string.h>

void stringFromCharCode(int code,char *out)
{
  out[0] = code;
  out[1] = '\0';
}

void stringCharAt(char *str,int loc,char *out)
{
  out[0] = str[loc];
  out[1] = '\0';
}

ascTableRef(

char *decodeEntities(char *param1)
{
  char loc2[100];
  char loc3[100];
  char loc4[100];
  char loc5[100];
  char loc6[100];
  int i;
  char out[2] = {0,0};
  
  loc2 = "";
  while (i < strlen(param1))
  {
    stringCharAt(param1,i,loc3);
    if (streq(loc3,"&")
    {
      strcpy(loc4,loc3);
      do
      {
        i++;
        stringCharAt(param1,i,loc5);
        strcat(loc4,loc5);
      
      } while (!streq(loc,";") && i < strlen(param1));
      loc6 = ascTabRev[loc4];
      if (loc6 != NULL)
      {
        strcat(loc2,loc6);
      
      } else {
        stringFromCharCode(loc4,out);
        strcat(loc2,out);
      }
    
    
    
    }
  
  
  }





}