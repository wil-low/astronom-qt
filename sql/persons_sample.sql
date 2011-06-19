begin transaction;
insert into TIME_LOCATION (NAME, DATE_TIME, TIMEZONE_OFFSET, LOCATION, LATITUDE, LONGITUDE) values
	('Wolfgang Amadeus Mozart', '1756-01-27T20:00:00', '+005200', 'SALZBURG, AU', '+0474800', '-0130200');
insert into TIME_LOCATION (NAME, DATE_TIME, TIMEZONE_OFFSET, LOCATION, LATITUDE, LONGITUDE) values
	('Vasyl', '1963-03-08T01:46:00', '+030000', 'Валуйки, Белгородская обл., Россия', '+0501300', '+0380500');
insert into TIME_LOCATION (NAME, DATE_TIME, TIMEZONE_OFFSET, LOCATION, LATITUDE, LONGITUDE) values
	('Андрей Ивушкин', '1980-08-25T19:30:00', '+030000', 'Луганск, Украина', '+0483300', '+0391900');
commit;
