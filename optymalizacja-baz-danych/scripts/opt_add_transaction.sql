create or replace NONEDITIONABLE procedure add_transaction (
    in_seed number
)
as
    rseed number(20);
    r_player_id number(38, 0);
    r_npc_id number(38, 0);
    r_item_id number(38, 0);
    r_price number(38, 0);
    transaction_timestamp timestamp(6);
begin
  -- transaction is a process of buying somethin by a player from an npc
  -- a tranasction can occure if all of the conditions are met:
  -- both entities are in the same map (player and npc),
  -- item of question is tradable (item_type = 1 or item_type = 2),
  -- price of the item is less than or equal to the wealth of the buying entitie (if not, haggle once),
  -- random player has to have creation timestamp from before the transaction timestap
  dbms_output.enable();

  select to_number(to_char(sysdate, 'sssss'))
  into rseed
  from dual;

  dbms_random.initialize((rseed+in_seed));

  -- random value for the price
  select dbms_random.value(1, 38)
  into r_price
  from dual;

  -- prepare transaction timestamp
  select to_date(sysdate + dbms_random.value(-3650, -365), 'YY-MM-DD HH24:MI:SS')
  into transaction_timestamp
  from dual;

  -- select random tradable item_id
  select item_id into r_item_id
  from (
    select item_id from item
    where item_type != 0
    order by dbms_random.random
  )
  where rownum = 1;

  -- select random player and npc, both have to be in the same location
  select p.player_id,
        n.npc_id
  into r_player_id,
      r_npc_id
  from (
    select el.player_id,
          el.map_id
    from entity_location el
    join (
      select player_id,
            wealth,
            created_at
      from player
      where wealth >= r_price
      and created_at < transaction_timestamp
    ) ori
    on el.player_id = ori.player_id
    where el.player_id is not null
    order by dbms_random.random
  ) p
  join (
    select npc_id,map_id
    from entity_location
    where npc_id is not null
    order by dbms_random.random
  ) n
  on p.map_id = n.map_id
  where rownum =  1;

  -- substract and add price value for the player and for the npc
  update (select wealth from player where player_id = r_player_id)
  set wealth = wealth - r_price;

  update (select wealth from non_player_character where npc_id = r_npc_id)
  set wealth = wealth + r_price;

  -- write the transaction to the ledger
  insert into item_ownership_ledger values(
  r_player_id, r_npc_id,
  r_item_id, r_price,
  transaction_timestamp
  );

  commit;

  dbms_random.terminate;
end add_transaction;
