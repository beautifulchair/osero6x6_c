def convert(lis):
    if(lis==[]):
        return -1
    ans=0
    # lis.reverse()
    for i,x in enumerate(lis):
        ans+=x*4**i
    return ans
    

# def compare(la, lb):
#     anslis=[0 for _ in la]
#     for i in range(len(la)):
#         anslis[i] = (la[i]!=lb[i])
#     ans=0
#     for i,x in enumerate(anslis):
#         ans+=(x<<i)
#     return ans

def compare(la, lb):
    l=len(la)
    if(la==lb):
        return 0
    anslis=[(la[iii]!=lb[iii]) for iii in range(l)]
    i=0
    while(anslis[i]==0):
        i+=1
    start=i
    while(i<l and anslis[i]==1):
        i+=1
    end=i-1
    return end*6+start

kk=0
with open("available2.csv", "w") as fo:
    for q in [6,5,4,3]:
        for n in range(3**q):
            # b=[(n//(3**(q-1-j)))%3 for j in range(q)]
            b=[(n//(3**(jj)))%3 for jj in range(q)]
            for i in range(q):
                # i=q-1-i
                left=b[:i]
                left.reverse()
                right=b[i+1:]
                Ll=len(left)
                Lr=len(right)
                leftBlack=left.copy()
                leftWhite=left.copy()
                rightWhite=right.copy()
                rightBlack=right.copy()
                bf=0
                wf=0
                afterBlack=b
                afterWhite=b
                if(len(left)>=2 and left[0]==2):
                    k=0
                    while(left[k]==2 and k<Ll-1):
                        k+=1
                    if(left[k]==1):
                        bf=1
                        k=0
                        while(leftBlack[k]==2):
                            leftBlack[k]=1
                            k+=1
                if(len(left)>=2 and left[0]==1):
                    k=0
                    while(left[k]==1 and k<Ll-1):
                        k+=1
                    if(left[k]==2):
                        wf=1
                        k=0
                        while(leftWhite[k]==1):
                            leftWhite[k]=2
                            k+=1
                if(len(right)>=2 and right[0]==2):
                    k=0
                    while(right[k]==2 and k<Lr-1):
                        k+=1
                    if(right[k]==1):
                        bf=1
                        k=0
                        while(rightBlack[k]==2):
                            rightBlack[k]=1
                            k+=1
                if(len(right)>=2 and right[0]==1):
                    k=0
                    while(right[k]==1 and k<Lr-1):
                        k+=1
                    if(right[k]==2):
                        wf=1
                        k=0
                        while(rightWhite[k]==1):
                            rightWhite[k]=2
                            k+=1
                if(bf):
                    leftBlack.reverse()
                    afterBlack=leftBlack+[1]+rightBlack
                if(wf):
                    leftWhite.reverse()
                    afterWhite=leftWhite+[2]+rightWhite
                # print(b, afterBlack, afterWhite)
                # print(b, afterBlack, afterWhite)
                # print(f"b:{b}, i:{i} {afterBlack},{afterWhite}")
                # print(f"{kk} {kk+1} b:{b}, cb:{convert(b)} i:{i} {convert(afterBlack)},{convert(afterWhite)}")
                kk+=2
                # print(f"{convert(afterBlack)},{convert(afterWhite)}", file=fo)
                #print(f"{b}: {i}: {afterBlack}: {afterWhite}: {compare(afterBlack, b)},{compare(afterWhite, b)}", file=fo)
                print(f"{compare(afterBlack, b)},{compare(afterWhite, b)}", file=fo)
                # print(f"{compare(afterBlack, b)},{compare(afterWhite, b)}, q:{q}, b:{b}, {afterBlack}, {afterWhite}", file=fo)