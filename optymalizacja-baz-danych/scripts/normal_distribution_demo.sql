create or replace procedure normal_distribution_demo as
    rseed number(20);
    r number(20);
    r1 number(20);
    r2 number(20);
    q number(20);
begin
  dbms_output.enable();

  select to_number(to_char(sysdate, 'sssss')) into rseed from dual;

  -- use temporary table 'numbers' to store results
  dbms_random.initialize(rseed);
  for i in 1 .. 10000
  loop
    -- uniform
    --r := dbms_random.value(1,100);
    --dbms_output.put_line(r);

    -- pseudo Gauss/normal
    r1 := dbms_random.value(1,50);
    r2 := dbms_random.value(1,50);
    r := to_number(trunc(r1+r2,50));
    --dbms_output.put_line(to_char(trunc(r1+r2,50)));

    insert into numbers values(r);
  end loop;
  dbms_random.terminate();

  -- check statistics by quantiles
  -- values are distributed between 1 and 100 so expect the folowing
  -- in normal distribution:
  -- values <= 1 - 0Q
  -- values <= 25 - 1Q
  -- values <= 50 - 2Q
  -- values <= 75 - 3Q
  -- values <= 100 - 4Q
  for i in 1 .. 5
  loop
    select count(*) into q from numbers where n <= ((i-1)*25);
    dbms_output.put_line(q);
  end loop;

end normal_distribution_demo;
