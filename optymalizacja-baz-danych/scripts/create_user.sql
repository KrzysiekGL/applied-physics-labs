create or replace NONEDITIONABLE procedure create_users as
    rseed number(20);
    user_name varchar2(32);
    created_at timestamp;
    wealth number(38);
begin
  dbms_output.enable();
  dbms_output.put_line('Create users procedure');
  
  -- initialise dbms random with rseed
  select to_number(to_char(sysdate, 'sssss'))
  into rseed
  from dual;
  dbms_random.initialize(rseed);
  
  -- random player (player_id, name, created_at, wealth)
  for i in 1..10
  loop
    -- player_id; simply the 'i' from for
    
    -- name
    user_name := dbms_random.string('L', trunc(dbms_random.value(6,32))); 
    --dbms_output.put_line(user_name);
    
    -- created_at timestamp
    select to_date(sysdate - 1000,'YY-MM-DD HH24:MI:SS') + dbms_random.value(0, 100)
    into created_at
    from dual;
    --dbms_output.put_line(created_at);
    
    -- wealth
    wealth := dbms_random.value(1,38);
    --dbms_output.put_line(wealth);
    
    -- generated player data
    dbms_output.put_line('player: ' || i ||' '|| user_name ||' '|| created_at ||' '|| wealth);
    
    -- insert into the player table
    insert into player values(i, user_name, created_at, wealth);
  end loop;
    
end create_users;
