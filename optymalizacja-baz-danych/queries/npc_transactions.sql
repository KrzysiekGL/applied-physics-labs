-- select all transactions done by a random npc
create global temporary table npc_transactions (
    npc_id number(38, 0),
    player_id number(38, 0),
    transactions number,
    total_prcie_amount number,
    first_transaction_date timestamp,
    last_transaction_date timestamp
)
on commit delete rows;
select npc_id from item_ownership_ledger order by dbms_random.random;
call npc_transactions_query([npc_id]);
select * from npc_transactions order by transactions desc;
commit;

create or replace procedure npc_transactions_query (
  this_npc_id number
)
as
  number_of_transactions number;
  total_price number;
  first_transaction timestamp;
  last_transaction timestamp;
begin
  for player_rec in (select player_id from player)
  loop
    select count(*) into number_of_transactions
    from item_ownership_ledger
    where player_id = player_rec.player_id
    and npc_id = this_npc_id;

    select min(transaction_time) into first_transaction
    from item_ownership_ledger
    where player_id = player_rec.player_id
    and npc_id = this_npc_id;

    select max(transaction_time) into last_transaction
    from item_ownership_ledger
    where player_id = player_rec.player_id
    and npc_id = this_npc_id;

    select sum(price) into total_price
    from item_ownership_ledger
    where player_id = player_rec.player_id
    and npc_id = this_npc_id;

    if total_price is not null
    and number_of_transactions is not null
    and first_transaction is not null
    and last_transaction is not null
    then
      insert into npc_transactions values(this_npc_id, player_rec.player_id, number_of_transactions, total_price, first_transaction, last_transaction);
    end if;

  end loop;
end npc_transactions_query;
