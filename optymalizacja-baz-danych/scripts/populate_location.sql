create or replace NONEDITIONABLE procedure populate_location as
  rseed number(20);
  rand_map number(38,0);
  max_map_id number(38,0);
  player_id number(38,0);
  npc_id number(38,0);
begin
  --dbms_output.enable();

  -- initialize dbms random with rseed
  select to_number(to_char(sysdate, 'sssss')) into rseed from dual;
  dbms_random.initialize(rseed);

  -- max map id pk
  select max(map_id) into max_map_id from map;

  -- put players into random locations
  begin
  for player_rec in (select player_id from player)
  loop
    rand_map := dbms_random.value(1,max_map_id);
    player_id := player_rec.player_id;
    insert into entity_location values(player_id, rand_map); -- can't find foreign key in both tables (npcs and players) at the same time
  end loop;
  end;

  -- put npcs into random locations
  begin
  for npc_rec in (select npc_id from non_player_character)
  loop
    rand_map := dbms_random.value(1,max_map_id);
    npc_id := npc_rec.npc_id;
    insert into entity_location values(npc_id, rand_map);
  end loop;
  end;

end populate_location;
