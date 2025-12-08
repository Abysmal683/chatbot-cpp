#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

namespace Constants {

/* ============================================================
 *  TABLAS DE LA BASE DE DATOS
 * ============================================================ */
namespace Tables {
inline const QString Games            = "games";
inline const QString Genres           = "genres";
inline const QString Platforms        = "platforms";
inline const QString Tags             = "tags";

inline const QString GameGenres       = "game_genres";
inline const QString GamePlatforms    = "game_platforms";
inline const QString GameTags         = "game_tags";

inline const QString MemoryLongTerm   = "memory_long_term";
inline const QString MemoryShortTerm  = "memory_short_term";

inline const QString ConversationHist = "conversation_history";
inline const QString Rules            = "rules";
inline const QString Keywords         = "keywords";
inline const QString UserPreferences  = "user_preferences";
inline const QString Logs             = "logs";
}

/* ============================================================
 *  COLUMNAS POR TABLA
 * ============================================================ */
namespace Columns {

/* -------- GAMES -------- */
namespace Games {
inline const QString Id          = "id";
inline const QString Title       = "title";
inline const QString Description = "description";
inline const QString Rating      = "rating";
inline const QString AvgPlaytime = "avg_playtime_minutes";
inline const QString CreatedAt   = "created_at";
}

/* -------- GENRES / TAGS / PLATFORMS -------- */
namespace GenericSimple {
inline const QString Id   = "id";
inline const QString Name = "name";
}

/* -------- RELATION TABLES -------- */
namespace GameGenres {
inline const QString GameId  = "game_id";
inline const QString GenreId = "genre_id";
}
namespace GamePlatforms {
inline const QString GameId     = "game_id";
inline const QString PlatformId = "platform_id";
}
namespace GameTags {
inline const QString GameId = "game_id";
inline const QString TagId  = "tag_id";
}

/* -------- LONG TERM MEMORY -------- */
namespace MemoryLongTerm {
inline const QString Id         = "id";
inline const QString Key        = "key";
inline const QString Value      = "value";
inline const QString Importance = "importance";
inline const QString CreatedAt  = "created_at";
}

/* -------- SHORT TERM MEMORY -------- */
namespace MemoryShortTerm {
inline const QString Id           = "id";
inline const QString Value        = "value";
inline const QString ExpiresAt    = "expires_at";
inline const QString RelatedIntent= "related_intent";
inline const QString CreatedAt    = "created_at";
}

/* -------- CONVERSATION HISTORY -------- */
/* -------- CONVERSATION HISTORY -------- */
namespace ConversationHistory {
inline const QString Id      = "id";
inline const QString UserMsg = "user_message";
inline const QString BotMsg  = "bot_message";
inline const QString Time    = "timestamp";  // <-- actualizado
}

/* -------- RULES -------- */
namespace Rules {
inline constexpr auto Table    = "rules";
inline constexpr auto Id       = "id";
inline constexpr auto Trigger  = "trigger";
inline constexpr auto Response = "response";
inline constexpr auto Priority = "priority";
}

/* -------- KEYWORDS -------- */
namespace Keywords {
inline const QString Id       = "id";
inline const QString Keyword  = "keyword";
inline const QString Category = "category";
}

/* -------- USER PREFERENCES -------- */
namespace UserPreferences {
inline const QString Id       = "id";
inline const QString Key      = "key";
inline const QString Value    = "value";
inline const QString UpdatedAt= "updated_at";
}

/* -------- LOGS -------- */
namespace Logs {
inline const QString Id        = "id";
inline const QString Level     = "level";
inline const QString Message   = "message";
inline const QString CreatedAt = "created_at";
}

} // namespace Columns

/* ============================================================
 * PALABRAS CLAVES GENERALES (para AI/NLP/UI)
 * NO SON TABLAS — Son keywords internas del sistema
 * ============================================================ */
namespace Keywords {
inline const QString Search     = "buscar";
inline const QString Recommend  = "recomienda";
inline const QString Tag        = "tag";
inline const QString Genre      = "genero";
inline const QString Platform   = "plataforma";
inline const QString Preference = "preferencia";
}

} // namespace Constants

#endif // CONSTANTS_H
