#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "database.h"

class Account
{
public:
    Account(std::string data);
    bool createAccount();
    bool deleteAccount(int idRecord);
    const std::string& getUserName() const;
    const std::string& getUserPass() const;

private:
    void parseData(std::string data);
    const std::string& formRecord();

private:
    Database m_db;
    std::string m_user;
    std::string m_password;
    std::string m_formRecord;
};

#endif // ACCOUNT_H
