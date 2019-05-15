//  Loan Payment Plan Creator
//
//  Created on 26.04.19 by
//Sabitre Paspuel
//Shaun Li, Bindushree Devaraj, Thomas Decker .
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <regex>
#include <fstream>
#include <ctime>
#include <sstream>
#include <limits>
#include <iomanip>
#include <chrono>

using namespace std;

typedef chrono::system_clock Clock;

double BoxMueller(double mean, double variance)
{

    double x, y, s, z;

    do
    {
        x = ((double) rand() * 2 / RAND_MAX) - 1;
        y = ((double) rand() * 2 / RAND_MAX) - 1;
        s = x * x + y * y;
    } while (s > 1);

    z = x * sqrt(-2 * log(s) / s);
    return  mean + sqrt(variance) * z;

}

enum paymentFrequencyType {annualy = 1, semiannualy = 2, quaterly = 4, monthly = 12};

void IncrementPeriod(paymentFrequencyType paymentFrequency, int* month, int* year)
{
    switch (paymentFrequency)
    {
        case annualy:
            (*year)++;
            break;
        case semiannualy:
            *month += 6;
            if(*month > 12){
                (*year)++;
                *month %= 12;
            }
            break;
        case quaterly:
            *month += 3;
            if(*month > 12){
                (*year)++;
                *month %= 12;
            }
            break;
        case monthly:
            (*month)++;
            if(*month > 12){
                (*year)++;
                *month = 1;
            }
            break;

    }

}

void PrintHeader(ofstream& file, char listSeparator)
{
    file << setprecision(2) << fixed;
    file << "period#"<< listSeparator <<"period"<< listSeparator <<"opening balance"<< listSeparator <<"principal"<< listSeparator <<"annual interest rate"<< listSeparator <<"periodic interest rate"<< listSeparator <<"interest"<< listSeparator <<"installment"<< listSeparator <<"closing balance\n";
}

void FloatingRateCalculation(double loanAmount, paymentFrequencyType paymentFrequency, int startingMonth, int startingYear, double principal, double margin, double mean, double variance)
{
    ofstream csvFile;
    csvFile.open ("LoanRepaymentPlan.csv");
    char listSeparator=',';
    csvFile << setprecision(2) << fixed;
    csvFile << "period#"<< listSeparator <<"period"<< listSeparator <<"opening balance"<< listSeparator <<"principal"<< listSeparator <<"floating rate"<< listSeparator <<"periodic interest rate"<< listSeparator <<"interests"<< listSeparator <<"installment"<< listSeparator <<"closing balance\n";


    int numberPeriods = ceil(loanAmount/principal);
    int periodMonth = startingMonth;
    int periodYear= startingYear;

    for(int i=1; i<=numberPeriods; ++i)
    {
        double floatingRate;
        do
        {
            floatingRate = BoxMueller(mean, variance);
        }while(margin+floatingRate<0);
        double periodicInterestRate = (margin + floatingRate)/paymentFrequency;
        double interests=loanAmount*periodicInterestRate/100;

        csvFile << i << listSeparator << periodMonth << "/" << periodYear << listSeparator <<loanAmount<< listSeparator <<min(principal,loanAmount)<< listSeparator << floatingRate<< "%" << listSeparator << periodicInterestRate << "%" << listSeparator <<interests<< listSeparator << min(principal+interests,loanAmount+interests)<< listSeparator <<loanAmount - min(principal,loanAmount)<<"\n";
        loanAmount = loanAmount - min(principal,loanAmount);
        IncrementPeriod(paymentFrequency, &periodMonth, &periodYear);
    }
    csvFile.close();
    cout << "Loan Payment Plan has been successfully created and saved in your directory!" << endl;
}

void FixedPrincipalFixedRateCalculation(double loanAmount, paymentFrequencyType paymentFrequency, int startingMonth, int startingYear, double principal, double interestRate){

    ofstream csvFile;
    csvFile.open ("LoanRepaymentPlan.csv");
    char listSeparator=',';
    PrintHeader(csvFile, listSeparator);
    unsigned int numberPeriods = ceil(loanAmount/principal);
    double periodicRate = interestRate / paymentFrequency;
    int periodMonth = startingMonth;
    int periodYear= startingYear;

    for(int i=1; i <= numberPeriods; ++i)
    {
        double interests=loanAmount*periodicRate/100;
        //PrintNewLine(csvFile, ',', i, periodMonth, periodYear, openBalance, principal, interestRate, periodicRate,  interests,  closingBalance);
        csvFile << i << listSeparator << periodMonth << "/" << periodYear << listSeparator <<loanAmount<< listSeparator <<min(principal,loanAmount)<< listSeparator <<interestRate<< "%" << listSeparator << periodicRate << "%" << listSeparator <<interests<< listSeparator << min(principal+interests,loanAmount+interests)<< listSeparator <<loanAmount - min(principal,loanAmount)<<"\n";
        loanAmount = loanAmount- min(principal,loanAmount);
        IncrementPeriod(paymentFrequency, &periodMonth, &periodYear);
    }
    csvFile.close();
    cout << "Loan Payment Plan has been successfully created and saved in your directory!" << endl;
}

void FixedInstallmentCalculateInstallment(double loanAmount, double interestRate, paymentFrequencyType frequency, double startingMonth, double startingYear, double numberPeriods)
{

    interestRate=interestRate/100/frequency;

    double installment = 1/(pow(1+interestRate,numberPeriods)-1);
    installment = loanAmount*interestRate*(1+installment);

    cout << setprecision(2) << fixed;
    cout<<"The installment is "<< installment <<endl;


    char listSeparator=',';
    ofstream csvFile;
    csvFile.open ("LoanRepaymentPlan.csv");
    PrintHeader(csvFile, listSeparator);

    int periodMonth = startingMonth;
    int periodYear = startingYear;
    for(int i=1; i<=numberPeriods; ++i)
    {
        csvFile <<i<< listSeparator <<periodMonth << "/" << periodYear<< listSeparator<<loanAmount<< listSeparator<<installment-loanAmount*interestRate<< listSeparator<<interestRate*frequency*100<<" %"<<listSeparator<<interestRate*100<<" %"<< listSeparator<<loanAmount*interestRate<< listSeparator<<installment<< listSeparator <<loanAmount-(installment-loanAmount*interestRate)<<"\n";
        loanAmount=loanAmount-(installment-loanAmount*interestRate);
        IncrementPeriod(frequency, &periodMonth, &periodYear);
    }
    csvFile.close();
    cout << "Loan Payment Plan has been successfully created and saved in your directory!" << endl;

}
void FixedInstallmentCalculateLoanAmount(double interestRate, double installment, paymentFrequencyType frequency, double startingMonth, double startingYear, double numberPeriods)
{
    interestRate=interestRate/100/frequency;

    double loanAmount = 1/(pow(1+interestRate,numberPeriods)-1);
    loanAmount = installment/(interestRate*(1+loanAmount));

    cout << setprecision(2) << fixed;
    cout<<"The Loan Amount is "<<loanAmount<<endl;


    char listSeparator=',';
    ofstream csvFile;
    csvFile.open ("LoanRepaymentPlan.csv");
    PrintHeader(csvFile, listSeparator);

    int periodMonth = startingMonth;
    int periodYear = startingYear;
    for(int i=1; i<=numberPeriods; ++i)
    {
        csvFile<<i<< listSeparator <<periodMonth << "/" << periodYear<< listSeparator<<loanAmount<< listSeparator<<installment-loanAmount*interestRate<< listSeparator<<interestRate*frequency*100<<" %"<<listSeparator<<interestRate*100<<" %"<< listSeparator<<loanAmount*interestRate<< listSeparator<<installment<< listSeparator <<loanAmount-(installment-loanAmount*interestRate)<<"\n";
        loanAmount=loanAmount-(installment-loanAmount*interestRate);
        IncrementPeriod(frequency, &periodMonth, &periodYear);
    }
    csvFile.close();
    cout << "Loan Payment Plan has been successfully created and saved in your directory!" << endl;

}
void FixedInstallmentCalculatePeriod(double loanAmount, double interestRate, double installment, paymentFrequencyType frequency,double startingMonth, double startingYear)

{
    interestRate=interestRate/100/frequency;

    double numberPeriods= 1/(installment/(interestRate*loanAmount)-1);
    numberPeriods=log(numberPeriods+1);
    numberPeriods=ceil(numberPeriods/log(1+interestRate));

    cout<<"The number of periods is "<<numberPeriods<<endl;


    char listSeparator=',';
    ofstream csvFile;
    csvFile.open ("LoanRepaymentPlan.csv");
    PrintHeader(csvFile, listSeparator);

    int periodMonth = startingMonth;
    int periodYear = startingYear;

    for(int i=1; i<=numberPeriods; ++i)
    {
        csvFile <<i<< listSeparator <<periodMonth << "/" << periodYear<< listSeparator<<loanAmount<< listSeparator<<min(loanAmount,installment-loanAmount*interestRate)<< listSeparator<<interestRate*frequency*100<<" %"<<listSeparator<<interestRate*100<<" %"<< listSeparator<<loanAmount*interestRate<< listSeparator<<min(loanAmount+loanAmount*interestRate,installment)<< listSeparator <<loanAmount-(min(loanAmount,installment-loanAmount*interestRate))<<"\n";
        loanAmount=loanAmount-(installment-loanAmount*interestRate);
        IncrementPeriod(frequency, &periodMonth, &periodYear);
    }
    csvFile.close();
    cout << "Loan Payment Plan has been successfully created and saved in your directory!" << endl;

}
double OptimisationFunction(double installment, double loanAmount,double numberPeriods, double r)
{
    double temp;
    temp = 1/(pow(1+r,numberPeriods)-1);
    temp = r*(1+temp);
    temp = temp-installment/loanAmount;
    return temp;

}
double CalculateInterestRate(double installment, double loanAmount,double numberPeriods, double r=0.5)
{
    double rNext,temp;
    rNext = 0.95*r;
    while (abs(OptimisationFunction(installment,loanAmount,numberPeriods,rNext))>0.0000000001)
    {
        temp = rNext;
        rNext = rNext-(OptimisationFunction(installment,loanAmount,numberPeriods,rNext)*(rNext - r))/(OptimisationFunction(installment,loanAmount,numberPeriods,rNext)-OptimisationFunction(installment,loanAmount,numberPeriods,r));
        r =temp;
    }

    cout<< setprecision(2) << fixed;
    cout<<"The periodic interest rate is "<<rNext*100<<"%"<<endl;

    return rNext;
}

void FixedInstallmentCalculateInterest(double loanAmount, double installment, paymentFrequencyType frequency, double numberPeriods, double startingMonth, double startingYear)

{
    double interestRate= CalculateInterestRate(installment, loanAmount, numberPeriods);
    cout<<"The annual interest rate is "<<interestRate*frequency*100<<"%"<<endl;

    char listSeparator=',';
    ofstream csvFile;
    csvFile.open ("LoanRepaymentPlan.csv");
    PrintHeader(csvFile, listSeparator);

    int periodMonth = startingMonth;
    int periodYear = startingYear;

    for(int i=1;i<=numberPeriods;++i)
    {
        csvFile <<i<< listSeparator <<periodMonth << "/" << periodYear<< listSeparator<<loanAmount<< listSeparator<<installment-loanAmount*interestRate<< listSeparator<<interestRate*frequency*100<<" %"<<listSeparator<<interestRate*100<<" %"<< listSeparator<<loanAmount*interestRate<< listSeparator<<installment<< listSeparator <<loanAmount-(installment-loanAmount*interestRate)<<"\n";
        loanAmount=loanAmount-(installment-loanAmount*interestRate);
        IncrementPeriod(frequency, &periodMonth, &periodYear);
    }
    csvFile.close();
    cout << "Loan Payment Plan has been successfully created and saved in your directory!" << endl;

}

//Input Validation Functions
regex dateRegex("[0-9]{4}/(0[1-9]|1[012])");
regex doubleRegex("-?[0-9]+(\.[0-9]+)?");
regex positiveIntRegex("[0-9]+");
regex positiveDoubleRegex("[0-9]+(\.[0-9]+)?");
regex optionRegexOneToFour("[1234]");
regex optionRegexOneToTwo("[12]");

string validateInputWithRegex(regex regex)
{
    bool invalidOption;
    string inputString;
    do
    {
        getline(cin,inputString);
        invalidOption= !regex_match(inputString, regex);
        if(invalidOption) cout<< "Please enter a valid input value"<<endl;
    }while(invalidOption);
    return inputString;
}

int main()
{
    auto now = Clock::now();
    time_t now_time = Clock::to_time_t(now);
    struct tm *parts = localtime(&now_time);

    string startingDate;
    int startingYear;
    int startingMonth;
    bool dateInPast=true;

    cout<<"Welcome to the Loan Repayment Plan Creator"<< endl;
    cout<<"Please choose a starting date in the format YYYY/MM:"<< endl;
    do
    {   getline(cin, startingDate);
        if(!regex_match(startingDate, dateRegex)){
            cout << "Invalid date, please enter a valid date in the format YYYY/MM"<<endl;
        } else
        {
            startingYear = stoi(startingDate.substr(0,4));
            startingMonth = stoi(startingDate.substr(startingDate.length()-2, 2));
            dateInPast = (startingYear < 1900 + parts->tm_year) || (startingYear == 1900 + parts->tm_year && startingMonth < 1+parts->tm_mon);
            if(dateInPast) cout<< "Your entered date is in the past, please enter a future starting date YYYY/MM!"<<endl;
        }

    }while (!regex_match(startingDate, dateRegex)|| dateInPast );

    paymentFrequencyType frequencyPayment;
    cout << "Please choose your frequency of payments:" << endl
         << "1 Annually" << endl
         << "2 Semiannually" << endl
         << "3 Quarterly" << endl
         << "4 Monthly" << endl;

    switch (stoi(validateInputWithRegex(optionRegexOneToFour)))
    {
        case 1:
            frequencyPayment=annualy;
            break;
        case 2:
            frequencyPayment=semiannualy;
            break;
        case 3:
            frequencyPayment=quaterly;
            break;
        case 4:
            frequencyPayment=monthly;
            break;
        default:
            break;
    }

    int loanType;

    cout << "Please choose an option: \n1 Fixed Principal \n2 Fixed Installment" << endl;

    loanType=stoi(validateInputWithRegex(optionRegexOneToTwo));

    int numberPeriods;
    double loanAmount,principal, marginRate, interestRate, installment, mean, variance;

    if(loanType == 1)
    {
        cout << "Please enter the amount of the loan" << endl;
        loanAmount=stod(validateInputWithRegex(positiveDoubleRegex));

        cout << "Please choose an option:" << endl
             << "1 Floating Rate" << endl
             << "2 Fixed Rate" << endl;

        loanType=stoi(validateInputWithRegex(optionRegexOneToTwo));

        if (loanType==1)
        {
            cout << "Please enter the principal amount:" << endl;
            principal=stod(validateInputWithRegex(positiveDoubleRegex));
            cout << "Please enter the annual margin rate in percentage:" << endl;
            marginRate=stod(validateInputWithRegex(positiveDoubleRegex));
            cout << "Please enter the mean of the random floating rate component in percentage:" << endl;
            mean=stod(validateInputWithRegex(doubleRegex));
            cout << "Please enter the variance of the random floating rate component in percentage:" << endl;
            variance=stod(validateInputWithRegex(positiveDoubleRegex));
            srand((unsigned) time (0));
            FloatingRateCalculation(loanAmount, frequencyPayment, startingMonth, startingYear, principal, marginRate, mean, variance);

        } else {
            cout << "Please enter the principal amount:" << endl;
            principal=stod(validateInputWithRegex(positiveDoubleRegex));
            cout << "Please enter the annual interest rate in percentage:" << endl;
            interestRate=stod(validateInputWithRegex(positiveDoubleRegex));
            FixedPrincipalFixedRateCalculation(loanAmount, frequencyPayment, startingMonth, startingYear, principal, interestRate);
        }

    } else
    {

        cout << "Please choose an option according to the information that you have available:" << endl
             << "1 Number of payment periods, loan amount, interest rate" << endl
             << "2 Number of payment periods, installment, interest rate" << endl
             << "3 installment, loan amount, interest rate" << endl
             << "4 Number of payment periods, loan amount, installment" << endl;

        loanType=stoi(validateInputWithRegex(optionRegexOneToFour));

        switch (loanType)
        {
            case 1:
                cout << "Please enter the loan amount:" << endl;
                loanAmount=stod(validateInputWithRegex(positiveDoubleRegex));
                cout << "Please enter the annual interest rate in percentage:" << endl;
                interestRate=stod(validateInputWithRegex(positiveDoubleRegex));
                cout << "Please enter the number of periods:" << endl;
                numberPeriods=stoi(validateInputWithRegex(positiveIntRegex));
                FixedInstallmentCalculateInstallment(loanAmount, interestRate, frequencyPayment,startingMonth, startingYear, numberPeriods);
                break;
            case 2:
                cout << "Please enter the installment:" << endl;
                installment=stod(validateInputWithRegex(positiveDoubleRegex));
                cout << "Please enter the annual interest rate in percentage:" << endl;
                interestRate=stod(validateInputWithRegex(positiveDoubleRegex));
                cout << "Please enter the number of periods:" << endl;
                numberPeriods=stoi(validateInputWithRegex(positiveIntRegex));
                FixedInstallmentCalculateLoanAmount(interestRate, installment, frequencyPayment, startingMonth, startingYear, numberPeriods);
                break;
            case 3:
                cout<< "We will calculate the number of periods" << endl;
                cout << "Please enter the loan amount:" << endl;
                cin>>loanAmount;
                cout << "Please enter the annual interest rate in percentage:" << endl;
                cin>>interestRate;
                cout << "Please enter the installment:" << endl;
                cout << "Notice: it has to be greater than "<<interestRate/frequencyPayment/100*loanAmount<<endl;
                do
                {
                    installment=stod(validateInputWithRegex(positiveDoubleRegex));;
                    if(installment<=interestRate/100/frequencyPayment*loanAmount) cout << "Please enter a number greater than "<< interestRate/100/frequencyPayment*loanAmount << endl;
                }while(installment<=interestRate/100/frequencyPayment*loanAmount);
                FixedInstallmentCalculatePeriod(loanAmount, interestRate, installment, frequencyPayment,startingMonth, startingYear);
                break;
            case 4:
                cout << "Please enter the loan amount:" << endl;
                loanAmount=stod(validateInputWithRegex(positiveDoubleRegex));
                cout << "Please enter the installment:" << endl;
                installment=stod(validateInputWithRegex(positiveDoubleRegex));
                cout << "Please enter the number of periods:" << endl;
                cout << "Notice: The number has to be greater than "<< loanAmount/installment << endl;
                do
                {
                    numberPeriods=stoi(validateInputWithRegex(positiveIntRegex));
                    if(numberPeriods<loanAmount/installment) cout << "Please enter a number greater than "<< loanAmount/installment << endl;
                }while(numberPeriods<loanAmount/installment);
                FixedInstallmentCalculateInterest(loanAmount, installment, frequencyPayment, numberPeriods,startingMonth, startingYear);
                break;
        }
    }
}