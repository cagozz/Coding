#include <stdio.h>

int main()
{

    char dgt1,dgt2,dgt3,dgt4,dgt5,dgt6,dgt7,dgt8,dgt9,dgt10,dgt11,dgt12;
    char control;
    //char line1,line2,line3,line4,line5;
    int option;


    printf("Welcome to MAC analyzer!\n");

    while(option != 5)
    {
        printf("Please enter a MAC address: ");
        dgt1=90,dgt2=90,dgt3=90,dgt4=90,dgt5=90,dgt6=90,dgt7=90,dgt8=90,dgt9=90,dgt10=90,dgt11=90,dgt12=90;
        fflush(stdin);
        scanf("%c%c-%c%c-%c%c-%c%c-%c%c-%c%c",&dgt1,&dgt2,&dgt3,&dgt4,&dgt5,&dgt6,&dgt7,&dgt8,&dgt9,&dgt10,&dgt11,&dgt12);
        //printf("%d",dgt1);

        if(((dgt1 >= 48 && dgt1<=57) || (dgt1 >= 65 && dgt1<=70))
           &&((dgt2 >= 48 && dgt2<=57) || (dgt2 >= 65 && dgt2<=70))
           //&&(line1=='-')
           &&((dgt3 >= 48 && dgt3<=57) || (dgt3 >= 65 && dgt3<=70))
           &&((dgt4 >= 48 && dgt4<=57) || (dgt4 >= 65 && dgt4<=70))
           //&&(line2=='-')
           &&((dgt5 >= 48 && dgt5<=57) || (dgt5 >= 65 && dgt5<=70))
           &&((dgt6 >= 48 && dgt6<=57) || (dgt6 >= 65 && dgt6<=70))
           //&&(line3=='-')
           &&((dgt7 >= 48 && dgt7<=57) || (dgt7 >= 65 && dgt7<=70))
           &&((dgt8 >= 48 && dgt8<=57) || (dgt8 >= 65 && dgt8<=70))
           //&&(line4=='-')
           &&((dgt9 >= 48 && dgt9<=57) || (dgt9 >= 65 && dgt9<=70))
           &&((dgt10 >= 48 && dgt10<=57) || (dgt10 >= 65 && dgt10<=70))
           //&&(line5=='-')
           &&((dgt11 >= 48 && dgt11<=57) || (dgt11 >= 65 && dgt11<=70))
           &&((dgt12 >= 48 && dgt12<=57) || (dgt12 >= 65 && dgt12<=70)))
           /*&&(control == '\n'))*/
        {
            option = 6;
            while(option != 5 && option != 0)
            {
                printf("==================\n1. Is It Unicast or Multicast?\n2. Is It Global or Local?\n3. What is the Manufacturer Info?\n4. Enter Another MAC address\n5. Exit\n==================\n");
                printf("What would you like to do? ");
                scanf("%d", &option);
                fflush(stdin);

                switch(option)
                {
                    case 1:
                        printf("\nIs It Unicast or Multicast?\n");
                        if(dgt2==48 || dgt2==50 || dgt2==52 || dgt2==54 || dgt2==56
                           || dgt2==65 || dgt2==67 || dgt2==69)
                        {
                            printf("Unicast: First bit = 0.\n\n");
                        }
                        else
                        {
                            printf("Multicast: First bit = 1.\n\n");
                        }
                        break;
                    case 2:
                        printf("\nIs It Global or Local?\n");
                        if(dgt2==48 || dgt2==49 || dgt2==52 || dgt2==53 || dgt2==56
                           || dgt2==57 || dgt2==67 || dgt2==68)
                        {
                            printf("Global: Second bit = 0.\n\n");
                        }
                        else
                        {
                            printf("Local: Second bit = 1.\n\n");
                        }
                        break;
                    case 3:
                        printf("\nWhat is the Manufacturer Info?\n");
                        if((dgt1==67&&dgt2==67&&dgt3==52&&dgt4==54&&dgt5==68&&dgt6==54)
                           ||(dgt1==48&&dgt2==48&&dgt3==48&&dgt4==56&&dgt5==50&&dgt6==48))
                        {
                            printf("Manufacturer Info: Cisco\n\n");
                        }
                        else if((dgt1==51&&dgt2==67&&dgt3==53&&dgt4==65&&dgt5==66&&dgt6==52))
                        {
                            printf("Manufacturer Info: Google\n\n");
                        }
                        else if((dgt1==48&&dgt2==48&&dgt3==57&&dgt4==65&&dgt5==67&&dgt6==68))
                        {
                            printf("Manufacturer Info: Huawei\n\n");
                        }
                        else
                        {
                            printf("Manufacturer Info: Unknown\n\n");
                        }
                        break;
                    case 4:
                        option = 0;
                        break;
                    case 5:
                        option = 5;
                        break;
                    default:
                        printf("It is not valid option!\n");
                        break;
                }

            }
        }
        else
        {
            printf("This is not a valid MAC address!\n");
        }
    }
    return 0;
}
