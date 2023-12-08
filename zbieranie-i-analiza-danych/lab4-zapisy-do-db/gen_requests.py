import sqlite3
import time
import math
import os

os.remove("db.db")
db = sqlite3.connect("db.db")

# create db tables
db.execute("CREATE TABLE with_pk (id integer not null primary key, log_a integer, log_b integer);")
db.execute("CREATE TABLE with_pk_ai (id integer not null primary key autoincrement, log_a integer, log_b integer);")
db.execute("CREATE TABLE without_pk (log_a integer, log_b integer);")

tables = ["with_pk", "with_pk_ai", "without_pk"]

# number of data to add
loads = [10000, 100000, 1000000, 10000000]
for table in tables:
    print("table ", table)
    for load in loads:
        print("load ", load)
        start = time.time()
        for i in range(0, load):
            id_val = i+load
            log_a = math.sqrt(i**2 + load)
            log_b = i**2
            query = ""
            if table == "with_pk":
                query = "insert into {} (id, log_a, log_b) values({}, {}, {});".format(table, id_val, log_a, log_b)
            else:
                query = "insert into {} (log_a, log_b) values({}, {});".format(table, log_a, log_b)
            db.execute(query)
        stop = time.time()
        print("dt ", stop-start)
    print("------------")

# clean db
for table in tables:
    query = "drop table {};".format(table)
    db.execute(query)

db.close()
