/*
 * This ThreadPool class was implemented mainly based on the following
 * answer on StackOverflow by PhD AP EcE:
 * https://stackoverflow.com/a/32593825/3097239
 * 
 * 
 */
#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include <functional>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>
#include <queue>
#include <utility>

#include "Types.h"

template<typename T>
class ThreadPool {
public:
	typedef std::function<void(T)> Function;
	
	struct Job {
		Function task;
		T arg;
		
		void call();
	};
private:
	// This will tell the threads to stop looking for jobs to execute.
	bool shouldTerminate = false;
	
	// This will prevent data races to the job queue.
	std::mutex queueMutex;
	// Prevents data races to the job queue.
	std::condition_variable mutexCondition;
	// Allows threads to wait on new jobs or terminateion.
	std::vector<std::thread> threads;
	// The queue of jobs for the threads.
	std::queue<Job> jobs;
	// The max number of threads to have running at a given time (avoid starvation).
	const size_t maxNumThreads;
public:
	
	/**
	 * @brief Construct a new Thread Pool object
	 * 
	 * @param maxNumThreads The maximum number of threads to be ran.
	 * Can pass std::thread::hardware_concurrency() to get the max number
	 * of threads that are available for the system.
	 */
	ThreadPool(const size_t& maxNumThreads);
	
	/**
	 * @brief This function handles starting the threads. We want to set
	 * a limit to the amount of threads that we can create in order to
	 * prevent starvation. This is where the maxNumThreads will be used.
	 */
	void start();
	
	/**
	 * @brief Queues the next job to be done. Can either pass a void function
	 * that doesn't receive a parameter, or can pass a lambda expression as such
	 * [] { code }
	 * 
	 * @param job The function to execute on a seperate thread.
	 */
	void queue(const Function& func, const T& t);
	
	/**
	 * @brief Stops executing the threads in the pool.
	 */
	void stop();
	
	/**
	 * @brief Checks if there are jobs waiting to be executed.
	 * 
	 * @return true If there are jobs that are waiting to be executed.
	 * @return false If there are no jobs that are waiting to be executed.
	 */
	bool busy();
private:
	/**
	 * @brief A loop for the thread pool waiting for jobs to execute,
	 * executing them as they arrive and if we are out of threads to
	 * execute, waits until a thread finishes and queues to it the
	 * next job to be done.
	 */
	void loop();
	
	Job getNextJob();
};

#endif // _THREAD_POOL_H