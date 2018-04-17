-- MySQL dump 10.13  Distrib 5.7.17, for Win64 (x86_64)
--
-- Host: localhost    Database: gabinet
-- ------------------------------------------------------
-- Server version	5.7.21-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `godziny`
--

DROP TABLE IF EXISTS `godziny`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `godziny` (
  `godziny_id` int(11) NOT NULL AUTO_INCREMENT,
  `uzytkownik_id` int(11) NOT NULL,
  `po_od` time DEFAULT NULL,
  `po_do` time DEFAULT NULL,
  `wt_od` time DEFAULT NULL,
  `wt_do` time DEFAULT NULL,
  `sr_od` time DEFAULT NULL,
  `sr_do` time DEFAULT NULL,
  `cz_od` time DEFAULT NULL,
  `cz_do` time DEFAULT NULL,
  `pi_od` time DEFAULT NULL,
  `pi_do` time DEFAULT NULL,
  `so_od` time DEFAULT NULL,
  `so_do` time DEFAULT NULL,
  `ni_od` time DEFAULT NULL,
  `ni_do` time DEFAULT NULL,
  PRIMARY KEY (`godziny_id`),
  UNIQUE KEY `godziny_id_UNIQUE` (`godziny_id`),
  KEY `fk_godziny_uzytkownik_idx` (`uzytkownik_id`),
  CONSTRAINT `fk_godziny_uzytkownik` FOREIGN KEY (`uzytkownik_id`) REFERENCES `uzytkownik` (`uzytkownik_id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `godziny`
--

LOCK TABLES `godziny` WRITE;
/*!40000 ALTER TABLE `godziny` DISABLE KEYS */;
INSERT INTO `godziny` VALUES (13,1,'09:00:00','17:00:00','09:00:00','17:00:00','08:00:00','17:00:00','07:00:00','16:00:00','07:00:00','13:00:00','09:00:00','15:00:00',NULL,NULL),(15,4,'12:12:00','16:50:00','12:12:00','16:50:00','12:12:00','16:50:00','12:12:00','16:50:00','12:12:00','16:50:00','12:12:00','16:50:00',NULL,NULL),(19,13,'07:00:00','15:00:00','07:00:00','15:00:00','07:00:00','15:00:00','07:00:00','15:00:00','07:00:00','15:00:00','07:00:00','15:00:00',NULL,NULL),(20,14,'13:00:00','19:30:00','13:00:00','19:30:00','13:00:00','19:30:00','13:00:00','19:30:00','13:00:00','19:30:00','13:00:00','19:30:00',NULL,NULL),(21,15,'07:00:00','15:00:00','07:00:00','15:00:00','07:00:00','15:00:00','09:00:00','15:00:00','07:00:00','15:00:00','07:00:00','15:00:00',NULL,NULL);
/*!40000 ALTER TABLE `godziny` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `info_o_firmie`
--

DROP TABLE IF EXISTS `info_o_firmie`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `info_o_firmie` (
  `firma_id` int(11) NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(200) NOT NULL DEFAULT '0',
  `branza` varchar(200) NOT NULL DEFAULT '0',
  `email` varchar(200) NOT NULL DEFAULT '0',
  `adres` varchar(200) NOT NULL DEFAULT '0',
  `kod_pocztowy` varchar(200) NOT NULL DEFAULT '0',
  `miasto` varchar(200) NOT NULL DEFAULT '0',
  `wojewodztwo` varchar(200) NOT NULL DEFAULT '0',
  `kraj` varchar(200) NOT NULL DEFAULT '0',
  `nip` varchar(15) NOT NULL DEFAULT '0',
  PRIMARY KEY (`firma_id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `info_o_firmie`
--

LOCK TABLES `info_o_firmie` WRITE;
/*!40000 ALTER TABLE `info_o_firmie` DISABLE KEYS */;
INSERT INTO `info_o_firmie` VALUES (1,'NazwaFirmy','Wielobranżowość','twoja@firma.pl','Przykładowa 10','25-500','PrzykładoweMiasto','Świętokrzyskie','Polska','999-999-99-99');
/*!40000 ALTER TABLE `info_o_firmie` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `klienci`
--

DROP TABLE IF EXISTS `klienci`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `klienci` (
  `klienci_id` int(11) NOT NULL AUTO_INCREMENT,
  `imie` varchar(45) COLLATE utf8_polish_ci NOT NULL,
  `nazwisko` varchar(120) COLLATE utf8_polish_ci NOT NULL,
  `email` varchar(200) COLLATE utf8_polish_ci DEFAULT NULL,
  `telefon` varchar(20) COLLATE utf8_polish_ci DEFAULT NULL,
  `ulica` varchar(120) COLLATE utf8_polish_ci DEFAULT NULL,
  `numer` varchar(10) COLLATE utf8_polish_ci DEFAULT NULL,
  `miejscowosc` varchar(120) COLLATE utf8_polish_ci DEFAULT NULL,
  `poczta` varchar(10) COLLATE utf8_polish_ci DEFAULT NULL,
  `modyfikacja` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`klienci_id`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `klienci`
--

LOCK TABLES `klienci` WRITE;
/*!40000 ALTER TABLE `klienci` DISABLE KEYS */;
INSERT INTO `klienci` VALUES (4,'Anna','Nowak','nowaka@mail.com','609 709 809','Dymińska','84','Kielce','25-390','2018-02-25 17:07:14'),(5,'Anna','Nowacka','nowacka@mail.com','609-709-707','Sienkiewicza','32','Kielce','25-700','2018-04-12 13:53:03'),(6,'Stefan','Kowalski','skowalski@mail.com','321-234-678','Kilińskiego','19','Poznań','45-239','2018-04-12 13:53:52'),(7,'Filip','Kozak','kozakfylyp@wp.pl','696-969-696','Sarbinowska','37','Wrocław','54-432','2018-04-17 10:35:04');
/*!40000 ALTER TABLE `klienci` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `uslugi`
--

DROP TABLE IF EXISTS `uslugi`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `uslugi` (
  `uslugi_id` int(11) NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(80) COLLATE utf8_polish_ci NOT NULL,
  `cena` decimal(6,2) NOT NULL,
  `czas` time NOT NULL,
  `opis` text COLLATE utf8_polish_ci,
  PRIMARY KEY (`uslugi_id`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `uslugi`
--

LOCK TABLES `uslugi` WRITE;
/*!40000 ALTER TABLE `uslugi` DISABLE KEYS */;
INSERT INTO `uslugi` VALUES (1,'Przegląd',15.80,'01:00:00','Przegląd, ustalenie stanu leczenia'),(3,'RTG - pojedynczy',17.80,'00:30:00','RTG pojedynczego zęba - pełny zabieg'),(7,'Usunięcie kamienia',20.99,'01:00:00','Usunięcie kamienia poddziąsłowego'),(8,'Konsultacja',39.90,'01:30:00','Wizyta konsultacyjna w gabinecie');
/*!40000 ALTER TABLE `uslugi` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `uzytkownik`
--

DROP TABLE IF EXISTS `uzytkownik`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `uzytkownik` (
  `uzytkownik_id` int(11) NOT NULL AUTO_INCREMENT,
  `uzytkownik_nazwa` varchar(45) COLLATE utf8_polish_ci NOT NULL,
  `uzytkownik_imie` varchar(45) COLLATE utf8_polish_ci NOT NULL,
  `uzytkownik_nazwisko` varchar(120) COLLATE utf8_polish_ci NOT NULL,
  `haslo` varchar(120) COLLATE utf8_polish_ci NOT NULL,
  `pracownik` tinyint(1) NOT NULL,
  PRIMARY KEY (`uzytkownik_id`),
  UNIQUE KEY `uzytkownik_id_UNIQUE` (`uzytkownik_id`),
  UNIQUE KEY `uzytkownik_nazwa_UNIQUE` (`uzytkownik_nazwa`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `uzytkownik`
--

LOCK TABLES `uzytkownik` WRITE;
/*!40000 ALTER TABLE `uzytkownik` DISABLE KEYS */;
INSERT INTO `uzytkownik` VALUES (1,'MG001','Maciek','Grzela','*00A43B0991AE5554FE6316312D41B0DAB23CB308',1),(4,'JK001','Jan','Kowalczyk','*A9B8A6EAD4ED6D909955D080300F2827FEC7F63A',1),(13,'MS001','Stępień','Miłosz','*90886E7512BF81072C50B63D2B4C473683743E9D',1),(14,'CK001','Coś','Ktoś','*25D2EE97459F3D8CCE57FB65872E26C909667F1B',1),(15,'AS001','Smolarski','Adam','*6CF40F6B310B43BCFEFCFE0AA92DD1034FFE26DE',1);
/*!40000 ALTER TABLE `uzytkownik` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `uzytkownik_usluga`
--

DROP TABLE IF EXISTS `uzytkownik_usluga`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `uzytkownik_usluga` (
  `uzytkownik_id` int(11) NOT NULL,
  `uslugi_id` int(11) NOT NULL,
  `modyfikacja` timestamp NULL DEFAULT CURRENT_TIMESTAMP,
  KEY `fk_uzytkownik_usluga_uzytkownik1_idx` (`uzytkownik_id`),
  KEY `fk_uzytkownik_usluga_uslugi1_idx` (`uslugi_id`),
  CONSTRAINT `fk_uzytkownik_usluga_uslugi1` FOREIGN KEY (`uslugi_id`) REFERENCES `uslugi` (`uslugi_id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT `fk_uzytkownik_usluga_uzytkownik1` FOREIGN KEY (`uzytkownik_id`) REFERENCES `uzytkownik` (`uzytkownik_id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `uzytkownik_usluga`
--

LOCK TABLES `uzytkownik_usluga` WRITE;
/*!40000 ALTER TABLE `uzytkownik_usluga` DISABLE KEYS */;
INSERT INTO `uzytkownik_usluga` VALUES (4,3,'2018-02-27 14:22:03'),(14,8,'2018-04-15 15:55:25'),(14,3,'2018-04-15 15:55:46'),(1,8,'2018-04-15 15:56:07'),(15,3,'2018-04-15 16:24:31'),(15,7,'2018-04-15 16:29:41'),(1,3,'2018-04-15 16:38:54'),(1,7,'2018-04-15 16:39:06'),(1,1,'2018-04-15 17:16:01'),(4,1,'2018-04-15 17:16:10'),(13,1,'2018-04-15 17:16:16'),(14,1,'2018-04-15 17:16:20'),(15,1,'2018-04-15 17:16:24'),(13,8,'2018-04-17 10:38:56');
/*!40000 ALTER TABLE `uzytkownik_usluga` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `wizyty`
--

DROP TABLE IF EXISTS `wizyty`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `wizyty` (
  `wizyty_id` int(11) NOT NULL AUTO_INCREMENT,
  `klienci_id` int(11) NOT NULL,
  `uslugi_id` int(11) NOT NULL,
  `uzytkownik_id` int(11) NOT NULL,
  `rezerwacja_od` datetime DEFAULT NULL,
  `rezerwacja_do` datetime DEFAULT NULL,
  `status` enum('oczekuje','wykonana','rezygnacja') COLLATE utf8_polish_ci DEFAULT NULL,
  `modyfikacja` timestamp NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`wizyty_id`),
  KEY `fk_wizyty_klienci1_idx` (`klienci_id`),
  KEY `fk_wizyty_uslugi1_idx` (`uslugi_id`),
  KEY `fk_wizyty_uzytkownik1_idx` (`uzytkownik_id`),
  CONSTRAINT `fk_wizyty_klienci1` FOREIGN KEY (`klienci_id`) REFERENCES `klienci` (`klienci_id`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  CONSTRAINT `fk_wizyty_uslugi1` FOREIGN KEY (`uslugi_id`) REFERENCES `uslugi` (`uslugi_id`) ON DELETE CASCADE ON UPDATE NO ACTION,
  CONSTRAINT `fk_wizyty_uzytkownik1` FOREIGN KEY (`uzytkownik_id`) REFERENCES `uzytkownik` (`uzytkownik_id`) ON DELETE CASCADE ON UPDATE NO ACTION
) ENGINE=InnoDB AUTO_INCREMENT=13 DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `wizyty`
--

LOCK TABLES `wizyty` WRITE;
/*!40000 ALTER TABLE `wizyty` DISABLE KEYS */;
INSERT INTO `wizyty` VALUES (4,4,1,1,'2018-02-27 15:00:00','2018-02-27 15:00:00','oczekuje','2018-02-26 11:25:47'),(8,4,3,1,'2018-02-21 09:30:00','2018-02-21 09:30:00','oczekuje','2018-02-26 11:50:21'),(12,4,1,1,'2018-02-28 11:00:00','2018-02-28 11:00:00','oczekuje','2018-02-27 10:03:26');
/*!40000 ALTER TABLE `wizyty` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-04-17 19:57:46
