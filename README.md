                                     Starve free Reader writer problem
                                      
Readers-writers problem is a problem of process synchronization. In this problem there are two type of processes the Readers, which wants to read the shared resource and the Writers, which wants to modify the shared resourcse. There are three variations to this problem:

__First readers–writers problem:__

when there is atleast one reader accessing the resource, then new readers can also enter the critical section to read that resource, but writer can't access resources till each reader process is done.So, it may not get a chance to modify the resourcse as new readers may continiously enter to read the resource, leading the writer to starvation.

__Second readers–writers problem__

This is similar to the above problem, but here the preference is given to writers.The reader must wait until the last writer is done. so, readers may starve.

__Third readers–writers problem__

in this variant, priority is given to the resources in the order of their arrival. This problem therefore overcomes the problem of starvation of previous two problems and known as the Starve-Free-Readers-Writers-Problem.

__SEMAPHORES used and Shared variables used:__

**1. queue_mutex :** Maintains the order of arrival of readers and writers.

**2. reader_mutex :** Semaphore used to provide mutual exclusion to r_count (or readers count) variable currently executing in critical section.

**3. writer_mutex :** Semaphore used to prevent readers and writer/s from simultaneously executing Critical Section Code.

**4. read_count :**  Stores number of readers present in critical section at any instant.

**5. data :** Part of program that is shared among various threads.

__Reader function__

**Entery section:**

**-->** Reader tries to acquires queue_mutex Semaphore first, if it is already acquired, reader is added to queue for the given Semaphore.

**-->** After aquiring queue_mutex, it then tries to aquire reader_mutex Semaphore to modify reader_counter.

**-->** If it is the first reader, it tries to aquire read_count Semaphore to confirm there are no writers in the critical section.

**-->** It releases queue_mutex and reader_mutex before entering critical section.

**Critical section :** Reader reads the shared data variable.

__Exit section :__


**-->** Reader waits till it aquires read_mutex Semaphore to modify read_count variable.

**-->** If it is the last reader, it releases writer_mutex Semaphore.

**-->** reader_mutex Semaphore is released after modifying read_count value.

__Writer function__

**Entry section:**

**-->** Writer Enters the request queue and waits till it acquires the queue_mutex Semaphore.

**-->** Now it waits to aquire writer_mutex Semaphore and enter critical section.

**-->** "queue_mutex" Semaphore is released before entering critical section.

__Critical section :__  Writer modifies the shared data.

__Exit section :__ Writer releases the write_mutex semaphore.

