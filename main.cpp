//Lee Reyes Lab 8A due 12/7/2021
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;
////struct declaration/////
struct householdType
{
  string IDNum;
  float annualIncome;
  int householdSize;
};
///constant////
const int LIMIT = 100;

//// prototypes ////
void GetData (ifstream &infile, householdType householdData[ ], int & size);
void ShowData(ofstream & outfile, householdType householdData[ ], int size);
void Average(ofstream & outfile, householdType householdData[], int size, string wealthyID [], float wealthyHomes[]);
void Poverty (ofstream & outfile, householdType householdData[], int size, string lowIncomeID[], float homesBelowPovertyLine[]);
void Sorted (householdType householdData[], householdType sortedHouseholdData[], int size);
void median (ofstream &outfile, householdType householdData[], int size);
void Menu(char & choice);


//// main function begins////
int main() 
{
  ifstream infile;
  ofstream outfile;
  infile.open("DataIn.txt"); 
  outfile.open("DataOut.txt");
  householdType householdData[LIMIT];
  householdType sortedHouseholdData[LIMIT];
  int size;
  string wealthyID[LIMIT];
  string lowIncomeID[LIMIT];
  float wealthyHomes[LIMIT];
  float homesBelowPovertyLine[LIMIT];
  bool keepLearning = true;
  char choice; 


  //error checking for input file///
  if (!infile)
  {
    cout << "Could not open file PayIn.txt. Terminating program." << endl;
    exit(1);
  }
  //error checking for output file///
  if (!outfile)
  {
    cout << "Could not open file PayOut.txt. Terminating program." << endl;
    exit(1);
  }

  GetData(infile, householdData, size);

  do
  {
    Menu(choice);
    switch(choice)
    {
      case 'a':
      case 'A':
        ShowData(outfile, householdData, size);
        break;
      case 'b':
      case 'B':
        Average(outfile, householdData,size, wealthyID, wealthyHomes);
        break;
      case 'c':
      case 'C':
        Poverty(outfile, householdData, size, lowIncomeID, homesBelowPovertyLine);
        break;
      case 'd':
      case 'D':
        outfile << "Household Data Sorted by Income Level in Ascending Order" << endl;
        Sorted(householdData, sortedHouseholdData, size);
        ShowData(outfile, sortedHouseholdData, size);
        break;
      case 'e':
      case 'E':
        Sorted(householdData, sortedHouseholdData, size);
        median(outfile, sortedHouseholdData, size);
        break;
      case 'f':
      case 'F':
        keepLearning = false;
        cout << "Program terminating" << endl;
        break;
      default:
        cout << "Invalid entry. Please try again. If you would like to exit the program please enter 'f'. The other options are presented below." << endl << endl;
        break;
    }
  } while(keepLearning);

  infile.close();
  outfile.close();
  return 0; 
}
////// GetData Function Begins -- Function Checked and Functional //////
void GetData (ifstream &infile, householdType householdData[], int & size)
{
  int count = 0;
  while(count < LIMIT && !infile.eof())
  {
    infile >> householdData[count].IDNum >> householdData[count].annualIncome >> householdData[count].householdSize; 
    count ++;
  }
  size = count;
}

////// ShowData Function Begins -- Function Checked and Functional //////
void ShowData(ofstream & outfile, householdType householdData[], int size)
{
  outfile << "Household ID Number " << " Household Annual Income " << " Household Size" << endl;
  outfile << fixed << showpoint<< setprecision(2);
  for (int i =0; i < size; i++)
  {
    outfile<< householdData[i].IDNum << setw(30) << right << householdData[i].annualIncome << setw(20)  << householdData[i].householdSize << endl;
  }
  outfile <<"___________________________________________________________" << endl << endl;
}
////// Average Function Begins -- Function Checked and Functional  //////
void Average(ofstream & outfile, householdType householdData[], int size, string wealthyID [], float wealthyHomes[])
{
  int i;
  int sizeofWealthyHomes = 0;
  float sum, average;
  for (i = 0;  i < size; i++)
  {
    sum += householdData[i].annualIncome;
  }
  average = sum/size;

  for (i = 0; i < size; i++)
  {
    if (householdData[i].annualIncome > average)
    {
      wealthyID[sizeofWealthyHomes] = householdData[i].IDNum;
      wealthyHomes[sizeofWealthyHomes] = householdData[i].annualIncome;
      sizeofWealthyHomes++;
    }
  }

outfile << "Average annual income for households in Woodland Hills: $" << fixed << showpoint<< setprecision(2) << average << endl;
outfile<< "The households below earn over the average household annual income." << endl;
outfile <<"___________________________________________________________" << endl;
outfile<<  "Household ID Number " << " Household Annual Income " << endl;
  for (i = 0; i < sizeofWealthyHomes; i++)
  {
    outfile << wealthyID[i] << setw(30) << right << wealthyHomes[i] << endl;
  }
outfile << endl <<"___________________________________________________________" << endl << endl << endl;

}

////// Poverty Function Begins -- Function Checked and Functional  //////
void Poverty (ofstream & outfile, householdType householdData[], int size, string lowIncomeID[], float homesBelowPovertyLine[] )
{
  int sizeofLowIncomeHomes = 0;
  int i;
  float povertyLevel, percentage;
  for (i = 0; i < size; i++)
  {
    povertyLevel = 8000 + 500 * (householdData[i].householdSize -2);
    if (householdData[i].annualIncome < povertyLevel)
    {
      lowIncomeID[sizeofLowIncomeHomes] = householdData[i].IDNum;
      homesBelowPovertyLine[sizeofLowIncomeHomes] = householdData[i].annualIncome;
      sizeofLowIncomeHomes++;
    }
  }
  percentage = float(sizeofLowIncomeHomes)/size * 100;


  outfile << "Percentage of homes who earn below the poverty line in Woodland Hills: " << fixed << setprecision(2) << percentage << "%" << endl << endl;
  outfile<< "The households below earn below the average household annual income." << endl;
  outfile <<"___________________________________________________________" << endl;
  outfile<<  "Household ID Number " << " Household Annual Income " << endl;
  for (i = 0; i < sizeofLowIncomeHomes; i++)
  {
    outfile << lowIncomeID[i] << setw(30) << right << homesBelowPovertyLine[i] << endl;
  }
  outfile << endl <<"___________________________________________________________" << endl << endl;

}
////// Sorting Function Begins -- Function Checked and Functional //////
void Sorted (householdType householdData[], householdType sortedHouseholdData[], int size)
{

   for (int i =0; i < size; i++)
  {
    sortedHouseholdData[i].annualIncome = householdData[i].annualIncome;
    sortedHouseholdData[i].IDNum = householdData[i].IDNum;
    sortedHouseholdData[i].householdSize = householdData[i].householdSize;
  }

  int Swap, tempAnnualIncome, tempHouseholdSize, Count;
  string tempID;
  do
  {
    Swap = 0;
    for (Count = 0; Count < (size-1); Count++)
    {
      if(sortedHouseholdData[Count].annualIncome > sortedHouseholdData[Count +1].annualIncome)
      {
        tempAnnualIncome = sortedHouseholdData[Count].annualIncome;
        tempHouseholdSize = sortedHouseholdData[Count].householdSize;
        tempID = sortedHouseholdData[Count].IDNum;
        sortedHouseholdData[Count].annualIncome = sortedHouseholdData[Count + 1].annualIncome;
        sortedHouseholdData[Count].householdSize =  sortedHouseholdData[Count +1].householdSize;
        sortedHouseholdData[Count].IDNum = sortedHouseholdData[Count+ 1].IDNum;
        sortedHouseholdData[Count + 1].annualIncome = tempAnnualIncome;
        sortedHouseholdData[Count +1].householdSize = tempHouseholdSize;
        sortedHouseholdData[Count+ 1].IDNum = tempID;
        Swap = 1;
      }
    }
    size--;
  }
  while(Swap != 0);


}

////// Median Function Begins -- Functional and Checked //////
void median (ofstream &outfile, householdType householdData[], int size)
{
  float median = 0.0;
  if (size % 2 == 0)
  {
    median = (householdData[size/2].annualIncome + householdData[size/2-1].annualIncome)/2.0;
  }
  else
  {
    median = householdData[size/2].annualIncome;
  }
outfile << fixed << showpoint<< setprecision(2);
outfile << "The households median is: " << median;
outfile << endl <<"___________________________________________________________" << endl << endl << endl;
}
////// Menu Function Begins --  Functional and Checked  //////

void Menu (char & choice)
{
  cout << "The results from the Woodland Hills household survey are now available. Please choose how you would like the data presented." << endl;
  cout << "___________________________________________________________" << endl;
  cout << "A. Show all data" << endl;
  cout << "B. Show Households with income above annual average" << endl; 
  cout << "C. Show Households below the poverty line" << endl;
  cout << "D. Show households sorted from lowest to heighest annual income" << endl;
  cout << "E. Show median income" << endl;
  cout << "F. Exit program" << endl;
  cin >> choice;
}

