from django.shortcuts import redirect
from rest_framework.decorators import api_view
from .models import hacker_data
from .serializers import  MHN_serializer
from rest_framework.response import Response
from django.db import models







@api_view(['POST'])
def sever_api(request,format=None):
    ip_ = request.POST['client_ip']
    name = request.POST['honeybot_name']
    print(ip_)
    print(name)

    form  = hacker_data(hacker_ip=ip_,attack_port = 3333 , honeybot_name=name)
    form.save()

    #data = MHN_serializer(form,many=True).data
    hakerdata = hacker_data.objects.all()
    data = MHN_serializer(hakerdata,many=True).data
    return Response({'data':data})




@api_view(['GET'])
def mhn_monitor(request):
    if request.user.is_active == False:
        return redirect('login')
    monitor_data = hacker_data.objects.all()
    data = MHN_serializer(monitor_data, many=True).data

    return Response({'data':data})