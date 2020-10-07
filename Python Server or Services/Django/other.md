# CORS
In views.py
```py
respose = HttpResponse() # or sth else
response['Access-Control-Allow-Origin'] = '*'
response['Access-Control-Allow-Headers'] = 'X-Requested-With,content-type,authorization'
response['Access-Control-Allow-Methods'] = 'GET, POST, OPTIONS, PUT, PATCH, DELETE'
return respose
```

In settings.py
```py
# Also add all hosts to ALLOWED_HOSTS

INSTALLED_APPS = [
    ...

    'corsheaders',
]

MIDDLEWARE = [
    ...

    'corsheaders.middleware.CorsMiddleware',
]

### CORS SETTINGS ###
CORS_ORIGIN_ALLOW_ALL = True
# CORS_ORIGIN_WHITELIST = (
#        'http://localhost:3000',
# )

# CSRF_TRUSTED_ORIGINS = [
#     'http://my.domain.com/',
# ]

CORS_ALLOW_HEADERS = [
    'accept',
    'accept-encoding',
    'authorization',
    'content-type',
    'dnt',
    'origin',
    'user-agent',
    'x-csrftoken',
    'x-requested-with',
]

CORS_ALLOW_CREDENTIALS = True
```

# Email
settings.py
```py
################## Email Config ##################
EMAIL_BACKEND = 'django.core.mail.backends.smtp.EmailBackend'
EMAIL_HOST = 'smtp.gmail.com'
EMAIL_PORT = 587 # will be diff for diff services
EMAIL_HOST_USER = 'sth@gmail.com'
EMAIL_HOST_PASSWORD = 'pass'
EMAIL_USE_TLS = True
EMAIL_USE_SSL = False
##################################################
```

send_mail
```py
return send_mail( # return 1/0 if mail sent or error?
        subject,
        body,
        'sth@gmail.com',
        [to_email],
        fail_silently=False,
    )
```