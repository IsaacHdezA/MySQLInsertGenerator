# MySQLInsertGenerator
I am too lazy to type a lot of INSERT instructions. So I created a C++ program to make it for me. This tiny program uses an .csv file as input (it has to have
an specific format) and creates an .sql file with the INSERT instruction. The output file is named after the table it's inserting ("tableNameInserts.sql").

The .csv file has to have in the first row the next data "databaseName;tablename", the next row: "colName1;colName2;...;colNameN", then the data to insert in
each corresponding column. If the data has strings, you should place that value in between quotation marks, so you don't have to when it creates the .sql file.

This program is still error prone, I, myself have experienced various errors during development, make sure to create the .csv file preferably from scratch and not
using Microsoft Excel or LibreOffice Calc, because those .csv have some weird hiden characters that make my program useless.

I think that's all, hope you like it and be useful to you.
