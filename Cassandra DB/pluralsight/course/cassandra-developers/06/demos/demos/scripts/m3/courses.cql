-- Create and use keyspace
DROP KEYSPACE IF EXISTS pluralsight;
CREATE KEYSPACE pluralsight
WITH replication = {'class':'SimpleStrategy','replication_factor':1};

USE pluralsight;

-- Create courses table
CREATE TABLE courses (
  id varchar primary key,
  name varchar,
  author varchar,
  audience int,
  duration int,
  cc boolean,
  released timestamp
) WITH comment = 'A table of courses';

-- Sample data for courses table
INSERT INTO courses (id, name, author, audience, duration, cc, released)
VALUES ('react-big-picture','React: The Big Picture', 'Cory House', 1, 4260, true, '2017-11-21');

INSERT INTO courses (id, name, author, audience, duration, cc, released)
VALUES ('nodejs-big-picture','Node.js: The Big Picture', 'Paul O''Fallon', 1, 3240, true, '2019-06-03');

INSERT INTO courses (id, name, author, audience, duration, cc, released)
VALUES ('advanced-javascript','Advanced Javascript', 'Kyle Simpson', 2, 24900, true, '2015-04-09');

INSERT INTO courses (id, name, author, audience, duration, cc, released)
VALUES ('advanced-python','Advanced Python', 'Robert Smallshire', 3, 13980, true, '2017-06-24');

INSERT INTO courses (id, name, author, audience, duration, cc, released)
VALUES ('raspberry-pi-for-developers','Raspberry Pi for Developers', 'Jon Flanders', 2, 8640, true, '2013-05-30');
