import threading  # Import the threading module to use threading capabilities
import time       # Import the time module to use sleep for delays

# Create a Condition object for thread synchronization
cond = threading.Condition()
done = 1  # A shared variable to control the flow between threads

# Define the task function to be run by each thread
def task(name):
    global done  # Indicate that we are using the global 'done' variable
    with cond:  # Acquire the condition variable
        if done == 1:
            # If 'done' is 1, wait for the condition
            done = 2  # Update 'done' to indicate this thread is waiting
            print("Waiting on conditional variable cond:", name)
            cond.wait()  # Wait for the condition to be notified
            print("Condition met:", name)  # This line runs after being notified
        else:
            # If 'done' is not 1, perform some work and then notify the condition
            for i in range(5):
                print(".")
                time.sleep(1)  # Simulate work by sleeping for 1 second
            print("Signalling condition variable cond:", name)
            cond.notify_all()  # Notify all waiting threads
            print("Notification done", name)

# Check if this script is being run as the main program
if __name__ == "__main__":
    # Create two threads, each running the task function with a different name
    t1 = threading.Thread(target=task, args=('t1',))  # 'args' must be a tuple
    t2 = threading.Thread(target=task, args=('t2',))

    # Start the threads
    t1.start()
    t2.start()

    # Wait for both threads to complete
    t1.join()
    t2.join()
