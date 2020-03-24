Exercício 1:
create view TIT_REAGGE as
    select TITULO from TITULO
    inner join GENERO on GENERO.ID_GENERO=TITULO.ID_GENERO
    where GENERO.NOME = 'Reagge'

alínea (a):
insert into TITULO values (50, 'Bom Bom Que Delícia', 10, to_date('10-01-2010', 'dd-mm-yyyy'), 2, 4, 5, 3);
select * from TIT_REAGGE

Exercício 2:
alter table TITULO add VAL_COMERCIAL number(3)

alínea (a):
update TITULO set VAL_COMERCIAL = PRECO

alínea (b):
create or replace procedure AtualizaValor (ano number, percentagem number)
    
is
    media number;
    
begin
    update TITULO
        set VAL_COMERCIAL = (select median(PRECO) from TITULO where extract(year from DTA_COMPRA) = ano) * (1+percentagem)
        where extract(year from DTA_COMPRA) = ano;
    
end AtualizaValor;
    
alínea (c):
call AtualizaValor(2010, 0.2)

alínea (d):
select TITULO, PRECO, VAL_COMERCIAL, VAL_COMERCIAL-PRECO as DIFERENCA from TITULO
    where VAL_COMERCIAL-PRECO > 0

Exercício 3:
create or replace function DA_PRECO (ID_TIT number)
return integer as RESULTADO integer:=0;

begin
        select PRECO into RESULTADO from TITULO
            where ID_TITULO = ID_TIT;
    
return RESULTADO;

end;

alínea (a):
select ID_TITULO, TITULO, PRECO from TITULO where DA_PRECO(ID_TITULO) = 10

alínea (b):
delete from TITULO where DA_PRECO(ID_TITULO) = 10

Exercício 4:
create table GASTO_TOTAL (
    ID_TOTAL_GASTO number not null constraint GASTO_TOTAL_PK primary key,
    VAL_ATUAL_TOTAL number not null,
    VAL_COMERCIAL_TOTAL number not null
);

alínea (a):
insert into GASTO_TOTAL values(1, 0, 0);

update GASTO_TOTAL 
    set VAL_ATUAL_TOTAL = (select sum(PRECO) from TITULO),
        VAL_COMERCIAL_TOTAL = (select sum(VAL_COMERCIAL) from TITULO)
    where ID_TOTAL_GASTO = 1;

alínea (b):
create sequence TITULO_SQ
    increment by 1
    start with 51
;

create or replace trigger ID_TITULO_TRIG
    before
        insert on TITULO
    for each row

begin
    if :NEW.ID_TITULO is null then
        select TITULO_SQ.NEXTVAL
        into :NEW.ID_TITULO
        from DUAL;
    end if;
end;

alínea (c):
create or replace trigger valor_total
    after 
    insert or update or delete 
    on TITULO

begin
    if inserting then
        update GASTO_TOTAL 
        set VAL_ATUAL_TOTAL = (select sum(PRECO) from TITULO),
            VAL_COMERCIAL_TOTAL = (select sum(VAL_COMERCIAL) from TITULO)
        where ID_TOTAL_GASTO = 1;
    end if;

    if updating then
        update GASTO_TOTAL 
        set VAL_ATUAL_TOTAL = (select sum(PRECO) from TITULO),
            VAL_COMERCIAL_TOTAL = (select sum(VAL_COMERCIAL) from TITULO)
        where ID_TOTAL_GASTO = 1;
    end if;

    if deleting then
        update GASTO_TOTAL 
        set VAL_ATUAL_TOTAL = (select sum(PRECO) from TITULO),
            VAL_COMERCIAL_TOTAL = (select sum(VAL_COMERCIAL) from TITULO)
        where ID_TOTAL_GASTO = 1;
    end if;
end;

alínea (d):
insert into TITULO
    values (NULL, 'Enjoy Triggers', 20, to_date('22-02-2000', 'dd-mm-yyyy'), 4, 6, 5, 6, 22);

alínea (e):
update TITULO set PRECO=30 where TITULO='get get get get';

alínea (f):
delete from MUSICA where ID_TITULO=15;
delete from REVIEW where ID_TITULO=15;
delete from TITULO where TITULO='go head';