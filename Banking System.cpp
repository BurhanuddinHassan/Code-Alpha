#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Account;


class Customer {
private:
    string name;
    string address;
    string phoneNumber;
    vector<Account*> accounts; 

public:
    Customer(string name, string address, string phoneNumber)
        : name(name), address(address), phoneNumber(phoneNumber) {}

    void addAccount(Account* account) {
        accounts.push_back(account);
    }

    void displayAccounts() const;

    string getName() const {
        return name;
    }
};


class Account {
private:
    string accountNumber;
    double balance;
    vector<string> transactions;

public:
    Account(string accountNumber, double balance)
        : accountNumber(accountNumber), balance(balance) {}

    string getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back("Deposit: $" + to_string(amount));
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return false;
        }
        balance -= amount;
        transactions.push_back("Withdrawal: $" + to_string(amount));
        return true;
    }

    void transfer(Account& toAccount, double amount) {
        if (withdraw(amount)) {
            toAccount.deposit(amount);
            transactions.push_back("Transfer to " + toAccount.getAccountNumber() + ": $" + to_string(amount));
            toAccount.addTransaction("Transfer from " + getAccountNumber() + ": $" + to_string(amount));
        }
    }

    void addTransaction(const string& transaction) {
        transactions.push_back(transaction);
    }

    void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "Recent Transactions:" << endl;
        for (const string& transaction : transactions) {
            cout << " - " << transaction << endl;
        }
    }
};


class Bank {
private:
    vector<Customer> customers;

public:
    void addCustomer(const Customer& customer) {
        customers.push_back(customer);
    }

    Customer* findCustomer(const string& name) {
        for (Customer& customer : customers) {
            if (customer.getName() == name) {
                return &customer;
            }
        }
        return nullptr;
    }

    void displayAllCustomers() const {
        for (const Customer& customer : customers) {
            cout << "Customer Name: " << customer.getName() << endl;
            customer.displayAccounts();
            cout << endl;
        }
    }
};


void Customer::displayAccounts() const {
    cout << "Customer: " << name << endl;
    for (const Account* account : accounts) {
        account->displayAccountInfo();
    }
}

int main() {
    
    Bank bank;
	

    Customer customer1("Default 1", "123 Main St", "555-1234");
    Customer customer2("Deafult 2", "456 Main St", "555-5678");


    Account account1("123456789", 1000.0);
    Account account2("987654321", 2000.0);


    customer1.addAccount(&account1);
    customer2.addAccount(&account2);


    bank.addCustomer(customer1);
    bank.addCustomer(customer2);


    bank.displayAllCustomers();


    cout << "\nPerforming transactions...\n" << endl;

    account1.deposit(500);
    account2.withdraw(300);
    account1.transfer(account2, 200);

    bank.displayAllCustomers();

    return 0;
}
