#include <iostream>
#include <cmath> 
#include <iomanip>
#include <fstream>
using namespace std; 

static string FormatNumberForOutput(double number)
{
  string strnum;
  char decimal = '.', comma = ',';
  //char is a data type designed to store letters

  strnum = to_string(number);
  //formats the double number to a string and it can be used to (.find) and (.insert)

  if (strnum.find(decimal) > 3)
    //format.find(decimal) is used to find the decimal in the       string(number)
  {
       strnum.insert(strnum.find(decimal) - 3, 1, comma);
    // Will add decimal to double number. So I took out << fixed << setpercision(2) from my code because this already does that. 
      //Will insert a comma in the first position
  }
  if (strnum.find(decimal) > 7)
     //format.find(decimal) is used to find the decimal in the       string(number)
      { 
          while (strnum.find(comma) > 3)
          //Uses a while function, where if there are no commas in more than every 3 letters it will insert a comma
         {
             strnum.insert(strnum.find(comma) - 3, 1, comma);
            //inserts the commas in the first position of as it loops, so every three numbers
         }
      }
  return strnum.substr(0, strnum.find(decimal) + 3.2);
  //returns a new string with the decimal and comma formatting
}

int main()
{
	double a;
	double b;
	double b2;
	double c;
	double d;
	string filename;
  
while (true) {
		cout << "Enter Loan amount(0-9999999), for example 300000.90: \n";
		cin >> a;
		if ((0 < a) && (a <= 9999999))
		{
			cout << FormatNumberForOutput(a) << "\n";
			break;
		}
		else
		{
			cout << a << " is not a number between 0 and 9999999 \n";
		}
	}


	while (true) {
		cout << "Enter annual interest rate(0-30), for example 4.25 meaning 4.25%: \n";
		cin >> b;
		if ((0 < b) && (b <= 30))
		{
			b2 = b / 100;
			cout << "Your interest rate is " << b2 << "% \n";
			break;
		}
		else
		{
			cout << b << " is not a number between 0 and 30 \n";
		}
	}

  
	while (true)
	{
		cout << "Enter no. of years as integer(1-99), for example 30: 25 \n";
		cin >> c;
		if ((1 <= c) && (c <= 99))
		{
			cout <<  c << " Years \n";
			break;
		}
		else
		{
			cout << c << " is not a number between 1 and 99 \n";
		}
	}

  
	while (true) {
		cout << "Enter additional principle per month(0-9999999), for example 300: \n";
		cin >> d;
		if ((0 <= d) && (d <= 9999999))
		{
			cout << "Your added principle is $" << d << "\n";
			break;
		}
		else
		{
			cout << d << " is not a number between 0 and 9999999 \n";
		}
	}
  
	cout << "Send the mortgage amortization table to a file (enter file name): \n";
	cin >> filename;
	ofstream myFile;
	myFile.open(filename);

  //Strict Calculations
 double MonthlyPayment = (a * (b2/12)) / (1 - 1/pow(1 + (b2/12), c*12));
 double TotalPayment = MonthlyPayment * c * 12;
 double ActualPayment = MonthlyPayment + d;
 double PIR = b / 100 / 12;
 double InterestPayment = a * PIR;
 double PrinciplePayment = ActualPayment - InterestPayment;
 double RemainingBalance = a - PrinciplePayment;

  //Rounding up MonthlyPayment and Actual Payment up because c++ rounds down
  double MonthlyPayment2 = ceil(MonthlyPayment * 100.0) / 100.0;
  double ActualPayment2 = ceil(ActualPayment * 100.0) / 100.0;
  
  //Top Half before Principle/Interest/Balance
	myFile << "\t" << "MORTAGE AMORTIZATION TABLE \n";
	myFile << "\n";
	myFile << setw(25) << left << "Amount:" ;
  myFile << setw(2) << left << "$";
  myFile << setw(10) << right << FormatNumberForOutput(a) << "\n";
  
	myFile << setw(25) << left << "Interest Rate:";
  myFile << setw(2) << left << b << "%\n";
  
	myFile << setw(25) << left << "Term(Years):";
  myFile << setw(2) << left << c << "\n";
  
  myFile << setw(25) << left << "Monthly Payment:";
  myFile << setw(2) << left << "$";
  myFile << setw(10) << right  << FormatNumberForOutput(MonthlyPayment2) << "\n";
  
	myFile << setw(25) << left << "Additional Principle:";
  myFile << setw(2) << left << "$";
  myFile << setw(10) << right << FormatNumberForOutput(d) << "\n";
  
	myFile << setw(25) << left << "Actual Payment:"; 
  myFile << setw(2) << left << "$";
  myFile << setw(10) << right << fixed << FormatNumberForOutput(ActualPayment2) << "\n";
	myFile << "\n";
	int period = 1;
  
  //Heading before code
	myFile << right << setw(15) << "Principle";
  myFile << left << " ";
  myFile << right << setw(11) << "Interest"; 
  myFile << left << " ";
  myFile << right << setw(13) << "Balance";
  myFile << "\n";
  
while (period == 1) {
   myFile << setw(3) << left << period;
      myFile << setw(2) << left << " $";
      
      myFile << setw(10) << right << (FormatNumberForOutput(ActualPayment - InterestPayment));
      myFile << setw(2) << left << " $";
      
      myFile << setw(10) << right << FormatNumberForOutput(a * PIR);
      myFile << setw(2) << left << " $";
      
      myFile << setw(13) << right << FormatNumberForOutput(a-PrinciplePayment) << "\n";
		
    a = a - PrinciplePayment;
		InterestPayment = a * PIR;
		PrinciplePayment = ActualPayment - InterestPayment;
		period++;
	}
  
  while(a > 0) {
      double total = a-PrinciplePayment;
      
  		  myFile << setw(3) << left << period;
        myFile << setw(2) << left << " ";

       if (total <= 0) {
          PrinciplePayment = a;
        myFile << setw(10) << right << FormatNumberForOutput(PrinciplePayment);
          }
        else
        myFile << setw(10) << right << (FormatNumberForOutput(PrinciplePayment));
        myFile << setw(2) << left << " ";
      
        myFile << setw(10) << right << FormatNumberForOutput(a * PIR);
        myFile << setw(2) << left << " ";

        if(total < 0) { 
          myFile << setw(13) << right << FormatNumberForOutput(0) << "\n";
        }
        else {
          myFile << setw(13) << right << FormatNumberForOutput(a-PrinciplePayment) << "\n";
        }
      
      a = a - PrinciplePayment;
  		InterestPayment = a * PIR;
  		PrinciplePayment = ActualPayment - InterestPayment;
  		period++;
  	}
    myFile.close();
  }
