#include "database.h"
#include "iostream"

bool Database::openDataBase(std::string database_name, std::string mode)
{
    file_db = std::fopen(database_name.c_str(), mode.c_str());
    if(!file_db)
    {
        std::cout << "Error for opening file base";
        return false;
    }
    else
    {
        return true;
    }
}

bool Database::insertRecord(std::string new_record)
{
    //flock(fileno(file_db), LOCK_EX | LOCK_NB);
    fseek(file_db, 0, SEEK_END);
    if(!fprintf(file_db, new_record.c_str()))
    {
        std::cout << "Error for inserting record" << std::endl;
        return false;
    }
    //flock(fileno (file_db), LOCK_UN);
    std::fclose(file_db);

    return true;
}

bool Database::deleteRecord(int idRecord)
{
    //flock(fileno(file_db), LOCK_EX | LOCK_NB);
    fseek(file_db, (idRecord - 1) * SIZE_OF_RECORD, SEEK_SET);
    if(!fprintf(file_db, DEL_FLAG_LINE.c_str()))
    {
        std::cout << "Error for deleting record" << std::endl;
        return false;
    }
    //flock(fileno (file_db), LOCK_UN);
    std::fclose(file_db);

    return true;
}
