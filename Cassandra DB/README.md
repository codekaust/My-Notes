This document contains my notes on Cassandra db, with these resources:
1. Videos: [1](https://www.youtube.com/watch?v=xQnIN9bW0og), [2](https://www.youtube.com/watch?v=iDhIjrJ7hG0)
2. GS Doc
2. [Documentation](https://cassandra.apache.org/doc/latest/)

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

 ![NoSQL](https://raw.githubusercontent.com/codekaust/My-Notes/master/Cassandra%20DB/NoSQL.png)

 ### Cassandra vs RDBMS
![Cassandra vs RDBMS](https://raw.githubusercontent.com/codekaust/My-Notes/master/Cassandra%20DB/Cassandra_vs_RDBMS.png)

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
