begin transaction;
insert into TIME_LOCATION (NAME, DATE_TIME, TIMEZONE_OFFSET, LOCATION, LATITUDE, LONGITUDE) values
	('Wolfgang Amadeus Mozart', '1756-01-27 20:00:00', '+005200', 'SALZBURG, AU', '0474800N', '0130200W');
insert into TIME_LOCATION (NAME, DATE_TIME, TIMEZONE_OFFSET, LOCATION, LATITUDE, LONGITUDE) values
	('Vasyl', '1963-03-08 01:46:00', '+030000', 'Валуйки, Белгородская обл., Россия', '0501300N', '0380500E');
commit;
