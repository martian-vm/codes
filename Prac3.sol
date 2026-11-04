pragma solidity ^0.8.20;

contract BankAccount {

    uint public balance;

    function deposit() public payable {
        require(msg.value > 0, "Deposit amount must be greater than zero");
        balance += msg.value;
    }

    function withdraw(uint amount) public {
        require(amount > 0, "Amount must be greater than zero");
        require(amount <= balance, "Insufficient balance");
        balance -= amount;
        payable(msg.sender).transfer(amount);
    }

    function showBalance() public view returns (uint) {
        return balance;
    }
}
