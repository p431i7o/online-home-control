CREATE TABLE `sessions` (
  `session_id` varchar(40) NOT NULL,
  `dir_ip` varchar(16) NOT NULL,
  `user_agent` varchar(150) NOT NULL,
  `user_id` int(11) NOT NULL,
  `state` varchar(8) NOT NULL DEFAULT 'inactive',
  `entered` int(11) NOT NULL,
  PRIMARY KEY (`session_id`),
  KEY `usuario_id` (`user_id`),
  CONSTRAINT `sessions_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `users` (`user_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
