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
bool recursive(size_t rows, size_t cols, size_t dailyNeed, const AvailabilityMatrix& avail, const size_t maxShifts, DailySchedule& sched, vector<size_t>& workedShifts);

bool isValid (const size_t maxShifts, size_t worker, vector<size_t>& workedShifts,DailySchedule& sched,size_t rows);

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
    size_t workers = avail[0].size();
    vector<size_t> workedShifts(workers,0);
    sched = DailySchedule(days, vector<Worker_T>(dailyNeed, INVALID_ID));

    return recursive(0,0,dailyNeed,avail, maxShifts, sched, workedShifts);


}

bool recursive(size_t rows, size_t cols, size_t dailyNeed, const AvailabilityMatrix& avail, const size_t maxShifts, DailySchedule& sched, vector<size_t>& workedShifts)
{
  if (rows == sched.size()){
    return true;
  }

  if(cols == dailyNeed){
    return recursive(rows+1, 0, dailyNeed, avail, maxShifts, sched, workedShifts);
  }

  for(size_t i = 0; i < workedShifts.size(); ++i){
      if(avail[rows][i] == 1){
          sched[rows][cols] = i;
          workedShifts[i] += 1;
          if(isValid(maxShifts, i, workedShifts, sched, rows)){
              if(recursive(rows, cols+1,dailyNeed,avail,maxShifts,sched,workedShifts)){
                return true;
              }
          }
          workedShifts[i] -= 1;
          sched[rows][cols] = INVALID_ID;
      }
  }

  return false;
}


bool isValid (const size_t maxShifts, size_t worker,vector<size_t>& workedShifts,DailySchedule& sched,size_t rows)
{
  if(workedShifts[worker] > maxShifts){
    return false;
  }

  return true;
}

