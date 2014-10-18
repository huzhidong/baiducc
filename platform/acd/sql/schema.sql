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
-- Table structure for table `agenttbl`
--

DROP TABLE IF EXISTS `agenttbl`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `agenttbl` (
  `Id` int(11) NOT NULL auto_increment,
  `AgentId` varchar(64) default NULL,
  `AgentPwd` varchar(64) default NULL,
  `Skills` varchar(64) default NULL,
  PRIMARY KEY  (`Id`),
  KEY `AgentId` (`AgentId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `restreasontbl`
--

DROP TABLE IF EXISTS `restreasontbl`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `restreasontbl` (
  `Id` int(11) NOT NULL auto_increment,
  `RestReason` varchar(255) default NULL,
  PRIMARY KEY  (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `skillidtbl`
--

DROP TABLE IF EXISTS `skillidtbl`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `skillidtbl` (
  `Id` int(11) NOT NULL auto_increment,
  `SkillName` varchar(255) default NULL,
  PRIMARY KEY  (`Id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `tb_opt_log`
--

DROP TABLE IF EXISTS `tb_opt_log`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `tb_opt_log` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `add_time` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP COMMENT '操作时间',
  `opt_type` varchar(200) NOT NULL COMMENT '操作类型',
  `opt_data` varchar(2000) NOT NULL COMMENT '操作详情',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COMMENT='操作日志表';
SET character_set_client = @saved_cs_client;

--
-- Current Database: `ccclouddb`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `ccclouddb` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `ccclouddb`;

--
-- Table structure for table `acd_01`
--

DROP TABLE IF EXISTS `acd_01`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acd_01` (
  `sessionid` varchar(30) default NULL,
  `callid` varchar(30) default NULL,
  `agentid` varchar(30) default NULL,
  `agentdn` varchar(30) default NULL,
  `skill` varchar(255) default NULL,
  `caller` varchar(30) default NULL,
  `callee` varchar(30) default NULL,
  `waitbegin` datetime default NULL,
  `waitend` datetime default NULL,
  `ackbegin` datetime default NULL,
  `ackend` datetime default NULL,
  `callbegin` datetime default NULL,
  `callend` datetime default NULL,
  `calltype` varchar(30) default NULL,
  `calldirect` varchar(30) default NULL,
  `release_cause` varchar(30) default NULL,
  `record_filename` varchar(255) default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `callid` (`callid`),
  KEY `agentid` (`agentid`),
  KEY `agentdn` (`agentdn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `acd_02`
--

DROP TABLE IF EXISTS `acd_02`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acd_02` (
  `sessionid` varchar(30) default NULL,
  `callid` varchar(30) default NULL,
  `agentid` varchar(30) default NULL,
  `agentdn` varchar(30) default NULL,
  `skill` varchar(255) default NULL,
  `caller` varchar(30) default NULL,
  `callee` varchar(30) default NULL,
  `waitbegin` datetime default NULL,
  `waitend` datetime default NULL,
  `ackbegin` datetime default NULL,
  `ackend` datetime default NULL,
  `callbegin` datetime default NULL,
  `callend` datetime default NULL,
  `calltype` varchar(30) default NULL,
  `calldirect` varchar(30) default NULL,
  `release_cause` varchar(30) default NULL,
  `record_filename` varchar(255) default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `callid` (`callid`),
  KEY `agentid` (`agentid`),
  KEY `agentdn` (`agentdn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `acd_03`
--

DROP TABLE IF EXISTS `acd_03`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acd_03` (
  `sessionid` varchar(30) default NULL,
  `callid` varchar(30) default NULL,
  `agentid` varchar(30) default NULL,
  `agentdn` varchar(30) default NULL,
  `skill` varchar(255) default NULL,
  `caller` varchar(30) default NULL,
  `callee` varchar(30) default NULL,
  `waitbegin` datetime default NULL,
  `waitend` datetime default NULL,
  `ackbegin` datetime default NULL,
  `ackend` datetime default NULL,
  `callbegin` datetime default NULL,
  `callend` datetime default NULL,
  `calltype` varchar(30) default NULL,
  `calldirect` varchar(30) default NULL,
  `release_cause` varchar(30) default NULL,
  `record_filename` varchar(255) default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `callid` (`callid`),
  KEY `agentid` (`agentid`),
  KEY `agentdn` (`agentdn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `acd_04`
--

DROP TABLE IF EXISTS `acd_04`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acd_04` (
  `sessionid` varchar(30) default NULL,
  `callid` varchar(30) default NULL,
  `agentid` varchar(30) default NULL,
  `agentdn` varchar(30) default NULL,
  `skill` varchar(255) default NULL,
  `caller` varchar(30) default NULL,
  `callee` varchar(30) default NULL,
  `waitbegin` datetime default NULL,
  `waitend` datetime default NULL,
  `ackbegin` datetime default NULL,
  `ackend` datetime default NULL,
  `callbegin` datetime default NULL,
  `callend` datetime default NULL,
  `calltype` varchar(30) default NULL,
  `calldirect` varchar(30) default NULL,
  `release_cause` varchar(30) default NULL,
  `record_filename` varchar(255) default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `callid` (`callid`),
  KEY `agentid` (`agentid`),
  KEY `agentdn` (`agentdn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `acd_05`
--

DROP TABLE IF EXISTS `acd_05`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acd_05` (
  `sessionid` varchar(30) default NULL,
  `callid` varchar(30) default NULL,
  `agentid` varchar(30) default NULL,
  `agentdn` varchar(30) default NULL,
  `skill` varchar(255) default NULL,
  `caller` varchar(30) default NULL,
  `callee` varchar(30) default NULL,
  `waitbegin` datetime default NULL,
  `waitend` datetime default NULL,
  `ackbegin` datetime default NULL,
  `ackend` datetime default NULL,
  `callbegin` datetime default NULL,
  `callend` datetime default NULL,
  `calltype` varchar(30) default NULL,
  `calldirect` varchar(30) default NULL,
  `release_cause` varchar(30) default NULL,
  `record_filename` varchar(255) default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `callid` (`callid`),
  KEY `agentid` (`agentid`),
  KEY `agentdn` (`agentdn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `acd_06`
--

DROP TABLE IF EXISTS `acd_06`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acd_06` (
  `sessionid` varchar(30) default NULL,
  `callid` varchar(30) default NULL,
  `agentid` varchar(30) default NULL,
  `agentdn` varchar(30) default NULL,
  `skill` varchar(255) default NULL,
  `caller` varchar(30) default NULL,
  `callee` varchar(30) default NULL,
  `waitbegin` datetime default NULL,
  `waitend` datetime default NULL,
  `ackbegin` datetime default NULL,
  `ackend` datetime default NULL,
  `callbegin` datetime default NULL,
  `callend` datetime default NULL,
  `calltype` varchar(30) default NULL,
  `calldirect` varchar(30) default NULL,
  `release_cause` varchar(30) default NULL,
  `record_filename` varchar(255) default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `callid` (`callid`),
  KEY `agentid` (`agentid`),
  KEY `agentdn` (`agentdn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `acd_07`
--

DROP TABLE IF EXISTS `acd_07`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acd_07` (
  `sessionid` varchar(30) default NULL,
  `callid` varchar(30) default NULL,
  `agentid` varchar(30) default NULL,
  `agentdn` varchar(30) default NULL,
  `skill` varchar(255) default NULL,
  `caller` varchar(30) default NULL,
  `callee` varchar(30) default NULL,
  `waitbegin` datetime default NULL,
  `waitend` datetime default NULL,
  `ackbegin` datetime default NULL,
  `ackend` datetime default NULL,
  `callbegin` datetime default NULL,
  `callend` datetime default NULL,
  `calltype` varchar(30) default NULL,
  `calldirect` varchar(30) default NULL,
  `release_cause` varchar(30) default NULL,
  `record_filename` varchar(255) default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `callid` (`callid`),
  KEY `agentid` (`agentid`),
  KEY `agentdn` (`agentdn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `acd_08`
--

DROP TABLE IF EXISTS `acd_08`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acd_08` (
  `sessionid` varchar(30) default NULL,
  `callid` varchar(30) default NULL,
  `agentid` varchar(30) default NULL,
  `agentdn` varchar(30) default NULL,
  `skill` varchar(255) default NULL,
  `caller` varchar(30) default NULL,
  `callee` varchar(30) default NULL,
  `waitbegin` datetime default NULL,
  `waitend` datetime default NULL,
  `ackbegin` datetime default NULL,
  `ackend` datetime default NULL,
  `callbegin` datetime default NULL,
  `callend` datetime default NULL,
  `calltype` varchar(30) default NULL,
  `calldirect` varchar(30) default NULL,
  `release_cause` varchar(30) default NULL,
  `record_filename` varchar(255) default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `callid` (`callid`),
  KEY `agentid` (`agentid`),
  KEY `agentdn` (`agentdn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `acd_09`
--

DROP TABLE IF EXISTS `acd_09`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acd_09` (
  `sessionid` varchar(30) default NULL,
  `callid` varchar(30) default NULL,
  `agentid` varchar(30) default NULL,
  `agentdn` varchar(30) default NULL,
  `skill` varchar(255) default NULL,
  `caller` varchar(30) default NULL,
  `callee` varchar(30) default NULL,
  `waitbegin` datetime default NULL,
  `waitend` datetime default NULL,
  `ackbegin` datetime default NULL,
  `ackend` datetime default NULL,
  `callbegin` datetime default NULL,
  `callend` datetime default NULL,
  `calltype` varchar(30) default NULL,
  `calldirect` varchar(30) default NULL,
  `release_cause` varchar(30) default NULL,
  `record_filename` varchar(255) default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `callid` (`callid`),
  KEY `agentid` (`agentid`),
  KEY `agentdn` (`agentdn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `acd_10`
--

DROP TABLE IF EXISTS `acd_10`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acd_10` (
  `sessionid` varchar(30) default NULL,
  `callid` varchar(30) default NULL,
  `agentid` varchar(30) default NULL,
  `agentdn` varchar(30) default NULL,
  `skill` varchar(255) default NULL,
  `caller` varchar(30) default NULL,
  `callee` varchar(30) default NULL,
  `waitbegin` datetime default NULL,
  `waitend` datetime default NULL,
  `ackbegin` datetime default NULL,
  `ackend` datetime default NULL,
  `callbegin` datetime default NULL,
  `callend` datetime default NULL,
  `calltype` varchar(30) default NULL,
  `calldirect` varchar(30) default NULL,
  `release_cause` varchar(30) default NULL,
  `record_filename` varchar(255) default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `callid` (`callid`),
  KEY `agentid` (`agentid`),
  KEY `agentdn` (`agentdn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `acd_11`
--

DROP TABLE IF EXISTS `acd_11`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acd_11` (
  `sessionid` varchar(30) default NULL,
  `callid` varchar(30) default NULL,
  `agentid` varchar(30) default NULL,
  `agentdn` varchar(30) default NULL,
  `skill` varchar(255) default NULL,
  `caller` varchar(30) default NULL,
  `callee` varchar(30) default NULL,
  `waitbegin` datetime default NULL,
  `waitend` datetime default NULL,
  `ackbegin` datetime default NULL,
  `ackend` datetime default NULL,
  `callbegin` datetime default NULL,
  `callend` datetime default NULL,
  `calltype` varchar(30) default NULL,
  `calldirect` varchar(30) default NULL,
  `release_cause` varchar(30) default NULL,
  `record_filename` varchar(255) default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `callid` (`callid`),
  KEY `agentid` (`agentid`),
  KEY `agentdn` (`agentdn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `acd_12`
--

DROP TABLE IF EXISTS `acd_12`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acd_12` (
  `sessionid` varchar(30) default NULL,
  `callid` varchar(30) default NULL,
  `agentid` varchar(30) default NULL,
  `agentdn` varchar(30) default NULL,
  `skill` varchar(255) default NULL,
  `caller` varchar(30) default NULL,
  `callee` varchar(30) default NULL,
  `waitbegin` datetime default NULL,
  `waitend` datetime default NULL,
  `ackbegin` datetime default NULL,
  `ackend` datetime default NULL,
  `callbegin` datetime default NULL,
  `callend` datetime default NULL,
  `calltype` varchar(30) default NULL,
  `calldirect` varchar(30) default NULL,
  `release_cause` varchar(30) default NULL,
  `record_filename` varchar(255) default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `callid` (`callid`),
  KEY `agentid` (`agentid`),
  KEY `agentdn` (`agentdn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `fs_01`
--

DROP TABLE IF EXISTS `fs_01`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `fs_01` (
  `caller_id_name` varchar(30) default NULL,
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `context` varchar(20) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `buuid_1` bigint(64) unsigned default NULL,
  `buuid_2` bigint(64) unsigned default NULL,
  `accountcode` varchar(10) default NULL,
  `record` varchar(512) default NULL,
  `fs_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `fs_02`
--

DROP TABLE IF EXISTS `fs_02`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `fs_02` (
  `caller_id_name` varchar(30) default NULL,
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `context` varchar(20) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `buuid_1` bigint(64) unsigned default NULL,
  `buuid_2` bigint(64) unsigned default NULL,
  `accountcode` varchar(10) default NULL,
  `record` varchar(512) default NULL,
  `fs_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `fs_03`
--

DROP TABLE IF EXISTS `fs_03`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `fs_03` (
  `caller_id_name` varchar(30) default NULL,
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `context` varchar(20) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `buuid_1` bigint(64) unsigned default NULL,
  `buuid_2` bigint(64) unsigned default NULL,
  `accountcode` varchar(10) default NULL,
  `record` varchar(512) default NULL,
  `fs_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `fs_04`
--

DROP TABLE IF EXISTS `fs_04`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `fs_04` (
  `caller_id_name` varchar(30) default NULL,
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `context` varchar(20) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `buuid_1` bigint(64) unsigned default NULL,
  `buuid_2` bigint(64) unsigned default NULL,
  `accountcode` varchar(10) default NULL,
  `record` varchar(512) default NULL,
  `fs_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `fs_05`
--

DROP TABLE IF EXISTS `fs_05`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `fs_05` (
  `caller_id_name` varchar(30) default NULL,
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `context` varchar(20) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `buuid_1` bigint(64) unsigned default NULL,
  `buuid_2` bigint(64) unsigned default NULL,
  `accountcode` varchar(10) default NULL,
  `record` varchar(512) default NULL,
  `fs_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `fs_06`
--

DROP TABLE IF EXISTS `fs_06`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `fs_06` (
  `caller_id_name` varchar(30) default NULL,
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `context` varchar(20) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `buuid_1` bigint(64) unsigned default NULL,
  `buuid_2` bigint(64) unsigned default NULL,
  `accountcode` varchar(10) default NULL,
  `record` varchar(512) default NULL,
  `fs_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `fs_07`
--

DROP TABLE IF EXISTS `fs_07`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `fs_07` (
  `caller_id_name` varchar(30) default NULL,
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `context` varchar(20) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `buuid_1` bigint(64) unsigned default NULL,
  `buuid_2` bigint(64) unsigned default NULL,
  `accountcode` varchar(10) default NULL,
  `record` varchar(512) default NULL,
  `fs_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `fs_08`
--

DROP TABLE IF EXISTS `fs_08`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `fs_08` (
  `caller_id_name` varchar(30) default NULL,
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `context` varchar(20) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `buuid_1` bigint(64) unsigned default NULL,
  `buuid_2` bigint(64) unsigned default NULL,
  `accountcode` varchar(10) default NULL,
  `record` varchar(512) default NULL,
  `fs_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `fs_09`
--

DROP TABLE IF EXISTS `fs_09`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `fs_09` (
  `caller_id_name` varchar(30) default NULL,
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `context` varchar(20) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `buuid_1` bigint(64) unsigned default NULL,
  `buuid_2` bigint(64) unsigned default NULL,
  `accountcode` varchar(10) default NULL,
  `record` varchar(512) default NULL,
  `fs_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `fs_10`
--

DROP TABLE IF EXISTS `fs_10`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `fs_10` (
  `caller_id_name` varchar(30) default NULL,
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `context` varchar(20) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `buuid_1` bigint(64) unsigned default NULL,
  `buuid_2` bigint(64) unsigned default NULL,
  `accountcode` varchar(10) default NULL,
  `record` varchar(512) default NULL,
  `fs_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `fs_11`
--

DROP TABLE IF EXISTS `fs_11`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `fs_11` (
  `caller_id_name` varchar(30) default NULL,
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `context` varchar(20) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `buuid_1` bigint(64) unsigned default NULL,
  `buuid_2` bigint(64) unsigned default NULL,
  `accountcode` varchar(10) default NULL,
  `record` varchar(512) default NULL,
  `fs_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `fs_12`
--

DROP TABLE IF EXISTS `fs_12`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `fs_12` (
  `caller_id_name` varchar(30) default NULL,
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `context` varchar(20) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `buuid_1` bigint(64) unsigned default NULL,
  `buuid_2` bigint(64) unsigned default NULL,
  `accountcode` varchar(10) default NULL,
  `record` varchar(512) default NULL,
  `fs_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ivr_01`
--

DROP TABLE IF EXISTS `ivr_01`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ivr_01` (
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ivr_02`
--

DROP TABLE IF EXISTS `ivr_02`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ivr_02` (
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ivr_03`
--

DROP TABLE IF EXISTS `ivr_03`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ivr_03` (
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ivr_04`
--

DROP TABLE IF EXISTS `ivr_04`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ivr_04` (
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ivr_05`
--

DROP TABLE IF EXISTS `ivr_05`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ivr_05` (
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ivr_06`
--

DROP TABLE IF EXISTS `ivr_06`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ivr_06` (
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ivr_07`
--

DROP TABLE IF EXISTS `ivr_07`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ivr_07` (
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ivr_08`
--

DROP TABLE IF EXISTS `ivr_08`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ivr_08` (
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ivr_09`
--

DROP TABLE IF EXISTS `ivr_09`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ivr_09` (
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ivr_10`
--

DROP TABLE IF EXISTS `ivr_10`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ivr_10` (
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ivr_11`
--

DROP TABLE IF EXISTS `ivr_11`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ivr_11` (
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `ivr_12`
--

DROP TABLE IF EXISTS `ivr_12`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `ivr_12` (
  `caller_id_number` varchar(30) default NULL,
  `destination_number` varchar(30) default NULL,
  `start_stamp` datetime default NULL,
  `answer_stamp` datetime default NULL,
  `end_stamp` datetime default NULL,
  `duration` int(11) default NULL,
  `billsec` int(11) default NULL,
  `hangup_cause` varchar(50) default NULL,
  `uuid_1` bigint(64) unsigned default NULL,
  `uuid_2` bigint(64) unsigned default NULL,
  `src_IP` varchar(32) default NULL,
  KEY `uuid_1` (`uuid_1`,`uuid_2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Current Database: `osips_db`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `osips_db` /*!40100 DEFAULT CHARACTER SET utf8 */;

USE `osips_db`;

--
-- Table structure for table `acc`
--

DROP TABLE IF EXISTS `acc`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `acc` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `method` char(16) NOT NULL default '',
  `from_tag` char(64) NOT NULL default '',
  `to_tag` char(64) NOT NULL default '',
  `callid` char(64) NOT NULL default '',
  `sip_code` char(3) NOT NULL default '',
  `sip_reason` char(32) NOT NULL default '',
  `time` datetime NOT NULL default '0000-00-00 00:00:00',
  `cdr_id` bigint(11) NOT NULL default '0',
  `duration` int(11) unsigned NOT NULL default '0',
  `setuptime` int(11) unsigned NOT NULL default '0',
  `created` datetime NOT NULL default '0000-00-00 00:00:00',
  `caller_id` char(64) NOT NULL default '',
  `callee_id` char(64) NOT NULL default '',
  PRIMARY KEY  (`id`),
  KEY `callid_idx` (`callid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `active_watchers`
--

DROP TABLE IF EXISTS `active_watchers`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `active_watchers` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `presentity_uri` varchar(128) NOT NULL default '',
  `watcher_username` varchar(64) NOT NULL default '',
  `watcher_domain` varchar(64) NOT NULL default '',
  `to_user` varchar(64) NOT NULL default '',
  `to_domain` varchar(64) NOT NULL default '',
  `event` varchar(64) NOT NULL default 'presence',
  `event_id` varchar(64) default NULL,
  `to_tag` varchar(64) NOT NULL default '',
  `from_tag` varchar(64) NOT NULL default '',
  `callid` varchar(64) NOT NULL default '',
  `local_cseq` int(11) NOT NULL default '0',
  `remote_cseq` int(11) NOT NULL default '0',
  `contact` varchar(128) NOT NULL default '',
  `record_route` text,
  `expires` int(11) NOT NULL default '0',
  `status` int(11) NOT NULL default '2',
  `reason` varchar(64) NOT NULL default '',
  `version` int(11) NOT NULL default '0',
  `socket_info` varchar(64) NOT NULL default '',
  `local_contact` varchar(128) NOT NULL default '',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `active_watchers_idx` (`presentity_uri`,`callid`,`to_tag`,`from_tag`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `address`
--

DROP TABLE IF EXISTS `address`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `address` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `grp` smallint(5) unsigned NOT NULL default '0',
  `ip` char(50) NOT NULL default '',
  `mask` tinyint(4) NOT NULL default '32',
  `port` smallint(5) unsigned NOT NULL default '0',
  `proto` char(4) NOT NULL default 'any',
  `pattern` char(64) default NULL,
  `context_info` char(32) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `aliases`
--

DROP TABLE IF EXISTS `aliases`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `aliases` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` char(64) NOT NULL default '',
  `domain` char(64) default NULL,
  `contact` char(255) NOT NULL default '',
  `received` char(128) default NULL,
  `path` char(128) default NULL,
  `expires` datetime NOT NULL default '2020-05-28 21:32:15',
  `q` float(10,2) NOT NULL default '1.00',
  `callid` char(255) NOT NULL default 'Default-Call-ID',
  `cseq` int(11) NOT NULL default '13',
  `last_modified` datetime NOT NULL default '1900-01-01 00:00:01',
  `flags` int(11) NOT NULL default '0',
  `cflags` int(11) NOT NULL default '0',
  `user_agent` char(255) NOT NULL default '',
  `socket` char(64) default NULL,
  `methods` int(11) default NULL,
  PRIMARY KEY  (`id`),
  KEY `alias_idx` (`username`,`domain`,`contact`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `carrierfailureroute`
--

DROP TABLE IF EXISTS `carrierfailureroute`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `carrierfailureroute` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `carrier` int(10) unsigned NOT NULL default '0',
  `domain` char(64) NOT NULL default '',
  `scan_prefix` char(64) NOT NULL default '',
  `host_name` char(128) NOT NULL default '',
  `reply_code` char(3) NOT NULL default '',
  `flags` int(11) unsigned NOT NULL default '0',
  `mask` int(11) unsigned NOT NULL default '0',
  `next_domain` char(64) NOT NULL default '',
  `description` char(255) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `carrierroute`
--

DROP TABLE IF EXISTS `carrierroute`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `carrierroute` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `carrier` int(10) unsigned NOT NULL default '0',
  `domain` char(64) NOT NULL default '',
  `scan_prefix` char(64) NOT NULL default '',
  `flags` int(11) unsigned NOT NULL default '0',
  `mask` int(11) unsigned NOT NULL default '0',
  `prob` float NOT NULL default '0',
  `strip` int(11) unsigned NOT NULL default '0',
  `rewrite_host` char(128) NOT NULL default '',
  `rewrite_prefix` char(64) NOT NULL default '',
  `rewrite_suffix` char(64) NOT NULL default '',
  `description` char(255) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `cdrs`
--

DROP TABLE IF EXISTS `cdrs`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `cdrs` (
  `cdr_id` bigint(20) NOT NULL auto_increment,
  `call_start_time` datetime NOT NULL default '0000-00-00 00:00:00',
  `duration` int(10) unsigned NOT NULL default '0',
  `sip_call_id` varchar(128) NOT NULL default '',
  `sip_from_tag` varchar(128) NOT NULL default '',
  `sip_to_tag` varchar(128) NOT NULL default '',
  `created` datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`cdr_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `cpl`
--

DROP TABLE IF EXISTS `cpl`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `cpl` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` varchar(64) NOT NULL default '',
  `domain` varchar(64) NOT NULL default '',
  `cpl_xml` text,
  `cpl_bin` text,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `account_idx` (`username`,`domain`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `dbaliases`
--

DROP TABLE IF EXISTS `dbaliases`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `dbaliases` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `alias_username` char(64) NOT NULL default '',
  `alias_domain` char(64) NOT NULL default '',
  `username` char(64) NOT NULL default '',
  `domain` char(64) NOT NULL default '',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `alias_idx` (`alias_username`,`alias_domain`),
  KEY `target_idx` (`username`,`domain`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `dialog`
--

DROP TABLE IF EXISTS `dialog`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `dialog` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `hash_entry` int(10) unsigned NOT NULL default '0',
  `hash_id` int(10) unsigned NOT NULL default '0',
  `callid` varchar(255) NOT NULL default '',
  `from_uri` varchar(128) NOT NULL default '',
  `from_tag` varchar(64) NOT NULL default '',
  `to_uri` varchar(128) NOT NULL default '',
  `to_tag` varchar(64) NOT NULL default '',
  `caller_cseq` varchar(11) NOT NULL default '',
  `callee_cseq` varchar(11) NOT NULL default '',
  `caller_route_set` text,
  `callee_route_set` text,
  `caller_contact` varchar(128) NOT NULL default '',
  `callee_contact` varchar(128) NOT NULL default '',
  `caller_sock` varchar(64) NOT NULL default '',
  `callee_sock` varchar(64) NOT NULL default '',
  `state` int(10) unsigned NOT NULL default '0',
  `start_time` int(10) unsigned NOT NULL default '0',
  `timeout` int(10) unsigned NOT NULL default '0',
  `vars` text,
  `profiles` text,
  `script_flags` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `hash_idx` (`hash_entry`,`hash_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `dialplan`
--

DROP TABLE IF EXISTS `dialplan`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `dialplan` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `dpid` int(11) NOT NULL default '0',
  `pr` int(11) NOT NULL default '0',
  `match_op` int(11) NOT NULL default '0',
  `match_exp` char(64) NOT NULL default '',
  `match_len` int(11) NOT NULL default '0',
  `subst_exp` char(64) NOT NULL default '',
  `repl_exp` char(32) NOT NULL default '',
  `attrs` char(32) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=18 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `dispatcher`
--

DROP TABLE IF EXISTS `dispatcher`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `dispatcher` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `setid` int(11) NOT NULL default '0',
  `destination` char(192) NOT NULL default '',
  `flags` int(11) NOT NULL default '0',
  `weight` int(11) NOT NULL default '1',
  `attrs` char(128) NOT NULL default '',
  `description` char(64) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `domain`
--

DROP TABLE IF EXISTS `domain`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `domain` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `domain` char(64) NOT NULL default '',
  `last_modified` datetime NOT NULL default '1900-01-01 00:00:01',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `domain_idx` (`domain`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `domainpolicy`
--

DROP TABLE IF EXISTS `domainpolicy`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `domainpolicy` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `rule` char(255) NOT NULL default '',
  `type` char(255) NOT NULL default '',
  `att` char(255) default NULL,
  `val` char(128) default NULL,
  `description` char(255) NOT NULL default '',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `rav_idx` (`rule`,`att`,`val`),
  KEY `rule_idx` (`rule`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `dr_gateways`
--

DROP TABLE IF EXISTS `dr_gateways`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `dr_gateways` (
  `gwid` int(10) unsigned NOT NULL auto_increment,
  `type` int(11) unsigned NOT NULL default '0',
  `address` char(128) NOT NULL default '',
  `strip` int(11) unsigned NOT NULL default '0',
  `pri_prefix` char(16) default NULL,
  `attrs` char(255) default NULL,
  `probe_mode` int(11) unsigned NOT NULL default '0',
  `description` char(128) NOT NULL default '',
  PRIMARY KEY  (`gwid`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `dr_groups`
--

DROP TABLE IF EXISTS `dr_groups`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `dr_groups` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` char(64) NOT NULL default '',
  `domain` char(128) NOT NULL default '',
  `groupid` int(11) unsigned NOT NULL default '0',
  `description` char(128) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `dr_gw_lists`
--

DROP TABLE IF EXISTS `dr_gw_lists`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `dr_gw_lists` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `gwlist` char(255) NOT NULL default '',
  `description` char(128) NOT NULL default '',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `dr_rules`
--

DROP TABLE IF EXISTS `dr_rules`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `dr_rules` (
  `ruleid` int(10) unsigned NOT NULL auto_increment,
  `groupid` char(255) NOT NULL default '',
  `prefix` char(64) NOT NULL default '',
  `timerec` char(255) NOT NULL default '',
  `priority` int(11) NOT NULL default '0',
  `routeid` char(255) NOT NULL default '',
  `gwlist` char(255) NOT NULL default '',
  `attrs` char(255) default NULL,
  `description` char(128) NOT NULL default '',
  PRIMARY KEY  (`ruleid`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `globalblacklist`
--

DROP TABLE IF EXISTS `globalblacklist`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `globalblacklist` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `prefix` char(64) NOT NULL default '',
  `whitelist` tinyint(1) NOT NULL default '0',
  `description` char(255) default NULL,
  PRIMARY KEY  (`id`),
  KEY `globalblacklist_idx` (`prefix`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `grp`
--

DROP TABLE IF EXISTS `grp`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `grp` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` char(64) NOT NULL default '',
  `domain` char(64) NOT NULL default '',
  `grp` char(64) NOT NULL default '',
  `last_modified` datetime NOT NULL default '1900-01-01 00:00:01',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `account_group_idx` (`username`,`domain`,`grp`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `gw`
--

DROP TABLE IF EXISTS `gw`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `gw` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `gw_name` char(128) NOT NULL default '',
  `grp_id` int(10) unsigned NOT NULL default '0',
  `ip_addr` char(15) NOT NULL default '',
  `port` smallint(5) unsigned default NULL,
  `uri_scheme` tinyint(3) unsigned default NULL,
  `transport` tinyint(3) unsigned default NULL,
  `strip` tinyint(3) unsigned default NULL,
  `tag` char(16) default NULL,
  `flags` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `gw_name_idx` (`gw_name`),
  KEY `grp_id_idx` (`grp_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `imc_members`
--

DROP TABLE IF EXISTS `imc_members`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `imc_members` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` char(64) NOT NULL default '',
  `domain` char(64) NOT NULL default '',
  `room` char(64) NOT NULL default '',
  `flag` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `account_room_idx` (`username`,`domain`,`room`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `imc_rooms`
--

DROP TABLE IF EXISTS `imc_rooms`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `imc_rooms` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `name` char(64) NOT NULL default '',
  `domain` char(64) NOT NULL default '',
  `flag` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `name_domain_idx` (`name`,`domain`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `lcr`
--

DROP TABLE IF EXISTS `lcr`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `lcr` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `prefix` char(16) default NULL,
  `from_uri` char(64) default NULL,
  `grp_id` int(10) unsigned NOT NULL default '0',
  `priority` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `prefix_idx` (`prefix`),
  KEY `from_uri_idx` (`from_uri`),
  KEY `grp_id_idx` (`grp_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `load_balancer`
--

DROP TABLE IF EXISTS `load_balancer`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `load_balancer` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `group_id` int(11) unsigned NOT NULL default '0',
  `dst_uri` char(128) NOT NULL default '',
  `resources` char(255) NOT NULL default '',
  `probe_mode` int(11) unsigned NOT NULL default '0',
  `description` char(128) NOT NULL default '',
  PRIMARY KEY  (`id`),
  KEY `dsturi_idx` (`dst_uri`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `location`
--

DROP TABLE IF EXISTS `location`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `location` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` char(64) NOT NULL default '',
  `domain` char(64) default NULL,
  `contact` char(255) NOT NULL default '',
  `received` char(128) default NULL,
  `path` char(128) default NULL,
  `expires` datetime NOT NULL default '2020-05-28 21:32:15',
  `q` float(10,2) NOT NULL default '1.00',
  `callid` char(255) NOT NULL default 'Default-Call-ID',
  `cseq` int(11) NOT NULL default '13',
  `last_modified` datetime NOT NULL default '1900-01-01 00:00:01',
  `flags` int(11) NOT NULL default '0',
  `cflags` int(11) NOT NULL default '0',
  `user_agent` char(255) NOT NULL default '',
  `socket` char(64) default NULL,
  `methods` int(11) default NULL,
  PRIMARY KEY  (`id`),
  KEY `account_contact_idx` (`username`,`domain`,`contact`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `missed_calls`
--

DROP TABLE IF EXISTS `missed_calls`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `missed_calls` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `method` char(16) NOT NULL default '',
  `from_tag` char(64) NOT NULL default '',
  `to_tag` char(64) NOT NULL default '',
  `callid` char(64) NOT NULL default '',
  `sip_code` char(3) NOT NULL default '',
  `sip_reason` char(32) NOT NULL default '',
  `time` datetime NOT NULL default '0000-00-00 00:00:00',
  PRIMARY KEY  (`id`),
  KEY `callid_idx` (`callid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `nh_sockets`
--

DROP TABLE IF EXISTS `nh_sockets`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `nh_sockets` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `rtpproxy_sock` text NOT NULL,
  `set_id` int(10) unsigned NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `pdt`
--

DROP TABLE IF EXISTS `pdt`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `pdt` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `sdomain` char(128) NOT NULL default '',
  `prefix` char(32) NOT NULL default '',
  `domain` char(128) NOT NULL default '',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `sdomain_prefix_idx` (`sdomain`,`prefix`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `presentity`
--

DROP TABLE IF EXISTS `presentity`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `presentity` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` varchar(64) NOT NULL default '',
  `domain` varchar(64) NOT NULL default '',
  `event` varchar(64) NOT NULL default '',
  `etag` varchar(64) NOT NULL default '',
  `expires` int(11) NOT NULL default '0',
  `received_time` int(11) NOT NULL default '0',
  `body` blob NOT NULL,
  `extra_hdrs` blob NOT NULL,
  `sender` varchar(128) NOT NULL default '',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `presentity_idx` (`username`,`domain`,`event`,`etag`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `pua`
--

DROP TABLE IF EXISTS `pua`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `pua` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `pres_uri` varchar(128) NOT NULL default '',
  `pres_id` varchar(255) NOT NULL default '',
  `event` int(11) NOT NULL default '0',
  `expires` int(11) NOT NULL default '0',
  `desired_expires` int(11) NOT NULL default '0',
  `flag` int(11) NOT NULL default '0',
  `etag` varchar(64) default NULL,
  `tuple_id` varchar(64) default NULL,
  `watcher_uri` varchar(128) default NULL,
  `to_uri` varchar(128) default NULL,
  `call_id` varchar(64) default NULL,
  `to_tag` varchar(64) default NULL,
  `from_tag` varchar(64) default NULL,
  `cseq` int(11) default NULL,
  `record_route` text,
  `contact` varchar(128) default NULL,
  `remote_contact` varchar(128) default NULL,
  `version` int(11) default NULL,
  `extra_headers` text,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `re_grp`
--

DROP TABLE IF EXISTS `re_grp`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `re_grp` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `reg_exp` char(128) NOT NULL default '',
  `group_id` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `group_idx` (`group_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `rls_presentity`
--

DROP TABLE IF EXISTS `rls_presentity`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `rls_presentity` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `rlsubs_did` varchar(255) NOT NULL default '',
  `resource_uri` varchar(128) NOT NULL default '',
  `content_type` varchar(255) NOT NULL default '',
  `presence_state` blob NOT NULL,
  `expires` int(11) NOT NULL default '0',
  `updated` int(11) NOT NULL default '0',
  `auth_state` int(11) NOT NULL default '0',
  `reason` varchar(64) NOT NULL default '',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `rls_presentity_idx` (`rlsubs_did`,`resource_uri`),
  KEY `updated_idx` (`updated`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `rls_watchers`
--

DROP TABLE IF EXISTS `rls_watchers`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `rls_watchers` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `presentity_uri` varchar(128) NOT NULL default '',
  `to_user` varchar(64) NOT NULL default '',
  `to_domain` varchar(64) NOT NULL default '',
  `watcher_username` varchar(64) NOT NULL default '',
  `watcher_domain` varchar(64) NOT NULL default '',
  `event` varchar(64) NOT NULL default 'presence',
  `event_id` varchar(64) default NULL,
  `to_tag` varchar(64) NOT NULL default '',
  `from_tag` varchar(64) NOT NULL default '',
  `callid` varchar(64) NOT NULL default '',
  `local_cseq` int(11) NOT NULL default '0',
  `remote_cseq` int(11) NOT NULL default '0',
  `contact` varchar(64) NOT NULL default '',
  `record_route` text,
  `expires` int(11) NOT NULL default '0',
  `status` int(11) NOT NULL default '2',
  `reason` varchar(64) NOT NULL default '',
  `version` int(11) NOT NULL default '0',
  `socket_info` varchar(64) NOT NULL default '',
  `local_contact` varchar(128) NOT NULL default '',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `rls_watcher_idx` (`presentity_uri`,`callid`,`to_tag`,`from_tag`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `route_tree`
--

DROP TABLE IF EXISTS `route_tree`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `route_tree` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `carrier` char(64) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `silo`
--

DROP TABLE IF EXISTS `silo`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `silo` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `src_addr` varchar(128) NOT NULL default '',
  `dst_addr` varchar(128) NOT NULL default '',
  `username` varchar(64) NOT NULL default '',
  `domain` varchar(64) NOT NULL default '',
  `inc_time` int(11) NOT NULL default '0',
  `exp_time` int(11) NOT NULL default '0',
  `snd_time` int(11) NOT NULL default '0',
  `ctype` varchar(32) NOT NULL default 'text/plain',
  `body` blob NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `account_idx` (`username`,`domain`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `sip_trace`
--

DROP TABLE IF EXISTS `sip_trace`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `sip_trace` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `time_stamp` datetime NOT NULL default '1900-01-01 00:00:01',
  `callid` varchar(255) NOT NULL default '',
  `traced_user` varchar(128) default NULL,
  `msg` text NOT NULL,
  `method` varchar(32) NOT NULL default '',
  `status` varchar(128) default NULL,
  `fromip` varchar(50) NOT NULL default '',
  `toip` varchar(50) NOT NULL default '',
  `fromtag` varchar(64) NOT NULL default '',
  `direction` varchar(4) NOT NULL default '',
  PRIMARY KEY  (`id`),
  KEY `traced_user_idx` (`traced_user`),
  KEY `date_idx` (`time_stamp`),
  KEY `fromip_idx` (`fromip`),
  KEY `callid_idx` (`callid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `speed_dial`
--

DROP TABLE IF EXISTS `speed_dial`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `speed_dial` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` char(64) NOT NULL default '',
  `domain` char(64) NOT NULL default '',
  `sd_username` char(64) NOT NULL default '',
  `sd_domain` char(64) NOT NULL default '',
  `new_uri` char(128) NOT NULL default '',
  `fname` char(64) NOT NULL default '',
  `lname` char(64) NOT NULL default '',
  `description` char(64) NOT NULL default '',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `speed_dial_idx` (`username`,`domain`,`sd_domain`,`sd_username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `subscriber`
--

DROP TABLE IF EXISTS `subscriber`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `subscriber` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` char(64) NOT NULL default '',
  `domain` char(64) NOT NULL default '',
  `password` char(25) NOT NULL default '',
  `email_address` char(64) NOT NULL default '',
  `ha1` char(64) NOT NULL default '',
  `ha1b` char(64) NOT NULL default '',
  `rpid` char(64) default NULL,
  PRIMARY KEY  (`id`),
  UNIQUE KEY `account_idx` (`username`,`domain`),
  KEY `username_idx` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `uri`
--

DROP TABLE IF EXISTS `uri`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `uri` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` char(64) NOT NULL default '',
  `domain` char(64) NOT NULL default '',
  `uri_user` char(64) NOT NULL default '',
  `last_modified` datetime NOT NULL default '1900-01-01 00:00:01',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `account_idx` (`username`,`domain`,`uri_user`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `userblacklist`
--

DROP TABLE IF EXISTS `userblacklist`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `userblacklist` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` char(64) NOT NULL default '',
  `domain` char(64) NOT NULL default '',
  `prefix` char(64) NOT NULL default '',
  `whitelist` tinyint(1) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  KEY `userblacklist_idx` (`username`,`domain`,`prefix`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `usr_preferences`
--

DROP TABLE IF EXISTS `usr_preferences`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `usr_preferences` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `uuid` char(64) NOT NULL default '',
  `username` char(128) NOT NULL default '0',
  `domain` char(64) NOT NULL default '',
  `attribute` char(32) NOT NULL default '',
  `type` int(11) NOT NULL default '0',
  `value` char(128) NOT NULL default '',
  `last_modified` datetime NOT NULL default '1900-01-01 00:00:01',
  PRIMARY KEY  (`id`),
  KEY `ua_idx` (`uuid`,`attribute`),
  KEY `uda_idx` (`username`,`domain`,`attribute`),
  KEY `value_idx` (`value`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `version`
--

DROP TABLE IF EXISTS `version`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `version` (
  `table_name` char(32) NOT NULL default '',
  `table_version` int(10) unsigned NOT NULL default '0',
  UNIQUE KEY `t_name_idx` (`table_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `watchers`
--

DROP TABLE IF EXISTS `watchers`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `watchers` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `presentity_uri` char(128) NOT NULL default '',
  `watcher_username` char(64) NOT NULL default '',
  `watcher_domain` char(64) NOT NULL default '',
  `event` char(64) NOT NULL default 'presence',
  `status` int(11) NOT NULL default '0',
  `reason` char(64) default NULL,
  `inserted_time` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `watcher_idx` (`presentity_uri`,`watcher_username`,`watcher_domain`,`event`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `xcap`
--

DROP TABLE IF EXISTS `xcap`;
SET @saved_cs_client     = @@character_set_client;
SET character_set_client = utf8;
CREATE TABLE `xcap` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `username` varchar(64) NOT NULL default '',
  `domain` varchar(64) NOT NULL default '',
  `doc` blob NOT NULL,
  `doc_type` int(11) NOT NULL default '0',
  `etag` varchar(64) NOT NULL default '',
  `source` int(11) NOT NULL default '0',
  `doc_uri` varchar(128) NOT NULL default '',
  `port` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `account_doc_type_idx` (`username`,`domain`,`doc_type`,`doc_uri`),
  KEY `source_idx` (`source`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
SET character_set_client = @saved_cs_client;