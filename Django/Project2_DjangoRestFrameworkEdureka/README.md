These are notes for creating a simple RESTful API using Django (from [this](https://www.youtube.com/watch?v=ejJ-2oz4AgI) video).

**API**: Application Programming Interface
**REST**: Representational State Transfer. Used for web based architecture for data transfer and mostly uses *Get, Put, Post, Delete* methods.
**REST APIs**: Basically a set of web pages that respond with pure information, not a formatted web page.

# Installation and Project Creation
You must have python3, pip3 installed. Also we will be installing `djangorestframework` in a virtualenv.
```
virtualenv -p /usr/bin/python3 python3-venv/django-rest-venv
source python3-venv/django-rest-venv/bin/activate
pip3 install Django
pip3 install djangorestframework
```
Keep the environment activated for all future commands.

Create project:
```
django-admin startproject myproject
```

**Project**: An app to store some information about empolyees and access them using REST API.

# Configuration
Create app named `webapp`:
```
django-admin startapp webapp
```

Add following to `myproject/setting.py`/INSTALLED_APPS:
```python
'rest_framework',
'webapp',
```

# Model: Employees
Add following class to `webapp/models`:
```python
from django.db import models

class employees(models.Model):
    firstname=models.CharField(max_length=20)
    lastname=models.CharField(max_length=20)
    emp_Id=models.IntegerField()

    def __str__(self):
        return self.firstname+" "+self.lastname
```

Make migrations and migrate. Run:
```
python3 manage.py makemigrations
python3 manage.py migrate
```

**Adding `employees` from admin page**:
-   Add following to `webapp/admin.py`:
    ```python
    from . models import employees

    admin.site.register(employees)
    ```
-   Now **create superuser** (`python3 manage.py createsuperuser`) and run `http://127.0.0.1:8000/admin` on server (`python3 manage.py runserver`). 
-   Add *employees* from this page.

# Serializer
Now, we will create a serializer class. This will convert model entries to `JSON` data.

Add file `webapp/serializers.py`. Add the following code in the file:
```python
from rest_framework import serializers
from . models import employees

class employeesSerializer(serializers.ModelSerializer):
    class Meta:
        model = employees
        fields = '__all__'
```

# Views
Here, we will add the code so when we request API, we just get the JSON back. Focus on `get` and `post` method.

```python
from django.shortcuts import render

from django.http import HttpResponse
from django.shortcuts import get_object_or_404
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status

from . models import employees
from . serializers import employeesSerializer

class employeesList(APIView):
    def get(self, request):
        employeesL = employees.objects.all()
        serializer = employeesSerializer(employeesL, many = True)
        return Response(serializer.data)

    def post(self):
        pass
```

Following is an unrelated `views.py` which show a basic post api and data manipulation:

```
from django.shortcuts import render

from django.http import HttpResponse
from django.shortcuts import get_object_or_404
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status

from .models import request_logs
from .serializers import rlogSerializer

from datetime import datetime
import pytz


class rloglist(APIView):
    def get(self, request):
        rloglist = request_logs.objects.all()
        serializer = rlogSerializer(rloglist, many=True)
        return Response(serializer.data)

    def post(self, request):
        """
        BODY FORMAT:
        
            {
              "timestamp": "{{{PARTICLE_PUBLISHED_AT}}}",
              "emergency": "{{{emergency}}}",
              "latitude": "{{{latitude}}}",
              "longitude": "{{{longitude}}}",
              "accuracy": "{{{accuracy}}}"
            }
        """

        # dictionary of recieved data body
        req_data = request.data

        print("Request Data:\n:", req_data)

        # update timestamp to use indian time (UTC -> Asia/Kolkata)
        utc_datetime = datetime.strptime(req_data["timestamp"], "%Y-%m-%dT%H:%M:%S.%fZ")
        utc_datetime = utc_datetime.replace(tzinfo=pytz.utc)

        db_datetime_format = "%Y-%m-%d %H:%M:%S"

        req_data['timestamp']=utc_datetime.strftime(db_datetime_format)

        # divide emergency string in emergency_type, core_id
        emergency = req_data["emergency"]
        emergency_type, core_id = emergency.split("-")

        del req_data["emergency"]
        req_data["emergency_type"] = emergency_type
        req_data["core_id"] = core_id

        # serialize data to save in db
        print("Parsed data:\n", req_data)
        serializer = rlogSerializer(data=req_data)

        if serializer.is_valid(raise_exception=True):
            # check for previous log
            query_set = request_logs.objects.filter(
                emergency_type = req_data['emergency_type'],
                core_id = req_data['core_id'],
                status='a',
            )

            should_save_logs = True

            if query_set.exists() :
                for log in query_set:
                    log_datetime = datetime.strptime(log.timestamp, '%Y-%m-%d %H:%M:%S')
                    log_datetime = log_datetime.replace(tzinfo=pytz.utc)

                    if isDifLessThanFiveMinutes(utc_datetime, log_datetime) :
                        should_save_logs = False
                        break
            
            if should_save_logs:
                print("Saving Log")
                saved_obj = serializer.save()
            else :
                print("Not Saving Log")

        # return_val
        if (
            req_data["latitude"] == "-1"
            or req_data["longitude"] == "-1"
            or req_data["accuracy"] == "-1"
        ):
            return_val = emergency + "/0"
        else:
            return_val = emergency + "/1"

        return Response(return_val,)

def isDifLessThanFiveMinutes(later, before):
    diff = later - before
    seconds_in_day = 24 * 60 * 60
    secs = diff.days * seconds_in_day + diff.seconds
    return  (secs < 300)
```

# URL
Add the following import:
```python
from rest_framework.urlpatterns import format_suffix_patterns
from webapp import views
```

Add following URL:
```py
urlpatterns = [
    path('employees/', views.employeesList.as_view()),
]
```