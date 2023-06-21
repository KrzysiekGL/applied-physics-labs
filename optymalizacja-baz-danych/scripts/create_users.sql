create or replace NONEDITIONABLE procedure create_users as
  rseed number(20);
  user_name varchar2(32);
  created_at timestamp;
  wealth number(38);
  last_pk number(38,0);
  cnt number;
begin
  --dbms_output.enable();
  --dbms_output.put_line('Create users procedure');

  -- initizalize dbms random with rseed
  select to_number(to_char(sysdate, 'sssss')) into rseed from dual;
  dbms_random.initialize(rseed);

  -- determine last pk if ther is any
  select count(*) into cnt from player;
  if(cnt = 0)
  then
    select 0 into last_pk from dual;
  else
    select max(player_id) into last_pk from player;
  end if;
  --dbms_output.put_line('Last player_id: '||last_pk);

  -- random player (player_id, name, created_at, wealth)
  for i in 1..10
  loop
    -- player_id; simply the 'i' from for

    -- name
    user_name := dbms_random.string('L', trunc(dbms_random.value(6,32)));
    --dbms_output.put_line(user_name);

    -- created_at timestamp
    select to_date(sysdate - 1000,'YY-MM-DD HH24:MI:SS')+dbms_random.value(0, 100) into created_at from dual;
    --dbms_output.put_line(created_at);

    -- wealth
    wealth := dbms_random.value(1,38);
    --dbms_output.put_line(wealth);

    -- generated player data
    --dbms_output.put_line('player: ' || (last_pk+i) ||' '|| user_name ||' '|| created_at ||' '|| wealth);

    -- insert into the player table
    insert into player values(last_pk+i, user_name, created_at, wealth);
  end loop;

end create_users;

