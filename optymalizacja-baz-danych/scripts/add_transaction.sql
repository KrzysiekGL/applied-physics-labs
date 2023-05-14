create or replace NONEDITIONABLE procedure add_transaction as
    rseed number(20);
    r_player_id number(38, 0);
    r_player_wealth number(38, 0);
    r_player_created_at timestamp;
    r_npc_id number(38, 0);
    r_map_id number(38, 0);
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

  select to_number(to_char(sysdate, 'sssss')) into rseed from dual;
  dbms_random.initialize(rseed);

  -- random value for the price
    r_price := dbms_random.value(1,38);

  -- select random tradable item
    insert into tmp_item select item_id,name from item
    where item_type != 0
    order by dbms_random.random;
    select item_id into r_item_id from tmp_item
    where rownum = 1;

  -- select random player and npc, both have to be in the same location
    insert into tmp_map select * from entity_location order by dbms_random.random;
  -- select random map
    select map_id into r_map_id from tmp_map where rownum = 1;
  -- select random palyer
    select player_id into r_player_id from tmp_map
    where rownum = 1 and map_id = r_map_id and player_id is not null;
  -- select random npc
    select npc_id into r_npc_id from tmp_map
    where rownum = 1 and map_id = r_map_id and npc_id is not null;

  -- prepare transaction timestamp
    select to_date(sysdate-1000, 'YY-MM-DD HH24:MI:SS')+dbms_random.value(-100, 100)
    into transaction_timestamp from dual;

  -- check whether this random player is able to buy the item
  -- wealth vs. price and created at timestamp vs. transaction timestamp
    select wealth,created_at into r_player_wealth,r_player_created_at from player
    where player_id=r_player_id;

  -- if so, then yes, buy the item
  -- substract and add price value accordingly for the player and for the npc
    if r_player_wealth >= r_price and r_player_created_at < transaction_timestamp
    then
        dbms_output.put_line('buy the item');

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
    end if;

    --dbms_output.put_line(r_map_id||' '||r_player_id||' '||r_npc_id);

  dbms_random.terminate;
end add_transaction;
