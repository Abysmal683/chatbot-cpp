
PRAGMA foreign_keys = ON;

CREATE TABLE genres (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT UNIQUE NOT NULL
);
CREATE TABLE platforms (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT UNIQUE NOT NULL
);
CREATE TABLE tags (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT UNIQUE NOT NULL
);
--TABLA de los videojuegos registrados

CREATE TABLE IF NOT EXISTS games(
   	id INTEGER PRIMARY KEY AUTOINCREMENT,    -- id 

    title TEXT UNIQUE NOT NULL,              -- Nombre del videojuego

    rating REAL CHECK (rating BETWEEN 1 AND 5),  -- valoracion del Videojuego

    description TEXT,       -- Descripcion del Videojuego
    
    avg_playtime_minutes INTEGER, --duraccion del videojuego promedio
    
    created_at TEXT NOT NULL DEFAULT (datetime('now'))
);
CREATE TABLE game_genres (
    game_id INTEGER NOT NULL,
    genre_id INTEGER NOT NULL,
    FOREIGN KEY(game_id) REFERENCES games(id) ON DELETE CASCADE,
    FOREIGN KEY(genre_id) REFERENCES genres(id)
);
CREATE TABLE game_platforms (
    game_id INTEGER NOT NULL,
    platform_id INTEGER NOT NULL,
    FOREIGN KEY(game_id) REFERENCES games(id) ON DELETE CASCADE,
    FOREIGN KEY(platform_id) REFERENCES platforms(id)
);
CREATE TABLE game_tags (
    game_id INTEGER NOT NULL,
    tag_id INTEGER NOT NULL,
    FOREIGN KEY(game_id) REFERENCES games(id) ON DELETE CASCADE,
    FOREIGN KEY(tag_id) REFERENCES tags(id)
);

CREATE INDEX IF NOT EXISTS idx_games_rating ON games(rating);
-- FTS5 virtual table para busquedas textuales rapidas (titulo, descripcion)
CREATE VIRTUAL TABLE IF NOT EXISTS games_fts 
USING fts5(
    title, 
    description, 
    content='games', 
    content_rowid='id'
);
--Tabla de memoria a largo plazo
CREATE TABLE IF NOT EXISTS memory_long_term(
   	id INTEGER PRIMARY KEY AUTOINCREMENT,    -- id

    key TEXT NOT NULL,              -- etiqueda del tema
    
    value TEXT NOT NULL,             -- dato guardado
    
    importance INTEGER CHECK (importance BETWEEN 1 AND 10) DEFAULT 5,			-- importancia dela conversacion
    
    created_at TEXT NOT NULL DEFAULT (datetime('now')) --ISO8601, YYYY - MM - DD fecha guardada de la conversacion
);

CREATE INDEX IF NOT EXISTS idx_memory_long_term_key ON memory_long_term(key);
-- tabla de memoria corto plazo
CREATE TABLE IF NOT EXISTS memory_short_term(
   	id INTEGER PRIMARY KEY AUTOINCREMENT,    -- id
    
    value TEXT NOT NULL,             -- conversacion guardada
   
    expires_at TEXT ,		-- tiempo de vida
    
    related_intent TEXT ,	-- intencion de la conversacion
    
    created_at TEXT NOT NULL DEFAULT (datetime('now'))
);

CREATE INDEX IF NOT EXISTS idx_memory_short_term_expires ON memory_short_term(expires_at);

-- tabla de historial conversado
CREATE TABLE IF NOT EXISTS conversation_history(
   	id INTEGER PRIMARY KEY AUTOINCREMENT,    -- id
    
    user_message TEXT,             -- conversacion guardada del usuario
   
    bot_message TEXT,			-- conversacion guardada del bot
    
    current_timestamp TEXT NOT NULL DEFAULT (datetime('now'))		-- Tiempo dela conversacion --ISO8601, YYYY - MM - DDThh : mm : ss
);

CREATE INDEX IF NOT EXISTS idx_conversation_history_time ON conversation_history(current_timestamp);
-- tabla de reglas
CREATE TABLE IF NOT EXISTS rules(
   	id INTEGER PRIMARY KEY AUTOINCREMENT,    -- id
    
    trigger TEXT NOT NULL,             -- palabra clave
   
    response TEXT NOT NULL,			-- repuesta indicada
    
    priority INTEGER NOT NULL DEFAULT 0		-- peso de la repuesta
);

CREATE INDEX IF NOT EXISTS idx_rules_trigger ON rules(trigger);
--tabla de palabras claves
CREATE TABLE IF NOT EXISTS keywords(
   	id INTEGER PRIMARY KEY AUTOINCREMENT,    -- id de la conversacion
    
    keyword TEXT NOT NULL,             -- palabra clave
   
    category TEXT NOT NULL		-- tipo de peticion
);

CREATE INDEX IF NOT EXISTS idx_keywords_keyword ON keywords(keyword);
-- tabla de preferencias
CREATE TABLE IF NOT EXISTS user_preferences(
   	id INTEGER PRIMARY KEY AUTOINCREMENT,    -- id
    
    key TEXT NOT NULL,             -- conversacion extraida
   
    value TEXT NOT NULL,			-- peso del dato
    
    updated_at TEXT NOT NULL DEFAULT (datetime('now'))
);

CREATE INDEX IF NOT EXISTS idx_user_preferences_key ON user_preferences(key);

-- Tabla de logs (opcional pero util)
CREATE TABLE IF NOT EXISTS logs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    
    level TEXT NOT NULL,                       -- INFOWARNINGERROR
    
    message TEXT NOT NULL,
    
    created_at TEXT NOT NULL DEFAULT (datetime('now'))
);
CREATE INDEX IF NOT EXISTS idx_logs_level ON logs(level);
