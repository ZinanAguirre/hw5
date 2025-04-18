#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

/* finalSchedule recursion function that will backtrack and try all possible combinations for workers to work in a maxShifts.
This will have a similar style to a soduko game backtracking using a 2d array and checking if certain users are valid.
*/
bool finalSchedule(size_t rows, size_t cols, size_t dailyNeed, const AvailabilityMatrix& avail, const size_t maxShifts, DailySchedule& sched, vector<size_t>& workedShifts);

// An insertion will be valid as long as the worker when they are inserted to the shift does not over pass the maxshifts 
bool isValid (const size_t maxShifts, size_t worker, vector<size_t>& workedShifts);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    size_t days = avail.size();
    // number of workers
    size_t workers = avail[0].size();
    //A vector to keep track how many shifts each worker has worked
    vector<size_t> workedShifts(workers,0);
    //Assign each day and workers working that day to -1 so that we could fix and insert their worker Id properly.
    sched = DailySchedule(days, vector<Worker_T>(dailyNeed, INVALID_ID));

    return finalSchedule(0,0,dailyNeed,avail, maxShifts, sched, workedShifts);


}

bool finalSchedule(size_t rows, size_t cols, size_t dailyNeed, const AvailabilityMatrix& avail, const size_t maxShifts, DailySchedule& sched, vector<size_t>& workedShifts)
{
  //Once all rows are completed then we are done since all days of the schedule have been divided.
  if (rows == sched.size()){
    return true;
  }

// Once we have determine the daily need of workers needed for the day we go on to the next day and start that row by filling in the workers again.
  if(cols == dailyNeed){
    return finalSchedule(rows+1, 0, dailyNeed, avail, maxShifts, sched, workedShifts);
  }

// Use the vectorsize of the worked shifts to iteratate through each worker in the company.
  for(size_t i = 0; i < workedShifts.size(); ++i){
      //First we will check if the worker is available that day, if so then they are a potential candidiate to work and save time if they cant work.
      if(avail[rows][i] == 1){
          // We will palce their id in the schedule.
          sched[rows][cols] = i;
          // Then add one to show the shift they are about to work in.
          workedShifts[i] += 1;
          // Now we have to check if this insertion of worker to work on that day is valid and capable.
          if(isValid(maxShifts, i, workedShifts)){
            // If they are able to work and it is valid then we go onto the next slot for worker we could have to work on that day.
              if(finalSchedule(rows, cols+1,dailyNeed,avail,maxShifts,sched,workedShifts)){
                return true;
              }
          }
          // if it was not valid, then we have to redo the opertions such as remove their shift value and put back id to -1, and check the next worker.
          workedShifts[i] -= 1;
          sched[rows][cols] = INVALID_ID;
      }
  }

  return false;
}


// Helper function to make sure that the worker that will work that day will not overdue the amount of maximum shifts they can do in the span of days.
bool isValid (const size_t maxShifts, size_t worker,vector<size_t>& workedShifts)
{
  if(workedShifts[worker] > maxShifts){
    return false;
  }

  return true;
}

