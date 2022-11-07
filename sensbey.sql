-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Server version:               8.0.31 - MySQL Community Server - GPL
-- Server OS:                    Linux
-- HeidiSQL Version:             11.1.0.6116
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;


-- Dumping database structure for sensbey
CREATE DATABASE IF NOT EXISTS `sensbey` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `sensbey`;

-- Dumping structure for table sensbey.currentConfig
CREATE TABLE IF NOT EXISTS `currentConfig` (
  `id` int NOT NULL,
  `st1` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci DEFAULT NULL,
  `st2` varchar(50) DEFAULT NULL,
  `st3` varchar(50) DEFAULT NULL,
  `st4` varchar(50) DEFAULT NULL,
  `st5` varchar(50) DEFAULT NULL,
  `st6` varchar(50) DEFAULT NULL,
  `calibration1` varchar(50) DEFAULT NULL,
  `calibration2` varchar(50) DEFAULT NULL,
  `calibration3` varchar(50) DEFAULT NULL,
  `calibration4` varchar(50) DEFAULT NULL,
  `calibration5` varchar(50) DEFAULT NULL,
  `calibration6` varchar(50) DEFAULT NULL,
  `st1min` varchar(50) DEFAULT NULL,
  `st2min` varchar(50) DEFAULT NULL,
  `st3min` varchar(50) DEFAULT NULL,
  `st4min` varchar(50) DEFAULT NULL,
  `st5min` varchar(50) DEFAULT NULL,
  `st6min` varchar(50) DEFAULT NULL,
  `st1max` varchar(50) DEFAULT NULL,
  `st2max` varchar(50) DEFAULT NULL,
  `st3max` varchar(50) DEFAULT NULL,
  `st4max` varchar(50) DEFAULT NULL,
  `st5max` varchar(50) DEFAULT NULL,
  `st6max` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Data exporting was unselected.

-- Dumping structure for table sensbey.tempControlDevice
CREATE TABLE IF NOT EXISTS `tempControlDevice` (
  `id` int NOT NULL AUTO_INCREMENT,
  `ts` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  `temp1` float DEFAULT '0',
  `temp2` float DEFAULT '0',
  `temp3` float DEFAULT '0',
  `temp4` float DEFAULT '0',
  `temp5` float DEFAULT '0',
  `temp6` float DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=1406 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Data exporting was unselected.

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
