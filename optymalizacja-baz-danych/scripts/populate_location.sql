create or replace NONEDITIONABLE procedure populate_location as
  rseed number(20);
  rand_map number(38,0);
  r1 number(38, 0);
  r2 number(38, 0);
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

  -- put players into random locations (pseudo normal distribution)
  begin
  for player_rec in (select player_id from player)
  loop
    -- random map id
    r1 := dbms_random.value(1, (max_map_id/2));
    r2 := dbms_random.value(1, (max_map_id/2));
    rand_map := to_number(trunc(r1+r2,(max_map_id/2)));

    -- next player id, insert into the table
    player_id := player_rec.player_id;
    insert into entity_location values(player_id, NULL, rand_map);
  end loop;
  end;

  -- put npcs into random locations (pseudo normal distribution)
  begin
  for npc_rec in (select npc_id from non_player_character)
  loop
    -- random map id
    r1 := dbms_random.value(1, (max_map_id/2));
    r2 := dbms_random.value(1, (max_map_id/2));
    rand_map := to_number(trunc(r1+r2,(max_map_id/2)));

    -- next npc into id, insert into the table
    npc_id := npc_rec.npc_id;
    insert into entity_location values(NULL, npc_id, rand_map);
  end loop;
  end;

  dbms_random.terminate;

end populate_location;

