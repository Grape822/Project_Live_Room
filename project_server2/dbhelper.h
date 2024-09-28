#ifndef DBHELPER_H
#define DBHELPER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include "pack.h"

class DbHelper
{
private:
    DbHelper();
    DbHelper(const DbHelper&);
    DbHelper& operator =(const DbHelper&);
    ~DbHelper();

public:
    static DbHelper& get_instance()
    {
        static DbHelper instance;
        return instance;
    }

public:
    bool init_db();
    Login_State user_login(const QString& strname, const QString& strpwd);
    Register_State user_register(const QString& strname, const QString& strpwd);

private:
    QSqlDatabase m_db;
};

#endif // DBHELPER_H
