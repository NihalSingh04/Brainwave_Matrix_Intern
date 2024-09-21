#include <iostream>
#include <string>
#include <map>
using namespace std;

map<int, pair<string, double>> accounts; 

void initializeAccounts();
void displayMenu();
void addAccount();
void removeAccount();
void selectAccount(int& accountID);
void checkBalance(int accountID);
void depositMoney(int accountID);
void withdrawMoney(int accountID);
void transferMoney(int fromAccountID);

void initializeAccounts() {
    accounts[1] = {"pratham", 1000.0};
    accounts[2] = {"rishabh", 500.0};
    accounts[3] = {"ayush", 1500.0};
    accounts[4] = {"arpit", 1300.0};
}

void displayMenu() {
    cout << "\nATM Menu\n";
    cout << "1. Add Account\n";
    cout << "2. Remove Account\n";
    cout << "3. Select Account\n";
    cout << "4. Check Balance\n";
    cout << "5. Deposit Money\n";
    cout << "6. Withdraw Money\n";
    cout << "7. Transfer Money\n";
    cout << "8. Exit\n";
    cout << "Choose an option (1-8): ";
}

void addAccount() {
    int accountID;
    string accountName;
    double initialBalance;

    cout << "Enter new account ID: ";
    cin >> accountID;

    if (accounts.find(accountID) != accounts.end()) {
        cout << "Account ID already exists.\n";
        return;
    }

    cout << "Enter account name: ";
    cin.ignore(); 
    getline(cin, accountName);
    
    cout << "Enter initial balance: ";
    cin >> initialBalance;

    if (initialBalance < 0) {
        cout << "Initial balance cannot be negative.\n";
        return;
    }

    accounts[accountID] = {accountName, initialBalance};
    cout << "Account created successfully.\n";
}

void removeAccount() {
    int accountID;
    cout << "Enter account ID to remove: ";
    cin >> accountID;

    auto it = accounts.find(accountID);
    if (it != accounts.end()) {
        accounts.erase(it);
        cout << "Account removed successfully.\n";
    } else {
        cout << "Account ID not found.\n";
    }
}

void selectAccount(int& accountID) {
    cout << "Available accounts:\n";
    for (const auto& account : accounts) {
        cout << account.first << ": " << account.second.first << endl;
    }
    cout << "Enter the account ID you want to use: ";
    cin >> accountID;

    if (accounts.find(accountID) == accounts.end()) {
        cout << "Invalid account ID.\n";
        accountID = -1; 
    } else {
        cout << "Selected account: " << accounts[accountID].first << endl;
    }
}

void checkBalance(int accountID) {
    if (accountID != -1) {
        cout << "Your balance is ₹" << accounts[accountID].second << endl;
    } else {
        cout << "No account selected.\n";
    }
}

void depositMoney(int accountID) {
    if (accountID != -1) {
        double amount;
        cout << "Enter amount to deposit: ";
        cin >> amount;

        if (amount > 0) {
            accounts[accountID].second += amount;
            cout << "Deposited ₹" << amount << ". New balance: ₹" << accounts[accountID].second << endl;
        } else {
            cout << "Invalid amount.\n";
        }
    } else {
        cout << "No account selected.\n";
    }
}

void withdrawMoney(int accountID) {
    if (accountID != -1) {
        double amount;
        cout << "Enter amount to withdraw: ";
        cin >> amount;

        if (amount > 0 && amount <= accounts[accountID].second) {
            accounts[accountID].second -= amount;
            cout << "Withdrew ₹" << amount << ". New balance: ₹" << accounts[accountID].second << endl;
        } else if (amount > accounts[accountID].second) {
            cout << "Insufficient funds.\n";
        } else {
            cout << "Invalid amount.\n";
        }
    } else {
        cout << "No account selected.\n";
    }
}

void transferMoney(int fromAccountID) {
    if (fromAccountID != -1) {
        int toAccountID;
        double amount;

        cout << "Enter the account ID to transfer to: ";
        cin >> toAccountID;

        if (accounts.find(toAccountID) == accounts.end()) {
            cout << "Invalid destination account ID.\n";
            return;
        }

        cout << "Enter amount to transfer: ";
        cin >> amount;

        if (amount > 0 && amount <= accounts[fromAccountID].second) {
            accounts[fromAccountID].second -= amount;
            accounts[toAccountID].second += amount;
            cout << "Transferred ₹" << amount << " to account ID " << toAccountID << ".\n";
            cout << "New balance: ₹" << accounts[fromAccountID].second << endl;
        } else if (amount > accounts[fromAccountID].second) {
            cout << "Insufficient funds.\n";
        } else {
            cout << "Invalid amount.\n";
        }
    } else {
        cout << "No account selected.\n";
    }
}

int main() {
    int accountID = -1; 
    int choice;

    initializeAccounts(); 

    cout << "Welcome to the ATM\n";

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addAccount();
                break;
            case 2:
                removeAccount();
                break;
            case 3:
                selectAccount(accountID);
                break;
            case 4:
                checkBalance(accountID);
                break;
            case 5:
                depositMoney(accountID);
                break;
            case 6:
                withdrawMoney(accountID);
                break;
            case 7:
                transferMoney(accountID);
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 8);

    return 0;
}
