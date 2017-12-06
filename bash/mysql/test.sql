# test.sql
drop database if exists tempdb;  
create database tempdb;  
use tempdb;
create table if not exists tb_tmp(id smallint,val varchar(20));  
insert into tb_tmp values (1,'jack'),(2,'robin'),(3,'mark');  
select * from tb_tmp;  
