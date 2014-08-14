INSERT INTO  `home`.`users` (
	`user_id` ,
	`user_email` ,
	`user_password` ,
	`user_state`
)
VALUES (
	NULL ,  'test@data.com', MD5(  '123456' ) ,  'active'
);
