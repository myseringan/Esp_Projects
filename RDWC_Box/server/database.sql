-- RDWC Box Database Schema
-- MySQL 8.0+

CREATE TABLE IF NOT EXISTS `devices` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `device_id` VARCHAR(32) NOT NULL UNIQUE,
  `name` VARCHAR(64) DEFAULT NULL,
  `created_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS `readings` (
  `id` BIGINT AUTO_INCREMENT PRIMARY KEY,
  `device_id` VARCHAR(32) NOT NULL DEFAULT 'wegabox',
  `root_temp` FLOAT DEFAULT NULL,
  `air_temp` FLOAT DEFAULT NULL,
  `cpu_temp` FLOAT DEFAULT NULL,
  `air_hum` FLOAT DEFAULT NULL,
  `air_press` FLOAT DEFAULT NULL,
  `ph` FLOAT DEFAULT NULL,
  `ph_mv` FLOAT DEFAULT NULL,
  `ec` FLOAT DEFAULT NULL,
  `co2` INT DEFAULT NULL,
  `tvoc` INT DEFAULT NULL,
  `distance` FLOAT DEFAULT NULL,
  `light` INT DEFAULT NULL,
  `ntc` FLOAT DEFAULT NULL,
  `hall` INT DEFAULT NULL,
  `rssi` INT DEFAULT NULL,
  `heap` INT DEFAULT NULL,
  `uptime` INT DEFAULT NULL,
  `created_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  INDEX `idx_device` (`device_id`),
  INDEX `idx_created` (`created_at`)
);

CREATE TABLE IF NOT EXISTS `calibration` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `device_id` VARCHAR(32) NOT NULL DEFAULT 'wegabox',
  `ntc_b` FLOAT DEFAULT 3950,
  `ntc_r25` FLOAT DEFAULT 10000,
  `ec_r1` FLOAT DEFAULT 1000,
  `ec_kt` FLOAT DEFAULT 0.02,
  `ec_val_p1` FLOAT DEFAULT 1.413,
  `ec_val_p2` FLOAT DEFAULT 2.76,
  `ec_r2_p1` FLOAT DEFAULT NULL,
  `ec_r2_p2` FLOAT DEFAULT NULL,
  `ec_val_korr` FLOAT DEFAULT 0,
  `ph_val_p1` FLOAT DEFAULT 4.0,
  `ph_val_p2` FLOAT DEFAULT 7.0,
  `ph_val_p3` FLOAT DEFAULT 10.0,
  `ph_raw_p1` FLOAT DEFAULT NULL,
  `ph_raw_p2` FLOAT DEFAULT NULL,
  `ph_raw_p3` FLOAT DEFAULT NULL,
  `updated_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS `pumps` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `device_id` VARCHAR(32) NOT NULL DEFAULT 'wegabox',
  `pump1` TINYINT DEFAULT 0,
  `pump2` TINYINT DEFAULT 0,
  `pump3` TINYINT DEFAULT 0,
  `pump4` TINYINT DEFAULT 0,
  `pump1_name` VARCHAR(32) DEFAULT 'pH Down',
  `pump2_name` VARCHAR(32) DEFAULT 'pH Up',
  `pump3_name` VARCHAR(32) DEFAULT 'Nutrient A',
  `pump4_name` VARCHAR(32) DEFAULT 'Nutrient B',
  `updated_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);

CREATE TABLE IF NOT EXISTS `logs` (
  `id` BIGINT AUTO_INCREMENT PRIMARY KEY,
  `device_id` VARCHAR(32) NOT NULL DEFAULT 'wegabox',
  `level` VARCHAR(10) DEFAULT 'INFO',
  `message` TEXT,
  `created_at` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
  INDEX `idx_device` (`device_id`),
  INDEX `idx_created` (`created_at`)
);

CREATE TABLE IF NOT EXISTS `settings` (
  `id` INT AUTO_INCREMENT PRIMARY KEY,
  `device_id` VARCHAR(32) NOT NULL DEFAULT 'wegabox',
  `key` VARCHAR(64) NOT NULL,
  `value` TEXT,
  UNIQUE KEY `device_key` (`device_id`, `key`)
);

-- Default data
INSERT INTO `devices` (`device_id`, `name`) VALUES ('wegabox', 'RDWC Box');
INSERT INTO `calibration` (`device_id`) VALUES ('wegabox');
INSERT INTO `pumps` (`device_id`) VALUES ('wegabox');
