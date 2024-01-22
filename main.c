#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

struct weights {
 char month[100];
 float weight;
};

struct dates {
 int year;
 int month;
 int date;
};

struct vaccinations {
 char nameOfVaccination[100];
 struct dates dateOfVaccination;
};

struct infants {
  int id;
  char name[100];
  struct dates dateOfBirth;
  struct weights weight[5];
  struct vaccinations vaccination[5];

};

void createRecord(void);
void readRecords(void);
bool compareBirthday(struct dates d1, struct dates d2);
void sortD(void);
void sortA(void);
int compareNames(const void *a, const void *b);
int deleteItemFromArray(struct infants *array, int size, int index);
void deleteRecord(void);
void updateRecord(void);

int main(void){
 char choice;
 puts("\n--------------SIMPLE CRUD APPLICATION----------------");
 puts("\n------------------Available choices------------------");
 puts("N / n - CREATE NEW RECORD");
 puts("U / u - UPDATE RECORD");
 puts("R / r - READ RECORDS");
 puts("D / d - DELETE A RECORD");
 puts("S / s - SORT ACCORDING TO THE ALPHABET");
 puts("T / t - SORT ACCORDING TO THE DATE OF BIRTH");
 puts("Q / q - EXIT");
 printf("Enter your choice -> ");scanf(" %c", &choice);

 while(choice!= EOF){
  switch(choice){
    case 'N':
    case 'n':
       createRecord();
       break;
    case 'R':
    case 'r':
       readRecords();
       break;
    case 'U':
    case 'u':
       updateRecord();
       break;
    case 'D':
    case 'd':
       deleteRecord();
       break;
    case 'S':
    case 's':
       sortA();
       break;
    case 'T':
    case 't':
       sortD();
       break;
    case 'Q':
    case 'q':
       puts("Terminating....");
       return 0;
    default:
       puts("\nInvalid choice");
       
  }
  puts("\n--------------SIMPLE CRUD APPLICATION----------------");
  puts("\n------------------Available choices------------------");
  puts("N / n - CREATE NEW RECORD");
  puts("U / u - UPDATE RECORD");
  puts("R / r - READ RECORDS");
  puts("D / d - DELETE A RECORD");
  puts("S / s - SORT ACCORDING TO THE ALPHABET");
  puts("T / t - SORT ACCORDING TO THE DATE OF BIRTH");
  puts("Q / q - EXIT");
  printf("Enter your choice -> ");scanf(" %c", &choice);
 }
 return 0;
}

//***************
//CRUD operations
//***************

//CREATE
void createRecord(void){
 struct infants infant;
 FILE *fptr;
 fptr = fopen("inf.dat","ab");
 if(!fptr){
  return;
 }

 printf("==================CREATE A RECORD==================");
 //Name
 printf("\nEnter infant's name : ");scanf("%s",&infant.name);
 //printf("\nEnter infant's name : ");fgets(infant.name, sizeof(infant.name),stdin);
 printf("\nEnter infant's ID : ");scanf("%d",&infant.id);

 //DateOfBirth
 printf("\nEnter infant's Date of birth : ");
 printf("\n\tYear :");scanf("%d",&infant.dateOfBirth.year);
 printf("\n\tMonth :");scanf("%d",&infant.dateOfBirth.month);
 printf("\n\tDate :");scanf("%d",&infant.dateOfBirth.date);

 //MonthlyWeights
 printf("\nEnter infant's monthly weights below : ");
 //Month 01
 printf("\n\tMonth 01");
 printf("\n\t\tMonth (STRING) : ");scanf("%s",&infant.weight[0].month);
 printf("\n\t\tWeight (FLOAT) : ");scanf("%f",&infant.weight[0].weight);
 //Month 02
 printf("\n\tMonth 02");
 printf("\n\t\tMonth (STRING): ");scanf("%s",&infant.weight[1].month);
 printf("\n\t\tWeight (FLOAT): ");scanf("%f",&infant.weight[1].weight);

 //Vaccines
 printf("\nEnter infant's vaccine Details below : ");
 //Vaccine 01
 printf("\n\tVACCINE 01");
 printf("\n\t\tName of the Vaccine :");scanf("%s",&infant.vaccination[0].nameOfVaccination);
 printf("\n\t\tVaccined date :");
 printf("\n\t\t\tYear (INTIGER): ");scanf("%d",&infant.vaccination[0].dateOfVaccination.year);
 printf("\n\t\t\tMonth (INTIGER): ");scanf("%d",&infant.vaccination[0].dateOfVaccination.month);
 printf("\n\t\t\tDate (INTIGER): ");scanf("%d",&infant.vaccination[0].dateOfVaccination.date);
 //Vaccine 02
 printf("\n\tVACCINE 02");
 printf("\n\t\tName of the Vaccine :");scanf("%s",&infant.vaccination[1].nameOfVaccination);
 printf("\n\t\tVaccined date :");
 printf("\n\t\t\tYear (INTIGER): ");scanf("%d",&infant.vaccination[1].dateOfVaccination.year);
 printf("\n\t\t\tMonth (INTIGER): ");scanf("%d",&infant.vaccination[1].dateOfVaccination.month);
 printf("\n\t\t\tDate (INTIGER): ");scanf("%d",&infant.vaccination[1].dateOfVaccination.date);

 fwrite(&infant, sizeof(struct infants), 1, fptr);
 fclose(fptr);
} 

//READ
void readRecords(void){
 int j = 0;
 FILE *fptr;
 fptr = fopen("inf.dat", "rb");
 struct infants infant[15];
 while (fread(&infant[j], sizeof(struct infants), 1, fptr) == 1) {
  j++;
  }
 fclose(fptr);

 if(j <= 0){
  printf("\nDatabase is empty.");
  return;
 }
 
 for(int i = 0; i < j; i++){
  printf("\n---------------------------------------------");
  printf("\nInfant-%d",i+1);
  printf("\n\tName - %s",infant[i].name);
  printf("\n\tID - %d",infant[i].id);
  printf("\n\tDate of Birth(dd/mm/yy) - %d/%d/%d",infant[i].dateOfBirth.date,infant[i].dateOfBirth.month,infant[i].dateOfBirth.year);
  printf("\n\tMonthly Weights : ");
  printf("\n\t\t%s - %.2f kg",infant[i].weight[0].month,infant[i].weight[0].weight);
  printf("\n\t\t%s - %.2f kg",infant[i].weight[1].month,infant[i].weight[1].weight);
  printf("\n\tVaccinaitons : ");
  printf("\n\t\t%s - %d/%d/%d (dd/mm/yy)",infant[i].vaccination[0].nameOfVaccination,infant[i].vaccination[0].dateOfVaccination.date,infant[i].vaccination[0].dateOfVaccination.month,infant[i].vaccination[0].dateOfVaccination.year);
  printf("\n\t\t%s - %d/%d/%d (dd/mm/yy)",infant[i].vaccination[1].nameOfVaccination,infant[i].vaccination[1].dateOfVaccination.date,infant[i].vaccination[1].dateOfVaccination.month,infant[i].vaccination[1].dateOfVaccination.year);
 }
}

//SORTING ACCORDING TO DATE OF BIRTH
void sortD(void){
  FILE *fptr;
  fptr = fopen("inf.dat", "rb");
  int j = 0;

  struct infants temp;
  struct infants infant[15];
  
  while(fread(&infant[j], sizeof(struct infants), 1, fptr) == 1) {
    j++;
  }
  fclose(fptr);
  if(j <= 0){
    printf("\nDatabase is empty.");
    return;
  }
  //Sorting with bubblesort
  for(int i = 0; i < j-1;i++){
    for(int k = 0; k < j - i - 1 ; k++)
      if(compareBirthday(infant[k].dateOfBirth,infant[k+1].dateOfBirth)){
        temp = infant[k+1];
        infant[k+1] = infant[k];
        infant[k] = temp;
      }
  }
  printf("\n---------------------------------------------------");
  printf("\n---------SORTED ACCORDING TO DATE OF BIRTH---------");
  for(int i = 0; i < j; i++){
    printf("\n---------------------------------------------");
    printf("\nInfant-%d",i+1);
    printf("\n\tName - %s",infant[i].name);
    printf("\n\tID - %d",infant[i].id);
    printf("\n\tDate of Birth(dd/mm/yy) - %d/%d/%d",infant[i].dateOfBirth.date,infant[i].dateOfBirth.month,infant[i].dateOfBirth.year);
    printf("\n\tMonthly Weights : ");
    printf("\n\t\t%s - %.2f kg",infant[i].weight[0].month,infant[i].weight[0].weight);
    printf("\n\t\t%s - %.2f kg",infant[i].weight[1].month,infant[i].weight[1].weight);
    printf("\n\tVaccinaitons : ");
    printf("\n\t\t%s - %d/%d/%d (dd/mm/yy)",infant[i].vaccination[0].nameOfVaccination,infant[i].vaccination[0].dateOfVaccination.date,infant[i].vaccination[0].dateOfVaccination.month,infant[i].vaccination[0].dateOfVaccination.year);
    printf("\n\t\t%s - %d/%d/%d (dd/mm/yy)",infant[i].vaccination[1].nameOfVaccination,infant[i].vaccination[1].dateOfVaccination.date,infant[i].vaccination[1].dateOfVaccination.month,infant[i].vaccination[1].dateOfVaccination.year);
 }

}

//SORT ACCORDING TO THE ALPHABET
void sortA(void){
  FILE *fptr;
  fptr = fopen("inf.dat", "rb");
  int j = 0;
  struct infants infant[15];

  while(fread(&infant[j], sizeof(struct infants), 1, fptr) == 1) {
    j++;
  }
  fclose(fptr);
  if(j <= 0){
    printf("\nDatabase is empty.");
    return;
  }
  qsort(infant,j,sizeof(struct infants),compareNames);
  printf("\n---------------------------------------------------");
  printf("\n---------------SORTED ALPHABATACALY----------------");
  for(int i = 0; i < j; i++){
    printf("\n---------------------------------------------");
    printf("\nInfant-%d",i+1);
    printf("\n\tName - %s",infant[i].name);
    printf("\n\tID - %d",infant[i].id);
    printf("\n\tDate of Birth(dd/mm/yy) - %d/%d/%d",infant[i].dateOfBirth.date,infant[i].dateOfBirth.month,infant[i].dateOfBirth.year);
    printf("\n\tMonthly Weights : ");
    printf("\n\t\t%s - %.2f kg",infant[i].weight[0].month,infant[i].weight[0].weight);
    printf("\n\t\t%s - %.2f kg",infant[i].weight[1].month,infant[i].weight[1].weight);
    printf("\n\tVaccinaitons : ");
    printf("\n\t\t%s - %d/%d/%d (dd/mm/yy)",infant[i].vaccination[0].nameOfVaccination,infant[i].vaccination[0].dateOfVaccination.date,infant[i].vaccination[0].dateOfVaccination.month,infant[i].vaccination[0].dateOfVaccination.year);
    printf("\n\t\t%s - %d/%d/%d (dd/mm/yy)",infant[i].vaccination[1].nameOfVaccination,infant[i].vaccination[1].dateOfVaccination.date,infant[i].vaccination[1].dateOfVaccination.month,infant[i].vaccination[1].dateOfVaccination.year);
 }
    
}


//DELETE
void deleteRecord(void){
 int j = 0,k=0,newSize,ID;
 bool isUserExists = false;
 FILE *fptr;
 fptr = fopen("inf.dat", "rb");
 struct infants infant[15];
 while(fread(&infant[j], sizeof(struct infants), 1, fptr) == 1) {
    j++;
  }
 printf("\nEnter ID of the infant to delete : ");scanf("%d",&ID);
 
 for( k; k < j ;k++){
  if(infant[k].id == ID){
    isUserExists = true;
    break;
  }
 }

 if(isUserExists){
  fptr = fopen("inf.dat", "wb");
  newSize = deleteItemFromArray(infant,j,k);
    if(newSize > 0){
      for(int i = 0; i < newSize; i++){
        fwrite(&infant[i], sizeof(struct infants), 1, fptr);
      }
    } 
 }else{
  printf("\nWrong ID.Enter a valid one.");
  }
 fclose(fptr);
}

//UPDATE
void updateRecord(void){
 int j = 0, k = 0, ID;
 bool isUserExists = false;
 FILE *fptr;
 fptr = fopen("inf.dat", "rb");
 struct infants infant[15];
 while(fread(&infant[j], sizeof(struct infants), 1, fptr) == 1) {
    j++;
  }
 printf("\nEnter ID of the infant to update : ");scanf("%d",&ID);

 for( k; k < j ;k++){
  if(infant[k].id == ID){
    isUserExists = true;
    break;
  }
 }
 if(isUserExists){
  fptr = fopen("inf.dat", "wb");
  printf("\nNew Name : ");scanf("%s",&infant[k].name); 
  printf("\nNew ID : ");scanf("%d",&infant[k].id);
  for(int i = 0; i < j; i++){
        fwrite(&infant[i], sizeof(struct infants), 1, fptr);
      }
  printf("\nSuccessfully updated Infant record.");
 }else{
  printf("\nWrong ID.Enter a valid one.");
  }
 fclose(fptr);
 return;
}

//Compare 2 names 
int compareNames(const void *a, const void *b){
  return strcmp(((struct infants*)a)->name, ((struct infants*)b)->name);
}


//Compare 2 birthdays
bool compareBirthday(struct dates d1, struct dates d2)
{
    if (d1.year < d2.year)
       return false;

    else if (d1.year > d2.year)
       return true;

    if (d1.year == d2.year)
    {
         if (d1.month<d2.month)
              return false;
         else if (d1.month>d2.month)
              return true;
         else if (d1.date<d2.date)
              return false;
         else if(d1.date>d2.date)
              return true;
         else
              return false;
    }
}

//Remove a object from infants array
int deleteItemFromArray(struct infants *array, int size, int index) {
    for (int i = index; i < size ; i++) {
        array[i] = array[i + 1];
    }

    size--;
    return size;
}