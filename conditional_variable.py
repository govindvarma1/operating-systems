import threading
import time

cond = threading.Condition()
done = 1

def task(name):
    global done
    with cond:
        if done == 1:
            done = 2
            print("Waiting on conditional variable cond:", name)
            cond.wait()
            print("Condition met:", name)
        else:
            for i in range(5):
                print(".")
                time.sleep(1)
            print("Signalling condition variable cond:", name)
            cond.notify_all()
            print("Notification done", name)

if __name__ == "__main__":
    t1 = threading.Thread(target=task, args=('t1',))  # Ensure single argument is a tuple
    t2 = threading.Thread(target=task, args=('t2',))

    t1.start()
    t2.start()

    t1.join()
    t2.join()
