#include <stdio.h>
#define LF 10

int main()
{
    char control;
    char dgt1,dgt2,dgt3,dgt4,dgt5,dgt6;
    int digitNumber=0;
    int option;
    int isValid;

    printf("Welcome to MAC analyzer!\n");

    while(option!=5)
    {
        fflush(stdin);
        printf("Please enter a MAC address: ");
        control=0;

        while(control != LF)
        {
            scanf("%c", &control);
            digitNumber++;
            //printf("%d ",control);

            switch(digitNumber)
            {
                case 1:
                    dgt1 = control;
                    break;
                case 2:
                    dgt2 = control;
                    break;
                case 4:
                    dgt3 = control;
                    break;
                case 5:
                    dgt4 = control;
                    break;
                case 7:
                    dgt5 = control;
                    break;
                case 8:
                    dgt6 = control;
                    break;
                default:
                    break;
            }

            if(((control >= 48 && control<=57) || (control >= 65 && control<=70))!=1 && digitNumber%3 != 0)
            {
                isValid=0;
                break;
            }
            else if (control != 45 && digitNumber%3 == 0 && digitNumber != 18)
            {
                isValid=0;
                break;
            }
            else if (control != '\n' && digitNumber==18)
            {
                isValid=0;
                break;
            }
            else if(digitNumber!=18)
            {
                isValid=0;
            }
            else
            {
                isValid=1;
                break;
            }
        }

        if(isValid)
        {
            option = 6;
            while(option!=5 && option != 0)
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
                        break;
                }
            }
        }
        else
        {
            printf("This is not a valid MAC address!\n");
        }

        digitNumber = 0;
    }
    return 0;
}
