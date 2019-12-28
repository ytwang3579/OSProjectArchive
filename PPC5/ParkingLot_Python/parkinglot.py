import threading
def MakeParkingLot(N):
    global sem
    global spots
    global spotsSync
    spots = [None for i in range(N)]
    sem = threading.Semaphore(value=N)
    spotsSync = threading.Semaphore()

def MakeCars(C):
    CarList = []
    for i in range(C):
        CarList.append(threading.Thread(target=Park, args=(i,)))
    return CarList

def Park(Car):
    global sem, spots, spotsSync
    sem.acquire()

    spotsSync.acquire()
    for i in range(len(spots)):
        if spots[i] is None:
            spots[i] = Car
            break
    snapshot = spots[:]
    spotsSync.release()
    print("Car %d got spot: %s" % (Car, snapshot))

    import time
    import random
    st = random.randrange(1,10)
    time.sleep(st)

    spotsSync.acquire()
    for i in range(len(spots)):
        if spots[i] == Car:
            spots[i] = None
            break
    myCopyshots = spots[:]
    spotsSync.release()
    print("Car %d left after %d sec, %s" % (Car, st, myCopyshots))

    sem.release()

if __name__ == '__main__':
    MakeParkingLot(5)
    cars = MakeCars(15)
    for i in range(15): cars[i].start()