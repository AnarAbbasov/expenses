CREATE DEFINER=`anar`@`192.168.1.112` PROCEDURE `GetExpenseByDateRange`(
    IN startDate DATE,
    IN endDate DATE
)
BEGIN
  select sum(gallons*price_g) as spent,purshase_date ,price_g from  expenses.gas_business
    WHERE purshase_date BETWEEN startDate AND endDate
    group by price_g,purshase_date,gallons;
END