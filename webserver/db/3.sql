CREATE TABLE IF NOT EXISTS `users` (
	  `user_id` int(11) NOT NULL AUTO_INCREMENT,
	  `user_email` varchar(255) NOT NULL,
	  `user_password` varchar(50) NOT NULL,
	  `user_state` enum('active','inactive') NOT NULL,
	  PRIMARY KEY (`user_id`)
	) ENGINE=InnoDB DEFAULT CHARSET=latin1 COMMENT='user table' AUTO_INCREMENT=1 ;
