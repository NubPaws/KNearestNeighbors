#include "ThreadPool.h"
#include "ExecutionStoppedException.h"

template<typename T>
void ThreadPool<T>::Job::call() {
	this->task(arg);
}

template<typename T>
ThreadPool<T>::ThreadPool(const size_t& maxNumThreads)
	: maxNumThreads(maxNumThreads) {
	threads.resize(maxNumThreads);
}

template<typename T>
void ThreadPool<T>::start() {
	for (size_t i = 0; i < maxNumThreads; i++) {
		threads[i] = std::thread(&ThreadPool::loop, this);
	}
}

template<typename T>
void ThreadPool<T>::queue(const Function& func, const T& t) {
	// Lock the queueMutex to add the job to it, therefore we won't have
	// a data race.
	{
		std::unique_lock<std::mutex> lock(queueMutex);
		Job job = { func, t };
		jobs.push(job);
	}
	// Notify the user waiting for the new job to check if we can continue.
	mutexCondition.notify_one();
}

template<typename T>
void ThreadPool<T>::stop() {
	{
		std::unique_lock<std::mutex> lock(queueMutex);
		shouldTerminate = true;
	}
	mutexCondition.notify_all();
	for (std::thread& activeThread : threads) {
		activeThread.join();
	}
	threads.clear();
}

template<typename T>
bool ThreadPool<T>::busy() {
	bool poolBusy;
	{
		std::unique_lock<std::mutex> lock(queueMutex);
		poolBusy = jobs.empty();
	}
	return poolBusy;
}

template<typename T>
typename ThreadPool<T>::Job ThreadPool<T>::getNextJob() {
	// Lock.
	std::unique_lock<std::mutex> lock(queueMutex);
	// Wait until the jobs queue has a task, or until we should terminate the program.
	mutexCondition.wait(lock, [this] {
		return !jobs.empty() || shouldTerminate;
	});
	// If we should terminate, do so.
	if (shouldTerminate)
		throw ExecutionStoppedException("Done Executing.");
	
	// If we are here then there is a job for us to do.
	// Take the job that we need to do.
	Job job = jobs.front();
	// Remove it from the queue.
	jobs.pop();
	
	return job;
}

template<typename T>
void ThreadPool<T>::loop() {
	while (true) {
		try {
			Job job = getNextJob();
			
			// Do the job we just received.
			job.call();
		} catch (ExecutionStoppedException& e) {
			return;
		}
	}
}

#include "Socket.h"
template class ThreadPool<TCPSocket>;
