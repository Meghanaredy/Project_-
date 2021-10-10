/*objective:Design a project to represent a bank account and its relevant operations
Author:Meghana
Created on:10/10/2021*/

#include <iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;
class Bank{
      char dpname[20];
      int actno;
      char actype;
      float bal;
      int amt;
      char address;
public:
      void getdata(); //taking data from user
      void displaydata(); //displaying the data
      void add();            //function to add new data
      void deposit(int);    //function to deposit amount
      void draw(int);      //function to withdraw amount
      void display() const; //function to display all the data
      int retactno() const; //function to return account number
     
      
};
void Bank::getdata()//Get the data from customer
{
       cout << "\nEnter The account No. : ";
       cin >> actno;
       cout << "\n\nEnter The Name of The account Holder : ";
       cin.ignore();
       cin.getline(dpname, 50);
       cout << "\nEnter Type of The account (C/S) : ";
       cin >> actype;
       cout << "\nEnter The Initial amount(>=100 for Saving and >=500 for current ) : ";
       cin >> amt;
       cout<<"Account created";
}

void Bank::displaydata() //Displaying the data that taken from the customer
{
       cout << "\nAccount No. : " << actno;
       cout << "\nAccount Holder Name : ";
       cout << dpname;
       cout << "\nType of Account : " << actype;
       cout << "\nBalance amount : " << amt;
}
void Bank::add()//ADd the information that needed to the customer
{
       cout<<"\nAdd the customer details"; 
       cout << "\nAccount No. : " ;
       cin>>actno;
       cout << "\nAccount Holder Name : ";
       cin.ignore();
       cin.getline(dpname, 20);
       cout << "\ntype of Account : ";
       cin >> actype;
       cout << "\nBalance amount : ";
       cin >>amt;
       fstream custInfo;
       custInfo.open("custInfo.txt",ios::app);
       custInfo<<actno;
            custInfo<<"\t\t";
            custInfo<<dpname;
            custInfo<<"\t\t";
            custInfo<<actype;
            custInfo<<"\t\t";
            custInfo<<bal;
            custInfo<<"\n";
            
            custInfo.close();
}


void Bank::deposit(int x)//Deposit the amount
{
       amt += x;
}

void Bank::draw(int x)//withdrawing the amount
{
       amt -= x;
}
void Bank::display() const//display the account details
{
       cout << actno << setw(10) << " " << dpname << setw(10) << " " << actype << setw(6) << amt << endl;
}
int Bank::retactno() const
{
       return actno;
}

void get_data();    
void add_account(int);
void display_data(int);  //function to modify record of file
void delete_account(int);  //function to delete record of file
void display_all();        //function to display all account details
void deposit_withdraw(int, int);
void Last_entry(); // function to desposit/withdraw amount for given account
 
int main()
{
       char ch;
       int num;
       do
       {
              cout << "\n\t0.Create account";
              cout << "\n\t1. DEPOSIT AMOUNT";
              cout << "\n\t2. WITHDRAW AMOUNT";
              cout << "\n\t3. BALANCE ENQUIRY";
              cout << "\n\t4. ALL ACCOUNT HOLDER LIST";
              cout << "\n\t5. DELETE AN ACCOUNT";
              cout << "\n\t6. ADD AN ACCOUNT";
              cout << "\n\tChoose from 0 to 7";
              cin >> ch;
              switch (ch)
              {
              case '0':
                     get_data();
                     break;
              case '1':
                     cout << "\n\n\tEnter The account No. : "; cin >> num;
                     deposit_withdraw(num, 1);
                     break;
              case '2':
                     cout << "\n\n\tEnter The account No. : "; cin >> num;
                     deposit_withdraw(num, 2);
                     break;
              case '3':
                     cout << "\n\n\tEnter The account No. : "; cin >> num;
                     display_data(num);
                     break;
              case '4':
                     display_all();
                     break;
              case '5':
                     cout << "\n\n\tEnter The account No. : "; cin >> num;
                     delete_account(num);
                     break;
              case '6':
                     add_account(num);
                     cout<<"\n\nenter the account number";
                     break;
            
              default:cout << "Choose from above";
              }
              cin.ignore();
              cin.get();
       } while (ch != '8');
       return 0;
}
void get_data()
{
       Bank ac;
       ofstream AFile;
       AFile.open("account.txt", ios::binary | ios::app);
       ac.getdata();
       AFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
       AFile.close();
}

void display_data(int n)
{
       Bank ac;
      bool flag = false;
       ifstream BFile;
       BFile.open("account.txt", ios::binary);
       if (!BFile){
       
              cout << "File could not be open";
              return;
       }
       cout<< "\nBALANCE DETAILS\n";
       while (BFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)))
       {
              if (ac.retactno() == n)
              {
                     ac.displaydata();
                     flag = true;
              }
       }
       BFile.close();
       if (flag == false)
              cout << "\n\nAccount number does not exist";
}
void deposit_withdraw(int n, int option)
{
       int amt;
       bool found = false;
       Bank ac;
       fstream File;
       File.open("account.txt", ios::binary | ios::in | ios::out);
       if (!File)
       {
              cout << "File not found";
              return;
       }
       while (!File.eof() && found == false)
       {
              File.read(reinterpret_cast<char *> (&ac), sizeof(Bank));
              if (ac.retactno() == n)
              {
                     ac.displaydata();
                     if (option == 1)
                     {
                           cout << "\n\n\tTO DEPOSITE AMOUNT ";
                           cout << "\n\nEnter The amount to be deposited";
                           cin >> amt;
                           ac.deposit(amt);
                     }
                     if (option == 2)
                     {
                           cout << "\n\n\tTO WITHDRAW AMOUNT ";
                           cout << "\n\nEnter The amount to be withdraw";
                           cin >> amt;
                           ac.draw(amt);
                     }
                     int pos = (-1)*static_cast<int>(sizeof(ac));
                     File.seekp(pos, ios::cur);
                     File.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
                     cout << "\n\n\t Record Updated";
                     found = true;
              }
       }
       File.close();
       if (found == false)
              cout << "\n\n Record Not Found ";
}




void add_account(int n)
{
       bool found = false;
       Bank ac;
       //bool found =false;
       fstream File;
       File.open("account.txt", ios::binary | ios::in | ios::out );
       if (!File)
       {
              cout << "File could not be open !! Press any Key...";
              return;
       }
       while (!File.eof() && found == false)
       {
              File.read(reinterpret_cast<char *> (&ac), sizeof(Bank));
              if (ac.retactno() == n)
              {
                     ac.displaydata();
                     cout << "\n\nEnter The New Details of account" << endl;
                     ac.add();
                     int pos = (-1)*static_cast<int>(sizeof(Bank));
                     File.seekp(pos, ios::cur);
                     File.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
                    
                     cout << "\n\n\t Record Updated";
                     ac.displaydata();
                     found = true;
              
              }
       }
       
       File.close();
       if (found == false)
              cout << "\n\n Record Not Found ";
      
}    
    


void delete_account(int n)
{
       Bank ac;
       ifstream BFile;
       ofstream AFile;
       AFile.open("account.txt", ios::binary);
       if (!AFile)
       {
              cout << "File could not be open !! Press any Key...";
              return;
       }
       AFile.open("cust.txt", ios::binary);
       BFile.seekg(0, ios::beg);
       while (BFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)))
       {
              if (ac.retactno() != n)
              {
                     AFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
              }
       }
       BFile.close();
       AFile.close();
       remove("account.");
       rename("cust.txt", "account.txt");
       cout << "\n\n\tRecord Deleted ..";
}


void display_all()
{
       Bank ac;
       ifstream BFile;
       BFile.open("account.txt", ios::binary);
       if (!BFile)
       {
              cout << "File could not be open !! Press any Key...";
              return;
       }
       cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
       cout << "====================================================\n";
       cout << "A/c no.      NAME           Type  Balance\n";
       cout << "====================================================\n";
       while (BFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)))
       {
              ac.displaydata();
       }

       BFile.close();
}
