CREATE TABLE IF NOT EXISTS `schedule` (
	  `schedule_id` int(11) NOT NULL AUTO_INCREMENT,
	  `schedule_name` varchar(50) NOT NULL,
	  `schedule_state` enum('active','inactive') NOT NULL,
	  `schedule_starts` datetime NOT NULL,
	  `schedule_ends` datetime NOT NULL,
	  `schedule_added` datetime NOT NULL,
	  PRIMARY KEY (`schedule_id`)
	) ENGINE=InnoDB DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
