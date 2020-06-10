CREATE KEYSPACE IF NOT EXISTS pluralsight
WITH replication = {'class':'SimpleStrategy','replication_factor':1};

USE pluralsight;

create table users (
    id varchar primary key,
    first_name varchar,
    last_name varchar,
    company varchar,
    tags set<varchar>,
    email varchar,
    password varchar,
    reset_token varchar,
    last_login tuple<timestamp,inet>
) with comment = 'A table of users';

insert into users (id, first_name, last_name, company, tags, email)
values ('john-doe', 'John', 'Doe', 'acme-corp', {'java'}, 'john@doe.com');

insert into users (id, first_name, last_name, email)
values ('jane-doe', 'Jane', 'Doe', 'jane@doe.com');

create index on users(company);
create index on users(tags);
