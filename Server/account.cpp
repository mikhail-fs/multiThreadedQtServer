#include "account.h"

Account::Account(std::string data)
{
    parseData(data);
}

bool Account::createAccount()
{
    if(m_db.openDataBase(PATH_DATABASE, "a"))
    {
        if(m_db.insertRecord(formRecord()))
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}

bool Account::deleteAccount(int idRecord)
{
    if(m_db.openDataBase(PATH_DATABASE, "r+"))
    {
        if(m_db.deleteRecord(idRecord))
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
}

const std::string& Account::getUserName() const
{
    return m_user;
}

const std::string& Account::getUserPass() const
{
    return m_password;
}

void Account::parseData(std::string data)
{
    std::string::size_type firstPosColon = data.find(":");
    std::string::size_type secondPosColon = data.find(":", firstPosColon + 1);
    if(firstPosColon != data.npos && secondPosColon != data.npos)
    {
        m_user = data.substr(firstPosColon + 1, secondPosColon - firstPosColon - 1);
        m_password = data.substr(secondPosColon + 1);
    }
}

const std::string& Account::formRecord()
{
    std::string tmpUser;
    std::string tmpPass;

    if(m_user.size() < SIZE_OF_FIELD)
    {
        std::string endFieldUser(SIZE_OF_FIELD - m_user.size(), ' ');
        tmpUser = m_user + endFieldUser;
    }

    if(m_password.size() < SIZE_OF_FIELD)
    {
        std::string endFieldPass(SIZE_OF_FIELD - m_password.size(), ' ');
        tmpPass = m_password + endFieldPass;
    }

    m_formRecord = FLAG_LINE + DELIMITER + tmpUser + DELIMITER + tmpPass + END_OF_LINE;
    return m_formRecord;
}
