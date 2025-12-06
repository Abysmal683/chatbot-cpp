#ifndef CONVERSATIONHISTORYDAO_H
#define CONVERSATIONHISTORYDAO_H

#include "baseentitydao.h"
#include "conversationhistory.h"

class ConversationHistoryDAO : public BaseEntityDAO<ConversationHistory>
{
public:
    explicit ConversationHistoryDAO(QSqlDatabase& db);

    // Implementaciones obligatorias
    ConversationHistory fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const ConversationHistory& m) const override;
    void bindUpdate(QSqlQuery& q, const ConversationHistory& m) const override;
    QList<ConversationHistory> getLastMessages(int limit) const;
};
#endif // CONVERSATIONHISTORYDAO_H
