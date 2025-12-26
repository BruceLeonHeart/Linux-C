#add_executable(server src/server.c)
add_executable(create_fifo.c src/fifo/create_fifo.c)
add_executable(write_fifo.c src/fifo/write_fifo.c)
add_executable(read_fifo.c src/fifo/read_fifo.c)
# add_executable(unlink_fifo.c src/fifo/unlink_fifo.c)

add_executable(msg_sender.c src/msg_queue/msg_sender.c)
add_executable(msg_receiver.c src/msg_queue/msg_receiver.c)

add_executable(shared_mem_writer.c src/shared_memory/shared_mem_writer.c)
add_executable(shared_mem_reader.c src/shared_memory/shared_mem_reader.c)

add_executable(sem_creator.c src/semaphores/sem_creator.c)
add_executable(sem_waiter.c src/semaphores/sem_waiter.c)
add_executable(sem_signaler.c src/semaphores/sem_signaler.c)