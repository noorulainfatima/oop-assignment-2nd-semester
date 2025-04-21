#include<iostream>
#include "ConsoleApplication14.h"
using namespace std;
class bankaccount {
	protected:
	int balance;
	int noofdeposit;
	int noofwithdraw;
	int annualinterestrate;
	int monthlyservicecharges;
public:
	// parametrized constructor...
	bankaccount(int b, int a) {
		balance = b;
		annualinterestrate = a;
		noofdeposit = 0;
		noofwithdraw = 0;
		monthlyservicecharges = 0;
	}
	
	virtual void deposit(int amount) {
		if(amount>0)
		balance += amount;
		noofdeposit++;
	}
	//withdraw:-
	virtual void withdraw(int amount) {
		if (amount > 0 && amount <= balance) {
			balance -= amount;
			noofwithdraw++;
		}
		else {
			cout << "  invalid amount." << endl;
		}
		//calcInt:
		virtual void calcInt() {
			int monthlyInterestRate = (annualinterestrate / 12);
			int monthlyInterest = (balance * monthlyInterestRate) / 100;
			balance += monthlyInterest;
			cout << "Monthly Interest: " << monthlyInterest << endl;
			cout << "Updated Balance: " << balance << endl;
		}
		virtual void monthlyProc() {
			balance -= monthlyServiceCharges;
			calcInt();
			numDeposits = 0;
			numWithdrawals = 0;
			monthlyServiceCharges = 0;
		}
		double getBalance() const { return balance; }
		int getNumDeposits() const { return numDeposits; }
		int getNumWithdrawals() const { return numWithdrawals; }
		double getServiceCharges() const { return monthlyServiceCharges; }
	};

		// Derived class:
		class SavingsAccount : public bankaccount {
		private:
			bool status; 

			void updateStatus() {
				status = (balance >= 25);
			}
	
		public:
			SavingsAccount(double bal, double rate) : bankaccount(bal, rate) {
				updateStatus();
			}

			void deposit(double amount) override {
				if (amount > 0) {
					balance += amount;
					noofdeposit++
					updateStatus();
				}
			}

			void withdraw(double amount) override {
				updateStatus();
				if (!status) {
					cout << "Withdrawal denied. Account is inactive.\n";
					return;
				}
				if (amount <= balance) {
					bankaccount::withdraw(amount);
					updateStatus();
				}
			}
			void monthlyProc() override {
				if (numWithdrawals > 4) {
					monthlyservicecharges += (numWithdrawals - 4) * 1.0;
				}
				bankaccount::monthlyProc();
				updateStatus();
			}
		};

		class CheckingAccount : public bankaccount {
		public:
			CheckingAccount(double bal, double rate) : bankaccount(bal, rate) {}

			void withdraw(double amount) override {
				if (amount > balance) {
					monthlyservicecharges += 15;
					cout << "Insufficient funds. $15 fee charged.\n";
				}
				else {
					bankaccount::withdraw(amount);
				}
			}
			void monthlyProc() override {
				monthlyservicecharges += 5.0 + (0.10 * noofwithdraw);
				bankaccount::monthlyProc();
			}
		};
		// Utility function to print account summary
		void printAccountSummary(const bankaccount& account) {
			cout << "Account Summary:\n";
			cout << "Balance: $" << account.getBalance() << endl;
			cout << "Number of Deposits: " << account.getNumDeposits() << endl;
			cout << "Number of Withdrawals: " << account.getNumWithdrawals() << endl;
			cout << "Monthly Service Charges: $" << account.getServicecharges() << endl;
		}
	
		int main() {
			double initialBalance, annualRate;

			// Savings Account
			cout << "Enter initial balance for Savings Account: ";
			cin >> initialBalance;
			cout << "Enter annual interest rate for Savings Account: ";
			cin >> annualRate;
			SavingsAccount savings(initialBalance, annualRate);

			// Checking Account
			cout << "Enter initial balance for Checking Account: ";
			cin >> initialBalance;
			cout << "Enter annual interest rate for Checking Account: ";
			cin >> annualRate;
			CheckingAccount checking(initialBalance, annualRate);

			// Perform transactions
			int choice;
			do {
				cout << "\n1. Deposit to Savings\n2. Withdraw from Savings\n";
				cout << "3. Deposit to Checking\n4. Withdraw from Checking\n";
				cout << "5. Process Monthly for Savings\n6. Process Monthly for Checking\n";
				cout << "7. Display Savings Summary\n8. Display Checking Summary\n9. Exit\n";
				cout << "Enter your choice: ";
				cin >> choice;

				double amount;
				switch (choice) {
				case 1:
					cout << "Enter deposit amount for savings: ";
					cin >> amount;
					savings.deposit(amount);
					break;
				case 2:
					cout << "Enter withdrawal amount for savings ";
					cin >> amount;
					savings.withdraw(amount);
					break;
				case 3:
					cout << "Enter deposit amount for Checking: ";
					cin >> amount;
					checking.deposit(amount);
					break;
				case 4:
					cout << "Enter withdrawal amount for Checking: ";
					cin >> amount;
					checking.withdraw(amount);
					break;
				case 5:
					savings.monthlyProc();
					break;
				case 6:
					checking.monthlyProc();

					break;
				case 7:
					printAccountSummary(savings);
					break;
				case 8:
					printAccountSummary(checking);
					break;
				case 9:
					cout << "Exiting program.\n";
					break;
				default:
					cout << "Invalid choice. Try again.\n";
				}
			} while (choice != 9);

			return 0;
		}
		


