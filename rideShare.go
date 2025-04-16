package main

import (
	"fmt"
	"math/rand"
	"os"
	"sync"
	"time"
)

const (
	WORKER_COUNT = 8
	TASK_COUNT   = 5
)
type RideRequest struct {
	id              int
	pickupLocation  string
	dropoffLocation string
}

// TaskQueue manages a thread-safe queue of ride requests
type TaskQueue struct {
	queue []RideRequest
	lock  sync.Mutex
}

//Enqueue adds request to the queue 
func (tq *TaskQueue) Enqueue(task RideRequest) {
	tq.lock.Lock()
	defer tq.lock.Unlock()
	tq.queue = append(tq.queue, task)
}

//Dequeue removes from the queue 
func (tq *TaskQueue) Dequeue() *RideRequest {
	tq.lock.Lock()
	defer tq.lock.Unlock()
	if len(tq.queue) == 0 {
		return nil
	}
	task := tq.queue[0]
	tq.queue = tq.queue[1:]
	return &task
}

var (
	taskQueue = &TaskQueue{}     
	results   = []string{}       
	resultsMu sync.Mutex         
	wg        sync.WaitGroup     
)

func main() {
	rand.Seed(time.Now().UnixNano()) 

	prepareRideRequests() 
	launchDrivers()       
	wg.Wait()             
	exportResults("results.txt") 

	fmt.Println("see results.txt for results.")
}

func prepareRideRequests() {
	for i := 1; i <= TASK_COUNT; i++ {
		req := RideRequest{
			id:              i,
			pickupLocation:  fmt.Sprintf("Pickup %d", i),
			dropoffLocation: fmt.Sprintf("Dropoff %d", i),
		}
		taskQueue.Enqueue(req)
	}
}

func launchDrivers() {
	for i := 1; i <= WORKER_COUNT; i++ {
		wg.Add(1)
		go driver(i)
	}
}

func driver(id int) {
	defer wg.Done()
	fmt.Printf("[Driver %d] Starting\n", id)
	for {
		task := taskQueue.Dequeue()
		if task == nil {
			break 
		}
		process(id, task)
	}
	fmt.Printf("[Driver %d] Finished.\n", id)
}

func process(driverID int, task *RideRequest) {
	time.Sleep(time.Duration(rand.Intn(1000)) * time.Millisecond) 
	log := fmt.Sprintf("[Driver %d] Completed Ride %d: %s to %s",
		driverID, task.id, task.pickupLocation, task.dropoffLocation)

	resultsMu.Lock()
	results = append(results, log)
	resultsMu.Unlock()
}

func exportResults(filename string) {
	file, err := os.Create(filename)
	if err != nil {
		fmt.Println("Error writing to file:", err)
		return
	}
	defer file.Close()

	for _, entry := range results {
		_, err := file.WriteString(entry + "\n")
		if err != nil {
			fmt.Println("Error writing entry:", err)
			return
		}
	}
}
