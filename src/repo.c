//
// Created by jdt on 2022-03-06.
//

#include <stdlib.h>

#include "repo.h"


int repo_add_transaction(Repository *repo, Transaction transaction) {
    // Add a Transaction to the Repository
    // pre: none extra
    // post: `transaction` is added to
    if(repo->crt_len == repo->max_len){
        return EXIT_FAILURE;
    }
    repo->transaction_log[repo->crt_len] = transaction;
    repo->crt_len += 1;
    return EXIT_SUCCESS;
}

Repository* make_repository(void){
    /** Create a repository
     * @pre: None
     * @post: Return a pointer to an empty Repository
     */
    Repository* repo = malloc(sizeof(Repository));
    repo->crt_len = 0;
    repo->max_len = MAX_LEN;
    return repo;
}

void destroy_repository(Repository* repo){
    //free(repo->transaction_log); // We aren't using dynamic allocation yet
    free(repo);
    repo = NULL;
}
