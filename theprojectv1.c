#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

float unitscharge(int, int);
float fine(float);
int header();
int login();

int main() {
    char id[10], name[20];
    int pcount, ccount, units, watercharge, size, housenumber; 
    float withVAT, total, dues, penalty;
    FILE *buddha;

    login();
    header();

    buddha = fopen("record.txt", "a"); // Open the file in append mode
    if (buddha == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    while (1) {
        printf("Name of the consumer: ");
        scanf("%s", name);
        if (name[0] == '0') {
            break;
        }

        printf("\nConsumer's ID: ");
        scanf("%s", id);
        printf("\nHouse Number: ");
        scanf("%d", &housenumber);
        printf("\nConsumer Type: (Type and hit enter the corresponding serial number) \n1. 0.5 Inch \n2. 0.75 Inch\n3. 1 Inch \n4. 1.5 Inch\n5. 2 Inches\n6. 3 Inches\n7. 4 Inches\n");
        scanf("%d", &size);
        printf("\nDues (If any): Rs. ");
        scanf("%f", &dues);
        printf("\nPreceding Reading: ");
        scanf("%d", &pcount);
        printf("\nCurrent Reading: ");
        scanf("%d", &ccount);
        
        if (ccount<pcount ||  (size<0 && size >7)) {
            printf("Couldn't proceed ahead!\n");
            return 0;
        }
        
        units = ccount - pcount;
        watercharge = unitscharge(units, size); 
        withVAT = watercharge + (0.13) * watercharge;    
        penalty = fine(dues);
            
        printf("\n.............................\n");
        printf("Consumed Units: %d\n", units);
        printf("Cost for %d units: Rs. %d\n", units, watercharge);
        printf("Cost with VAT: Rs. %f\n", withVAT);  
        printf("Cost with dues: %f\n", (withVAT + dues));
        if (penalty > 0) {
            printf("Total charge with penalty: Rs. %f\n", withVAT + dues + penalty);
        }

        fprintf(buddha, "The record is of: %s\n", name);
        fprintf(buddha, "Consumer's ID: %s\n", id);
        fprintf(buddha, "Home Number: %d\n", housenumber);
        fprintf(buddha, "Units Consumed: %d\n", units);
        fprintf(buddha, "Water Charge: %d\n", unitscharge(units, size));
        fprintf(buddha, "Dues: %f\n", dues);
        fprintf(buddha, "Charge With VAT: %f\n", withVAT);
        fprintf(buddha, "Penalty Amount: %f\n", penalty);
        fprintf(buddha, "Net Amount: %f\n", withVAT + dues + penalty);
        fprintf(buddha, "*************************************\n\n\n");
        printf("\n\n\n\n");
    }

    fclose(buddha); // Close the file after processing all entries
    return 0;
}

float unitscharge(int units, int size) {
    int amount = 0, mincharge, totalcharge;
    
    if (size == 1) {
        mincharge = 100;
        if (units > 10) {
            amount = (units - 10) * 32;
        }
    }
    
    if (size == 2) {
        mincharge = 1910;
        if (units > 27) {
            amount = (units - 27) * 71;
        }
    }
    
    if (size == 3) {
        mincharge = 3960;
        if (units > 56) {
            amount = (units - 56) * 71;
        }
    }
    
    if (size == 4) {
        mincharge = 10950;
        if (units > 155) {
            amount = (units - 155) * 71;
        }
    }
    
    if (size == 5) {
        mincharge = 22600;
        if (units > 320) {
            amount = (units - 320) * 71;
        }
    }    
    
    if (size == 6) {
        mincharge = 62240;
        if (units > 881) {
            amount = (units - 881) * 71;
        }
    }
    
    if (size == 7) {
        mincharge = 127865;
        if (units > 1810) {
            amount = (units - 1810) * 71;
        }
    }
    totalcharge = amount + mincharge;
    return totalcharge;
} 

float fine(float dues) {
    if (dues > 500) {
        return (0.05 * dues);
    }
    return 0;
}

int header() {
    printf("\t\t\t\t\t Arniko Drinking Water Project\n");
    printf("\t\t\t\t\t .............................\n\n\n");
    printf("Input as Instructed! \nEntering 0 as the name of the consumer terminates the input process.\n\n");
    return 0;
}

int login() {
    int try = 5;
    char text[5], key[] = "12345";
    while(try>0) {
        int flag = 0;
        printf("Password: \n");
        for (int i=0; i<5; i++) {
            text[i] = getch();
            printf("*");
            if (text[i] != key[i]) {
                flag = 1;    
            }
        }
        
        if (flag == 0) {
            printf("\nPlease, Wait while the interface is loading!\n");
            for (int i=0; i<5; i++) {
                sleep(1);
                printf("~");
            }
            system("cls");
            return 0;
        }
        else {
            try --;
            printf("\nIncorrect Password. Try again. \n");
        }
    }
    printf("Too many wrong attempts were encountered. \nWait a minute to retry. \n");
    sleep(60);
    login();
    return 0;
}
