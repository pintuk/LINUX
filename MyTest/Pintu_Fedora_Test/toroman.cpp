#include <iostream>
 #include <iomanip>
 #include <string>
 
 
 using namespace std;  //introduces namespace std
 
 void ShowList();
 int ToIntegers(string);
 int DoOperation(int, int, string);
 string ToNumerals(int);
 
 
 int main()
 {
 	string RomanNumeral1="";
 	string RomanNumeral2="";
 	string Operation="";
 	string FinalNumeral="";
 
 	int Integer1 = 0;
 	int Integer2 = 0;
 	int FinalInteger = 0;
 
 
 	ShowList();
 
 	cout << endl << "Enter One Roman Numeral Value: ";
 	cin  >> RomanNumeral1;
 
 	cout << "Enter Another Roman Numeral Value: ";
 	cin  >> RomanNumeral2;
 
 	cout << "Enter Operation: ";
 	cin  >> Operation;
 
 
 	Integer1 = ToIntegers(RomanNumeral1);
 	Integer2 = ToIntegers(RomanNumeral2);

 	FinalInteger = DoOperation(Integer1, Integer2, Operation);
 
 	FinalNumeral = ToNumerals(FinalInteger);
 
 	cout << endl << endl << "Operation: Roman Numeral 1 (" << Integer1 << ") " << Operation << " Roman Numeral 2 (" << Integer2 << ")";
 	cout << endl << "Answer: " << FinalNumeral;
 
 	return 0;
 }
 
 void ShowList()
 {
 
 	cout << "I";
 		cout << fixed << setw(10) << "1";
 	cout << endl << "V";
 		cout << setw(10) << "5";
 	cout << endl << "X";
 		cout << setw(10) << "10";
 	cout << endl << "L";
 		cout << setw(10) << "50";
 	cout << endl << "C";
 		cout << setw(10) << "100";
 	cout << endl << "D";
 		cout << setw(10) << "500";
 	cout << endl << "M";
 		cout << setw(10) << "1000";
 
 
 }
 
 int ToIntegers(string RN)
 {
 //	string 	numString=0;
        string  numString="";
 	int burp = RN.length();
 	int	numInt=0;
 
 	for(int i = 0; i < burp; i++)
 	{
 		numString = RN.substr(i, 1);
 		if(numString == "M")
 			numInt +=1000;
 		else if(numString == "D")
 			numInt +=500;
 		else if(numString == "C")
 			numInt +=100;
 		else if(numString == "L")
 			numInt +=50;
 		else if(numString == "X")
 			numInt +=10;
 		else if(numString == "V")
 			numInt +=5;
 		else //(numString == "I")
 			numInt +=1;
 
 
 	}
 
 return numInt;
 }
 
 int DoOperation(int int1, int int2, string oper)
 {
 	int IntegerFinal;
 
 	if(oper == "+")
 		IntegerFinal = int1 + int2;
 	else if(oper == "-")
 		IntegerFinal = int1 - int2;
 	else if(oper == "*")
 		IntegerFinal = int1 * int2;
 	else if(oper == "/")
 		IntegerFinal = int1 / int2;
 
 	else cout << "INVALID OPERATOR!";
 return IntegerFinal;
 }
 
 string ToNumerals(int FI)
 {
 	string NumeralFinal="";
 
 	while( FI >= 1000)
 	{
 		NumeralFinal += "M";
 		FI -= 1000;
 	}
 	while(FI >= 500)
 	{
 		NumeralFinal +="D";
 		FI -= 500;
 	}
 
 	while( FI >= 100)
 	{
 		NumeralFinal += "C";
 		FI -= 100;
 	}
 	while( FI >= 50)
 	{
 		NumeralFinal += "L";
 		FI -= 50;
 	}
 	while( FI >= 10)
 	{
 		NumeralFinal += "X";
 		FI -= 10;
 	}
 	while( FI >= 5)
 	{
 		NumeralFinal += "V";
 		FI -= 5;
 	}
 	while( FI >= 1)
 	{
 		NumeralFinal += "I";
 		FI -= 1;
 	}
 
 return NumeralFinal;
 }
 

See RED ... It crashed for me untill I changed that one line.

 
