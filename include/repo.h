//
// Created by jdt on 2022-03-06.
//

#ifndef LAB2_DATASTORE_H
#define LAB2_DATASTORE_H

#include "domain.h"
#include "vector.h"

#define MAX_LEN 300

typedef struct Repository {
    Vector* transactions;
} Repository;

/**
 * Add a transaction to a given Repository.
 * @param repo - the repository to add the Transaction to
 * @param transaction - the transaction to be added
 * @return The exit code, either EXIT_SUCCESS or EXIT_FAILURE.
 */
int repo_add_transaction(Repository *repo, Transaction transaction);


/**
 * Create a repository
 * @return The new Repository object.
 */
Repository* make_repository(void);

/**
 * Deallocate a repository and its contents.
 * @param repo - the Repository ot be destroyed
 */
void destroy_repository(Repository* repo);

/**
 * Find a Transaction by its ID
 * @param repo - the repository to search in
 * @param id - the ID ot search for
 * @return A pointer to the Transaction if found, or NULL otherwise.
 */
Transaction* repo_find_by_id(Repository* repo,  long id);

#endif //LAB2_DATASTORE_H
