The following are my short notes on django tutorial [Django-Girls](https://tutorial.djangogirls.org/en/).

# Installing Django in Virtual Environment

First check if you have python3 and pip3 installed in your system. Install `virtualenv`, create a virtual env named `django-venv`, activate it, install `Django` in it, keep it activated: 
```python
sudo pip3 install virtualenv
mkdir python3-venv
virtualenv -p /usr/bin/python3 ~/python3-venv/django-venv
source ~/python3-venv/django-venv/bin/activate
pip3 install Django
```

# Start Project
Make and change directory to a folder `LearnDjango-Blog-DjangoGirls`, start project `mysite`:
```python
django-admin startproject mysite .
```
- `manage.py` helps manage site and run the server.
- `mysite/settings.py` contains website configuration.
- `mysite/urls.py` contains urls used by `urlresolver`.

#### Changes in settings.py
Add path for static files used in future. Below `STATIC_URL` add `STATIC_ROOT`:
```python
STATIC_URL = '/static/'
STATIC_ROOT = os.path.join(BASE_DIR, 'static')
```

When `DEBUG` is True and `ALLOWED_HOSTS` is empty, the host is validated against `['localhost', '127.0.0.1', '[::1]']`. This won't match our hostname on PythonAnywhere (where we shall deploy our app soon), make the following changes so that the setings can be used for deployment too.
```python
ALLOWED_HOSTS = ['127.0.0.1', '.pythonanywhere.com']
```

Also,you can change setting for database in dictionary `DATABASES`. By default, splite3 database is used by django.

#### Creating Database
Run the following command to create the database.
```python
python3 manage.py migrate
```
**Migrations**: Migrations are Django’s way of propagating changes you make to your models (adding a field, deleting a model, etc.) into your database schema. Some useful commands are: `migrate`, `makemigrations`, `sqlmigrate`, `showmigrations`.

### Running Server
Run the following command to start server:
```python
python3 manage.py runserver
```

# Django Models
As we need to make objects of `blogs`, so lets build their models:

NOTE: A model in Django is a special kind of object (a model will be like a separate spreadsheet in the db) only. All objects are stored in database in django.

The model of blog will be inside an `app` named blog. For one project, numerous apps are created in django for clarity, which serve different low-coupled purposes.

Create an app blog:
```python
python3 manage.py startapp blog
```
Tell Django to use the app, under `INSTALLED_APPS` in `mysite/setting.py` add `'blog.apps.BlogConfig'`. Finally,
```python
INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'blog.apps.BlogConfig',
]
```
### Creating BlogPost Model
Inside `blog/models.py` add class (with required imports) which represents the model for a `Post` (blog post). Final `blog/models.py`:
```python
from django.conf import settings
from django.db import models
from django.utils import timezone


class Post(models.Model):
    author = models.ForeignKey(settings.AUTH_USER_MODEL, on_delete=models.CASCADE)
    title = models.CharField(max_length=200)
    text = models.TextField()
    created_date = models.DateTimeField(default=timezone.now)
    published_date = models.DateTimeField(blank=True, null=True)

    def publish(self):
        self.published_date = timezone.now()
        self.save()

    def __str__(self):
        return self.title
```

### Creating the tables in database
We need to make migrations to add the changes in `models` in the database.
- First make Django know that we made migrations, thus create a migration file using `makemigrations`.
- Apply the migration file to the database.
```python
python3 manage.py makemigrations blog
python3 manage.py migrate blog
```

# Django Admin
Above we created model for `Post`, we can add, edit and delete them using `Django Admin`. Add this in `blog/admin.py` which basically adds interface to manipulate Posts (a model) on admin page:
```python
from django.contrib import admin
from .models import Post

admin.site.register(Post)
```

Now, `createsuperuser` to login in admin page, and run the server. Visit `http://127.0.0.1:8000/admin`.
```python
python3 manage.py createsuperuser
...
python3 manage.py runserver
```

# Deploy on PythonAnywhere
We will push our code to Github, and the will pull the whole project from terminal of `PythonAnywhere` only. 

**NOTE**: The following **`.gitignore`** file **should be added** (I have not added it in this project).
```
*.pyc
*~
__pycache__
myvenv
db.sqlite3
/static
.DS_Store
```

Follow the following instructions for deployment: [Django Girls Deploy](https://tutorial.djangogirls.org/en/deploy/).

# Django URLs
URL is Universal Resource Locator. Django matches the requested URL to `URLconf` (a set of patterns) to find the correct view.

Check `mysite/urls.py` to find the list of `urlpatters`. `admin/` is added there by default. 
```python
urlpatterns = [
    path('admin/', admin.site.urls),
]
```
Though we are adding a lot of admin urls but all of them are not directly written here (readability).

### Adding Django URL
Changing current home url (http://127.0.0.1:8000/) (default 'Successful Installation' page) **-->>** home page of our blog app.

**Change `mysite/urls.py`**
Final file:
```python
from django.contrib import admin
from django.urls import path, include

urlpatterns = [
    path('admin/', admin.site.urls),
    path('', include('blog.urls')),
]
```

Now **create file `blog/urls.py`**. Add the following code:
```python
from django.urls import path
from . import views

urlpatterns = [
    path('', views.post_list, name='post_list'),
]
```

If you open the site right now, it will show error because:
- The home url (http://127.0.0.1:8000/) takes to `views.post_list` which does not exist yet.
`AttributeError: module object has no attribute post_list`

# Django Views
Django Views (places in `views.py` for each app) are basically python functions which request information from the `model` and pass it to a `template`.

Add the following to `blog/views.py`. Function `post_list` takes `request` and returns the value it gets from calling another function `render` that will render (put together) our `template blog/post_list.html` (which is not yet created).
```python
def post_list(request):
    return render(request, 'blog/post_list.html', {})
```

# Django Templates Introduction and HTML
Django templates present different information in consistent form and are written in `HTML`. The templates for app blog will be saved in `blog/templates/blog` (a good naming convention as project gets big).

Create file `post_list.html`. If you try running the server now, it will run with no errors but an empty page will appear.

Add the code below in `post_list.html` template:
```html
<html>
    <head>
        <title>Django Girls blog</title>
    </head>
    <body>
        <div>
            <h1><a href="/">Django Girls Blog</a></h1>
        </div>

        <div>
            <p>published: 14.06.2014, 12:14</p>
            <h2><a href="">My First post</a></h2>
            <p>Aenean eu leo quam. Pellentesque ornare sem lacinia quam venenatis vestibulum. Donec id elit non mi porta gravida at eget metus. Fusce dapibus, tellus ac cursus commodo, tortor mauris condimentum nibh, ut fermentum massa justo sit amet risus.</p>
        </div>

        <div>
            <p>published: 14.06.2014, 12:14</p>
            <h2><a href="">My Second post</a></h2>
            <p>Aenean eu leo quam. Pellentesque ornare sem lacinia quam venenatis vestibulum. Donec id elit non mi porta gravida at eget metus. Fusce dapibus, tellus ac cursus commodo, tortor mauris condimentum nibh, ut f.</p>
        </div>
    </body>
</html>
```
**NOTICE**: 
1. This is only showing the harcoded text but template is supposed to show different information in same format.
2. To deploy, commit and push to Github. Then, in pytonanywhere bash: `cd ~/<your-pythonanywhere-domain>.pythonanywhere.com && git pull origin master`.

# Databse: Django ORM and QuerySets
**ORM** - Django includes default Object Relational Mapping layer used to interact withh application data from various relational databases.
**QuerySets** - Its a list of objects of a model, can be filtered and ordered.
**Django Shell** - Run interactive Django Shell by `python3 manage.py shell`. Check out some commands to see objects of `Post and User`, to create (specifying different attribites) and publish (running the function of publish in the Post model) a post here, filter output of queries, and to order output objects.

**NOTICE**: Look at Query `Post.objects.filter(title__contains='title')`. Here, **two underscore characters** (_) between title and contains. Django's ORM uses this rule to *separate field* names ("title") and *operations* or filters ("contains").

# Dynamic Data in Templates
Here, we will display the posts of model `Post` from our database on the homepage.

**`views` decide which model to be displayed in a template and connect models and templates.** Thus in `post_list` view, take Post model data and pass to template, where it it will be displayed.

Add the following to the `post_list` view:
- import : `from .models import Post`. Also import `from django.utils import timezone` (not imp, just required here in queryset).
- QuerySet: `posts = Post.objects.filter(published_date__lte=timezone.now()).order_by('published_date')`
- Pass the result in form of dictionary. Currently we have: `return render(request, 'blog/post_list.html', {})`. Add `'posts':posts` in the dictionary.

Final blog/view.py:
```py
from django.shortcuts import render
from django.utils import timezone
from .models import Post

def post_list(request):
    posts = Post.objects.filter(published_date__lte=timezone.now()).order_by('published_date')
    return render(request, 'blog/post_list.html', {'posts': posts})
```

**Template Tags**: Django template tags allow us to transfer Python-like things into HTML, so you can build dynamic websites faster.

Here, we will add template tags to `post_list.html` template to show the list of posts in the browser.

To print a variable in Django templates, we use double curly brackets with the variable's name inside, like `{{ posts }}`.
Try adding:
1. `{{posts}}` directly in html.
2. ```
    {% for post in posts %}
        {{post}}
    {% endfor %}
3. Final `post_list.html`:
```html
<html>
    <head>
        <title>Django Girls blog</title>
    </head>
    <body>
        <div>
                <h1><a href="/">Django Girls Blog</a></h1>
        </div>

        {% for post in posts %}
            <div>
                <p>published: {{ post.published_date }}</p>
                <h2><a href="">{{ post.title }}</a></h2>
                <p>{{ post.text|linebreaksbr }}</p>
            </div>
        {% endfor %}
    </body>
</html>
```

You can also use *Template Extending*.