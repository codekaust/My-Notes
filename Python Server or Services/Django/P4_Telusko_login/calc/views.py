from django.shortcuts import render
from django.http import HttpResponse
from django.contrib.auth.models import auth

# Create your views here.
def home(request):
    if request.user.is_authenticated:
        un = request.user.username
    else:
        un = 'NONE'
    return render(request, "home.html", {'username':un})

def add(request):
    if request.user.is_authenticated:
        try:
            res = int(request.POST['num1'])+int(request.POST['num2'])
            return render(request, "result.html", {'result':res})
        except Exception as e:
            return HttpResponse("No POST data")
    else:
        return HttpResponse("Not Logged IN")