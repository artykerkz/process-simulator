/*
* File:   processTestCode.h
 * Author: Gerstl
 *
 * (C) 2025, all rights reserved.
 */


#include "processTestCode.h"
#include "processManagement.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int processTestOne() {
    /* super simple run for you to use to develop your code */
    /* we will walk through this sequence in class */
    processStructure* ps; /* heap allocated */
    int processes[4]; /* process ID for 4 processes */
    int i; /* for for loops */
    ps = (processStructure *) malloc(sizeof (processStructure));
    processScheduleInitialize(ps);
    /* note that we must ensure that processAdd does not return 0 as a valid
     * pid.
     */
    processes[0] = processAdd(ps, 0);
    if (RUNNING != getProcessStatus(ps, processes[0])) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    /* There's only one process, so the interrupt should start it again */
    if (processes[0] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[0] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (RUNNING != getProcessStatus(ps, processes[0])) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }

    processes[1] = processAdd(ps, processes[0]);
    /* should I allow students to schedule p[1] with an add? */
    if (RUNNABLE != getProcessStatus(ps, processes[1])) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    processes[2] = processAdd(ps, processes[0]);
    /* should I allow students to schedule p[1] with an add? */
    if (RUNNABLE != getProcessStatus(ps, processes[2])) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    /* p[0] waits for p[2]. p[1] should then start */
    /* check that p[1] is running */
    if (processes[0] != processGetRunningPID(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }

    if (RUNNING != getProcessStatus(ps, processes[0])) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    /* if we wait, the next process running will be */
    if (0 != processWaitFor(ps, processes[2])) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    /* recall. Round robin, so p2 should be running */
    if (RUNNING != getProcessStatus(ps, processes[1])) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (RUNNABLE != getProcessStatus(ps, processes[2])) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (SLEEPING != getProcessStatus(ps, processes[0])) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[2] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[1] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    processes[3] = processAdd(ps, processes[1]);
    /* should I allow students to schedule p2 with an add? */
    if (RUNNABLE != getProcessStatus(ps, processes[3])) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[2] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[3] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[1] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[2] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    /* p[2] exits. Note that p[0] was waiting, so it's ready now */
    if (0 != processExit(ps, processes[2])) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }

    /* at this point, only p[0]. p[1] and p[3] exist */
    if (processes[3] != processGetRunningPID(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (0 != processIORequest(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    /* at this point, p[3] is waiting for io. */
    if (processes[0] != processGetRunningPID(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[1] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[0] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (0 != processIODone(ps, processes[3])) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    /* now p[0]. p[1] and p[3] exist */
    if (processes[1] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[3] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[0] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[1] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[3] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processes[0] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    /* p[0] ends */
    processExit(ps, processes[0]);
    /* now all should be dead */
    for (i = 0; i < 4; ++i) {
        if (READY == getProcessStatus(ps, processes[i]) ||
                BLOCKED == getProcessStatus(ps, processes[i]) ||
                RUNNING == getProcessStatus(ps, processes[i])) {
            fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
            return(1);
        } /* if */
    } /* for */
    free(ps);
    ps = 0;

    return 0;
}

/* return 1 if the pid appears in 0..i in pids */
int processIDCheck(int pid, int * pids, int n, int i) {
    int j;
    assert(i<n);
    for (j=0;j<=i;++j) {
        if (pid == pids[j]) {
            return 1;
        }
    }
    return 0;
}

int processTestTwo() {
    /* More complex run based on a file or array (may repeat with a driver)  */
    /* super simple run for you to use to develop your code */
    /* we will walk through this sequence in class */
    processStructure* ps; /* heap allocated */
    int processes[NPROC + 1]; /* process ID for NPROC+1 processes */
    int i; /* for for loops */
    int parent;
    ps = (processStructure *) malloc(sizeof (processStructure));
    processScheduleInitialize(ps);
    /* allocate ALL of the processes (each child of the previous one) */
    processes[0] = processAdd(ps, 0);
    for (i = 1; i < NPROC; ++i) {
        parent = processes[i - 1];
        /* fix the border cases */
        /* to facilitate cleaning, (NPROC/4) will have parent 0
         * and (3*(PROC/4)) will have parent (NPROC/4)-1 */
        if ((3 * (NPROC / 4)) == i) {
            parent = processes[(NPROC / 4) - 1];
        }
        if ((NPROC / 4) == i) {
            parent = 0;
        }
        processes[i] = processAdd(ps, parent);
        // ensure the id is unique
        if (0 != processIDCheck(processes[i], processes, NPROC + 1, i-1)) {
            fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
            return 1;
        }
    }
    /* validate that the order is correct */
    for (i = 1; i < NPROC; ++i) {
        if (processTimerInterrupt(ps) != processes[i]) {
            fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
            return(1);
        }
    }
    /* get back to zero */
    if (processes[0] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    if (processGetRunningPID(ps) != processes[0]) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    /* knock out some of the middle */
    /* from n/4 to 3n/4 - these are a parent/child sequence*/
    fprintf(stderr, "Currently running %d and killing %d (slot %d)",
            processGetRunningPID(ps), processes[NPROC / 4], NPROC / 4);

    processExit(ps, processes[NPROC / 4]);
    /* allocate to fill as children of 0 */
    for (i = (NPROC / 4); i < (3 * (NPROC / 4)); ++i) {
        processes[i] = processAdd(ps, 0);
    }
    /* make sure you can't overallocate */
    if (0 != processAdd(ps, 0)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    /* cycle through the jobs, making sure it does the correct (arrival) order */
    /* order should be processes[0] to processes[(NPROC/4) - 1] then
     * processes[3*NPROC/4] to processes[NPROC -1 ] then
     *  processes[NPROC/4] to processes[(3*NPROC/4)-1 ] */
    if (processGetRunningPID(ps) != processes[0]) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    for (i = 1; i < (NPROC / 4); ++i) {
        if (processTimerInterrupt(ps) != processes[i]) {
            fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
            return(1);
        }
    }
    for (i = (3 * (NPROC / 4)); i < NPROC; ++i) {
        if (processTimerInterrupt(ps) != processes[i]) {
            fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
            return(1);
        }
    }
    for (i = (NPROC / 4); i < (3 * (NPROC / 4)); ++i) {
        if (processTimerInterrupt(ps) != processes[i]) {
            fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
            return(1);
        }
    }
    /* set back to [0] as running */
    if (processes[0] != processTimerInterrupt(ps)) {
        fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
        return(1);
    }
    /* kill job 1. All jobs but 0 and its children should die */
    fprintf(stderr, "Currently running %d and killing job %d\n",
            processGetRunningPID(ps),
            processes[1]);
    processExit(ps, processes[1]);
    /* cycle through the jobs, making sure it does the correct jobs */
    /* only [0] and [NPROC/4] to [(3*(NPROC/4)) - 1] */
    for (i = (NPROC / 4); i < (3 * (NPROC / 4)); ++i) {
        if (processTimerInterrupt(ps) != processes[i]) {
            fprintf(stderr, "Error at line %d in file %s", __LINE__, __FILE__);
            return(1);
        }
    }
    free(ps);
    ps = 0;
    return 0;
}

