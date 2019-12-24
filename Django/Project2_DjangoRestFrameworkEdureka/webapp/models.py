from django.db import models

class employees(models.Model):
    firstname=models.CharField(max_length=20)
    lastname=models.CharField(max_length=20)
    emp_Id=models.IntegerField()

    def __str__(self):
        return self.firstname+" "+self.lastname