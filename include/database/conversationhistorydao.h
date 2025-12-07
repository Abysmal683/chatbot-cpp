#ifndef CONVERSATIONHISTORYDAO_H
#define CONVERSATIONHISTORYDAO_H

#include "baseentitydao.h"
#include "conversationhistory.h"
#include "constants.h"

class ConversationHistoryDAO : public BaseEntityDAO<ConversationHistory>
{
public:
    explicit ConversationHistoryDAO(QSqlDatabase& db);

    ConversationHistory fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const ConversationHistory& m) const override;
    void bindUpdate(QSqlQuery& q, const ConversationHistory& m) const override;

    QList<ConversationHistory> getLastMessages(int limit) const;

private:
    // Alias para no repetir tanto nombre
    static inline const QString& T = Constants::Tables::ConversationHist;

    // Columnas
    static inline const QString& C_Id      = Constants::Columns::ConversationHistory::Id;
    static inline const QString& C_UserMsg = Constants::Columns::ConversationHistory::UserMsg;
    static inline const QString& C_BotMsg  = Constants::Columns::ConversationHistory::BotMsg;
    static inline const QString& C_Time    = Constants::Columns::ConversationHistory::Time;
};

#endif // CONVERSATIONHISTORYDAO_H
