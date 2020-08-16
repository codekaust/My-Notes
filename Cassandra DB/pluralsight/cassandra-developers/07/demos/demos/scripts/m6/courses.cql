-- Create and use keyspace
DROP KEYSPACE IF EXISTS pluralsight;
CREATE KEYSPACE pluralsight
WITH replication = {'class':'SimpleStrategy','replication_factor':1};

USE pluralsight;

-- Create clip type
CREATE TYPE clip (
  name varchar,
  duration int
);

-- Create courses table
CREATE TABLE courses (
  id varchar,
  name varchar static,
  author varchar static,
  audience int static,
  duration int static,
  features set<varchar> static,
  released timestamp static,
  module_id int,
  module_name varchar,
  module_duration int,
  clips list<frozen<clip>>,
  PRIMARY KEY (id, module_id)
) WITH comment = 'A table of courses';

-- Sample data for courses table

BEGIN UNLOGGED BATCH

  INSERT INTO courses (id, name, author, audience, duration, features, released)
  VALUES ('react-big-picture','React: The Big Picture', 'Cory House', 1, 4260, {'cc'}, '2017-11-21');

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('react-big-picture', 1, 'Course Overview', 41, [
      {name: 'Hello!', duration: 41}
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('react-big-picture', 2, 'Why React?', 1555, [
      {name: 'Intro',                          duration:  53},
      {name: 'History',                        duration: 121},
      {name: 'Why React?',                     duration:  27},
      {name: 'Reason 1: Flexibility',          duration: 210},
      {name: 'Reason 2: Developer Experience', duration: 290},
      {name: 'Reason 3: Corporate Investment', duration: 137},
      {name: 'Reason 4: Community',            duration: 211},
      {name: 'Reason 5: Performance',          duration: 187},
      {name: 'Reason 6: Testability',          duration: 235},
      {name: 'Summary',                        duration:  81}
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('react-big-picture', 3, 'Tradeoffs', 1412, [
      {name: 'Intro',                                               duration:  31},
      {name: 'Tradeoff 1: Framework vs. Library',                   duration: 156},
      {name: 'Tradeoff 2: Concise vs. Explicit',                    duration: 141},
      {name: 'Tradeoff 3: Template-centric vs. JavaScript-centric', duration: 369},
      {name: 'Tradeoff 4: Separate vs. Single File',                duration: 237},
      {name: 'Tradeoff 5: Standard vs. Non-standard',               duration: 255},
      {name: 'Tradeoff 6: Community vs. Corporate',                 duration: 111},
      {name: 'Summary',                                             duration: 109}
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('react-big-picture', 4, 'Why Not React?', 1236, [
      {name: 'Intro',                                duration:  61},
      {name: 'Concern 1: HTML and JSX Differ',       duration: 139},
      {name: 'Concern 2: Build Step Required',       duration:  99},
      {name: 'Concern 3: Version Conflicts',         duration: 141},
      {name: 'Concern 4: Outdated Resources Online', duration: 164},
      {name: 'Concern 5: Decision Fatigue',          duration: 487},
      {name: 'Next Steps',                           duration:  66},
      {name: 'Summary',                              duration:  77}
    ]);

APPLY BATCH;

BEGIN UNLOGGED BATCH

  INSERT INTO courses (id, name, author, audience, duration, features, released)
  VALUES ('nodejs-big-picture','Node.js: The Big Picture', 'Paul O''Fallon', 1, 3240, {'cc'}, '2019-06-03');

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('nodejs-big-picture', 1, 'Course Overview', 70, [
      {name: 'Course Overview', duration: 70}
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('nodejs-big-picture', 2, 'Considering Node.js', 900, [
      {name: 'Course Introduction',                                 duration: 184 },
      {name: 'Where Is Node.js Commonly Found?',                    duration: 277 },
      {name: 'What Makes up Node.js?',                              duration: 173 },
      {name: 'A Brief History / When Node May Not Be the Best Fit', duration: 265 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('nodejs-big-picture', 3, 'Thinking Asynchronously', 1304, [
      {name: 'Node''s Event Loop',          duration: 339 },
      {name: 'Asynchronous Development',    duration: 362 },
      {name: 'Node APIs and EventEmitters', duration: 221 },
      {name: 'Streams',                     duration: 380 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('nodejs-big-picture', 4, 'Defining an Application and Managing Dependencies', 525, [
      {name: 'Modularizing Your Application',    duration: 217},
      {name: 'npm and Application Dependencies', duration: 308}
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('nodejs-big-picture', 5, 'Assembling a Development Toolset', 489, [
      {name: 'Installing Node / Testing Applications', duration: 357},
      {name: 'Debugging / Conclusion',                 duration: 132}
    ]);

APPLY BATCH;

BEGIN UNLOGGED BATCH

  INSERT INTO courses (id, name, author, audience, duration, features, released)
  VALUES ('advanced-javascript','Advanced Javascript', 'Kyle Simpson', 2, 24900, {}, '2015-04-09');

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-javascript', 1, 'Introduction', 2408, [
      {name: 'Speaker Introduction',              duration: 878},
      {name: 'Speaker Introduction Part 2',       duration: 340},
      {name: 'JavaScript Resources',              duration: 209},
      {name: 'ECMAScript Language Specification', duration: 561},
      {name: 'Course Plan',                       duration: 418}
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-javascript', 2, 'Scope', 9914, [
      {name: 'Scope and the JavaScript Compiler',                            duration: 636},
      {name: 'Compiling Function Scope',                                     duration: 546},
      {name: 'Execution of Function Code',                                   duration: 696},
      {name: 'Scope and Execution Example',                                  duration: 794},
      {name: 'Function Declarations, Function Expressions, and Block Scope', duration: 594},
      {name: 'Lexical Scope',                                                duration: 300},
      {name: 'Cheating Lexical Scope: eval',                                 duration: 550},
      {name: 'IIFE Pattern',                                                 duration: 571},
      {name: 'IIFE Pattern Questions',                                       duration: 257},
      {name: 'Block Scope in ES6',                                           duration: 251},
      {name: 'Problems with the Let Keyword',                                duration: 490},
      {name: 'Dynamic Scope',                                                duration: 111},
      {name: 'Quiz: Scope',                                                  duration: 103},
      {name: 'Hoisting',                                                     duration: 775},
      {name: 'Exercise 1',                                                   duration: 174},
      {name: 'Exercise 1: Solution',                                         duration: 475},
      {name: 'this Keyword',                                                 duration: 724},
      {name: 'Binding Confusion',                                            duration: 395},
      {name: 'Explicit Binding',                                             duration: 759},
      {name: 'The New keyword',                                              duration: 491},
      {name: 'Quiz: this',                                                   duration: 211}
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-javascript', 3, 'Closure', 2801, [
      {name: 'Closures',              duration: 406 },
      {name: 'Closure Examples',      duration: 477 },
      {name: 'More Closure Examples', duration: 321 },
      {name: 'Module Patterns',       duration: 629 },
      {name: 'Quiz: Closure',         duration: 240 },
      {name: 'Exercise 2',            duration: 119 },
      {name: 'Exercise 2 Solution',   duration: 605 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-javascript', 4, 'Object Orienting', 6376, [
      {name: 'Prototype',                    duration:  305 },
      {name: 'Prototypes Explained, Part 1', duration:  603 },
      {name: 'Prototypes Explained, Part 2', duration:  417 },
      {name: 'Prototype Linkages',           duration:  511 },
      {name: 'Prototype: Objects Linked',    duration:  376 },
      {name: 'Linked Prototype Diagram',     duration:  267 },
      {name: 'Quiz: Prototype Behavior',     duration:  182 },
      {name: 'Exercise 3',                   duration:  169 },
      {name: 'Exercise 3: Solution',         duration:  404 },
      {name: 'Inheritance',                  duration:  306 },
      {name: 'OLOO',                         duration:  378 },
      {name: 'OLOO Questions',               duration:  547 },
      {name: 'Quiz: Prototype Unit',         duration:  434 },
      {name: 'Exercise 4',                   duration:  131 },
      {name: 'Exercise 4 Solution',          duration: 1338 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-javascript', 5, 'Async Patterns', 3437, [
      {name: 'Callbacks',                 duration:  495 },
      {name: 'Solving Callback Problems', duration:  182 },
      {name: 'Generators',                duration:  453 },
      {name: 'Promises',                  duration:  471 },
      {name: 'asynquence',                duration:  348 },
      {name: 'Quiz: Async Patterns',      duration:  148 },
      {name: 'Exercise 5',                duration:  151 },
      {name: 'Exercise 5 Solution',       duration: 1186 }
    ]);

APPLY BATCH;

BEGIN UNLOGGED BATCH

  INSERT INTO courses (id, name, author, audience, duration, features, released)
  VALUES ('advanced-python','Advanced Python', 'Robert Smallshire', 3, 13980, {'cc'}, '2017-06-24');

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-python', 1, 'Course Overview', 130, [
      {name: 'Course Overview', duration: 130 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-python', 2, 'Advanced Flow Control', 2579, [
      {name: 'Advanced Python', duration: 391 },
      {name: 'Introducing Advanced Flow Control',            duration:  32 },
      {name: 'Loop-else Clauses and While-else',             duration: 196 },
      {name: 'While-else for Evaluating Stack Programs',     duration: 403 },
      {name: 'For-else Clauses and Handling Search Failure', duration: 172 },
      {name: 'Alternatives to Loop-else Clauses',            duration:  86 },
      {name: 'Try-else Clauses',                             duration:  76 },
      {name: 'Emulating Switch Statements',                  duration: 432 },
      {name: 'Dispatching on Type',                          duration: 412 },
      {name: 'Double Dispatch with Methods',                 duration: 189 },
      {name: 'Summary',                                      duration: 185 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-python', 3, 'Byte-oriented Programming', 2526, [
      {name: 'Everything Is Bits and Bytes',       duration:  62 },
      {name: 'Bitwise Operations on Integers',     duration: 522 },
      {name: 'Byte-wise Operations with Integers', duration:  97 },
      {name: 'The Bytes Type in Depth',            duration: 213 },
      {name: 'The bytearray Type',                 duration: 142 },
      {name: 'Interpreting Binary Structures',     duration: 695 },
      {name: 'The memoryview Type',                duration: 413 },
      {name: 'Memory-mapped Files',                duration: 246 },
      {name: 'Summary',                            duration: 132 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-python', 4, 'Object Internals and Custom Attributes', 1851, [
      {name: 'Introducing Object Internals', duration: 40 },
      {name: 'How are Python Objects Represented?', duration: 321 },
      {name: 'Overriding __getattr__',                 duration: 134 },
      {name: 'Overriding __setattr__',                 duration:  36 },
      {name: 'Pitfalls with __getattr__',              duration: 154 },
      {name: 'Overriding __delattr__',                 duration:  73 },
      {name: 'Customizing Attribute Storage',          duration: 171 },
      {name: 'Direct vs. Indirect Access to __dict__', duration:  63 },
      {name: 'Overriding __getattribute__',            duration: 267 },
      {name: 'Attribute Lookup for Special Methods',   duration: 125 },
      {name: 'Where are Methods Stored?',              duration: 122 },
      {name: 'Trading Size for Dynamism with Slots',   duration: 228 },
      {name: 'Summary',                                duration: 112 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-python', 5, 'Descriptors', 1329, [
      {name: 'Introducing Descriptors',        duration: 214 },
      {name: 'Properties are Descriptors',     duration: 288 },
      {name: 'Implementing a Descriptor',      duration: 466 },
      {name: 'Calling Descriptors on Classes', duration:  82 },
      {name: 'Data vs. Non-data Descriptors',  duration: 151 },
      {name: 'Summary',                        duration: 125 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-python', 6, 'Instance Creation', 647, [
      {name: 'Instance Creation',         duration: 198 },
      {name: 'Allocation with __new__()', duration: 139 },
      {name: 'Customizing Allocation',    duration: 246 },
      {name: 'Summary',                   duration:  63 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-python', 7, 'Metaclasses', 2182, [
      {name: 'Metaclasses',                                  duration: 177 },
      {name: 'Class Allocation and Initialization',          duration: 520 },
      {name: 'Metaclass Keyword Arguments',                  duration: 187 },
      {name: 'Metaclass Method Visibility',                  duration: 129 },
      {name: 'Metaclass __call__: The Instance Constructor', duration: 263 },
      {name: 'A Practical Metaclass Example',                duration: 253 },
      {name: 'Naming Descriptors Using Metaclasses',         duration: 223 },
      {name: 'Metaclasses and Inheritance',                  duration: 306 },
      {name: 'Summary',                                      duration: 120 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-python', 8, 'Class Decorators', 717, [
      {name: 'Class Decorators',                  duration: 151 },
      {name: 'Enforcing Class Invariants',        duration: 257 },
      {name: 'Detecting and Wrapping Properties', duration: 168 },
      {name: 'Chaining Class Decorators',         duration: 110 },
      {name: 'Summary',                           duration:  30 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('advanced-python', 9, 'Abstract Base Classes', 2036, [
      {name: 'Introducing Abstract Base Classes',             duration: 261 },
      {name: 'Abstract Base Classes in Python',               duration: 207 },
      {name: 'Abstract Base Classes in Practice',             duration: 191 },
      {name: 'Non-transitive Subclass Relationships',         duration: 122 },
      {name: 'Method Resolution with Virtual Base Classes',   duration:  53 },
      {name: 'Library Support for Abstract Base Classes',     duration: 142 },
      {name: 'Virtual Subclass Registration',                 duration:  60 },
      {name: 'Combining Subclass Detection and Registration', duration: 121 },
      {name: 'The ABC Convenience Base Class',                duration:  32 },
      {name: 'Declaring Abstract Methods',                    duration: 166 },
      {name: 'Combining Method Decorators',                   duration: 143 },
      {name: 'Improving @invariant with ABCs',                duration: 269 },
      {name: 'Summary', duration: 262 }
    ]);

APPLY BATCH;

BEGIN UNLOGGED BATCH

  INSERT INTO courses (id, name, author, audience, duration, features, released)
  VALUES ('raspberry-pi-for-developers','Raspberry Pi for Developers', 'Jon Flanders', 2, 8640, {'cc'}, '2013-05-30');

    INSERT INTO courses JSON '{
       "id": "raspberry-pi-for-developers",
       "module_id": 1,
       "module_name": "Introduction to Raspberry Pi",
       "module_duration": 1765,
       "clips": [
         { "name": "Introduction",                "duration": 206 },
         { "name": "Hardware and Software",       "duration": 299 },
         { "name": "Programming",                 "duration": 447 },
         { "name": "Getting Set Up",              "duration": 335 },
         { "name": "Demo: Intro to Raspberry Pi", "duration": 412 },
         { "name": "Summary",                     "duration":  66 }
       ]
     }';

   INSERT INTO courses JSON '{
     "id": "raspberry-pi-for-developers",
     "module_id": 2,
     "module_name": "Programming the Raspberry Pi",
     "module_duration": 2250,
     "clips": [
       { "name": "Introduction",            "duration":  12 },
       { "name": "Programming Choices",     "duration": 190 },
       { "name": "Python Basics",           "duration": 770 },
       { "name": "Demo: Python",            "duration": 383 },
       { "name": "Python and Raspberry Pi", "duration":  58 },
       { "name": "Python GUI",              "duration":  42 },
       { "name": "Demo: Python GUI",        "duration": 538 },
       { "name": "Other languages",         "duration": 194 },
       { "name": "Summary",                 "duration":  63 }
     ]
   }';

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('raspberry-pi-for-developers', 3, 'Raspberry Pi and Hardware', 1877, [
      {name: 'Introduction',             duration: 215 },
      {name: 'GPIO',                     duration: 195 },
      {name: 'Using a Breadboard',       duration: 100 },
      {name: 'Using Bash',               duration:  84 },
      {name: 'From Python',              duration:  52 },
      {name: 'Demo: Hardware',           duration: 311 },
      {name: 'Raspberry Pi and Arduino', duration: 387 },
      {name: 'Demo: Pi with Arduino',    duration: 488 },
      {name: 'Summary',                  duration:  45 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('raspberry-pi-for-developers', 4, 'Raspberry Pi as a Web Server', 1592, [
      {name: 'Introduction',            duration: 158 },
      {name: 'Serving Up Static Files', duration: 102 },
      {name: 'Demo: nginx',             duration: 163 },
      {name: 'Dynamic Content',         duration:  99 },
      {name: 'Demo:Python',             duration: 551 },
      {name: 'Node.js',                 duration:  92 },
      {name: 'Demo: Node.js',           duration: 410 },
      {name: 'Summary',                 duration:  17 }
    ]);

    INSERT INTO courses (id, module_id, module_name, module_duration, clips)
    VALUES ('raspberry-pi-for-developers', 5, 'Raspberry Pi as a DVR', 1197, [
      {name: 'Introduction',                  duration:  53 },
      {name: 'Getting XBMC',                  duration:  97 },
      {name: 'XBMC Add-ons',                  duration: 293 },
      {name: 'Demo: Building an XBMC Add-on', duration: 745 },
      {name: 'Summary',                       duration:   9 }
    ]);

APPLY BATCH;
