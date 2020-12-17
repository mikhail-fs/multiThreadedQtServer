#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <sys/file.h>

const std::string PATH_DATABASE = "/home/mikhail/Qt/my_file_db";
const std::string DELIMITER = ":";
const std::string END_OF_LINE = "\n";
const std::string FLAG_LINE = "R";
const std::string DEL_FLAG_LINE = "D";
const int SIZE_OF_FIELD = 15;
const int COUNT_FIELDS = 2;
const int SIZE_OF_RECORD = (COUNT_FIELDS * SIZE_OF_FIELD) + (COUNT_FIELDS * DELIMITER.size()) +
          END_OF_LINE.size() + FLAG_LINE.size();

class Database{
public:
    bool openDataBase(std::string database_name, std::string mode);
    bool insertRecord(std::string new_record);
    bool deleteRecord(int idRecord);
private:
    FILE * file_db;
};

#endif // DATABASE_H
