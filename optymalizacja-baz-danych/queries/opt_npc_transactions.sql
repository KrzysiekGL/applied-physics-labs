create or replace NONEDITIONABLE procedure npc_transactions_query (
  this_npc_id number
)
as
  number_of_transactions number;
  total_price number;
  first_transaction timestamp;
  last_transaction timestamp;
begin
  for player_rec in (
    select player_id
    from item_ownership_ledger
    where npc_id = this_npc_id
  )
  loop

    select oldest,
          latest,
          cnt,
          prc
    into first_transaction,
         last_transaction,
         number_of_transactions,
         total_price
    from (
          select min(transaction_time) oldest,
                max(transaction_time) latest,
                count(*) cnt,
                sum(price) prc
          from item_ownership_ledger
          where npc_id  = this_npc_id
          and player_id = player_rec.player_id
    );

    insert into npc_transactions
    values(
      this_npc_id,
      player_rec.player_id,
      number_of_transactions,
      total_price,
      first_transaction,
      last_transaction
    );
  end loop;
end npc_transactions_query;
