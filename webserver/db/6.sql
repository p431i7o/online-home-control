ALTER TABLE  `schedule` ADD  `user_id` INT NOT NULL AFTER  `schedule_id` ,
ADD INDEX (  `user_id` ) ;
ALTER TABLE  `schedule` ADD FOREIGN KEY (  `user_id` ) REFERENCES  `home`.`users` (
	`user_id`
) ON DELETE CASCADE ON UPDATE CASCADE ;
