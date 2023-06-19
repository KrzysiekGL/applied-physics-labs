create or replace NONEDITIONABLE procedure npc_transactions_query (
  this_npc_id number
)
as
begin
    insert into npc_transactions
    select this_npc_id,player_id,count(transaction_time),sum(price),min(transaction_time),max(transaction_time)
    from item_ownership_ledger
    where npc_id = this_npc_id
    group by player_id;
end npc_transactions_query;
