create or replace procedure create_npcs as
  rseed number(20);
  npc_name varchar2(32);
  wealth number(38,0);
  last_pk number(38,0);
  cnt number;
begin
  --dbms_output.enable();
  --dbms_output.put_line('Create users procedure');

  -- initizalize dbms random with rseed
  select to_number(to_char(sysdate, 'sssss')) into rseed from dual;
  dbms_random.initialize(rseed);

  -- determine last pk if ther is any
  select count(*) into cnt from non_player_character;
  if(cnt=0)
  then
    select 0 into last_pk from dual;
  else
    select max(npc_id) into last_pk from non_player_character;
  end if;
  --dbms_output.put_line('Last npc_id: '||last_pk);

  -- random npc (npc_id, name, wealth)
  for i in 1..1000
  loop
    -- npc_id; simply the 'last_pk+i' from for

    -- name
    npc_name := dbms_random.string('L', trunc(dbms_random.value(6,32)));
    --dbms_output.put_line(user_name);

    -- wealth
    wealth := dbms_random.value(1,38);
    --dbms_output.put_line(wealth);

    -- generated player data
    --dbms_output.put_line('npc: ' || (last_pk+i) ||' '|| npc_name ||' '|| wealth);

    -- insert into the player table
    insert into non_player_character values(last_pk+i, npc_name, wealth);
  end loop;

end create_npcs;

