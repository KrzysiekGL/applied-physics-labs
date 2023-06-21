-- select all (random) player's items which were obtaind in transactions
-- with the:
-- * seller of the item (an npc)
-- * item id
-- * type of the item
-- * value of the transaction
-- * timestamp of acquisition of each of the items
select item_ownership_ledger.player_id,
      item_ownership_ledger.npc_id,
      item_ownership_ledger.item_id, item.item_type,
      item_ownership_ledger.price,
      item_ownership_ledger.transaction_time
from item_ownership_ledger
left join item on item_ownership_ledger.item_id = item.item_id
where player_id =
    (select player_id from (
        select player_id
        from item_ownership_ledger
        order by dbms_random.random
        ) where rownum = 1
    )
