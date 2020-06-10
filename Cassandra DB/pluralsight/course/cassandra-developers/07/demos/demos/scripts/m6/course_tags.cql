use pluralsight;

-- Create course_tags table

CREATE TABLE course_tags (
  tag varchar,
  course_id varchar,
  PRIMARY KEY (tag, course_id)
);

ALTER TABLE courses ADD tags set<varchar> STATIC;

-- Sample data for courses and course_tags table

BEGIN BATCH

UPDATE courses SET tags = {'developer', 'open-source', 'javascript', 'node.js'} where id = 'nodejs-big-picture';

  INSERT INTO course_tags (tag, course_id, course_name) VALUES ('developer','nodejs-big-picture');
  INSERT INTO course_tags (tag, course_id, course_name) VALUES ('open-source','nodejs-big-picture');
  INSERT INTO course_tags (tag, course_id, course_name) VALUES ('javascript','nodejs-big-picture');
  INSERT INTO course_tags (tag, course_id, course_name) VALUES ('node.js','nodejs-big-picture');

APPLY BATCH;
