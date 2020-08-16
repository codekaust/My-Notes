This document contains my notes on Cassandra db, with these resources:
1. Videos: [1](https://www.youtube.com/watch?v=xQnIN9bW0og), [2](https://www.youtube.com/watch?v=iDhIjrJ7hG0)
2. Blogs & Related: [Simplilearn](https://www.simplilearn.com/cassandra-architecture-tutorial-video), [Tutorials Point](https://www.tutorialspoint.com/cassandra/cassandra_data_model.htm), [DZone](https://dzone.com/articles/introduction-apache-cassandras)
3. [Documentation](https://cassandra.apache.org/doc/latest/)

# General Intro to NoSQL
How do you choose your database? 

Query patterns (cause the compute is much costlier than storage), shape/kind of data (is it highly structured or smth else), scalability (some databases are horizontaly scalable and some don't have that facility)..., then odcourse think of the cost too.
 
## Pros and Cons of RDBMS & NoSQL db
Cassandra is a NoSQL db. RDBMS provides a much organized storage of data than NoSQL. It is commonly said that NoSQL is better in cases when the db size is huge, as RDBMS is expensive in such cases, but scalability is not the only factor.

### 5 V's of Big Data:
1. Volume
2. Variety
3. Velocity
4. Value
5. Veracity

### Pros of NoSQL:

1. Fast Insertion Retrieval: NoSQL uses id->value mapping. *Value is usually a big fat blob of data*. The important point is that if a particular kind of data, like profile of person, is stored and retrieved in this blob fashion, i.e. **complete blob is read and written, then NoSQL gives very high performance**.

2. Schema Easily Changeable: Also, NoSQL gives you facility of no fix schema having different structures for values of different keys, which makes things easy in scenarios like you need to add a new column in a table etc and fill with default values for all previous rows [expensive op].

3. Built for Scale, Availability, Cost Effective [most NoSQL are free to use]: Usually, horizontal scalability is pre-provided, and redundancy can be produced easily increasing availability [due to distributed nature of most NoSQL dbs].

4. Built for data aggregations / metrics / analytics.

### Cons of NoSQL:

1. Not built for high number of updates.

2. ACID [Atomicity, consistency, isolation, durability] not guaranteed, as there is no fix schema for value blobs which specially hurts consistency. Thus not preferred by financial systems.

3. Not read optimized, eg. you just need to read ages of all students in student db, it will be expensive in NoSQL, also some students may not have age defined too. Even teh return values for age may be different for different students.
 
 4. Relations are not implicit.
 
 5. Joins are hard and expensive

 ![NoSQL](https://raw.githubusercontent.com/codekaust/My-Notes/master/Cassandra%20DB/pictures/NoSQL.png)

 ### Cassandra vs RDBMS
![Cassandra vs RDBMS](https://raw.githubusercontent.com/codekaust/My-Notes/master/Cassandra%20DB/pictures/General-Cassandra_vs_RDBMS.png)

# Cassandra
- Cassandra is massively scalable [offers linear scalability], distributed, open source, non-relational database.

- **CAP** [Consistency, Availability, Partition Tolerance] Theorem states that in presence of network partition, one has to choose between Consistency and Availability. **Cassandra chose Availability**, so it offers very high availability and is eventually [after a while of data being written] consistent. 

Availability is supported by **Active Everywhere Design** -> all nodes maybe read and written at.

**Continuous Availability** eliminates single point of failure by redundancy in both data and node functioning.

**CQL & Flexible-Dynamic data models**: Cassandra offers Cassandra Query Language [SQL like] and supports modern data types with fast read write.

## Cassandra Architecture
- Architecture is the reason for ability to scale, perform, and offer continuous uptime. 
- Has a master-less “ring” design, and not legacy master-slave or a manual and difficult-to-maintain sharded architecture.
- All nodes play an identical role; no concept of a master node; all nodes communicating with each other equally.
- This built-for-scale architecture means that it is capable of handling large amounts of data and thousands of concurrent users or operations per second— even across multiple data centers— as easily as it can manage much smaller amounts of data and user traffic. 
- Unlike other master-slave or sharded systems, it has no single point of failure and therefore is capable of offering true continuous availability and uptime — simply add new nodes to an existing cluster without having to take it down.

You can use the resources and get comfortable with following concepts for better understanding of Cassandra Architecture:
1. Clusters
2. Data Centers
3. Nodes, and Coordinator Node
4. Read and Write Sequence in Cassandra
5. Replication and its strategies
6. Gossip Protocol, Hashing


## Cassandra Data Model
### Cluster
Cassandra db is distributed over several machines [for reasons like availability, failure handling, etc]. The outermost container, which can contain multiple machines [*nodes*], is called a **Cluster**. Cassandra arranges *nodes* like a ring in a *cluster*.

### Keyspace
Outermost container for data; contains data tables [column families] and indices; like a db in rdbms. Level at which replication is defined [and thus done].
Attributes:
1. Replication Factor
2. Replica Placement Strategy: simple strategy (rack-aware strategy), network topology strategy (data center shared strategy)
3. Column Families: At least one and often many column families.

![Keyspace](https://raw.githubusercontent.com/codekaust/My-Notes/master/Cassandra%20DB/pictures/Keyspace.png)

*Syntax for Keyspace creation:*
```SQL
CREATE KEYSPACE Keyspace name
WITH replication = {'class': 'SimpleStrategy', 'replication_factor' : 3};
```

### Column Family
Container of a collection of rows; each row contains ordered columns.

Column families represent the structure of your data.

Like rdbms table; but can hold vast amount of data + fast row insert and column level read.

|Relational Table|	Cassandra column Family|
|-|-|
|A schema in a relational model is fixed. Once we define certain columns for a table, while inserting data, in every row all the columns must be filled at least with a null value.|Although the column families are defined, the columns are not. You can freely add any column to any column family at any time.Cassandra is somewhat a nested sorted map data structure.|
|Relational tables define only columns and the user fills in the table with values.|A table contains columns, or can be defined as a super column family. |


![Column_Family](https://raw.githubusercontent.com/codekaust/My-Notes/master/Cassandra%20DB/pictures/Column_Family.png)

Attributes:
1. *keys_cached* − It represents the number of locations to keep cached per SSTable.
2. *rows_cached* − It represents the number of rows whose entire contents will be cached in memory.
3. *preload_row_cache* − It specifies whether you want to pre-populate the row cache.

### Column & Super Column
Basic data str.; key value pair; has name, value, timestamp.

![Column](https://raw.githubusercontent.com/codekaust/My-Notes/master/Cassandra%20DB/pictures/Column.png)

**Super Column** is a special column, and thus key-value pair with value as *map of sub-columns*. Used to optimize performance keeping columns likely to be queried together in one map, and thus super column.

![Super_Column](https://raw.githubusercontent.com/codekaust/My-Notes/master/Cassandra%20DB/pictures/Super_Col.png)

### Some Important Keys
1. **Primary Key:** Identifies rows uniquely in *a table*. Distributes a table's rows across multiple nodes in cluster.
2. **Partition Key:** Key on which data partitioned across nodes.
3. **Clustering Keys:** Key on which data is clustered on a node.

NOTE: Primary, Partition, Clustering key to be declared at time of table creation itself.

### Cassandra vs RDBMS in Data Model

|RDBMS|Cassandra|
|-|-|
|RDBMS deals with structured data.|Cassandra deals with unstructured data.|
|It has a fixed schema.|Cassandra has a flexible schema.|
|In RDBMS, a table is an array of arrays. (ROW x COLUMN)	|In Cassandra, a table is a list of “nested key-value pairs”. (ROW x COLUMN key x COLUMN value)|
|Database is the outermost container that contains data corresponding to an application.|Keyspace is the outermost container that contains data corresponding to an application.|
|Tables are the entities of a database.|Tables or column families are the entity of a keyspace.|
|Row is an individual record in RDBMS.|Row is a unit of replication in Cassandra.|
|Column represents the attributes of a relation.|Column is a unit of storage in Cassandra.|
RDBMS supports the concepts of foreign keys, joins.|Relationships are represented using collections.|

# Cassandra Installation
Cassandra can be accessed using `cqlsh`[CQL Shell] as well as drivers of different languages. Here, we will only focus on cqlsh.

So there are many installation guides to install Cassandra in your local machine. I ended up using the following commands from [official download page](https://cassandra.apache.org/download/):
```bash
echo "deb https://downloads.apache.org/cassandra/debian 311x main" | sudo tee -a /etc/apt/sources.list.d/cassandra.sources.list
curl https://downloads.apache.org/cassandra/KEYS | sudo apt-key add -
sudo apt-get update
sudo apt-get install cassandra
```

Some other imp points:
1. `sudo systemctl status/start/stop/restart/enable/disable cassandra` [enable / disable used to make cassandra start / not-start on startup]
2. Cassandra has some issues running with java versions > 8. So to use java 8, install it and `sudo update-alternatives --config java` to change what version you will use now on.
3. These commands can also be of use: I) `sudo nodetool status`. II) `cqlsh`

# CQLSH [Cassandra Query Language Shell]
Using cqlsh, you can define a schema, insert data, and execute a query. To start CQLSH use command `cqlsh`. Some important options:
|Option|Usage|
|-|-|
|cqlsh --{color/no-color}|Directs the shell to use colored/non-coloured output.|
|cqlsh --execute <cql_stmt>|Executes statement and exit|
|cqlsh --file <file_name>|Execute statement from file and exit|
|cqlsh -u <user_name>|Authenticate a user. Default user: cassandra.|
|cqlsh -p <password>|Use it with `-u` to auth user with password. Default pass: cassandra.|

## Shell Commands
Given below are the Cqlsh documented shell commands. These are the commands used to perform tasks such as displaying help topics, exit from cqlsh, describe,etc.

HELP − Displays help topics for all cqlsh commands.

CAPTURE − Captures the output of a command and adds it to a file.

CONSISTENCY − Shows the current consistency level, or sets a new consistency level.

COPY − Copies data to and from Cassandra.

DESCRIBE − Describes the current cluster of Cassandra and its objects.

EXPAND − Expands the output of a query vertically.

EXIT − Using this command, you can terminate cqlsh.

PAGING − Enables or disables query paging.

SHOW − Displays the details of current cqlsh session such as Cassandra version, host, or data type assumptions.

SOURCE − Executes a file that contains CQL statements.

TRACING − Enables or disables request tracing.

### CQL Data Definition Commands

CREATE KEYSPACE − Creates a KeySpace in Cassandra.

USE − Connects to a created KeySpace.

ALTER KEYSPACE − Changes the properties of a KeySpace.

DROP KEYSPACE − Removes a KeySpace

CREATE TABLE − Creates a table in a KeySpace.

ALTER TABLE − Modifies the column properties of a table.

DROP TABLE − Removes a table.

TRUNCATE − Removes all the data from a table.

CREATE INDEX − Defines a new index on a single column of a table.

DROP INDEX − Deletes a named index.

### CQL Data Manipulation Commands

INSERT − Adds columns for a row in a table.

UPDATE − Updates a column of a row.

DELETE − Deletes data from a table.

BATCH − Executes multiple DML statements at once.

CQL Clauses
SELECT − This clause reads data from a table

WHERE − The where clause is used along with select to read a specific data.

ORDERBY − The orderby clause is used along with select to read a specific data in a specific order.
