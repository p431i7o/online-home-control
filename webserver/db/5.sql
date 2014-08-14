ALTER TABLE  `schedule` CHANGE  `schedule_state`  `schedule_state` ENUM(  'pending',  'active',  'finished',  'canceled' ) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL ;
