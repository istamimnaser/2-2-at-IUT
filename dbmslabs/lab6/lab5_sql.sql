-- ============================================================
--  Valorant Lab -- Schema & Sample Data
-- ============================================================

-- ── Tables ──────────────────────────────────────────────────

CREATE TABLE agents (
    agent_id             SERIAL PRIMARY KEY,
    agent_name           VARCHAR(50),
    role                 VARCHAR(20),   -- Duelist, Initiator, Controller, Sentinel
    rank_rating          INTEGER,
    contracts_completed  INTEGER,
    bonus_points         NUMERIC(10,2)
);

CREATE TABLE matches (
    match_id        SERIAL PRIMARY KEY,
    map_name        VARCHAR(30),
    available_slots INTEGER,
    match_status    VARCHAR(20)        -- OPEN, FULL
);

CREATE TABLE player_match (
    registration_id   SERIAL PRIMARY KEY,
    agent_id          INTEGER REFERENCES agents(agent_id),
    match_id          INTEGER REFERENCES matches(match_id),
    registration_date DATE DEFAULT CURRENT_DATE
);

CREATE TABLE agent_performance (
    performance_id SERIAL PRIMARY KEY,
    agent_id       INTEGER REFERENCES agents(agent_id),
    kills          INTEGER,
    deaths         INTEGER,
    assists        INTEGER,
    combat_score   INTEGER
);

CREATE TABLE bonus_audit (
    audit_id    SERIAL PRIMARY KEY,
    agent_id    INTEGER,
    old_bonus   NUMERIC(10,2),
    new_bonus   NUMERIC(10,2),
    action_type VARCHAR(50),
    action_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE promotion_review (
    review_id        SERIAL PRIMARY KEY,
    agent_id         INTEGER,
    avg_combat_score NUMERIC(8,2),
    tier             VARCHAR(50),
    review_date      DATE DEFAULT CURRENT_DATE
);

-- ── Agents ───────────────────────────────────────────────────
-- 8 agents covering all four roles

INSERT INTO agents (agent_name, role, rank_rating, contracts_completed, bonus_points) VALUES
    ('Jett',    'Duelist',    1800, 5,  500.00),
    ('Reyna',   'Duelist',    1650, 4,  450.00),
    ('Sova',    'Initiator',  1720, 6,  520.00),
    ('Breach',  'Initiator',  1400, 3,  300.00),
    ('Brimstone','Controller',1550, 5,  480.00),
    ('Omen',    'Controller', 1500, 4,  400.00),
    ('Killjoy', 'Sentinel',   1680, 7,  600.00),
    ('Cypher',  'Sentinel',   1200, 2,  150.00);   -- no performance rows (for Task 3 skip test)

-- ── Matches ──────────────────────────────────────────────────

INSERT INTO matches (map_name, available_slots, match_status) VALUES
    ('Ascent',   5, 'OPEN'),   -- match_id 1
    ('Bind',     1, 'OPEN'),   -- match_id 2  (will go FULL after one insert)
    ('Haven',    0, 'FULL'),   -- match_id 3  (Rule 1 test: already full)
    ('Split',    3, 'OPEN'),   -- match_id 4
    ('Fracture', 4, 'OPEN');   -- match_id 5

-- ── Performance Records ───────────────────────────────────────
-- Jett: 4 matches  →  efficiencies = (12+4-3)=13, (18+6-5)=19, (22+8-4)=26, (15+3-7)=11
--   avg = (13+19+26+11)/4 = 17.25  →  PRO
INSERT INTO agent_performance (agent_id, kills, deaths, assists, combat_score) VALUES
    (1, 12, 3,  4,  280),
    (1, 18, 5,  6,  320),
    (1, 22, 4,  8,  350),
    (1, 15, 7,  3,  295);

-- Reyna: 3 matches  →  efficiencies = (20+2-8)=14, (14+1-6)=9, (17+3-5)=15
--   avg = (14+9+15)/3 = 12.67  →  ADVANCED
INSERT INTO agent_performance (agent_id, kills, deaths, assists, combat_score) VALUES
    (2, 20, 8,  2,  260),
    (2, 14, 6,  1,  230),
    (2, 17, 5,  3,  245);

-- Sova: 4 matches  →  combat scores avg = (310+295+330+305)/4 = 310  →  Radiant Candidate
INSERT INTO agent_performance (agent_id, kills, deaths, assists, combat_score) VALUES
    (3, 10, 4, 12,  310),
    (3,  8, 5, 10,  295),
    (3, 12, 3, 14,  330),
    (3,  9, 6, 11,  305);

-- Breach: 2 matches  →  fewer than 3  →  "Insufficient data for evaluation"
INSERT INTO agent_performance (agent_id, kills, deaths, assists, combat_score) VALUES
    (4,  7, 8,  5,  190),
    (4,  6, 9,  4,  175);

-- Brimstone: 3 matches  →  avg combat = (270+255+265)/3 = 263.33  →  Immortal Candidate
INSERT INTO agent_performance (agent_id, kills, deaths, assists, combat_score) VALUES
    (5,  9, 5,  8,  270),
    (5,  7, 6,  9,  255),
    (5,  8, 4,  7,  265);

-- Omen: 3 matches  →  avg combat = (215+225+220)/3 = 220  →  Ascendant Candidate
INSERT INTO agent_performance (agent_id, kills, deaths, assists, combat_score) VALUES
    (6,  8, 7,  6,  215),
    (6, 10, 6,  7,  225),
    (6,  9, 8,  5,  220);

-- Killjoy: 4 matches  →  avg combat = (190+180+195+170)/4 = 183.75  →  Needs Training
INSERT INTO agent_performance (agent_id, kills, deaths, assists, combat_score) VALUES
    (7,  5, 9,  8,  190),
    (7,  4, 10, 7,  180),
    (7,  6, 8,  9,  195),
    (7,  3, 11, 6,  170);

-- Cypher: NO performance rows  →  Task 3 "Skipping Cypher - No performance data found."

-- ── Existing Registrations (for trigger duplicate / cap tests) ────────────
-- Jett is already in 3 active matches (matches 1, 4, 5)
-- Inserting her into match 2 should trigger Rule 5 (4th active match)

INSERT INTO player_match (agent_id, match_id) VALUES
    (1, 1),   -- Jett  → Ascent
    (1, 4),   -- Jett  → Split
    (1, 5),   -- Jett  → Fracture  (now at cap)
    (2, 1),   -- Reyna → Ascent
    (3, 4),   -- Sova  → Split
    (5, 5);   -- Brimstone → Fracture 