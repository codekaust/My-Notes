from django.shortcuts import render,redirect
from django.contrib.auth.models import User, auth

# Create your views here.
def reg(request):
    print("REGISTER",request.method)
    if request.method == 'GET':
        return render(request,'reg.html')
    else:
        email = request.POST['email']
        password = request.POST['password']

        user = User.objects.create_user(email = email, password=password, username=email)
        user.save()
        return redirect(to = '/') 
def login(request):
    print("LOGIN", request.method)
    if request.method == 'GET':
        return render(request,'login.html')
    else:
        print("LOGGING IN", request.POST['email'], request.POST['password'])
        user = auth.authenticate(request, username = request.POST['email'], password = request.POST['password'])
        if user is not None:
            auth.login(request, user)
            return redirect(to = '/') 
        else:
            return redirect(to = 'login')