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

CREATE TABLE [entity_location] (
  [player_id] int,
  [npc_id] int,
  [map_id] int
)
GO

CREATE TABLE [item] (
  [item_id] int PRIMARY KEY,
  [type] nvarchar(255) NOT NULL CHECK ([type] IN ('consumable', 'wearable', 'tool', 'quest')),
  [name] nvarchar(255)
)
GO

CREATE TABLE [item_ownership_ledger] (
  [player_id] int,
  [npc_id] int,
  [item_id] int,
  [price] int,
  [tansaction_time] timestamp
)
GO

ALTER TABLE [entity_location] ADD FOREIGN KEY ([map_id]) REFERENCES [map] ([map_id])
GO

ALTER TABLE [item_ownership_ledger] ADD FOREIGN KEY ([item_id]) REFERENCES [item] ([item_id])
GO

ALTER TABLE [player] ADD FOREIGN KEY ([player_id]) REFERENCES [entity_location] ([player_id])
GO

ALTER TABLE [non_player_character] ADD FOREIGN KEY ([npc_id]) REFERENCES [entity_location] ([npc_id])
GO

ALTER TABLE [player] ADD FOREIGN KEY ([player_id]) REFERENCES [item_ownership_ledger] ([player_id])
GO

ALTER TABLE [non_player_character] ADD FOREIGN KEY ([npc_id]) REFERENCES [item_ownership_ledger] ([npc_id])
GO
