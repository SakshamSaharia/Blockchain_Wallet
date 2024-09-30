#include <iostream>
#include <vector>
#include "Blockchain.h"
#include "Wallet.h"

int main() {
    Blockchain myBlockchain;
    std::vector<Wallet*> wallets;

    Wallet saksham("saksham");
    Wallet nikhil("nihkil");
    Wallet dipen("dipen");

    saksham.balance = 100;
    nikhil.balance = 100;
    dipen.balance = 0;

// pass by reference because their data is modified dependently everywhere 
    wallets.push_back(&saksham);
    wallets.push_back(&nikhil);
    wallets.push_back(&dipen);

    Transaction tx1 = saksham.sendFunds(nikhil, 50);  
    Transaction tx2 = nikhil.sendFunds(dipen, 30); 

    // we modified amount externally , it will show lock chain is not valid , bad signature 
    // tx1.amount=60;
    myBlockchain.createTransaction(tx1);
    myBlockchain.createTransaction(tx2);

    myBlockchain.minePendingTransactions();

    myBlockchain.notifyWallets(wallets);
    Transaction tx3 = saksham.sendFunds(nikhil, 50);
    Transaction tx4 = dipen.sendFunds(nikhil, 20);
    myBlockchain.createTransaction(tx3);
    myBlockchain.createTransaction(tx4);
    myBlockchain.minePendingTransactions();

    // for (const auto& wallet : wallets) {
    //     //wallet->printWalletData();
    //     std::cout << "Wallet " << wallet->id << " has balance: " << wallet->balance << std::endl;
    // }

    myBlockchain.notifyWallets(wallets);

    if (myBlockchain.isChainValid()) {
        std::cout << "Blockchain is valid.\n";
    } else {
        std::cout << "Blockchain is not valid!\n";
    }

    myBlockchain.printChain();

    for (const auto& wallet : wallets) {
        //wallet->printWalletData();
        std::cout << "Wallet " << wallet->id << " has balance: " << wallet->balance << std::endl;
    }

    return 0;
}