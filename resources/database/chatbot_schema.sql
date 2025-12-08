PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS genres (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS platforms (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS tags (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT UNIQUE NOT NULL
);

CREATE TABLE IF NOT EXISTS games(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT UNIQUE NOT NULL,
    rating REAL CHECK (rating BETWEEN 1 AND 5),
    description TEXT,
    avg_playtime_minutes INTEGER,
    created_at TEXT NOT NULL DEFAULT (datetime('now'))
);

CREATE TABLE IF NOT EXISTS game_genres (
    game_id INTEGER NOT NULL,
    genre_id INTEGER NOT NULL,
    PRIMARY KEY(game_id, genre_id),
    FOREIGN KEY(game_id) REFERENCES games(id) ON DELETE CASCADE,
    FOREIGN KEY(genre_id) REFERENCES genres(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS game_platforms (
    game_id INTEGER NOT NULL,
    platform_id INTEGER NOT NULL,
    PRIMARY KEY(game_id, platform_id),
    FOREIGN KEY(game_id) REFERENCES games(id) ON DELETE CASCADE,
    FOREIGN KEY(platform_id) REFERENCES platforms(id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS game_tags (
    game_id INTEGER NOT NULL,
    tag_id INTEGER NOT NULL,
    PRIMARY KEY(game_id, tag_id),
    FOREIGN KEY(game_id) REFERENCES games(id) ON DELETE CASCADE,
    FOREIGN KEY(tag_id) REFERENCES tags(id) ON DELETE CASCADE
);

CREATE INDEX IF NOT EXISTS idx_games_rating ON games(rating);

CREATE VIRTUAL TABLE IF NOT EXISTS games_fts
USING fts5(
    title,
    description,
    content='games',
    content_rowid='id'
);

CREATE TABLE IF NOT EXISTS memory_long_term(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    key TEXT NOT NULL,
    value TEXT NOT NULL,
    importance INTEGER CHECK (importance BETWEEN 1 AND 10) DEFAULT 5,
    created_at TEXT NOT NULL DEFAULT (datetime('now'))
);

CREATE INDEX IF NOT EXISTS idx_memory_long_term_key ON memory_long_term(key);

CREATE TABLE IF NOT EXISTS memory_short_term(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    value TEXT NOT NULL,
    expires_at TEXT,
    related_intent TEXT,
    created_at TEXT NOT NULL DEFAULT (datetime('now'))
);

CREATE INDEX IF NOT EXISTS idx_memory_short_term_expires ON memory_short_term(expires_at);

CREATE TABLE IF NOT EXISTS conversation_history(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_message TEXT,
    bot_message TEXT,
    timestamp TEXT NOT NULL
);

CREATE INDEX IF NOT EXISTS idx_conversation_history_time ON conversation_history(timestamp);

CREATE TABLE IF NOT EXISTS rules(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    trigger TEXT NOT NULL,
    response TEXT NOT NULL,
    priority INTEGER NOT NULL DEFAULT 0,
    category TEXT DEFAULT NULL,
    source TEXT DEFAULT 'manual',
    is_active INTEGER NOT NULL DEFAULT 1,
    created_at TEXT DEFAULT (datetime('now')),
    updated_at TEXT DEFAULT (datetime('now')),
    UNIQUE(trigger, response)
);

CREATE INDEX IF NOT EXISTS idx_rules_trigger ON rules(trigger);

CREATE TABLE IF NOT EXISTS keywords(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    keyword TEXT NOT NULL,
    category TEXT NOT NULL,
    UNIQUE(keyword, category)
);

CREATE INDEX IF NOT EXISTS idx_keywords_keyword ON keywords(keyword);

CREATE TABLE IF NOT EXISTS user_preferences(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    key TEXT NOT NULL,
    value TEXT NOT NULL,
    updated_at TEXT NOT NULL DEFAULT (datetime('now'))
);

CREATE INDEX IF NOT EXISTS idx_user_preferences_key ON user_preferences(key);

CREATE TABLE IF NOT EXISTS logs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    level TEXT NOT NULL,
    message TEXT NOT NULL,
    created_at TEXT NOT NULL DEFAULT (datetime('now'))
);

CREATE INDEX IF NOT EXISTS idx_logs_level ON logs(level);
