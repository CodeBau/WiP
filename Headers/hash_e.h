#ifndef HASH_E_H
#define HASH_E_H
#include <QString>

QString pswd_to_hash (QString user_pswd, int user_key);
QString hash_to_pswd (QString hash_pswd, int user_key);

#endif // HASH_E_H
