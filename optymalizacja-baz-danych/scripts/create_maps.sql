create or replace procedure create_maps as
  rseed number(20);
  map_name varchar2(32);
  last_pk number(38,0);
  cnt number;
begin
  -- initizalize dbms random with rseed
  select to_number(to_char(sysdate, 'sssss')) into rseed from dual;
  dbms_random.initialize(rseed);

  -- determine last pk if ther is any
  select count(*) into cnt from map;
  if(cnt = 0)
  then
    select 0 into last_pk from dual;
  else
    select max(map_id) into last_pk from map;
  end if;

  -- random map (map_id, name)
  for i in 1..100
  loop
    -- name
    map_name := dbms_random.string('L', trunc(dbms_random.value(4,32)));

    -- generated map
    insert into map values(last_pk+i, map_name);
  end loop;

end create_maps;
