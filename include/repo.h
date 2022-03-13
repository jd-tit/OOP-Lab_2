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

int repo_add_transaction(Repository *repo, Transaction transaction);
Repository* make_repository(void);
void destroy_repository(Repository* repo);
Transaction* repo_find_by_id(Repository* repo,  long id);

#endif //LAB2_DATASTORE_H
