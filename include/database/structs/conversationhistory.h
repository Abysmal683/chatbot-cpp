#ifndef CONVERSATIONHISTORY_H
#define CONVERSATIONHISTORY_H
#include <QString>

struct ConversationHistory {
    int id = 0;
    QString user_message;
    QString bot_message;
    QString timestamp;   // current_timestamp
};

#endif // CONVERSATIONHISTORY_H
