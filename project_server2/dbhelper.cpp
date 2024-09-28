#include "dbhelper.h"
#include <QDebug>

DbHelper::DbHelper():m_db(QSqlDatabase::addDatabase("QODBC"))
{

}

DbHelper::~DbHelper()
{

}

// 初始化，对数据库进行连接
bool DbHelper::init_db()
{
    m_db.setHostName("127.0.0.1");
    m_db.setPort(3306);
    m_db.setUserName("root");
    m_db.setPassword("ljs.0822");
    m_db.setDatabaseName("projectdb");

    return m_db.open();
}

// 收到用户的登录请求
Login_State DbHelper::user_login(const QString& strname, const QString& strpwd)
{
    // 1.名字不符合约束
    if(strname.length() < 3 || strname.length() > 12)
    {
        return ERR_NAME_RULE_LOGIN;
    }

    // 2.密码不符合约束
    if(strpwd.length() < 3 || strpwd.length() > 12)
    {
        return ERR_PWD_RULE_LOGIN;
    }

    // 3.重复登录

    // 4.登录用户名错误或者密码错误或者数据库错误
    QSqlQuery query;
    QString strsql = QString("select pwd from user where name='%1';").arg(strname);

    if(!query.exec(strsql))
    {
        return ERR_DB_LOGIN;
    }

    // 如果 query.next() 有值，说明数据库里面有该用户名：用户名正确
    if(query.next())
    {
        // 密码错误
        if(strpwd != query.value("pwd"))
        {
           return ERR_PWD_LOGIN;
        }

        // 用户名和密码都正确
        return SUCCESS_LOGIN;
    }

    // query.next() 没有值，说明数据库没有该用户名：用户名错误
    return ERR_NAME_LOGIN;
}

// 收到用户的注册请求
Register_State DbHelper::user_register(const QString& strname, const QString& strpwd)
{
    // 1.名字不符合约束
    if(strname.length() < 3 || strname.length() > 12)
    {
        return ERR_NAME_RULE_REGISTER;
    }

    // 2.密码不符合约束
    if(strpwd.length() < 3 || strpwd.length() > 12)
    {
        return ERR_PWD_RULE_REGISTER;
    }

    // 3.两次密码不一致
    // 大家补上

    // 4.重复注册
    QSqlQuery query;
    QString strsql = QString("select name from user where name='%1';").arg(strname);

    if(!query.exec(strsql))
    {
        return ERR_DB_REGISTER;
    }

    if(query.next())
    {
        return ERR_REREGISTER_REGISTER;
    }

    // 5.数据库错误
    strsql = QString("insert into user(name, pwd) values('%1', '%2');").arg(strname).arg(strpwd);

    if(query.exec(strsql))
    {
        return SUCCESS_REGISTER;
    }

    return ERR_DB_REGISTER;
}
