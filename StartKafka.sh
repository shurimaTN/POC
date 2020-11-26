#!/bin/bash 
cd kafka_2.13-2.6.0
ls
bin/zookeeper-server-start.sh config/zookeeper.properties & bin/kafka-server-start.sh config/server.properties & echo  "Started Kafka " 