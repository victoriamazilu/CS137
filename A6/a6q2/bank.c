#include "bank.h"

Bank* CreateBank(double money, double maxLoan, double loanInterest, double transferFeeRate) {
    // Allocate bank
    Bank *bank = malloc(sizeof(Bank));
    assert(bank);
    // No accounts yet
    bank->accounts = NULL;
    bank->nAcc = 0;
    // Assign inputs
    bank->money = money;
    bank->maxLoan = maxLoan;
    bank->loanInterest = loanInterest;
    bank->transferFeeRate = transferFeeRate;

    return bank;
}

Account* OpenAccount(Bank *bank) {
    Account *result = malloc(sizeof(Account));
    
    bank -> nAcc += 1;
    result -> id = (bank -> nAcc);
    result -> active = true;
    result -> balance = 0.0;
    result -> bank = bank;
    result -> loan.active = false;
    result -> loan.amount = 0.0;
    result -> loan.interest = 1.0;

    bank -> accounts = realloc(bank -> accounts, bank -> nAcc * sizeof(Account *));
    bank -> accounts[(bank -> nAcc) - 1] = result;
    
    return result;
}

void Deposit(double amount, Account *account) {
    if(account -> active == true){
        account -> balance += amount;
    }
}

bool Withdraw(double amount, Account *account) {
    if(account -> balance >= amount){
        account -> balance -= amount;
        return true;
    } else 
        return false;
}

bool TakeLoan(double amount, Account *account) {
    if (account->active && !account->loan.active) {
        if (amount <= account->bank->maxLoan && account->bank->money >= amount) {
            account->balance += amount;  // Add the loan amount to the account balance
            account->bank->money -= amount;  // Deduct the loan amount from the bank's money
            
            account->loan.active = true;  // Mark the loan as active
            account->loan.amount = amount;  // Record the loan amount
            account->loan.interest = account->bank->loanInterest;  // Set the loan interest

            return true;  // The loan was successfully taken
        } else {
            return false;  // The loan amount exceeds the maximum loan amount or the bank's money
        }
    } else {
        return false;  // The account is not active or there is already an active loan
    }

    
    /*if (account->active && !account->loan.active) {
        if (amount <= account->bank->maxLoan && account->bank->money >= amount) {
            account->balance += amount;
            account->bank->money -= amount;
            
            account->loan.active = true;
            account->loan.amount = amount;

            return true;
        } else{
            return false;
        }
    } else{
        return false;
    } */
   
}

bool PayLoan(Account *account) {
    if((account -> active == true) && (account -> loan.active == true)){
        if(account -> balance >= (account -> loan.amount * account -> loan.interest)){
            float totalPayment = account -> loan.amount * account -> loan.interest;
            account -> balance -= totalPayment;
            
            account -> bank -> money += account -> loan.amount;
            account -> bank -> loanInterest += totalPayment - account -> loan.amount;
            
            account -> loan.active = false;
            account -> loan.amount = 0;
            
            return true;
        }
    }
    return false;
}


bool Transfer(double amount, Account *sender, Account *receiver) {
    if (!sender->active || !receiver->active) return false;  // Both accounts must be active

    double fee = (sender->bank != receiver->bank) ? sender->bank->transferFeeRate * amount : 0;
    if (sender->balance < amount + fee) return false;  // The sender must have enough balance to cover the amount and fee

    sender->balance -= amount + fee;  // Deduct the amount and fee from the sender's balance
    if (sender->bank != receiver->bank) {
        sender->bank->money += fee;  // Add the fee to the sender's bank money
    }
    receiver->balance += amount;  // Add the amount to the receiver's balance

    return true;
    
    /*if(sender -> bank != receiver -> bank){
        double fee = sender->bank->transferFeeRate * amount;
        if (sender->balance < amount + fee) {
            return false;
        }
        sender -> balance -= (amount + fee);
        sender -> bank -> money += fee;
        receiver -> balance += amount;
        return true;
    } else{
        sender -> balance -= amount;
        receiver -> balance += amount;
        return true;
    }*/
}

bool CollectLoanPayments(Bank *bank) {
    for (int i = 0; i < bank->nAcc; i++) {
        Account *account = bank->accounts[i];
        if (account->loan.active) {
            double paymentAmount = account->loan.amount * account->loan.interest;
            if (account->balance < paymentAmount) return false;  // The account must have enough balance to cover the payment

            account->balance -= paymentAmount;  // Deduct the payment amount from the account balance
            account->bank->money += paymentAmount;  // Add the payment to the bank's money
            account->loan.active = false;  // Mark the loan as inactive
        }
    }
    return true;
    
    /*for(int i = 0; i < bank -> nAcc; i++){
        if(!PayLoan(bank -> accounts[i])){
            return false;
        }
    }
    return true; */
}

bool CloseAccount(Account *account) {
    if (!account->active) return false;  // The account must be active to be closed

    if (account->loan.active && !PayLoan(account)) return false;  // If there is an active loan, it must be paid off

    account->active = false;  // Mark the account as inactive
    account->balance = 0;  // Set the account balance to 0

    return true;
    
    /*if(PayLoan(account)){
        account -> active = false;
        account -> balance = 0;
        return true;
    }

    return false; */
}

Bank* ForceDestroyBank(Bank *bank) {
    // Check if bank exists
    if (!bank)
        return NULL;
    // Just free the memory
    for (int i = 0; i < bank->nAcc; i++) {
                  free(bank->accounts[i]);
    }
    free(bank->accounts);
        
    free(bank);
    bank = NULL;
    return NULL;
}

void ShowAccount(Account *account) {
    printf("Account #%d:\n", account->id);
    if (account->active) {
        printf("Balance: %.3f\n", account->balance);
        if (account->loan.active) {
            printf("Loaned %.3f with interest %f\n",
                account->loan.amount, account->loan.interest);
        }
    } else {
        printf("Inactive account\n");
    }
}

void ShowBank(Bank *bank) {
    printf("BANK:\n");
    printf("Total money in bank: %.3f\n", bank->money);
    printf("Maximum loan offered: %.3f\n", bank->maxLoan);
    printf("Interest for loans: %f\n", bank->loanInterest);
    printf("Fee for a money transfer: %f\n", bank->transferFeeRate);
    //printf("----------------\n");
    for (int i = 0; i < bank->nAcc; i++) {
        ShowAccount(bank->accounts[i]);
        printf("----------------\n");
    }
}

