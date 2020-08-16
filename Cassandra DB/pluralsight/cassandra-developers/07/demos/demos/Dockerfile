FROM cassandra:3.11
COPY cqlshrc /root/.cqlshrc
RUN sed -i -E "s/user_defined_functions: false/user_defined_functions: true/g" /etc/cassandra/cassandra.yaml
