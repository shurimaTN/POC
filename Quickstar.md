# POC CACIB: Quickstart guide 

## Start hadoop:
If you want to install hadoop please follow [this guide](https://data-flair.training/blogs/install-hadoop-on-ubuntu/)
in order to start hadoop run the following shell script:

```
$ ./Starthadoop.sh
```
if you wish to stop hadoop 
```
$ stop-yarn.sh
```
## Start Kafka: 
kafka dependencies are included within this repository to make sure  it can be started within the project as kafka is path-agnostic.
We assume this step occurs after correctly installing hadoop in step  one
Start kafka by running the following command:
```
$ ./StartKafka.sh
```
## Start elasticsearch inside docker 
```
docker run -p 9200:9200 -p 9300:9300 -e "discovery.type=single-node" docker.elastic.co/elasticsearch/elasticsearch:7.9.2
```