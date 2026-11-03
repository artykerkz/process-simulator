/*
* File:   processTestCode.h
 * Author: Gerstl
 *
 * (C) 2025, all rights reserved.
 */


#include "processManagement.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* This is a test that students can write */
int processTestThree() {
    /* More complex run based on a file or array (may repeat with a driver)  */
    /* for next time */
    return 0;
}



/* find the next pid, unless we're the biggest, then find smallest
 * very non efficient
 */
int processTimerInterrupt(processStructure* ps) {
    // FILL IN
    int currentPID = ps->runningPID;

    if (currentPID != 0) {
        for (int i = 0; i < NPROC; i++) {
            if (ps->processes[i].pid == currentPID &&
                ps->processes[i].state == RUNNING) {
                ps->processes[i].state = READY;
                break;
    }
        }
    }

    int nextPID = -1;

    for (int i = 0; i < NPROC; i++) {
        int pid = ps->processes[i].pid;

        if (pid > currentPID &&
            ps->processes[i].state == READY &&
            (nextPID == -1 || pid < nextPID)) {
            nextPID = pid;
            }
    }

    if (nextPID == -1) {
        for (int i = 0; i < NPROC; i++) {
            int pid = ps->processes[i].pid;

            if (pid != 0 &&
                ps->processes[i].state == READY &&
                (nextPID == -1 || pid < nextPID)) {
                nextPID = pid;
                }
        }
    }

    if (nextPID == -1) {
        ps->runningPID = 0;
        return 0;
    }

    for (int i = 0; i < NPROC; i++) {
        if (ps->processes[i].pid == nextPID) {
            ps->processes[i].state = RUNNING;
            break;
        }
    }

    ps->runningPID = nextPID;
    return nextPID;
}

void processScheduleInitialize(processStructure* ps) {
    // FILL IN
    for (int i = 0; i < NPROC; i++) {
        ps->processes[i].pid = 0;
        ps->processes[i].parentPID = 0;
        ps->processes[i].waitingFor = 0;
        ps->processes[i].state = UNUSED;
    }

    ps->runningPID = 0;
    ps->nextPID = 1;
}

int processAdd(processStructure*ps, int parent) {
    // FILL IN
        int parentExists = (parent == 0);

        if (parent != 0) {
            for (int i = 0; i < NPROC; i++) {
                if (ps->processes[i].pid == parent &&
                    ps->processes[i].state != UNUSED &&
                    ps->processes[i].state != ZOMBIE) {
                    parentExists = 1;
                    break;
                    }
            }
        }

        if (!parentExists) {
            return 0;
        }

        int slot = -1;

        for (int i = 0; i < NPROC; i++) {
            if (ps->processes[i].state == UNUSED) {
                slot = i;
                break;
            }
        }

        if (slot == -1) {
            return 0;
        }

        int pid = ps->nextPID++;
        if (pid == 0) {
            pid = ps->nextPID++;
        }

        ps->processes[slot].pid = pid;
        ps->processes[slot].parentPID = parent;
        ps->processes[slot].waitingFor = 0;

        if (ps->runningPID == 0) {
            ps->processes[slot].state = RUNNING;
            ps->runningPID = pid;
        } else {
            ps->processes[slot].state = READY;
        }
    return pid;
}

int processGetRunningPID(processStructure* ps) {
    // FILL IN
    return ps->runningPID;
}

int processIORequest(processStructure* ps) {
    // FILL IN
    int currentPID = ps->runningPID;

    if (currentPID == 0) {
        return -1;
    }

    for (int i = 0; i < NPROC; i++) {
        if (ps->processes[i].pid == currentPID &&
            ps->processes[i].state == RUNNING) {
            ps->processes[i].state = SLEEPING;
            break;
            }
    }

    if (processTimerInterrupt(ps) == 0) {
        return -1;
    }

    return 0;
}

int processIODone(processStructure* ps, int processID) {
    // FILL IN
    if (processID == 0) {
        return -1;
    }

    for (int i = 0; i < NPROC; i++) {
        if (ps->processes[i].pid == processID) {
            if (ps->processes[i].state != SLEEPING ||
                ps->processes[i].waitingFor != 0) {
                return -1;
                }

            ps->processes[i].state = READY;
            return 0;
        }
    }

    return -1;
}

/* returns pid of the next process running */
int processWaitFor(processStructure* ps, int processID) {
    // FILL IN
    if (processID == 0 || processID == ps->runningPID) {
        return -1;
    }

    int targetExists = 0;

    for (int i = 0; i < NPROC; i++) {
        if (ps->processes[i].pid == processID &&
            ps->processes[i].state != UNUSED &&
            ps->processes[i].state != ZOMBIE) {
            targetExists = 1;
            break;
            }
    }

    if (!targetExists) {
        return -1;
    }

    int currentPID = ps->runningPID;

    if (currentPID == 0) {
        return -1;
    }

    for (int i = 0; i < NPROC; i++) {
        if (ps->processes[i].pid == currentPID) {
            ps->processes[i].state = SLEEPING;
            ps->processes[i].waitingFor = processID;
            break;
        }
    }

    processTimerInterrupt(ps);

    return 0;
}

int processExit(processStructure* ps, int processID) {
    // FILL IN
    if (processID == 0) {
        return -1;
    }

    int slot = -1;

    for (int i = 0; i < NPROC; i++) {
        if (ps->processes[i].pid == processID) {
            slot = i;
            break;
        }
    }

    if (slot == -1) {
        return -1;
    }

    for (int i = 0; i < NPROC; i++) {
        if (ps->processes[i].pid != 0 &&
            ps->processes[i].parentPID == processID) {
            int childPID = ps->processes[i].pid;
            processExit(ps, childPID);
            }
    }

    for (int i = 0; i < NPROC; i++) {
        if (ps->processes[i].pid != 0 &&
            ps->processes[i].waitingFor == processID) {
            ps->processes[i].waitingFor = 0;
            ps->processes[i].state = READY;
            }
    }

    int wasRunning = (ps->runningPID == processID);

    ps->processes[slot].pid = 0;
    ps->processes[slot].parentPID = 0;
    ps->processes[slot].waitingFor = 0;
    ps->processes[slot].state = UNUSED;

    if (wasRunning) {
        processTimerInterrupt(ps);
    }

    return 0;

}

processState getProcessStatus(processStructure* ps, int processID) {
    // FILL IN
    if (processID == 0) {
        return UNUSED;
    }

    for (int i = 0; i < NPROC; i++) {
        if (ps->processes[i].pid == processID) {
            return ps->processes[i].state;
        }
    }

    return UNUSED;
}
