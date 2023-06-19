-- sellers ranking by the most amount of transactions or by the most total value of transactions
create global temporary table npc_ranking (
    npc_id number(38, 0),
    total_transactions number,
    total_price_amount number
)
on commit delete rows;
call npc_ranking_query();
select * from npc_ranking where rownum = 10 order by total_transactions desc;
select * from npc_ranking where rownum = 10 order by total_price_amount desc;
commit;

create or replace procedure npc_ranking_query
as
    total_transactios number;
    total_price_amount number;
begin
  for npc_rec in (select npc_id from non_player_character)
  loop
    begin
    NPC_TRANSACTIONS_QUERY(THIS_NPC_ID => npc_rec.npc_id);
    end;
    select sum(transactions) into total_transactios from npc_transactions;
    select sum(total_prcie_amount) into total_price_amount from npc_transactions;
    if total_transactios is not null
    and total_price_amount is not null
    then
      insert into npc_ranking values(npc_rec.npc_id, total_transactios, total_price_amount);
    end if;
    commit;
  end loop;
end npc_ranking_query;
