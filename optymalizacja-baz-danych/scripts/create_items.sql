create or replace procedure create_items as
  rseed number(20);
  item_name varchar2(32);
  item_type number(2); -- 0: non-tradable; 1: consumable; 2: bind type
  last_pk number(38,0);
  cnt number;
begin
  -- initizalize dbms random with rseed
  select to_number(to_char(sysdate, 'sssss')) into rseed from dual;
  dbms_random.initialize(rseed);

  -- determine last pk if ther is any
  select count(*) into cnt from item;
  if(cnt = 0)
  then
    select 0 into last_pk from dual;
  else
    select max(item_id) into last_pk from item;
  end if;

  --dbms_output.enable();

  -- random item (item_id, item_type, name)
  for i in 1..100000
  loop
    -- type
    item_type := dbms_random.value(0,2);

    -- name
    item_name := dbms_random.string('L', trunc(dbms_random.value(3,32)));

    -- generated item
    --dbms_output.put_line('item: '||(last_pk+i)||' '||item_type||' '||item_name);
    insert into item values(last_pk+i, item_type, item_name);
  end loop;

end create_items;
