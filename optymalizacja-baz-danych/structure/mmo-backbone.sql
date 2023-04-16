CREATE TABLE player (
	player_id INT PRIMARY KEY,
	name varchar(32),
	created_at TIMESTAMP,
	wealth INT
);

CREATE TABLE non_player_character (
	npc_id INT PRIMARY KEY,
	name varchar(32),
	wealth int
);

CREATE TABLE MAP (
	map_id int PRIMARY KEY,
	name varchar(32)
);

CREATE TABLE item (
	item_id int PRIMARY KEY,
	item_type int, --- 0 - non-tradable, 1 - consumable (could be used only once), 2 - bind type (could be used many times)
	name varchar(32)
);

CREATE TABLE entity_location (
	entity_id int,
	map_id int
);

CREATE TABLE item_ownership_ledger (
	owner_id int,
	item_id int,
	transaction_price int,
	transaction_time TIMESTAMP
);