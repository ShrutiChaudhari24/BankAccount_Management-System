# include <bits/stdc++.h>
using namespace std;

class BankAccount{
    protected:
    int accountNo;
    string accountHolderName;
    string mobileNo;
    double balance;

    public:
    BankAccount ( void ) : accountNo(0), accountHolderName(""), mobileNo(""), balance(0.0)
    { }

    BankAccount(int accountNo, string accountHolderName, string mobileNo, double balance) : accountNo(accountNo), accountHolderName(accountHolderName), mobileNo(mobileNo), balance(balance)
    { }

    virtual void acceptAccount(int acc_no)
    {   
        accountNo = acc_no;

        /* double double account no mang raha hai kyoki humney main mae bhi likha hai
        cout << "Enter Account Number : ";
        cin >> accountNo;
        */

        cout << "Enter Account Holder Name : ";
        cin.ignore();
        getline(cin,accountHolderName);

        cout << "Mobile no. : ";
        cin >> mobileNo;

        cout << "Balance : ";
        cin >> balance;

    }

    virtual void displayAccount(){
        cout << "-----------------------------" << endl;
        cout << "Account Number : " << accountNo << endl;
        cout << "Account Holder Name : " << accountHolderName << endl;
        cout << "Mobile no. : " << mobileNo << endl;
        cout << "Balance : " << balance << endl;
        cout << "------------------------------" << endl;
    }

    int getAccountNo(){
        return this->accountNo;
    }

    virtual void deposit(double amount)
    {
        balance = balance + amount;

    }

    virtual void withdraw(double amount)
    {
        if(amount <= balance)
        {
            balance = balance - amount;
        }
        else
        {
            cout << "Insufficient balance" << endl;
        }
    }

    double getBalance()
    {
        return this->balance;
    }

    virtual ~BankAccount()
    { 

    }

};

class SavingsAccount : public BankAccount
{
    private:
    double interestRate;

    public:
    void acceptAccount(int acc_no)
    {
        BankAccount ::acceptAccount(acc_no);
        cout << "Intrest Rate : " ;
        cin >> interestRate;
    }

    void displayAccount()
    {
        BankAccount ::displayAccount();
        cout << "Intrest Rate " << interestRate << " % " << endl;
    }

};

class CurrentAccount : public BankAccount
{
    private:
    double overdraftlimit;

    public:
    void acceptAccount(int acc_no)
    {
        BankAccount::acceptAccount(acc_no);
        cout << "Enter OverDraft Limit : ";
        cin >> overdraftlimit;
    }

    void displayAccount()
    {
        BankAccount::displayAccount();
        cout << "OverDraft Limit : " << overdraftlimit << endl;
    }

    void withdraw(double amount)
    {
        if(amount <= balance + overdraftlimit)
        {
            balance = balance - amount;
        }
        else{
            cout << "Amount exceeds overdraft limit. " << endl;
        }
    }
};

class BankException
{
    private:
    string message;

    public:
    BankException(string message)
    {
        this->message = message;
    }

    string getMessage()
    {
        return this->message;
    }
};

int menuList()
{
    int choice;

    cout << endl <<"************************Bank-Account-Management-System*********************************" << endl;
    cout << "Enter your choice" << endl;
    cout << "1. Add a new Account " << endl;
    cout << "2.Display all Accounts " << endl;
    cout << "3. Search Account " << endl;  // will search account with acc no.
    cout << "4.Deposit Amount " << endl; // acc no lae kae then deposit
    cout << "5.Withdraw Amount " << endl; // acc no lae kae then withdraw
    cout << "6.Display Account Type " << endl; // acc no lae kae then type display karenge typeid use karna pedega
    cout << "7. Exit " << endl;

    cin >> choice;
    return choice;
}

int main()
{   
    BankAccount * accounts[5];
    int choice;
    int count = 0;

    while((choice = menuList()) != 7)
    {
        try
        {
            switch (choice)
            {
            case 1:
            {
                /* 1. Add a new Account  */

                if(count == 5)
                {
                    cout << "Maximum 5 accounts reached." << endl;
                    break;
                }

                int accNo;
                int type;

                cout << "Enter Account number: ";
                cin >> accNo;

                // check duplicate accounts
                bool exists = false;

                for(int i = 0; i < count; i++)
                {
                    if(accounts[i]->getAccountNo() == accNo)
                    {
                        exists = true;
                        // cout << "Account number already exists" << endl;
                        break; // ye break loop sae bhar nikalne kae liye hai
                    }
                }    
                if(exists)
                {
                    cout << "Account number already exists" << endl;
                    break; // ye case sae bhar nikalne kae liye hai
                }
                else{
                    cout << "Enter type of account : "<< endl;
                    cout << "1. Savings Account " << endl;
                    cout << "2. Current Account " << endl;
                    cin >> type;

                    if(type == 1)
                    {
                        accounts[count] = new SavingsAccount();

                    }
                    else if(type == 2)
                    {
                        accounts[count] = new CurrentAccount();
                    }
                    else{
                        cout << "Invalid account type. " << endl;
                        break;
                    }

                    accounts[count]->acceptAccount(accNo);
                    count++;
                    
                    break;  // ye bhi case sae bhar nikalne kae liye hai
                }     
                // break; abb yaha break liknhe ki jarurat nahi hai
            }

            case 2:
            {
                /* 2.Display all Accounts  */
                if(count == 0)
                {
                    cout << "No Accounts Found" << endl;
                    break;
                }
                else{
                    for(int i = 0; i < count; i++)
                    {
                        accounts[i]->displayAccount();
                    }
                    break;
                }
            }

            case 3:  /* 3. Search Account */ 
            {  
                int accNo;
                bool found = false;

                cout << "Enter Account Number: ";
                cin >> accNo;

                for(int i = 0; i < count; i++)
                {
                    if(accounts[i]->getAccountNo() == accNo)
                    {
                        cout << "Account Found\n";
                        accounts[i]->displayAccount();

                        found = true;
                        break;
                    }
                }
                if(!found)
                {
                    cout << "Account Number not found." << endl;
                }
                break;
            }

            case 4:
            {
                /* 4.Deposit Amount */
                int accNo;
                double amount;
                bool found = false;

                cout << "Enter account Number : ";
                cin >> accNo;

                for(int i = 0; i < count; i++)
                {
                    if(accounts[i]->getAccountNo() == accNo)
                    {
                        found = true;

                        cout << "Enter Amount to deposit : ";
                        cin >> amount;

                        if(amount <= 0)
                        {
                            cout << "Invalid deposit amount" << endl;
                        }
                        else
                        {
                            accounts[i]->deposit(amount);

                            cout << "Amount deposited sucessfully" << endl;
                            cout << "Updated Balance : " << accounts[i]->getBalance() << endl;
                        }
                        break;
                    }
                }

                if(!found)
                {
                    cout << "Account Number not Found" << endl;
                }
                break;
            }

            case 5:
            {
                /*5.Withdraw Amount*/
                int accNo;
                double amount;
                bool found = false;

                cout << "Enter Account Number: ";
                cin >> accNo;

                for(int i = 0; i < count; i++)
                {
                    if(accounts[i]->getAccountNo() == accNo)
                    {
                        found = true;

                        cout << "Enter Amount to withdraw : ";
                        cin >> amount;

                        if(amount <= 0)
                        {
                            cout << "Invalid withdraw amount" << endl;
                        }
                        else{
                            accounts[i]->withdraw(amount);

                            cout << "Current Balance: " << accounts[i]->getBalance() << endl;
                        }
                        break;  // ye break loop ko break karne kae liye hai
                    }
                }
                if(!found)
                {
                    cout << "Account Number not found" << endl;
                }
                break; // ye break case ko break karne kae liye hai
            }

            case 6:
            {
                /* 6.Display Account Type  --> yaha typeid ka use karna pedega*/
                int accNo;
                bool found = false;

                cout << "Enter Account Number : ";
                cin >> accNo;

                for(int i = 0; i < count; i++)
                    {
                        if(accounts[i]->getAccountNo() == accNo)
                        {
                            if(typeid(*accounts[i]) == typeid(SavingsAccount)){
                                cout << "Account Type: Saving Account" << endl;
                            }
                            else if(typeid(*accounts[i]) == typeid(CurrentAccount)){
                                cout << "Account Type: Current Account" << endl;
                            }

                            found = true;
                            break; // ye found huya tho for loop sae break hone kae liye hai
                        }
                    }
                    if(!found)
                    {
                        cout << "Account Number not found" << endl;
                    }
                
                    break;
            }

            case 7:
            {
                cout << "Terminating the program " << endl;
                break;
            }

            default:
                cout << "Invalid Choice " << endl;
                break;
            }
        }
        catch(BankException e)
        {
            cout << e.getMessage() << endl;
        }
        
    }
    return 0;
}