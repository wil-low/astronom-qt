create table TIME_LOCATION (
	ID integer primary key,
	NAME varchar(255),
	DATE_TIME varchar(255), 
	TIMEZONE_OFFSET vatchar(10),
	LOCATION varchar(255),
	LATITUDE varchar(10),
	LONGITUDE varchar(10)
);
