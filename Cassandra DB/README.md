This document contains my notes on Cassandra db, with these resources:
1. Videos: [1](https://www.youtube.com/watch?v=xQnIN9bW0og), [2](https://www.youtube.com/watch?v=iDhIjrJ7hG0)
2. Blogs & Related: [Simplilearn](https://www.simplilearn.com/cassandra-architecture-tutorial-video), [Tutorials Point](https://www.tutorialspoint.com/cassandra/cassandra_data_model.htm), [DZone](https://dzone.com/articles/introduction-apache-cassandras)
3. [Documentation](https://cassandra.apache.org/doc/latest/)

# General Intro to NoSQL
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
![Cassandra vs RDBMS](https://raw.githubusercontent.com/codekaust/My-Notes/master/Cassandra%20DB/pictures/Cassandra_vs_RDBMS.png)

# Cassandra
- Cassandra is massively scalable [offers linear scalability], distributed, open source, non-relational database.

- **CAP** [Consistency, Availability, Partition Tolerance] Theorem states that in presence of network partition, one has to choose between Consistency and Availability. **Cassandra chose Availability**, so it offers very high availability and is eventually [after a while of data being written] consistent. 

Availability is supported by **Active Everywhere Design** -> all nodes maybe read and written at.

**Continuous Availability** eliminates single point of failure by redundancy in both data and node functioning.

**CQL & Flexible-Dynamic data models**: Cassandra offers Cassandra Query Language [SQL like] and supports modern data types with fast read write.

## Cassandra Architecture
- Architecture reason for ability to scale, perform, and offer continuous uptime. 
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
|A schema in a relational model is fixed. Once we define certain columns for a table, while inserting data, in every row all the columns must be filled at least with a null value.|Although the column families are defined, the columns are not. You can freely add any column to any column family at any time.|
|Relational tables define only columns and the user fills in the table with values.|A table contains columns, or can be defined as a super column family.|

![Column_Family](https://raw.githubusercontent.com/codekaust/My-Notes/master/Cassandra%20DB/pictures/Column_Family.png)

Attributes:
1. *keys_cached* − It represents the number of locations to keep cached per SSTable.
2. *rows_cached* − It represents the number of rows whose entire contents will be cached in memory.
3. *preload_row_cache* − It specifies whether you want to pre-populate the row cache.

### Column
Basic data str.; has name, value, timestamp
![Column](https://raw.githubusercontent.com/codekaust/My-Notes/master/Cassandra%20DB/pictures/Column.png)


3. **Primary Key:** Identifies rows uniquely in *a table*. Distributes a table's rows across multiple nodes in cluster.
4. **Partition Key:** Key on which data partitioned across nodes.
5. **Clustering Keys:** Key on which data is clustered on a node.

This seems quite like a rdbms, *its made to look so but is not*. Its something like a nested sorted map data structure.

NOTE: Primary, Partition, Clustering key to be declared at time of table creation itself.