CREATE TABLE [player] (
  [player_id] int PRIMARY KEY,
  [name] nvarchar(255),
  [created_at] [timestamp],
  [wealth] int
)
GO

CREATE TABLE [non_player_character] (
  [npc_id] int PRIMARY KEY,
  [name] nvarchar(255),
  [wealth] int
)
GO

CREATE TABLE [map] (
  [map_id] int PRIMARY KEY,
  [name] nvarchar(255)
)
GO

-- Entity location ---------------------------------------
create table entity_location (
    player_id number(38, 0),
    npc_id number(38,0),
    map_id number(38,0)
);

alter table entity_location add constraint el_xor_player_npc check (
    (player_id is null and npc_id is not null)
    or (player_id is not null and npc_id is null)
);

alter table entity_location add constraint el_not_null_map check (
    (map_id is not null)
);

alter table entity_location add constraint el_fk_player
    foreign key (player_id)
    references player(player_id)
;

alter table entity_location add constraint el_fk_npc
    foreign key (npc_id)
    references non_player_character(npc_id)
;

alter table entity_location add constraint el_fk_map
    foreign key (map_id)
    references map(map_id)
;

-- test
select count(*) from player;
select count(*) from non_player_character;
select count(*) from map;
select count(*) from entity_location;
describe entity_location;

insert into entity_location values(10100, NULL, 64);
insert into entity_location values(NULL, 240, 4);
insert into entity_location values(10100, 12, 64);
insert into entity_location values(NULL, NULL, 13);
insert into entity_location values(10, NULL, NULL);

select * from entity_location;
truncate table entity_location;
-- Entity location ---------------------------------------


CREATE TABLE [item] (
  [item_id] int PRIMARY KEY,
  [type] nvarchar(255) NOT NULL CHECK ([type] IN ('consumable', 'wearable', 'tool', 'quest')),
  [name] nvarchar(255)
)
GO

-- Item Ownership Ledger ---------------------------------------
create table item_ownership_ledger (
    player_id number(38, 0),
    npc_id number(38, 0),
    item_id number(38, 0),
    price number(38, 0),
    transaction_time timestamp(6)
);

alter table item_ownership_ledger add constraint iol_not_null_item
    check (item_id is not null)
;

alter table item_ownership_ledger add constraint iol_not_null_player check
    (player_id is not null)
;

alter table item_ownership_ledger add constraint iol_not_null_npc check
    (npc_id is not null)
;

alter table item_ownership_ledger add constraint iol_fk_player
    foreign key (player_id)
    references player(player_id)
;

alter table item_ownership_ledger add constraint iol_fk_npc
    foreign key (npc_id)
    references non_player_character(npc_id)
;
-- Item Ownership Ledger ---------------------------------------

ALTER TABLE [item_ownership_ledger] ADD FOREIGN KEY ([item_id]) REFERENCES [item] ([item_id])
GO

ALTER TABLE [player] ADD FOREIGN KEY ([player_id]) REFERENCES [item_ownership_ledger] ([player_id])
GO

ALTER TABLE [non_player_character] ADD FOREIGN KEY ([npc_id]) REFERENCES [item_ownership_ledger] ([npc_id])
GO
