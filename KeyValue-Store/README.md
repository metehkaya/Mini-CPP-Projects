# Key-Value Store

The project is based on an efficient key-value store where users are able to add key-value pairs, get and delete values by key.

## Interface

Keys and values are strings.

Commands are "PUT", "GET" and "DELETE".

## Functionalities

The task is implemented in a multi-threaded way so that multiple users can access the key-value store.

Synchronization issues are dealt with to have no conflict.

A cache is implemented which means server has some memory limit.

Whenever certain amount of memory is reached, key-value pairs are evicted on LRU technique.

Non-least recently used key-value pairs are stored in persisting storage.
