--
-- Host: localhost    Database: 
-- ------------------------------------------------------
-- Server version	5.0.51b-log

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
-- Current Database: `acddb`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `acddb` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `acddb`;

--
-- Data for table `agenttbl`
--

LOCK TABLES `agenttbl` WRITE;
/*!40000 ALTER TABLE `agenttbl` DISABLE KEYS */;
/*!40000 ALTER TABLE `agenttbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `restreasontbl`
--

LOCK TABLES `restreasontbl` WRITE;
/*!40000 ALTER TABLE `restreasontbl` DISABLE KEYS */;
INSERT INTO `restreasontbl` VALUES (1,'吃饭'),(2,'上厕所'),(3,'抽烟'),(4,'午休');
/*!40000 ALTER TABLE `restreasontbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `skillidtbl`
--

LOCK TABLES `skillidtbl` WRITE;
/*!40000 ALTER TABLE `skillidtbl` DISABLE KEYS */;
INSERT INTO `skillidtbl` VALUES (5,'咨询'),(6,'test'),(7,'投诉'),(8,'客服'),(9,'销售');
/*!40000 ALTER TABLE `skillidtbl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `tb_opt_log`
--

LOCK TABLES `tb_opt_log` WRITE;
/*!40000 ALTER TABLE `tb_opt_log` DISABLE KEYS */;
INSERT INTO `tb_opt_log` VALUES (1,'2012-06-08 11:33:09','skill_Id','update id:8');
/*!40000 ALTER TABLE `tb_opt_log` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Current Database: `ccclouddb`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `ccclouddb` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `ccclouddb`;

--
-- Data for table `acd_01`
--

LOCK TABLES `acd_01` WRITE;
/*!40000 ALTER TABLE `acd_01` DISABLE KEYS */;
/*!40000 ALTER TABLE `acd_01` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `acd_02`
--

LOCK TABLES `acd_02` WRITE;
/*!40000 ALTER TABLE `acd_02` DISABLE KEYS */;
/*!40000 ALTER TABLE `acd_02` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `acd_03`
--

LOCK TABLES `acd_03` WRITE;
/*!40000 ALTER TABLE `acd_03` DISABLE KEYS */;
/*!40000 ALTER TABLE `acd_03` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `acd_04`
--

LOCK TABLES `acd_04` WRITE;
/*!40000 ALTER TABLE `acd_04` DISABLE KEYS */;
/*!40000 ALTER TABLE `acd_04` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `acd_05`
--

LOCK TABLES `acd_05` WRITE;
/*!40000 ALTER TABLE `acd_05` DISABLE KEYS */;
/*!40000 ALTER TABLE `acd_05` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `acd_06`
--

LOCK TABLES `acd_06` WRITE;
/*!40000 ALTER TABLE `acd_06` DISABLE KEYS */;
/*!40000 ALTER TABLE `acd_06` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `acd_07`
--

LOCK TABLES `acd_07` WRITE;
/*!40000 ALTER TABLE `acd_07` DISABLE KEYS */;
/*!40000 ALTER TABLE `acd_07` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `acd_08`
--

LOCK TABLES `acd_08` WRITE;
/*!40000 ALTER TABLE `acd_08` DISABLE KEYS */;
/*!40000 ALTER TABLE `acd_08` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `acd_09`
--

LOCK TABLES `acd_09` WRITE;
/*!40000 ALTER TABLE `acd_09` DISABLE KEYS */;
/*!40000 ALTER TABLE `acd_09` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `acd_10`
--

LOCK TABLES `acd_10` WRITE;
/*!40000 ALTER TABLE `acd_10` DISABLE KEYS */;
/*!40000 ALTER TABLE `acd_10` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `acd_11`
--

LOCK TABLES `acd_11` WRITE;
/*!40000 ALTER TABLE `acd_11` DISABLE KEYS */;
/*!40000 ALTER TABLE `acd_11` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `acd_12`
--

LOCK TABLES `acd_12` WRITE;
/*!40000 ALTER TABLE `acd_12` DISABLE KEYS */;
/*!40000 ALTER TABLE `acd_12` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `fs_01`
--

LOCK TABLES `fs_01` WRITE;
/*!40000 ALTER TABLE `fs_01` DISABLE KEYS */;
/*!40000 ALTER TABLE `fs_01` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `fs_02`
--

LOCK TABLES `fs_02` WRITE;
/*!40000 ALTER TABLE `fs_02` DISABLE KEYS */;
/*!40000 ALTER TABLE `fs_02` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `fs_03`
--

LOCK TABLES `fs_03` WRITE;
/*!40000 ALTER TABLE `fs_03` DISABLE KEYS */;
/*!40000 ALTER TABLE `fs_03` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `fs_04`
--

LOCK TABLES `fs_04` WRITE;
/*!40000 ALTER TABLE `fs_04` DISABLE KEYS */;
/*!40000 ALTER TABLE `fs_04` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `fs_05`
--

LOCK TABLES `fs_05` WRITE;
/*!40000 ALTER TABLE `fs_05` DISABLE KEYS */;
/*!40000 ALTER TABLE `fs_05` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `fs_06`
--

LOCK TABLES `fs_06` WRITE;
/*!40000 ALTER TABLE `fs_06` DISABLE KEYS */;
/*!40000 ALTER TABLE `fs_06` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `fs_07`
--

LOCK TABLES `fs_07` WRITE;
/*!40000 ALTER TABLE `fs_07` DISABLE KEYS */;
/*!40000 ALTER TABLE `fs_07` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `fs_08`
--

LOCK TABLES `fs_08` WRITE;
/*!40000 ALTER TABLE `fs_08` DISABLE KEYS */;
/*!40000 ALTER TABLE `fs_08` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `fs_09`
--

LOCK TABLES `fs_09` WRITE;
/*!40000 ALTER TABLE `fs_09` DISABLE KEYS */;
/*!40000 ALTER TABLE `fs_09` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `fs_10`
--

LOCK TABLES `fs_10` WRITE;
/*!40000 ALTER TABLE `fs_10` DISABLE KEYS */;
/*!40000 ALTER TABLE `fs_10` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `fs_11`
--

LOCK TABLES `fs_11` WRITE;
/*!40000 ALTER TABLE `fs_11` DISABLE KEYS */;
/*!40000 ALTER TABLE `fs_11` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `fs_12`
--

LOCK TABLES `fs_12` WRITE;
/*!40000 ALTER TABLE `fs_12` DISABLE KEYS */;
/*!40000 ALTER TABLE `fs_12` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `ivr_01`
--

LOCK TABLES `ivr_01` WRITE;
/*!40000 ALTER TABLE `ivr_01` DISABLE KEYS */;
/*!40000 ALTER TABLE `ivr_01` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `ivr_02`
--

LOCK TABLES `ivr_02` WRITE;
/*!40000 ALTER TABLE `ivr_02` DISABLE KEYS */;
/*!40000 ALTER TABLE `ivr_02` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `ivr_03`
--

LOCK TABLES `ivr_03` WRITE;
/*!40000 ALTER TABLE `ivr_03` DISABLE KEYS */;
/*!40000 ALTER TABLE `ivr_03` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `ivr_04`
--

LOCK TABLES `ivr_04` WRITE;
/*!40000 ALTER TABLE `ivr_04` DISABLE KEYS */;
/*!40000 ALTER TABLE `ivr_04` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `ivr_05`
--

LOCK TABLES `ivr_05` WRITE;
/*!40000 ALTER TABLE `ivr_05` DISABLE KEYS */;
/*!40000 ALTER TABLE `ivr_05` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `ivr_06`
--

LOCK TABLES `ivr_06` WRITE;
/*!40000 ALTER TABLE `ivr_06` DISABLE KEYS */;
/*!40000 ALTER TABLE `ivr_06` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `ivr_07`
--

LOCK TABLES `ivr_07` WRITE;
/*!40000 ALTER TABLE `ivr_07` DISABLE KEYS */;
/*!40000 ALTER TABLE `ivr_07` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `ivr_08`
--

LOCK TABLES `ivr_08` WRITE;
/*!40000 ALTER TABLE `ivr_08` DISABLE KEYS */;
/*!40000 ALTER TABLE `ivr_08` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `ivr_09`
--

LOCK TABLES `ivr_09` WRITE;
/*!40000 ALTER TABLE `ivr_09` DISABLE KEYS */;
/*!40000 ALTER TABLE `ivr_09` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `ivr_10`
--

LOCK TABLES `ivr_10` WRITE;
/*!40000 ALTER TABLE `ivr_10` DISABLE KEYS */;
/*!40000 ALTER TABLE `ivr_10` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `ivr_11`
--

LOCK TABLES `ivr_11` WRITE;
/*!40000 ALTER TABLE `ivr_11` DISABLE KEYS */;
/*!40000 ALTER TABLE `ivr_11` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `ivr_12`
--

LOCK TABLES `ivr_12` WRITE;
/*!40000 ALTER TABLE `ivr_12` DISABLE KEYS */;
/*!40000 ALTER TABLE `ivr_12` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Current Database: `osips_db`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `osips_db` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `osips_db`;

--
-- Data for table `acc`
--

LOCK TABLES `acc` WRITE;
/*!40000 ALTER TABLE `acc` DISABLE KEYS */;
/*!40000 ALTER TABLE `acc` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `active_watchers`
--

LOCK TABLES `active_watchers` WRITE;
/*!40000 ALTER TABLE `active_watchers` DISABLE KEYS */;
/*!40000 ALTER TABLE `active_watchers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `address`
--

LOCK TABLES `address` WRITE;
/*!40000 ALTER TABLE `address` DISABLE KEYS */;
INSERT INTO `address` VALUES (1,10,'172.17.113.31',24,0,'ANY',NULL,'TO SHENZHEN TELECOM'),(2,10,'172.17.113.32',24,0,'ANY',NULL,'TO SHENZHEN TELECOM');
/*!40000 ALTER TABLE `address` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `aliases`
--

LOCK TABLES `aliases` WRITE;
/*!40000 ALTER TABLE `aliases` DISABLE KEYS */;
/*!40000 ALTER TABLE `aliases` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `carrierfailureroute`
--

LOCK TABLES `carrierfailureroute` WRITE;
/*!40000 ALTER TABLE `carrierfailureroute` DISABLE KEYS */;
/*!40000 ALTER TABLE `carrierfailureroute` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `carrierroute`
--

LOCK TABLES `carrierroute` WRITE;
/*!40000 ALTER TABLE `carrierroute` DISABLE KEYS */;
/*!40000 ALTER TABLE `carrierroute` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `cdrs`
--

LOCK TABLES `cdrs` WRITE;
/*!40000 ALTER TABLE `cdrs` DISABLE KEYS */;
/*!40000 ALTER TABLE `cdrs` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `cpl`
--

LOCK TABLES `cpl` WRITE;
/*!40000 ALTER TABLE `cpl` DISABLE KEYS */;
/*!40000 ALTER TABLE `cpl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `dbaliases`
--

LOCK TABLES `dbaliases` WRITE;
/*!40000 ALTER TABLE `dbaliases` DISABLE KEYS */;
/*!40000 ALTER TABLE `dbaliases` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `dialog`
--

LOCK TABLES `dialog` WRITE;
/*!40000 ALTER TABLE `dialog` DISABLE KEYS */;
/*!40000 ALTER TABLE `dialog` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `dialplan`
--

LOCK TABLES `dialplan` WRITE;
/*!40000 ALTER TABLE `dialplan` DISABLE KEYS */;
INSERT INTO `dialplan` VALUES (13,0,1,1,'^[0-9]{8}',0,'','','ChinaTeleCom'),(16,0,1,1,'100[0-9][0-9]',0,'','','ChinaTeleCom'),(17,0,1,1,'^/*',0,'','','usrloc');
/*!40000 ALTER TABLE `dialplan` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `dispatcher`
--

LOCK TABLES `dispatcher` WRITE;
/*!40000 ALTER TABLE `dispatcher` DISABLE KEYS */;
INSERT INTO `dispatcher` VALUES (4,1,'sip:10.36.159.19',0,1,'','yf-ccl16.yf01');
/*!40000 ALTER TABLE `dispatcher` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `domain`
--

LOCK TABLES `domain` WRITE;
/*!40000 ALTER TABLE `domain` DISABLE KEYS */;
/*!40000 ALTER TABLE `domain` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `domainpolicy`
--

LOCK TABLES `domainpolicy` WRITE;
/*!40000 ALTER TABLE `domainpolicy` DISABLE KEYS */;
/*!40000 ALTER TABLE `domainpolicy` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `dr_gateways`
--

LOCK TABLES `dr_gateways` WRITE;
/*!40000 ALTER TABLE `dr_gateways` DISABLE KEYS */;
INSERT INTO `dr_gateways` VALUES (1,2,'192.168.29.135',0,'','NULL',0,'Gateway USA'),(2,2,'192.168.29.134',0,NULL,NULL,0,'Gateway USA 2'),(3,1,'172.17.113.31',0,NULL,NULL,2,'China TeleCom'),(4,1,'172.17.113.32',0,NULL,NULL,2,'China TeleCom');
/*!40000 ALTER TABLE `dr_gateways` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `dr_groups`
--

LOCK TABLES `dr_groups` WRITE;
/*!40000 ALTER TABLE `dr_groups` DISABLE KEYS */;
INSERT INTO `dr_groups` VALUES (1,'.*','.*',0,'Everyone');
/*!40000 ALTER TABLE `dr_groups` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `dr_gw_lists`
--

LOCK TABLES `dr_gw_lists` WRITE;
/*!40000 ALTER TABLE `dr_gw_lists` DISABLE KEYS */;
INSERT INTO `dr_gw_lists` VALUES (1,'2,1','My Media Servers'),(2,'3','China TeleCom group');
/*!40000 ALTER TABLE `dr_gw_lists` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `dr_rules`
--

LOCK TABLES `dr_rules` WRITE;
/*!40000 ALTER TABLE `dr_rules` DISABLE KEYS */;
INSERT INTO `dr_rules` VALUES (1,'0','','',1,'0','#2',NULL,'Routes to ChinaTeleCom'),(2,'0','011','',0,'0','#1',NULL,'International Calls');
/*!40000 ALTER TABLE `dr_rules` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `globalblacklist`
--

LOCK TABLES `globalblacklist` WRITE;
/*!40000 ALTER TABLE `globalblacklist` DISABLE KEYS */;
/*!40000 ALTER TABLE `globalblacklist` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `grp`
--

LOCK TABLES `grp` WRITE;
/*!40000 ALTER TABLE `grp` DISABLE KEYS */;
/*!40000 ALTER TABLE `grp` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `gw`
--

LOCK TABLES `gw` WRITE;
/*!40000 ALTER TABLE `gw` DISABLE KEYS */;
/*!40000 ALTER TABLE `gw` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `imc_members`
--

LOCK TABLES `imc_members` WRITE;
/*!40000 ALTER TABLE `imc_members` DISABLE KEYS */;
/*!40000 ALTER TABLE `imc_members` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `imc_rooms`
--

LOCK TABLES `imc_rooms` WRITE;
/*!40000 ALTER TABLE `imc_rooms` DISABLE KEYS */;
/*!40000 ALTER TABLE `imc_rooms` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `lcr`
--

LOCK TABLES `lcr` WRITE;
/*!40000 ALTER TABLE `lcr` DISABLE KEYS */;
/*!40000 ALTER TABLE `lcr` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `load_balancer`
--

LOCK TABLES `load_balancer` WRITE;
/*!40000 ALTER TABLE `load_balancer` DISABLE KEYS */;
INSERT INTO `load_balancer` VALUES (2,2,'SIP:172.17.113.13:5080','transc=32000; pstn=32000',2,''),(3,2,'SIP:172.17.113.14:5080','transc=32000; pstn=32000',2,''),(4,2,'SIP:172.17.113.15:5080','transc=32000; pstn=32000',2,'');
/*!40000 ALTER TABLE `load_balancer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `location`
--

LOCK TABLES `location` WRITE;
/*!40000 ALTER TABLE `location` DISABLE KEYS */;
/*!40000 ALTER TABLE `location` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `missed_calls`
--

LOCK TABLES `missed_calls` WRITE;
/*!40000 ALTER TABLE `missed_calls` DISABLE KEYS */;
/*!40000 ALTER TABLE `missed_calls` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `nh_sockets`
--

LOCK TABLES `nh_sockets` WRITE;
/*!40000 ALTER TABLE `nh_sockets` DISABLE KEYS */;
/*!40000 ALTER TABLE `nh_sockets` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `pdt`
--

LOCK TABLES `pdt` WRITE;
/*!40000 ALTER TABLE `pdt` DISABLE KEYS */;
/*!40000 ALTER TABLE `pdt` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `presentity`
--

LOCK TABLES `presentity` WRITE;
/*!40000 ALTER TABLE `presentity` DISABLE KEYS */;
/*!40000 ALTER TABLE `presentity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `pua`
--

LOCK TABLES `pua` WRITE;
/*!40000 ALTER TABLE `pua` DISABLE KEYS */;
/*!40000 ALTER TABLE `pua` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `re_grp`
--

LOCK TABLES `re_grp` WRITE;
/*!40000 ALTER TABLE `re_grp` DISABLE KEYS */;
/*!40000 ALTER TABLE `re_grp` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `rls_presentity`
--

LOCK TABLES `rls_presentity` WRITE;
/*!40000 ALTER TABLE `rls_presentity` DISABLE KEYS */;
/*!40000 ALTER TABLE `rls_presentity` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `rls_watchers`
--

LOCK TABLES `rls_watchers` WRITE;
/*!40000 ALTER TABLE `rls_watchers` DISABLE KEYS */;
/*!40000 ALTER TABLE `rls_watchers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `route_tree`
--

LOCK TABLES `route_tree` WRITE;
/*!40000 ALTER TABLE `route_tree` DISABLE KEYS */;
/*!40000 ALTER TABLE `route_tree` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `silo`
--

LOCK TABLES `silo` WRITE;
/*!40000 ALTER TABLE `silo` DISABLE KEYS */;
/*!40000 ALTER TABLE `silo` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `sip_trace`
--

LOCK TABLES `sip_trace` WRITE;
/*!40000 ALTER TABLE `sip_trace` DISABLE KEYS */;
/*!40000 ALTER TABLE `sip_trace` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `speed_dial`
--

LOCK TABLES `speed_dial` WRITE;
/*!40000 ALTER TABLE `speed_dial` DISABLE KEYS */;
/*!40000 ALTER TABLE `speed_dial` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `subscriber`
--

LOCK TABLES `subscriber` WRITE;
/*!40000 ALTER TABLE `subscriber` DISABLE KEYS */;
/*!40000 ALTER TABLE `subscriber` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `uri`
--

LOCK TABLES `uri` WRITE;
/*!40000 ALTER TABLE `uri` DISABLE KEYS */;
/*!40000 ALTER TABLE `uri` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `userblacklist`
--

LOCK TABLES `userblacklist` WRITE;
/*!40000 ALTER TABLE `userblacklist` DISABLE KEYS */;
/*!40000 ALTER TABLE `userblacklist` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `usr_preferences`
--

LOCK TABLES `usr_preferences` WRITE;
/*!40000 ALTER TABLE `usr_preferences` DISABLE KEYS */;
/*!40000 ALTER TABLE `usr_preferences` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `version`
--

LOCK TABLES `version` WRITE;
/*!40000 ALTER TABLE `version` DISABLE KEYS */;
INSERT INTO `version` VALUES ('acc',6),('active_watchers',10),('address',5),('aliases',1005),('carrierfailureroute',2),('carrierroute',3),('cpl',2),('dbaliases',2),('dialog',4),('dialplan',2),('dispatcher',4),('domain',2),('domainpolicy',3),('dr_gateways',4),('dr_groups',2),('dr_gw_lists',1),('dr_rules',3),('globalblacklist',2),('grp',3),('gw',8),('imc_members',2),('imc_rooms',2),('lcr',3),('load_balancer',2),('location',1005),('missed_calls',4),('nh_sockets',0),('pdt',2),('presentity',5),('pua',8),('re_grp',2),('rls_presentity',1),('rls_watchers',2),('route_tree',2),('silo',6),('sip_trace',3),('speed_dial',3),('subscriber',7),('uri',2),('userblacklist',2),('usr_preferences',3),('watchers',4),('xcap',4);
/*!40000 ALTER TABLE `version` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `watchers`
--

LOCK TABLES `watchers` WRITE;
/*!40000 ALTER TABLE `watchers` DISABLE KEYS */;
/*!40000 ALTER TABLE `watchers` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Data for table `xcap`
--

LOCK TABLES `xcap` WRITE;
/*!40000 ALTER TABLE `xcap` DISABLE KEYS */;
/*!40000 ALTER TABLE `xcap` ENABLE KEYS */;
UNLOCK TABLES;