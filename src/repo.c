//
// Created by jdt on 2022-03-06.
//

#include <stdlib.h>
#include <memory.h>

#include "repo.h"


int repo_add_transaction(Repository *repo, Transaction transaction) {
    // Add a Transaction to the Repository
    // pre: none extra
    // post: `transaction` is added to the repository
    if(push_back(repo->transactions, &transaction) == EXIT_FAILURE)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

Repository* make_repository(void){
    /** Create a repository
     * @pre: None
     * @post: Return a pointer to an empty Repository
     */
    Repository* repo = malloc(sizeof(Repository));
    repo->transactions = make_vector(TRANSACTION);
    return repo;
}

void destroy_repository(Repository* repo){
    destroy_vector(repo->transactions);
    free(repo);
    repo = NULL;
}

Transaction* repo_find_by_id(Repository* repo,  long id){
    Transaction* contents = repo->transactions->contents;
    for(size_t i = 0; i < repo->transactions->crt_len; ++i){
        if(contents[i].id == id){
            return &contents[i];
        }
    }
    return NULL;
}