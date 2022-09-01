list=[2,1,1,0,2,1]
for i in range(6):
    if(list[i]):
        continue
    left=list[:i]
    left.reverse()
    right=list[i+1:]
    Ll=len(left)
    Lr=len(right)
    if(Ll>=2):
        k=0
        while(k<Ll and left[k]==1):
            k+=1
        if(0<k<Ll and left[k]==2):
            print(i)
        k=0
        while(k<Ll and left[k]==2):
            k+=1
        if(0<k<Ll and left[k]==1):
            print(i)
    if(Lr>=2):
        k=0
        while(k<Lr and right[k]==1):
            k+=1
        if(0<k<Lr and right[k]==2):
            print(i)
        k=0
        while(k<Lr and right[k]==2):
            k+=1
        if(0<k<Lr and right[k]==1):
            print(i)