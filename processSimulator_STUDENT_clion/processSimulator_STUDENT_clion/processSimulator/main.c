#include <stdio.h>

/*
 * File:   main.c
 * Author: student
 *
 * Created on February 26, 2023, 1:04 PM
 */

#include "processManagement.h"
#include "processTestCode.h"
#include <stdio.h>
#include <stdlib.h>

/*
 *
 */
int main(int argc, char** argv) {
    int exit_status = EXIT_SUCCESS;
    if (0 != processTestOne()) {
        fprintf(stderr,"Failure in process test one\n");
        fflush(stderr);
        exit_status = EXIT_FAILURE;
    } else {
        fprintf(stderr,"Success in process test one\n");
    }
    if (0 != processTestTwo()) {
        fprintf(stderr,"Failure in process test two\n");
        fflush(stderr);
        exit_status = EXIT_FAILURE;
    } else {
        fprintf(stderr,"Success in process test two\n");
    }
    if (0 != processTestThree()) {
        fprintf(stderr,"Failure in process test three\n");
        fflush(stderr);
        exit_status = EXIT_FAILURE;
    } else {
        fprintf(stderr,"Success in process test three\n");
    }
    if (EXIT_SUCCESS==exit_status) {
        fprintf(stderr,"Tests Succeeded");
    } else {
        fprintf(stderr,"At least one test failed");
    }
    fflush(stderr);
    return (EXIT_SUCCESS);
}


