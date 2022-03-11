//
// Created by jdt on 2022-03-06.
//

#ifndef LAB2_DATASTORE_H
#define LAB2_DATASTORE_H

#include "domain.h"
#define MAX_LEN 300

typedef struct Repository {
    size_t max_len ;
    size_t crt_len;
    Transaction transaction_log[MAX_LEN];
} Repository;

int repo_add_transaction(Repository *repo, Transaction transaction);

Repository* make_repository(void);

void destroy_repository(Repository* repo);

#endif //LAB2_DATASTORE_H
